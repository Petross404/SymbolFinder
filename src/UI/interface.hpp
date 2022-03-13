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

#ifndef INTERFACE_H
#define INTERFACE_H

#include <qglobal.h>	    // for Q_DISABLE_COPY_MOVE
#include <qobjectdefs.h>    // for Q_OBJECT
#include <qstring.h>	    // for QString
#include <qwidget.h>	    // for QWidget

#include <gsl/pointers>	    // for owner
class ArgumentsLineEdit;    // lines 38-38
class QAction;		    // lines 27-27
class QCheckBox;	    // lines 33-33
class QComboBox;	    // lines 31-31
class QGridLayout;	    // lines 28-28
class QGroupBox;	    // lines 35-35
class QObject;
class QPushButton;	 // lines 30-30
class QTabWidget;	 // lines 32-32
class QTextBrowser;	 // lines 36-36
class Scanner;		 // lines 26-26
class SymbolLineEdit;	 // lines 39-39

namespace Ui {
/*!
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
	 * \param scanner is a ptr to the `Scanner` instance. We
	 * need this to extract some info for our custom widgets.
	 * \param parent is a ptr to the parent widget.
	 */
	explicit Interface( Scanner* scanner, QWidget* parent = nullptr );

	/*!
	 * Virtual, default destructor.
	 */
	~Interface() override;

	gsl::owner<QGridLayout*> gridLayout; /*!< Central grid layout */
	gsl::owner<QGridLayout*> buttonsGrid; /*!< Upper grid layout, for the buttons */
	gsl::owner<QGridLayout*> tabsGrid; /*!< Last grid layout, for the tabWidget */
	gsl::owner<QGroupBox*>	 buttonsGroup;
	gsl::owner<QGroupBox*>	 tabsGroup;
	gsl::owner<QPushButton*> closeBtn;
	gsl::owner<QPushButton*> searchBtn;
	gsl::owner<QPushButton*> resetArgsBtn;
	gsl::owner<QComboBox*>	 scannersBox;
	gsl::owner<QCheckBox*>	 advancedCheckBox;

	gsl::owner<SymbolLineEdit*>    symbolEdit;
	gsl::owner<ArgumentsLineEdit*> argumentsEdit;

	gsl::owner<QTabWidget*>	  tabWidget;
	gsl::owner<QTextBrowser*> textBrowserStdOut;
	gsl::owner<QTextBrowser*> textBrowserStdErr;
	gsl::owner<QAction*>	  actionScan;
	gsl::owner<QAction*>	  actionQuit;
	gsl::owner<QAction*>	  actionAboutQt;
};
}    // end namespace Ui
#endif	  // INTERFACE_H
