TEMPLATE = app
CONFIG += console
CONFIG -= qt

LIBS += -lpthread
SOURCES += main.cpp \
    memorylog.cpp \
    mlog_init.cpp

HEADERS += \
    memorylog.h \
    mlog_init.h \
    pub_defines.h

