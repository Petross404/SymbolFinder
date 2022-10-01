#include "ui_p.hpp"

#include <qaction.h>	       // for QAction
#include <qapplication.h>      // for QApplication
#include <qcheckbox.h>	       // for QCheckBox
#include <qgridlayout.h>       // for QGridLayout
#include <qgroupbox.h>	       // for QGroupBox
#include <qicon.h>	       // for QIcon
#include <qnamespace.h>	       // for UniqueCon...
#include <qobject.h>	       // for QObject
#include <qobjectdefs.h>       // for QMetaObje...
#include <qpushbutton.h>       // for QPushButton
#include <qstring.h>	       // for QString
#include <qstringliteral.h>    // for QStringLi...
#include <qtabwidget.h>	       // for QTabWidget
#include <qtextedit.h>	       // for QTextEdit

#include <type_traits>	  // for enable_if...

#include "../../../../ConnectVerifier/connectverifier.hpp"    // for ConnectVe...
#include "../../../../DriverWidgets/argumentslineedit.hpp"    // for Arguments...
#include "../../../../DriverWidgets/pluginscombobox.hpp"      // for PluginsCo...
#include "../../../../DriverWidgets/symbollineedit.hpp"	      // for SymbolLin...
#include "../ui.hpp"					      // for Interface

constexpr int btnMinWidth = 150;

InterfacePrivate::InterfacePrivate( Ui::Interface* pi )
	: q_ptr{ pi }
	, m_gridLayout{ gsl::make_not_null( new QGridLayout{ pi } ) }
	, m_buttonsGrid{ gsl::make_not_null( new QGridLayout{ pi } ) }
	, m_tabsGrid{ gsl::make_not_null( new QGridLayout{ pi } ) }
	, m_buttonsGroup{ gsl::make_not_null(
		  new QGroupBox{ "Symbol name and options", pi } ) }
	, m_tabsGroup{ gsl::make_not_null( new QGroupBox{ "Output", pi } ) }
	, m_closeBtn{ gsl::make_not_null( new QPushButton{
		  QIcon::fromTheme( "application-exit" ), "&Close", pi } ) }
	, m_searchBtn{ gsl::make_not_null( new QPushButton{
		  QIcon::fromTheme( "edit-find" ), "&Search", pi } ) }
	, m_resetArgsBtn{ gsl::make_not_null( new QPushButton{
		  QIcon::fromTheme( "view-refresh" ), "&Reset", pi } ) }
	, m_advancedCheckBox{ gsl::make_not_null(
		  new QCheckBox{ "Advanced arguments", pi } ) }
	, m_scannersBox{ gsl::make_not_null( new PluginsComboBox{ pi } ) }
	, m_symbolEdit{ gsl::make_not_null( new SymbolLineEdit{ pi } ) }
	, m_argumentsEdit{ gsl::make_not_null( new ArgumentsLineEdit{ pi } ) }
	, m_tabWidget{ gsl::make_not_null( new QTabWidget{ pi } ) }
	, m_textEditStdOut{ gsl::make_not_null( new QTextEdit{ pi } ) }
	, m_textEditStdErr{ gsl::make_not_null( new QTextEdit{ pi } ) }
	, m_actionScan{ gsl::make_not_null(
		  new QAction{ QIcon::fromTheme( QStringLiteral( "edit-find" ) ),
			       QStringLiteral( "Scan" ),
			       pi } ) }
	, m_actionQuit{ gsl::make_not_null( new QAction{
		  QIcon::fromTheme( QStringLiteral( "application-exit" ) ),
		  QStringLiteral( "&Quit" ),
		  pi } ) }
	, m_actionAboutQt{ gsl::make_not_null(
		  new QAction{ QIcon::fromTheme( QStringLiteral( "help-about" ) ),
			       QStringLiteral( "About Qt" ),
			       pi } ) }
{
	Q_Q( Ui::Interface );

	q->setLayout( m_gridLayout );

	// Set size
	q->setMinimumWidth( 850 );
	q->setMinimumHeight( 400 );

	m_closeBtn->setMinimumWidth( btnMinWidth );
	m_searchBtn->setMinimumWidth( btnMinWidth );
	m_resetArgsBtn->setMinimumWidth( btnMinWidth );

	m_gridLayout->addWidget( m_buttonsGroup, 0, 0 );
	m_gridLayout->addWidget( m_tabsGroup, 1, 0 );

	m_buttonsGroup->setLayout( m_buttonsGrid );
	m_tabsGroup->setLayout( m_tabsGrid );

	m_buttonsGrid->addWidget( m_scannersBox, 0, 0 );
	m_buttonsGrid->addWidget( m_symbolEdit, 0, 1 );
	m_buttonsGrid->addWidget( m_searchBtn, 0, 2 );
	m_buttonsGrid->addWidget( m_closeBtn, 0, 3 );
	m_buttonsGrid->addWidget( m_advancedCheckBox, 1, 0 );
	m_buttonsGrid->addWidget( m_argumentsEdit, 1, 1, 1, 2 );
	m_buttonsGrid->addWidget( m_resetArgsBtn, 1, 3 );

	m_tabsGrid->addWidget( m_tabWidget, 0, 0 );
	m_textEditStdOut->setReadOnly( true );
	m_tabWidget->insertTab( 0, m_textEditStdOut, QObject::tr( "Standard Output " ) );
	m_textEditStdErr->setReadOnly( true );
	m_tabWidget->insertTab( 1, m_textEditStdErr, QObject::tr( "Standard Error " ) );

	m_tabWidget->setTabToolTip( 0, QObject::tr( "Standard output is redirected here" ) );
	m_tabWidget->setTabToolTip(
		1,
		QObject::tr( "Standard error is redirected here. The tab is "
			     "enabled when there is an actual error to print" ) );

	setupConnections();
}

InterfacePrivate::~InterfacePrivate() = default;

void InterfacePrivate::resizeLineEditWidgets( int w ) const
{
	m_argumentsEdit->setMinimumWidth( w );
}

void InterfacePrivate::setupConnections()
{
	Q_Q( Ui::Interface );

	ConnectVerifier v;

	v = QObject::connect( m_closeBtn,
			      &QPushButton::clicked,
			      m_actionQuit,
			      &QAction::trigger,
			      Qt::UniqueConnection );

	v = QObject::connect( m_searchBtn,
			      &QPushButton::clicked,
			      m_actionScan,
			      &QAction::trigger,
			      Qt::UniqueConnection );

	v = QObject::connect( m_actionScan,
			      &QAction::triggered,
			      q,
			      &Ui::Interface::startScanning,
			      Qt::UniqueConnection );

	v = QObject::connect( m_actionQuit,
			      &QAction::triggered,
			      qApp,
			      &QApplication::quit,
			      Qt::UniqueConnection );

	v = QObject::connect( m_actionAboutQt,
			      &QAction::triggered,
			      qApp,
			      &QApplication::aboutQt,
			      Qt::UniqueConnection );
}
