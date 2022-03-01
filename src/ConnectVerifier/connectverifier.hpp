/*
 * <one line to give the program's name and a brief idea of
 * what it does.> Copyright (C) 2020  Πέτρος Σιλιγκούνας
 * <petross404@gmail.com>
 *
 * This program is free software: you can redistribute it
 * and/or modify it under the terms of the GNU General
 * Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the
 * implied warranty of MERCHANTABILITY or FITNESS FOR A
 * PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this program.  If not, see
 * <http://www.gnu.org/licenses/>.
 */

#ifndef CONNECTVERIFIER_HPP
#define CONNECTVERIFIER_HPP

//! \class ConnectVerifier class
/*!
 * `ConnectVerifier` is a fancy way to assert if some `QObject::connection`
 * silenty failed. It works only on Debug builds.
 */
class ConnectVerifier
{
public:
	//! Default constructor of `ConnectVerifier`
	explicit ConnectVerifier() = default;
	//! Copy constructor of `ConnectVerifier`
	explicit ConnectVerifier( const bool& b );
	//! Copy operator of `ConnectVerifier`
	ConnectVerifier& operator=( const bool& b );
};

#endif	  // CONNECTVERIFIER_HPP
