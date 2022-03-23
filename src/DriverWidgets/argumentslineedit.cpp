// <one line to give the program's name and a brief idea of what it does.>
// SPDX-FileCopyrightText: 2022 Πέτρος Σιλιγκούνας <petross404@gmail.com>
// SPDX-License-Identifier: GPL-3.0-or-later

#include "argumentslineedit.hpp"

#include <qevent.h>	   // for QMouseEvent, QKey...
#include <qnamespace.h>	   // for MouseButton, Uniq...
#include <qpoint.h>	   // for QPoint

#include "src/ConnectVerifier/connectverifier.hpp"    // for ConnectVerifier
#include "src/Scanner/Drivers/idriver.hpp"	      // for StopIndex
class QWidget;					      // lines 14-14

ArgumentsLineEdit::ArgumentsLineEdit( const QString& text, StopIndex stopIndex, QWidget* parent )
	: QLineEdit{ text, parent }
	, m_text{ text }
	, m_stopIndex{ stopIndex }
{
	init();
}

ArgumentsLineEdit::ArgumentsLineEdit( QWidget* parent )
	: QLineEdit{ parent }
{
	init();
}

ArgumentsLineEdit::~ArgumentsLineEdit() = default;

void ArgumentsLineEdit::setStopIndex( const StopIndex& stopIndex )
{
	m_stopIndex = stopIndex;
}

StopIndex ArgumentsLineEdit::stopIndex() const { return m_stopIndex; }

void ArgumentsLineEdit::init()
{
	setStyleSheet( "QLineEdit{ "
		       "padding: 0 8px;"
		       "selection-background-color: darkgray;"
		       "font-family: Lucida Console, Courier New, monospace;"
		       "font-size: 13px;}" );

	setMouseTracking( true );

	ConnectVerifier v;

	// Make sure that the stop string can't be selected or deleted
	v = connect( this,
		     &ArgumentsLineEdit::selectionChanged,
		     this,
		     &ArgumentsLineEdit::checkStopString,
		     Qt::UniqueConnection );

	v = connect( this,
		     &ArgumentsLineEdit::symbolSizeChanged,
		     this,
		     &ArgumentsLineEdit::setSymbolSizeSlot,
		     Qt::UniqueConnection );
}

void ArgumentsLineEdit::checkStopString()
{
	const QString stop{ stopIndex().stopStr };
	if ( selectedText().contains( stop ) ) { emit symbolManuallyChanged(); }
}

void ArgumentsLineEdit::setSymbolSizeSlot( uint16_t size )
{
	m_synbolSz = size + 2;
}

void ArgumentsLineEdit::mousePressEvent( QMouseEvent* event )
{
	if ( Qt::MouseButton btn = event->button();
	     btn == Qt::MouseButton::LeftButton || btn == Qt::MouseButton::RightButton )
	{
		QPoint position = event->pos();

		int posAt = cursorPositionAt( position );
		int index = stopIndex().indexOfStop;

		if ( posAt >= index && posAt < ( index + m_synbolSz ) )
		{
			emit symbolManuallyChanged();
		}
	}
	QLineEdit::mousePressEvent( event );
}

void ArgumentsLineEdit::keyPressEvent( QKeyEvent* event )
{
	const QString txt = text();

	int posAt = cursorPosition();
	int index = stopIndex().indexOfStop;

	if ( posAt >= index && posAt < ( index + m_synbolSz ) )
	{
		emit symbolManuallyChanged();
	}
	QLineEdit::keyPressEvent( event );
}
