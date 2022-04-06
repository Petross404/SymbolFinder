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

#include <qapplication.h>
#include <qchar.h>    // for QChar
#include <qdebug.h>
#include <qdir.h>
#include <qglobal.h>	// for QNonConstOverload
#include <qlibrary.h>
#include <qnamespace.h>	   // for UniqueConnection
#include <qpluginloader.h>

#include <algorithm>
#include <iostream>

#include "../ConnectVerifier/connectverifier.hpp"    // for ConnectVerifier
#include "interface/driverfactory.hpp"
#include "plugins/nmdriver.hpp"		// for NmDriver
#include "plugins/scanelfdriver.hpp"	// for ScanelfDriver

constexpr QChar spaceChar{ ' ' };
constexpr int	NoPlugin = -1;

const QString m_symbolArg{ "#symbol#" }; /*<! Call from setSymbolName */
const QString m_resetArg{ "#default#" }; /*<! Call from resetInvocation */

using CreateCallBack	 = IDriver* (*)( QObject* parent );
using DriverNameCallback = QString ( * )();
using ArgumentsCallBack	 = QStringList ( * )();

Scanner::Scanner( QObject* parent )
	: QObject{ parent }
	, DriverFactory{}
{
	bool calledFromCtor = true;
	init( m_choosenDriverName, calledFromCtor );
}

Scanner::Scanner( const QString& driverName, QObject* parent )
	: QObject{ parent }
	, DriverFactory{}
	, m_choosenDriverName{ driverName }
{
	bool calledFromCtor = true;
	init( m_choosenDriverName, calledFromCtor );
}

Scanner::~Scanner() = default;

QStringList Scanner::defaultInvocation() const
{
	return driver()->defaultInvocation();
}

QStringList Scanner::invocation() const { return driver()->invocation(); }

void Scanner::resetInvocation()
{
	// Call setInvocation with m_resetArg
	setInvocation( defaultInvocation().join( spaceChar ), m_resetArg );
}

IDriver* Scanner::driver() const { return m_d; }

void Scanner::init( const QString& driverName, bool calledFromCtor )
{
	try
	{
		setDriverName( driverName );
		init();

		if ( calledFromCtor ) { setupConnections(); }
	} catch ( ConnectVerifierException& e )
	{
		std::cerr << e.what() << std::endl;
	} catch ( std::exception& e )
	{
		std::cerr << e.what() << std::endl;
	}
}

/*
 * init can be ran multiple times; not just the first time Scanner is contructed.
 */
void Scanner::init()
{
	// Only run the first time ie when m_plugins is empty
	if ( m_pluginCount && m_choosenDriverName.isEmpty() )
	{
		if ( loadDriverPlugins() != 0 )
		{
			static QStringList pluginNames;
			for ( PluginDriver pair : m_plugins )
			{
				pluginNames << pair.driverName;
			}
			emit pluginsLoaded( pluginNames );
			qDebug() << pluginNames;
		}
	}

	if ( !driver() || m_choosenDriverName.isEmpty() )
	{
		qDebug() << "m_name" << m_choosenDriverName;
		int i = -1;
		for ( PluginDriver& pair : m_plugins )
		{
			i++;

			// TODO !!! Make scanner{} to NOT initialize m_name, and append to m_d the first plugin.
			// TODO Later, inform the UI about the plugins and let it handle the insertion. For now,
			//  m_d must be initialized to the first plugin, and inform the combobox about it to select it visually.
			const QString currentName{ pair.driverName };

			/*
			 * It make sense to initialize m_d to the first available plugin as none is
			 * selected when the UI first starts.
			 */
			if ( auto d = static_cast<IDriver*>( pair.driver );
			     d != nullptr && !m_choosenDriverName.isEmpty() )
			{
				if ( m_choosenDriverName == currentName )
				{
					m_d = static_cast<IDriver*>( pair.driver );
					setDriver( pair.driver,
						   std::bind( &Scanner::createDriver,
							      this,
							      currentName,
							      this ) );
				}
			}
			else if ( m_choosenDriverName.isEmpty() && i == 0 )
			{
				m_d = static_cast<IDriver*>( pair.driver );
				setDriver( pair.driver,
					   std::bind( &Scanner::createDriver,
						      this,
						      currentName,
						      this ) );
			}
		}
	}
	else
	{
		for ( PluginDriver& pair : m_plugins )
		{
			if ( m_choosenDriverName == pair.driverName )
			{
				// Allocate a new Driver, if there isn't already created for this plugin.
				if ( pair.driver == nullptr || pair.driver != m_d )
				{
					m_d = static_cast<IDriver*>( pair.driver );
					setDriver( pair.driver,
						   std::bind( &Scanner::createDriver,
							      this,
							      m_choosenDriverName,
							      this ) );
				}

				qDebug() << driver()->driverName()
					 << driver()->defaultInvocation().join( spaceChar );

				setSymbolName( symbolName() );
				emit driverInitialized( driver()->driverName() );
			}
		}
	}
	qDebug() << "After init" << m_d->driverName();
}

