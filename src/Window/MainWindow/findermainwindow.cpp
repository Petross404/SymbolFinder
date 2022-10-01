/*
 * <one line to give the library's name and an idea of what it does.>
 * Copyright (C) 2022  <copyright holder> <email>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "findermainwindow.hpp"

#include <bits/chrono.h>
#include <qaction.h>
#include <qapplication.h>
#include <qbytearray.h>
#include <qchar.h>    // for QChar
#include <qcheckbox.h>
#include <qcoreapplication.h>
#include <qevent.h>
#include <qgridlayout.h>
#include <qgroupbox.h>
#include <qmessagebox.h>
#include <qnamespace.h>
#include <qpushbutton.h>
#include <qstatusbar.h>
#include <qstringliteral.h>
#include <qtabwidget.h>
#include <qtextedit.h>
#include <qtimer.h>

#include <algorithm>
#include <cctype>
#include <functional>
#include <string>
#include <vector>

#include "../../DriverWidgets/argumentslineedit.hpp"
#include "../../DriverWidgets/messagewidget.hpp"
#include "../../DriverWidgets/pluginscombobox.hpp"
#include "../../DriverWidgets/symbollineedit.hpp"
#include "../../Helper/string.hpp"
#include "../../Scanner/scanner.hpp"
#include "UI/ui.hpp"
#include "implementation/finderwindow_p.hpp"
#include "src/DriverWidgets/implementation/messagewidgettype.hpp"
#include "src/Scanner/interface/idriver.hpp"
#include "src/Scanner/interface/pluginmanageraliases.hpp"
class QWidget;	  // lines 60-60

constexpr std::chrono::milliseconds g_milliseconds{ 3000 };

constexpr QChar g_spaceChar{ ' ' };

FinderWindow::FinderWindow( std::optional<QWidget*> parent )
	: QMainWindow{ parent.value_or( nullptr ) }
	, d_ptr{ new FinderWindowPrivate{ this } }
	, m_ui{ gsl::make_strict_not_null( new Ui::Interface{ this } ) }
	, m_scanner{ gsl::make_strict_not_null( new Scanner{ this } ) }
{
	setCentralWidget( m_ui );

	setupWidgets();
	setupActions();
	setupConnections();
}

FinderWindow::~FinderWindow() { delete d_ptr; }

void FinderWindow::setupConnections()
{
	Q_D( FinderWindow );
	d->setupConnections();
}

void FinderWindow::setupActions()
{
	Q_D( FinderWindow );
	d->setupActions();
}

void FinderWindow::setupWidgets()
{
	Q_D( FinderWindow );
	d->setupWidgets();
}

void FinderWindow::showStdErrorTab()
{
	m_ui->tabWidget()->setTabEnabled( 1, true );
}

void FinderWindow::hideStdErrorTab()
{
	m_ui->tabWidget()->setTabEnabled( 1, false );
}

void FinderWindow::enableSymbolSearchSlot( bool option )
{
	m_ui->actionScan()->setEnabled( option );
	m_ui->searchBtn()->setEnabled( option );
}

void FinderWindow::enableAdvancedLineEdit( bool option )
{
	m_ui->argumentsEdit()->setEnabled( option );
	if ( option ) { m_ui->argumentsEdit()->setCursorPosition( 0 ); }
}

void FinderWindow::updateStdErrorSlot()
{
	QByteArray error = m_scanner->standardError();
	m_ui->textBrowserStdErr()->setText( error );
}

void FinderWindow::updateStdOutputSlot()
{
	QByteArray output = m_scanner->standardOut();
	m_ui->textBrowserStdOut()->setText( output );
}

void FinderWindow::updateSymbolSlot( const std::string_view symbol )
{
	m_scanner->setSymbolName( symbol );
}

void FinderWindow::updateAdvancedArgumentsSlot()
{
	std::string_view str{ string::join_string_list( m_scanner->invocation() ) };

	m_ui->argumentsEdit()->setText( string::toqstring( str ) );
}

void FinderWindow::resetAdvancedLineEditSlot()
{
	const QString oldText = m_ui->argumentsEdit()->text();

	/*
	 * The name of the symbol should be altered only in the relevant widget.
	 * This is the intended behavior since otherwise the program would infinitely alter
	 * the arguments which would trigger another signal to alter them and back again.
	 *
	 * After showing a warning widget with the message to the user, we need to signal
	 * this widget when to close and re-enable the advanced argument's QLineEdit.
	 */
	const std::string_view message{
		"Do not edit the symbol name in this widget." };

	gsl::owner<MessageWidget*> messageWidget{
		new MessageWidget{ message, this, MessageType::Type::Error } };

	messageWidget->setAttribute( Qt::WA_DeleteOnClose );

	/*
	 * While the MessageWidget is active, let's replace the checkbox
	 * and the custom lineedit. This way the user can't interact with
	 * these elements and focus on the warning. Also, show the warning
	 * on the statusBar as well.
	 */
	m_ui->advancedCheckBox()->setEnabled( false );
	m_ui->resetArgsBtn()->setEnabled( false );
	m_ui->buttonsGrid()->replaceWidget( m_ui->argumentsEdit(), messageWidget );

	statusBar()->showMessage( QString::fromUtf8( message.data(), message.size() ),
				  g_milliseconds.count() );

	/*
	 * Toggle the "Advanced Arguments" checkbox so a chain reaction of the
	 * connections can take place.
	 */
	m_ui->advancedCheckBox()->toggle();

	// Fire up a timer to countdown until the widget is "unblocked" again.
	QTimer::singleShot( g_milliseconds.count(), [this, oldText, messageWidget]() {
		m_ui->advancedCheckBox()->setEnabled( true );
		m_ui->resetArgsBtn()->setEnabled( true );
		m_ui->advancedCheckBox()->toggle();
		m_ui->argumentsEdit()->setText( oldText );

		m_ui->buttonsGrid()->replaceWidget( messageWidget, m_ui->argumentsEdit() );
		messageWidget->close();
	} );
}

