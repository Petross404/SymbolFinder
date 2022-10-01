/*
 * <one line to give the library's name and an idea of what it does.>
 * Copyright (C) 2022  petros <email>
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

#include "pluginmanager.hpp"

#include <fmt/core.h>
#include <qapplication.h>
#include <qdebug.h>
#include <qdir.h>
#include <qglobal.h>
#include <qlibrary.h>
#include <qlibraryinfo.h>
#include <qregularexpression.h>

#include <functional>
#include <gsl/pointers>	   // for owner
#include <iostream>
#include <memory>

#include "../../ConnectVerifier/connectverifier.hpp"
#include "../../Helper/string.hpp"
#include "idriver.hpp"
#include "pluginmanager_p.hpp"

using FnPtr  = QFunctionPointer;
using InitCB = IDriver* (*)( QObject* parent );

constexpr int NoPlugin{ 0 };
const QChar   emptyChar{ ' ' };

std::uint16_t g_pluginsNumber{ 0 };

PluginManager::PluginManager( QObject* parent )
	: QObject{ parent }
	, d_ptr{ new PluginManagerPrivate( this ) }
	, m_currentDriver{ std::make_optional<IDriver*>() }
{
	Q_D( PluginManager );
	Q_ASSERT_X( d->q_ptr == this, "", "" );

	lookup();

	ConnectVerifier v;

	v = connect( this,
		     &PluginManager::driverInitialized,
		     this,
		     &PluginManager::setCurrentDriver,
		     Qt::UniqueConnection );
}

PluginManager::~PluginManager() { delete d_ptr; }

void PluginManager::lookup()
{
	bool isRunningInRepo = true;
	QDir pluginDir;

	/*
	 * The plugins have a different directory stucture from the one when they
	 * are installed. If the app is being ran from the src tree, we must take
	 * care of this situation.
	 */
	QDir appDir{ QApplication::applicationDirPath() };

	if ( !appDir.absolutePath().contains( QStringLiteral( "build" ) )
	     || !appDir.absolutePath().contains( qAppName(), Qt::CaseInsensitive ) )
	{
		isRunningInRepo = false;
	}

	QStringList libPaths;

	// This is about scanner plugins, not other qt5 plugins
	const QString systemPluginPath{ QLibraryInfo::location( QLibraryInfo::PluginsPath )
					+ QStringLiteral( "/scanner/" ) };

	QCoreApplication::addLibraryPath( systemPluginPath );

	if ( isRunningInRepo )
	{
		const QString developmentPluginPath{ "/src/Scanner/plugins/" };

		/*
		 * When this is running from inside the repository, it has to
		 * look for plugins at src/Scanner/plugins. Other paths are
		 * removed, to favor these plugins when it's under development.
		 */
		QCoreApplication::removeLibraryPath( appDir.absolutePath() );

		/*
		 * If src/Scanner/plugins doesn't exist it is because we don't
		 * need to develop further any plugin. In this case, look at the
		 * system installed plugins (if any).
		 */
		std::string developmentPath{ appDir.absolutePath().toStdString()
					     + developmentPluginPath.toStdString() };

		if ( pluginDir.cd( string::toqstring( developmentPath ) ) )
		{
			// Add the build dir of the executable
			QCoreApplication::addLibraryPath(
				string::toqstring( developmentPath ) );
			fmt::print( stderr, "libraryPath: {}\n", developmentPath );
		}
		else
		{
			fmt::print( stderr,
				    "{} doesn't exist or couldn't cd in.\n",
				    developmentPath );
		}
	}

	// Append the paths in a variable
	libPaths = QCoreApplication::libraryPaths();

	for ( QString path : libPaths )
	{
		findPlugins( isRunningInRepo, QDir{ path } );
	}
}

std::uint16_t PluginManager::pluginsNumber() const
{
	return static_cast<std::uint16_t>( registeredPlugins().size() );
}

const std::vector<PluginDesc> PluginManager::pluginsDescription() const
{
	Q_D( const PluginManager );

	return d->pluginNames();
}

const PluginsTable PluginManager::registeredPlugins() const
{
	Q_D( const PluginManager );

	return d->registeredPlugins();
}

void PluginManager::unregisterIDriver( std::string_view driverName )
{
	Q_D( PluginManager );

	d->unregisterPlugin( driverName );
}

std::optional<IDriver*> PluginManager::createDriver( std::string_view driverName )
{
	Q_D( PluginManager );

	/*
	 * DriverFactory::initPlugin catches a null value in the case of a memory
	 * error. If this is null then the driver might not have been registered.
	 */
	std::optional<IDriver*> pdriver{ d->initPlugin( driverName, this ) };

	return pdriver;
}

std::optional<IDriver*> PluginManager::chooseDriver( std::string_view driverName )
{
	return createDriver( driverName );
}

std::optional<IDriver*> PluginManager::currentDriver() const
{
	return m_currentDriver;
}

void PluginManager::setCurrentDriver( std::optional<IDriver*> driver )
{
	m_currentDriver = driver;
}

void PluginManager::findPlugins( bool isRunningInRepo, const QDir& pluginDir )
{
	/*
	 * Read the contents of the directory and keep only the libraries
	 * and those who aren't symlinks.
	 */
	for ( const QFileInfo& fileInfo : pluginDir.entryInfoList( QDir::Filter::Files ) )
	{
		if ( !QLibrary::isLibrary( fileInfo.absoluteFilePath() )
#ifdef Q_OS_UNIX
		     || fileInfo.isSymbolicLink()
#elif Q_OS_WIN
		     || fileInfo.isShortcut()
#endif
		)
		{
			break;
		}

		std::string absPath{ string::tostring( fileInfo.absolutePath() )
				     + std::string{ "/" } };
		std::string suffix{ string::tostring( fileInfo.completeSuffix() ) };

		std::string libraryName{ absPath + string::tostring( fileInfo.fileName() ) };
		fmt::print( stderr, "{:s}\n", libraryName );

		preparePlugin( libraryName );
	}
}

void PluginManager::preparePlugin( std::string_view libraryName )
{
	Q_D( PluginManager );

	std::optional<QLibrary*> library{
		new QLibrary{ string::toqstring( libraryName ), this } };

	if ( !library.has_value() ) { return; }

	QFunctionPointer fPtr{ nullptr };

	// Resolve the functions and hold them to function objects.
	fPtr = library.value()->resolve( IDriver::Init );
	InitCB init_fnc{ reinterpret_cast<InitCB>( fPtr ) };

	fPtr = library.value()->resolve( IDriver::DrName );
	DriverNameCB driverNameGlobal_fnc{ reinterpret_cast<DriverNameCB>( fPtr ) };

	fPtr = library.value()->resolve( IDriver::DrDesc );
	DriverDescCB driverDescGlobal_fnc{ reinterpret_cast<DriverDescCB>( fPtr ) };

	// Don't crash and burn if resolve failed.
	if ( !init_fnc || !driverNameGlobal_fnc || !driverDescGlobal_fnc )
	{
		return;
	}

	// Pass the objects to function so it can execute them
	d->registerPlugin( driverNameGlobal_fnc,
			   driverDescGlobal_fnc,
			   std::bind( init_fnc, this ) );
}

std::uint16_t PluginManager::pluginsCounter() { return g_pluginsNumber; }
