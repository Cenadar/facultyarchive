#ifndef BOOKS_H
#define BOOKS_H

#include <QWidget>

namespace Ui {
  class Books;
}

class Books : public QWidget
{
  Q_OBJECT
  
public:
  explicit Books(QWidget *parent = 0);
  ~Books();
  
private:
  Ui::Books *ui;
};

#endif // BOOKS_H
