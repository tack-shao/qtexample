#include "widget1.h"
#include "ui_widget1.h"

#include <QFileDialog>
#include <QBuffer>
#include <QDebug>
#include <QProcess>

Widget1::Widget1(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget1)
{
    ui->setupUi(this);
    shareMemory.setKey("share");
}

Widget1::~Widget1()
{
    delete ui;
}

void Widget1::on_pushButton_clicked()
{
    if(shareMemory.isAttached())
    {
        shareMemory.detach();//将该进程与共享内存段分离
    }

    QString filename = QFileDialog::getOpenFileName(this);
    QPixmap pixMap;
    pixMap.load(filename);
    ui->label->setPixmap(pixMap);
    uint32_t width  = pixMap.width();
    uint32_t height = pixMap.height();
    ui->label->resize(width, height);

    QBuffer buffer;
    QDataStream out(&buffer);
    buffer.open(QBuffer::ReadWrite);
    out << pixMap;
    qDebug()<<buffer.size();
    int size = buffer.size();
    if(!shareMemory.create(size))
    {
        qDebug()<<tr("can't create memory segment");
        qDebug()<<shareMemory.error();
        return;
    }

    qDebug()<<shareMemory.size();
    shareMemory.lock();
    char *to = (char*)shareMemory.data();
    const char *from = (char*)buffer.data().data();
    memcpy(to,from,qMin(size,shareMemory.size()));//数据从该进程中拷贝到共享数据内存中
    shareMemory.unlock();//共享内层解锁
}

void Widget1::on_pushButton_2_clicked()
{

}
