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

#include "../../ConnectVerifier/connectverifier.hpp"	// for ConnectVerifier
#include "../interface/driver.hpp"			// for Driver
#include "../interface/idriver.hpp"			// for StopIndex

class QObject;	  // lines 12-12

const QChar	  spaceChar{ ' ' };
const QString	  g_program{ "nm" };
const QStringList g_defaultArguments{
	"-Dn -o --defined-only /lib/* /usr/lib64/* 2> /dev/null | grep "
	"'\b\b'" };

NmDriver::NmDriver( QObject* parent )
	: Driver{ g_program, g_defaultArguments, parent }
	, m_jsonFile{ "nmplugin.json", this }
{
	// updateStopIndexSlot();

	qDebug() << "I am nmdriver's ctor";

	ConnectVerifier v;
	v = connect( this,
		     &Driver::stopIndexUpdated,
		     this,
		     &NmDriver::updateStopIndexSlot,
		     Qt::UniqueConnection );
}

NmDriver::~NmDriver() = default;

void NmDriver::updateStopIndexSlot()
{
	std::exit( -1 );
	const QString s{ "\b" };

	QString strArgs{ m_effectiveArgList.join( spaceChar ) };

	int i = strArgs.indexOf( s );
	qDebug() << "index of" << s << i;

	if ( i > 0 )
	{
		setStopIndexSlot( StopIndex{ static_cast<uint32_t>( i ), s } );
	}
	else
	{
		emit stopIndexUpdatingFailed();
	}
}

IDriver* create( QObject* parent ) { return new NmDriver{ parent }; }

QString NmDriver::driverNameStatic() { return g_program; }

QStringList NmDriver::argumentsStatic() { return g_defaultArguments; }
