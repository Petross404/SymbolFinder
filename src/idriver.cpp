// <one line to give the program's name and a brief idea of what it does.>
// SPDX-FileCopyrightText: 2022 Πέτρος Σιλιγκούνας <petross404@gmail.com>
// SPDX-License-Identifier: GPL-3.0-or-later

#include "idriver.hpp"

IDriver::IDriver( QObject* parent )
	: QProcess{ parent }
{}

IDriver::~IDriver() = default;
