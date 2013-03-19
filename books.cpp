#include "books.h"
#include "ui_books.h"
#include "databaseconnector.h"

Books::Books(QWidget *parent): QWidget(parent), ui(new Ui::Books) {
  ui->setupUi(this);

  db = QSqlDatabase::addDatabase("QMYSQL");
  db.setHostName("localhost");
  db.setDatabaseName("farch");
  db.setUserName("fviewer");
  db.setPassword("superpass");
  db.open();

  model = new QSqlTableModel(this, db);
  model->setTable("books");
  model->setEditStrategy(QSqlTableModel::OnFieldChange);
  model->select();
  ui->tableView->setModel(model);
//  model->removeColumn(0);
}

Books::~Books() {
  delete model;
  delete ui;
}

void Books::on_delButton_clicked(){
  QModelIndex idx = ui->tableView->currentIndex();
  if (idx.row() == -1) return;

  QSqlQuery query(db);
  query.prepare("DELETE FROM books WHERE bk_id = :id;");
  query.bindValue(":id", model->index(idx.row(), 0).data().toInt());
  query.exec();
  model->select();
}

void Books::on_addButton_clicked() {
  QSqlQuery query(db);
  query.exec("INSERT INTO books(bk_dp, bk_name, bk_size, bk_publisher, bk_year)"
             " VALUES (-1, '', NULL, NULL, NULL),");
  model->select();
}
