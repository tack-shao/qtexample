/********************************************************************************
** Form generated from reading UI file 'widget_s.ui'
**
** Created: Fri Jun 3 22:17:46 2016
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_S_H
#define UI_WIDGET_S_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget_S
{
public:
    QPushButton *pushButton;
    QLabel *label;

    void setupUi(QWidget *Widget_S)
    {
        if (Widget_S->objectName().isEmpty())
            Widget_S->setObjectName(QString::fromUtf8("Widget_S"));
        Widget_S->resize(559, 380);
        pushButton = new QPushButton(Widget_S);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(20, 10, 91, 51));
        label = new QLabel(Widget_S);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(140, 30, 401, 321));

        retranslateUi(Widget_S);

        QMetaObject::connectSlotsByName(Widget_S);
    } // setupUi

    void retranslateUi(QWidget *Widget_S)
    {
        Widget_S->setWindowTitle(QApplication::translate("Widget_S", "Widget_S", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("Widget_S", "PushButton", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("Widget_S", "TextLabel", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Widget_S: public Ui_Widget_S {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_S_H
