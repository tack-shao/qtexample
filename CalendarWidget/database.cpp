#include "database.h"
#include "event.h"
#define test 1

#if test
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QSqlRecord>
#endif
#include <QApplication>
#include <QDebug>

DataBase::DataBase(QObject *parent) :
    QObject(parent)
{

}

void DataBase::connectdb()
{
#if test
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    QString strDbName = QApplication::applicationDirPath() + "/plan.db";
    db.setDatabaseName(strDbName);
    if (!db.open()) {
        qFatal("Cannot open database");
        return;
    }

    QSqlQuery query;
    // We store the time as seconds because it's easier to query.
    query.exec("create table Event (id DATE primary key, content TEXT, startDate DATE, startTime INT, endDate DATE, endTime INT)");
    query.exec("insert into Event values('2016-04-13', 'Grocery shopping', '2014-01-01', 36000, '2014-01-01', 39600)");
    query.exec("insert into Event values('2016-04-15', 'Ice skating', '2014-01-01', 57600, '2014-01-01', 61200)");
    query.exec("insert into Event values('2016-04-16', 'Doctor''s appointment', '2014-01-15', 57600, '2014-01-15', 63000)");
    query.exec("insert into Event values('2016-04-18', 'Conference', '2014-01-24', 32400, '2014-01-28', 61200)");
#endif
}

bool DataBase::updateDb(const QString &content, const QString &dateId)
{
#if test
    QSqlQuery query;
    query.prepare("update Event set content = ? where id = ?");
    query.addBindValue(content);
    query.addBindValue(dateId);
    return query.exec();
#else
    qDebug() << content << dateId;
    return false;
#endif
}

QStringList DataBase::selectDb(const QString &dateId)
{
#if test
    QStringList eventDb;
    QSqlQuery query;
    query.prepare("select * from Event where id = ?");
    query.addBindValue(dateId);
    query.exec();

    while (query.next()) {

        eventDb << query.value(0).toString() << query.value(1).toString()
                << query.value(2).toString() << query.value(3).toString()
                << query.value(4).toString() << query.value(5).toString();
    }

    return eventDb;
#else
    return QStringList() << "";
#endif
}
