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

#include "ui.hpp"

#include <qaction.h>	     // for QAction
#include <qbytearray.h>	     // for QByteArray
#include <qcheckbox.h>	     // for QCheckBox
#include <qcombobox.h>	     // for QComboBox
#include <qgridlayout.h>     // for QGridLayout
#include <qgroupbox.h>	     // for QGroupBox
#include <qicon.h>	     // for QIcon
#include <qpushbutton.h>     // for QPushButton
#include <qstringlist.h>     // for QStringList
#include <qtabwidget.h>	     // for QTabWidget
#include <qtextbrowser.h>    // for QTextBrowser

#include "../../../DriverWidgets/argumentslineedit.hpp"	   // for ArgumentsLineEdit
#include "../../../DriverWidgets/symbollineedit.hpp"	   // for SymbolLineEdit
#include "../../../Scanner/interface/idriver.hpp"
#include "../../../Scanner/scanner.hpp"	   // for Scanner

constexpr int btnMinWidth = 150;

Ui::Interface::Interface( QWidget* parent )
	: QWidget{ parent }
	, m_gridLayout{ new QGridLayout{ this } }
	, m_buttonsGrid{ new QGridLayout{ this } }
	, m_tabsGrid{ new QGridLayout{ this } }
	, m_buttonsGroup{ new QGroupBox{ tr( "Symbol name and options" ), this } }
	, m_tabsGroup{ new QGroupBox{ tr( "Output" ), this } }
	, m_closeBtn{ new QPushButton{
		  QIcon::fromTheme( "application-exit" ), tr( "&Close" ), this } }
	, m_searchBtn{ new QPushButton{
		  QIcon::fromTheme( "edit-find" ), tr( "&Search" ), this } }
	, m_resetArgsBtn{ new QPushButton{
		  QIcon::fromTheme( "view-refresh" ), tr( "&Reset" ), this } }
	, m_scannersBox{ new QComboBox{ this } }
	, m_advancedCheckBox{ new QCheckBox{ tr( "Advanced arguments" ), this } }
	, m_symbolEdit{ new SymbolLineEdit{ this } }
	, m_argumentsEdit{ new ArgumentsLineEdit{ this } }
	, m_tabWidget{ new QTabWidget{ this } }
	, m_textBrowserStdOut{ new QTextBrowser{ this } }
	, m_textBrowserStdErr{ new QTextBrowser{ this } }
	, m_actionScan{ new QAction{ QIcon::fromTheme( "edit-find" ), tr( "Scan" ), this } }
	, m_actionQuit{ new QAction{
		  QIcon::fromTheme( "application-exit" ), tr( "&Quit" ), this } }
	, m_actionAboutQt{ new QAction{
		  QIcon::fromTheme( "help-about" ), tr( "About Qt" ), this } }
{
	setLayout( m_gridLayout );

	// Set size
	setMinimumWidth( 850 );
	setMinimumHeight( 400 );
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
	QWidget* tabStdOut{ new QWidget{ this } };
	QWidget* tabStdErr{ new QWidget{ this } };
	m_tabWidget->insertTab( 0, tabStdOut, tr( "Standard Output " ) );
	m_tabWidget->insertTab( 1, tabStdErr, tr( "Standard Error " ) );

	m_tabWidget->setTabToolTip( 0, tr( "Standard output is redirected here" ) );
	m_tabWidget->setTabToolTip(
		1,
		tr( QString::fromLatin1(
			    "Standard error is redirected here. The tab is "
			    "enabled when there is an actual error to print" )
			    .toLatin1()
			    .data() ) );
}

Ui::Interface::~Interface() = default;

gsl::owner<QAction*> Ui::Interface::actionAboutQt() { return m_actionAboutQt; }

gsl::owner<QAction*> Ui::Interface::actionQuit() { return m_actionQuit; }

gsl::owner<QPushButton*> Ui::Interface::closeBtn() { return m_closeBtn; }

gsl::owner<QGridLayout*> Ui::Interface::tabsGrid() { return m_tabsGrid; }

gsl::owner<QPushButton*> Ui::Interface::searchBtn() { return m_searchBtn; }

gsl::owner<QGroupBox*> Ui::Interface::tabsGroup() { return m_tabsGroup; }

gsl::owner<QTabWidget*> Ui::Interface::tabWidget() { return m_tabWidget; }

gsl::owner<QAction*> Ui::Interface::actionScan() { return m_actionScan; }

gsl::owner<QCheckBox*> Ui::Interface::advancedCheckBox()
{
	return m_advancedCheckBox;
}

gsl::owner<QGridLayout*> Ui::Interface::gridLayout() { return m_gridLayout; }

gsl::owner<SymbolLineEdit*> Ui::Interface::symbolEdit() { return m_symbolEdit; }

gsl::owner<ArgumentsLineEdit*> Ui::Interface::argumentsEdit()
{
	return m_argumentsEdit;
}

gsl::owner<QGridLayout*> Ui::Interface::buttonsGrid() { return m_buttonsGrid; }

gsl::owner<QComboBox*> Ui::Interface::scannersBox() { return m_scannersBox; }

gsl::owner<QGroupBox*> Ui::Interface::buttonsGroup() { return m_buttonsGroup; }

gsl::owner<QPushButton*> Ui::Interface::resetArgsBtn()
{
	return m_resetArgsBtn;
}

gsl::owner<QTextBrowser*> Ui::Interface::textBrowserStdErr()
{
	return m_textBrowserStdErr;
}

gsl::owner<QTextBrowser*> Ui::Interface::textBrowserStdOut()
{
	return m_textBrowserStdOut;
}

void Ui::Interface::resizeLineEditWidgetsSlot( int w ) const
{
	m_argumentsEdit->setMinimumWidth( w );
	//+ btnMinWidth + advancedCheckBox->width()
}
