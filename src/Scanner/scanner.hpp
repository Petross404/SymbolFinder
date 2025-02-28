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

#ifndef SCANNER_H
#define SCANNER_H

#include <qbytearray.h>	    // for QByteArray
#include <qglobal.h>	    // for Q_DISABLE_COPY_MOVE
#include <qobject.h>	    // for QObject
#include <qobjectdefs.h>    // for slots, Q_OBJECT, signals
#include <qprocess.h>	    // for QProcess, QProcess::ExitStatus, QProc...
#include <qstring.h>	    // for QString
#include <qstringlist.h>    // for QStringList
#include <stdint.h>	    // for uint16_t

#include <gsl/pointers>	   // for owner
#include <optional>
#include <utility>
#include <vector>

#include "interface/idriver.hpp"    // for StopIndex
#include "interface/pluginmanager.hpp"
#include "interface/pluginpair.hpp"

class GenericDriver;
class PluginManager;

template<typename T>
using OptionalRef = std::optional<typename std::reference_wrapper<const T>::type>;

/*!
 * `Scanner` class can create and hold an `IDriver*` instance.
 *
 * `Scanner` inherits the `QObject` and DriverFactory class and defines
 * the interface that gives the `MainWindow` the ability to I/O information
 * to and from the supported driver plugins.
 *
 * As of now, the only supported drivers are `nm` and `scanelf`.
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
	explicit Scanner( std::optional<QObject*> parent );

	/*!
	 * Return the `IDriver` ptr (`m_d` for this class)
	 * \return The driver that is selected.
	 */
	[[nodiscard]] std::optional<IDriver*> driver() const;

	/*! Return the default arguments that the active driver is called
	 * \return A list of default arguments
	 */
	[[nodiscard]] std::list<std::string_view> defaultInvocation() const;

	/*!
	 * Return the current arguments of the active driver
	 * \return A list of the current arguments
	 */
	[[nodiscard]] std::list<std::string_view> invocation() const;

	/*! Reset the driver's arguments to the default list. */
	void resetInvocation();

	/*!
	 * Set the list of arguments that the driver will be invoked with.
	 * \param args is the `QString` text of the arguments for the driver.
	 * It is converted to `QStringList` inside the function again.
	 * \param secret is a `QString` that is used to determine where this
	 * function was called from. In order to not write 3 times the same
	 * overloaded function with slightly different functionality, this
	 * simple way was chosen.
	 * \sa `void setSymbolName(const QString& symbol)`
	 */
	void setInvocation( std::string_view		    arguments,
			    std::optional<std::string_view> secret );

	[[nodiscard]] StopIndex stopIndexOfArguments() const;

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
	 * emmited.
	 * \sa void Scanner::argumentsUpdated(const QStringList& args)+
	 */
	void setSymbolName( std::string_view symbol );

	/*!
	 * Read the name of the symbol.
	 * \return the name of the symbol.
	 */
	[[nodiscard]] std::string symbolName() const;

	/*!
	 * Can the driver quit (hence the application) or is it still searching?
	 * \return true if the driver isn't searching
	 */
	[[nodiscard]] bool canQuit() const;

	/*!
	 * When the driver in the combobox is changed, reset to another
	 * `Driver`.
	 * \param driverName is the new driver's name.
	 */
	void reset( std::string_view driverName );

	[[nodiscard]] std::vector<PluginDriver> plugins() const;

	/*! Destructor */
	~Scanner() override;

	[[nodiscard]] std::vector<PluginDesc> pluginDescription() const;

public slots:
	/*! The function that searches for the symbol with the predefined driver. */
	void performScanSlot() const;

	void driverInitializedSlot( const std::string_view symbol );

	void aboutToCloseSlot();

signals:
	/*! IDriver got stderr ready */
	void readyReadStandardError();
	/*! IDriver got stdout ready */
	void readyReadStandardOutput();
	/*! The driver's arguments are updated. */
	void argumentsUpdated();

	/*! Scan for symbol started */
	void scanStarted();

	/*!
	 * This signal is emitted when the scanner finishes. After the IDriver
	 * has finished, the buffers in QProcess are still intact. You can still
	 * read any data that the process may have written before it finished.
	 * \param exitCode is the exit code of the process.
	 * \param exitStatus is the exit status.
	 */
	void scanFinished( int exitCode, QProcess::ExitStatus exitStatus );

	/*!
	 * Emit this signal when the scanner is finished.
	 * \param error is the error that happened.
	 */
	void scanErrorOccured( QProcess::ProcessError error );

	void symbolSizeChanged( uint16_t size );

	/*!
	 * Emit this signal when the driver is initialized.
	 * \param name is the driver's name.
	 */
	void driverInitialized( std::string_view name ) const;

	void pluginsLoaded( std::reference_wrapper<const QStringList> pluginNames );

	void aboutToClose();

protected:
	/*!
	 * Set's the driver's name. This function is used only internally to re-init
	 * the `IDriver` instance, thus it isn't public.
	 * \param driverName is the driver's name.
	 */
	void setEffectiveDriverName( std::optional<std::string_view> driverName );

	/*!
	 */
	const std::string selectedDriverName();

protected slots:
	/*! Read the stderr of the `IDriver` to set the `m_stderr` */
	void setStandardErrSlot();
	/*! Read the stdout of the `IDriver` to set the `m_stdout` */
	void setStandardOutSlot();

private:
	std::uint32_t m_pluginCount = 0;
	std::string   m_selectedDriverName; /*!< Driver's name */
	QByteArray    m_stdout; /*!< stdout text from the underlying driver */
	QByteArray    m_stderr; /*!< stderr text from the underlying driver */

	std::optional<IDriver*> m_d{ std::nullopt }; /*!< Ptr to the `IDriver` instance */

	gsl::owner<PluginManager*> m_pluginManager{ nullptr };

	std::vector<PluginDriver> m_plugins;

	/*!
	 * Private function to setup all the connections
	 */
	void setupConnections( const std::uint16_t    counter,
			       const std::string_view drName ) const;

	void init();
	void init( std::string_view driverName );

	std::uint16_t loadDriverPlugins();

	/*!
	 * Setup the new driver for `Scanner` and destroy the previous
	 * one (if any).
	 * \param newDriver is an `std::optional` for the new driver because
	 * it can be null.
	 */
	void setupDriver( std::optional<IDriver*> newDriver );

	/*!
	 * Low-level function to set `m_d`.
	 * \param d is the `std::optional` driver.
	 */
	void setDriver( std::optional<IDriver*> d );
};

#endif	  // SCANNER_H
