#ifndef PLUGINMANAGERALIASES_HPP
#define PLUGINMANAGERALIASES_HPP

#include <functional>
#include <map>
#include <string_view>

class QObject;
class IDriver;

//! Plugin Description: Driver's name and driver's description.
using PluginDesc = std::pair<std::string_view, std::string_view>;

//! std:vector that holds a PluginDesc pair.
using PluginDescVec = std::vector<PluginDesc>;

using DriverNameCB = const char* (*)();
using DriverDescCB = const char* (*)();
using ArgumentsCB  = const char* (*)();

//! Init callback signature.
using InitFCB = std::function<IDriver*( QObject* )>;

//! Plugin's description as key, with the driver's init callback
using PluginsPair = std::pair<PluginDesc, InitFCB>;

//! Plugin's description with the init callback
using PluginsTable = std::map<PluginDesc, InitFCB>;

//! Pair of map iterator and bool value that indicates if insert failed.
using AssignPair = std::pair<PluginsTable::const_iterator, bool>;

#endif
