/****************************************************************************
** Meta object code from reading C++ file 'messagewidget.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>

#include <memory>

#include "../../../src/DriverWidgets/messagewidget.hpp"
#if !defined( Q_MOC_OUTPUT_REVISION )
#	error "The header file 'messagewidget.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#	error "This file was generated using the moc from 5.15.2. It"
#	error "cannot be used with the include files from this version of Qt."
#	error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MessageWidget_t
{
	QByteArrayData data[5];
	char	       stringdata0[45];
};
#define QT_MOC_LITERAL( idx, ofs, len )                                               \
	Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(                      \
		len,                                                                  \
		qptrdiff( offsetof( qt_meta_stringdata_MessageWidget_t, stringdata0 ) \
			  + ofs - idx * sizeof( QByteArrayData ) ) )
static const qt_meta_stringdata_MessageWidget_t qt_meta_stringdata_MessageWidget = {
	{
		QT_MOC_LITERAL( 0, 0, 13 ),	// "MessageWidget"
		QT_MOC_LITERAL( 1, 14, 4 ),	// "Type"
		QT_MOC_LITERAL( 2, 19, 11 ),	// "Information"
		QT_MOC_LITERAL( 3, 31, 7 ),	// "Warning"
		QT_MOC_LITERAL( 4, 39, 5 )	// "Error"

	},
	"MessageWidget\0Type\0Information\0Warning\0"
	"Error" };
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MessageWidget[] = {

	// content:
	8,    // revision
	0,    // classname
	0,
	0,    // classinfo
	0,
	0,    // methods
	0,
	0,    // properties
	1,
	14,    // enums/sets
	0,
	0,    // constructors
	0,    // flags
	0,    // signalCount

	// enums: name, alias, flags, count, data
	1,
	1,
	0x0,
	3,
	19,

	// enum data: key, value
	2,
	uint( MessageWidget::Information ),
	3,
	uint( MessageWidget::Warning ),
	4,
	uint( MessageWidget::Error ),

	0    // eod
};

void MessageWidget::qt_static_metacall( QObject *_o, QMetaObject::Call _c, int _id, void **_a )
{
	Q_UNUSED( _o );
	Q_UNUSED( _id );
	Q_UNUSED( _c );
	Q_UNUSED( _a );
}

QT_INIT_METAOBJECT const QMetaObject MessageWidget::staticMetaObject = {
	{ QMetaObject::SuperData::link<QFrame::staticMetaObject>(),
	  qt_meta_stringdata_MessageWidget.data,
	  qt_meta_data_MessageWidget,
	  qt_static_metacall,
	  nullptr,
	  nullptr } };

const QMetaObject *MessageWidget::metaObject() const
{
	return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject()
					  : &staticMetaObject;
}

void *MessageWidget::qt_metacast( const char *_clname )
{
	if ( !_clname ) return nullptr;
	if ( !strcmp( _clname, qt_meta_stringdata_MessageWidget.stringdata0 ) )
		return static_cast<void *>( this );
	return QFrame::qt_metacast( _clname );
}

int MessageWidget::qt_metacall( QMetaObject::Call _c, int _id, void **_a )
{
	_id = QFrame::qt_metacall( _c, _id, _a );
	return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
