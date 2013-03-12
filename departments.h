#ifndef DEPARTMENTS_H
#define DEPARTMENTS_H

#include <QWidget>

namespace Ui {
  class Departments;
}

class Departments : public QWidget
{
  Q_OBJECT
  
public:
  explicit Departments(QWidget *parent = 0);
  ~Departments();
  
private:
  Ui::Departments *ui;
};

#endif // DEPARTMENTS_H
