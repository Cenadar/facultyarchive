#include "books.h"
#include "ui_books.h"
#include "idretriever.h"
#include <cassert>

#include <QtCore>
#include <QtSql>
#include <QtGui>
#include <QSqlRelationalTableModel>

Books::Books(QSqlDatabase& db, QWidget *parent): QDialog(parent),
    ui(new Ui::Books), _db(&db) {
  ui->setupUi(this);

  _searchAgain = true;

  _model = new QSqlRelationalTableModel(this, *_db);
  _model->setTable("books");
  _model->setEditStrategy(QSqlTableModel::OnFieldChange);
  _model->setRelation(5, QSqlRelation("departments", "dp_id", "dp_name"));
  reloadTable();

  QTableView* view = ui->tableView;
  view->setModel(_model);
  view->setItemDelegate(new QSqlRelationalDelegate(view));

  _modelAuthors = new QSqlQueryModel(this);
  ui->tableAuthorsView->setModel(_modelAuthors);
}

Books::~Books() {
  delete _model;
  delete ui;
}

void Books::on_delButton_clicked(){
  QModelIndex idx = ui->tableView->currentIndex();
  if (idx.row() == -1) return;

  QSqlQuery query(*_db);
  query.prepare("DELETE FROM books_authors WHERE bka_bk = :id;");
  query.bindValue(":id", _model->index(idx.row(), 0).data().toInt());
  query.exec();

  query.prepare("DELETE FROM books WHERE bk_id = :id;");
  query.bindValue(":id", _model->index(idx.row(), 0).data().toInt());
  query.exec();

  if (query.lastError().isValid()) {
    qDebug() << query.lastQuery();
    qDebug() << query.lastError();
  }
  reloadTable();
}

void Books::on_addButton_clicked() {
  int dp_id = IdRetriever::getId(*_db, "departments", "dp_id", "dp_name",
                                 "Department", "Choose department", this);
  if (dp_id == -1) return;

  QSqlQuery query(*_db);
  query.prepare("INSERT INTO books(bk_dp, bk_name, bk_size, bk_publisher, bk_year)"
                " VALUES (:dp_id, '', NULL, NULL, NULL);");
  query.bindValue(":dp_id", dp_id);
  query.exec();
  if (query.lastError().isValid()) {
    qDebug() << query.lastQuery();
    qDebug() << query.lastError();
  }
  reloadTable();
}

void Books::paintEvent(QPaintEvent *) {
  QModelIndex idx = ui->tableView->currentIndex();
  if (idx.row() == -1) {
    _currentId = -1;
    _modelAuthors->clear();
  } else if (_currentId != _model->index(idx.row(), 0).data().toInt()) {
    _currentId = _model->index(idx.row(), 0).data().toInt();
    _modelAuthors->setQuery(QString("SELECT au_id, CONCAT(au_second_name, ' ',"
                                                  "au_first_name, ' ',"
                                                  "au_fathers_name) FROM authors"
                                    " WHERE au_id IN\n"
                                    "(SELECT bka_au FROM books_authors WHERE bka_bk = %1);").arg(_currentId));
    if (_modelAuthors->lastError().isValid()) {
      qDebug() << _modelAuthors->lastError();
    }
  }
}

void Books::on_tableView_clicked(const QModelIndex &) {
  paintEvent(NULL);
}

void Books::on_addAuthorButton_clicked() {
  QModelIndex idx = ui->tableView->currentIndex();
  if (idx.row() == -1) return;
  assert(_currentId == _model->index(idx.row(), 0).data().toInt());

  int author_id = IdRetriever::getIdWithQuery(*_db,
      QString("SELECT au_id, CONCAT(au_second_name, ' ',"
                                   "au_first_name, ' ',"
                                   "au_fathers_name) FROM authors"
                                   " WHERE au_id NOT IN\n"
              "(SELECT bka_bk FROM books_authors WHERE bka_au = %1);").arg(_currentId),
      "Authors", "Choose author", this);
  if (author_id == -1) return;

  QSqlQuery query(*_db);
  query.prepare("INSERT INTO books_authors(bka_au, bka_bk) VALUES(:au, :bk);");
  query.bindValue(":au", author_id);
  query.bindValue(":bk", _currentId);
  query.exec();

  if (query.lastError().isValid()) {
    qDebug() << query.lastQuery();
    qDebug() << query.lastError();
  }
  reloadTable();
}

void Books::on_delAuthorButton_clicked() {
  QModelIndex auIdx = ui->tableAuthorsView->currentIndex();
  QModelIndex bkIdx = ui->tableView->currentIndex();
  if (auIdx.row() == -1 || bkIdx.row() == -1) return;
  int au = _modelAuthors->index(auIdx.row(), 0).data().toInt();
  int bk = _model->index(bkIdx.row(), 0).data().toInt();

  QSqlQuery query(*_db);
  query.prepare("DELETE FROM books_authors WHERE bka_au = :au AND bka_bk = :bk;");
  query.bindValue(":au", au);
  query.bindValue(":bk", bk);
  query.exec();

  if (query.lastError().isValid()) {
    qDebug() << query.lastQuery();
    qDebug() << query.lastError();
  }
  reloadTable();
  paintEvent(NULL);
}

void Books::on_pushButtonSearch_clicked() {
  if (_searchAgain) {
    _searchAgain = false;
    QString textToFind = "'%" + ui->lineEditSearch->text() + "%'";
    _searchQuery.exec(QString("SELECT bk_id FROM books WHERE "
                              "bk_name LIKE %1;").arg(textToFind));
  }
  if (!_searchQuery.next() && !_searchQuery.first()) return;

  int nextId = _searchQuery.value(0).toInt();
  int row = 0;
  while(ui->tableView->model()->index(row, 0).data().toInt() != nextId) {++row;}

  ui->tableView->setCurrentIndex(ui->tableView->model()->index(row, 0));
}

void Books::on_lineEditSearch_textChanged(const QString&) {
  _searchAgain = true;
}

void Books::reloadTable() {
  _model->select();
  _searchAgain = true;
}
