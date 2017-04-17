TEMPLATE = app
CONFIG += console
CONFIG -= qt

SOURCES += main.c \
    nanomsg-1.0.0/src/aio/worker.c \
    nanomsg-1.0.0/src/aio/usock.c \
    nanomsg-1.0.0/src/aio/timerset.c \
    nanomsg-1.0.0/src/aio/timer.c \
    nanomsg-1.0.0/src/aio/pool.c \
    nanomsg-1.0.0/src/aio/poller.c \
    nanomsg-1.0.0/src/aio/fsm.c \
    nanomsg-1.0.0/src/aio/ctx.c \
    nanomsg-1.0.0/src/core/symbol.c \
    nanomsg-1.0.0/src/core/sockbase.c \
    nanomsg-1.0.0/src/core/sock.c \
    nanomsg-1.0.0/src/core/poll.c \
    nanomsg-1.0.0/src/core/pipe.c \
    nanomsg-1.0.0/src/core/global.c \
    nanomsg-1.0.0/src/core/epbase.c \
    nanomsg-1.0.0/src/core/ep.c \
    nanomsg-1.0.0/src/devices/device.c \
    nanomsg-1.0.0/src/protocols/bus/xbus.c \
    nanomsg-1.0.0/src/protocols/bus/bus.c

OTHER_FILES += \
    nanomsg-1.0.0/src/README \
    nanomsg-1.0.0/src/pkgconfig.in \
    nanomsg-1.0.0/src/CMakeLists.txt \
    nanomsg-1.0.0/src/core/README

HEADERS += \
    nanomsg-1.0.0/src/ws.h \
    nanomsg-1.0.0/src/transport.h \
    nanomsg-1.0.0/src/tcp.h \
    nanomsg-1.0.0/src/survey.h \
    nanomsg-1.0.0/src/reqrep.h \
    nanomsg-1.0.0/src/pubsub.h \
    nanomsg-1.0.0/src/protocol.h \
    nanomsg-1.0.0/src/pipeline.h \
    nanomsg-1.0.0/src/pair.h \
    nanomsg-1.0.0/src/nn.h \
    nanomsg-1.0.0/src/ipc.h \
    nanomsg-1.0.0/src/inproc.h \
    nanomsg-1.0.0/src/bus.h \
    nanomsg-1.0.0/src/aio/worker_win.inc \
    nanomsg-1.0.0/src/aio/worker_win.h \
    nanomsg-1.0.0/src/aio/worker_posix.inc \
    nanomsg-1.0.0/src/aio/worker_posix.h \
    nanomsg-1.0.0/src/aio/worker.h \
    nanomsg-1.0.0/src/aio/usock_win.inc \
    nanomsg-1.0.0/src/aio/usock_win.h \
    nanomsg-1.0.0/src/aio/usock_posix.inc \
    nanomsg-1.0.0/src/aio/usock_posix.h \
    nanomsg-1.0.0/src/aio/usock.h \
    nanomsg-1.0.0/src/aio/timerset.h \
    nanomsg-1.0.0/src/aio/timer.h \
    nanomsg-1.0.0/src/aio/pool.h \
    nanomsg-1.0.0/src/aio/poller_poll.inc \
    nanomsg-1.0.0/src/aio/poller_poll.h \
    nanomsg-1.0.0/src/aio/poller_kqueue.inc \
    nanomsg-1.0.0/src/aio/poller_kqueue.h \
    nanomsg-1.0.0/src/aio/poller_epoll.inc \
    nanomsg-1.0.0/src/aio/poller_epoll.h \
    nanomsg-1.0.0/src/aio/poller.h \
    nanomsg-1.0.0/src/aio/fsm.h \
    nanomsg-1.0.0/src/aio/ctx.h \
    nanomsg-1.0.0/src/core/sock.h \
    nanomsg-1.0.0/src/core/global.h \
    nanomsg-1.0.0/src/core/ep.h \
    nanomsg-1.0.0/src/devices/device.h \
    nanomsg-1.0.0/src/protocols/bus/xbus.h \
    nanomsg-1.0.0/src/protocols/bus/bus.h

