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

#ifndef SCANELFDRIVER_HPP
#define SCANELFDRIVER_HPP

#include <qfile.h>
#include <qglobal.h>	    // for Q_DISABLE_COPY_MOVE
#include <qobjectdefs.h>    // for Q_OBJECT
#include <qstring.h>	    // for QString
#include <qstringlist.h>    // for QStringList

#include <optional>
// #include <tl/expected.hpp>

#include "../interface/genericdriver.hpp"    // for IDriver

#if defined( SCANELFDRIVER_HPP )
#	ifdef Q_OS_WIN
#		define SCANELFLIB_EXPORT __declspec( dllexport )
#	else
#		define SCANELFLIB_EXPORT Q_DECL_EXPORT
#	endif
#else
#	define SCANELFLIB_EXPORT Q_DECL_IMPORT
#endif

/*!
 * \brief `ScanelfDriver` acts as a driver for `scanelf`.
 * `ScanelfDriver`  inherits from `IDriver` and defines some scanelf-specific
 * functions.
 */
class SCANELFLIB_EXPORT ScanelfDriver: public GenericDriver
{
	Q_OBJECT
	Q_DISABLE_COPY_MOVE( ScanelfDriver )

public:
	/*!
	 * Construct a ScanelfDriver
	 * \param parent is the `QObject` parent of this object
	 */
	explicit ScanelfDriver( std::optional<QObject*> parent );

	/*! Default destructor */
	~ScanelfDriver() override;

private slots:
	void updateStopIndexSlot();
};

extern "C" SCANELFLIB_EXPORT IDriver*	 init( QObject* parent );
extern "C" SCANELFLIB_EXPORT const char* driverNameGlobal();
extern "C" SCANELFLIB_EXPORT const char* driverDescGlobal();
extern "C" SCANELFLIB_EXPORT const char* argumentsGlobal();

#endif	  // SCANELFDRIVER_HPP
