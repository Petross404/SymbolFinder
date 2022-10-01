// <one line to give the program's name and a brief idea of what it does.>
// SPDX-FileCopyrightText: 2022 Πέτρος Σιλιγκούνας <petross404@gmail.com>
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef PLUGINSCOMBOBOX_H
#define PLUGINSCOMBOBOX_H

#include <qcombobox.h>	    // for QComboBox
#include <qglobal.h>	    // for Q_DISABLE_COPY_MOVE
#include <qobjectdefs.h>    // for Q_OBJECT
#include <qstring.h>	    // for QString

#include <optional>    // for optional
#include <vector>      // for vector

#include "../Scanner/interface/pluginmanageraliases.hpp"    // for PluginDesc

class QObject;	  // lines 17-17
class QPaintEvent;
class QWidget;	  // lines 18-18
class PluginsComboBoxPrivate;

/*!
 * Implement a custom `QComboBox` to override some functions.
 */
class PluginsComboBox: public QComboBox
{
	Q_OBJECT
	Q_DISABLE_COPY_MOVE( PluginsComboBox )

public:
	/*!
	 * Constructor
	 * \param parent is the parent `QWidget`
	 */
	explicit PluginsComboBox( std::optional<QWidget*> parent );

	~PluginsComboBox() override;

	/*!
	 * Initialize and setup the widget. Add any information
	 * about any plugin the program may have found.
	 * \param vec is the vector holding any plugin information
	 */
	void initScannerBox( std::vector<PluginDesc>& vec );

protected:
	PluginsComboBoxPrivate* const d_ptr; /*!< Pointer to the private implemantation */

	/*!
	 * Override `QComboBox::paintEvent`.
	 * \param event is a ptr to the `QPaintEvent` that happened.
	 */
	void paintEvent( QPaintEvent* event ) override;

private:
	Q_DECLARE_PRIVATE( PluginsComboBox )
};

#endif	  // PLUGINSCOMBOBOX_H