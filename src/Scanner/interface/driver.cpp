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

#include "driver.hpp"

#include <qbytearray.h>	   // for QByteArray
#include <qdebug.h>	   // for QDebug
#include <qlist.h>	   // for QList
#include <qprocess.h>	   // for QProcess::NotRunning, QPr...

#include <utility>    // for move

#include "idriver.hpp"	  // for StopIndex, IDriver
class QObject;

Driver::Driver( QObject* parent )
	: QProcess{ parent }
{
	init();
}

Driver::Driver( QString program, QStringList defArgList, QObject* parent )
	: QProcess{ parent }
	, m_program{ std::move( program ) }
	, m_defArgList{ std::move( defArgList ) }
	, m_effectiveArgList{ m_defArgList }
{
	init();
}

void Driver::init() { emit driverInitialized( m_program ); }

Driver::~Driver() = default;

IDriver* Driver::create( QObject* parent )
{
	Q_UNUSED( parent )
	qDebug() << "Create in Driver";

	return this;
}

QStringList Driver::defaultInvocation() const { return m_defArgList; }

QString Driver::driverName() const { return m_program; }

bool Driver::isSymbolInArgs() const
{
	return m_effectiveArgList.contains( m_symbol );
}

bool Driver::setInvocation( const QStringList& args )
{
	if ( m_effectiveArgList != args )
	{
		m_effectiveArgList = args;
		emit stopIndexUpdated();
		return true;
	}
	return false;
}

void Driver::setSymbolName( const QString& symbolName )
{
	if ( m_symbol != symbolName )
	{
		// Keep this for later.
		bool sizeChanged = m_symbol.size() != symbolName.size();

		m_symbol = symbolName;

		if ( sizeChanged )
		{
			emit stopIndexUpdated();
			emit symbolSizeChanged( symbolName.size() );
		}
	}
}

QString Driver::symbolName() const { return m_symbol; }

bool Driver::canDriverQuit() const
{
	return state() == QProcess::ProcessState::Running
	       || state() == QProcess::ProcessState::Starting;
}

void Driver::exec()
{
	QProcess::start( driverName(), invocation() );

	QString message;
	switch ( state() )
	{
		case Running:
		{
			/*
			 * The main window shouldn't allow this case to happen,
			 * but one can never be 100% safe.
			 */
			if ( Q_UNLIKELY( symbolName().isEmpty() ) )
			{
				message = "WTF how did this happen?";
				break;
			}
			qDebug() << processId();
		}
		case Starting:
		{
			message = QString{ "Starting..." + symbolName() };
			break;
		}
		case NotRunning:
		default:
		{
			message = QString{ "An error happened, when "
					   + driverName() + " tried to start" };
			break;
		}
	}
	qDebug() << tr( message.toLatin1() );
}

QStringList Driver::invocation() const { return m_effectiveArgList; }

void Driver::setStopIndexSlot( StopIndex sIndex )
{
	m_stopIndex = std::move( sIndex );
}

void Driver::setDriverName( const QString& name ) { m_program = name; }

void Driver::setDefaultInvocation( const QStringList& argList )
{
	m_defArgList = argList;
}

StopIndex Driver::stopIndex() const { return m_stopIndex; }
