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

#include "scanelfdriver.hpp"

#include <qchar.h>    // for operator==, QChar
#include <qdebug.h>
#include <qfile.h>
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qnamespace.h>	   // for UniqueConnection
#include <qpluginloader.h>

#include <cstdint>    // for uint16_t
#include <cstring>

// TODO When this plugin (and others) are installed, this path won't work
#include "../../ConnectVerifier/connectverifier.hpp"	// for ConnectVerifier
#include "../../Helper/string.hpp"
#include "../interface/genericdriver.hpp"    // for Driver
#include "../interface/idriver.hpp"	     // for StopIndex
#include "../interface/pluginmanager.hpp"

class QObject;	  // lines 12-12

const char g_spaceChar{ ' ' };

constexpr char const* g_program{ "scanelf" };
constexpr char const* g_defaultArguments{ "-qRys + /lib64/" };

ScanelfDriver::ScanelfDriver( std::optional<QObject*> parent )
	: GenericDriver{ g_program, g_defaultArguments, parent.value_or( nullptr ) }
{
	updateStopIndexSlot();

	ConnectVerifier v;

	v = connect( this,
		     &GenericDriver::stopIndexUpdated,
		     this,
		     &ScanelfDriver::updateStopIndexSlot,
		     Qt::UniqueConnection );
}

ScanelfDriver::~ScanelfDriver() = default;

void ScanelfDriver::updateStopIndexSlot()
{
	std::string_view args{ string::join_string_list( invocation() ) };

	for ( uint16_t i = 0; i < static_cast<uint16_t>( args.size() ); i++ )
	{
		const char stopChar = args.at( i );

		const int symbolSize{ static_cast<int>( symbolName().size() ) };

		/*
		 * '+' or '-' are considered stopStrings for scanelf's arguments but
		 * '-' needs extra care; It can appear not only before the symbol's
		 * name but to other arguments as well (ie -qRs.. etc).
		 *
		 * That's why we need to match the '-' sign that sits exactly before
		 * the symbol's name in the arguments list.
		 */
		std::string_view sub{ args.substr( i, symbolSize ) };

		if ( stopChar == '+' || ( stopChar == '-' && ( args.find( sub, i ) ) ) )
		{
			setStopIndexSlot( StopIndex::makeStopIndex( i, &stopChar ) );
		}
	}
}

IDriver* init( QObject* parent ) { return new ScanelfDriver{ parent }; }

const char* driverNameGlobal()
{
	const size_t size = std::strlen( g_program );

	char* ptr = new char[size + 1];
	std::strcpy( ptr, g_program );

	return ptr;
}

const char* driverDescGlobal()
{
	std::unique_ptr<QProcess> pr{ std::make_unique<QProcess>() };

	const QStringList args{ "--help" };
	pr->start( g_program, QStringList{ g_defaultArguments } );
	pr->waitForFinished( -1 );

	QByteArray  result{ pr->readAllStandardOutput() };
	QStringList lines{ QString::fromLocal8Bit( result ).split( '\n' ) };
	// result = lines.at( 0 ).toLocal8Bit();

	const size_t size = std::strlen( qPrintable( result ) );

	char* pc = new char[size + 1];
	std::strcpy( pc, result );

	return pc;
}

const char* argumentsGlobal()
{
	const size_t size = std::strlen( g_defaultArguments );

	char* ptr = new char[size + 1];
	std::strcpy( ptr, g_defaultArguments );

	return ptr;
}
