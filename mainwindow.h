#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>

namespace Ui {
  class MainWindow;
}

class MainWindow: public QMainWindow {
  Q_OBJECT
  
 public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();
  
private slots:
  void on_authorsButton_clicked();
  void on_facultiesButton_clicked();
  void on_departmentsButton_clicked();
  void on_booksButton_clicked();
  void on_pushButton_clicked();

private:
  Ui::MainWindow *ui;  
  QSqlDatabase _db;
};

#endif // MAINWINDOW_H
