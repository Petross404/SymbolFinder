// <one line to give the program's name and a brief idea of what it does.>
// SPDX-FileCopyrightText: 2022 Πέτρος Σιλιγκούνας <petross404@gmail.com>
// SPDX-License-Identifier: GPL-3.0-or-later

#include "messagewidget.hpp"

#include <qapplication.h>    // for QApplication, qApp
#include <qcolor.h>	     // for QColor
#include <qcoreevent.h>	     // for QEvent, QEvent::Pare...
#include <qlabel.h>	     // for QLabel
#include <qmargins.h>	     // for operator+, QMargins
#include <qpainter.h>	     // for QPainter, QPainter::...
#include <qpalette.h>	     // for QPalette, QPalette::...
#include <qpen.h>	     // for QPen
#include <qrect.h>	     // for QRect
#include <qtoolbutton.h>     // for QToolButton
#include <qwidget.h>	     // for QWidget

#include "implementation/messagewidget_p.h"	   // for MessageWidgetPrivate
#include "implementation/messagewidgettype.hpp"	   // for MessageType, Message...
class QCloseEvent;				   // lines 27-27
class QPaintEvent;				   // lines 28-28

MessageWidget::MessageWidget( const std::string_view  text,
			      std::optional<QWidget*> parent,
			      MessageType::Type	      type,
			      QFrame::Shape	      shape,
			      QFrame::Shadow	      shadow )
	: QFrame{ parent.value_or( nullptr ) }
	, d_ptr{ new MessageWidgetPrivate{ this, text, type } }
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

MessageWidget::~MessageWidget() { delete d_ptr; }

void MessageWidget::setPallete( const QPalette& paletteArgument, bool forceParameter )
{
	Q_D( const MessageWidget );
	d->setPallete( paletteArgument, forceParameter );

	QFrame::setPalette( d->m_label->palette() );
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

QString MessageWidget::text() const
{
	Q_D( const MessageWidget );

	return d->m_label->text();
}

void MessageWidget::setText( const QString& text )
{
	Q_D( MessageWidget );

	d->m_label->setText( text );
}

bool MessageWidget::isCloseButtonVisible() const
{
	Q_D( const MessageWidget );

	return d->m_closeBtn->isVisible();
}

void MessageWidget::setCloseButtonVisible( bool show )
{
	Q_D( MessageWidget );

	d->m_closeBtn->setVisible( show );
}

MessageType::Type MessageWidget::messageType() const
{
	Q_D( const MessageWidget );

	return d->m_messageType;
}

void MessageWidget::setMessageType( MessageType::Type type )
{
	Q_D( MessageWidget );

	d->m_messageType = type;
}

void MessageWidget::updateLayout()
{
	Q_D( MessageWidget );

	d->createLayout();
}

void MessageWidget::createLayout()
{
	Q_D( MessageWidget );

	d->createLayout();
}

int MessageWidget::bestContentHeight() const
{
	Q_D( const MessageWidget );

	return d->bestContentHeight();
}

void MessageWidget::setupWidgets()
{
	Q_D( MessageWidget );

	d->setupWidgets();
}

void MessageWidget::setupConnections()
{
	Q_D( MessageWidget );

	d->setupConnections();
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
	Q_D( MessageWidget );
	Q_UNUSED( event )

	QPainter painter{ this };

	constexpr float radius = 4 * 0.6;
	const QRect innerRect = rect().marginsRemoved( QMargins() + d->borderSize() / 2 );
	const QColor	color = palette().color( QPalette::Window );
	constexpr float alpha = 0.2;

	const QColor parentWindowColor{
		( parentWidget() != nullptr ? parentWidget()->palette() : qApp->palette() )
			.color( QPalette::Window ) };

	const int newRed =
		( color.red() * alpha ) + ( parentWindowColor.red() * ( 1 - alpha ) );
	const int newGreen = ( color.green() * alpha )
			     + ( parentWindowColor.green() * ( 1 - alpha ) );
	const int newBlue = ( color.blue() * alpha )
			    + ( parentWindowColor.blue() * ( 1 - alpha ) );

	painter.setPen( QPen( color, d->borderSize() ) );
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
	else if ( event->type() == QEvent::ParentChange ) { setPallete(); }

	return QFrame::event( event );
}
