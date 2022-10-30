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

#include "genericdriver.hpp"

#include <fmt/color.h>
#include <fmt/core.h>
#include <qbytearray.h>	   // for QByteArray
#include <qdebug.h>	   // for QDebug
#include <qlist.h>	   // for QList
#include <qprocess.h>	   // for QProcess::NotRunning, QPr...

#include <iostream>
#include <utility>    // for move

#include "../../Helper/string.hpp"
#include "idriver.hpp"	  // for StopIndex, IDriver

class QObject;

GenericDriver::GenericDriver( std::string_view	      program,
			      std::string_view	      defArgList,
			      std::optional<QObject*> parent )
	: IDriver{ program, parent }
	, m_defArgList{ defArgList }
	, m_effectiveArgList{ m_defArgList }
	, m_stopIndex{ std::make_optional<StopIndex>() }
{
	setProgram( string::toqstring( program ) );
}

GenericDriver::~GenericDriver() = default;

std::list<std::string_view> GenericDriver::defaultInvocation() const
{
	return m_defArgList;
}

std::string GenericDriver::driverName() const
{
	const std::string prog{ string::tostring( program() ) };

	if ( prog.empty() )
	{
		// TODO The program name can't be empty.
	}

	return prog;
}

bool GenericDriver::isSymbolInArgs() const
{
	std::list<std::string_view>::const_iterator it{
		std::find( m_effectiveArgList.begin(), m_effectiveArgList.end(), m_symbol ) };
	return it != m_effectiveArgList.end();
}

bool GenericDriver::setInvocation( std::string_view args )
{
	const std::list<std::string_view> argList{ string::split_string_list( args, " " ) };

	if ( string::comparelists( m_effectiveArgList, argList ) )
	{
		m_effectiveArgList = argList;
		emit stopIndexUpdated();
		return true;
	}

	return false;
}

void GenericDriver::setSymbolName( std::string_view newSymbolName )
{
	if ( m_symbol != newSymbolName )
	{
		// Keep this for later.
		std::string_view oldSymbolName{ symbolName() };

		m_symbol = newSymbolName;

		if ( oldSymbolName.size() != symbolName().size() )
		{
			emit stopIndexUpdated();
			emit symbolSizeChanged( symbolName().size() );
		}
	}
}

std::string GenericDriver::symbolName() const { return m_symbol; }

bool GenericDriver::canDriverQuit() const
{
	return state() != QProcess::ProcessState::Running
	       || state() != QProcess::ProcessState::Starting;
}

void GenericDriver::exec()
{
	const QString	  dName{ string::toqstring( driverName() ) };
	const QStringList args{ string::toqstring( *invocation().begin() ),
				string::toqstring( *invocation().end() ) };

	// This actually starts the QProcess of the driver.
	start( dName, args );
	waitForStarted( 1000 );

	std::string message;

	switch ( state() )
	{
		case Running:
		{
			/*
			 * The main window shouldn't allow this case to happen,
			 * but one can never be 100% safe.
			 */
			if ( symbolName().empty() ) [[unlikely]]
			{
				message =
					std::string_view{ "How did this happen?" };
				break;
			}
			fmt::print( fmt::emphasis::underline, "{:d}", processId() );
		}
		case Starting:
		{
			message = fmt::format( "Starting...{}", driverName() );
			break;
		}
		case NotRunning:
		default:
		{
			message = fmt::format(
				"An error happened, when {} tried to start",
				driverName() );
			break;
		}
	}

	fmt::print( fmt::emphasis::bold | fg( fmt::color::red ), message );
}

std::list<std::string_view> GenericDriver::invocation() const
{
	return m_effectiveArgList;
}

void GenericDriver::setStopIndexSlot( const StopIndex sIndex )
{
	m_stopIndex.emplace( sIndex );
}

void GenericDriver::setDriverName( std::string_view name )
{
	setProgram( QString::fromLocal8Bit( name.data(), name.size() ) );
}

void GenericDriver::setDefaultInvocation( std::string_view argList )
{
	m_defArgList = string::split_string_list( argList, " " );
}

StopIndex GenericDriver::stopIndex() const
{
	StopIndex si;
	try
	{
		si = m_stopIndex.value();
		return si;
	} catch ( const std::bad_optional_access& e )
	{
		std::cerr << e.what() << '\n';
	}
	return si;
}

void GenericDriver::deleteDriver() const { delete this; }
