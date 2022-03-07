#ifndef SYMBOLFINDER_H
#define SYMBOLFINDER_H

#include <QMainWindow>
#include <gsl/pointers>
#include <memory>

namespace Ui {
class MainWindow;
}
class QLineEdit;
class QTextBrowser;
class QPushButton;
class IDriver;
class Scanner;
class ArgumentsLineEdit;
class SymbolTextEdit;

class Interface;

using ArgsLineEdit = ArgumentsLineEdit;

/*!
 * Main window for SymbolFinder.
 *
 * This object is a `QMainWindow` and is providing the UI for
 * a user to interact with the drivers.
 */
class MainWindow: public QMainWindow
{
	Q_OBJECT
	Q_DISABLE_COPY_MOVE( MainWindow )

public:
	/*!
	 * Constructs the MainWindow of SymbolFinder.
	 * \param parent is the pointer to the `QWidget` parent.
	 */
	explicit MainWindow( QWidget* parent = nullptr );

	/*!
	 * Default destructor
	 */
	~MainWindow() override;

	/*!
	 * Helper fumction to run inside a `QTimer::singleShot` and
	 * unblock the `ArgumentsLineEdit` widget.
	 * \param text is what will be written to the widget once it's unblocked
	 * \sa void MainWindow::resetAdvancedArgumentsSlot()
	 */
	void unblockHelper( const QString& text );

public slots:
	/*!
	 * Slot to de-activate the stderr `QTabWidget` when no output exists.
	 * \sa void MainWindow::showStdErrorTab()
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
	void updateSymbolSlot( const QString& symbol );
	/*!
	 * Slot to update the arguments, when the symbol name is altered.
	 */
	void updateAdvancedArgumentsSlot();
	/*!
	 * Slot to reset the blocked advanced arguments widgets. This
	 * happens when the user tries to edit the symbol name directly
	 * in this widget.
	 */
	void resetAdvancedArgumentsSlot();

	/*!
	 * Slot to block the UI when the QProcess is running, so the user
	 * doesn't interact with it.
	 * \sa void MainWindow::unblockUISlot()
	 */
	void blockUISlot();
	/*!
	 * Slot to unblock the UI when the QProcess finished, so it's ready
	 * to interact again.
	 */
	void unblockUISlot();

	/*!
	 * Slot to set the scanner's arguments. The arguments are taken
	 * from the relevant `ArgumentsLineEdit` widget.
	 * \param advancedArgs is the text in the widget (ie the arguments).
	 */
	void setInvocationSlot( const QString& advancedArgs );

signals:
	/*!
	 * Signal any listener that the `ArgumentsLineEdit` widget is
	 * enabled and ready to handle input again.
	 * \sa void MainWindow::resetAdvancedArgumentsSlot()
	 */
	void advancedArgumentssUnblocked() const;

private:
	gsl::owner<Scanner*>   m_scanner; /*!< Ptr to the scanner instance */
	gsl::owner<Interface*> m_ui; /*!< Ptr to the hand-made user interface */

	void setupConnections();
	void setupWidgets();
	void setupActions();
};

#endif	  // SYMBOLFINDER_H
