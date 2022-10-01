// <one line to give the program's name and a brief idea of what it does.>
// SPDX-FileCopyrightText: 2022 Πέτρος Σιλιγκούνας <petross404@gmail.com>
// SPDX-License-Identifier: GPL-3.0-or-later

#include "symbollineedit.hpp"

#include <QtCore/qglobal.h>    // for Q_UNLIKELY
#include <qevent.h>	       // for QKeyEvent, QFocusEvent (ptr only)
#include <qnamespace.h>	       // for Key, UniqueConnection, AlignCenter
#include <qstringliteral.h>    // for QStringLiteral

#include <cctype>	 // for isdigit
#include <cstdint>	 // for uint8_t
#include <functional>	 // for _Bind_helper<>::type, bind
#include <string>	 // for char_traits, string

#include "src/Helper/string.hpp"    // for toqstring, tostring

std::string_view constexpr g_empty{ " " };

int constexpr g_milliseconds = 6000;

SymbolLineEdit::SymbolLineEdit( QWidget* parent )
	: QLineEdit{ parent }
{
	init();
}

SymbolLineEdit::SymbolLineEdit( std::string_view text, QWidget* parent )
	: QLineEdit{ parent }
	, msg{ text }
{
	init();
}

SymbolLineEdit::~SymbolLineEdit() = default;

void SymbolLineEdit::focusInEvent( QFocusEvent* event )
{
	// Use QLineEdit::text() on purpose, this class hides this function with another!
	if ( QLineEdit::text().contains( string::toqstring( msg ) ) )
	{
		setMessage();
	}

	QLineEdit::focusInEvent( event );
}

void SymbolLineEdit::leaveEvent( QEvent* event )
{
	// Don't print any text if the cursor is active
	if ( !hasFocus() ) { setMessage(); }

	QLineEdit::leaveEvent( event );
}

void SymbolLineEdit::keyPressEvent( QKeyEvent* event )
{
	if ( const int key = event->key();
	     key == Qt::Key::Key_Enter || key == Qt::Key::Key_Return )
	{
		emit keyEnterPressed();
	}
	else if ( std::string_view s{ string::tostring<QString>( event->text() ) };
		  std::isdigit( static_cast<unsigned char>( s.at( 0 ) ) ) )
	{
		clear();
		emit enableSymbolLineWarning();
		emit enableSymbolSearch( false );
	}

	QLineEdit::keyPressEvent( event );
}

void SymbolLineEdit::init()
{
	setMaximumHeight( 30 );
	setClearButtonEnabled( true );
	setAlignment( Qt::AlignCenter );
	setToolTip( string::toqstring( msg ) );

	const QString stylesheet{ QStringLiteral(
		"QLineEdit{ "
		"padding: 0 8px;"
		"selection-background-color: black;"
		"selection-background-color: blue;"
		"font-family: Lucida Console, Courier New, monospace;"
		"font-size: 13px;}" ) };

	setStyleSheet( stylesheet );

	connect( this,
		 &SymbolLineEdit::keyEnterPressed,
		 this,
		 std::bind( &QLineEdit::textChanged, this, this->text() ),
		 Qt::UniqueConnection );

	connect( this,
		 &QLineEdit::textChanged,
		 this,
		 &SymbolLineEdit::textChangedSlot,
		 Qt::UniqueConnection );
}

QString SymbolLineEdit::text() const
{
	return QLineEdit::text().remove( string::toqstring( msg ) );
}

void SymbolLineEdit::setMessage()
{
	blockSignals( true );
	setText( string::toqstring( msg ) );
	blockSignals( false );
}

void SymbolLineEdit::textChangedSlot( const QString& txt )
{
	std::string_view text{ string::tostring( txt ) };

	// If the user entered the msg value as text, return
	if ( Q_UNLIKELY( text == msg ) ) { return; }

	// First of all, check for numbers stating a symbol.
	const std::uint8_t firstIndex = 0;

	bool enableSearch =
		text.find( g_empty ) == std::string::npos
		|| std::isdigit( static_cast<unsigned char>( text.at( firstIndex ) ) )
		|| !text.empty();

	if ( enableSearch != m_enableSearch )
	{
		m_enableSearch = enableSearch;
		emit enableSymbolSearch( enableSearch );
		emit symbolChanged( text );

		if ( enableSearch == false )
		{
			clear();
			emit enableSymbolLineWarning();
		}
	}
}
