#include "faculties.h"
#include "ui_faculties.h"

Faculties::Faculties(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::Faculties)
{
  ui->setupUi(this);
}

Faculties::~Faculties()
{
  delete ui;
}
