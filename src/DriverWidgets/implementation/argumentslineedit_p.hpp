// <one line to give the program's name and a brief idea of what it does.>
// SPDX-FileCopyrightText: 2022 Πέτρος Σιλιγκούνας <petross404@gmail.com>
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef ARGUMENTSLINEEDITPRIVATE_HPP_INCLUDED
#define ARGUMENTSLINEEDITPRIVATE_HPP_INCLUDED

#include <qglobal.h>	   // for Q_DECLARE_PUBLIC, Q_D...
#include <qnamespace.h>	   // for MouseButton
#include <qstring.h>	   // for QString

#include <cstdint>     // for uint16_t
#include <optional>    // for optional

#include "../../Scanner/interface/idriver.hpp"	  // for StopIndex
class ArgumentsLineEdit;			  // lines 15-15			  // lines 13-13

class ArgumentsLineEditPrivate
{
	Q_DISABLE_COPY_MOVE( ArgumentsLineEditPrivate )
public:
	/*!
	 * Construct an `ArgumentsLineEdit` object with the following parameters.
	 *
	 * \param arguments is the `QString` for the driver arguments
	 * \param stopString is the `QString` that imediately after we find the symbol's name
	 * \param parent is the ptr of the parent `QWidget` for this object
	 */
	explicit ArgumentsLineEditPrivate( ArgumentsLineEdit* lineEdit,
					   const QString&     arguments,
					   StopIndex	      stopIndex );

	explicit ArgumentsLineEditPrivate( std::optional<ArgumentsLineEdit*> lineEdit );

	/*!
	 * Default destructor
	 */
	~ArgumentsLineEditPrivate();

	/*!
	 * This function sets the stop string
	 * \param str is the stop string
	 * \sa void ArgumentsLineEdit::stopString() const
	 */
	void setStopIndex( const StopIndex& stopIndex );

	/*!
	 * This function returns the selected driver's "stop string".
	 * \return `QString` that is the stop string.
	 * \sa void ArgumentsLineEdit::setStopString(const QString& str)
	 */
	[[nodiscard]] StopIndex stopIndex() const;

	std::uint16_t symbolSize() const;

	void setSymbolSize( uint16_t size );

private:
	Q_DECLARE_PUBLIC( ArgumentsLineEdit )

	ArgumentsLineEdit* const q_ptr;

	uint16_t m_synbolSz = 0;
	QString	 m_text; /*!< Text that this widget contains>*/

	QString m_specialStr; /*!< The string in the argument that immediately after the symbol name exists.
			       *\sa void ArgumentsLineEdit::stopString() const
			       */

	StopIndex m_stopIndex;
	/*!
	 * The constructors share some functionality.
	 */
	void init();

	void checkStopString() const;

	void handleCursorPosition( std::uint16_t	 positionAt,
				   const Qt::MouseButton button ) const;
};

#endif	  // ARGUMENTSLINEEDITPRIVATE_HPP_INCLUDED
