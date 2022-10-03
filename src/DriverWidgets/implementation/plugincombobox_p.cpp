#include "plugincombobox_p.hpp"
#include <bits/utility.h>           // for tuple_element<>::type
#include <fmt/core.h>               // for print
#include <qcolor.h>                 // for QColor
#include <qicon.h>                  // for QIcon
#include <qnamespace.h>             // for ItemDataRole, AlignCenter, Alignm...
#include <qpainter.h>               // for QPainter
#include <qpalette.h>               // for QPalette
#include <qstringliteral.h>         // for QStringLiteral
#include <stdio.h>                  // for stderr
#include <algorithm>                // for transform
#include <cctype>                   // for toupper
#include <cstdint>                  // for uint16_t
#include <string>                   // for string
#include <string_view>              // for string_view
#include "../../Helper/string.hpp"  // for toqstring
#include "../pluginscombobox.hpp"   // for PluginsComboBox

void setBoxItemData( PluginsComboBox*	 pluginCombobox,
		     const std::uint16_t indexOfItem,
		     std::string_view	 driverDescription );

PluginsComboBoxPrivate::PluginsComboBoxPrivate( PluginsComboBox* pc )
	: q_ptr{ pc }
{}

PluginsComboBoxPrivate::~PluginsComboBoxPrivate() = default;

void PluginsComboBoxPrivate::initScannerBox( std::vector<PluginDesc>& vec )
{
	if ( vec.empty() )
	{
		fmt::print( stderr, "Empty vector\n" );
		return;
	}

	// The default value should be a placeholder text
	constexpr int	 nonSelectableIndex = -1;
	std::string_view placeholder{ "-- Select a driver from the list: --" };

	Q_Q( PluginsComboBox );

	q->setPlaceholderText( string::toqstring( placeholder ) );
	q->setToolTip( string::toqstring( placeholder ) );
	q->setCurrentIndex( nonSelectableIndex );

	// Iterate through the list of plugins and fill the QComboBox
	for ( int i = 0; i < vec.size(); i++ )
	{
		// Initialize the variables from the tuple
		const auto& [driverName, driverDescription] = vec.at( i );

		std::string driverNameUpper{ driverName };

		std::transform( driverNameUpper.begin(),
				driverNameUpper.begin(),
				driverNameUpper.begin(),
				[]( unsigned char c ) -> unsigned char {
					return std::toupper( c );
				} );

		// Put a discrete icon next to the driver name
		std::string_view iconName{ "emblem-system" };

		q->addItem( QIcon::fromTheme( string::toqstring( iconName ) ),
			    string::toqstring( driverNameUpper ),
			    Qt::ItemDataRole::StatusTipRole );

		setBoxItemData( q, i, driverDescription );
	}
}

void PluginsComboBoxPrivate::setWarningColor( std::optional<QPaintEvent*> event,
					      std::optional<const QColor> warnColor )
{
	Q_UNUSED( event );
	Q_Q( PluginsComboBox );

	// Exit if not empty
	if ( q->count() ) { return; }

	QPainter p{q};
	p.setPen(Qt::GlobalColor::black);
	p.drawText(q->rect(), Qt::AlignCenter, QStringLiteral("No drivers found."));

	const QPalette warnPalette{ warnColor.has_value()
					    ? warnColor.value()
					    : QColor::fromRgb( 220, 150, 140, 150 ) };

	q->setPalette( warnPalette );
}

void setBoxItemData( PluginsComboBox*	 pluginCombobox,
		     const std::uint16_t indexOfItem,
		     std::string_view	 driverDescription )
{
	pluginCombobox->setItemData( indexOfItem,
				     string::toqstring( driverDescription ),
				     Qt::ItemDataRole::ToolTipRole );

	pluginCombobox->setItemData( indexOfItem,
				     Qt::AlignmentFlag::AlignCenter,
				     Qt::ItemDataRole::TextAlignmentRole );
}