int Scanner::loadDriverPlugins()
{
	/*
	 * The plugins have a different directory stucture from the one when
	 * they are installed. If the app is being ran from the src tree, we
	 * must take care of this situation.
	 */
	bool isRunningInRepo = true;
	QDir appDir{ QApplication::applicationDirPath() };

	if ( !appDir.absolutePath().contains( "build" )
	     || !appDir.absolutePath().contains( qAppName(), Qt::CaseInsensitive ) )
	{
		isRunningInRepo = false;
	}

	// ${PREFIX}/lib64/scanner/plugins/*

	QDir pluginDir{ appDir };

	// qDebug() << QCoreApplication::libraryPaths();
	if ( isRunningInRepo )
	{
		if ( !pluginDir.cd( "src/Scanner/plugins" ) )
		{
			return NoPlugin;
		}
	}
	else
	{
		QDir root = QDir::root();
		root.cd( "usr/lib64/Scanner/plugins" );

		if ( !pluginDir.cd( root.absolutePath() ) ) { return NoPlugin; }
	}

	/*
	 * Read the contents of the directory and keep only the libraries
	 * and those who aren't symlinks.
	 */
	QStringList pluginNameList;
	for ( const QFileInfo& fileInfo : pluginDir.entryInfoList( QDir::Files ) )
	{
		if ( QLibrary::isLibrary( fileInfo.absoluteFilePath() )
#ifdef Q_OS_UNIX
		     && !fileInfo.isSymbolicLink()
#elif Q_OS_WIN
		     && fileInfo.isShortcut()
#endif
		)
		{
			qDebug() << "fileInfo" << fileInfo.fileName();
			pluginNameList.append( fileInfo.fileName() );
		}
	}

	/*
	 * Register the plugins with their respective "create"
	 * function so that later we can instantiate them based on their name.
	 */
	for ( const QString& fileName : pluginNameList )
	{
		QLibrary* library{ new QLibrary{ fileName, this } };

		CreateCallBack createDriverFn{ reinterpret_cast<CreateCallBack>(library->resolve( "create" ) ) };
		DriverNameCallback driverNameFn{
			reinterpret_cast<DriverNameCallback>(library->resolve(
				"driverNameStatic" ) ) };
		ArgumentsCallBack argumentsFn =
			(ArgumentsCallBack)library->resolve(
				"argumentsStatic" );

		if ( createDriverFn && driverNameFn && argumentsFn )
		{
			const QString driverName{ driverNameFn() };
			// Register the plugin, it will be retrieved later to be instantiated.
			registerPlugin( driverName,
					std::bind( createDriverFn, this ) );

			m_pluginCount++;
		}
		else
		{
			return NoPlugin;
		}
	}

	return m_pluginCount;
}

std::vector<PluginDriver> Scanner::plugins() const { return m_plugins; }

void Scanner::setupConnections() const
{
	// When no driver plugins are found, this shouldn't crash.
	Driver* d{ static_cast<Driver*>( driver() ) };
	if ( d == nullptr ) { return; }

	ConnectVerifier v;

	// v = false;
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

	// Emit a signal when the driver is (re)initialized.
	v = connect( d,
		     &Driver::driverInitialized,
		     this,
		     &Scanner::driverInitialized,
		     Qt::UniqueConnection );

	v = connect( this,
		     &Scanner::driverInitialized,
		     this,
		     &Scanner::driverInitializedSlot,
		     Qt::UniqueConnection );

	v = connect( this,
		     &Scanner::driverReset,
		     this,
		     &Scanner::driverInitializedSlot,
		     Qt::UniqueConnection );

	// Emit a signal when the driver's symbol, internally changed size.
	v = connect( d,
		     &Driver::symbolSizeChanged,
		     this,
		     &Scanner::symbolSizeChanged,
		     Qt::UniqueConnection );
}

void Scanner::performScanSlot() const { driver()->exec(); }

bool Scanner::canQuit() const
{
	bool quit = true;
	if ( IDriver * d{ driver() }; d != nullptr )
	{
		quit = d->canDriverQuit();
	}
	else
	{
		throw std::runtime_error( tr( "Driver is null" ).toLatin1() );
	}
	return quit;
}

