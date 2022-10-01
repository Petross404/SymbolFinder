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

#include <bits/basic_string.h>
#include <fmt/core.h>
#include <qapplication.h>
#include <qchar.h>    // for QChar
#include <qdebug.h>
#include <qdir.h>
#include <qglobal.h>	// for QNonConstOverload
#include <qlibrary.h>
#include <qnamespace.h>	   // for UniqueConnection
#include <qpluginloader.h>
#include <qstringliteral.h>

#include <algorithm>
#include <future>
#include <iostream>
#include <thread>

#include "../ConnectVerifier/connectverifier.hpp"    // for ConnectVerifier
#include "../Helper/string.hpp"
#include "interface/pluginmanager.hpp"
#include "plugins/nmdriver.hpp"		// for NmDriver
#include "plugins/scanelfdriver.hpp"	// for ScanelfDriver
// #include <QtConcurrent/qtconcurrentrun.h>

constexpr char g_spaceChar{ ' ' };
constexpr int  NoPlugin = -1;

std::string_view g_emptyStr{ "" };

namespace Invocation::Source {
std::string_view FromSymbol{ "#symbol#" }; /*<! Call from setSymbolName */
std::string_view FromReset{ "#default#" }; /*<! Call from resetInvocation */
};					   // namespace Invocation::Source

Scanner::Scanner( std::optional<QObject*> parent )
	: QObject{ parent.value_or( nullptr ) }
{
	init( m_selectedDriverName );
}

Scanner::~Scanner() = default;

std::list<std::string_view> Scanner::defaultInvocation() const
{
	return driver().has_value() ? driver().value()->defaultInvocation()
				    : string::create_list( g_emptyStr );
}

std::list<std::string_view> Scanner::invocation() const
{
	return driver().has_value() ? driver().value()->invocation()
				    : string::create_list( g_emptyStr );
}

void Scanner::resetInvocation()
{
	// Call setInvocation with m_resetArg
	std::string_view strDefArguments{ string::join_string_list( defaultInvocation() ) };

	setInvocation( strDefArguments, Invocation::Source::FromReset );
}

std::optional<IDriver*> Scanner::driver() const
{
	return m_d.has_value() ? m_d : std::nullopt;
}

void Scanner::init( std::string_view driverName )
{
	try
	{
		setEffectiveDriverName( driverName );
		init();

		const IDriver* d{ driver().has_value() ? driver().value() : nullptr };
		const std::string drName{ d != nullptr ? d->driverName() : g_emptyStr };

		/*
		 * setupConnections must be ran the first time a driver got
		 * initialized. Any subsequent invocation of this code must
		 * ignore setupConnections.
		 */
		static std::uint16_t initCounter     = 0;
		const std::uint16_t  firstInvocation = 1;

		if ( d != nullptr )
		{
			if ( initCounter == firstInvocation )
			{
				setupConnections( initCounter, drName );
			}
		}

		// Increment counter until next time.
		initCounter++;

	} catch ( ConnectVerifierException& e )
	{
		std::cerr << e.what() << std::endl;
	} catch ( std::exception& e )
	{
		std::cerr << e.what() << std::endl;
	}
}

/*
 * init() can be ran multiple times; not just the first time Scanner is contructed.
 * The first this is called, no driver name is set. Thus
 */
void Scanner::init()
{
	// Only discover load the plugins the first time...
	if ( !PluginManager::pluginsCounter() && selectedDriverName().empty() )
	{
		if ( !loadDriverPlugins() )
		{
			// TODO
		}
	}

	setupDriver( std::nullopt );
}

std::uint16_t Scanner::loadDriverPlugins()
{
	m_pluginManager = new PluginManager{ this };
	return m_pluginManager->pluginsNumber();
}

std::vector<PluginDriver> Scanner::plugins() const { return m_plugins; }

std::vector<PluginDesc> Scanner::pluginDescription() const
{
	std::vector<PluginDesc> v;

	const PluginsTable pluginTable{ m_pluginManager->registeredPlugins() };

	for ( auto const& [pair, initcallback] : pluginTable )
	{
		v.push_back( pair );
	}

	return v;
}

