// <one line to give the program's name and a brief idea of what it does.>
// SPDX-FileCopyrightText: 2022 Πέτρος Σιλιγκούνας <petross404@gmail.com>
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef MESSAGEWIDGET_H
#define MESSAGEWIDGET_H

#include <qframe.h>	    // for QFrame, QFrame::Raised
#include <qglobal.h>	    // for qGetPtrHelper, Q_DEC...
#include <qobjectdefs.h>    // for Q_OBJECT, signals
#include <qpalette.h>	    // for QPalette
#include <qsize.h>	    // for QSize
#include <qstring.h>	    // for QString

#include <gsl/pointers>	   // for owner, strict_not_null
#include <memory>	   // for unique_ptr
#include <optional>	   // for optional
#include <string_view>	   // for string_view

#include "implementation/messagewidgettype.hpp"	   // for MessageType, Message...
class MessageWidgetPrivate;			   // lines 20-20
class QAction;					   // lines 21-21
class QCloseEvent;				   // lines 22-22
class QEvent;					   // lines 23-23
class QObject;					   // lines 24-24
class QPaintEvent;				   // lines 25-25
class QWidget;					   // lines 26-26

template<typename T> using not_null_owner = gsl::strict_not_null<gsl::owner<T>>;

/*!
 * `MessageWidget` overrides `QFrame` and tries to implement a widget
 * that outputs informations, errors and other messages for the user.
 */
class MessageWidget: public QFrame
{
	Q_OBJECT
	Q_DISABLE_COPY_MOVE( MessageWidget )

public:
	/*!
	 * Constructor of the public part of the widget.
	 * \param text is the text for the widget.
	 * \param parent is the parent qobject for this widget.
	 * \param type describes if this will output Info, Error etc.
	 * \param shape is of type `QFrame::StyledPanel`.
	 * \param shadow is of type `QFrame::Shadow`.
	 */
	explicit MessageWidget( const std::string_view		 text,
				std::optional<QWidget*>		 parent,
				std::optional<MessageType::Type> type,
				std::optional<QFrame::Shape>	 shape,
				std::optional<QFrame::Shadow>	 shadow );

	/*!
	 *Virtual destructor
	 */
	~MessageWidget() override;

	void setPallete( const QPalette& paletteArgument = QPalette{},
			 bool		 forceParameter	 = false );

	[[nodiscard]] QString text() const;

	void setText( const QString& text );

	[[nodiscard]] MessageType::Type messageType() const;

	void setMessageType( MessageType::Type type );
	void updateLayout();
	void createLayout();

	[[nodiscard]] int  bestContentHeight() const;
	[[nodiscard]] bool isCloseButtonVisible() const;

	void setCloseButtonVisible( bool show );
	void addAction( QAction* action );
	void removeAction( QAction* action );

	[[nodiscard]] QSize sizeHint() const override;
	[[nodiscard]] QSize minimumSizeHint() const override;

signals:
	void messageWidgetClosed() const;

protected:
	std::unique_ptr<MessageWidgetPrivate> const d_ptr; /*!< Pointer to the private implementation */

	/*!
	 * Re-implement this function to paint this widget.
	 * \param event is the event to be processed
	 */
	void paintEvent( QPaintEvent* event ) override;

	void closeEvent( QCloseEvent* event ) override;

	/*!
	 * Re-implement this function to change the active QPalette etc.
	 * \param event is the event to be processed
	 * \return true if the event was processed
	 */
	bool event( QEvent* event ) override;

private:
	Q_DECLARE_PRIVATE( MessageWidget );

	void setupWidgets();
	void setupConnections();
};

#endif	  // MESSAGEWIDGET_H
