#ifndef DEPARTMENTS_H
#define DEPARTMENTS_H

#include <QDialog>
#include <QtSql>
#include <QtGui>
#include <QSqlDatabase>
#include <QTableView>

namespace Ui {
  class Departments;
}

class Departments: public QDialog {
  Q_OBJECT
  
public:
  explicit Departments(QSqlDatabase& db, QWidget *parent = 0);
  ~Departments();
  
private slots:
  void on_delButton_clicked();
  void on_addButton_clicked();
  void on_pushButtonSearch_clicked();
  void on_lineEditSearch_textChanged(const QString&);

private:
  void reloadTable();

  Ui::Departments *ui;  
  QSqlRelationalTableModel* _model;
  QSqlDatabase* _db;
  QSqlQuery _searchQuery;
  bool _searchAgain;
};

#endif // DEPARTMENTS_H
