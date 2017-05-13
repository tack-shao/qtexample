/****************************************************************************
** Meta object code from reading C++ file 'widget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../widget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'widget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Widget_t {
    QByteArrayData data[19];
    char stringdata[302];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Widget_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Widget_t qt_meta_stringdata_Widget = {
    {
QT_MOC_LITERAL(0, 0, 6),
QT_MOC_LITERAL(1, 7, 21),
QT_MOC_LITERAL(2, 29, 0),
QT_MOC_LITERAL(3, 30, 23),
QT_MOC_LITERAL(4, 54, 19),
QT_MOC_LITERAL(5, 74, 5),
QT_MOC_LITERAL(6, 80, 12),
QT_MOC_LITERAL(7, 93, 14),
QT_MOC_LITERAL(8, 108, 4),
QT_MOC_LITERAL(9, 113, 9),
QT_MOC_LITERAL(10, 123, 23),
QT_MOC_LITERAL(11, 147, 21),
QT_MOC_LITERAL(12, 169, 15),
QT_MOC_LITERAL(13, 185, 22),
QT_MOC_LITERAL(14, 208, 5),
QT_MOC_LITERAL(15, 214, 32),
QT_MOC_LITERAL(16, 247, 12),
QT_MOC_LITERAL(17, 260, 14),
QT_MOC_LITERAL(18, 275, 26)
    },
    "Widget\0on_pushButton_clicked\0\0"
    "on_pushButton_2_clicked\0on_treeView_clicked\0"
    "index\0getTopParent\0QStandardItem*\0"
    "item\0itemIndex\0on_pushButton_3_clicked\0"
    "on_treeWidget_clicked\0treeItemChanged\0"
    "treeItem_checkAllChild\0check\0"
    "treeItem_checkAllChild_recursion\0"
    "checkSibling\0Qt::CheckState\0"
    "treeItem_CheckChildChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Widget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   84,    2, 0x08 /* Private */,
       3,    0,   85,    2, 0x08 /* Private */,
       4,    1,   86,    2, 0x08 /* Private */,
       6,    1,   89,    2, 0x08 /* Private */,
       6,    1,   92,    2, 0x08 /* Private */,
      10,    0,   95,    2, 0x08 /* Private */,
      11,    1,   96,    2, 0x08 /* Private */,
      12,    1,   99,    2, 0x08 /* Private */,
      13,    2,  102,    2, 0x08 /* Private */,
      13,    1,  107,    2, 0x28 /* Private | MethodCloned */,
      15,    2,  110,    2, 0x08 /* Private */,
      15,    1,  115,    2, 0x28 /* Private | MethodCloned */,
      16,    1,  118,    2, 0x08 /* Private */,
      18,    1,  121,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QModelIndex,    5,
    0x80000000 | 7, 0x80000000 | 7,    8,
    QMetaType::QModelIndex, QMetaType::QModelIndex,    9,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QModelIndex,    5,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void, 0x80000000 | 7, QMetaType::Bool,    8,   14,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void, 0x80000000 | 7, QMetaType::Bool,    8,   14,
    QMetaType::Void, 0x80000000 | 7,    8,
    0x80000000 | 17, 0x80000000 | 7,    8,
    QMetaType::Void, 0x80000000 | 7,    8,

       0        // eod
};

void Widget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Widget *_t = static_cast<Widget *>(_o);
        switch (_id) {
        case 0: _t->on_pushButton_clicked(); break;
        case 1: _t->on_pushButton_2_clicked(); break;
        case 2: _t->on_treeView_clicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 3: { QStandardItem* _r = _t->getTopParent((*reinterpret_cast< QStandardItem*(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QStandardItem**>(_a[0]) = _r; }  break;
        case 4: { QModelIndex _r = _t->getTopParent((*reinterpret_cast< QModelIndex(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QModelIndex*>(_a[0]) = _r; }  break;
        case 5: _t->on_pushButton_3_clicked(); break;
        case 6: _t->on_treeWidget_clicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 7: _t->treeItemChanged((*reinterpret_cast< QStandardItem*(*)>(_a[1]))); break;
        case 8: _t->treeItem_checkAllChild((*reinterpret_cast< QStandardItem*(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 9: _t->treeItem_checkAllChild((*reinterpret_cast< QStandardItem*(*)>(_a[1]))); break;
        case 10: _t->treeItem_checkAllChild_recursion((*reinterpret_cast< QStandardItem*(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 11: _t->treeItem_checkAllChild_recursion((*reinterpret_cast< QStandardItem*(*)>(_a[1]))); break;
        case 12: { Qt::CheckState _r = _t->checkSibling((*reinterpret_cast< QStandardItem*(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< Qt::CheckState*>(_a[0]) = _r; }  break;
        case 13: _t->treeItem_CheckChildChanged((*reinterpret_cast< QStandardItem*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject Widget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Widget.data,
      qt_meta_data_Widget,  qt_static_metacall, 0, 0}
};


const QMetaObject *Widget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Widget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Widget.stringdata))
        return static_cast<void*>(const_cast< Widget*>(this));
    return QWidget::qt_metacast(_clname);
}

int Widget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
