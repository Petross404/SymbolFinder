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

#include "connectverifier.hpp"

const char* const g_msg{ "Connection failed" };

const char* ConnectVerifierException::what() const noexcept { return g_msg; }

ConnectVerifier::ConnectVerifier( const bool& b )
{
	if ( !b ) { throw ConnectVerifierException{}; }
	(void)( b );
}

ConnectVerifier& ConnectVerifier::operator=( const bool& b )
{
	if ( !b ) { throw ConnectVerifierException{}; }

	(void)( b );
	return *this;
}
