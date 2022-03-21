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
 * `StopIndex` packs the index and the string that our symbol's name will be
 * appended right after. For example, when working with `nm` and `NmDriver` we
 * grep the output like this: `grep '\bsymbol\b` . So, "\b" is considered to be
 * the "stopString" at a certain index.
 *
 * Likewise, scanelf's stopString is either "+" or "-". Plus is used when we are
 * searching a symbol that is defined in a library and minus is used when we are
 * searching an undefined symbol.
 *
 * The latter is a tricky situation because minus ("-") is used to pass args as
 * well, like `--help`, '-v' etc. `ScanelfDriver` handles this situation
 * internally as it should.
 */
struct StopIndex
{
	uint16_t indexOfStop; /*!< Index of the stop string*/
	QString	 stopStr;     /*!< The `QString` representation of the stopStr*/

	/*!
	 * The index or the stopStr can't be null or empty
	 * \return False if the object isn't unset or empty.
	 */
	bool isNull();
};

namespace Process {
/*!
 * \brief `IDriver` serves as an interface for `NmDriver` and `ScanelfDriver`.
 *
 * `IDriver` inherits from `QProcess` and it's an abstract class just to
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
	 * Abstract destructor (=0)
	 */
	~IDriver() override = 0;

	/*!
	 * The driver's name (ie nm)
	 * \return `QString` that is the driver's name
	 */
	[[nodiscard]] virtual QString driverName() const = 0;

	/*!
	 * Get the arguments that this driver is invoked with most of the times.
	 * \return `QStringList` that has the "default" arguments for this driver.
	 */
	[[nodiscard]] virtual QStringList defaultInvocation() const = 0;

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
	[[nodiscard]] virtual QStringList invocation() const = 0;

	/*!
	 * Fire up this driver without any further modification to it's
	 * arguments. Use this when you think the driver setup is complete and
	 * all its left is to run it.
	 */
	virtual void exec() = 0;

	/*!
	 * Read the name of the current symbol that is searched.
	 * \return `QString` that is the symbol's name (ie `printf`).
	 */
	[[nodiscard]] virtual QString symbolName() const = 0;

	/*!
	 * Set the name of the symbol that will be searched.
	 * \param symbolName is the name of the symbol.
	 */
	virtual void setSymbolName( const QString& symbolName ) = 0;

	[[nodiscard]] virtual bool isSymbolInArgs() const = 0;

	/*!
	 * Return the `StopIndex` of the arguments.
	 *\return The `StopIndex` value.
	 */
	[[nodiscard]] virtual StopIndex stopIndex() const = 0;

signals:
	void driverInitialized( const QString& name );
};
}    // namespace Process
#endif	  // IDRIVER_H
