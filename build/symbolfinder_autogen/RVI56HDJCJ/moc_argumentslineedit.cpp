/****************************************************************************
** Meta object code from reading C++ file 'argumentslineedit.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>

#include <memory>

#include "../../../src/DriverWidgets/argumentslineedit.hpp"
#if !defined( Q_MOC_OUTPUT_REVISION )
#	error "The header file 'argumentslineedit.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#	error "This file was generated using the moc from 5.15.2. It"
#	error "cannot be used with the include files from this version of Qt."
#	error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ArgumentsLineEdit_t
{
	QByteArrayData data[7];
	char	       stringdata0[91];
};
#define QT_MOC_LITERAL( idx, ofs, len )                                                   \
	Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(                          \
		len,                                                                      \
		qptrdiff( offsetof( qt_meta_stringdata_ArgumentsLineEdit_t, stringdata0 ) \
			  + ofs - idx * sizeof( QByteArrayData ) ) )
static const qt_meta_stringdata_ArgumentsLineEdit_t qt_meta_stringdata_ArgumentsLineEdit = {
	{
		QT_MOC_LITERAL( 0, 0, 17 ),	// "ArgumentsLineEdit"
		QT_MOC_LITERAL( 1, 18, 21 ),	// "symbolManuallyChanged"
		QT_MOC_LITERAL( 2, 40, 0 ),	// ""
		QT_MOC_LITERAL( 3, 41, 17 ),	// "symbolSizeChanged"
		QT_MOC_LITERAL( 4, 59, 8 ),	// "uint16_t"
		QT_MOC_LITERAL( 5, 68, 4 ),	// "size"
		QT_MOC_LITERAL( 6, 73, 17 )	// "setSymbolSizeSlot"

	},
	"ArgumentsLineEdit\0symbolManuallyChanged\0"
	"\0symbolSizeChanged\0uint16_t\0size\0"
	"setSymbolSizeSlot" };
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ArgumentsLineEdit[] = {

	// content:
	8,    // revision
	0,    // classname
	0,
	0,    // classinfo
	3,
	14,    // methods
	0,
	0,    // properties
	0,
	0,    // enums/sets
	0,
	0,    // constructors
	0,    // flags
	2,    // signalCount

	// signals: name, argc, parameters, tag, flags
	1,
	0,
	29,
	2,
	0x06 /* Public */,
	3,
	1,
	30,
	2,
	0x06 /* Public */,

	// slots: name, argc, parameters, tag, flags
	6,
	1,
	33,
	2,
	0x0a /* Public */,

	// signals: parameters
	QMetaType::Void,
	QMetaType::Void,
	0x80000000 | 4,
	5,

	// slots: parameters
	QMetaType::Void,
	0x80000000 | 4,
	5,

	0    // eod
};

void ArgumentsLineEdit::qt_static_metacall( QObject	    *_o,
					    QMetaObject::Call _c,
					    int		      _id,
					    void		 **_a )
{
	if ( _c == QMetaObject::InvokeMetaMethod )
	{
		auto *_t = static_cast<ArgumentsLineEdit *>( _o );
		Q_UNUSED( _t )
		switch ( _id )
		{
			case 0: _t->symbolManuallyChanged(); break;
			case 1:
				_t->symbolSizeChanged(
					( *reinterpret_cast<uint16_t( * )>( _a[1] ) ) );
				break;
			case 2:
				_t->setSymbolSizeSlot(
					( *reinterpret_cast<uint16_t( * )>( _a[1] ) ) );
				break;
			default:;
		}
	}
	else if ( _c == QMetaObject::IndexOfMethod )
	{
		int *result = reinterpret_cast<int *>( _a[0] );
		{
			using _t = void ( ArgumentsLineEdit::* )();
			if ( *reinterpret_cast<_t *>( _a[1] )
			     == static_cast<_t>( &ArgumentsLineEdit::symbolManuallyChanged ) )
			{
				*result = 0;
				return;
			}
		}
		{
			using _t = void ( ArgumentsLineEdit::* )( uint16_t );
			if ( *reinterpret_cast<_t *>( _a[1] )
			     == static_cast<_t>( &ArgumentsLineEdit::symbolSizeChanged ) )
			{
				*result = 1;
				return;
			}
		}
	}
}

QT_INIT_METAOBJECT const QMetaObject ArgumentsLineEdit::staticMetaObject = {
	{ QMetaObject::SuperData::link<QLineEdit::staticMetaObject>(),
	  qt_meta_stringdata_ArgumentsLineEdit.data,
	  qt_meta_data_ArgumentsLineEdit,
	  qt_static_metacall,
	  nullptr,
	  nullptr } };

const QMetaObject *ArgumentsLineEdit::metaObject() const
{
	return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject()
					  : &staticMetaObject;
}

void *ArgumentsLineEdit::qt_metacast( const char *_clname )
{
	if ( !_clname ) return nullptr;
	if ( !strcmp( _clname, qt_meta_stringdata_ArgumentsLineEdit.stringdata0 ) )
		return static_cast<void *>( this );
	return QLineEdit::qt_metacast( _clname );
}

int ArgumentsLineEdit::qt_metacall( QMetaObject::Call _c, int _id, void **_a )
{
	_id = QLineEdit::qt_metacall( _c, _id, _a );
	if ( _id < 0 ) return _id;
	if ( _c == QMetaObject::InvokeMetaMethod )
	{
		if ( _id < 3 ) qt_static_metacall( this, _c, _id, _a );
		_id -= 3;
	}
	else if ( _c == QMetaObject::RegisterMethodArgumentMetaType )
	{
		if ( _id < 3 ) *reinterpret_cast<int *>( _a[0] ) = -1;
		_id -= 3;
	}
	return _id;
}

// SIGNAL 0
void ArgumentsLineEdit::symbolManuallyChanged()
{
	QMetaObject::activate( this, &staticMetaObject, 0, nullptr );
}

// SIGNAL 1
void ArgumentsLineEdit::symbolSizeChanged( uint16_t _t1 )
{
	void *_a[] = { nullptr,
		       const_cast<void *>( reinterpret_cast<const void *>(
			       std::addressof( _t1 ) ) ) };
	QMetaObject::activate( this, &staticMetaObject, 1, _a );
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
