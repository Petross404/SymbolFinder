// <one line to give the program's name and a brief idea of what it does.>
// SPDX-FileCopyrightText: 2022 Πέτρος Σιλιγκούνας <petross404@gmail.com>
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef IDRIVER_H
#define IDRIVER_H

#include <qglobal.h>	    // for Q_DISABLE_COPY_MOVE
#include <qobjectdefs.h>    // for Q_OBJECT, signals
#include <qprocess.h>	    // for QProcess
#include <qstring.h>	    // for QString
#include <qstringlist.h>    // for QStringList
class QObject;

/*!
 * \brief `IDriver` serves as an interface for `NmDriver` and `ScanelfDriver`
 *
 * `IDriver` inherits from `QProcess` and it is an abstract class just to
 * define an interface for other classes to inherit.
 */
class IDriver: public QProcess
{
	Q_OBJECT
	Q_DISABLE_COPY_MOVE( IDriver )

public:
	/*!
	 * Constructor for `IDriver`
	 * \param parent QObject* that by default is null
	 */
	IDriver( QObject* parent = nullptr );

	/*!
	 * Abstract destructor
	 */
	virtual ~IDriver() = 0;

	/*!
	 * The driver's name (ie nm)
	 * \return `QString` that is the driver's name
	 */
	[[nodiscard]] virtual const QString driverName() const = 0;

	/*!
	 * Get the arguments that this driver is invoked with most of the times.
	 * \return `QStringList` that has the "default" arguments for this driver.
	 */
	[[nodiscard]] virtual const QStringList defaultInvocation() const = 0;

	/*!
	 * This function doesn't override the list of the default arguments,
	 * just the active arguments.
	 * \param args is the `QStringList` that has the driver arguments.
	 */
	[[nodiscard]] virtual bool setInvocation( const QStringList& args ) = 0;

	/*!
	 * Get the active list of arguments that the driver is using.
	 * \return `QStringList` that has the driver's active list of arguments.
	 */
	[[nodiscard]] virtual const QStringList invocation() const = 0;

	/*!
	 * Fire up this driver without any further modification to it's
	 * arguments. Use this when you think the driver setup is complete and
	 * all its left is to run it.
	 */
	virtual void exec() = 0;

	/*!
	 * Run the driver with these specific arguments. This is an overloaded function.
	 * \param arg is the list of arguments that this driver will be started with.
	 */
	virtual void exec( const QStringList& arg ) = 0;

	/*!
	 * Read the name of the current symbol that is searched.
	 * \return `QString` that is the symbol's name (ie `printf`).
	 */
	[[nodiscard]] virtual const QString symbolName() const = 0;

	/*!
	 * Set the name of the symbol that will be searched.
	 * \param symbolName is the name of the symbol.
	 */
	virtual void setSymbolName( const QString& symbolName ) = 0;

	[[nodiscard]] virtual const bool isSymbolInArgs() const = 0;

	[[nodiscard]] virtual const QString stopString() const = 0;

signals:
	void startedSearchFor( const QString& symbol );
};

#endif	  // IDRIVER_H