void Scanner::setupConnections( std::uint16_t counter, const std::string_view drName ) const
{
	const IDriver* d{ driver().value() };

	if ( counter ) { return; }

	ConnectVerifier v;

	/*
	 * When the Driver is done producing output in the stdout,
	 * set the relevant property of Scanner by reading the former.
	 */
	v = connect( d,
		     &QProcess::readyReadStandardOutput,
		     this,
		     &Scanner::setStandardOutSlot,
		     Qt::UniqueConnection );

	/*
	 * When the Driver is done producing output in the stderr,
	 * set the relevant property of Scanner by reading the former.
	 */
	v = connect( d,
		     &QProcess::readyReadStandardError,
		     this,
		     &Scanner::setStandardErrSlot,
		     Qt::UniqueConnection );

	// Emit a signal when the driver is started.
	v = connect( d, &QProcess::started, this, &Scanner::scanStarted, Qt::UniqueConnection );

	// Emit a signal when the driver is finished.
	v = connect( d,
		     qOverload<int, QProcess::ExitStatus>( &QProcess::finished ),
		     this,
		     &Scanner::scanFinished,
		     Qt::UniqueConnection );

	v = connect( m_pluginManager,
		     &PluginManager::driverInitialized,
		     this,
		     [this]( IDriver* const driver ) {
			     emit driverInitialized( driver->driverName() );
		     } );

	v = connect( this,
		     &Scanner::driverInitialized,
		     this,
		     &Scanner::driverInitializedSlot,
		     Qt::UniqueConnection );

	// Emit a signal when the driver's symbol, internally changed size.
	v = connect( d,
		     &IDriver::symbolSizeChanged,
		     this,
		     &Scanner::symbolSizeChanged,
		     Qt::UniqueConnection );
}

void Scanner::performScanSlot() const { driver().value()->exec(); }

bool Scanner::canQuit() const
{
	bool quit = true;

	if ( const IDriver * pdriver{ driver().value() }; pdriver != nullptr )
	{
		quit = pdriver->canDriverQuit();
	}

	return quit;
}

void Scanner::reset( std::string_view driverName ) { init( driverName ); }

void Scanner::setEffectiveDriverName( std::optional<std::string_view> driverName )
{
	m_selectedDriverName = driverName.value_or( g_emptyStr );
}

const std::string Scanner::selectedDriverName() { return m_selectedDriverName; }

void Scanner::setSymbolName( std::string_view symbol )
{
	const std::string_view oldSymbol{ symbolName() };

	// If the symbols don't match, update.
	if ( ( oldSymbol != symbol && oldSymbol.size() != symbol.size() ) )
	{
		driver().value()->setSymbolName( symbol );

		/*
		 * Every time the symbol name is changed, the arguments of the
		 * command should be informed of this change. We must call
		 * setInvocation here. This has the side-effect that updates the
		 * widget that is holding the arguments as well.
		 *
		 * We call Scanner::setInvocation with m_symbolArg, to let the
		 * function know it was called after a symbol change took place.
		 */
		std::string_view strArguments{ string::join_string_list( invocation() ) };
		setInvocation( strArguments, Invocation::Source::FromSymbol );
	}
}

