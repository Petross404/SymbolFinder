// <one line to give the program's name and a brief idea of what it does.>
// SPDX-FileCopyrightText: 2022 Πέτρος Σιλιγκούνας <petross404@gmail.com>
// SPDX-License-Identifier: GPL-3.0-or-later

#include "pluginscombobox.hpp"

#include <qcolor.h>    // for QColor

#include <string_view>	  // for string_view

#include "implementation/plugincombobox_p.hpp"		     // for PluginsCom...
#include "src/Scanner/interface/pluginmanageraliases.hpp"    // for PluginDesc
class QPaintEvent;					     // lines 11-11
class QWidget;	  // lines 12-12					     // lines 14-14

/*!
 * Free function to set item's data inside the combobox
 * \param combobox is the this pointer
 * \param index is the index which we edit
 * \param driverDescription is the text for the tooltip
 */
void setBoxItemData( PluginsComboBox* combobox,
		     const int	      index,
		     std::string_view driverDescription );

PluginsComboBox::PluginsComboBox( std::optional<QWidget*> parent )
	: QComboBox{ parent.value_or( nullptr ) }
	, d_ptr{ std::make_unique<PluginsComboBoxPrivate>( this ) }
{
	Q_D( PluginsComboBox );
	Q_ASSERT_X( d->q_ptr == this, "", "" );
}

PluginsComboBox::~PluginsComboBox() = default;

void PluginsComboBox::initScannerBox( std::vector<PluginDesc>& vec )
{
	Q_D( PluginsComboBox );
	d->initScannerBox( vec );
}

void PluginsComboBox::paintEvent( QPaintEvent* event )
{
	Q_D( PluginsComboBox );

	// Colorize this combobox as red, if it is empty.
	d->setWarningColor( std::nullopt, std::nullopt );

	// Forward the event.
	QComboBox::paintEvent( event );
}
