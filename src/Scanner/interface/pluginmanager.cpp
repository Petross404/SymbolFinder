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

#include <functional>

using CreateCallBack	 = IDriver* (*)( QObject* parent );
using DriverNameCallback = QString ( * )();
using ArgumentsCallBack	 = QStringList ( * )();

constexpr int NoPlugin = -1;

PluginManager::PluginManager( QObject* parent )
	: QObject{ parent }
	, DriverFactory{}
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

	// ${PREFIX}/lib64/scanner/plugins/*

	QDir pluginDir{ appDir };

	// qDebug() << QCoreApplication::libraryPaths();
	if ( isRunningInRepo )
	{
		if ( !pluginDir.cd( "src/Scanner/plugins" ) )
		{
			m_pluginCount = NoPlugin;
			return;
		}
	}
	else
	{
		QDir root = QDir::root();
		root.cd( "usr/lib64/Scanner/plugins" );

		if ( !pluginDir.cd( root.absolutePath() ) )
		{
			m_pluginCount = NoPlugin;
			return;
		}
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

			QLibrary* library{
				new QLibrary{ fileInfo.absoluteFilePath(), this } };

			CreateCallBack createDriverFn{ reinterpret_cast<CreateCallBack>(
				library->resolve( "create" ) ) };
			DriverNameCallback driverNameFn{ reinterpret_cast<DriverNameCallback>(
				library->resolve( "driverNameStatic" ) ) };
			ArgumentsCallBack argumentsFn =
				(ArgumentsCallBack)library->resolve(
					"argumentsStatic" );

			qDebug() << library->errorString();

			if ( createDriverFn && driverNameFn && argumentsFn )
			{
				const QString driverName{ driverNameFn() };
				qDebug() << "driverNane" << driverName;

				// Register the plugin, it will be retrieved later to be instantiated.
				registerPlugin( driverName,
						std::bind( createDriverFn, this ) );

				m_pluginCount++;
			}
		}
		qDebug() << "mpluginCount " << m_pluginCount;
	}
}

int PluginManager::pluginsNumber() const { return m_pluginCount; }

std::vector<PluginDriver> PluginManager::registeredPlugins()
{
	plugins_table_t map{ DriverFactory::registeredPlugins() };
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
	registerPlugin( driverName, createCb );
}

void PluginManager::unregisterIDriver( const QString& driverName )
{
	unregisterPlugin( driverName );
}

IDriver* PluginManager::driver( const QString& driverName )
{
	return createDriver( driverName, this );
}
