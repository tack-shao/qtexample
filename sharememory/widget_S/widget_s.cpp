#include "widget_s.h"
#include "ui_widget_s.h"
#include <QBuffer>
#include <QDebug>

Widget_S::Widget_S(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget_S)
{
    ui->setupUi(this);
    shareMemory.setKey("share");//设置标志一定要与共享内存的标志一样
    this->on_pushButton_clicked();
}

Widget_S::~Widget_S()
{
    delete ui;
}

void Widget_S::on_pushButton_clicked()
{
    if(!shareMemory.attach())//将shareMemory与该进程绑定使之可以访问shareMemory里的内容
    {
        qDebug()<<tr("can't attach share memory");
    }
    QBuffer buffer;
    QDataStream in(&buffer);
    QPixmap pixMap;
    shareMemory.lock();//给shareMemory枷锁
    qDebug()<<shareMemory.size();
    buffer.setData((char*)shareMemory.constData(),shareMemory.size());//将shareMemeory里的数据放到buffer里
    buffer.open(QBuffer::ReadWrite);
    in>>pixMap;
    shareMemory.unlock();//将shareMemory解锁
    shareMemory.detach();//将shareMemeory与该进程分离
    ui->label->setPixmap(pixMap);

    uint32_t width  = pixMap.width();
    uint32_t height = pixMap.height();
    ui->label->resize(width, height);
}
