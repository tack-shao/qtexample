#include <QtGui/QApplication>
#include "widget_f.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    WidGet_F w;
    w.show();
    
    return a.exec();
}
