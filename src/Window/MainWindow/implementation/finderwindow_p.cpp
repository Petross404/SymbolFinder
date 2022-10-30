#include "finderwindow_p.hpp"

#include <qaction.h>
#include <qcheckbox.h>	  // for QCheckBox
#include <qcombobox.h>	  // for QComboBox
#include <qicon.h>	  // for QIcon
#include <qlineedit.h>	  // for QLineEdit
#include <qmenu.h>
#include <qmenubar.h>
#include <qnamespace.h>	       // for UniqueConnec...
#include <qobject.h>	       // for QObject
#include <qobjectdefs.h>       // for QMetaObject:...
#include <qpushbutton.h>       // for QPushButton
#include <qsize.h>	       // for QSize
#include <qstring.h>	       // for QString
#include <qstringliteral.h>    // for QStringLiteral

#include <gsl/pointers>	   // for not_null
#include <optional>	   // for optional

#include "../../../ConnectVerifier/connectverifier.hpp"	   // for ConnectVerifier
#include "../../../DriverWidgets/pluginscombobox.hpp"	   // for PluginsComboBox
#include "../../../DriverWidgets/symbollineedit.hpp"	   // for SymbolLineEdit
#include "../../../Scanner/scanner.hpp"			   // for Scanner
#include "../../MainWindow/UI/ui.hpp"			   // for not_null_owner
#include "../findermainwindow.hpp"			   // for FinderWindow
#include "src/DriverWidgets/argumentslineedit.hpp"	   // for ArgumentsLin...

FinderWindowPrivate::FinderWindowPrivate( FinderWindow* pfw )
	: q_ptr{ pfw }
{}

FinderWindowPrivate::~FinderWindowPrivate() = default;

void FinderWindowPrivate::setupActions()
{
	Q_Q( FinderWindow );

	QMenu* fileMenu{ new QMenu{ "&File", q } };
	fileMenu->addAction( q->m_ui->actionScan() );

	// Start with the action grayed out.
	q->m_ui->actionScan()->setEnabled( false );
	fileMenu->addSeparator();

	fileMenu->addAction( q->m_ui->actionQuit() );
	q->menuBar()->addMenu( fileMenu );

	QMenu* helpMenu{ new QMenu{ QStringLiteral( "Help" ), q } };
	helpMenu->addAction( q->m_ui->actionAboutQt() );
	q->menuBar()->addMenu( helpMenu );
}

void FinderWindowPrivate::setupConnections()
{
	Q_Q( FinderWindow );

	ConnectVerifier v;

	v = QObject::connect( q,
			      &FinderWindow::startScanner,
			      q->m_scanner,
			      &Scanner::performScanSlot,
			      Qt::UniqueConnection );

	v = QObject::connect( q->m_ui->argumentsEdit(),
			      &QLineEdit::textEdited,
			      q,
			      &FinderWindow::setInvocationSlot,
			      Qt::UniqueConnection );

	v = QObject::connect( q->m_ui->resetArgsBtn(),
			      &QPushButton::clicked,
			      q,
			      &FinderWindow::resetAdvancedArgumentsSlot,
			      Qt::UniqueConnection );

	v = QObject::connect( q->m_scanner,
			      &Scanner::readyReadStandardError,
			      q,
			      &FinderWindow::showStdErrorTab,
			      Qt::UniqueConnection );

	v = QObject::connect( q->m_scanner,
			      &Scanner::readyReadStandardOutput,
			      q,
			      &FinderWindow::updateStdOutputSlot,
			      Qt::UniqueConnection );

	v = QObject::connect( q->m_scanner,
			      &Scanner::readyReadStandardError,
			      q,
			      &FinderWindow::updateStdErrorSlot,
			      Qt::UniqueConnection );

	// When the symbol size changes, update the index that will block the cursor in ArgumentsLineEdit
	v = QObject::connect( q->m_scanner,
			      &Scanner::symbolSizeChanged,
			      q->m_ui->argumentsEdit(),
			      &ArgumentsLineEdit::symbolSizeChanged,
			      Qt::UniqueConnection );

	// Search button is enabled conditionally
	v = QObject::connect( q->m_ui->symbolEdit(),
			      &SymbolLineEdit::enableSymbolSearch,
			      q,
			      &FinderWindow::enableSymbolSearchSlot,
			      Qt::UniqueConnection );

	v = QObject::connect( q->m_ui->symbolEdit(),
			      &SymbolLineEdit::symbolChanged,
			      q,
			      &FinderWindow::updateSymbolSlot,
			      Qt::UniqueConnection );

	/*
	 * If the user clicked to edit the arguments, some
	 * actions should occur:
	 *
	 * A) Visually alter the QLineEdit that accepts the args
	 * B) Inform the Scanner instance that other args will
	 * be passed to it's nm/scanelf driver.
	 */

	v = QObject::connect( q->m_ui->advancedCheckBox(),
			      &QCheckBox::toggled,
			      q,
			      &FinderWindow::enableAdvancedLineEdit,
			      Qt::UniqueConnection );

	v = QObject::connect( q->m_ui->symbolEdit(),
			      &SymbolLineEdit::enableSymbolLineWarning,
			      q,
			      &FinderWindow::resetSymbolLineWarningSlot,
			      Qt::UniqueConnection );

	v = QObject::connect( q->m_ui->argumentsEdit(),
			      &ArgsLineEdit::symbolManuallyChanged,
			      q,
			      &FinderWindow::resetAdvancedLineEditSlot,
			      Qt::UniqueConnection );

	v = QObject::connect( q->m_scanner,
			      &Scanner::argumentsUpdated,
			      q,
			      &FinderWindow::updateAdvancedArgumentsSlot,
			      Qt::UniqueConnection );

	/*
	 * When a scan is active, block some widgets.
	 * Likewise, unblock when it's over.
	 */
	v = QObject::connect( q->m_scanner,
			      &Scanner::scanStarted,
			      q,
			      &FinderWindow::scanStartedSlot,
			      Qt::UniqueConnection );

	v = QObject::connect( q->m_scanner,
			      &Scanner::scanFinished,
			      q,
			      &FinderWindow::scanFinishedSlot,
			      Qt::UniqueConnection );

	v = QObject::connect( q->m_scanner,
			      &Scanner::driverInitialized,
			      q,
			      &FinderWindow::driverInitalizedSlot,
			      Qt::UniqueConnection );

	v = QObject::connect( q->m_ui->scannersBox(),
			      qOverload<int>( &QComboBox::currentIndexChanged ),
			      q,
			      &FinderWindow::resetScannerInstanceSlot,
			      Qt::UniqueConnection );
}

void FinderWindowPrivate::setupWidgets()
{
	Q_Q( FinderWindow );

	int argumentsSize = q->m_ui->argumentsEdit()->text().size();
	q->setMinimumSize( QSize{ argumentsSize + 620, 450 } );

	/****** No need to be enabled until they are needed ******/
	bool b = q->m_ui->advancedCheckBox()->isChecked();
	q->m_ui->argumentsEdit()->setEnabled( b );
	q->hideStdErrorTab();
	q->m_ui->searchBtn()->setEnabled( !q->m_ui->symbolEdit()->text().isEmpty() );
	q->m_ui->symbolEdit()->setEnabled( q->m_scanner->driver().has_value() );
	/*********************************************************/

	QString symbolName{ q->m_ui->symbolEdit()->text() };

	q->m_ui->argumentsEdit()->setClearButtonEnabled( true );
	q->setWindowIcon( QIcon{ QStringLiteral( ":resources/pngegg.png" ) } );

	q->discoverPlugins();
}
