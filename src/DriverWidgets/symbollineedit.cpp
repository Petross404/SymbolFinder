// <one line to give the program's name and a brief idea of what it does.>
// SPDX-FileCopyrightText: 2022 Πέτρος Σιλιγκούνας <petross404@gmail.com>
// SPDX-License-Identifier: GPL-3.0-or-later

#include "symbollineedit.hpp"

#include <QtCore/qglobal.h>    // for qDebug
#include <qdebug.h>	       // for QDebug
#include <qnamespace.h>	       // for UniqueConnection

#include <functional>	 // for _Bind_helper<>::type, bind, _Placeholder
#include <utility>	 // for move
class QEvent;
class QFocusEvent;
class QWidget;

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

void SymbolLineEdit::init()
{
	setMaximumHeight( 30 );

	setToolTip( msg );
	setStyleSheet( "QLineEdit{ "
		       "padding: 0 8px;"
		       "selection-background-color: black;"
		       "selection-background-color: blue;"
		       "font-family: Lucida Console, Courier New, monospace;"
		       "font-size: 13px;}" );

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
