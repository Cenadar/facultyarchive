#ifndef BOOKS_H
#define BOOKS_H

#include <QDialog>
#include <QtSql>
#include <QtGui>
#include <QSqlDatabase>
#include <QTableView>

namespace Ui {
  class Books;
}

class Books: public QDialog {
  Q_OBJECT
  
public:
  explicit Books(QSqlDatabase& db, QWidget *parent = 0);
  ~Books();
  
private slots:
  void on_delButton_clicked();

  void on_addButton_clicked();

private:
  Ui::Books *ui;
  QSqlRelationalTableModel* _model;
  QSqlDatabase* _db;
};

#endif // BOOKS_H
