// <one line to give the program's name and a brief idea of what it does.>
// SPDX-FileCopyrightText: 2022 Πέτρος Σιλιγκούνας <petross404@gmail.com>
// SPDX-License-Identifier: GPL-3.0-or-later

#include "connectexception.hpp"

#include <qobject.h>

const char* g_msg{ "Connection failed!" };

ConnectException::ConnectException( const char* msg )
	: m_msg{ qPrintable( msg ) }
{}

const char* ConnectException::what() const throw() { return "Connection failed!"; }
