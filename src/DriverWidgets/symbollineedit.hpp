// <one line to give the program's name and a brief idea of what it does.>
// SPDX-FileCopyrightText: 2022 Πέτρος Σιλιγκούνας <petross404@gmail.com>
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef SYMBOLLINEEDIT_H
#define SYMBOLLINEEDIT_H

#include <qglobal.h>	    // for Q_DISABLE_COPY_MOVE
#include <qlineedit.h>	    // for QLineEdit
#include <qobjectdefs.h>    // for Q_OBJECT, signals, slots
#include <qstring.h>	    // for QString
class QEvent;
class QFocusEvent;
class QObject;
class QWidget;

/*!
 * `SymbolLineEdit` extends Qt's `QTextEdit` and adds more functi
 */
class SymbolLineEdit: public QLineEdit
{
	Q_OBJECT
	Q_DISABLE_COPY_MOVE( SymbolLineEdit )

public:
	/*!
	 * Constructs a `SymbolTextEdit` from the following:
	 * \param parent is the ptr to the parent widget
	 */
	explicit SymbolLineEdit( QWidget* parent = nullptr );
	/*!
	 * Constructs a `SymbolTextEdit` from the following:
	 * \param text is the default text
	 * \param parent is the ptr to the parent widget
	 */
	explicit SymbolLineEdit( const QString& text = QString::fromLocal8Bit( "printf" ),
				 QWidget* parent = nullptr );

	/*!
	 * Virtual, default destructor
	 */
	~SymbolLineEdit() override;

public slots:
	void textChangedSlot( const QString& txt );

signals:
	void symbolChanged( const QString& txt ) const;
	void enableSymbolSearch( bool enable ) const;

protected:
	/*!
	 * /todo write docs
	 *
	 * /param  TODO
	 * /return TODO
	 */
	void focusInEvent( QFocusEvent* event ) override;

	void leaveEvent( QEvent* event ) override;

private:
	bool m_enableSearch{ false };

	const QString msg{ tr( "Enter a symbol (ie printf)" ) };

	void init();
};

#endif	  // SYMBOLLINEEDIT_H
