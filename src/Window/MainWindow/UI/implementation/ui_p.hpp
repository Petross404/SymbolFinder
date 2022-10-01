#ifndef UI_P_HPP
#define UI_P_HPP

#include <qglobal.h>	// for Q_DECLARE_PUBLIC, Q_DISABLE_COPY_MOVE

#include <gsl/pointers>	    // for owner, strict_not_null
class ArgumentsLineEdit;    // lines 7-7
class PluginsComboBox;	    // lines 8-8
class QAction;		    // lines 9-9
class QCheckBox;	    // lines 10-10
class QGridLayout;	    // lines 11-11
class QGroupBox;	    // lines 12-12
class QPushButton;	    // lines 14-14
class QTabWidget;	    // lines 15-15
class QTextEdit;	    // lines 16-16
class SymbolLineEdit;	    // lines 17-17
namespace Ui {
class Interface;
}    // namespace Ui

template<typename T> using not_null_owner = gsl::strict_not_null<gsl::owner<T>>;

/*!
 * Private implementation of the Interface
 */
class InterfacePrivate
{
	Q_DISABLE_COPY_MOVE( InterfacePrivate )
public:
	/*!
	 * Constructor.
	 * \param pi is the pointer to the public part.
	 */
	explicit InterfacePrivate( Ui::Interface* pi );

	virtual ~InterfacePrivate();

	void resizeLineEditWidgets( int w ) const;

private:
	Q_DECLARE_PUBLIC( Ui::Interface )
	Ui::Interface* const q_ptr; /*!< Pointer to the the public part */

	not_null_owner<QGridLayout*> m_gridLayout; /*!< Central grid layout */
	not_null_owner<QGridLayout*> m_buttonsGrid; /*!< Upper grid layout, for the buttons */
	not_null_owner<QGridLayout*> m_tabsGrid; /*!< Last grid layout, for the tabWidget */
	not_null_owner<QGroupBox*>   m_buttonsGroup;
	not_null_owner<QGroupBox*>   m_tabsGroup;
	not_null_owner<QPushButton*> m_closeBtn;
	not_null_owner<QPushButton*> m_searchBtn;
	not_null_owner<QPushButton*> m_resetArgsBtn;
	not_null_owner<QCheckBox*>   m_advancedCheckBox;

	not_null_owner<PluginsComboBox*>   m_scannersBox;
	not_null_owner<SymbolLineEdit*>	   m_symbolEdit;
	not_null_owner<ArgumentsLineEdit*> m_argumentsEdit;

	not_null_owner<QTabWidget*> m_tabWidget;
	not_null_owner<QTextEdit*>  m_textEditStdOut;
	not_null_owner<QTextEdit*>  m_textEditStdErr;
	not_null_owner<QAction*>    m_actionScan;
	not_null_owner<QAction*>    m_actionQuit;
	not_null_owner<QAction*>    m_actionAboutQt;

	void setupConnections();
};

#endif
