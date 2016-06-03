/********************************************************************************
** Form generated from reading UI file 'widget1.ui'
**
** Created: Fri Jun 3 22:08:33 2016
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET1_H
#define UI_WIDGET1_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget1
{
public:
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QLabel *label;

    void setupUi(QWidget *Widget1)
    {
        if (Widget1->objectName().isEmpty())
            Widget1->setObjectName(QString::fromUtf8("Widget1"));
        Widget1->resize(400, 300);
        pushButton = new QPushButton(Widget1);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(40, 40, 101, 51));
        pushButton_2 = new QPushButton(Widget1);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(40, 130, 101, 51));
        label = new QLabel(Widget1);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(170, 50, 211, 161));

        retranslateUi(Widget1);

        QMetaObject::connectSlotsByName(Widget1);
    } // setupUi

    void retranslateUi(QWidget *Widget1)
    {
        Widget1->setWindowTitle(QApplication::translate("Widget1", "Widget1", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("Widget1", "PushButton", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("Widget1", "PushButton", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("Widget1", "TextLabel", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Widget1: public Ui_Widget1 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET1_H
