// <one line to give the program's name and a brief idea of what it does.>
// SPDX-FileCopyrightText: 2022 Πέτρος Σιλιγκούνας <petross404@gmail.com>
// SPDX-License-Identifier: GPL-3.0-or-later

#include "messagewidget.hpp"

#include <qaction.h>	     // for QAction
#include <qapplication.h>    // for QApplication, qApp
#include <qcolor.h>	     // for QColor
#include <qcoreevent.h>	     // for QEvent, QEvent::ParentChange, QEvent::Polish
#include <qgridlayout.h>     // for QGridLayout
#include <qlabel.h>	     // for QLabel
#include <qlayout.h>	     // for QLayout
#include <qmargins.h>	     // for operator+, QMargins
#include <qnamespace.h>	     // for UniqueConnection, TextBrowserInteraction
#include <qpainter.h>	     // for QPainter, QPainter::Antialiasing
#include <qpalette.h>	    // for QPalette, QPalette::Window, QPalette::Wind...
#include <qpen.h>	    // for QPen
#include <qrect.h>	    // for QRect
#include <qsizepolicy.h>    // for QSizePolicy, QSizePolicy::Fixed, QSizePoli...
#include <qstyle.h>	    // for QStyle, QStyle::SP_DialogCloseButton
#include <qstyleoption.h>    // for QStyleOptionFrame
#include <qtoolbutton.h>     // for QToolButton
#include <qwidget.h>	     // for QWidget
class QCloseEvent;
class QPaintEvent;

constexpr int borderSize = 2;

MessageWidget::MessageWidget( const QString& text,
			      Type	     type,
			      QWidget*	     parent,
			      QFrame::Shape  shape,
			      QFrame::Shadow shadow )
	: QFrame{ parent }
	, m_closeBtn{ new QToolButton{ this } }
	, m_closeAction{ new QAction{ this } }
	, m_grid{ new QGridLayout{ this } }
	, m_label{ new QLabel{ text, this } }
	, m_messageType{ type }
{
	setFrameShape( shape );
	setFrameShadow( shadow );
	createLayout();
	setPallete();
	ensurePolished();
	setupWidgets();
	setupConnections();
	update();
}

MessageWidget::~MessageWidget() = default;

void MessageWidget::setPallete()
{
	QColor bgBaseColor;

	switch ( m_messageType )
	{
		case MessageWidget::Information:
			bgBaseColor.setRgb( 61, 174, 233 );
			break;
		case MessageWidget::Warning:
			bgBaseColor.setRgb( 246, 116, 0 );
			break;
		case MessageWidget::Error:
			bgBaseColor.setRgb( 218, 68, 83 );
			break;
		default: break;
	}

	QPalette palette = this->palette();
	palette.setColor( QPalette::Window, bgBaseColor );

	const QColor parentTextColor =
		( this->parentWidget() ? this->parentWidget()->palette()
				       : qApp->palette() )
			.color( QPalette::WindowText );

	m_label->setPalette( palette );
	QFrame::setPalette( palette );
}

void MessageWidget::addAction( QAction* action )
{
	QFrame::addAction( action );
	updateLayout();
}

void MessageWidget::removeAction( QAction* action )
{
	QFrame::removeAction( action );
	updateLayout();
}

QString MessageWidget::text() const { return m_label->text(); }

void MessageWidget::setText( const QString& text )
{
	m_label->setText( text );
	updateGeometry();
}

bool MessageWidget::isCloseButtonVisible() const
{
	return m_closeBtn->isVisible();
}

void MessageWidget::setCloseButtonVisible( bool show )
{
	m_closeBtn->setVisible( show );
	updateGeometry();
}

MessageWidget::Type MessageWidget::messageType() const { return m_messageType; }

void MessageWidget::setMessageType( MessageWidget::Type type )
{
	m_messageType = type;
	setPallete();
}

void MessageWidget::updateLayout() { createLayout(); }

void MessageWidget::createLayout()
{
	m_grid->addWidget( m_label, 0, 0 );
	m_grid->addWidget( m_closeBtn, 0, 1 );
	this->setLayout( m_grid );

	layout()->setContentsMargins( layout()->contentsMargins() + borderSize );

	if ( isVisible() )    // Call to virtual method 'MessageWidget::sizeHint' during construction bypasses virtual dispatch
	{
		setFixedHeight( MessageWidget::sizeHint().height() );
	}

	updateGeometry();
}

int MessageWidget::bestContentHeight() const
{
	int height = heightForWidth( width() );
	if ( height == -1 ) { height = sizeHint().height(); }

	return height;
}

void MessageWidget::setupWidgets()
{
	m_label->setSizePolicy( QSizePolicy::Preferred, QSizePolicy::Fixed );
	m_label->setTextInteractionFlags( Qt::TextBrowserInteraction );

	m_closeAction->setText( tr( "&Close", "@action:button" ) );
	QStyleOptionFrame opt;
	opt.initFrom( this );
	m_closeAction->setIcon(
		style()->standardIcon( QStyle::SP_DialogCloseButton, &opt, this ) );

	m_closeBtn->setAutoRaise( true );
	m_closeBtn->setDefaultAction( m_closeAction );
}

void MessageWidget::setupConnections()
{
	connect( m_closeAction, &QAction::triggered, this, &MessageWidget::hide, Qt::UniqueConnection );

	connect( qApp,
		 &QApplication::paletteChanged,
		 this,
		 &MessageWidget::setPallete,
		 Qt::UniqueConnection );
}

QSize MessageWidget::sizeHint() const
{
	ensurePolished();
	return QFrame::sizeHint();
}

QSize MessageWidget::minimumSizeHint() const
{
	ensurePolished();
	return QFrame::minimumSizeHint();
}

void MessageWidget::paintEvent( QPaintEvent* event )
{
	Q_UNUSED( event )

	QPainter painter{ this };

	constexpr float radius = 4 * 0.6;
	const QRect innerRect = rect().marginsRemoved( QMargins() + borderSize / 2 );
	const QColor	color = palette().color( QPalette::Window );
	constexpr float alpha = 0.2;

	const QColor parentWindowColor{ ( parentWidget() != nullptr
						  ? parentWidget()->palette()
						  : qApp->palette() )
						.color( QPalette::Window ) };
	const int    newRed = ( color.red() * alpha )
			   + ( parentWindowColor.red() * ( 1 - alpha ) );
	const int newGreen = ( color.green() * alpha )
			     + ( parentWindowColor.green() * ( 1 - alpha ) );
	const int newBlue = ( color.blue() * alpha )
			    + ( parentWindowColor.blue() * ( 1 - alpha ) );

	painter.setPen( QPen( color, borderSize ) );
	painter.setBrush( QColor( newRed, newGreen, newBlue ) );
	painter.setRenderHint( QPainter::Antialiasing );
	painter.drawRoundedRect( innerRect, radius, radius );
}

void MessageWidget::closeEvent( QCloseEvent* event )
{
	emit messageWidgetClosed();
	QFrame::closeEvent( event );
}

bool MessageWidget::event( QEvent* event )
{
	if ( event->type() == QEvent::Polish && layout() == nullptr )
	{
		createLayout();
	}
	else if ( event->type() == QEvent::Show )
	{
		setFixedHeight( bestContentHeight() );
	}
	else if ( event->type() == QEvent::ParentChange )
	{
		setPallete();
	}

	return QFrame::event( event );
}
