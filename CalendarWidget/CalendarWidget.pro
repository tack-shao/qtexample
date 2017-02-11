#-------------------------------------------------
#
# Project created by QtCreator 2016-04-12T14:31:37
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CalendarWidget
TEMPLATE = app


SOURCES += main.cpp\
        calendarwidget.cpp \
    date.cpp \
    database.cpp \
    event.cpp \
    inputdialog.cpp

HEADERS  += calendarwidget.h \
    date.h \
    database.h \
    event.h \
    inputdialog.h

RESOURCES += \
    images.qrc

DESTDIR     += $$PWD/bin
OBJECTS_DIR += $$PWD/tmp
MOC_DIR     += $$PWD/tmp
RCC_DIR     += $$PWD/tmp

#安卓apk所需的资源文件夹，包括manifest文件和图片、声音等文件
ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android-sources

OTHER_FILES += \
    android-sources/AndroidManifest.xml \

DISTFILES += \
    android-sources/AndroidManifest.xml
