#include <QCoreApplication>
#include "qsshsocket.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    qDebug() <<"==begin===\n";
    QSshSocket *sshtest = new QSshSocket();
    sshtest->connectToHost("192.168.59.132");
    sshtest->login("weilaidb", "00000000");
    sshtest->start();

    qDebug() <<"isConnected():" << sshtest->isConnected();
    qDebug() <<"==end===\n";
    return a.exec();
}
