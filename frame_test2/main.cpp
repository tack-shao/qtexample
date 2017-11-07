#include "tabframe.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TabFrame w;
    w.show();

    return a.exec();
}
