// <one line to give the program's name and a brief idea of what it does.>
// SPDX-FileCopyrightText: 2022 Πέτρος Σιλιγκούνας <petross404@gmail.com>
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef SCANNER_H
#define SCANNER_H

#include <qbytearray.h>	    // for QByteArray
#include <qglobal.h>	    // for Q_DISABLE_COPY_MOVE
#include <qobject.h>	    // for QObject
#include <qobjectdefs.h>    // for Q_OBJECT, signals, slots
#include <qprocess.h>	 // for QProcess, QProcess::ExitStatus, QProcess::P...
#include <qstring.h>	 // for QString
#include <qstringlist.h>    // for QStringList

#include <gsl/pointers>	   // for owner
class IDriver;

/*!
 * `Scanner` class creates an object that can hold an `IDriver*` instance.
 *
 * `Scanner` inherits the `QObject` class and defines the interface that
 * gives the `MainWindow` the ability to input and output information to/from
 * the supported drivers.
 *
 * As of now, the only supported driver is `nm`.
 *
 * \todo Add support for `scanelf` as well.
 */
class Scanner: public QObject
{
	Q_OBJECT
	Q_DISABLE_COPY_MOVE( Scanner )

public:
	/*!
	 * Default constructor
	 * \param parent is the `QObject*` that is the parent for `Scanner` class
	 */
	Scanner( QObject* parent = nullptr );

	/*!
	 * Constructor that accepts the name of the driver
	 * \param driverName is the name of the driver
	 * \param parent is the `QObject*` that is the parent for `Scanner` class
	 */
	Scanner( const QString& driverName, QObject* parent = nullptr );

	/*!
	 * Return the `IDriver` ptr (m_d for this class)
	 * \return The driver that is selected.
	 */
	[[nodiscard]] IDriver* driver() const;

	/*! Return the default arguments that the active driver is called
	 * \return A list of default arguments
	 */
	[[nodiscard]] QStringList defaultInvocation() const;

	/*!
	 * Return the current arguments of the active driver
	 * \return A list of the current arguments
	 */
	[[nodiscard]] QStringList invocation() const;

	/*!
	 * Reset the driver's arguments to a default.
	 */
	void resetInvocation();

	/*!
	 * Set the list of arguments that the driver will be invoked with
	 * \param args is the `QString` text of the arguments for the driver.
	 * It is converted to `QStringList` inside the function again.
	 * \param secret is set if the function was called from
	 * `setSymbolName()` and the symbol is changed. Do NOT set this
	 * parameter your self when calling this function!
	 * \sa `void setSymbolName(const QString& symbol)`
	 */
	void setInvocation( const QString& args, const QString& secret = "" );

	[[nodiscard]] QString stopString() const;

	/*!
	 * Read the stderr that the driver produced
	 * \return stderr as a `QByteArray`
	 */
	[[nodiscard]] QByteArray standardError() const;

	/*!
	 * Read the stdout that the driver produced
	 * \return stdout as a `QByteArray`
	 */
	[[nodiscard]] QByteArray standardOut() const;

	/*!
	 * Set the name of the symbol to be searched for the driver. If the
	 * symbol is correctly set inside the list of the driver arguments, the
	 * `void Scanner::argumentsUpdated(const QStringList& args)` signal is
	 * emmited. \sa void Scanner::argumentsUpdated(const QStringList& args)+
	 */
	void setSymbolName( const QString& symbol );

	[[nodiscard]] QString symbolName() const;

	/*!
	 * Destructor
	 */
	~Scanner() override;

public slots:
	void performScan();

signals:
	//! IDriver got stderr ready
	void readyReadStandardError();
	//! IDriver got stdout ready
	void readyReadStandardOutput();
	//! The driver's arguments are updated.
	void argumentsUpdated();

	void scanStarted();
	void scanFinished( int exitCode, QProcess::ExitStatus exitStatus );
	void scanErrorOccured( QProcess::ProcessError error );

protected:
	/*! Read the stderr of the `IDriver` to set the `m_stderr` */
	void setStandardErrSlot();
	/*! Read the stdout of the `IDriver` to set the `m_stdout` */
	void setStandardOutSlot();

private:
	QString	   m_name;
	QByteArray m_stdout; /*!< stdout text from the underlying driver*/
	QByteArray m_stderr; /*!< stderr text from the underlying driver*/

	const QString m_secretSetSymbolArgument{ "#symbol#" };
	const QString m_secretSetDefaultArgument{ "#default#" };

	gsl::owner<IDriver*> m_d; /*!< Ptr to the `IDriver` instance */

	//! Private function to setup all the connections that have to be made
	void setupConnections();
};

#endif	  // SCANNER_H
