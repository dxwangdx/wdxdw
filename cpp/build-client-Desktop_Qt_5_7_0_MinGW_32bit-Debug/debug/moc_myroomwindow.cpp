/****************************************************************************
** Meta object code from reading C++ file 'myroomwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../client/myroomwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'myroomwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MyRoomWindow_t {
    QByteArrayData data[12];
    char stringdata0[190];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MyRoomWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MyRoomWindow_t qt_meta_stringdata_MyRoomWindow = {
    {
QT_MOC_LITERAL(0, 0, 12), // "MyRoomWindow"
QT_MOC_LITERAL(1, 13, 22), // "on_btn_refresh_clicked"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 19), // "on_btn_send_clicked"
QT_MOC_LITERAL(4, 57, 26), // "on_btn_camera_open_clicked"
QT_MOC_LITERAL(5, 84, 27), // "on_btn_camera_close_clicked"
QT_MOC_LITERAL(6, 112, 11), // "UdpReadRead"
QT_MOC_LITERAL(7, 124, 14), // "onvideoChanged"
QT_MOC_LITERAL(8, 139, 11), // "QVideoFrame"
QT_MOC_LITERAL(9, 151, 8), // "curFrame"
QT_MOC_LITERAL(10, 160, 22), // "on_btn_bs_send_clicked"
QT_MOC_LITERAL(11, 183, 6) // "onTime"

    },
    "MyRoomWindow\0on_btn_refresh_clicked\0"
    "\0on_btn_send_clicked\0on_btn_camera_open_clicked\0"
    "on_btn_camera_close_clicked\0UdpReadRead\0"
    "onvideoChanged\0QVideoFrame\0curFrame\0"
    "on_btn_bs_send_clicked\0onTime"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MyRoomWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x08 /* Private */,
       3,    0,   55,    2, 0x08 /* Private */,
       4,    0,   56,    2, 0x08 /* Private */,
       5,    0,   57,    2, 0x08 /* Private */,
       6,    0,   58,    2, 0x08 /* Private */,
       7,    1,   59,    2, 0x08 /* Private */,
      10,    0,   62,    2, 0x08 /* Private */,
      11,    0,   63,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MyRoomWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MyRoomWindow *_t = static_cast<MyRoomWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_btn_refresh_clicked(); break;
        case 1: _t->on_btn_send_clicked(); break;
        case 2: _t->on_btn_camera_open_clicked(); break;
        case 3: _t->on_btn_camera_close_clicked(); break;
        case 4: _t->UdpReadRead(); break;
        case 5: _t->onvideoChanged((*reinterpret_cast< QVideoFrame(*)>(_a[1]))); break;
        case 6: _t->on_btn_bs_send_clicked(); break;
        case 7: _t->onTime(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QVideoFrame >(); break;
            }
            break;
        }
    }
}

const QMetaObject MyRoomWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MyRoomWindow.data,
      qt_meta_data_MyRoomWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MyRoomWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MyRoomWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MyRoomWindow.stringdata0))
        return static_cast<void*>(const_cast< MyRoomWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MyRoomWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
