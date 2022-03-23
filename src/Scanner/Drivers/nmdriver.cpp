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
#include <qnamespace.h>	   // for UniqueConnection
#include <stdint.h>	   // for uint16_t

#include "../../ConnectVerifier/connectverifier.hpp"	// for ConnectVerifier
#include "driver.hpp"					// for Driver
#include "idriver.hpp"					// for StopIndex
class QObject;						// lines 12-12

const QString	  NmDriver::m_program{ "nm" };
const QStringList NmDriver::m_defArgList{
	"-Dn -o --defined-only /lib/* /usr/lib64/* 2> /dev/null | grep "
	"'\b\b'" };

QString NmDriver::name() { return NmDriver::m_program; }

QStringList NmDriver::argList() { return NmDriver::m_defArgList; }

NmDriver::NmDriver( QObject* parent )
	: Driver{ NmDriver::m_program, NmDriver::m_defArgList, parent }
{
	updateStopIndexSlot();

	ConnectVerifier v;
	v = connect( this,
		     &Driver::stopIndexUpdated,
		     this,
		     &NmDriver::updateStopIndexSlot,
		     Qt::UniqueConnection );
}

NmDriver::~NmDriver() = default;

QStringList NmDriver::defaultInvocation() const { return m_defArgList; }

void NmDriver::updateStopIndexSlot()
{
	const QString s{ "\b" };
	auto	      i = m_effectiveArgList.join( ' ' ).indexOf( s );
	qDebug() << i;

	if ( i > 0 )
	{
		setStopIndexSlot( StopIndex{ static_cast<uint32_t>( i ), s } );
	}
	else
	{
		emit stopIndexUpdatingFailed();
	}
}
