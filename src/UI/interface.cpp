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

#include "interface.hpp"

#include <qcheckbox.h>
#include <qcombobox.h>
#include <qgridlayout.h>
#include <qgroupbox.h>
#include <qlabel.h>
#include <qmenubar.h>
#include <qpushbutton.h>
#include <qtabwidget.h>
#include <qtextbrowser.h>

#include "../DriverWidgets/argumentslineedit.hpp"
#include "../DriverWidgets/symbollineedit.hpp"
#include "../scanner.hpp"

Interface::Interface( Scanner* scanner, QWidget* parent )
	: QWidget{ parent }
	, gridLayout{ new QGridLayout{ this } }
	, buttonsGrid{ new QGridLayout{ this } }
	, tabsGrid{ new QGridLayout{ this } }
	, buttonsGroup{ new QGroupBox{ tr( "Symbol name and options" ), this } }
	, tabsGroup{ new QGroupBox{ tr( "Output" ), this } }
	, closeBtn{ new QPushButton{
		  QIcon::fromTheme( "application-exit" ), tr( "&Close" ), this } }
	, searchBtn{ new QPushButton{
		  QIcon::fromTheme( "edit-find" ), tr( "&Search" ), this } }
	, scannersBox{ new QComboBox{ this } }
	, advancedCheckBox{ new QCheckBox{ tr( "Advanced" ), this } }
	, symbolEdit{ new SymbolLineEdit{ this } }
	, argumentsEdit{ new ArgumentsLineEdit{
		  scanner->invocation().join( ' ' ), scanner->stopString(), this } }
	, tabWidget{ new QTabWidget{ this } }
	, textBrowserStdOut{ new QTextBrowser{ this } }
	, textBrowserStdErr{ new QTextBrowser{ this } }
	, actionScan{ new QAction{ QIcon::fromTheme( "edit-find" ), tr( "Scan" ), this } }
	, actionQuit{ new QAction{
		  QIcon::fromTheme( "application-exit" ), tr( "&Quit" ), this } }
	, actionAboutQt{ new QAction{
		  QIcon::fromTheme( "help-about" ), tr( "About Qt" ), this } }
{
	setLayout( gridLayout );

	gridLayout->addWidget( buttonsGroup, 0, 0 );
	gridLayout->addWidget( tabsGroup, 1, 0 );

	buttonsGroup->setLayout( buttonsGrid );
	tabsGroup->setLayout( tabsGrid );

	buttonsGrid->addWidget( scannersBox, 0, 0 );
	buttonsGrid->addWidget( symbolEdit, 0, 1 );
	buttonsGrid->addWidget( searchBtn, 0, 2 );
	buttonsGrid->addWidget( closeBtn, 0, 3 );
	buttonsGrid->addWidget( advancedCheckBox, 1, 0 );
	buttonsGrid->addWidget( argumentsEdit, 1, 1, 1, 3 );

	tabsGrid->addWidget( tabWidget, 0, 0 );
	QWidget* tabStdOut{ new QWidget{ this } };
	QWidget* tabStdErr{ new QWidget{ this } };
	tabWidget->insertTab( 0, tabStdOut, tr( "Standard Output " ) );
	tabWidget->insertTab( 1, tabStdErr, tr( "Standard Error " ) );

	tabWidget->setTabToolTip( 0, tr( "Standard output is redirected here" ) );
	tabWidget->setTabToolTip(
		1,
		tr( QString::fromLatin1(
			    "Standard error is redirected here. The tab is "
			    "enabled when there is an actual error to print" )
			    .toLatin1()
			    .data() ) );
}

Interface::~Interface() = default;
