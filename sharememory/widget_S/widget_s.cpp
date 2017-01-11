#include "widget_s.h"
#include "ui_widget_s.h"
#include <QBuffer>
#include <QDebug>

Widget_S::Widget_S(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget_S)
{
    ui->setupUi(this);
    shareMemory.setKey("share");//���ñ�־һ��Ҫ�빲���ڴ�ı�־һ��
    this->on_pushButton_clicked();
}

Widget_S::~Widget_S()
{
    delete ui;
}

void Widget_S::on_pushButton_clicked()
{
    if(!shareMemory.attach())//��shareMemory��ý��̰�ʹ֮���Է���shareMemory�������
    {
        qDebug()<<tr("can't attach share memory");
    }
    QBuffer buffer;
    QDataStream in(&buffer);
    QPixmap pixMap;
    shareMemory.lock();//��shareMemory����
    qDebug()<<shareMemory.size();
    buffer.setData((char*)shareMemory.constData(),shareMemory.size());//��shareMemeory������ݷŵ�buffer��
    buffer.open(QBuffer::ReadWrite);
    in>>pixMap;
    shareMemory.unlock();//��shareMemory����
    shareMemory.detach();//��shareMemeory��ý��̷���
    ui->label->setPixmap(pixMap);

    uint32_t width  = pixMap.width();
    uint32_t height = pixMap.height();
    ui->label->resize(width, height);
}
