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

#ifndef IDRIVER_HPP
#define IDRIVER_HPP

#if defined( IDRIVER_HPP )
#	ifdef Q_OS_WIN
#		define IDRIVER_EXPORT __declspec( dllexport )
#	else
#		define IDRIVER_EXPORT Q_DECL_EXPORT
#	endif
#else
#	define IDRIVER_EXPORT Q_DECL_IMPORT
#endif

#include <qglobal.h>	    // for Q_DISABLE_COPY_MOVE
#include <qobjectdefs.h>    // for Q_OBJECT, signals
#include <qprocess.h>	    // for QProcess
#include <qstring.h>	    // for QString
#include <qstringlist.h>    // for QStringList
#include <stdint.h>	    // for uint16_t

#include <optional>

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
 * internally.
 */
struct StopIndex
{
	uint32_t    indexOfStop{ 0 }; /*!< Index of the stop string*/
	std::string stopStr{}; /*!< The `QString` representation of the stopStr*/

	/*!
	 * The index or the stopStr can't be null or empty
	 * \return False if the object isn't unset or empty.
	 */
	[[nodiscard]] bool isNull() const;

	StopIndex() = default;

	explicit StopIndex( const uint32_t indexOfStop_, std::string_view stopStr_ );

	static StopIndex makeStopIndex();

	static StopIndex makeStopIndex( const uint32_t	 indexOfStop_,
					std::string_view stopStr_ );
};

/*!
 * \brief `IDriver` serves as an interface for any plugin that wants to search
 * symbols for SymbolFinder.
 *
 * `IDriver` is an abstract class that acts as an interface for other classes to inherit.
 */
class IDriver: public QProcess
{
	Q_OBJECT
	Q_DISABLE_COPY_MOVE( IDriver )
	Q_CLASSINFO( "Author", "Peter Siligkounas" )

public:
	/*!
	 * Constructor for `IDriver`
	 */
	explicit IDriver( std::string_view name, std::optional<QObject*> parent );

	~IDriver() override;

	/*!
	 * The driver's name (ie nm)
	 * \return `QString` that is the driver's name
	 */
	[[nodiscard]] virtual std::string driverName() const = 0;

	/*!
	 * Get the arguments that this driver is invoked with most of the times.
	 * \return `QStringList` that has the "default" arguments for this driver.
	 */
	[[nodiscard]] virtual std::list<std::string_view> defaultInvocation() const = 0;

	/*!
	 * This function doesn't override the list of the default arguments,
	 * just the active arguments.
	 * \param args is the `QStringList` that has the driver arguments.
	 */
	[[nodiscard]] virtual bool setInvocation( std::string_view args ) = 0;

	/*!
	 * Get the active list of arguments that the driver is using.
	 * \return `QStringList` that has the driver's active list of arguments.
	 */
	[[nodiscard]] virtual std::list<std::string_view> invocation() const = 0;

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
	[[nodiscard]] virtual std::string symbolName() const = 0;

	/*!
	 * Set the name of the symbol that will be searched.
	 * \param symbolName is the name of the symbol.
	 */
	virtual void setSymbolName( std::string_view newSymbolName ) = 0;

	[[nodiscard]] virtual bool isSymbolInArgs() const = 0;

	/*!
	 * Can driver quit when asked to?
	 */
	[[nodiscard]] virtual bool canDriverQuit() const = 0;

	/*!
	 * Return the `StopIndex` of the arguments.
	 *\return The `StopIndex` value.
	 */
	[[nodiscard]] virtual StopIndex stopIndex() const = 0;

	/*!
	 * Delete this driver when asked.
	 */
	virtual void deleteDriver() const = 0;

	//// Static variables to describe the free functions that are used ////
	inline static constexpr char const* Init{ "init" };
	inline static constexpr char const* DrName{ "driverNameGlobal" };
	inline static constexpr char const* DrDesc{ "driverDescGlobal" };
	inline static constexpr char const* DefArgs{ "argumentsGlobal" };
	///////////////////////////////////////////////////////////////////////

signals:
	/*!
	 * Inform any listener that a driver just contructed.
	 * \param driverName is the driver's name
	 */
	void initialized( std::string_view driverName );

	void symbolSizeChanged( uint16_t size );

protected:
	/*!
	 * Set the driver's name
	 * \param name is the driver's name
	 */
	virtual void setDriverName( std::string_view nane ) = 0;

	/*!
	 * Set the driver's arguments
	 * \param argList is the driver's arguments
	 */
	virtual void setDefaultInvocation( std::string_view argList ) = 0;
};

#endif	  // IDRIVER_HPP
