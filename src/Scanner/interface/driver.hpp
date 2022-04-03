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

#ifndef DRIVER_H
#define DRIVER_H

//#include <qglobal.h>	    // for Q_DISABLE_COPY_MOVE
#include <qobjectdefs.h>    // for Q_OBJECT, signals, slots
#include <qstring.h>	    // for QString
#include <qstringlist.h>    // for QStringList

#include "idriver.hpp"	  // for StopIndex, IDriver
class QObject;

/*!
 * `Driver` is a concrete class for the `IDriver`. It defines some generic
 * fuctions for the derived plugins.
 */
class Driver
	: public QProcess
	, public IDriver
{
	Q_OBJECT
	Q_INTERFACES( IDriver )

public:
	/*!
	 * Constructs a Driver.
	 * \param parent is a pointer to the `QObject` that is passed.
	 */
	Driver( QObject* parent = nullptr );

	/*! Destructor */
	~Driver() override;

	[[nodiscard]] IDriver* create( QObject* parent ) override;

	/*
	 * Mark the following functions as "final" and don't allow
	 * derived classes to override them further.
	 * https://en.cppreference.com/w/cpp/language/final
	 */
	[[nodiscard]] QString driverName() const final;

	[[nodiscard]] bool isSymbolInArgs() const final;

	[[nodiscard]] QStringList defaultInvocation() const final;

	void setSymbolName( const QString& symbolName ) final;

	bool setInvocation( const QStringList& args ) final;

	[[nodiscard]] QString symbolName() const final;

	void exec() final;

	[[nodiscard]] bool canDriverQuit() const final;

	[[nodiscard]] QStringList invocation() const final;

	[[nodiscard]] StopIndex stopIndex() const final;

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
	Driver( QString program, QStringList defArgList, QObject* parent );

protected slots:
	/*!
	 * Set the stop index of the driver's arguments.
	 * \param sIndex is the stop index.
	 * \sa void Driver::stopIndexUpdated()
	 * \sa StopIndex IDriver::stopIndex() const
	 */
	void setStopIndexSlot( StopIndex sIndex );

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

	void symbolSizeChanged( uint16_t size );

protected:
	void setDriverName( const QString& name ) override;

	void setDefaultInvocation( const QStringList& argList ) override;

private:
	QString m_program; /*!< Program name, ie nm */
	QString m_symbol;  /*!< Symbol name to search with m_program */

	QStringList m_defArgList;	/*!< Default arguments */
	QStringList m_effectiveArgList; /*!< Effective arguments */

	StopIndex m_stopIndex;

	void init();
};

#endif	  // DRIVER_H
