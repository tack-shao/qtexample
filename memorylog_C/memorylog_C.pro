TEMPLATE = app
CONFIG += console
CONFIG -= qt

LIBS += -lpthread
SOURCES += main.c \
    rbtree.c \
    memorylog.c

HEADERS += \
    rbtree.h \
    memorylog.h

