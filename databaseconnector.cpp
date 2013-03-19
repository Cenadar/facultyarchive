#include "databaseconnector.h"

static void QSqlDatabase::init(const QSqlDatabase& db) {
  db = QSqlDatabase(QSqlDatabase::addDatabase("QMYSQL"));
  db.setHostName("localhost");
  db.setDatabaseName("farch");
  db.setUserName("fviewer");
  db.setPassword("superpass");
  db.open();
}
