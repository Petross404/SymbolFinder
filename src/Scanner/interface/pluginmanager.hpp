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

#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include <qobject.h>

#include "driverfactory.hpp"
#include "pluginpair.hpp"

/*!
 * `PluginManager` is a class that tries to contain the needed funtionality
 * for the plugins to be discovered, registered and provided to the software.
 */
class PluginManager
	: public QObject
	, public DriverFactory
{
	Q_OBJECT

public:
	PluginManager( QObject* parent );
	~PluginManager() override;

	/*!
	 * Lookup for plugins at pre-defined locations.
	 */
	void look();

	/*!
	 * Number of plugins that are found.
	 * \return the number of plugins that are found.
	 */
	int pluginsNumber() const;

	/*!
	 * Register the current driver.
	 * \param driverName is the name describes the driver.
	 * \param createCb is the callback to be retrieved and create
	 * the driver.
	 */
	void registerIDriver( const QString& driverName, callback_t createCb );

	/*!
	 * Remove the following driver if existant
	 * \param driverName is the driver that needs to be removed.
	 */
	void unregisterIDriver( const QString& driverName );

	IDriver* driver( const QString& driverName );

	/*!
	 * Return the table that contains the names of the driver
	 * and their respective callbacks.
	 * \return the driver's table.
	 */
	std::vector<PluginDriver> registeredPlugins();

private:
	int m_pluginCount;

	std::vector<PluginDriver> m_vecOfDrivers;
};

#endif	  // PLUGINMANAGER_H
