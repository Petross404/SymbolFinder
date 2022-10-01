/*
 * <one line to give the library's name and an idea of what it does.>
 * Copyright (C) 2022  <copyright holder> <email>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include <qglobal.h>	    // for qGetPtrHelper, Q_DECLARE_PRIVATE, Q_DISABLE...
#include <qobjectdefs.h>    // for Q_OBJECT, signals, slots
#include <qstring.h>	    // for QString
#include <qwidget.h>	    // for QWidget

#include <gsl/pointers>	    // for owner, strict_not_null
class ArgumentsLineEdit;    // lines 28-28
class InterfacePrivate;	    // lines 39-39
class PluginsComboBox;	    // lines 29-29
class QAction;		    // lines 30-30
class QCheckBox;	    // lines 31-31
class QGridLayout;	    // lines 32-32
class QGroupBox;	    // lines 33-33
class QObject;		    // lines 34-34
class QPushButton;	    // lines 35-35
class QShowEvent;
class QTabWidget;	 // lines 36-36
class QTextEdit;	 // lines 37-37
class SymbolLineEdit;	 // lines 38-38

template<typename T> using not_null_owner = gsl::strict_not_null<gsl::owner<T>>;

namespace Ui {
/*!
 * \brief `Interface` the ui file, ported to a class.
 * `Interface` is the User Interface of the .ui file, ported to
 * a hand-made widget for better control.
 */
class Interface: public QWidget
{
	Q_OBJECT
	Q_DISABLE_COPY_MOVE( Interface )

public:
	/*!
	 * Construct the User Interface for the main window.
	 * \param parent is a ptr to the parent widget.
	 */
	explicit Interface( QWidget* parent = nullptr );

	/*!
	 * Virtual, default destructor.
	 */
	~Interface() override;

	not_null_owner<QGridLayout*> gridLayout();
	not_null_owner<QGridLayout*> buttonsGrid();
	not_null_owner<QGridLayout*> tabsGrid();
	not_null_owner<QGroupBox*>   buttonsGroup();
	not_null_owner<QGroupBox*>   tabsGroup();
	not_null_owner<QPushButton*> closeBtn();
	not_null_owner<QPushButton*> searchBtn();
	not_null_owner<QPushButton*> resetArgsBtn();
	not_null_owner<QCheckBox*>   advancedCheckBox();

	not_null_owner<PluginsComboBox*>   scannersBox();
	not_null_owner<SymbolLineEdit*>	   symbolEdit();
	not_null_owner<ArgumentsLineEdit*> argumentsEdit();

	not_null_owner<QTabWidget*> tabWidget();
	not_null_owner<QTextEdit*>  textBrowserStdOut();
	not_null_owner<QTextEdit*>  textBrowserStdErr();
	not_null_owner<QAction*>    actionScan();
	not_null_owner<QAction*>    actionQuit();
	not_null_owner<QAction*>    actionAboutQt();

signals:
	void startScanning() const;
	void uiIsShown() const;

public slots:
	void resizeLineEditWidgetsSlot( int w ) const;

protected:
	InterfacePrivate* const d_ptr; /*!< Pointer to the private implementation */

	/*!
	 */
	void showEvent( QShowEvent* event ) override;

private:
	Q_DECLARE_PRIVATE( Interface )
};
}    // end namespace Ui
#endif	  // INTERFACE_HPP
