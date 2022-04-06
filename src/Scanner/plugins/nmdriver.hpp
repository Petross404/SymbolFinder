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

#include <qfile.h>
#include <qglobal.h>	    // for Q_DISABLE_COPY_MOVE
#include <qobjectdefs.h>    // for Q_OBJECT
#include <qstring.h>	    // for QString
#include <qstringlist.h>    // for QStringList

#include "../interface/driver.hpp"    // for IDriver
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

	/*! Destructor */
	~NmDriver() override;

	static IDriver*	   create( QObject* parent );
	static QString	   driverNameStatic();
	static QStringList argumentsStatic();

private slots:
	void updateStopIndexSlot();

private:
	QFile	    m_jsonFile;
	QStringList m_effectiveArgList;
	QStringList m_defaultArguments;
	QString	    m_name;
};

#endif	  // NMDRIVER_H
