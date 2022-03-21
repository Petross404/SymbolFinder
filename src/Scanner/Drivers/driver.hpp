// <one line to give the program's name and a brief idea of what it does.>
// SPDX-FileCopyrightText: 2022 Πέτρος Σιλιγκούνας <petross404\gmail.com>
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef DRIVER_H
#define DRIVER_H

#include "idriver.hpp"

/*!
 * `Driver` is a concrete class for the `IDriver`. It defines some generic
 * fuctions for the derived `NmDriver` and `ScanelfDriver`.
 */
class Driver: public Process::IDriver
{
	Q_OBJECT
	Q_DISABLE_COPY_MOVE( Driver )

public:
	/*!
	 * Constructs a Driver.
	 * \param parent is a pointer to the `QObject` that is passed.
	 */
	Driver( QObject* parent = nullptr );

	/*!
	 * Destructor
	 */
	~Driver() override;

	[[nodiscard]] QString driverName() const final;

	[[nodiscard]] bool isSymbolInArgs() const final;

	void setSymbolName( const QString& symbolName ) final;

	bool setInvocation( const QStringList& args ) final;

	[[nodiscard]] QString symbolName() const final;

	void exec() final;

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

private:
	QString m_program; /*!< Program name, ie nm */
	QString m_symbol;  /*!< Symbol name to search with m_program */

	QStringList m_defArgList;	/*!< Default arguments */
	QStringList m_effectiveArgList; /*!< Effective arguments */

	StopIndex m_stopIndex;

	void init();
};

#endif	  // DRIVER_H