void FinderWindow::driverInitalizedSlot( const std::string_view name )
{
	qApp->setApplicationName( qAppName() + string::toqstring( name ) );

	// Set the current symbol for the new driver
	const QString symbol{ m_ui->symbolEdit()->text() };

	// Enable widgets depending on driver
	m_ui->symbolEdit()->setEnabled( true );
	m_ui->searchBtn()->setEnabled( true );

	// Set the stop index
	StopIndex index{ m_scanner->stopIndexOfArguments() };
	m_ui->argumentsEdit()->setStopIndex( index );
}

void FinderWindow::resetAdvancedArgumentsSlot() { m_scanner->resetInvocation(); }

void FinderWindow::resetSymbolLineWarningSlot()
{
	const std::string message{ "Wrong symbol name" };

	gsl::owner<MessageWidget*> messageWidget{
		new MessageWidget{ message, this, MessageType::Type::Error } };

	messageWidget->setAttribute( Qt::WA_DeleteOnClose );

	m_ui->symbolEdit()->hide();
	m_ui->searchBtn()->setEnabled( false );
	m_ui->buttonsGrid()->replaceWidget( m_ui->symbolEdit(), messageWidget );

	QTimer::singleShot( g_milliseconds.count(), [this, messageWidget]() {
		m_ui->searchBtn()->setEnabled( true );
		m_ui->symbolEdit()->show();
		m_ui->buttonsGrid()->replaceWidget( messageWidget, m_ui->symbolEdit() );
		m_ui->symbolEdit()->clear();
		messageWidget->close();
	} );
}

void FinderWindow::setInvocationSlot( const QString& advancedArgs )
{
	m_scanner->setInvocation( string::tostring( advancedArgs ), std::nullopt );
}

void FinderWindow::resetScannerInstanceSlot( int index )
{
	std::string driverName{ m_ui->scannersBox()->itemText( index ).toStdString() };

	std::ranges::transform( driverName,
				driverName.begin(),
				[=]( unsigned char c ) -> unsigned char {
					// TODO convert tolower only the first char
					return std::tolower( c );
				} );

	m_scanner->reset( driverName );
}

void FinderWindow::scanStartedSlot()
{
	m_ui->buttonsGroup()->setEnabled( false );
	setWindowTitle( QStringLiteral( "Searching" ) );
}

void FinderWindow::scanFinishedSlot()
{
	m_ui->buttonsGroup()->setEnabled( true );
	setWindowTitle( qAppName() );

	// Update the output.
	updateStdOutputSlot();
	updateStdErrorSlot();
}

void FinderWindow::discoverPlugins()
{
	std::vector<PluginDesc> pd{ m_scanner->pluginDescription() };
	m_ui->scannersBox()->initScannerBox( pd );
}

void FinderWindow::closeEvent( QCloseEvent* event )
{
	if ( m_scanner->canQuit() )
	{
		const QString question{
			"Do you want to quit while still looking?" };
		const QString title{ "Still searching..." };

		auto ans{ QMessageBox::question( this,
						 title,
						 question,
						 QMessageBox::Yes | QMessageBox::No ) };

		if ( QMessageBox::Yes == ans ) { event->ignore(); }
		else { event->accept(); }
	}
}
