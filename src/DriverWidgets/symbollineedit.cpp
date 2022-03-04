// <one line to give the program's name and a brief idea of what it does.>
// SPDX-FileCopyrightText: 2022 Πέτρος Σιλιγκούνας <petross404@gmail.com>
// SPDX-License-Identifier: GPL-3.0-or-later

#include "symbollineedit.hpp"

#include <qevent.h>

SymbolLineEdit::SymbolLineEdit( QWidget* parent )
	: QLineEdit{ parent }
{}

SymbolLineEdit::SymbolLineEdit( const QString& text, QWidget* parent )
	: QLineEdit{ parent }
{
	setText( text );
}

SymbolLineEdit::~SymbolLineEdit() = default;

void SymbolLineEdit::paintEvent( QPaintEvent* event)
{
}

void SymbolLineEdit::focusInEvent( QFocusEvent* event )
{
	QLineEdit::blockSignals( true );

	setTextMargins( QMargins{ 20, 20, 20, 20 } );
	setText( "Enter a symbol (ie printf):" );

	QLineEdit::blockSignals( false );
}
