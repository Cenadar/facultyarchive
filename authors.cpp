#include "authors.h"
#include "ui_authors.h"

Authors::Authors(QWidget *parent): QWidget(parent), ui(new Ui::Authors) {
  ui->setupUi(this);

  db = QSqlDatabase::addDatabase("QMYSQL");
  db.setHostName("localhost");
  db.setDatabaseName("farch");
  db.setUserName("fviewer");
  db.setPassword("superpass");

  if (!db.open()) {
    qDebug() << db.lastError().text();
  } else {
    qDebug() << "Connection is well";
  }

  model = new QSqlTableModel(this, db);  
  model->setTable("authors");
  model->setEditStrategy(QSqlTableModel::OnFieldChange);
  model->select();
  ui->tableView->setModel(model);
//  model->removeColumn(0);
}

Authors::~Authors() {
  delete model;
  delete ui;
}

void Authors::on_delButton_clicked() {
  QModelIndex idx = ui->tableView->currentIndex();
  if (idx.row() == -1) return;

  QSqlQuery query(db);
  query.prepare("DELETE FROM authors WHERE au_id = :id;");
  query.bindValue(":id", model->index(idx.row(), 0).data().toInt());
  query.exec();
  model->select();
}

void Authors::on_addButton_clicked() {
  QSqlQuery query(db);
  query.exec("INSERT INTO authors(au_second_name, au_first_name, au_fathers_name) VALUES('', '', '')");
  model->select();
}
