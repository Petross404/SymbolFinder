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

#ifndef SYMBOLFINDER_H
#define SYMBOLFINDER_H

#include <qglobal.h>	    // for Q_DISABLE_COPY_...
#include <qmainwindow.h>    // for QMainWindow
#include <qobjectdefs.h>    // for Q_OBJECT, signals
#include <qstring.h>	    // for QString

#include <gsl/pointers>	   // for owner
#include <optional>	   // for optional, nullopt
#include <string_view>	   // for string_view

#include "../../DriverWidgets/argumentslineedit.hpp"	// for ArgumentsLineEdit

class QCloseEvent;    // lines 33-33
class QObject;	      // lines 34-34
class QWidget;	      // lines 35-35
class Scanner;	      // lines 36-36
namespace Ui {
class Interface;
}    // namespace Ui
class FinderWindowPrivate;

using ArgsLineEdit = ArgumentsLineEdit;

/*!
 * Main window for SymbolFinder.
 *
 * This object is a `QMainWindow` and is providing the UI for
 * a user to interact with the drivers.
 */
class FinderWindow: public QMainWindow
{
	Q_OBJECT
	Q_DISABLE_COPY_MOVE( FinderWindow )

public:
	/*!
	 * Constructs the MainWindow of SymbolFinder.
	 * \param parent is the pointer to the `QWidget` parent.
	 */
	explicit FinderWindow( std::optional<QWidget*> parent = std::nullopt );

	/*!
	 * Default destructor
	 */
	~FinderWindow() override;

public slots:
	/*!
	 * Slot to de-activate the stderr `QTabWidget` when no output exists.
	 * \sa void MainWindow::showStdErrorTab()
	 * \callgraph
	 */
	void hideStdErrorTab();

	/*!
	 * Slot to activate the sterr `QTabWidget` when the output is ready.
	 * \sa void MainWindow::hideStdErrorTab()
	 */
	void showStdErrorTab();

	/*!
	 * Slot to dis|enable the `ArgumentsLineEdit` widget
	 * \param option is a boolen that enables or not the widget.
	 */
	void enableAdvancedLineEdit( bool option );

	/*!
	 * Slot to dis|enable scan-related actions and widgets based on
	 * some conditions (symbol name in the widget, valid scanner etc).
	 * \param option is a boolen that enables or not the widgets.
	 */
	void enableSymbolSearchSlot( bool option );

	/*!
	 * Slot to update the text that the scanning produced.
	 * \sa void MainWindow::updateStdErrorSlot()
	 */
	void updateStdOutputSlot();

	/*!
	 * Slot to update the text that the scanning produced.
	 * \sa void MainWindow::updateStdOutputSlot()
	 */
	void updateStdErrorSlot();

	/*!
	 * Slot to set the symbol name with the `Scanner` instance.
	 */
	void updateSymbolSlot( const std::string_view symbol );

	/*!
	 * Slot to update the arguments, when the symbol name is altered.
	 */
	void updateAdvancedArgumentsSlot();

	/*!
	 * When the driver is changed or first-initialized, we must handle
	 * this change.
	 * \param name is the driver's name.
	 */
	void driverInitalizedSlot( const std::string_view name );

	/*!
	 * Slot to reset the blocked advanced arguments widgets. This
	 * happens when the user tries to edit the symbol name directly
	 * in this widget.
	 * \sa void MainWindow::resetSymbolLineWarningSlot()
	 */
	void resetAdvancedLineEditSlot();

	/*!
	 * Slot to reset the arguments of the active driver.
	 */
	void resetAdvancedArgumentsSlot();

	/*!
	 * Slot to handle any improper symbol name in the `SymbolLineEditor`.
	 * \sa void MainWindow::resetAdvancedLineEditSlot()
	 */
	void resetSymbolLineWarningSlot();

	/*!
	 * Slot to block the UI when the QProcess is running, so the user
	 * doesn't interact with it.
	 * \sa void MainWindow::scanFinishedSlot()
	 */
	void scanStartedSlot();

	/*!
	 * Slot to unblock the UI when the QProcess finished, so it's ready
	 * to interact again.
	 * \sa void MainWindow::scanStartedSlot()
	 */
	void scanFinishedSlot();

	/*!
	 * Slot to set the scanner's arguments. The arguments are taken
	 * from the relevant `ArgumentsLineEdit` widget.
	 * \param advancedArgs is the text in the widget (ie the arguments).
	 */
	void setInvocationSlot( const QString& advancedArgs );

	/*!
	 * Every time a different driver will be selected in the combobox,
	 * a new driver will be initialized.
	 * \param scannerName is the name of the new scanner driver.
	 */
	void resetScannerInstanceSlot( int index );

	void discoverPlugins();

signals:
	/*!
	 * Signal any listener that the `ArgumentsLineEdit` widget is
	 * enabled and ready to handle input again.
	 * \sa void MainWindow::resetAdvancedArgumentsSlot()
	 */
	void advancedArgumentssUnblocked() const;

	void startScanner() const;

protected:
	void closeEvent( QCloseEvent* event ) override;

private:
	Q_DECLARE_PRIVATE( FinderWindow )
	FinderWindowPrivate* const d_ptr;

	gsl::owner<Ui::Interface*> m_ui; /*!< Ptr to the hand-made user interface */
	gsl::owner<Scanner*>	   m_scanner; /*!< Ptr to the scanner instance */

	void setupConnections();
	void setupWidgets();
	void setupActions();
};

#endif	  // SYMBOLFINDER_H
