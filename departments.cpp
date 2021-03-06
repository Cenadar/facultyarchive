#include "departments.h"
#include "ui_departments.h"
#include "idretriever.h"

#include <QtCore>
#include <QtSql>
#include <QtGui>
#include <QSqlRelationalTableModel>

Departments::Departments(QSqlDatabase& db, QWidget *parent): QDialog(parent),
    ui(new Ui::Departments), _db(&db) {
  ui->setupUi(this);

  _searchAgain = true;

  _model = new QSqlRelationalTableModel(this, *_db);
  _model->setTable("departments");
  _model->setEditStrategy(QSqlTableModel::OnFieldChange);
  _model->setRelation(2, QSqlRelation("faculties", "fc_id", "fc_name"));
  reloadTable();

  QTableView* view = ui->tableView;
  view->setModel(_model);
  view->setItemDelegate(new QSqlRelationalDelegate(view));
}

Departments::~Departments() {
  delete _model;
  delete ui;
}

void Departments::on_delButton_clicked() {
  QModelIndex idx = ui->tableView->currentIndex();
  if (idx.row() == -1) return;

  QSqlQuery query(*_db);
  query.prepare("DELETE FROM books_authors WHERE bka_bk IN "
                "(SELECT bk_id FROM books WHERE bk_dp = :id);");
  query.bindValue(":id", _model->index(idx.row(), 0).data().toInt());
  query.exec();

  query.prepare("DELETE FROM books WHERE bk_dp = :id;");
  query.bindValue(":id", _model->index(idx.row(), 0).data().toInt());
  query.exec();

  query.prepare("DELETE FROM departments WHERE dp_id = :id;");
  query.bindValue(":id", _model->index(idx.row(), 0).data().toInt());
  query.exec();

  if (query.lastError().isValid()) {
    qDebug() << query.lastQuery();
    qDebug() << query.lastError();
  }
  reloadTable();
}

void Departments::on_addButton_clicked() {
  int fc_id = IdRetriever::getId(*_db, "faculties", "fc_id", "fc_name",
                                 "Faculty", "Choose faculty", this);
  if (fc_id == -1) return;

  QSqlQuery query(*_db);
  query.prepare("INSERT INTO departments(dp_fc, dp_name)"
                " VALUES (:fc_id, '');");
  query.bindValue(":fc_id", fc_id);
  query.exec();
  if (query.lastError().isValid()) {
    qDebug() << query.lastQuery();
    qDebug() << query.lastError();
  }
  reloadTable();
}

void Departments::on_pushButtonSearch_clicked() {
  if (_searchAgain) {
    _searchAgain = false;
    QString textToFind = "'%" + ui->lineEditSearch->text() + "%'";
    _searchQuery.exec(QString("SELECT dp_id FROM departments WHERE "
                              "dp_name LIKE %1;").arg(textToFind));
  }
  if (!_searchQuery.next() && !_searchQuery.first()) return;

  int nextId = _searchQuery.value(0).toInt();
  int row = 0;
  while(ui->tableView->model()->index(row, 0).data().toInt() != nextId) {++row;}

  ui->tableView->setCurrentIndex(ui->tableView->model()->index(row, 0));
}

void Departments::on_lineEditSearch_textChanged(const QString&) {
  _searchAgain = true;
}

void Departments::reloadTable() {
  _model->select();
  _searchAgain = true;
}
