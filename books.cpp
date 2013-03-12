#include "books.h"
#include "ui_books.h"

Books::Books(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::Books)
{
  ui->setupUi(this);
}

Books::~Books()
{
  delete ui;
}
