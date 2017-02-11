/****************************************************************************
** Meta object code from reading C++ file 'calendarwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../calendarwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'calendarwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_DayLabel_t {
    QByteArrayData data[7];
    char stringdata0[53];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DayLabel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DayLabel_t qt_meta_stringdata_DayLabel = {
    {
QT_MOC_LITERAL(0, 0, 8), // "DayLabel"
QT_MOC_LITERAL(1, 9, 13), // "signalClicked"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 5), // "ntype"
QT_MOC_LITERAL(4, 30, 3), // "day"
QT_MOC_LITERAL(5, 34, 10), // "signalPlan"
QT_MOC_LITERAL(6, 45, 7) // "content"

    },
    "DayLabel\0signalClicked\0\0ntype\0day\0"
    "signalPlan\0content"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DayLabel[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   24,    2, 0x06 /* Public */,
       5,    1,   29,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    3,    4,
    QMetaType::Void, QMetaType::QString,    6,

       0        // eod
};

void DayLabel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        DayLabel *_t = static_cast<DayLabel *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalClicked((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->signalPlan((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (DayLabel::*_t)(int , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DayLabel::signalClicked)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (DayLabel::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DayLabel::signalPlan)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject DayLabel::staticMetaObject = {
    { &QLabel::staticMetaObject, qt_meta_stringdata_DayLabel.data,
      qt_meta_data_DayLabel,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *DayLabel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DayLabel::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_DayLabel.stringdata0))
        return static_cast<void*>(const_cast< DayLabel*>(this));
    return QLabel::qt_metacast(_clname);
}

int DayLabel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QLabel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void DayLabel::signalClicked(int _t1, int _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void DayLabel::signalPlan(const QString & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
struct qt_meta_stringdata_CalendarWidget_t {
    QByteArrayData data[12];
    char stringdata0[131];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CalendarWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CalendarWidget_t qt_meta_stringdata_CalendarWidget = {
    {
QT_MOC_LITERAL(0, 0, 14), // "CalendarWidget"
QT_MOC_LITERAL(1, 15, 16), // "signalDayClicked"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 4), // "nday"
QT_MOC_LITERAL(4, 38, 16), // "signalDayChanged"
QT_MOC_LITERAL(5, 55, 10), // "signalPlan"
QT_MOC_LITERAL(6, 66, 7), // "content"
QT_MOC_LITERAL(7, 74, 13), // "sltDayClicked"
QT_MOC_LITERAL(8, 88, 4), // "type"
QT_MOC_LITERAL(9, 93, 3), // "day"
QT_MOC_LITERAL(10, 97, 16), // "sltShowPrevMonth"
QT_MOC_LITERAL(11, 114, 16) // "sltShowNextMonth"

    },
    "CalendarWidget\0signalDayClicked\0\0nday\0"
    "signalDayChanged\0signalPlan\0content\0"
    "sltDayClicked\0type\0day\0sltShowPrevMonth\0"
    "sltShowNextMonth"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CalendarWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x06 /* Public */,
       4,    0,   47,    2, 0x06 /* Public */,
       5,    1,   48,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    2,   51,    2, 0x08 /* Private */,
      10,    0,   56,    2, 0x08 /* Private */,
      11,    0,   57,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    6,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    8,    9,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void CalendarWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CalendarWidget *_t = static_cast<CalendarWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalDayClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->signalDayChanged(); break;
        case 2: _t->signalPlan((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->sltDayClicked((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 4: _t->sltShowPrevMonth(); break;
        case 5: _t->sltShowNextMonth(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (CalendarWidget::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CalendarWidget::signalDayClicked)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (CalendarWidget::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CalendarWidget::signalDayChanged)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (CalendarWidget::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CalendarWidget::signalPlan)) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject CalendarWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_CalendarWidget.data,
      qt_meta_data_CalendarWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CalendarWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CalendarWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CalendarWidget.stringdata0))
        return static_cast<void*>(const_cast< CalendarWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int CalendarWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void CalendarWidget::signalDayClicked(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CalendarWidget::signalDayChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void CalendarWidget::signalPlan(const QString & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
struct qt_meta_stringdata_Window_t {
    QByteArrayData data[9];
    char stringdata0[88];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Window_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Window_t qt_meta_stringdata_Window = {
    {
QT_MOC_LITERAL(0, 0, 6), // "Window"
QT_MOC_LITERAL(1, 7, 13), // "sltDayClicked"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 4), // "nday"
QT_MOC_LITERAL(4, 27, 13), // "sltDayChanged"
QT_MOC_LITERAL(5, 41, 11), // "sltDateJump"
QT_MOC_LITERAL(6, 53, 13), // "sltBack2today"
QT_MOC_LITERAL(7, 67, 12), // "sltShowPlans"
QT_MOC_LITERAL(8, 80, 7) // "content"

    },
    "Window\0sltDayClicked\0\0nday\0sltDayChanged\0"
    "sltDateJump\0sltBack2today\0sltShowPlans\0"
    "content"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Window[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x08 /* Private */,
       4,    0,   42,    2, 0x08 /* Private */,
       5,    0,   43,    2, 0x08 /* Private */,
       6,    0,   44,    2, 0x08 /* Private */,
       7,    1,   45,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    8,

       0        // eod
};

void Window::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Window *_t = static_cast<Window *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sltDayClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->sltDayChanged(); break;
        case 2: _t->sltDateJump(); break;
        case 3: _t->sltBack2today(); break;
        case 4: _t->sltShowPlans((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject Window::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Window.data,
      qt_meta_data_Window,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Window::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Window::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Window.stringdata0))
        return static_cast<void*>(const_cast< Window*>(this));
    return QWidget::qt_metacast(_clname);
}

int Window::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
