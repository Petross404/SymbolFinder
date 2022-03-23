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

#ifndef SCANELFDRIVER_H
#define SCANELFDRIVER_H

#include <qglobal.h>	    // for Q_DISABLE_COPY_MOVE
#include <qobjectdefs.h>    // for Q_OBJECT
#include <qstring.h>	    // for QString
#include <qstringlist.h>    // for QStringList

#include "driver.hpp"	 // for IDriver
class QObject;

/*!
 * \brief `ScanelfDriver` acts as a driver for `scanelf`.
 * `ScanelfDriver`  inherits from `IDriver` and defines some scanelf-specific
 * functions.
 */
class ScanelfDriver: public Driver
{
	Q_OBJECT
	Q_DISABLE_COPY_MOVE( ScanelfDriver )

public:
	/*!
	 * Construct a ScanelfDriver
	 * \param parent is the `QObject` parent of this object
	 */
	ScanelfDriver( QObject* parent = nullptr );

	/*! Default destructor */
	~ScanelfDriver() override;

	[[nodiscard]] QStringList defaultInvocation() const override;

	static const QString name();

	static const QStringList argList();

	static const QString	 m_program;
	static const QStringList m_defArgList;

private slots:
	void updateStopIndexSlot();

private:
	QStringList m_effectiveArgList;
};

#endif	  // SCANELFDRIVER_H
