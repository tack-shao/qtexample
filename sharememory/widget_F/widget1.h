#ifndef WIDGET1_H
#define WIDGET1_H

#include <QWidget>
#include <QSharedMemory>


namespace Ui {
class Widget1;
}

class Widget1 : public QWidget
{
    Q_OBJECT
    
public:
    explicit Widget1(QWidget *parent = 0);
    ~Widget1();
    
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Widget1 *ui;
    QSharedMemory shareMemory;//注意该变量不要在函数内局部定义，由于函数内的局部变量随着函数执行结束而消失

};

#endif // WIDGET1_H
