// <one line to give the program's name and a brief idea of what it does.>
// SPDX-FileCopyrightText: 2022 Πέτρος Σιλιγκούνας <petross404\gmail.com>
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef SCANELFDRIVER_H
#define SCANELFDRIVER_H

#include <qglobal.h>	    // for Q_DISABLE_COPY_MOVE
#include <qobjectdefs.h>    // for Q_OBJECT
#include <qstring.h>	    // for QString
#include <qstringlist.h>    // for QStringList

#include "driver.hpp"	 // for IDriver
class QObject;

/*!
 * \brief `ScanelfDriver` inherits from `IDriver` and acts as a driver for
 * `scanelf` `ScanelfDriver` defines some scanelf-specific functions.
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

	/*!
	 * Default destructor
	 */
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
