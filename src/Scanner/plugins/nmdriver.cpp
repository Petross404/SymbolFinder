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

#include "nmdriver.hpp"

#include <qdebug.h>
#include <qfile.h>
#include <qjsondocument.h>
#include <qnamespace.h>	   // for UniqueConnection
#include <stdint.h>	   // for uint16_t

#include <QJsonObject>
#include <functional>

#include "../../ConnectVerifier/connectverifier.hpp"	// for ConnectVerifier
#include "../interface/genericdriver.hpp"		// for Driver
#include "../interface/idriver.hpp"			// for StopIndex
#include "../interface/pluginmanager.hpp"

class QObject;	  // lines 12-12

constexpr char	      g_spaceChar{ ' ' };
constexpr char const* g_program{ "nm" };
constexpr char const* g_defArgs{ "-Dn -o --defined-only /lib/* /usr/lib64/* 2> "
				 "/dev/null | grep '\b\b'" };

NmDriver::NmDriver( std::optional<QObject*> parent )
	: GenericDriver{ g_program, g_defArgs, parent.value_or( nullptr ) }
{
	updateStopIndexSlot();

	ConnectVerifier v;

	v = connect( this,
		     &GenericDriver::stopIndexUpdated,
		     this,
		     &NmDriver::updateStopIndexSlot,
		     Qt::UniqueConnection );
}

NmDriver::~NmDriver() = default;

void NmDriver::updateStopIndexSlot()
{
	std::string_view s{ "\b" };

	std::list<std::string_view> strArgs{ invocation() };

	std::list<std::string_view>::iterator it{ std::ranges::find( strArgs, s ) };

	if ( int index = std::distance( strArgs.begin(), it ); index )
	{
		const StopIndex si{ StopIndex::makeStopIndex( (uint32_t)index, s ) };
		setStopIndexSlot( std::cref( si ) );
	}
	else { emit stopIndexUpdatingFailed(); }
}

IDriver* init( QObject* parent ) { return new NmDriver{ parent }; }

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
