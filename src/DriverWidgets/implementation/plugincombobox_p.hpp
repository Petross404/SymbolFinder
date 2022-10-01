#ifndef PLUGINCOMBOBOX_P_HPP
#define PLUGINCOMBOBOX_P_HPP

#include <qglobal.h>	// for Q_DECLARE_...

#include <optional>    // for optional
#include <vector>      // for vector

#include "src/Scanner/interface/pluginmanageraliases.hpp"    // for PluginDesc
class PluginsComboBox;					     // lines 11-11
class QColor;
class QPaintEvent;    // lines 12-12

/*!
 * Private implementation of `PluginsComboBox`.
 */
class PluginsComboBoxPrivate
{
	Q_DISABLE_COPY_MOVE( PluginsComboBoxPrivate )

public:
	/*!
	 * Constructor of the private part.
	 * \param pc is `PluginsComboBox` pointer to the public instance.
	 */
	explicit PluginsComboBoxPrivate( PluginsComboBox* pc );

	/*!
	 * Destructor
	 */
	virtual ~PluginsComboBoxPrivate();

	/*!
	 * Initialize and setup the widget. Add any information
	 * about any plugin the program may have found.
	 *
	 * \param vec is the vector holding any plugin information
	 */
	void initScannerBox( std::vector<PluginDesc>& vec );

private:
	Q_DECLARE_PUBLIC( PluginsComboBox );

	PluginsComboBox* const q_ptr; /*!< Pointer to the public instance. */

	/*!
	 * Set the warning color of the widget
	 * \param event is a ptr to `QPaintEvent` that happened, wrapped
	 * in an std::optional
	 */
	void setWarningColor( std::optional<QPaintEvent*> event,
			      std::optional<const QColor> warnColor );
};
#endif	  // PLUGINCOMBOBOX_P_HPP
