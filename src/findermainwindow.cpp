#include "findermainwindow.hpp"

#include <qdebug.h>
#include <qmessagebox.h>
#include <qtimer.h>

#include <chrono>
#include <functional>

#include "ConnectVerifier/connectverifier.hpp"
#include "DriverWidgets/argumentslineedit.hpp"
#include "DriverWidgets/messagewidget.hpp"
#include "DriverWidgets/symbollineedit.hpp"
#include "nmdriver.hpp"
#include "scanner.hpp"
#include "ui_findermainwindow.h"

int constexpr milliseconds = 3000;

MainWindow::MainWindow( QWidget* parent )
	: QMainWindow( parent )
	, m_ui( std::make_unique<Ui::MainWindow>() )
	, m_scanner{ new Scanner{ "nm", this } }
	, m_lineEditSymbol{ new SymbolLineEdit{ this } }
	, m_lineEditDefaultArgs{ new ArgsLineEdit{ m_scanner->invocation().join( ' ' ),
						   m_scanner->driver()->stopString(),
						   this } }
{
	m_ui->setupUi( this );

	initializeScanner();
	setupWidgets();
	setupConnections();
}

MainWindow::~MainWindow() = default;

void MainWindow::setupConnections()
{
	ConnectVerifier v;

	v = connect( m_ui->actionQuit,
		     &QAction::triggered,
		     qApp,
		     &QApplication::quit,
		     Qt::UniqueConnection );

	v = connect( m_lineEditDefaultArgs,
		     &QLineEdit::textEdited,
		     this,
		     &MainWindow::setInvocationSlot,
		     Qt::UniqueConnection );

	v = connect( m_scanner,
		     &Scanner::readyReadStandardError,
		     this,
		     &MainWindow::showStdErrorTab );

	v = connect( m_scanner,
		     &Scanner::readyReadStandardOutput,
		     this,
		     &MainWindow::updateStdOutputSlot );

	v = connect( m_scanner,
		     &Scanner::readyReadStandardError,
		     this,
		     &MainWindow::updateStdErrorSlot );

	v = connect( m_lineEditSymbol, &QLineEdit::textEdited, this, &MainWindow::updateSymbolSlot );

	/**
	 * If the user clicked to edit the arguments, some
	 * actions should occur:
	 *
	 * A) Visually alter the QLineEdit that accepts the args
	 * B) Inform the Scanner instance that other args will
	 * be passed to it's nm/scanelf driver.
	 */

	v = connect( m_ui->checkBox,
		     &QCheckBox::toggled,
		     this,
		     &MainWindow::enableAdvancedLineEdit,
		     Qt::UniqueConnection );

	v = connect( m_lineEditDefaultArgs,
		     &ArgsLineEdit::symbolManuallyChanged,
		     this,
		     &MainWindow::unblockAdvancedArgumentsSlot );

	v = connect( m_lineEditDefaultArgs,
		     &QLineEdit::textEdited,
		     this,
		     &MainWindow::setInvocationSlot );

	v = connect( m_scanner,
		     &Scanner::argumentsUpdated,
		     this,
		     &MainWindow::updateAdvancedArgumentsSlot,
		     Qt::UniqueConnection );
}

void MainWindow::setupWidgets()
{
	/****** No need to be enabled until they are needed ******/
	bool b = m_ui->checkBox->isChecked();
	m_lineEditDefaultArgs->setEnabled( b );
	hideStdErrorTab();
	m_ui->pbtnSearch->setEnabled( !m_lineEditSymbol->text().isEmpty() );
	/**********************************************************/

	m_ui->gridLayout_3->addWidget( m_lineEditSymbol, 2, 2 );
	m_ui->gridLayout_3->addWidget( m_lineEditDefaultArgs, 3, 1 );
	QString symbolName   = m_lineEditSymbol->text();
	QString advancedArgs = m_scanner->invocation().join( ' ' );

	m_lineEditDefaultArgs->setToolTip(
		tr( "Enter here any additional arguments. Do not edit the "
		    "symbol name here!" ) );
	if ( m_lineEditDefaultArgs->text() != advancedArgs )
	{
		m_lineEditDefaultArgs->setText( advancedArgs );
	}

	m_lineEditSymbol->setClearButtonEnabled( true );

	m_ui->tabWidget->setTabText( 0, tr( "Standard Output" ) );
	m_ui->tabWidget->setTabText( 1, tr( "Standard Error" ) );

	m_ui->tabWidget->setTabToolTip( 0, tr( "Standard output is redirected here" ) );
	m_ui->tabWidget->setTabToolTip(
		1,
		tr( QString::fromLatin1(
			    "Standard error is redirected here. The tab is "
			    "enabled when there is an actual error to print" )
			    .toLatin1()
			    .data() ) );

	setWindowIcon( QIcon{ ":resources/pngegg.png" } );

	if ( !m_ui->comboBoxDrivers->count() )
	{
		m_ui->comboBoxDrivers->addItem( "nm" );
		m_ui->comboBoxDrivers->addItem( "scanelf" );
	}

	m_ui->textBrowserStdOut->setTextBackgroundColor(
		QColor{ Qt::GlobalColor::black } );
	m_ui->textBrowserStdError->setTextBackgroundColor(
		QColor{ Qt::GlobalColor::black } );
}

