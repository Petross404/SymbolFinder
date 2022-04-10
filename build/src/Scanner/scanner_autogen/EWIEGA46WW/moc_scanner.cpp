/****************************************************************************
** Meta object code from reading C++ file 'scanner.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../../src/Scanner/scanner.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'scanner.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Scanner_t {
    QByteArrayData data[29];
    char stringdata0[402];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Scanner_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Scanner_t qt_meta_stringdata_Scanner = {
    {
QT_MOC_LITERAL(0, 0, 7), // "Scanner"
QT_MOC_LITERAL(1, 8, 22), // "readyReadStandardError"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 23), // "readyReadStandardOutput"
QT_MOC_LITERAL(4, 56, 16), // "argumentsUpdated"
QT_MOC_LITERAL(5, 73, 11), // "scanStarted"
QT_MOC_LITERAL(6, 85, 12), // "scanFinished"
QT_MOC_LITERAL(7, 98, 8), // "exitCode"
QT_MOC_LITERAL(8, 107, 20), // "QProcess::ExitStatus"
QT_MOC_LITERAL(9, 128, 10), // "exitStatus"
QT_MOC_LITERAL(10, 139, 16), // "scanErrorOccured"
QT_MOC_LITERAL(11, 156, 22), // "QProcess::ProcessError"
QT_MOC_LITERAL(12, 179, 5), // "error"
QT_MOC_LITERAL(13, 185, 17), // "symbolSizeChanged"
QT_MOC_LITERAL(14, 203, 8), // "uint16_t"
QT_MOC_LITERAL(15, 212, 4), // "size"
QT_MOC_LITERAL(16, 217, 17), // "driverInitialized"
QT_MOC_LITERAL(17, 235, 4), // "name"
QT_MOC_LITERAL(18, 240, 11), // "driverReset"
QT_MOC_LITERAL(19, 252, 10), // "symbolName"
QT_MOC_LITERAL(20, 263, 13), // "pluginsLoaded"
QT_MOC_LITERAL(21, 277, 11), // "pluginNames"
QT_MOC_LITERAL(22, 289, 12), // "aboutToClose"
QT_MOC_LITERAL(23, 302, 15), // "performScanSlot"
QT_MOC_LITERAL(24, 318, 21), // "driverInitializedSlot"
QT_MOC_LITERAL(25, 340, 6), // "symbol"
QT_MOC_LITERAL(26, 347, 16), // "aboutToCloseSlot"
QT_MOC_LITERAL(27, 364, 18), // "setStandardErrSlot"
QT_MOC_LITERAL(28, 383, 18) // "setStandardOutSlot"

    },
    "Scanner\0readyReadStandardError\0\0"
    "readyReadStandardOutput\0argumentsUpdated\0"
    "scanStarted\0scanFinished\0exitCode\0"
    "QProcess::ExitStatus\0exitStatus\0"
    "scanErrorOccured\0QProcess::ProcessError\0"
    "error\0symbolSizeChanged\0uint16_t\0size\0"
    "driverInitialized\0name\0driverReset\0"
    "symbolName\0pluginsLoaded\0pluginNames\0"
    "aboutToClose\0performScanSlot\0"
    "driverInitializedSlot\0symbol\0"
    "aboutToCloseSlot\0setStandardErrSlot\0"
    "setStandardOutSlot"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Scanner[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      11,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   94,    2, 0x06 /* Public */,
       3,    0,   95,    2, 0x06 /* Public */,
       4,    0,   96,    2, 0x06 /* Public */,
       5,    0,   97,    2, 0x06 /* Public */,
       6,    2,   98,    2, 0x06 /* Public */,
      10,    1,  103,    2, 0x06 /* Public */,
      13,    1,  106,    2, 0x06 /* Public */,
      16,    1,  109,    2, 0x06 /* Public */,
      18,    1,  112,    2, 0x06 /* Public */,
      20,    1,  115,    2, 0x06 /* Public */,
      22,    0,  118,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      23,    0,  119,    2, 0x0a /* Public */,
      24,    1,  120,    2, 0x0a /* Public */,
      26,    0,  123,    2, 0x0a /* Public */,
      27,    0,  124,    2, 0x09 /* Protected */,
      28,    0,  125,    2, 0x09 /* Protected */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 8,    7,    9,
    QMetaType::Void, 0x80000000 | 11,   12,
    QMetaType::Void, 0x80000000 | 14,   15,
    QMetaType::Void, QMetaType::QString,   17,
    QMetaType::Void, QMetaType::QString,   19,
    QMetaType::Void, QMetaType::QStringList,   21,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   25,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Scanner::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Scanner *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->readyReadStandardError(); break;
        case 1: _t->readyReadStandardOutput(); break;
        case 2: _t->argumentsUpdated(); break;
        case 3: _t->scanStarted(); break;
        case 4: _t->scanFinished((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QProcess::ExitStatus(*)>(_a[2]))); break;
        case 5: _t->scanErrorOccured((*reinterpret_cast< QProcess::ProcessError(*)>(_a[1]))); break;
        case 6: _t->symbolSizeChanged((*reinterpret_cast< uint16_t(*)>(_a[1]))); break;
        case 7: _t->driverInitialized((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 8: _t->driverReset((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 9: _t->pluginsLoaded((*reinterpret_cast< const QStringList(*)>(_a[1]))); break;
        case 10: _t->aboutToClose(); break;
        case 11: _t->performScanSlot(); break;
        case 12: _t->driverInitializedSlot((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 13: _t->aboutToCloseSlot(); break;
        case 14: _t->setStandardErrSlot(); break;
        case 15: _t->setStandardOutSlot(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Scanner::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Scanner::readyReadStandardError)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Scanner::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Scanner::readyReadStandardOutput)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (Scanner::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Scanner::argumentsUpdated)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (Scanner::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Scanner::scanStarted)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (Scanner::*)(int , QProcess::ExitStatus );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Scanner::scanFinished)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (Scanner::*)(QProcess::ProcessError );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Scanner::scanErrorOccured)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (Scanner::*)(uint16_t );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Scanner::symbolSizeChanged)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (Scanner::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Scanner::driverInitialized)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (Scanner::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Scanner::driverReset)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (Scanner::*)(const QStringList & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Scanner::pluginsLoaded)) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (Scanner::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Scanner::aboutToClose)) {
                *result = 10;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Scanner::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_Scanner.data,
    qt_meta_data_Scanner,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Scanner::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Scanner::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Scanner.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Scanner::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 16;
    }
    return _id;
}

// SIGNAL 0
void Scanner::readyReadStandardError()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void Scanner::readyReadStandardOutput()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void Scanner::argumentsUpdated()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void Scanner::scanStarted()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void Scanner::scanFinished(int _t1, QProcess::ExitStatus _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void Scanner::scanErrorOccured(QProcess::ProcessError _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void Scanner::symbolSizeChanged(uint16_t _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void Scanner::driverInitialized(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void Scanner::driverReset(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void Scanner::pluginsLoaded(const QStringList & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void Scanner::aboutToClose()
{
    QMetaObject::activate(this, &staticMetaObject, 10, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
