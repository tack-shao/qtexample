#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include "event.h"

class DataBase : public QObject
{
    Q_OBJECT
public:
    explicit DataBase(QObject *parent = 0);

    static void connectdb();
    static bool updateDb(const QString &content, const QString &dateId);
    static QStringList selectDb(const QString &dateId);
signals:

public slots:
};

#endif // DATABASE_H
