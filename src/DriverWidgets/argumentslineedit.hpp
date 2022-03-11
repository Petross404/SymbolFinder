// <one line to give the program's name and a brief idea of what it does.>
// SPDX-FileCopyrightText: 2022 Πέτρος Σιλιγκούνας <petross404@gmail.com>
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef ARGUMENTSLINEEDIT_H
#define ARGUMENTSLINEEDIT_H

#include <qglobal.h>	    // for Q_DISABLE_COPY_MOVE
#include <qlineedit.h>	    // for QLineEdit
#include <qobjectdefs.h>    // for Q_OBJECT, Q_PROPERTY, signals
#include <qstring.h>	    // for QString
class QKeyEvent;
class QMouseEvent;
class QObject;
class QWidget;

/*!
 * \brief `ArgumentsLineEdit` is a customized `QLineEdit`.
 *
 * What it offers over the Qt's widget, is that we can handle some special characters and
 * emit signals that are usefull elsewhere.
 *
 * Since this widget can both display and edit the driver's arguments, one could by
 * mistake edit the symbol's name here, confusing the program that reads this name
 * from another input widget. Clicking or typing at a certain position in the arguments
 * list, is prohibeted and the user is visually informed about the error.
 */
class ArgumentsLineEdit: public QLineEdit
{
	Q_OBJECT
	Q_PROPERTY( QString m_specialStr READ stopString WRITE setStopString NOTIFY symbolManuallyChanged )
	Q_DISABLE_COPY_MOVE( ArgumentsLineEdit )

public:
	/*!
	 * Construct an `ArgumentsLineEdit` object with the following parameters.
	 *
	 * \param arguments is the `QString` for the driver arguments
	 * \param stopString is the `QString` that imediately after we find the symbol's name
	 * \param parent is the ptr of the parent `QWidget` for this object
	 */
	explicit ArgumentsLineEdit( const QString& arguments,
				    const QString& stopString,
				    QWidget*	   parent = nullptr );

	/*!
	 * Construct an `ArgumentsLineEdit` object just with the parent `QWidget`
	 */
	explicit ArgumentsLineEdit( QWidget* parent = 0 );

	/*!
	 * Default destructor
	 */
	~ArgumentsLineEdit() override;

	/*!
	 * This function sets the stop string
	 * \param str is the stop string
	 * \sa void ArgumentsLineEdit::stopString() const
	 */
	void setStopString( const QString& str );

	/*!
	 * This function returns the selected driver's "stop string".
	 * \return `QString` that is the stop string.
	 * \sa void ArgumentsLineEdit::setStopString(const QString& str)
	 */
	[[nodiscard]] QString stopString() const;

signals:
	/*!
	 * This signal is emmited when the user tries to edit the symbol's name
	 * in this widget. The signal is used to warn the user and reset this widget.
	 *
	 * \sa void ArgumentsLineEdit::mousePressEvent(QMouseEvent* event)
	 * \sa void ArgumentsLineEdit::keyPressEvent(QKeyEvent* event)
	 */
	void symbolManuallyChanged();

protected:
	/*!
	 * Override and re-implement `QLineEdit::mousePressEvent(QMouseEvent*)` so we can
	 * handle left-clicks above the symbol's name.
	 * \param event is a ptr to `QMouseEvent` that occured.
	 */
	void mousePressEvent( QMouseEvent* event ) override;

	/*!
	 * Override and re-implement `QLineEdit::keyPressEvent(QKeyEvent*)` so we can
	 * handle keystrokes above the symbol's name.
	 * \param event is a ptr to `QKeyEvent` that occured.
	 */
	void keyPressEvent( QKeyEvent* event ) override;

private:
	QString m_text; /*!< Text that this widget contains>*/

	QString m_specialStr; /*! The string in the argument that immediately after the symbol name exists.
			       *\sa void ArgumentsLineEdit::stopString() const
			       */

	/*!
	 * The constructors share some functionality.
	 */
	void init();
};

#endif	  // ARGUMENTSLINEEDIT_H
