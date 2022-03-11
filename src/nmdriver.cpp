// <one line to give the program's name and a brief idea of what it does.>
// SPDX-FileCopyrightText: 2022 Πέτρος Σιλιγκούνας <petross404@gmail.com>
// SPDX-License-Identifier: GPL-3.0-or-later

#include "nmdriver.hpp"

#include <QtCore/qglobal.h>    // for qDebug
#include <qdebug.h>	       // for QDebug
#include <qlist.h>	       // for QList

#include "ConnectVerifier/connectverifier.hpp"	  // for ConnectVerifier
#include "src/idriver.hpp"			  // for IDriver
class QObject;

NmDriver::NmDriver( QObject* parent )
	: IDriver{ parent }
{
	setupConnections();
}

NmDriver::~NmDriver() = default;

const QString NmDriver::driverName() const { return m_program; }

const QStringList NmDriver::defaultInvocation() const { return m_defArgList; }

const QStringList NmDriver::invocation() const { return m_effectiveArgList; }

const bool NmDriver::isSymbolInArgs() const
{
	bool b;
	if ( !m_symbol.isEmpty() && m_argList.contains( m_symbol ) )
		b = true;
	else
		b = false;

	return b;
}

void NmDriver::setInvocation( const QStringList& args )
{
	if ( m_effectiveArgList != args ) { m_effectiveArgList = args; }
}

void NmDriver::exec()
{
	qDebug() << m_program << ".." << m_effectiveArgList.join( ' ' );
	start( m_program, m_effectiveArgList );
	waitForStarted();
}

void NmDriver::exec( const QStringList& arg )
{
	if ( isSymbolInArgs() ) { this->start( m_program, arg ); }
	else
	{
		auto tmp = arg;
		tmp.append( m_symbol );
		start( m_program, tmp );
		waitForStarted();
	}
}

void NmDriver::setupConnections() { ConnectVerifier v; }

void NmDriver::setSymbolName( const QString& s ) { m_symbol = s; }

const QString NmDriver::symbolName() const { return m_symbol; }

QString NmDriver::stDriverName() { return "nm"; }

const QString NmDriver::stopString() const { return "\b"; }
