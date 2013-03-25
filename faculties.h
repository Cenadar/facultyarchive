#ifndef FACULTIES_H
#define FACULTIES_H

#include <QDialog>
#include <QtSql>
#include <QtGui>
#include <QSqlDatabase>
#include <QTableView>

namespace Ui {
  class Faculties;
}

class Faculties: public QDialog {
  Q_OBJECT
  
public:
  explicit Faculties(QSqlDatabase& db, QWidget *parent = 0);
  ~Faculties();
  
private slots:
  void on_delButton_clicked();

  void on_addButton_clicked();

private:
  Ui::Faculties *ui;
  QSqlRelationalTableModel* _model;
  QSqlDatabase* _db;
};

#endif // FACULTIES_H
