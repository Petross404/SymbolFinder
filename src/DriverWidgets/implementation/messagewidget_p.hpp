// <one line to give the program's name and a brief idea of what it does.>
// SPDX-FileCopyrightText: 2022 Πέτρος Σιλιγκούνας <petross404@gmail.com>
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef MESSAGEWIDGET_P_HPP
#define MESSAGEWIDGET_P_HPP

#include <qglobal.h>	 // for Q_DECLARE_PUBLIC, Q_DISABLE_COPY_MOVE
#include <qpalette.h>	 // for QPalette
#include <qstring.h>	 // for QString

#include <gsl/pointers>	   // for owner, strict_not_null
#include <optional>
#include <string_view>	  // for string_view

#include "messagewidgettype.hpp"    // for MessageType, MessageType::Type, Mes...
class MessageWidget;		    // lines 33-33
class QAction;			    // lines 21-21
class QGridLayout;		    // lines 24-24
class QLabel;			    // lines 25-25
class QToolButton;		    // lines 28-28

template<typename T> using not_null_owner = gsl::strict_not_null<gsl::owner<T>>;

/*!
 */
class MessageWidgetPrivate
{
	Q_DISABLE_COPY_MOVE( MessageWidgetPrivate )

public:
	/*!
	 * Constructor
	 * \param messageWidget
	 * \param text
	 * \param type
	 */
	explicit MessageWidgetPrivate( MessageWidget*	      messageWidget,
				       const std::string_view text,
				       std::optional<MessageType::Type> type );

	/*! destructor */
	virtual ~MessageWidgetPrivate();

	/*!
	 * Set the palette for the widget.
	 *
	 * \param paletteArgument is the palette to set for the widget
	 * \param forceParameter defines if the MessageType::Type should be enforced.
	 */
	void setPallete( const QPalette& paletteArgument = QPalette{},
			 const bool	 forceParameter	 = false ) const;

	/*!
	 * Read the text of the widget.
	 * \return The text as `QString` value.
	 */
	[[nodiscard]] QString text() const;

	/*!
	 * Set the text displayed in `QLabel`
	 * \param text is displayed in `QLabel`
	 */
	void setText( const QString& text );

	void updateLayout();
	void createLayout();

	[[nodiscard]] int  bestContentHeight() const;
	[[nodiscard]] bool isCloseButtonVisible() const;

	void setCloseButtonVisible( bool show );

private:
	Q_DECLARE_PUBLIC( MessageWidget )

	MessageWidget* const q_ptr; /*!< Pointer to the public instance  */

	not_null_owner<QToolButton*> m_closeBtn;    /*!< Close toolbutton */
	not_null_owner<QAction*>     m_closeAction; /*!< Close action */
	not_null_owner<QGridLayout*> m_gridLayout; /*!< Grid layoyt to hold the widgets */
	not_null_owner<QLabel*> m_label; /*!< Label inside the widget to show text */

	MessageType::Type m_messageType; /*!<  */

	int borderSize() const;

	void setupWidgets();
	void setupConnections();
	void handlePaintEvent();
};

#endif	  // MESSAGEWIDGET_P_HPP
