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