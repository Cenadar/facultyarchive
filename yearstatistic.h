#ifndef YEARSTATISTIC_H
#define YEARSTATISTIC_H

#include <QDialog>
#include <QtSql>

namespace Ui {
  class YearStatistic;
}

class YearStatistic : public QDialog {
  Q_OBJECT
  
public:
  explicit YearStatistic(QSqlDatabase& db, QWidget *parent = 0);
  ~YearStatistic();
  
private:
  void paintEvent(QPaintEvent*);

  Ui::YearStatistic *ui;
  QSqlDatabase* _db;
};

#endif // YEARSTATISTIC_H
