#ifndef WIDGET_S_H
#define WIDGET_S_H

#include <QWidget>
#include <QSharedMemory>

namespace Ui {
class Widget_S;
}

class Widget_S : public QWidget
{
    Q_OBJECT
    
public:
    explicit Widget_S(QWidget *parent = 0);
    ~Widget_S();
    
private slots:
    void on_pushButton_clicked();

private:
    Ui::Widget_S *ui;
    QSharedMemory shareMemory;
};

#endif // WIDGET_S_H
