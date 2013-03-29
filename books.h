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

  void paintEvent(QPaintEvent *);
  
private slots:
  void on_delButton_clicked();
  void on_addButton_clicked();
  void on_tableView_clicked(const QModelIndex &);
  void on_addAuthorButton_clicked();
  void on_delAuthorButton_clicked();
  void on_pushButtonSearch_clicked();
  void on_lineEditSearch_textChanged(const QString&);

private:
  void reloadTable();

  Ui::Books *ui;
  QSqlRelationalTableModel* _model;
  QSqlQueryModel* _modelAuthors;
  QSqlDatabase* _db;
  int _currentId;
  QSqlQuery _searchQuery;
  bool _searchAgain;
};

#endif // BOOKS_H
