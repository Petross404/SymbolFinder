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

#include "idriver.hpp"
class QObject;

StopIndex::StopIndex( const uint32_t indexOfStop_, std::string_view stopStr_ )
	: indexOfStop{ indexOfStop_ }
	, stopStr{ stopStr_ }
{}

StopIndex StopIndex::makeStopIndex() { return StopIndex{}; }

StopIndex StopIndex::makeStopIndex( const uint32_t indexOfStop_, std::string_view stopStr_ )
{
	return StopIndex{ indexOfStop_, stopStr_ };
}

bool StopIndex::isNull() const
{
	bool is_null = true;
	if ( indexOfStop && stopStr.empty() ) { is_null = false; }

	return is_null;
}

IDriver::IDriver( const std::string_view name, std::optional<QObject*> parent )
	: QProcess{ parent.value_or( nullptr ) }
{
	emit initialized( name );
}

IDriver::~IDriver() = default;
