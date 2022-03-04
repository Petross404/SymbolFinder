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
class SymbolLineEdit;

using Window	   = Ui::MainWindow;
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
	 * \sa void MainWindow::unblockAdvancedArgumentsSlot()
	 */
	void unblockHelper( const QString& text );

public slots:
	/*!
	 * De-activate the stderr `QTabWidget` when no output exists.
	 * \sa void MainWindow::showStdErrorTab()
	 */
	void hideStdErrorTab();
	/*!
	 * Activate the sterr `QTabWidget` when the output is ready.
	 * \sa void MainWindow::hideStdErrorTab()
	 */
	void showStdErrorTab();

	/*!
	 * Dis|enable the `ArgumentsLineEdit` widget
	 * \param option is a boolen that enables or not the widget.
	 */
	void enableAdvancedLineEdit( bool option );

	void updateStdOutputSlot();
	void updateStdErrorSlot();
	void updateSymbolSlot( const QString& symbol );
	void updateAdvancedArgumentsSlot();
	void unblockAdvancedArgumentsSlot();

	void setInvocationSlot( const QString& advancedArgs );

signals:
	void advancedArgumentssUnblocked() const;

private:
	std::unique_ptr<Window>	    m_ui; /*!< Smart pointer to UI object */
	gsl::owner<Scanner*>	    m_scanner;
	gsl::owner<SymbolLineEdit*> m_lineEditSymbol;
	gsl::owner<ArgsLineEdit*>   m_lineEditDefaultArgs;

	void setupConnections();
	void setupWidgets();
};

#endif	  // SYMBOLFINDER_H
