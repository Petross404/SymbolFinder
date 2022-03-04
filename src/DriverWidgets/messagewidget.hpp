// <one line to give the program's name and a brief idea of what it does.>
// SPDX-FileCopyrightText: 2022 Πέτρος Σιλιγκούνας <petross404@gmail.com>
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef MESSAGEWIDGET_H
#define MESSAGEWIDGET_H

#include <qframe.h>

#include <gsl/pointers>

class QGridLayout;
class QLabel;
class QToolButton;
class QAction;
class QTimeLine;

/**
 * @todo write docs
 */
class MessageWidget: public QFrame
{
	Q_OBJECT
	Q_DISABLE_COPY_MOVE( MessageWidget )

public:
	enum Type {
		Information = 0,
		Warning,
		Error,
	};
	Q_ENUM( Type )

	/**
	 * Default constructor
	 */
	explicit MessageWidget( const QString& text,
				Type	       type   = Type::Information,
				QWidget*       parent = nullptr,
				QFrame::Shape  shape  = QFrame::StyledPanel,
				QFrame::Shadow shadow = QFrame::Raised );

	~MessageWidget() override;

	void setPallete();

	QString text() const;

	void setText( const QString& text );
	Type messageType() const;
	void setMessageType( Type type );
	void updateLayout();
	void createLayout();
	int  bestContentHeight() const;
	bool isCloseButtonVisible() const;
	void setCloseButtonVisible( bool show );
	void addAction( QAction* action );
	void removeAction( QAction* action );

protected:
	QSize sizeHint() const override;
	QSize minimumSizeHint() const override;

	/*!
	 * Re-implement this function to paint this widget.
	 * \param event is the event to be processed
	 */
	void paintEvent( QPaintEvent* event ) override;

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
