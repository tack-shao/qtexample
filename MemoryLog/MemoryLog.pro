TEMPLATE = app
CONFIG += console
CONFIG -= qt

LIBS += -lpthread
SOURCES += main.cpp \
    memorylog.cpp

HEADERS += \
    memorylog.h

