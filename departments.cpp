#include "departments.h"
#include "ui_departments.h"

Departments::Departments(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::Departments)
{
  ui->setupUi(this);
}

Departments::~Departments()
{
  delete ui;
}
