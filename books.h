#ifndef BOOKS_H
#define BOOKS_H

#include <QWidget>
#include <QtSql>
#include <QtGui>
#include <QSqlDatabase>
#include <QTableView>

namespace Ui {
  class Books;
}

class Books: public QWidget {
  Q_OBJECT
  
public:
  explicit Books(QWidget *parent = 0);
  ~Books();
  
private slots:
  void on_delButton_clicked();

  void on_addButton_clicked();

private:
  Ui::Books *ui;
  QSqlTableModel *model;
  QSqlDatabase db;
};

#endif // BOOKS_H
