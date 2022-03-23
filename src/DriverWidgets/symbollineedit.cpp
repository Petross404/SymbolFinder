// <one line to give the program's name and a brief idea of what it does.>
// SPDX-FileCopyrightText: 2022 Πέτρος Σιλιγκούνας <petross404@gmail.com>
// SPDX-License-Identifier: GPL-3.0-or-later

#include "symbollineedit.hpp"

#include <QtCore/qglobal.h>    // for Q_LIKELY, qDebug
#include <qchar.h>	       // for QChar
#include <qdebug.h>	       // for QDebug
#include <qevent.h>	       // for QFocusEvent (ptr only), QKeyEvent
#include <qnamespace.h>	   // for Key, UniqueConnection, Key_Enter, Key_Re...
#include <stddef.h>	   // for size_t

#include <functional>	 // for _Bind_helper<>::type, bind
#include <utility>	 // for move
class QWidget;		 // lines 15-15

int constexpr milliseconds = 6000;

SymbolLineEdit::SymbolLineEdit( QWidget* parent )
	: QLineEdit{ parent }
{
	init();
}

SymbolLineEdit::SymbolLineEdit( const QString& text, QWidget* parent )
	: QLineEdit{ parent }
	, msg{ text }
{
	init();
}

SymbolLineEdit::~SymbolLineEdit() = default;

void SymbolLineEdit::focusInEvent( QFocusEvent* event )
{
	if ( text().contains( msg ) )
	{
		blockSignals( true );
		clear();
		blockSignals( false );
	}

	QLineEdit::focusInEvent( event );
}

void SymbolLineEdit::leaveEvent( QEvent* event )
{
	// Don't print any text if the cursor is active
	if ( !hasFocus() )
	{
		blockSignals( true );
		setText( msg );
		blockSignals( false );
	}

	QLineEdit::leaveEvent( event );
}

void SymbolLineEdit::keyPressEvent( QKeyEvent* event )
{
	if ( const int key = event->key();
	     key == Qt::Key::Key_Enter || key == Qt::Key::Key_Return )
	{
		emit keyEnterPressed();
	}

	QLineEdit::keyPressEvent( event );
}

void SymbolLineEdit::init()
{
	setMaximumHeight( 30 );
	setClearButtonEnabled( true );

	setToolTip( msg );
	setStyleSheet( "QLineEdit{ "
		       "padding: 0 8px;"
		       "selection-background-color: black;"
		       "selection-background-color: blue;"
		       "font-family: Lucida Console, Courier New, monospace;"
		       "font-size: 12px;}" );

	connect( this,
		 &SymbolLineEdit::keyEnterPressed,
		 this,
		 std::bind( &QLineEdit::textChanged, this, text() ),
		 Qt::UniqueConnection );

	connect( this,
		 &QLineEdit::textChanged,
		 this,
		 &SymbolLineEdit::textChangedSlot,
		 Qt::UniqueConnection );
}

void SymbolLineEdit::textChangedSlot( const QString& txt )
{
	if ( Q_LIKELY( txt != msg ) )
	{
		/*
		 *
		 */
		int index = 0;
		for ( size_t i = 0; i < txt.size(); i++ )
		{
			if ( QChar c = txt.at( i ); c.isSpace() ) { index++; }
			else
			{
				break;
			}
		}

		// Keep the text without the first blanc characters.
		QString rightmostText = txt.right( txt.size() - index );
		qDebug() << "rightmostText" << rightmostText;

		bool enableSearch = !( rightmostText.contains( " " ) );

		emit symbolChanged( rightmostText );

		if ( enableSearch != m_enableSearch )
		{
			m_enableSearch = enableSearch;
			emit enableSymbolSearch( enableSearch );

			if ( enableSearch == false )
			{
				emit enableSymbolLineWarning();
			}
		}
	}
}
