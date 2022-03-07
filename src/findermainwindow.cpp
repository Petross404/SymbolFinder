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
#include "UI/interface.hpp"
#include "nmdriver.hpp"
#include "scanner.hpp"
#include "ui_findermainwindow.h"

int constexpr milliseconds = 3000;

MainWindow::MainWindow( QWidget* parent )
	: QMainWindow{ parent }
	, m_scanner{ new Scanner{ "nm", this } }
	, m_ui{ new Interface{ m_scanner, this } }
{
	setCentralWidget( m_ui );

	setupWidgets();
	setupActions();
	setupConnections();
}

MainWindow::~MainWindow() = default;

void MainWindow::setupConnections()
{
	ConnectVerifier v;

	v = connect( m_ui->closeBtn,
		     &QPushButton::clicked,
		     m_ui->actionQuit,
		     &QAction::trigger,
		     Qt::UniqueConnection );

	v = connect( m_ui->searchBtn,
		     &QPushButton::clicked,
		     m_ui->actionScan,
		     &QAction::trigger,
		     Qt::UniqueConnection );

	v = connect( m_ui->actionScan,
		     &QAction::triggered,
		     m_scanner,
		     &Scanner::performScan,
		     Qt::UniqueConnection );

	v = connect( m_ui->actionQuit,
		     &QAction::triggered,
		     qApp,
		     &QApplication::quit,
		     Qt::UniqueConnection );

	v = connect( m_ui->actionAboutQt,
		     &QAction::triggered,
		     qApp,
		     &QApplication::aboutQt,
		     Qt::UniqueConnection );

	v = connect( m_ui->argumentsEdit,
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

	// Search button is enabled conditionally
	v = connect( m_ui->symbolEdit,
		     &SymbolLineEdit::enableSymbolSearch,
		     this,
		     &MainWindow::enableSymbolSearchSlot,
		     Qt::UniqueConnection );

	// TODO We call updateSymbolSlot AND setInvocationSlot with the new symbol. Why?
	v = connect( m_ui->symbolEdit,
		     &SymbolLineEdit::symbolChanged,
		     this,
		     &MainWindow::updateSymbolSlot );

	/*
	 * If the user clicked to edit the arguments, some
	 * actions should occur:
	 *
	 * A) Visually alter the QLineEdit that accepts the args
	 * B) Inform the Scanner instance that other args will
	 * be passed to it's nm/scanelf driver.
	 */

	v = connect( m_ui->advancedCheckBox,
		     &QCheckBox::toggled,
		     this,
		     &MainWindow::enableAdvancedLineEdit,
		     Qt::UniqueConnection );

	v = connect( m_ui->argumentsEdit,
		     &ArgsLineEdit::symbolManuallyChanged,
		     this,
		     &MainWindow::resetAdvancedArgumentsSlot,
		     Qt::UniqueConnection );

	v = connect( m_scanner,
		     &Scanner::argumentsUpdated,
		     this,
		     &MainWindow::updateAdvancedArgumentsSlot,
		     Qt::UniqueConnection );

	/*
	 * When a scan is active, block some widgets.
	 * Likewise, unblock when it's over.
	 */
	connect( m_scanner, &Scanner::scanStarted, this, &MainWindow::blockUISlot, Qt::UniqueConnection );

	connect( m_scanner,
		 &Scanner::scanFinished,
		 this,
		 &MainWindow::unblockUISlot,
		 Qt::UniqueConnection );
}

void MainWindow::setupActions()
{
	QMenu* fileMenu{ new QMenu{ tr( "&File" ), this } };
	fileMenu->addAction( m_ui->actionScan );

	// Start with the action grayed out.
	m_ui->actionScan->setEnabled( false );
	fileMenu->addSeparator();

	fileMenu->addAction( m_ui->actionQuit );
	menuBar()->addMenu( fileMenu );

	QMenu* helpMenu{ new QMenu{ tr( "Help" ), this } };
	helpMenu->addAction( m_ui->actionAboutQt );
	menuBar()->addMenu( helpMenu );
}

void MainWindow::setupWidgets()
{
	int argumentsSize = m_ui->argumentsEdit->text().size();
	setMinimumSize( QSize{ argumentsSize + 620, 450 } );

	/****** No need to be enabled until they are needed ******/
	bool b = m_ui->advancedCheckBox->isChecked();
	m_ui->argumentsEdit->setEnabled( b );
	hideStdErrorTab();
	m_ui->searchBtn->setEnabled( !m_ui->symbolEdit->text().isEmpty() );
	/**********************************************************/

	QString symbolName   = m_ui->symbolEdit->text();
	QString advancedArgs = m_scanner->invocation().join( ' ' );

	m_ui->argumentsEdit->setToolTip(
		tr( "Enter here any additional arguments. Do not edit the "
		    "symbol name here!" ) );
	if ( m_ui->argumentsEdit->text() != advancedArgs )
	{
		m_ui->argumentsEdit->setText( advancedArgs );
	}

	m_ui->argumentsEdit->setClearButtonEnabled( true );

	setWindowIcon( QIcon{ ":resources/pngegg.png" } );

	if ( !m_ui->scannersBox->count() )
	{
		m_ui->scannersBox->addItem( "nm" );
		m_ui->scannersBox->addItem( "scanelf" );
	}
}

void MainWindow::showStdErrorTab()
{
	m_ui->tabWidget->setTabEnabled( 1, true );
}

void MainWindow::hideStdErrorTab()
{
	m_ui->tabWidget->setTabEnabled( 1, false );
}

void MainWindow::enableSymbolSearchSlot( bool option )
{
	m_ui->actionScan->setEnabled( option );
	m_ui->searchBtn->setEnabled( option );
}

void MainWindow::enableAdvancedLineEdit( bool option )
{
	m_ui->argumentsEdit->setEnabled( option );
	if ( option ) { m_ui->argumentsEdit->setCursorPosition( 0 ); }
}

void MainWindow::updateStdErrorSlot()
{
	auto error = m_scanner->standardError();
	m_ui->textBrowserStdErr->setText( error );
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
	m_ui->argumentsEdit->setText( m_scanner->invocation().join( ' ' ) );
}

void MainWindow::unblockHelper( const QString& text )
{
	m_ui->advancedCheckBox->setEnabled( true );
	m_ui->advancedCheckBox->toggle();
	m_ui->argumentsEdit->setText( text );
	m_ui->argumentsEdit->setFocus();
	m_ui->argumentsEdit->setCursorPosition( 0 );

	// Signal any listener that the widget is unblocked.
	emit advancedArgumentssUnblocked();
}

void MainWindow::resetAdvancedArgumentsSlot()
{
	QString oldText = m_ui->argumentsEdit->text();

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
	ConnectVerifier v;
	v = connect( this,
		     &MainWindow::advancedArgumentssUnblocked,
		     messageWidget,
		     &MessageWidget::close );

	/*
	 * While the MessageWidget is active, let's disable the checkbox
	 * and the custom lineedit. This way the user can't interact with
	 * these elements and focus on the warning. Also, show the warning
	 * on the statusBar too.
	 */
	m_ui->advancedCheckBox->setEnabled( false );
	m_ui->buttonsGrid->replaceWidget( m_ui->argumentsEdit, messageWidget );
	statusBar()->showMessage( message, milliseconds );

	/*
	 * Toggle the "Advanced Arguments" checkbox so a chain reaction of the
	 * connections can take place.
	 */
	m_ui->advancedCheckBox->toggle();

	// Fire up a timer to countdown until the widget is "unblocked" again.
	QTimer::singleShot( milliseconds,
			    std::bind( &MainWindow::unblockHelper, this, oldText ) );
}

void MainWindow::setInvocationSlot( const QString& advancedArgs )
{
	m_scanner->setInvocation( advancedArgs );
}

void MainWindow::blockUISlot()
{
	m_ui->buttonsGroup->setEnabled( false );
	setWindowTitle( tr( "Searching" ) );
}

void MainWindow::unblockUISlot()
{
	m_ui->buttonsGroup->setEnabled( true );
	setWindowTitle( qAppName() );
}
