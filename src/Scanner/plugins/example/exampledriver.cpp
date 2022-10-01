/*
 * <one line to give the library's name and an idea of what it does.>
 * Copyright (C) 2022  <copyright holder> <email>
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

#include "exampledriver.hpp"

#include <qdebug.h>
#include <qfile.h>
#include <qjsondocument.h>
#include <qnamespace.h>	   // for UniqueConnection
#include <stdint.h>	   // for uint16_t

#include <QJsonObject>
#include <functional>

#include "../../ConnectVerifier/connectverifier.hpp"	// for ConnectVerifier
#include "../interface/driver.hpp"			// for Driver
#include "../interface/idriver.hpp"			// for StopIndex
#include "../interface/plugiexampleanager.hpp"

class QObject;	  // lines 12-12

constexpr char	      g_spaceChar{ ' ' };
constexpr char const* g_program{ "example" };
constexpr char const* g_defArgs{ "--arguments" };

ExampleDriver::ExampleDriver( std::optional<QObject*> parent )
	: GenericDriver{ QString::fromLocal8Bit( g_program ),
			 QStringList{ g_defArgs },
			 parent.value_or( nullptr ) }
{
	updateStopIndexSlot();

	ConnectVerifier v;

	v = connect( this,
		     &GenericDriver::stopIndexUpdated,
		     this,
		     &ExampleDriver::updateStopIndexSlot,
		     Qt::UniqueConnection );
}

ExampleDriver::~ExampleDriver() = default;

void ExampleDriver::updateStopIndexSlot()
{
	// After this string, your symbol name exists.
	const QString s{ /* string */ };

	QString strArgs{ invocation().join( g_spaceChar ) };

	int i = strArgs.indexOf( s );

	if ( i > 0 )
	{
		setStopIndexSlot( StopIndex{ static_cast<uint32_t>( i ), s } );
	}
	else { emit stopIndexUpdatingFailed(); }
}

IDriver* create( QObject* parent ) { return new ExampleDriver{ parent }; }

const char* driverNameGlobal()
{
	const size_t size = strlen( g_program );

	char* p = new char[size + 1];
	strcpy( p, g_program );

	return p;
}

const char* driverDescGlobal()
{
	std::unique_ptr<QProcess> pr{ std::make_unique<QProcess>() };

	const QStringList args{ "--help" };
	pr->start( g_program, args );
	pr->waitForFinished( -1 );

	QByteArray  result{ pr->readAllStandardOutput() };
	QStringList lines{ QString::fromLocal8Bit( result ).split( '\n' ) };

	const size_t size = strlen( qPrintable( result ) );

	char* pc = new char[size + 1];
	strcpy( pc, result );

	return pc;
}

const char* argumentsGlobal()
{
	const size_t size = strlen( g_defArgs );

	char* p = new char[size + 1];
	strcpy( p, g_defArgs );

	return p;
}
