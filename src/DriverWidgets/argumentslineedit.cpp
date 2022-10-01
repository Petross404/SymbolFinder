// <one line to give the program's name and a brief idea of what it does.>
// SPDX-FileCopyrightText: 2022 Πέτρος Σιλιγκούνας <petross404@gmail.com>
// SPDX-License-Identifier: GPL-3.0-or-later

#include "argumentslineedit.hpp"

#include <qevent.h>	   // for QMouseEvent, QKeyE...
#include <qnamespace.h>	   // for MouseButton, LeftB...
#include <qpoint.h>	   // for QPoint

#include <utility>    // for move

#include "../Helper/string.hpp"
#include "../Scanner/interface/idriver.hpp"	     // for StopIndex
#include "implementation/argumentslineedit_p.hpp"    // for ArgumentsLineEditP...

ArgumentsLineEdit::ArgumentsLineEdit( std::string_view text, StopIndex stopIndex, QWidget* parent )
	: QLineEdit{ string::toqstring( text ), parent }
	, d_ptr{ new ArgumentsLineEditPrivate{
		  this, string::toqstring( text ), std::move( stopIndex ) } }
{
	init();
}

ArgumentsLineEdit::ArgumentsLineEdit( std::optional<QWidget*> parent )
	: QLineEdit{ parent.value_or( nullptr ) }
	, d_ptr{ new ArgumentsLineEditPrivate{ this } }
{
	init();
}

ArgumentsLineEdit::~ArgumentsLineEdit() { delete d_ptr; }

void ArgumentsLineEdit::setStopIndex( const StopIndex& stopIndex )
{
	Q_D( ArgumentsLineEdit );
	d->setStopIndex( stopIndex );
}

StopIndex ArgumentsLineEdit::stopIndex() const
{
	Q_D( const ArgumentsLineEdit );
	return d->stopIndex();
}

void ArgumentsLineEdit::init() { Q_D( ArgumentsLineEdit ); }

void ArgumentsLineEdit::checkStopString() const
{
	Q_D( const ArgumentsLineEdit );
	d->checkStopString();
}

void ArgumentsLineEdit::setSymbolSizeSlot( uint16_t size )
{
	Q_D( ArgumentsLineEdit );
	d->setSymbolSize( size );
}

void ArgumentsLineEdit::mousePressEvent( QMouseEvent* event )
{
	if ( Qt::MouseButton btn = event->button();
	     btn == Qt::MouseButton::LeftButton || btn == Qt::MouseButton::RightButton )
	{
		QPoint position{ event->pos() };

		Q_D( const ArgumentsLineEdit );
		d->handleCursorPosition( cursorPositionAt( position ) );
	}

	QLineEdit::mousePressEvent( event );
}

void ArgumentsLineEdit::keyPressEvent( QKeyEvent* event )
{
	Q_D( const ArgumentsLineEdit );
	d->handleCursorPosition( cursorPosition() );

	QLineEdit::keyPressEvent( event );
}
