// <one line to give the program's name and a brief idea of what it does.>
// SPDX-FileCopyrightText: 2022 Πέτρος Σιλιγκούνας <petross404@gmail.com>
// SPDX-License-Identifier: GPL-3.0-or-later

#include "argumentslineedit_p.hpp"

#include <qnamespace.h>	       // for UniqueConnection
#include <qobject.h>	       // for QObject
#include <qobjectdefs.h>       // for QMetaObject::Co...
#include <qstringliteral.h>    // for QStringLiteral

#include <string>	  // for string
#include <string_view>	  // for string_view

#include "../../ConnectVerifier/connectverifier.hpp"	// for ConnectVerifier
#include "../../Helper/string.hpp"			// for tostring
#include "../../Scanner/interface/idriver.hpp"		// for StopIndex
#include "../argumentslineedit.hpp"			// for ArgumentsLineEdit

ArgumentsLineEditPrivate::ArgumentsLineEditPrivate( ArgumentsLineEdit* lineEdit,
						    const QString&     text,
						    StopIndex	       stopIndex )
	: q_ptr{ lineEdit }
	, m_text{ text }
	, m_stopIndex{ stopIndex }
{
	init();
}

ArgumentsLineEditPrivate::ArgumentsLineEditPrivate( std::optional<ArgumentsLineEdit*> lineEdit )
	: q_ptr{ lineEdit.value_or( nullptr ) }
{
	init();
}

ArgumentsLineEditPrivate::~ArgumentsLineEditPrivate() = default;

void ArgumentsLineEditPrivate::setStopIndex( const StopIndex& stopIndex )
{
	m_stopIndex		= stopIndex;
	m_stopIndex.indexOfStop = m_stopIndex.indexOfStop - 2;
}

StopIndex ArgumentsLineEditPrivate::stopIndex() const { return m_stopIndex; }

void ArgumentsLineEditPrivate::init()
{
	Q_Q( ArgumentsLineEdit );

	q->setStyleSheet( QStringLiteral(
		"QLineEdit{ "
		"padding: 0 8px;"
		"selection-background-color: darkgray;"
		"font-family: Lucida Console, Courier New, monospace;"
		"font-size: 13px;}" ) );

	q->setMouseTracking( true );

	ConnectVerifier v;

	// Make sure that the stop string can't be selected or deleted
	v = QObject::connect( q,
			      &ArgumentsLineEdit::selectionChanged,
			      q,
			      &ArgumentsLineEdit::checkStopString,
			      Qt::UniqueConnection );

	v = QObject::connect( q,
			      &ArgumentsLineEdit::symbolSizeChanged,
			      q,
			      &ArgumentsLineEdit::setSymbolSizeSlot,
			      Qt::UniqueConnection );

	setSymbolSize( m_text.count() );

	if ( !m_stopIndex.isNull() ) { m_stopIndex.indexOfStop -= 2; }
	else { m_stopIndex.indexOfStop = 0; }
}

void ArgumentsLineEditPrivate::checkStopString() const
{
	Q_Q( const ArgumentsLineEdit );

	std::string_view stop{ stopIndex().stopStr };
	if ( string::tostring( q->selectedText() ).find( stop ) )
	{
		emit q->symbolManuallyChanged();
	}
}

void ArgumentsLineEditPrivate::handleCursorPosition( std::uint16_t positionAt,
						     const Qt::MouseButton button ) const
{
	Q_Q( const ArgumentsLineEdit );

	int index = stopIndex().indexOfStop;

	/*
	 * Position shouldn't be near the index
	 */
	if ( !( positionAt >= index && positionAt < ( index + symbolSize() ) ) )
	{
		return;
	}

	switch ( button )
	{
		case Qt::MouseButton::LeftButton:
			emit q->symbolManuallyChanged();
			break;

		case Qt::MouseButton::RightButton:
		case Qt::MouseButton::MiddleButton: emit q->symbolPaste(); break;

		default: break;
	}
}

void ArgumentsLineEditPrivate::setSymbolSize( uint16_t size )
{
	m_synbolSz = size + 2;
}

std::uint16_t ArgumentsLineEditPrivate::symbolSize() const { return m_synbolSz; }
