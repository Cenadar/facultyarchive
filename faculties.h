#ifndef FACULTIES_H
#define FACULTIES_H

#include <QWidget>

namespace Ui {
  class Faculties;
}

class Faculties : public QWidget
{
  Q_OBJECT
  
public:
  explicit Faculties(QWidget *parent = 0);
  ~Faculties();
  
private:
  Ui::Faculties *ui;
};

#endif // FACULTIES_H
