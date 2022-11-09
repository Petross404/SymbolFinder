// <one line to give the program's name and a brief idea of what it does.>
// SPDX-FileCopyrightText: 2022 Πέτρος Σιλιγκούνας <petross404@gmail.com>
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef DRIVERFACTORY_H
#define DRIVERFACTORY_H

#include <qcoreapplication.h>
#include <qstring.h>

#include <functional>
#include <map>
#include <optional>
#include <string>
#include <utility>

// #include <tl/expected.hpp>

#include "pluginmanageraliases.hpp"

class PluginManager;

/*!
 * Implements the factory pattern for the `IDriver` plugins.
 */
class PluginManagerPrivate
{
	Q_DISABLE_COPY_MOVE( PluginManagerPrivate )
public:
	PluginManagerPrivate( PluginManager* pm );

	/*!
	 * Destructor
	 */
	~PluginManagerPrivate() = default;

	/*!
	 * Register the driver.
	 * \param driverNameGlobal is the driver's name callback
	 * \param driverDescGlobal is the driver's description callback
	 * \param initcb is the driver's callback to create an instance.
	 */
	void registerPlugin( const DriverNameCB& driverNameGlobal,
			     const DriverDescCB& driverDescGlobal,
			     const InitFCB&	 initcb );

	/*!
	 * Uregister the specified driver.
	 * \param name is the driver to be unregistered.
	 */
	void unregisterPlugin( std::string_view name );

	/*!
	 * Get the table of the registered drivers.
	 */
	[[nodiscard]] PluginsTable registeredPlugins() const;

	/*!
	 * Initialize the plugin.
	 * \param name of the plugin to initialize
	 * \param parent parent for the plugin (inherits QObject)
	 * \return Pointer to the instance.
	 */
	[[nodiscard]] std::optional<IDriver*> initPlugin( std::string_view name,
							  QObject*	   parent );

	[[nodiscard]] const PluginDescVec pluginNames() const;

protected:
	PluginManager* const q_ptr;

private:
	Q_DECLARE_PUBLIC( PluginManager )

	PluginsTable m_tableOfDrivers{}; /*!< Map that holds a PluginDesc and a callback*/
};

#endif	  // DRIVERFACTORY_H
