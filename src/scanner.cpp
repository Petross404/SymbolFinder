// <one line to give the program's name and a brief idea of what it does.>
// SPDX-FileCopyrightText: 2022 Πέτρος Σιλιγκούνας <petross404@gmail.com>
// SPDX-License-Identifier: GPL-3.0-or-later

#include "scanner.hpp"

#include <qdebug.h>
#include <qlineedit.h>
#include <qtextbrowser.h>

#include "ConnectVerifier/connectverifier.hpp"
#include "findermainwindow.hpp"
#include "idriver.hpp"
#include "nmdriver.hpp"

Scanner::Scanner( QObject* parent )
	: QObject{ parent }
	, m_d{ nullptr }

{}

Scanner::Scanner( const QString& driverName, QObject* parent )
	: QObject{ parent }
	, m_name{ driverName }
{
	if ( m_name == NmDriver::stDriverName() )
	{
		m_d = new NmDriver{ this };
	}
}

Scanner::~Scanner() = default;

QStringList Scanner::defaultInvocation() const
{
	return m_d->defaultInvocation();
}

QStringList Scanner::invocation() const { return m_d->invocation(); }

IDriver* Scanner::driver() const { return m_d; }

void Scanner::scanSymbol( const QString& name ) {}

void Scanner::setupConnections()
{
	ConnectVerifier v;

	v = connect( m_d,
		     &QProcess::readyReadStandardOutput,
		     this,
		     &Scanner::setStandardOutSlot,
		     Qt::UniqueConnection );

	v = connect( m_d,
		     &QProcess::readyReadStandardError,
		     this,
		     &Scanner::setStandardErrorSlot,
		     Qt::UniqueConnection );
}

void Scanner::setSymbolName( const QString& symbol )
{
	const QString previousSymbolName = symbolName();

	// If the symbol doesn't exist in the list, update.
	if ( previousSymbolName != symbol )
	{
		m_d->setSymbolName( symbol );
		QString arguments = invocation().join( ' ' );
		setInvocation( arguments, true );
	}
}

void Scanner::setInvocation( const QString& args, bool changedSymbol )
{
	QStringList currentArguments =
		changedSymbol ? args.split( ' ' ) : invocation();

	if ( args.split( ' ' ) != currentArguments )
	{
		if ( args.isEmpty() ) { return; }

		QString newArgs = args;
		QString stopStr = m_d->stopString();

		// +1 because we need to insert to the next position.
		int index = newArgs.indexOf( stopStr ) + 1;

		/*
		 * Insert the symbolName where it belongs and call the driver
		 * function to set it's arguments.
		 */
		newArgs.insert( index, symbolName() );
		m_d->setInvocation( newArgs.split( ' ' ) );

		// All set, now emit the signal.
		emit argumentsUpdated();
	}
}

QString Scanner::symbolName() const { return m_d->symbolName(); }

void Scanner::setStandardOutSlot() { m_stdout = m_d->readAllStandardOutput(); }

void Scanner::setStandardErrorSlot()
{
	m_stderr = m_d->readAllStandardOutput();
}

QByteArray Scanner::standardOut() const { return m_stdout; }

QByteArray Scanner::standardError() const { return m_stderr; }
