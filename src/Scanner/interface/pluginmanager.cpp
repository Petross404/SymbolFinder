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

#include <qapplication.h>
#include <qdebug.h>
#include <qdir.h>
#include <qlibrary.h>
#include <qlibraryinfo.h>
#include <qregularexpression.h>

#include <functional>

#include "idriver.hpp"

using CreateCB	   = IDriver* (*)( QObject* parent );
using DriverNameCB = QString ( * )();
using ArgumentsCB  = QStringList ( * )();

constexpr int NoPlugin = 0;

PluginManager::PluginManager( QObject* parent )
	: QObject{ parent }
{
	look();
}

PluginManager::~PluginManager() = default;

void PluginManager::look()
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

	QString location{ QLibraryInfo::location( QLibraryInfo::PluginsPath ) + "scanner" };

	QDir pluginDir;

	if ( isRunningInRepo )
	{
		QCoreApplication::addLibraryPath( "src/Scanner/plugins" );
		QCoreApplication::removeLibraryPath(appDir.absolutePath());
		QCoreApplication::removeLibraryPath(QLibraryInfo::location( QLibraryInfo::PluginsPath ));

		if ( auto path{appDir.absolutePath() + "/src/Scanner/plugins" }; !pluginDir.cd( path ) )
		{
			qDebug() << "cd error for plugin dir";
			return;
		}
	else
	{
		QCoreApplication::addLibraryPath( location );

		for ( auto pluginPath : QCoreApplication::libraryPaths() )
			if ( !pluginDir.cd( pluginPath ) )
			{
				qDebug() << "cd error for plugin dir";
				return;
			}
		}
	}

	qDebug() << QCoreApplication::libraryPaths();

	/*
	 * Read the contents of the directory and keep only the libraries
	 * and those who aren't symlinks.
	 */
	QStringList pluginNameList;
	for ( const QFileInfo& fileInfo : pluginDir.entryInfoList( QDir::Filter::Files ) )
	{
		if ( !QLibrary::isLibrary( fileInfo.absoluteFilePath() )
#ifdef Q_OS_UNIX
		     && fileInfo.isSymbolicLink()
#elif Q_OS_WIN
		     && fileInfo.isShortcut()
#endif
		)
		{
			continue;
		}

		qDebug() << "fileInfo" << fileInfo.fileName();
		pluginNameList << fileInfo.fileName();

		QString libName;
		if ( isRunningInRepo )
		{
			QRegularExpression re{ "([^.]+)" };
			qDebug() << fileInfo.completeSuffix() << fileInfo.baseName();
			libName = fileInfo.absoluteFilePath().remove(
				fileInfo.completeSuffix() );
			libName.remove( '.' );
		}
		else
		{
			libName = fileInfo.baseName();
		}

		qDebug() << "LibName: " << libName;

		QLibrary* library{ new QLibrary{ libName, this } };

		auto createDriverFn{ (CreateCB)library->resolve( "create" ) };
		auto driverNameFn{
			(DriverNameCB)library->resolve( "driverNameStatic" ) };
		auto argumentsFn{
			(ArgumentsCB)library->resolve( "argumentsStatic" ) };

		/*
		 * At this point the library should be loaded already;
		 * Make sure it is and if not, print the error.
		 */
		if ( !library->isLoaded() )
		{
			qDebug() << "Library error : " << library->errorString();
		}

		if ( createDriverFn && driverNameFn && argumentsFn )
		{
			const QString driverName{ driverNameFn() };

			// Register the plugin, it will be retrieved later to be instantiated.
			registerPlugin_impl( driverName,
					     std::bind( createDriverFn, this ) );

			m_pluginCount++;
		}
		qDebug() << "mpluginCount " << m_pluginCount;
	}
}

int PluginManager::pluginsNumber() const { return m_pluginCount; }

std::vector<PluginDriver> PluginManager::registeredPlugins()
{
	plugins_table_t map{ registeredPlugins_impl() };

	plugins_table_t::const_iterator it{ map.begin() };

	for ( int i = 0; i < map.size(); i++ )
	{
		m_vecOfDrivers.at( i ).driverName = it->first;
		it++;
	}
	return m_vecOfDrivers;
}

void PluginManager::registerIDriver( const QString& driverName, callback_t createCb )
{
	registerPlugin_impl( driverName, std::move( createCb ) );
}

void PluginManager::unregisterIDriver( const QString& driverName )
{
	unregisterPlugin_impl( driverName );
}

IDriver* PluginManager::driver( const QString& driverName )
{
	return createDriver_impl( driverName, this );
}

int PluginManager::indexOfLibSuffix( const QString& libName )
{
	int index = 0;
	for ( const QChar c : libName )
	{
		if ( c == '.' ) { index++; }
	}

	return index;
}
