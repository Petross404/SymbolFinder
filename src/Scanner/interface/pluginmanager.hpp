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

#include <qdir.h>
#include <qobject.h>

#include <gsl/pointers>
#include <optional>

#include "pluginmanageraliases.hpp"

template<typename T> using not_null_owner = gsl::strict_not_null<gsl::owner<T>>;

class PluginManagerPrivate;

/*!
 * `PluginManager` is a class that tries to contain the needed funtionality
 * for the plugins to be discovered, registered and provided to the software.
 */
class PluginManager: public QObject
{
	Q_OBJECT
	Q_DISABLE_COPY_MOVE( PluginManager )

public:
	/*!
	 * Constructor for `PluginManager`
	 * \param parent is a `QObject*` that is the parent of this object.
	 */
	explicit PluginManager( QObject* parent );

	/*!
	 *Destructor
	 */
	~PluginManager() override;

	/*!
	 * Number of plugins that are found.
	 * \return the number of plugins that are found.
	 */
	[[nodiscard]] std::uint16_t pluginsNumber() const;

	/*!
	 * Remove the following driver if existant
	 * \param driverName is the driver that needs to be removed.
	 */
	void unregisterIDriver( std::string_view driverName );

	/*!
	 * Find the registered constructor for the driver name and execute it.
	 * \param driverName is the driver's name to look for.
	 * \return Not-Null Pointer to newly created `IDriver` plugin.
	 */
	std::optional<IDriver*> createDriver( std::string_view driverName );

	/*!
	 * Return the table that contains the names of the driver
	 * and their respective callbacks.
	 * \return the driver's table.
	 */
	[[nodiscard]] const PluginsTable registeredPlugins() const;

	[[nodiscard]] const std::vector<PluginDesc> pluginsDescription() const;

	[[nodiscard]] std::optional<IDriver*> chooseDriver( std::string_view driverName );

	[[nodiscard]] std::optional<IDriver*> currentDriver() const;

	static std::uint16_t pluginsCounter();

public slots:
	/*!
	 * Set the `IDriver` pointer to the current plugin.
	 * \param driver is the plugin wrapped in `std::optional` type.
	 */
	void setCurrentDriver( std::optional<IDriver*> driver );

signals:
	/*!
	 * Inform any listeners that a new plugin was initialized.
	 * \param pdriver is a pointer to the plugin that was initialized.
	 */
	void driverInitialized( IDriver* const pdriver );

	/*!
	 * Inform any listeners that the number of registered plugins changed.
	 * \param size is the size of the table of drivers (= counter of plugins).
	 */
	void tableOfDriversAltered( const std::size_t size );

protected:
	PluginManagerPrivate* const d_ptr; /*!< Smart pointer to private implemantation */

private:
	Q_DECLARE_PRIVATE( PluginManager )

	std::optional<IDriver*> m_currentDriver; /*!< Optional pointer to current driver */
	std::uint16_t m_pluginCount{ 0 }; /*!< Counter of plugin number in the system */

	/*!
	 * Lookup for plugins at pre-defined locations.
	 */
	void lookup();

	/*!
	 * Discover plugins in the specified directory.
	 * \param isRunningInRepo determines if this app is still being developed.
	 * \param pluginDir is the directory that will be searched for plugins.
	 */
	void findPlugins( bool isRunningInRepo, const QDir& pluginDir );

	/*!
	 * Resolve the needed functions for the specified library and if the
	 * value isn't nullptr, register the plugin.
	 * \param libraryName is the library to load.
	 */
	void preparePlugin( std::string_view libraryName );
};

#endif	  // PLUGINMANAGER_H
