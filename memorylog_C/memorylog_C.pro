TEMPLATE = app
CONFIG += console
CONFIG -= qt

LIBS += -lpthread
SOURCES += main.c \
    rbtree.c \
    memorylog.c \
    cvector.c

HEADERS += \
    rbtree.h \
    memorylog.h \
    cvector.h

