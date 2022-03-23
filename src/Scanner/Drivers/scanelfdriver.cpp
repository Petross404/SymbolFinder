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

#include <qchar.h>	   // for operator==, QChar
#include <qnamespace.h>	   // for UniqueConnection
#include <stdint.h>	   // for uint16_t

#include "../../ConnectVerifier/connectverifier.hpp"	// for ConnectVerifier
#include "driver.hpp"					// for Driver
#include "idriver.hpp"					// for StopIndex
class QObject;						// lines 12-12

const QString	  ScanelfDriver::m_program{ "scanelf" };
const QStringList ScanelfDriver::m_defArgList{ "-qRys + /usr/lib64/ /lib64/" };

const QString ScanelfDriver::name() { return ScanelfDriver::m_program; }

const QStringList ScanelfDriver::argList()
{
	return ScanelfDriver::m_defArgList;
}

ScanelfDriver::ScanelfDriver( QObject* parent )
	: Driver{ ScanelfDriver::m_program, ScanelfDriver::m_defArgList, parent }
	, m_effectiveArgList{ ScanelfDriver::m_defArgList }
{
	updateStopIndexSlot();

	ConnectVerifier v;
	v = connect( this,
		     &Driver::stopIndexUpdated,
		     this,
		     &ScanelfDriver::updateStopIndexSlot,
		     Qt::UniqueConnection );
}

ScanelfDriver::~ScanelfDriver() = default;

QStringList ScanelfDriver::defaultInvocation() const
{
	return ScanelfDriver::m_defArgList;
}

void ScanelfDriver::updateStopIndexSlot()
{
	const QString args = m_effectiveArgList.join( " " );

	for ( uint16_t i = 0; i < static_cast<uint16_t>( args.size() ); i++ )
	{
		const QChar stopChar = args.at( i );

		auto symbol{ symbolName() };
		auto symbolSize{ symbolName().size() };

		/*
		 * '+' or '-' are considered stopStrings for scanelf's arguments but
		 * '-' needs extra care; It can appear not only before the symbol's
		 * name but to other arguments as well (ie -qRs.. etc).
		 *
		 * That's why we need to match the '-' sign that sits exactly before
		 * the symbol's name in the arguments list.
		 */
		if ( stopChar == '+'
		     || ( stopChar == '-'
			  && QStringRef{ &args, i, symbolSize }.contains( symbol ) ) )
		{
			QString stopStr{ QString::fromRawData( &stopChar, 1 ) };
			setStopIndexSlot( StopIndex{ i, stopStr } );
		}
	}
}