void Scanner::setInvocation( std::string_view		     arguments,
			     std::optional<std::string_view> secret )
{
	/*
	 * There are three ways for this function to be invoked:
	 *
	 * A) secret == m_symbolArg which means that this function was called from
	 * Scanner::setSymbolName(..) and the currentArguments should be initialized
	 * from the driver with Scanner::invocation().
	 *
	 * B) secret == m_resetArg which means that this function was called from
	 * Scanner::resetInvocation when a signal-slot connection asked for it.
	 *
	 * C) secret != m_symbolArg && !m_resetArg which means that this function
	 * was called from somewhere else (ie by a slot connected to a signal) and
	 * that the passed parameter `args` should be used.
	 */
	std::string currentDriverArgs;

	if ( secret.has_value() )
	{
		if ( secret == Invocation::Source::FromSymbol )
		{
			currentDriverArgs = string::join_string_list( invocation() );
		}
		else if ( secret == Invocation::Source::FromReset )
		{
			currentDriverArgs =
				string::join_string_list( defaultInvocation() );
		}
		else { currentDriverArgs = arguments; }
	}

	/*
	 * We need the previous symbol name as well to remove it from the string
	 * and we need  to hold it's value between function invocations.
	 */
	std::string_view   symbol{ symbolName() };
	static std::string oldSymbol;
	static std::string oldArguments{ currentDriverArgs };

	// The first time a symbol is entered, there isn't an old symbol.
	if ( oldSymbol.empty() ) { oldSymbol = symbol; }

	// +1 because we need to insert to the next position.
	int indexOfStop = static_cast<int>( stopIndexOfArguments().indexOfStop ) + 1;

	/*
	 * Convert the QStringList to string in place and cut it in half, with the
	 * stopStr being the last character of the first half. Then add the parts
	 * with symbol to create a single one.
	 *
	 * Then, call the driver to actually change the arguments for the driver to
	 * run. Emit that the arguments changed, only if this function was called
	 * from setSymbolName() or resetInvocation().
	 *
	 * This is to avoid recursively emmiting after editing the text.
	 */
	std::string afterStopStr{
		currentDriverArgs.substr( indexOfStop, currentDriverArgs.size() ) };
	std::string_view untilStopStr{ currentDriverArgs.substr( 0, indexOfStop ) };

	/*
	 * Delete any occurances of the old symbol from the substring.
	 * Then, update the current arguments to reflect this change.
	 */
	std::string::size_type pos = afterStopStr.find( oldSymbol );
	if ( pos != std::string::npos )
	{
		std::string::iterator iter{
			std::ranges::find( afterStopStr, *oldSymbol.data() ) };
		afterStopStr.erase( iter );
	}

	currentDriverArgs = string::tostring( untilStopStr )
			    + string::tostring( symbol ) + afterStopStr;

	// if driver in null, setting the arguments will lead to crash.
	const bool succedded = ( driver().has_value() )
				       ? driver().value()->setInvocation( currentDriverArgs )
				       : false;

	// If setting the arguments succedded, emit a signal.
	if ( succedded
	     && ( secret == Invocation::Source::FromSymbol
		  || secret == Invocation::Source::FromReset ) )
	{
		emit argumentsUpdated();
	}

	// symbol is now "old". A new one will replace it next time.
	oldSymbol = symbol;
}

void Scanner::driverInitializedSlot( const std::string_view symbol )
{
	resetInvocation();

	// Nothing to set if empty
	if ( !symbol.empty() ) { setSymbolName( symbol ); }
}

StopIndex Scanner::stopIndexOfArguments() const
{
	return driver().has_value() ? driver().value()->stopIndex()
				    : StopIndex::makeStopIndex();
}

std::string Scanner::symbolName() const
{
	return driver().has_value() ? driver().value()->symbolName()
				    : string::tostring( g_emptyStr );
}

void Scanner::setStandardOutSlot()
{
	m_stdout = driver().value()->readAllStandardOutput();
	fmt::print( "{}", m_stdout );
}

void Scanner::setStandardErrSlot()
{
	m_stderr = driver().value()->readAllStandardError();
}

QByteArray Scanner::standardOut() const { return m_stdout; }

QByteArray Scanner::standardError() const { return m_stderr; }

void Scanner::aboutToCloseSlot() {}

void Scanner::setupDriver( std::optional<IDriver*> newDriver )
{
	/*
	 * The old driver doesn't exist in the first run, so it
	 * can be null. Therefore it is declared as an optional.
	 */
	std::optional<IDriver*> oldDriver{ driver() };

	/*
	 * If this is the first run there is no value yet, so we create a new
	 * driver. Else if old and new drivers are different, we take the
	 * function's argument to set the new driver instance of this class.
	 */
	gsl::owner<IDriver*> tmpDriver{ nullptr };
	if ( !newDriver.has_value() )
	{
		std::string_view selectedDriver{ selectedDriverName() };
		tmpDriver = m_pluginManager->chooseDriver( selectedDriver ).value();
	}
	else
	{
		if ( oldDriver.value() == newDriver.value() ) { return; }

		tmpDriver = newDriver.value();
	}

	// Set m_d with new driver.
	setDriver( std::move( tmpDriver ) );

	std::string_view drName{ driver().has_value() ? driver().value()->driverName()
						      : g_emptyStr };
	setEffectiveDriverName( drName );

	// Free the previous plugin memory.
	if ( oldDriver.has_value() ) { oldDriver.value()->deleteDriver(); }
}

void Scanner::setDriver( std::optional<IDriver*> d ) { m_d = d; }
