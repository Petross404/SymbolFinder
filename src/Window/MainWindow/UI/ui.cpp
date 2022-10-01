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

#include <qnamespace.h>	   // for UniqueConnec...

#include "../../../ConnectVerifier/connectverifier.hpp"	   // for ConnectVerifier
#include "../findermainwindow.hpp"			   // for FinderWindow
#include "implementation/ui_p.hpp"			   // for InterfacePri...
class QShowEvent;

Ui::Interface::Interface( QWidget* parent )
	: QWidget{ parent }
	, d_ptr{ new InterfacePrivate{ this } }
{
	if ( const auto fw{ static_cast<FinderWindow*>( parent ) }; fw != nullptr )
	{
		ConnectVerifier v;
		v = connect( this,
			     &Interface::startScanning,
			     fw,
			     &FinderWindow::startScanner,
			     Qt::UniqueConnection );
	}
}

Ui::Interface::~Interface() { delete d_ptr; }

not_null_owner<QAction*> Ui::Interface::actionAboutQt()
{
	Q_D( Interface );
	return d->m_actionAboutQt;
}

not_null_owner<QAction*> Ui::Interface::actionQuit()
{
	Q_D( Interface );
	return d->m_actionQuit;
}

not_null_owner<QPushButton*> Ui::Interface::closeBtn()
{
	Q_D( Interface );
	return d->m_closeBtn;
}

not_null_owner<QGridLayout*> Ui::Interface::tabsGrid()
{
	Q_D( Interface );
	return d->m_tabsGrid;
}

not_null_owner<QPushButton*> Ui::Interface::searchBtn()
{
	Q_D( Interface );
	return d->m_searchBtn;
}

not_null_owner<QGroupBox*> Ui::Interface::tabsGroup()
{
	Q_D( Interface );
	return d->m_tabsGroup;
}

not_null_owner<QTabWidget*> Ui::Interface::tabWidget()
{
	Q_D( Interface );
	return d->m_tabWidget;
}

not_null_owner<QAction*> Ui::Interface::actionScan()
{
	Q_D( Interface );
	return d->m_actionScan;
}

not_null_owner<QCheckBox*> Ui::Interface::advancedCheckBox()
{
	Q_D( Interface );
	return d->m_advancedCheckBox;
}

not_null_owner<QGridLayout*> Ui::Interface::gridLayout()
{
	Q_D( Interface );
	return d->m_gridLayout;
}

not_null_owner<SymbolLineEdit*> Ui::Interface::symbolEdit()
{
	Q_D( Interface );
	return d->m_symbolEdit;
}

not_null_owner<ArgumentsLineEdit*> Ui::Interface::argumentsEdit()
{
	Q_D( Interface );
	return d->m_argumentsEdit;
}

not_null_owner<QGridLayout*> Ui::Interface::buttonsGrid()
{
	Q_D( Interface );
	return d->m_buttonsGrid;
}

not_null_owner<PluginsComboBox*> Ui::Interface::scannersBox()
{
	Q_D( Interface );
	return d->m_scannersBox;
}

not_null_owner<QGroupBox*> Ui::Interface::buttonsGroup()
{
	Q_D( Interface );
	return d->m_buttonsGroup;
}

not_null_owner<QPushButton*> Ui::Interface::resetArgsBtn()
{
	Q_D( Interface );
	return d->m_resetArgsBtn;
}

not_null_owner<QTextEdit*> Ui::Interface::textBrowserStdErr()
{
	Q_D( Interface );
	return d->m_textEditStdErr;
}

not_null_owner<QTextEdit*> Ui::Interface::textBrowserStdOut()
{
	Q_D( Interface );
	return d->m_textEditStdOut;
}

void Ui::Interface::resizeLineEditWidgetsSlot( int w ) const
{
	Q_D( const Interface );
	d->resizeLineEditWidgets( w );
}

void Ui::Interface::showEvent( QShowEvent* event )
{
	emit uiIsShown();
	QWidget::showEvent( event );
}
