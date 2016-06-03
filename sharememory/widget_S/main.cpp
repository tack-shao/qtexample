#include <QtGui/QApplication>
#include "widget_s.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget_S w;
    w.show();
    
    return a.exec();
}
