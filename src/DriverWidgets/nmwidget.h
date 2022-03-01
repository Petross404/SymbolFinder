// <one line to give the program's name and a brief idea of what it does.>
// SPDX-FileCopyrightText: 2022 Πέτρος Σιλιγκούνας <petross404@gmail.com>
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef NMWIDGET_H
#define NMWIDGET_H

#include <qwidget.h>

class NmWidget: public QWidget
{
	Q_OBJECT
	Q_DISABLE_COPY_MOVE( NmWidget )

public:
	explicit NmWidget( QWidget* parent = 0 );
	~NmWidget() override;
};

#endif	  // NMWIDGET_H
