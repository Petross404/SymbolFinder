// <one line to give the program's name and a brief idea of what it does.>
// SPDX-FileCopyrightText: 2022 Πέτρος Σιλιγκούνας <petross404@gmail.com>
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef DRIVERFACTORY_H
#define DRIVERFACTORY_H

#include <functional>
#include <map>

#include "driver.hpp"

class QObject;

//! Alias for `std::function<IDriver*> (IDriver::*)(QObject*)>`
using CreateCallback = std::function<IDriver* (IDriver::*)( QObject* )>;

/*!
 * Implements the factory pattern for `IDriver` plugins.
 */
class DriverFactory
{
public:
	/*! Constructor */
	DriverFactory();
	/*! Destructor */
	~DriverFactory();

	/*!
	 * Register the driver
	 * \param name is the driver's name
	 * \param cb is the driver's callback to create an instance.
	 */
	void registerDriver( const QString& name, CreateCallback cb );

	/*!
	 * Uregister the specified driver.
	 * \param name is the driver to be unregistered.
	 */
	void unregisterDriver( const QString& name );

	/*!
	 * Get the table of the registered drivers.
	 */
	std::map<QString, CreateCallback> registeredPlugins();

	/*!
	 */
	IDriver* createDriver( const QString& name, QObject* parent );

private:
	std::map<QString, CreateCallback> tableOfDrivers;
};

#endif	  // DRIVERFACTORY_H
