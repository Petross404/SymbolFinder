// <one line to give the program's name and a brief idea of what it does.>
// SPDX-FileCopyrightText: 2022 Πέτρος Σιλιγκούνας <petross404@gmail.com>
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef NMDRIVER_H
#define NMDRIVER_H

#include <qglobal.h>	    // for Q_DISABLE_COPY_MOVE
#include <qobjectdefs.h>    // for Q_OBJECT
#include <qstring.h>	    // for QString
#include <qstringlist.h>    // for QStringList

#include "driver.hpp"	 // for IDriver
class QObject;

/*!
 * \brief `NmDriver` inherits from `IDriver` and acts as a driver for nm
 *
 * `NmDriver` defines some nm-specific functions.
 */
class NmDriver: public Driver
{
	Q_OBJECT
	Q_DISABLE_COPY_MOVE( NmDriver )

public:
	/*!
	 * Construct a `NmDriver`
	 * \param parent is the pointer to the `QObject` parent
	 */
	NmDriver( QObject* parent = nullptr );

	/*!
	 * Destructor
	 */
	~NmDriver() override;

	[[nodiscard]] QStringList defaultInvocation() const override;

	static QString name();

	static QStringList argList();

	static const QString m_program; /*!< The name of the executable to call */
	static const QStringList m_defArgList; /*! The default arguments for nm */

private slots:
	void updateStopIndexSlot();

private:
	const QStringList l{ "-Dn -o --defined-only /lib/* /usr/lib64/* 2> "
			     "/dev/null | grep '\b\b'" };

	QStringList m_effectiveArgList{ l };
	QString	    m_symbol;
};

#endif	  // NMDRIVER_H
