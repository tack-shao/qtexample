#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>



#if 1
//编码汉字
//#define str_china(A)     QString::fromLocal8Bit(#A)
#define str_china(A)     QString::fromLocal8Bit(A)
//#define str_china(A)     QString::fromUtf8(#A)
#else
#define str_china(A)     codec->toUnicode(#A)
#endif



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::drawLine(int x1, int y1, int x2, int y2,QString text)
{
    qDebug() << "x1, y1, x2, y2" << "(" << x1 << "," << y1 << "), "
                << "(" << x2 << "," << y2 << "), ";
    QPainter painter(this);
    // 反走样
    painter.setRenderHint(QPainter::Antialiasing, true);
    // 设置画笔颜色
    painter.setPen(QPen(Qt::red,5,Qt::SolidLine));
    // 绘制直线
    painter.drawLine(QPointF(x1, y1), QPointF(x2, y2));
    // 设置画笔颜色
    painter.setPen(QPen(Qt::blue,10,Qt::SolidLine));

    painter.drawPoint(x1,  y1);
    painter.drawPoint(x2,  y2);
    painter.drawText((x1 + x2)/2, y1, text);
    const int offset = 10;
    painter.drawText(x1 + offset, y1, QString("%1").arg(x1));
    painter.drawText(x2 + offset, y2, QString("%1").arg(x2));
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    static quint32 count = 0;

    qDebug() << "paintEvent-------------------------------->> " << count++;

#if 0
    //    drawLine(100, height()/ 2, 200, height() / 2, "0x1A6F");
    const int heightoff = 15;
    const int heightbegin = 30;


    for (int i = 0; i < 10;i ++)
    {
        drawLine(100 + i*10, heightbegin + i*heightoff,
                 200 + i*20, heightbegin + i*heightoff,
                 "0x1A6F");
    }
#else
    const int heightoff = 15;
    const int heightbegin = 30;
    int i = 0;

    if(vecLineFmts.size() == 0)
    {
        for (int i = 0; i < 10;i ++)
        {
            drawLine(100 + i*10, heightbegin + i*heightoff,
                     200 + i*20, heightbegin + i*heightoff,
                     "0x1A6F test");
        }
    }


    QVector<LineFormat>::iterator it;
    for (it = vecLineFmts.begin(); it != vecLineFmts.end(); ++it)
    {
       LineFormat &lfmtex = (*it);
       drawLine(lfmtex.cbegint - firsttime, heightbegin + i*heightoff,
                lfmtex.cendint - firsttime, heightbegin + i*heightoff,
                lfmtex.tips);
       i++;
    }

#endif



    //    QPainter painter(this);
    //    // 反走样
    //    painter.setRenderHint(QPainter::Antialiasing, true);
    //    // 设置画笔颜色
    //    painter.setPen(QColor(0, 160, 230));
    //    // 绘制直线
    //    painter.drawLine(QPointF(100, height()/ 2), QPointF(200, height() / 2));
    //    // 设置画笔颜色
    //    painter.setPen(QColor(244, 0, 230));
    //    painter.setPen(QPen(Qt::blue,10,Qt::DashLine));

    //    painter.drawPoint(100,  height()/ 2);
    //    painter.drawLine(QPointF(0, height()), QPointF(width() / 2, height() / 2));
}


void MainWindow::on_pushButton_clicked()
{
    //加载文件,格式如下
    /*
begintime  endtime  string
10         20       "cpl"



*/
    LineFormat lfmt;
    vecLineFmts.clear();

    QStringList textcont;
    textcont.clear();

    QString filename = QFileDialog::getOpenFileName(this);
    qDebug() << "open filename "<< filename;


    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug()<<"Can't open the file!"<<endl;
        QMessageBox::warning(NULL, str_china("提示"), str_china("Can't open the file"),NULL,NULL);
        return;
    }
    while(!file.atEnd()) {
        QByteArray line = file.readLine();
        QString str(line.trimmed());
        if (str.length() > 0)
        {
            textcont.append(str);
//            qDebug()<< str;
        }
    }

    qDebug()<< "Got Info\n";
    loadflag = 0;
    for ( QStringList::Iterator it = textcont.begin(); it != textcont.end(); ++it )
    {
        qDebug() << *it ;
        QString tmp = *it;
        QStringList lst = tmp.split(' ');
        for ( QStringList::Iterator it2 = lst.begin(); it2 != lst.end(); ++it2 )
        {
            qDebug() << *it2 ;
        }
        bool ok;
        lfmt.begintime.mHour = lst.at(0).mid(0,2).toInt(&ok, 10);
        lfmt.begintime.mMin  = lst.at(0).mid(3,2).toInt(&ok, 10);
        lfmt.begintime.mSec  = lst.at(0).mid(6,2).toInt(&ok, 10);
        lfmt.begintime.mMsec = lst.at(0).mid(9,3).toInt(&ok, 10);

        lfmt.cbegint =  lfmt.begintime.mSec *1000 + lfmt.begintime.mMsec;
        if(!loadflag){
            loadflag = 1;
            firsttime    = lfmt.begintime.mSec *1000 + lfmt.begintime.mMsec;
            firsttime -= 20;
        }
        qDebug() << "firsttime : "<< firsttime;
        qDebug() << "begin h-m-s-ms begt" << lfmt.begintime.mHour
                    << lfmt.begintime.mMin
                       <<lfmt.begintime.mSec
                         <<lfmt.begintime.mMsec
                           <<lfmt.cbegint;
        lfmt.endtime.mHour = lst.at(1).mid(0,2).toInt(&ok, 10);
        lfmt.endtime.mMin  = lst.at(1).mid(3,2).toInt(&ok, 10);
        lfmt.endtime.mSec  = lst.at(1).mid(6,2).toInt(&ok, 10);
        lfmt.endtime.mMsec = lst.at(1).mid(9,3).toInt(&ok, 10);
        lfmt.cendint =  lfmt.endtime.mSec *1000 + lfmt.endtime.mMsec;

        qDebug() << "end   h-m-s-ms endt" << lfmt.endtime.mHour
                 << lfmt.endtime.mMin
                 <<lfmt.endtime.mSec
                <<lfmt.endtime.mMsec
                  <<lfmt.cendint;

        lfmt.tips = lst.at(2);
        qDebug() << "lfmt.tips : "<< lfmt.tips;

        vecLineFmts << lfmt;

    }

    qDebug() << "vecLineFmts size :" << vecLineFmts.size();


    loadflag = 0;





}
