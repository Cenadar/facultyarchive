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
  explicit Authors(QSqlDatabase& db, QWidget *parent = 0);
  ~Authors();

  void paintEvent(QPaintEvent *);
  
private slots:
  void on_delButton_clicked();

  void on_addButton_clicked();

  void on_addBookButton_clicked();

  void on_tableView_clicked(const QModelIndex &);

private:
  Ui::Authors *ui;
  QSqlRelationalTableModel* _model;
  QSqlQueryModel* _modelBooks;
  QSqlDatabase* _db;
  int _currentId;
};

#endif // AUTHORS_H
