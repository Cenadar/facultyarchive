#ifndef IDRETRIEVER_H
#define IDRETRIEVER_H

#include <QWidget>
#include <QtSql>
#include <QtGui>
#include <QSqlDatabase>
#include <QDebug>

class IdRetriever {
 public:
  static int getId(QSqlDatabase& db,
                   const QString& table,
                   const QString& idColumnHeader,
                   const QString& nameColumnHeader,
                   const QString& title,
                   const QString& label,
                   QWidget* parent = 0) {
    bool ok;
    QSqlQuery q(db);
    q.prepare(QString("SELECT %1 FROM %2;").arg(nameColumnHeader, table));
    q.exec();
    if (q.lastError().isValid()) {
      qDebug() << q.executedQuery();
      qDebug() << q.lastError();
      return -1;
    }

    QStringList items;
    while(q.next()) items.append(q.value(0).toString());
    QString item = QInputDialog::getItem(parent, title, label, items, 0, false, &ok);
    if (!ok) return -1;

    q.prepare(QString("SELECT %1 FROM %2 WHERE %3 = :curName;").arg(idColumnHeader, table, nameColumnHeader));
    q.bindValue(":curName", item);
    q.exec();
    if (q.lastError().isValid()) {
      qDebug() << q.executedQuery();
      qDebug() << q.lastError();
      return -1;
    }
    if (!q.next()) return -1;

    return q.value(0).toInt();
  }
};

#endif // IDRETRIEVER_H
