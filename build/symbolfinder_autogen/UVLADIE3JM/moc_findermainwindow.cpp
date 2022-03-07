/****************************************************************************
** Meta object code from reading C++ file 'findermainwindow.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>

#include <memory>

#include "../../../src/findermainwindow.hpp"
#if !defined( Q_MOC_OUTPUT_REVISION )
#	error "The header file 'findermainwindow.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#	error "This file was generated using the moc from 5.15.2. It"
#	error "cannot be used with the include files from this version of Qt."
#	error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t
{
	QByteArrayData data[18];
	char	       stringdata0[300];
};
#define QT_MOC_LITERAL( idx, ofs, len )                                            \
	Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(                   \
		len,                                                               \
		qptrdiff( offsetof( qt_meta_stringdata_MainWindow_t, stringdata0 ) \
			  + ofs - idx * sizeof( QByteArrayData ) ) )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
	{
		QT_MOC_LITERAL( 0, 0, 10 ),	// "MainWindow"
		QT_MOC_LITERAL( 1, 11, 27 ),	// "advancedArgumentssUnblocked"
		QT_MOC_LITERAL( 2, 39, 0 ),	// ""
		QT_MOC_LITERAL( 3, 40, 15 ),	// "hideStdErrorTab"
		QT_MOC_LITERAL( 4, 56, 15 ),	// "showStdErrorTab"
		QT_MOC_LITERAL( 5, 72, 22 ),	// "enableAdvancedLineEdit"
		QT_MOC_LITERAL( 6, 95, 6 ),	// "option"
		QT_MOC_LITERAL( 7, 102, 22 ),	  // "enableSymbolSearchSlot"
		QT_MOC_LITERAL( 8, 125, 19 ),	  // "updateStdOutputSlot"
		QT_MOC_LITERAL( 9, 145, 18 ),	  // "updateStdErrorSlot"
		QT_MOC_LITERAL( 10, 164, 16 ),	  // "updateSymbolSlot"
		QT_MOC_LITERAL( 11, 181, 6 ),	  // "symbol"
		QT_MOC_LITERAL( 12, 188, 27 ),	  // "updateAdvancedArgumentsSlot"
		QT_MOC_LITERAL( 13, 216, 26 ),	  // "resetAdvancedArgumentsSlot"
		QT_MOC_LITERAL( 14, 243, 11 ),	  // "blockUISlot"
		QT_MOC_LITERAL( 15, 255, 13 ),	  // "unblockUISlot"
		QT_MOC_LITERAL( 16, 269, 17 ),	  // "setInvocationSlot"
		QT_MOC_LITERAL( 17, 287, 12 )	  // "advancedArgs"

	},
	"MainWindow\0advancedArgumentssUnblocked\0"
	"\0hideStdErrorTab\0showStdErrorTab\0"
	"enableAdvancedLineEdit\0option\0"
	"enableSymbolSearchSlot\0updateStdOutputSlot\0"
	"updateStdErrorSlot\0updateSymbolSlot\0"
	"symbol\0updateAdvancedArgumentsSlot\0"
	"resetAdvancedArgumentsSlot\0blockUISlot\0"
	"unblockUISlot\0setInvocationSlot\0"
	"advancedArgs" };
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

	// content:
	8,    // revision
	0,    // classname
	0,
	0,    // classinfo
	13,
	14,    // methods
	0,
	0,    // properties
	0,
	0,    // enums/sets
	0,
	0,    // constructors
	0,    // flags
	1,    // signalCount

	// signals: name, argc, parameters, tag, flags
	1,
	0,
	79,
	2,
	0x06 /* Public */,

	// slots: name, argc, parameters, tag, flags
	3,
	0,
	80,
	2,
	0x0a /* Public */,
	4,
	0,
	81,
	2,
	0x0a /* Public */,
	5,
	1,
	82,
	2,
	0x0a /* Public */,
	7,
	1,
	85,
	2,
	0x0a /* Public */,
	8,
	0,
	88,
	2,
	0x0a /* Public */,
	9,
	0,
	89,
	2,
	0x0a /* Public */,
	10,
	1,
	90,
	2,
	0x0a /* Public */,
	12,
	0,
	93,
	2,
	0x0a /* Public */,
	13,
	0,
	94,
	2,
	0x0a /* Public */,
	14,
	0,
	95,
	2,
	0x0a /* Public */,
	15,
	0,
	96,
	2,
	0x0a /* Public */,
	16,
	1,
	97,
	2,
	0x0a /* Public */,

	// signals: parameters
	QMetaType::Void,

	// slots: parameters
	QMetaType::Void,
	QMetaType::Void,
	QMetaType::Void,
	QMetaType::Bool,
	6,
	QMetaType::Void,
	QMetaType::Bool,
	6,
	QMetaType::Void,
	QMetaType::Void,
	QMetaType::Void,
	QMetaType::QString,
	11,
	QMetaType::Void,
	QMetaType::Void,
	QMetaType::Void,
	QMetaType::Void,
	QMetaType::Void,
	QMetaType::QString,
	17,

	0    // eod
};

