// <one line to give the program's name and a brief idea of what it does.>
// SPDX-FileCopyrightText: 2022 Πέτρος Σιλιγκούνας <petross404@gmail.com>
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef DRIVERFACTORY_H
#define DRIVERFACTORY_H

#include <qstring.h>

#include <functional>
#include <map>
#include <utility>

class QObject;
class QPluginLoader;
class IDriver;

//! Alias for `std::function<IDriver* (*)(QObject*)>`
using callback_t = std::function<IDriver*( QObject* )>;

//! Alias for `std::map<QString, callback_t>`
using plugins_table_t = std::map<QString, callback_t>;

//! Alias for `std::pair<QString, callback_t>`
using plugin_pair_t = std::pair<QString, callback_t>;

/*!
 * Implements the factory pattern for the `IDriver` plugins.
 */
class DriverFactory
{
protected:
	/*! Constructor */
	DriverFactory();

	/*! Destructor */
	~DriverFactory();

	/*!
	 * Register the driver
	 * \param name is the driver's name
	 * \param cb is the driver's callback to create an instance.
	 */
	void registerPlugin_impl( const QString& name, callback_t cb );

	/*!
	 * Uregister the specified driver.
	 * \param name is the driver to be unregistered.
	 */
	void unregisterPlugin_impl( const QString& name );

	/*!
	 * Get the table of the registered drivers.
	 */
	plugins_table_t registeredPlugins_impl() const;

	/*!
	 */
	IDriver* createDriver_impl( const QString& name, QObject* parent );

private:
	plugins_table_t tableOfDrivers{};
};

#endif	  // DRIVERFACTORY_H
