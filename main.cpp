#include <QApplication>
#include <QtGui>
#include <QtSql>
#include <QSqlDatabase>
#include <QDebug>
#include "mainwindow.h"

int main(int argc, char *argv[]) {  
  QApplication a(argc, argv);
  MainWindow w;
  w.show();
  
  return a.exec();
}
