#ifndef DATABASECONNECTOR_H
#define DATABASECONNECTOR_H

#include <QSqlDatabase>

class DatabaseConnector {
 public:
  static void init(QSqlDatabase& db);
};

#endif // DATABASECONNECTOR_H
