/*
 * <one line to give the library's name and an idea of what it does.>
 * Copyright (C) 2022  <copyright holder> <email>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "scanner.hpp"

#include <qchar.h>    // for QChar
#include <qdebug.h>
#include <qglobal.h>	   // for QNonConstOverload
#include <qnamespace.h>	   // for UniqueConnection

#include "../ConnectVerifier/connectverifier.hpp"    // for ConnectVerifier
#include "Drivers/idriver.hpp"			     // for IDriver, StopIndex
#include "Drivers/nmdriver.hpp"			     // for NmDriver
#include "Drivers/scanelfdriver.hpp"		     // for ScanelfDriver

constexpr QChar spaceChar{ ' ' };

const QString m_secretSetSymbolArgument{ "#symbol#" }; /*<! Call from setSymbolName */
const QString m_secretSetResetArgument{ "#default#" }; /*<! Call from resetInvocation */

Scanner::Scanner( QObject* parent )
	: QObject{ parent }
{}

Scanner::Scanner( const QString& driverName, QObject* parent )
	: QObject{ parent }
	, m_name{ driverName }
{
	init();
}

Scanner::~Scanner() = default;

QStringList Scanner::defaultInvocation() const
{
	return m_d->defaultInvocation();
}

QStringList Scanner::invocation() const { return m_d->invocation(); }

// Call setInvocation with m_secretSetResetArgument
void Scanner::resetInvocation()
{
	setInvocation( defaultInvocation().join( spaceChar ), m_secretSetResetArgument );
}

Process::IDriver* Scanner::driver() const { return m_d; }

void Scanner::init( const QString& driverName )
{
	setDriverName( driverName );
	init();
}

void Scanner::init()
{
	if ( m_name == NmDriver::name() ) { m_d = new NmDriver{ this }; }
	else if ( m_name == ScanelfDriver::name() )
	{
		m_d = new ScanelfDriver{ this };
	}

	Q_ASSERT_X( m_d != nullptr,
		    tr( "Scanner::init" ).toLocal8Bit(),
		    tr( "m_d is null!" ).toLocal8Bit() );
}

void Scanner::setupConnections() const
{
	ConnectVerifier v;

	v = connect( driver(),
		     &QProcess::readyReadStandardOutput,
		     this,
		     &Scanner::setStandardOutSlot,
		     Qt::UniqueConnection );

	v = connect( driver(),
		     &QProcess::readyReadStandardError,
		     this,
		     &Scanner::setStandardErrSlot,
		     Qt::UniqueConnection );

	v = connect( driver(), &QProcess::started, this, &Scanner::scanStarted, Qt::UniqueConnection );

	v = connect( driver(),
		     qOverload<int, QProcess::ExitStatus>( &QProcess::finished ),
		     this,
		     &Scanner::scanFinished,
		     Qt::UniqueConnection );

	v = connect( driver(),
		     &Process::IDriver::driverInitialized,
		     this,
		     &Scanner::driverInitialized );
}

void Scanner::performScanSlot() { m_d->exec(); }

void Scanner::reset( const QString& driverName )
{
	init( driverName );
	setInvocation( driver()->defaultInvocation().join( "" ),
		       m_secretSetResetArgument );
}

void Scanner::setDriverName( const QString& driverName )
{
	m_name = driverName;
}

void Scanner::setSymbolName( const QString& symbol )
{
	const QString previousSymbolName = symbolName();

	// If the symbols don't match, update.
	if ( int newSize = symbol.size();
	     previousSymbolName != symbol && previousSymbolName.size() != newSize )
	{
		// Change the symbol in the Driver
		m_d->setSymbolName( symbol );
		emit symbolSizeChanged( newSize );

		// Call Scanner::setInvocation with m_secretArgument
		setInvocation( invocation().join( spaceChar ),
			       m_secretSetSymbolArgument );
	}
}

void Scanner::setInvocation( const QString& args, const QString& secret )
{
	/*
	 * There are three ways for this function to be invoked:
	 *
	 * A) secret == m_secretSetSymbolArgument which means that this function was
	 * called from Scanner::setSymbolName(..) and the currentArguments should be
	 * initialized from the driver with Scanner::invocation().
	 *
	 * B) secret == m_secretSetDefaultArgument which means that this function was
	 * called from Scanner::resetInvocation when a signal-slot connection asked
	 * for it.
	 *
	 * C) secret != m_secretArgument && m_secretSetDefaultArgument which means that
	 * this function was called from somewhere else (ie by a slot connected to a
	 * signal) and that the passed parameter `args` should be used.
	 */
	QStringList currentArguments{ secret == m_secretSetSymbolArgument
					      ? invocation()
					      : args.split( spaceChar ) };

	QString argsStr{ currentArguments.join( spaceChar ) };

	/*
	 * We need the previous symbol name as well, to remove it from the string and
	 * we need it to keep it's value between function invocations.
	 */
	const QString  symbol{ symbolName() };
	static QString oldSymbol;

	if ( oldSymbol.isNull() ) { oldSymbol = symbol; }

	// +1 because we need to insert to the next position.
	int indexOfStop = stopIndexOfDriver().indexOfStop + 1;

	/*
	 * Cut the string in half, with the stopStr being the last character of
	 * the first half. Then prepend the symbol to the second part and
	 * re-unite the two parts again.
	 *
	 * Then, call the driver to actually change the arguments for the driver
	 * to run but emit that the arguments changed, only if this function was
	 * called from setSymbolName() or resetInvocation().
	 *
	 * This is to avoid recursively emmiting after editing the text.
	 */
	QString untilStopString{ argsStr.left( indexOfStop ) };
	QString afterStopString{ argsStr.right( argsStr.size() - indexOfStop ) };

	if ( afterStopString.contains( oldSymbol ) )
	{
		afterStopString.remove( oldSymbol );
	}

	// Now, the symbol is old. A new one will replace it next time.
	oldSymbol = symbol;

	currentArguments =
		QString{ untilStopString + symbol + afterStopString }.split( spaceChar );

	if ( m_d->setInvocation( currentArguments )
	     && ( secret == m_secretSetSymbolArgument || secret == m_secretSetResetArgument ) )
	{
		emit argumentsUpdated();
	}
}

StopIndex Scanner::stopIndexOfDriver() const { return m_d->stopIndex(); }

QString Scanner::symbolName() const { return m_d->symbolName(); }

void Scanner::setStandardOutSlot() { m_stdout = m_d->readAllStandardOutput(); }

void Scanner::setStandardErrSlot() { m_stderr = m_d->readAllStandardError(); }

QByteArray Scanner::standardOut() const { return m_stdout; }

QByteArray Scanner::standardError() const { return m_stderr; }
