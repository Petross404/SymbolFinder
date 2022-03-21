// <one line to give the program's name and a brief idea of what it does.>
// SPDX-FileCopyrightText: 2022 Πέτρος Σιλιγκούνας <petross404@gmail.com>
// SPDX-License-Identifier: GPL-3.0-or-later

#include "scanelfdriver.hpp"

#include <qchar.h>     // for operator==, QChar
#include <stddef.h>    // for size_t

#include "../../ConnectVerifier/connectverifier.hpp"
#include "idriver.hpp"	  // for IDriver
class QObject;

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
