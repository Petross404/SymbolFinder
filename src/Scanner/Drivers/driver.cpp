// <one line to give the program's name and a brief idea of what it does.>
// SPDX-FileCopyrightText: 2022 Πέτρος Σιλιγκούνας <petross404@gmail.com>
// SPDX-License-Identifier: GPL-3.0-or-later

#include "driver.hpp"

#include <qdebug.h>

Driver::Driver( QObject* parent )
	: IDriver{ parent }
{
	init();
}

Driver::Driver( QString program, QStringList defArgList, QObject* parent )
	: IDriver{ parent }
	, m_program{ std::move( program ) }
	, m_defArgList{ std::move( defArgList ) }
	, m_effectiveArgList{ m_defArgList }
{
	init();
}

void Driver::init() { emit driverInitialized( driverName() ); }

Driver::~Driver() = default;

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
		m_symbol = symbolName;
		emit stopIndexUpdated();
	}
}

QString Driver::symbolName() const { return m_symbol; }

void Driver::exec()
{
	start( driverName(), invocation() );

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

StopIndex Driver::stopIndex() const { return m_stopIndex; }
