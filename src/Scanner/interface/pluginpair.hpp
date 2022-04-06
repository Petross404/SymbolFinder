// <one line to give the program's name and a brief idea of what it does.>
// SPDX-FileCopyrightText: 2022 Πέτρος Σιλιγκούνας <petross404@gmail.com>
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef PLUGINPAIR_H
#define PLUGINPAIR_H

#include <QString>
#include <QStringList>

class IDriver;

struct PluginDriver
{
	QString	    driverName;
	QStringList defArguments;
	IDriver*    driver;
};

#endif