void MainWindow::qt_static_metacall( QObject *_o, QMetaObject::Call _c, int _id, void **_a )
{
	if ( _c == QMetaObject::InvokeMetaMethod )
	{
		auto *_t = static_cast<MainWindow *>( _o );
		Q_UNUSED( _t )
		switch ( _id )
		{
			case 0: _t->advancedArgumentssUnblocked(); break;
			case 1: _t->hideStdErrorTab(); break;
			case 2: _t->showStdErrorTab(); break;
			case 3:
				_t->enableAdvancedLineEdit(
					( *reinterpret_cast<bool( * )>( _a[1] ) ) );
				break;
			case 4:
				_t->enableSymbolSearchSlot(
					( *reinterpret_cast<bool( * )>( _a[1] ) ) );
				break;
			case 5: _t->updateStdOutputSlot(); break;
			case 6: _t->updateStdErrorSlot(); break;
			case 7:
				_t->updateSymbolSlot( (
					*reinterpret_cast<const QString( * )>( _a[1] ) ) );
				break;
			case 8: _t->updateAdvancedArgumentsSlot(); break;
			case 9: _t->resetAdvancedArgumentsSlot(); break;
			case 10: _t->blockUISlot(); break;
			case 11: _t->unblockUISlot(); break;
			case 12:
				_t->setInvocationSlot( (
					*reinterpret_cast<const QString( * )>( _a[1] ) ) );
				break;
			default:;
		}
	}
	else if ( _c == QMetaObject::IndexOfMethod )
	{
		int *result = reinterpret_cast<int *>( _a[0] );
		{
			using _t = void ( MainWindow::* )() const;
			if ( *reinterpret_cast<_t *>( _a[1] )
			     == static_cast<_t>( &MainWindow::advancedArgumentssUnblocked ) )
			{
				*result = 0;
				return;
			}
		}
	}
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = {
	{ QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
	  qt_meta_stringdata_MainWindow.data,
	  qt_meta_data_MainWindow,
	  qt_static_metacall,
	  nullptr,
	  nullptr } };

const QMetaObject *MainWindow::metaObject() const
{
	return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject()
					  : &staticMetaObject;
}

void *MainWindow::qt_metacast( const char *_clname )
{
	if ( !_clname ) return nullptr;
	if ( !strcmp( _clname, qt_meta_stringdata_MainWindow.stringdata0 ) )
		return static_cast<void *>( this );
	return QMainWindow::qt_metacast( _clname );
}

int MainWindow::qt_metacall( QMetaObject::Call _c, int _id, void **_a )
{
	_id = QMainWindow::qt_metacall( _c, _id, _a );
	if ( _id < 0 ) return _id;
	if ( _c == QMetaObject::InvokeMetaMethod )
	{
		if ( _id < 13 ) qt_static_metacall( this, _c, _id, _a );
		_id -= 13;
	}
	else if ( _c == QMetaObject::RegisterMethodArgumentMetaType )
	{
		if ( _id < 13 ) *reinterpret_cast<int *>( _a[0] ) = -1;
		_id -= 13;
	}
	return _id;
}

// SIGNAL 0
void MainWindow::advancedArgumentssUnblocked() const
{
	QMetaObject::activate( const_cast<MainWindow *>( this ), &staticMetaObject, 0, nullptr );
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
