#include "mysqltest.h"
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlDriver>
#include <QtGui>
#include <QMessageBox>

mysqltest::mysqltest()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    //   db.setDatabaseName("my.db");
    db.setHostName("192.168.0.107");
    db.setPort(3306);
    db.setDatabaseName("database");
    db.setUserName("root");
    db.setPassword("Zzerp123");
    if (!db.open())
    {
        QMessageBox::critical(0, "Cannot open database1",
                              "Unable to establish a database connection.",
                              QMessageBox::Cancel);
        return ;
    }

}


