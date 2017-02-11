#ifndef INPUTDIALOG_H
#define INPUTDIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
class QPushButton;
class QLabel;
class QGroupBox;
class QLineEdit;
class QHBoxLayout;
class QVBoxLayout;
QT_END_NAMESPACE

class InputDialog : public QDialog
{
    Q_OBJECT
public:
    explicit InputDialog(QWidget *parent = 0);

signals:

public slots:

private:
    QLabel *labelTitle;
    QLineEdit *editInput;
    QPushButton *btnOk;
    QPushButton *btnCancel;
};

#endif // INPUTDIALOG_H
