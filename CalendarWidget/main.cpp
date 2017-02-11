#include "calendarwidget.h"
#include <QApplication>

#include <QDir>
#include <QMessageBox>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // 检查目录
//    QString strPath = a.applicationDirPath() + "/data/";
//    QDir dir(strPath);
//    if (!dir.exists()) {
//        dir.mkdir(strPath);
//    }

    Window w;
    w.show();

    return a.exec();
}
