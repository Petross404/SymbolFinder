// <one line to give the program's name and a brief idea of what it does.>
// SPDX-FileCopyrightText: 2022 Πέτρος Σιλιγκούνας <petross404@gmail.com>
// SPDX-License-Identifier: GPL-3.0-or-later

#include "pluginmanager_p.hpp"

#include <fmt/format.h>
#include <qdebug.h>
#include <qobject.h>

#include <algorithm>
#include <exception>
#include <functional>
#include <iostream>
#include <iterator>

#include "../../Helper/filename.hpp"
#include "../../Helper/qmacros.hpp"
#include "idriver.hpp"
#include "pluginmanager.hpp"

/*!
 * `CompareName` acts a functor to compare driver's name with another.
 * `DescrPair` is the std::pair<QString, QString> aka PluginDesc type
 * and `InitCallBack` is the CreateFCB type
 */
template<typename DescrPair, typename InitCallBack> class CompareName
{
	std::string name;

public:
	/*!
	 * Create a class and overload operator().
	 * \param dName is the name of the driver we need to compare to.
	 */
	explicit CompareName( std::string_view dName )
		: name{ dName }
	{}

	/*!
	 * Overload operator() to create a functor
	 * \param pair is the pair of the map that holds the description
	 * pair and the driver's init callback
	 */
	bool operator()( const std::pair<DescrPair, InitCallBack>& pair ) const
	{
		// This map holds an std::pair as "first" and CreateFCB as "second"
		const auto& [desc_pair, _cb]	       = pair;
		const auto& [driver_name, driver_desc] = desc_pair;

		// Compare the current name with the registered driver's name
		return ( name == driver_name );
	}
};

PluginManagerPrivate::PluginManagerPrivate( PluginManager* pm )
	: q_ptr{ pm }
{}

std::optional<IDriver*> PluginManagerPrivate::initPlugin( std::string_view name,
							  QObject*	   parent )
{
	if ( name.empty() || !name.size() ) { return std::nullopt; }

	/*
	 * Dynamic memory allocation may fail. The user should be informed
	 * about this, by returning std::nullopt
	 */
	std::optional<IDriver*> driver{ std::nullopt };

	// Find where the "name" is registered.
	PluginsTable::const_iterator it{
		std::ranges::find_if( m_tableOfDrivers,
				      CompareName<PluginDesc, InitFCB>{ name } ) };

	if ( it != m_tableOfDrivers.end() )
	{
		const InitFCB& initcb{ it->second };

		/*
		 * Invoke the callback and initialize the plugin, but
		 * emit the signal only if a plugin actually initialized.
		 */
		if ( driver = std::invoke( initcb, parent ); driver.has_value() )
		{
			Q_Q( PluginManager );
			emit q->driverInitialized( driver.value() );
		}
	}

	return driver;
}

void PluginManagerPrivate::registerPlugin( const DriverNameCB& driverNameGlobal,
					   const DriverDescCB& driverDescGlobal,
					   const InitFCB&      initcb )
{
	if ( !driverNameGlobal || !driverDescGlobal || !initcb ) { return; }

	// Hold the heap memory in smart pointers.
	std::unique_ptr<const char[]> driverName{ std::invoke( driverNameGlobal ) };
	std::unique_ptr<const char[]> driverDesc{ std::invoke( driverDescGlobal ) };

	// Create the pair that will be the "key" for the map.
	const PluginDesc descrPair{ std::make_pair( driverName.get(), driverDesc.get() ) };

	// Find the location of the driver's name - if any!
	PluginsTable::const_iterator it{ m_tableOfDrivers.find( descrPair ) };

	if ( it != m_tableOfDrivers.end() )
	{
		const InitFCB& cb{ it->second };

		if ( cb.target_type() != initcb.target_type() )
		{
			/*
			 * In this case the name exists but with a different
			 * callback type. Overwrite the callback with the new one.
			 */
			m_tableOfDrivers.at( descrPair ) = std::move( initcb );
		}
		else
		{
			// Print a message that the plugin is registered.
			fmt::print( stderr, "This plugin is registered already. Ignoring.\n" );
		}

		// Exit early
		return;
	}

	// Construct it in place.
	AssignPair p{ m_tableOfDrivers.insert_or_assign( descrPair, initcb ) };

	if ( const auto& [it, succeeded] = p; !succeeded )
	{
		// TODO Handle error.
	}
	else
	{
		Q_Q( PluginManager );
		emit q->tableOfDriversAltered( m_tableOfDrivers.size() );
	}
}

void PluginManagerPrivate::unregisterPlugin( std::string_view name )
{
	std::size_t size{ std::erase_if( m_tableOfDrivers,
					 CompareName<PluginDesc, InitFCB>{ name } ) };

	Q_Q( PluginManager );
	emit q->tableOfDriversAltered( size );
}

PluginsTable PluginManagerPrivate::registeredPlugins() const
{
	return m_tableOfDrivers;
}

const PluginDescVec PluginManagerPrivate::pluginNames() const
{
	std::vector<PluginDesc> v{};

	for ( const auto& [pair, callback] : m_tableOfDrivers )
	{
		v.push_back( pair );
	}

	return v;
}
