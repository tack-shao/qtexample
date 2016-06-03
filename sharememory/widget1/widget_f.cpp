#include "widget_f.h"
#include "ui_widget_f.h"

WidGet_F::WidGet_F(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WidGet_F)
{
    ui->setupUi(this);
}

WidGet_F::~WidGet_F()
{
    delete ui;
}
