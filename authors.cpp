#include "authors.h"
#include "ui_authors.h"
#include "databaseconnector.h"
#include "idretriever.h"
#include <cassert>

#include <QtCore>
#include <QtSql>
#include <QtGui>
#include <QSqlRelationalTableModel>

Authors::Authors(QSqlDatabase& db, QWidget *parent): QDialog(parent),
    ui(new Ui::Authors), _db(&db) {
  ui->setupUi(this);

  _currentId = -1;

  _model = new QSqlRelationalTableModel(this, *_db);
  _model->setTable("authors");
  _model->setEditStrategy(QSqlTableModel::OnFieldChange);
  _model->select();  

  QTableView* view = ui->tableView;
  view->setModel(_model);
  view->setItemDelegate(new QSqlRelationalDelegate(view));

  _modelBooks = new QSqlQueryModel(this);
  ui->tableBooksView->setModel(_modelBooks);
}

Authors::~Authors() {
  delete _model;
  delete _modelBooks;
  delete ui;
}

void Authors::on_delButton_clicked() {
  QModelIndex idx = ui->tableView->currentIndex();
  if (idx.row() == -1) return;

  QSqlQuery query(*_db);
  query.prepare("DELETE FROM books_authors WHERE bka_au = :id;");
  query.bindValue(":id", _model->index(idx.row(), 0).data().toInt());
  query.exec();

  query.prepare("DELETE FROM authors WHERE au_id = :id;");
  query.bindValue(":id", _model->index(idx.row(), 0).data());
  query.exec();

  if (query.lastError().isValid()) {
    qDebug() << query.lastQuery();
    qDebug() << query.lastError();
  }
  _model->select();
}

void Authors::on_addButton_clicked() {
  QSqlQuery query(*_db);
  query.exec("INSERT INTO authors(au_second_name, au_first_name, au_fathers_name)\n"
             "VALUES('', '', '')");
  _model->select();
}

void Authors::on_addBookButton_clicked() {
  QModelIndex idx = ui->tableView->currentIndex();
  if (idx.row() == -1) return;
  assert(_currentId == _model->index(idx.row(), 0).data().toInt());

  int book_id = IdRetriever::getIdWithQuery(*_db,
      QString("SELECT bk_id, bk_name FROM books WHERE bk_id NOT IN\n"
              "(SELECT bka_bk FROM books_authors WHERE bka_au = %1);").arg(_currentId),
              "Books", "Choose book", this);
  if (book_id == -1) return;

  QSqlQuery query(*_db);
  query.prepare("INSERT INTO books_authors(bka_au, bka_bk) VALUES(:au, :bk);");
  query.bindValue(":au", _currentId);
  query.bindValue(":bk", book_id);
  query.exec();

  if (query.lastError().isValid()) {
    qDebug() << query.lastQuery();
    qDebug() << query.lastError();
  }
  _model->select();
}

void Authors::paintEvent(QPaintEvent *) {
  QModelIndex idx = ui->tableView->currentIndex();
  if (idx.row() == -1) {
    _currentId = -1;
    _modelBooks->clear();
  } else if (_currentId != _model->index(idx.row(), 0).data().toInt()) {
    _currentId = _model->index(idx.row(), 0).data().toInt();
    _modelBooks->setQuery(QString("SELECT bk_name FROM books WHERE bk_id IN\n"
                                  "(SELECT bka_bk FROM books_authors WHERE bka_au = %1);").arg(_currentId));
    if (_modelBooks->lastError().isValid()) {
      qDebug() << _modelBooks->lastError();
    }
  }
}

void Authors::on_tableView_clicked(const QModelIndex &) {
  paintEvent(NULL);
}
