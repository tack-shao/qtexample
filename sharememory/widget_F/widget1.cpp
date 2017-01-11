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
        shareMemory.detach();//���ý����빲���ڴ�η���
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
    memcpy(to,from,qMin(size,shareMemory.size()));//���ݴӸý����п��������������ڴ���
    shareMemory.unlock();//�����ڲ����
}

void Widget1::on_pushButton_2_clicked()
{

}
