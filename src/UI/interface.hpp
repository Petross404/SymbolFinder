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

#include <qwidget.h>

#include <gsl/pointers>

class Scanner;
class QAction;
class QGridLayout;
class QLabel;
class QPushButton;
class QComboBox;
class QTabWidget;
class QCheckBox;
class QMenuBar;
class QGroupBox;
class QTextBrowser;

class ArgumentsLineEdit;
class SymbolLineEdit;

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

#endif	  // INTERFACE_H
