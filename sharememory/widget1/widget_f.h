#ifndef WIDGET_F_H
#define WIDGET_F_H

#include <QMainWindow>

namespace Ui {
class WidGet_F;
}

class WidGet_F : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit WidGet_F(QWidget *parent = 0);
    ~WidGet_F();
    
private:
    Ui::WidGet_F *ui;
};

#endif // WIDGET_F_H
