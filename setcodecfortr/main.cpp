#include <QtGui/QApplication>
#include "mainwindow.h"
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTextCodec::setCodecForTr(QTextCodec::codecForLocale()); //��ʾ����
//    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8")); //��ʾΪ����
//    QTextCodec::setCodecForTr(QTextCodec::codecForName("GB2312")); //��ʾ����
    MainWindow w;
    w.show();
    
    return a.exec();
}
