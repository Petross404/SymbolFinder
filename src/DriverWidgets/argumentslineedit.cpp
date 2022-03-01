// <one line to give the program's name and a brief idea of what it does.>
// SPDX-FileCopyrightText: 2022 Πέτρος Σιλιγκούνας <petross404@gmail.com>
// SPDX-License-Identifier: GPL-3.0-or-later

#include "argumentslineedit.hpp"

#include <qdebug.h>
#include <qevent.h>
#include <qtimer.h>
#include <qtooltip.h>

#include "../ConnectVerifier/connectverifier.hpp"

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

void ArgumentsLineEdit::init() { setMouseTracking( true ); }

void ArgumentsLineEdit::mousePressEvent( QMouseEvent* event )
{
	if ( event->button() == Qt::MouseButton::LeftButton )
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
	int index     = text().indexOf( stopString() );

	if ( cursorPos >= index ) { emit symbolManuallyChanged(); }
	QLineEdit::keyPressEvent( event );
}
