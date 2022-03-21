// <one line to give the program's name and a brief idea of what it does.>
// SPDX-FileCopyrightText: 2022 Πέτρος Σιλιγκούνας <petross404@gmail.com>
// SPDX-License-Identifier: GPL-3.0-or-later

#include "idriver.hpp"
class QObject;

bool StopIndex::isNull()
{
	bool is_null{ true };
	if ( this->indexOfStop > 0
	     && ( !this->stopStr.isNull() || !this->stopStr.isEmpty() ) )
	{
		is_null = false;
	}
	return is_null;
}

Process::IDriver::IDriver( QObject* parent )
	: QProcess{ parent }
{}

Process::IDriver::~IDriver() = default;
