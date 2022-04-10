// <one line to give the program's name and a brief idea of what it does.>
// SPDX-FileCopyrightText: 2022 Πέτρος Σιλιγκούνας <petross404@gmail.com>
// SPDX-License-Identifier: GPL-3.0-or-later

#include "driverfactory.hpp"

#include <qobject.h>

#include <exception>
#include <iostream>

#include "idriver.hpp"

DriverFactory::DriverFactory()	= default;
DriverFactory::~DriverFactory() = default;

IDriver* DriverFactory::createDriver( const QString& name, QObject* parent )
{
	plugins_table_t::const_iterator it{ tableOfDrivers.find( name ) };

	if ( it != tableOfDrivers.end() )
	{
		// std::map<QString, callback_t>, the callback is second.
		IDriver* d{ ( it->second )( parent ) };

		if ( d == nullptr )
		{
			const char* msg{ QObject::tr( "Driver is nullptr" ).toLatin1() };
			throw std::runtime_error( msg );
		}

		return d;
	}

	return nullptr;
}

void DriverFactory::registerPlugin( const QString& name, callback_t cb )
{
	// Make sure the driver name doesn't exist already with another cb
	plugins_table_t::const_iterator it{ DriverFactory::tableOfDrivers.find( name ) };

	if ( it != tableOfDrivers.end() )
	{
		if ( it->second.target_type() != cb.target_type() )
		{
			tableOfDrivers.at( name ) = cb;
		}
	}

	tableOfDrivers.insert( { name, cb } );
}

void DriverFactory::unregisterPlugin( const QString& name )
{
	tableOfDrivers.erase( name );
}

std::map<QString, callback_t> DriverFactory::registeredPlugins() const
{
	return tableOfDrivers;
}
