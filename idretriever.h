#ifndef IDRETRIEVER_H
#define IDRETRIEVER_H

#include <QWidget>
#include <QtSql>
#include <QtGui>
#include <QSqlDatabase>
#include <QDebug>
#include <cassert>

class IdRetriever {
 public:
  static int getIdWithQuery(QSqlDatabase& db,
                            const QString& queryString,
                            const QString& title,
                            const QString& label,
                            QWidget* parent = 0) {
    bool ok;
    QSqlQuery q(db);
    q.exec(queryString);
    if (q.lastError().isValid()) {
      qDebug() << q.executedQuery();
      qDebug() << q.lastError();
      return -1;
    }

    QList<int> ids;
    QStringList items;
    assert(q.record().count() == 2);
    while(q.next()) {
      ids.append(q.value(0).toInt());
      items.append(q.value(1).toString());
    }
    QString item = QInputDialog::getItem(parent, title, label, items, 0, false, &ok);
    if (!ok) return -1;

    return ids.at(items.indexOf(item));
  }

  static int getId(QSqlDatabase& db,
                   const QString& table,
                   const QString& idColumnHeader,
                   const QString& nameColumnHeader,
                   const QString& title,
                   const QString& label,
                   QWidget* parent = 0) {
    return getIdWithQuery(
          db, QString("SELECT %1, %2 FROM %3;").arg(idColumnHeader, nameColumnHeader, table),
          title, label, parent);
  }
};

#endif // IDRETRIEVER_H
