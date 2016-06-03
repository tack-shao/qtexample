#include <QtGui/QApplication>
#include "widget1.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget1 w;
    w.show();
    
    return a.exec();
}