void Scanner::reset( const QString& driverName ) { init( driverName ); }

void Scanner::setDriverName( const QString& driverName )
{
	m_choosenDriverName = driverName;
}

void Scanner::setSymbolName( const QString& symbol )
{
	const QString oldSymbol = symbolName();

	// If the symbols don't match, update.
	if ( int sz = symbol.size(); oldSymbol != symbol && oldSymbol.size() != sz )
	{
		m_d->setSymbolName( symbol );

		/*
		 * Every time the symbol name is changed, the arguments of the
		 * command should be informed of this change. We must call
		 * setInvocation here. This has the side-effect that updates the
		 * widget that is holding the arguments as well.
		 *
		 * We call Scanner::setInvocation with m_symbolArg, to let the
		 * function know it was called after a symbol change took place.
		 */
		setInvocation( invocation().join( spaceChar ), m_symbolArg );
	}
}

void Scanner::setInvocation( const QString& arguments, const QString& secret )
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
	 * C) secret != m_symbolArg && !m_resetArg which means that this function was
	 * called from somewhere else (ie by a slot connected to a signal) and that
	 * the passed parameter `args` should be used.
	 */
	QStringList currentArguments{ secret == m_symbolArg
					      ? invocation()
					      : arguments.split( spaceChar ) };

	/*
	 * We need the previous symbol name as well, to remove it from the string and
	 * we need it to keep it's value between function invocations.
	 */
	const QString	   symbol{ symbolName() };
	static QString	   oldSymbol;
	static QStringList oldArguments{ currentArguments };

	if ( oldSymbol.isNull() ) { oldSymbol = symbol; }

	// +1 because we need to insert to the next position.
	int indexOfStop = stopIndexOfDriver().indexOfStop + 1;
	int rightSize = currentArguments.join( spaceChar ).size() - indexOfStop;

	/*
	 * Convert the QStringList to string in place and cut it in half, with
	 * the stopStr being the last character of the first half. Then add the
	 * parts with symbol to create a single one.
	 *
	 * Then, call the driver to actually change the arguments for the driver
	 * to run. Emit that the arguments changed, only if this function was
	 * called from setSymbolName() or resetInvocation().
	 *
	 * This is to avoid recursively emmiting after editing the text.
	 */
	QString untilStopStr{ currentArguments.join( spaceChar ).left( indexOfStop ) };
	QString afterStopStr{ currentArguments.join( spaceChar ).right( rightSize ) };

	if ( afterStopStr.contains( oldSymbol ) )
	{
		afterStopStr.remove( oldSymbol );
	}

	currentArguments = ( untilStopStr + symbol + afterStopStr ).split( spaceChar );

	bool succedded = driver()->setInvocation( currentArguments );

	if ( succedded && ( secret == m_symbolArg || secret == m_resetArg ) )
	{
		emit argumentsUpdated();
	}

	// Symbol is now old. A new one will replace it next time.
	oldSymbol = symbol;
}

void Scanner::driverInitializedSlot( const QString& symbol )
{
	resetInvocation();
	setSymbolName( symbol );
}

StopIndex Scanner::stopIndexOfDriver() const { return m_d->stopIndex(); }

QString Scanner::symbolName() const { return m_d->symbolName(); }

void Scanner::setStandardOutSlot()
{
	m_stdout = static_cast<Driver*>( m_d )->readAllStandardOutput();
	qDebug() << m_stdout;
}

void Scanner::setStandardErrSlot()
{
	m_stderr = static_cast<Driver*>( m_d )->readAllStandardError();
}

QByteArray Scanner::standardOut() const { return m_stdout; }

QByteArray Scanner::standardError() const { return m_stderr; }

void Scanner::aboutToCloseSlot() {}

void Scanner::setDriver( IDriver* pairDriver, callback_t createDriver )
{
	// Throw if newDriver is null and append it to the driver that is paired with QPluginLoader.
	IDriver* newDriver{ createDriver( this ) };
	if ( !newDriver )
	{
		throw std::runtime_error( tr( "Driver is null" ).toLatin1() );
	}
	pairDriver = newDriver;

	// Now get busy with m_d
	IDriver* oldDriver = driver();
	if ( oldDriver != newDriver )
	{
		m_d = newDriver;

		QString symbolName{ "" };
		if ( oldDriver != nullptr )
		{
			symbolName = oldDriver->symbolName();
		}

		emit driverReset( symbolName );
	}
}
