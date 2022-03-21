// <one line to give the program's name and a brief idea of what it does.>
// SPDX-FileCopyrightText: 2022 Πέτρος Σιλιγκούνας <petross404@gmail.com>
// SPDX-License-Identifier: GPL-3.0-or-later

#include "nmdriver.hpp"

#include <qlist.h>	 // for QList
#include <qprocess.h>	 // for QProcess

#include "../../ConnectVerifier/connectverifier.hpp"	// for ConnectVerifier
#include "idriver.hpp"					// for IDriver
class QObject;						// lines 13-13

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
	setStopIndexSlot( StopIndex{ (uint16_t)m_effectiveArgList.indexOf( s ), s } );
}
