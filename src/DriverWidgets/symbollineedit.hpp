// <one line to give the program's name and a brief idea of what it does.>
// SPDX-FileCopyrightText: 2022 Πέτρος Σιλιγκούνας <petross404@gmail.com>
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef SYMBOLLINEEDIT_H
#define SYMBOLLINEEDIT_H

#include <qlineedit.h>

/**
 * @todo write docs
 */
class SymbolLineEdit: public QLineEdit
{
	Q_OBJECT
	Q_DISABLE_COPY_MOVE( SymbolLineEdit )

public:
	/**
	 * Default constructor
	 */
	explicit SymbolLineEdit( QWidget* parent = nullptr );
	explicit SymbolLineEdit( const QString& text = QString::fromLocal8Bit( "printf" ),
				 QWidget* parent = nullptr );

	/**
	 * Destructor
	 */
	~SymbolLineEdit() override;

signals:
	void blockSignals();
	void unblockSignals();

protected:
	/*!
	 * /todo write docs
	 *
	 * /param  TODO
	 * /return TODO
	 */
	void paintEvent( QPaintEvent* ) override;

	void focusInEvent( QFocusEvent* event ) override;
};

#endif	  // SYMBOLLINEEDIT_H
