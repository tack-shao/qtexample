#ifndef TABFRAME_H
#define TABFRAME_H

#include <QMainWindow>

namespace Ui {
class TabFrame;
}

class TabFrame : public QMainWindow
{
    Q_OBJECT

public:
    explicit TabFrame(QWidget *parent = 0);
    ~TabFrame();

private:
    Ui::TabFrame *ui;
};

#endif // TABFRAME_H
