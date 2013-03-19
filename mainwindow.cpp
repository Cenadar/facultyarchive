#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "databaseconnector.h"
#include "authors.h"
#include "faculties.h"
#include "departments.h"
#include "books.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent),
    ui(new Ui::MainWindow) {
  ui->setupUi(this);
}

MainWindow::~MainWindow() {
  delete ui;
}

void MainWindow::on_authorsButton_clicked() {
  Authors w(this);
  w.show();
}

void MainWindow::on_facultiesButton_clicked() {
  Faculties w(this);
  w.show();
}

void MainWindow::on_departmentsButton_clicked() {
  Departments w(this);
  w.show();
}

void MainWindow::on_booksButton_clicked() {
  Books w(this);
  w.show();
}
