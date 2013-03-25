#ifndef FACULTIES_H
#define FACULTIES_H

#include <QDialog>

namespace Ui {
  class Faculties;
}

class Faculties: public QDialog {
  Q_OBJECT
  
public:
  explicit Faculties(QWidget *parent = 0);
  ~Faculties();
  
private:
  Ui::Faculties *ui;
};

#endif // FACULTIES_H
