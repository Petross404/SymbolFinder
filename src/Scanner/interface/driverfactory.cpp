// <one line to give the program's name and a brief idea of what it does.>
// SPDX-FileCopyrightText: 2022 Πέτρος Σιλιγκούνας <petross404@gmail.com>
// SPDX-License-Identifier: GPL-3.0-or-later

#include "driverfactory.hpp"

std::map<QString, CreateCallback> DriverFactory::tableOfDrivers;

DriverFactory::DriverFactory( QObject* parent )
	: QObject{ parent }
{}

Process::IDriver* DriverFactory::createDriver( const QString& name )
{
	std::map<QString, CreateCallback>::iterator it{ tableOfDrivers.find( name ) };

	if ( it != tableOfDrivers.end() ) { return ( it->second )(); }

	return nullptr;
}

void DriverFactory::registerDriver( const QString& name, CreateCallback cb )
{
	tableOfDrivers[name] = cb;
}

void DriverFactory::unregisterDriver( const QString& name )
{
	tableOfDrivers.erase( name );
}
