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

#ifndef NMDRIVER_HPP
#define NMDRIVER_HPP

#include <qfile.h>
#include <qglobal.h>	    // for Q_DISABLE_COPY_MOVE
#include <qobjectdefs.h>    // for Q_OBJECT
#include <qstring.h>	    // for QString
#include <qstringlist.h>    // for QStringList

#include "../interface/genericdriver.hpp"    // for IDriver

#if defined( NMDRIVER_HPP )
#	ifdef Q_OS_WIN
#		define NMLIB_EXPORT __declspec( dllexport )
#	else
#		define NMLIB_EXPORT Q_DECL_EXPORT
#	endif
#else
#	define NMLIB_EXPORT Q_DECL_IMPORT
#endif

/*!
 * \brief `NmDriver` inherits from `IDriver` and acts as a driver for nm
 *
 * `NmDriver` defines some nm-specific functions.
 */
class NMLIB_EXPORT NmDriver: public GenericDriver
{
	Q_OBJECT
	Q_DISABLE_COPY_MOVE( NmDriver )

public:
	/*!
	 * Construct a `NmDriver`
	 * \param parent is the pointer to the `QObject` parent
	 */
	explicit NmDriver( std::optional<QObject*> parent );

	/*! Destructor */
	~NmDriver() override;

private slots:
	void updateStopIndexSlot();
};

extern "C" NMLIB_EXPORT IDriver*    init( QObject* parent );
extern "C" NMLIB_EXPORT const char* driverNameGlobal();
extern "C" NMLIB_EXPORT const char* driverDescGlobal();
extern "C" NMLIB_EXPORT const char* argumentsGlobal();

#endif	  // NMDRIVER_HPP
