// <one line to give the program's name and a brief idea of what it does.>
// SPDX-FileCopyrightText: 2022 Πέτρος Σιλιγκούνας <petross404@gmail.com>
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef NMDRIVER_H
#define NMDRIVER_H

#include <qglobal.h>	    // for Q_DISABLE_COPY_MOVE
#include <qobjectdefs.h>    // for Q_OBJECT
#include <qstring.h>	    // for QString
#include <qstringlist.h>    // for QStringList

#include "idriver.hpp"	  // for IDriver
class QObject;

/**
 * \brief NmDriver inherits from IDriver and acts as a driver for /usr/bin/nm
 */
class NmDriver: public IDriver
{
	Q_OBJECT
	Q_DISABLE_COPY_MOVE( NmDriver )

public:
	NmDriver( QObject* parent = nullptr );

	/**
	 * Destructor
	 */
	~NmDriver() override;

	static QString stDriverName();

	const QString driverName() const override;

	const QStringList defaultInvocation() const override;
	const QStringList invocation() const override;
	void		  setInvocation( const QStringList& args ) override;

	void exec() override;
	void exec( const QStringList& arg ) override;

	const QString symbolName() const override;
	void	      setSymbolName( const QString& s ) override;

	const bool isSymbolInArgs() const override;

	const QString stopString() const override;

private:
	const QString m_program{ "nm" }; /*!< The name of the executable to call */
	const QStringList m_defArgList{
		"-Dn -o --defined-only /lib/* /usr/lib64/* 2> /dev/null | grep "
		"'\b\b'" };
	QStringList m_effectiveArgList{ m_defArgList };
	QStringList m_argList; /*!< The list of arguments */
	QString	    m_symbol;

	void setupConnections();
};

#endif	  // NMDRIVER_H
