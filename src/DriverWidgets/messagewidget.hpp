// <one line to give the program's name and a brief idea of what it does.>
// SPDX-FileCopyrightText: 2022 Πέτρος Σιλιγκούνας <petross404@gmail.com>
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef MESSAGEWIDGET_H
#define MESSAGEWIDGET_H

#include <qframe.h>	    // for QFrame, QFrame::Raised, QFrame::StyledPanel
#include <qglobal.h>	    // for Q_DISABLE_COPY_MOVE
#include <qobjectdefs.h>    // for Q_ENUM, Q_OBJECT, signals
#include <qsize.h>	    // for QSize
#include <qstring.h>	    // for QString

#include <gsl/pointers>	   // for owner
class QAction;		   // lines 15-15
class QCloseEvent;
class QEvent;
class QGridLayout;    // lines 12-12
class QLabel;	      // lines 13-13
class QObject;
class QPaintEvent;
class QToolButton;    // lines 14-14
class QWidget;

/*!
 * \todo Write documentation
 */
class MessageWidget: public QFrame
{
	Q_OBJECT
	Q_DISABLE_COPY_MOVE( MessageWidget )

public:
	enum Type {
		Information = 0x001,
		Warning,
		Error,
	};
	Q_ENUM( Type )

	/*!
	 * Default constructor
	 */
	explicit MessageWidget( const QString&	    text,
				MessageWidget::Type type   = Type::Information,
				QWidget*	    parent = nullptr,
				QFrame::Shape	    shape = QFrame::StyledPanel,
				QFrame::Shadow	    shadow = QFrame::Raised );

	/*! Virtual destructor */
	~MessageWidget() override;

	void setPallete( const QPalette& paletteArgument = QPalette{},
			 bool		 forceParameter	 = false );

	[[nodiscard]] QString text() const;

	void setText( const QString& text );

	[[nodiscard]] Type messageType() const;

	void setMessageType( Type type );
	void updateLayout();
	void createLayout();

	[[nodiscard]] int  bestContentHeight() const;
	[[nodiscard]] bool isCloseButtonVisible() const;

	void setCloseButtonVisible( bool show );
	void addAction( QAction* action );
	void removeAction( QAction* action );

signals:
	void messageWidgetClosed() const;

protected:
	[[nodiscard]] QSize sizeHint() const override;
	[[nodiscard]] QSize minimumSizeHint() const override;

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
	gsl::owner<QToolButton*> m_closeBtn;
	gsl::owner<QAction*>	 m_closeAction;
	gsl::owner<QGridLayout*> m_grid;
	gsl::owner<QLabel*>	 m_label;

	Type m_messageType;

	void setupWidgets();
	void setupConnections();
};

#endif	  // MESSAGEWIDGET_H
