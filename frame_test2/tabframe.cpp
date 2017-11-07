#include "tabframe.h"
#include "ui_tabframe.h"

TabFrame::TabFrame(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TabFrame)
{
    ui->setupUi(this);
}

TabFrame::~TabFrame()
{
    delete ui;
}
