#include <QtGui/QApplication>
#include "mainwindow.h"
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTextCodec::setCodecForTr(QTextCodec::codecForLocale()); //显示正常
//    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8")); //显示为乱码
//    QTextCodec::setCodecForTr(QTextCodec::codecForName("GB2312")); //显示正常
    MainWindow w;
    w.show();
    
    return a.exec();
}
