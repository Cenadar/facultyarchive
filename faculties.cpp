#include "faculties.h"
#include "ui_faculties.h"
#include "idretriever.h"

#include <QtCore>
#include <QtSql>
#include <QtGui>
#include <QSqlRelationalTableModel>

Faculties::Faculties(QSqlDatabase& db, QWidget *parent): QDialog(parent),
    ui(new Ui::Faculties), _db(&db) {
  ui->setupUi(this);

  _searchAgain = true;

  _model = new QSqlRelationalTableModel(this, *_db);
  _model->setTable("faculties");
  _model->setEditStrategy(QSqlTableModel::OnFieldChange);
  reloadTable();

  QTableView* view = ui->tableView;
  view->setModel(_model);
  view->setItemDelegate(new QSqlRelationalDelegate(view));
}

Faculties::~Faculties() {
  delete _model;
  delete ui;
}

void Faculties::on_delButton_clicked() {
  QModelIndex idx = ui->tableView->currentIndex();
  if (idx.row() == -1) return;

  QSqlQuery query(*_db);
  query.prepare("DELETE FROM books_authors WHERE bka_bk IN\n"
                "(SELECT bk_id FROM books WHERE bk_dp IN\n"
                "(SELECT dp_id FROM departments WHERE dp_fc = :id));");
  query.bindValue(":id", _model->index(idx.row(), 0).data().toInt());
  query.exec();

  query.prepare("DELETE FROM books WHERE bk_dp IN\n"
                "(SELECT dp_id FROM departments WHERE dp_fc = :id);");
  query.bindValue(":id", _model->index(idx.row(), 0).data().toInt());
  query.exec();

  query.prepare("DELETE FROM departments WHERE dp_fc = :id;");
  query.bindValue(":id", _model->index(idx.row(), 0).data().toInt());
  query.exec();

  query.prepare("DELETE FROM faculties WHERE fc_id = :id;");
  query.bindValue(":id", _model->index(idx.row(), 0).data().toInt());
  query.exec();

  if (query.lastError().isValid()) {
    qDebug() << query.lastQuery();
    qDebug() << query.lastError();
  }
  reloadTable();
}

void Faculties::on_addButton_clicked() {
  QSqlQuery query(*_db);
  query.prepare("INSERT INTO faculties(fc_name)"
                " VALUES ('');");
  query.exec();
  if (query.lastError().isValid()) {
    qDebug() << query.lastQuery();
    qDebug() << query.lastError();
  }
  reloadTable();
}

void Faculties::on_pushButtonSearch_clicked() {
  if (_searchAgain) {
    _searchAgain = false;
    QString textToFind = "'%" + ui->lineEditSearch->text() + "%'";
    _searchQuery.exec(QString("SELECT fc_id FROM faculties WHERE "
                              "fc_name LIKE %1;").arg(textToFind));
  }
  if (!_searchQuery.next() && !_searchQuery.first()) return;

  int nextId = _searchQuery.value(0).toInt();
  int row = 0;
  while(ui->tableView->model()->index(row, 0).data().toInt() != nextId) {++row;}

  ui->tableView->setCurrentIndex(ui->tableView->model()->index(row, 0));
}

void Faculties::on_lineEditSearch_textChanged(const QString&) {
  _searchAgain = true;
}

void Faculties::reloadTable() {
  _model->select();
  _searchAgain = true;
}
