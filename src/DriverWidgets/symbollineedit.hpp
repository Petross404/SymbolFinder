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
	/*!
	 * Handle here what needs to be handled when the text
	 * is changed in the widget.
	 * \param txt is the new text in the widget
	 * \sa void SymbolLineEdit::symbolChanged(const QString& txt)
	 * \sa void SymbolLineEdit::enableSymbolSearch(bool enable)
	 */
	void textChangedSlot( const QString& txt );

signals:
	/*!
	 * Emit the new text
	 * \param txt is the new text in the widget
	 */
	void symbolChanged( const QString& txt );

	/*!
	 * Emit when the enabled or disabled status of some widgets
	 * should change. Some pushbuttons and other controls, should
	 * be conditionally enabled, based on whether there is text
	 * on this widget.
	 * \param enable is a boolean value that describes the situation
	 */
	void enableSymbolSearch( bool enable );

	/*!
	 * Emit this signal when the user enters an improper symbol name
	 * like one with spaces or other characters.
	 */
	void enableSymbolLineWarning();

protected:
	void focusInEvent( QFocusEvent* event ) override;
	void leaveEvent( QEvent* event ) override;

private:
	bool m_enableSearch{ false };

	const QString msg{ tr( "Enter a symbol (ie printf)" ) };

	void init();
};

#endif	  // SYMBOLLINEEDIT_H
