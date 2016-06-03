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
    QSharedMemory shareMemory;//ע��ñ�����Ҫ�ں����ھֲ����壬���ں����ڵľֲ��������ź���ִ�н�������ʧ

};

#endif // WIDGET1_H
