#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>

namespace Ui {
class MainWindow;
}

struct TimeFormat
{
    quint32 mHour;
    quint32 mMin;
    quint32 mSec;
    quint32 mMsec;
};

struct LineFormat
{
    TimeFormat begintime;
    TimeFormat endtime;
    quint32 cbegint; //转换后的时间， sec*1000 + msec
    quint32 cendint;
    QString tips;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void paintEvent(QPaintEvent *event);

    void drawLine(int x1, int y1, int x2, int y2, QString text);

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QVector<LineFormat> vecLineFmts;
    quint32 firsttime;
    quint32 loadflag;
    quint8 drawdone;
};

#endif // MAINWINDOW_H
