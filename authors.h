#ifndef AUTHORS_H
#define AUTHORS_H

#include <QDialog>
#include <QtSql>
#include <QtGui>
#include <QSqlDatabase>
#include <QTableView>

namespace Ui {
  class Authors;
}

class Authors: public QDialog {
  Q_OBJECT
  
public:
  explicit Authors(QWidget *parent = 0);
  ~Authors();
  
private slots:
  void on_delButton_clicked();

  void on_addButton_clicked();

private:
  Ui::Authors *ui;
  QSqlTableModel *model;
  QSqlDatabase db;
};

#endif // AUTHORS_H
