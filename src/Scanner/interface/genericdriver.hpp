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

#ifndef DRIVER_HPP
#define DRIVER_HPP

#include <qobjectdefs.h>    // for Q_OBJECT, signals, slots
#include <qstring.h>	    // for QString
#include <qstringlist.h>    // for QStringList

#include "idriver.hpp"	  // for StopIndex, IDriver
class QObject;

/*!
 * `Driver` is a concrete class for the `IDriver`. It defines some generic
 * fuctions for the derived plugins.
 */
class GenericDriver: public IDriver
{
	Q_OBJECT
	Q_DISABLE_COPY_MOVE( GenericDriver )

public:
	/*! Destructor */
	~GenericDriver() override;

	/*!
	 *
	 */
	[[nodiscard]] std::string driverName() const final;

	/*!
	 * Determines if the symbol to be searched, is already in the
	 * arguments of the driver.
	 *
	 * \return true if the symbol is in the arguments.
	 */
	[[nodiscard]] bool isSymbolInArgs() const final;

	/*!
	 * Default invocation of the selected driver.
	 *
	 * \return The default invocation of the selected driver as
	 * a `QStringList`.
	 */
	[[nodiscard]] std::list<std::string_view> defaultInvocation() const final;

	/*!
	 * Set the symbol that is going to be searched.
	 * \param symbolName is the symbol's name.
	 */
	void setSymbolName( std::string_view newSymbolName ) final;

	/*!
	 * Set the arguments for the selected driver.
	 * \param args is the `QStringList` of the arguments.
	 */
	bool setInvocation( std::string_view args ) final;

	/*!
	 * Read the symbol's name.
	 * \return the symbol's name.
	 */
	[[nodiscard]] std::string symbolName() const final;

	/*!
	 * Override the `QProcess::exec()` with some `Driver` specific
	 * functions.
	 */
	void exec() final;

	[[nodiscard]] bool canDriverQuit() const final;

	[[nodiscard]] std::list<std::string_view> invocation() const final;

	[[nodiscard]] StopIndex stopIndex() const final;

	void deleteDriver() const final;

protected:
	/*!
	 * \brief Protected constructor, not to be publicly used.
	 *
	 * This constructor is protected, since only the derived classes are
	 * allowed to call it internally.
	 *
	 * \param program is the driver's program name.
	 * \param defArgList is the driver's default argument list.
	 * \param parent is a pointer to the parent `QObject`.
	 */
	explicit GenericDriver( std::string_view	program,
				std::string_view	defArgList,
				std::optional<QObject*> parent );

protected slots:
	/*!
	 * Set the stop index of the driver's arguments.
	 *
	 * \param sIndex is the stop index.
	 * \sa void Driver::stopIndexUpdated()
	 * \sa StopIndex IDriver::stopIndex() const
	 */
	void setStopIndexSlot( const StopIndex sIndex );

signals:
	/*!
	 * When the aruments or the symbol name changes, the stop index
	 * changes. Emit and connect to change the index. This signal is
	 * handled in `NmDriver` and `ScanelfDriver`.
	 * \sa void Driver::setStopIndexSlot( StopIndex sIndex )
	 */
	void stopIndexUpdated();

	void driverInitialized( const QString& name );

	void stopIndexUpdatingFailed();

protected:
	void setDriverName( std::string_view name ) override;

	void setDefaultInvocation( std::string_view argList ) override;

private:
	std::string m_symbol; /*!< Symbol name to search with m_program */

	std::list<std::string_view> m_defArgList;	/*!< Default arguments */
	std::list<std::string_view> m_effectiveArgList; /*!< Effective arguments */

	std::optional<StopIndex> m_stopIndex;

	void init();
};

#endif	  // DRIVER_HPP