void MainWindow::showStdErrorTab()
{
	m_ui->tabWidget->setTabEnabled( 1, true );
}

void MainWindow::hideStdErrorTab()
{
	m_ui->tabWidget->setTabEnabled( 1, false );
}

void MainWindow::enableAdvancedLineEdit( bool option )
{
	m_lineEditDefaultArgs->setEnabled( option );
	if ( option ) { m_lineEditDefaultArgs->setCursorPosition( 0 ); }
}


void MainWindow::updateStdErrorSlot()
{
	auto error = m_scanner->standardError();
	m_ui->textBrowserStdError->setText( error );
}

void MainWindow::updateStdOutputSlot()
{
	auto output = m_scanner->standardOut();
	m_ui->textBrowserStdOut->setText( output );
}

void MainWindow::updateSymbolSlot( const QString& symbol )
{
	m_scanner->setSymbolName( symbol );
}

void MainWindow::updateAdvancedArgumentsSlot()
{
	m_lineEditDefaultArgs->setText( m_scanner->invocation().join( ' ' ) );
}

void MainWindow::unblockHelper( const QString& text )
{
	m_ui->checkBox->toggle();
	m_lineEditDefaultArgs->setText( text );
	m_lineEditDefaultArgs->setFocus();
	m_lineEditDefaultArgs->setCursorPosition( 1 );

	// Signal any listener that the widget is unblocked.
	emit advancedArgumentssUnblocked();
}

void MainWindow::unblockAdvancedArgumentsSlot()
{
	QString oldText = m_lineEditDefaultArgs->text();

	/*
	 * The name of the symbol should be altered only in the relevant widget.
	 * This is the intended behavior since otherwise the program would infinitely alter
	 * the arguments which would trigger another signal to alter them and back again.
	 *
	 * After showing a warning widget with the message to the user, we need to signal
	 * this widget when to close and re-enable the advanced argument's QLineEdit.
	 */

	QString message{ tr( "Do not edit the symbol name in this widget." ) };
	gsl::owner<MessageWidget*> messageWidget{
		new MessageWidget{ message, MessageWidget::Type::Error, this } };

	// Close the MessageWidget as soon as the lineedit is enabled again.
	connect( this,
		 &MainWindow::advancedArgumentssUnblocked,
		 messageWidget,
		 &MessageWidget::close,
		 Qt::UniqueConnection );

	m_ui->gridLayout_3->addWidget( messageWidget, 3, 2, 1, 2, Qt::AlignCenter );

	statusBar()->showMessage( message,
				  std::chrono::milliseconds( milliseconds ).count() );

	/*
	 * Toggle the "Advanced Arguments" checkbox so a chain reaction of the
	 * connections can take place.
	 *
	 * The if(..) isn't really needed here since the signal that connects to
	 * this slot can't be triggered when the checkbox isn't enabled (= the
	 * QLineEdit is disabled). But it's better to be safe than sorry.
	 */
	if ( Q_UNLIKELY( m_ui->checkBox->isChecked() ) )
	{
		m_ui->checkBox->toggle();
	}

	// Fire up a timer to countdown until the widget is "unblocked" again.
	QTimer::singleShot( std::chrono::milliseconds( milliseconds ),
			    std::bind( &MainWindow::unblockHelper, this, oldText ) );
}

void MainWindow::setInvocationSlot( const QString& advancedArgs )
{
	m_scanner->setInvocation( advancedArgs );
}
