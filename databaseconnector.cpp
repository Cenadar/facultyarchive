#include "databaseconnector.h"
#include <QDebug>
#include <QtSql>

void DatabaseConnector::init(QSqlDatabase& db) {
  db = QSqlDatabase(QSqlDatabase::addDatabase("QMYSQL"));
  db.setHostName("localhost");
  db.setDatabaseName("farch");
  db.setUserName("fviewer");
  db.setPassword("superpass");
  if (!db.open()) {
    qDebug() << db.lastError().text();
  }
}
