#include "yearstatistic.h"
#include "ui_yearstatistic.h"
#include "libs/nightcharts.h"
#include <cassert>
#include <QMap>

YearStatistic::YearStatistic(QSqlDatabase& db, QWidget *parent): QDialog(parent),
    ui(new Ui::YearStatistic), _db(&db) {
  ui->setupUi(this);  
}

void YearStatistic::paintEvent(QPaintEvent*) {
  QPainter painter;
  painter.begin(this);
  Nightcharts PieChart;
  PieChart.setType(Nightcharts::Histogramm);//{Histogramm,Pie,DPie};
  PieChart.setLegendType(Nightcharts::Vertical);//{Round,Vertical}
  PieChart.setCords(10, 10, 250, 280);

  QSqlQuery query;
  query.exec("SELECT au_birth_year, COUNT(*) FROM authors WHERE au_birth_year IS NOT NULL GROUP BY au_birth_year;");
  int total = 0;
  while(query.next()) {
    total += query.value(1).toInt();
  }
  if (query.first()) do {
    PieChart.addPiece(query.value(0).toString(), Qt::lightGray, 10000*query.value(1).toInt()/total*0.01);
  } while(query.next());

  PieChart.draw(&painter);
  PieChart.drawLegend(&painter);
  painter.end();
}

YearStatistic::~YearStatistic() {
  delete ui;
}
