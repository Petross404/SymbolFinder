// <one line to give the program's name and a brief idea of what it does.>
// SPDX-FileCopyrightText: 2022 Πέτρος Σιλιγκούνας <petross404@gmail.com>
// SPDX-License-Identifier: GPL-3.0-or-later

#include "argumentslineedit.hpp"

#include <QtCore/qglobal.h>    // for qDebug
#include <qdebug.h>	       // for QDebug
#include <qevent.h>	       // for QMouseEvent, QKeyEvent (ptr only)
#include <qnamespace.h>	       // for MouseButton, LeftButton, RightButton
#include <qpoint.h>	       // for QPoint
class QWidget;

ArgumentsLineEdit::ArgumentsLineEdit( const QString& text,
				      const QString& stopString,
				      QWidget*	     parent )
	: QLineEdit{ text, parent }
	, m_text{ text }
	, m_specialStr{ stopString }
{
	init();
}

ArgumentsLineEdit::ArgumentsLineEdit( QWidget* parent )
	: QLineEdit{ parent }
{
	init();
}

ArgumentsLineEdit::~ArgumentsLineEdit() = default;

void ArgumentsLineEdit::setStopString( const QString& str )
{
	m_specialStr = str;
}

QString ArgumentsLineEdit::stopString() const { return m_specialStr; }

void ArgumentsLineEdit::init()
{
	setStyleSheet( "QLineEdit{ "
		       "padding: 0 8px;"
		       "selection-background-color: darkgray;"
		       "font-family: Lucida Console, Courier New, monospace;"
		       "font-size: 13px;}" );

	setMouseTracking( true );
}

void ArgumentsLineEdit::mousePressEvent( QMouseEvent* event )
{
	if ( Qt::MouseButton btn = event->button();
	     btn == Qt::MouseButton::LeftButton || btn == Qt::MouseButton::RightButton )
	{
		QPoint position = event->pos();

		int posAt = cursorPositionAt( position );
		int index = text().indexOf( stopString() );

		if ( posAt >= index ) { emit symbolManuallyChanged(); }
	}
	QLineEdit::mousePressEvent( event );
}

void ArgumentsLineEdit::keyPressEvent( QKeyEvent* event )
{
	int cursorPos = cursorPosition();
	int strIndex  = text().indexOf( stopString() );

	qDebug() << text();

	setCursorPosition( cursorPos );

	if ( cursorPos >= strIndex ) { emit symbolManuallyChanged(); }
	QLineEdit::keyPressEvent( event );
}
