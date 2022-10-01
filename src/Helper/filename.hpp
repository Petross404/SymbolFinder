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

#ifndef FILENAME_HPP
#define FILENAME_HPP

#include <iostream>
#include <source_location>
#include <string_view>

namespace Helper {
void log( std::ostream&		     os,
	  const std::string_view     message,
	  const std::source_location location = std::source_location::current() );

template<typename T> void fun( T x ) { log( x ); }
};    // namespace Helper

#endif	  // FILENAME_HPP
