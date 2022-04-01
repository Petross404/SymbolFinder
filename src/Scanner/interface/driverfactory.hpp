// <one line to give the program's name and a brief idea of what it does.>
// SPDX-FileCopyrightText: 2022 Πέτρος Σιλιγκούνας <petross404@gmail.com>
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef DRIVERFACTORY_H
#define DRIVERFACTORY_H

#include <qobject.h>

#include <map>

#include "driver.hpp"

typedef Process::IDriver* ( *CreateCallback )();

/**
 * @todo write docs
 */
class DriverFactory: public QObject
{
	Q_OBJECT

public:
	DriverFactory( QObject* parent = nullptr );

	static void registerDriver( const QString& name, CreateCallback cb );
	static void unregisterDriver( const QString& name );

	static Process::IDriver* createDriver( const QString& name );

private:
	static std::map<QString, CreateCallback> tableOfDrivers;
};

#endif	  // DRIVERFACTORY_H
