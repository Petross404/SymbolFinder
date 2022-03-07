// <one line to give the program's name and a brief idea of what it does.>
// SPDX-FileCopyrightText: 2022 Πέτρος Σιλιγκούνας <petross404@gmail.com>
// SPDX-License-Identifier: GPL-3.0-or-later

#include "scanner.hpp"

#include <qdebug.h>
#include <qlineedit.h>
#include <qtextbrowser.h>

#include "ConnectVerifier/connectverifier.hpp"
#include "findermainwindow.hpp"
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

void Scanner::performScan() { m_d->exec(); }

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

	v = connect( m_d, &QProcess::started, this, &Scanner::scanStarted, Qt::UniqueConnection );

	v = connect( m_d,
		     qOverload<int, QProcess::ExitStatus>( &QProcess::finished ),
		     this,
		     &Scanner::scanFinished,
		     Qt::UniqueConnection );
}

void Scanner::setSymbolName( const QString& symbol )
{
	const QString previousSymbolName = symbolName();

	// If the symbols don't match, update.
	if ( previousSymbolName != symbol )
	{
		m_d->setSymbolName( symbol );
		setInvocation( invocation().join( ' ' ), m_secretArgument );
	}
}

void Scanner::setInvocation( const QString& args, const QString& secret )
{
	/*
	 * There are two ways for this function to be called:
	 *
	 * A) secret == m_secretArgument which means that this function was
	 * called from Scanner::setSymbolName(..) and the currentArguments
	 * should be initialized from the driver with Scanner::invocation().
	 *
	 * B) secret != m_secretArgument which means that this function was
	 * called from somewhere else (ie by a slot connected to a signal)
	 * and that the passed parameter `args` should be used. m_secretArgument
	 * is private and constant and no other user of this class can know
	 * it and confuse Scanner::setInvocation(...), since the latter uses
	 * default argument for the second parameter.
	 */
	QStringList currentArguments =
		secret == m_secretArgument ? invocation() : args.split( ' ' );

	QString stopStr = stopString();
	QString argsStr = currentArguments.join( ' ' );

	// +1 because we need to insert to the next position.
	int indexOfStop = argsStr.indexOf( stopStr ) + 1;
	int symbolSize	= symbolName().size();

	/*
	 * Replace (in the widget) `symbolSize` characters at position
	 * `stopIndex`, with the new name that is returned from
	 * symbolName(). Then, call the driver to actually change
	 * the arguments for the driver to run.
	 */
	if ( secret == m_secretArgument )
	{
		argsStr.replace( indexOfStop, symbolSize, symbolName() );
	}
	m_d->setInvocation( currentArguments );

	// All set, now emit the signal.
	emit argumentsUpdated();
}

QString Scanner::stopString() const { return m_d->stopString(); }

QString Scanner::symbolName() const { return m_d->symbolName(); }

void Scanner::setStandardOutSlot() { m_stdout = m_d->readAllStandardOutput(); }

void Scanner::setStandardErrorSlot()
{
	m_stderr = m_d->readAllStandardOutput();
}

QByteArray Scanner::standardOut() const { return m_stdout; }

QByteArray Scanner::standardError() const { return m_stderr; }
