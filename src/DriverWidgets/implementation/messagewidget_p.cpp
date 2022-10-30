#include "messagewidget_p.hpp"

#include <qaction.h>	     // for QAction
#include <qapplication.h>    // for QApplication, qApp
#include <qcolor.h>	     // for QColor
#include <qgridlayout.h>     // for QGridLayout
#include <qlabel.h>	     // for QLabel
#include <qlayout.h>	     // for QLayout
#include <qmargins.h>	     // for operator+, QMar...
#include <qnamespace.h>	     // for UniqueConnection
#include <qobject.h>	     // for QObject
#include <qpainter.h>	     // for QPainter, QPain...
#include <qpalette.h>	     // for QPalette, QPale...
#include <qpen.h>	     // for QPen
#include <qrect.h>	     // for QRect
#include <qsize.h>	     // for QSize
#include <qsizepolicy.h>     // for QSizePolicy
#include <qstyle.h>	     // for QStyle, QStyle:...
#include <qstyleoption.h>    // for QStyleOptionFrame
#include <qtoolbutton.h>     // for QToolButton
#include <qwidget.h>	     // for QWidget

#include <functional>	  // for _Bind_helper<>:...
#include <type_traits>	  // for enable_if<>::type
#include <utility>	  // for as_const

#include "../../ConnectVerifier/connectverifier.hpp"	// for ConnectVerifier
#include "../../Helper/string.hpp"			// for toqstring
#include "../messagewidget.hpp"				// for MessageWidget
#include "messagewidgettype.hpp"			// for MessageType::Type

constexpr int borderSz = 2;

MessageWidgetPrivate::MessageWidgetPrivate( MessageWidget*	   messageWidget,
					    const std::string_view text,
					    std::optional<MessageType::Type> type )
	: q_ptr{ messageWidget }
	, m_closeBtn{ gsl::make_not_null( new QToolButton{ messageWidget } ) }
	, m_closeAction{ gsl::make_not_null( new QAction{ messageWidget } ) }
	, m_gridLayout{ gsl::make_not_null( new QGridLayout{ messageWidget } ) }
	, m_label{ gsl::make_not_null( new QLabel{ string::toqstring( text ), messageWidget } ) }
	, m_messageType{ type.value_or( MessageType::Type::Information ) }
{
	setupWidgets();
	setupConnections();
}

MessageWidgetPrivate::~MessageWidgetPrivate() = default;

void MessageWidgetPrivate::setPallete( const QPalette& paletteArgument,
				       const bool      forceParameter ) const
{
	Q_Q( const MessageWidget );

	QColor	 bgBaseColor;
	QPalette palette;

	if ( !forceParameter )
	{
		switch ( m_messageType )
		{
			case MessageType::Type::Information:
				bgBaseColor.setRgb( 61, 174, 233 );
				break;
			case MessageType::Type::Warning:
				bgBaseColor.setRgb( 246, 116, 0 );
				break;
			case MessageType::Type::Error:
				bgBaseColor.setRgb( 218, 68, 83 );
				break;
			default: break;
		}

		palette = q->palette();
		palette.setColor( QPalette::Window, bgBaseColor );
	}
	else { palette = paletteArgument; }

	const QColor parentTextColor{
		( q->parentWidget() ? q->parentWidget()->palette() : qApp->palette() )
			.color( QPalette::WindowText ) };

	m_label->setPalette( palette );
}

void MessageWidgetPrivate::updateLayout() { createLayout(); }

void MessageWidgetPrivate::createLayout()
{
	Q_Q( MessageWidget );

	m_gridLayout->addWidget( m_label, 0, 0 );
	m_gridLayout->addWidget( m_closeBtn, 0, 1 );
	q->setLayout( m_gridLayout );

	q->layout()->setContentsMargins( q->layout()->contentsMargins() + borderSize() );

	if ( q->isVisible() ) { q->setFixedHeight( q->sizeHint().height() ); }

	q->updateGeometry();
}

int MessageWidgetPrivate::bestContentHeight() const
{
	Q_Q( const MessageWidget );

	int height = q->heightForWidth( q->width() );
	if ( height == -1 ) { height = q->sizeHint().height(); }

	return height;
}

QString MessageWidgetPrivate::text() const { return m_label->text(); }

void MessageWidgetPrivate::setText( const QString& text )
{
	Q_Q( MessageWidget );

	m_label->setText( text );
	q->updateGeometry();
}

void MessageWidgetPrivate::setupWidgets()
{
	Q_Q( MessageWidget );

	m_label->setSizePolicy( QSizePolicy::Preferred, QSizePolicy::Fixed );
	m_label->setTextInteractionFlags( Qt::TextBrowserInteraction );

	m_closeAction->setText( QObject::tr( "&Close", "@action:button" ) );
	QStyleOptionFrame opt;
	opt.initFrom( q );

	const QStyle* tstyle{ q->style() };
	m_closeAction->setIcon(
		tstyle->standardIcon( QStyle::SP_DialogCloseButton, &opt, q ) );

	m_closeBtn->setAutoRaise( true );
	m_closeBtn->setDefaultAction( m_closeAction );
}

void MessageWidgetPrivate::setupConnections()
{
	Q_Q( MessageWidget );

	ConnectVerifier v;

	QObject::connect( m_closeAction,
			  &QAction::triggered,
			  std::as_const( q ),
			  &MessageWidget::close,
			  Qt::UniqueConnection );

	v = QObject::connect(
		qApp,
		&QApplication::paletteChanged,
		q,
		std::bind( &MessageWidget::setPallete, q, std::placeholders::_1, true ),
		Qt::UniqueConnection );
}

void MessageWidgetPrivate::handlePaintEvent()
{
	Q_Q( MessageWidget );

	QPainter painter{ q };

	constexpr float radius = 4 * 0.6;
	const QRect innerRect = q->rect().marginsRemoved( QMargins{} + borderSize() / 2 );
	const QColor	color = q->palette().color( QPalette::Window );
	constexpr float alpha = 0.2;

	const QColor parentWindowColor{ ( q->parentWidget() != nullptr
						  ? q->parentWidget()->palette()
						  : qApp->palette() )
						.color( QPalette::Window ) };

	const int newRed =
		( color.red() * alpha ) + ( parentWindowColor.red() * ( 1 - alpha ) );
	const int newGreen = ( color.green() * alpha )
			     + ( parentWindowColor.green() * ( 1 - alpha ) );
	const int newBlue = ( color.blue() * alpha )
			    + ( parentWindowColor.blue() * ( 1 - alpha ) );

	painter.setPen( QPen( color, borderSize() ) );
	painter.setBrush( QColor( newRed, newGreen, newBlue ) );
	painter.setRenderHint( QPainter::Antialiasing );
	painter.drawRoundedRect( innerRect, radius, radius );
}

bool MessageWidgetPrivate::isCloseButtonVisible() const
{
	return m_closeBtn->isVisible();
}

void MessageWidgetPrivate::setCloseButtonVisible( bool show )
{
	Q_Q( MessageWidget );

	m_closeBtn->setVisible( show );
	q->updateGeometry();
}

int MessageWidgetPrivate::borderSize() const { return borderSz; }
