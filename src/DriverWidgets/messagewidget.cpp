// <one line to give the program's name and a brief idea of what it does.>
// SPDX-FileCopyrightText: 2022 Πέτρος Σιλιγκούνας <petross404@gmail.com>
// SPDX-License-Identifier: GPL-3.0-or-later

#include "messagewidget.hpp"

#include <qcoreevent.h>	    // for QEvent, QEvent::Pare...
#include <qlabel.h>	    // for QLabel
#include <qpalette.h>	    // for QPalette
#include <qtoolbutton.h>    // for QToolButton

#include "implementation/messagewidget_p.hpp"	   // for MessageWidgetPrivate
#include "implementation/messagewidgettype.hpp"	   // for MessageType::Type
class QCloseEvent;				   // lines 21-21
class QPaintEvent;				   // lines 22-22

MessageWidget::MessageWidget( const std::string_view	       text,
			      std::optional<QWidget*>	       parent,
			      std::optional<MessageType::Type> type,
			      std::optional<QFrame::Shape>     shape,
			      std::optional<QFrame::Shadow>    shadow )
	: QFrame{ parent.value_or( nullptr ) }
	, d_ptr{ std::make_unique<MessageWidgetPrivate>( this, text, type ) }
{
	setFrameShape( shape.value_or( QFrame::Shape::StyledPanel ) );
	setFrameShadow( shadow.value_or( QFrame::Shadow::Raised ) );
	createLayout();
	setPallete();
	ensurePolished();
	setupWidgets();
	setupConnections();
	update();
}

MessageWidget::~MessageWidget() = default;

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

	d->handlePaintEvent();
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
