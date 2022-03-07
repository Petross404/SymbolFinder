/********************************************************************************
** Form generated from reading UI file 'findermainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FINDERMAINWINDOW_H
#define UI_FINDERMAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
	QAction	*actionQuit;
	QAction	*actionAbout;
	QWidget	*centralWidget;
	QGridLayout  *gridLayout;
	QGridLayout  *gridLayout_Central;
	QGridLayout  *gridLayout_Buttons;
	QGroupBox	  *groupBox_Buttons;
	QGridLayout  *gridLayout_3;
	QComboBox	  *comboBoxDrivers;
	QCheckBox	  *checkBox;
	QPushButton  *pbtnClear;
	QPushButton  *pbtnSearch;
	QGridLayout  *gridLayout_ToolBox;
	QGroupBox	  *groupBox_Output;
	QGridLayout  *gridLayout_4;
	QGridLayout  *gridLayout_groupBoxOutput;
	QTabWidget   *tabWidget;
	QWidget	*tabStdOut;
	QGridLayout  *gridLayout_2;
	QGridLayout  *gridLayout_5;
	QScrollArea  *scrollAreaStdOut;
	QWidget	*scrollAreaWidgetContentsStdOut;
	QGridLayout  *gridLayout_6;
	QTextBrowser *textBrowserStdOut;
	QWidget	*tabStdError;
	QGridLayout  *gridLayout_8;
	QGridLayout  *gridLayout_7;
	QScrollArea  *scrollAreaStdError;
	QWidget	*scrollAreaWidgetContentsStdError;
	QGridLayout  *gridLayout_9;
	QTextBrowser *textBrowserStdError;
	QSpacerItem  *verticalSpacer;
	QMenuBar	 *menuBar;
	QMenu	      *menuFile;
	QMenu	      *menuHelp;
	QToolBar	 *mainToolBar;
	QStatusBar   *statusBar;

	void setupUi( QMainWindow *MainWindow )
	{
		if ( MainWindow->objectName().isEmpty() )
			MainWindow->setObjectName(
				QString::fromUtf8( "MainWindow" ) );
		MainWindow->resize( 1330, 891 );
		actionQuit = new QAction( MainWindow );
		actionQuit->setObjectName( QString::fromUtf8( "actionQuit" ) );
		actionAbout = new QAction( MainWindow );
		actionAbout->setObjectName(
			QString::fromUtf8( "actionAbout" ) );
		centralWidget = new QWidget( MainWindow );
		centralWidget->setObjectName(
			QString::fromUtf8( "centralWidget" ) );
		gridLayout = new QGridLayout( centralWidget );
		gridLayout->setObjectName( QString::fromUtf8( "gridLayout" ) );
		gridLayout_Central = new QGridLayout();
		gridLayout_Central->setObjectName(
			QString::fromUtf8( "gridLayout_Central" ) );
		gridLayout_Buttons = new QGridLayout();
		gridLayout_Buttons->setObjectName(
			QString::fromUtf8( "gridLayout_Buttons" ) );
		groupBox_Buttons = new QGroupBox( centralWidget );
		groupBox_Buttons->setObjectName(
			QString::fromUtf8( "groupBox_Buttons" ) );
		gridLayout_3 = new QGridLayout( groupBox_Buttons );
		gridLayout_3->setObjectName(
			QString::fromUtf8( "gridLayout_3" ) );
		comboBoxDrivers = new QComboBox( groupBox_Buttons );
		comboBoxDrivers->setObjectName(
			QString::fromUtf8( "comboBoxDrivers" ) );
		comboBoxDrivers->setMinimumSize( QSize( 250, 0 ) );

		gridLayout_3->addWidget( comboBoxDrivers, 2, 0, 1, 1 );

		checkBox = new QCheckBox( groupBox_Buttons );
		checkBox->setObjectName( QString::fromUtf8( "checkBox" ) );

		gridLayout_3->addWidget( checkBox, 3, 0, 1, 1 );

		pbtnClear = new QPushButton( groupBox_Buttons );
		pbtnClear->setObjectName( QString::fromUtf8( "pbtnClear" ) );
		pbtnClear->setMinimumSize( QSize( 150, 0 ) );

		gridLayout_3->addWidget( pbtnClear, 2, 2, 1, 1 );

		pbtnSearch = new QPushButton( groupBox_Buttons );
		pbtnSearch->setObjectName( QString::fromUtf8( "pbtnSearch" ) );
		pbtnSearch->setMinimumSize( QSize( 150, 0 ) );

		gridLayout_3->addWidget( pbtnSearch, 2, 1, 1, 1 );

		gridLayout_Buttons->addWidget( groupBox_Buttons, 0, 0, 1, 1 );

		gridLayout_Central->addLayout( gridLayout_Buttons, 0, 0, 1, 1 );

		gridLayout_ToolBox = new QGridLayout();
		gridLayout_ToolBox->setObjectName(
			QString::fromUtf8( "gridLayout_ToolBox" ) );
		groupBox_Output = new QGroupBox( centralWidget );
		groupBox_Output->setObjectName(
			QString::fromUtf8( "groupBox_Output" ) );
		gridLayout_4 = new QGridLayout( groupBox_Output );
		gridLayout_4->setObjectName(
			QString::fromUtf8( "gridLayout_4" ) );
		gridLayout_groupBoxOutput = new QGridLayout();
		gridLayout_groupBoxOutput->setObjectName(
			QString::fromUtf8( "gridLayout_groupBoxOutput" ) );
		tabWidget = new QTabWidget( groupBox_Output );
		tabWidget->setObjectName( QString::fromUtf8( "tabWidget" ) );
		tabStdOut = new QWidget();
		tabStdOut->setObjectName( QString::fromUtf8( "tabStdOut" ) );
		gridLayout_2 = new QGridLayout( tabStdOut );
		gridLayout_2->setObjectName(
			QString::fromUtf8( "gridLayout_2" ) );
		gridLayout_5 = new QGridLayout();
		gridLayout_5->setObjectName(
			QString::fromUtf8( "gridLayout_5" ) );
		scrollAreaStdOut = new QScrollArea( tabStdOut );
		scrollAreaStdOut->setObjectName(
			QString::fromUtf8( "scrollAreaStdOut" ) );
		scrollAreaStdOut->setWidgetResizable( true );
		scrollAreaWidgetContentsStdOut = new QWidget();
		scrollAreaWidgetContentsStdOut->setObjectName(
			QString::fromUtf8( "scrollAreaWidgetContentsStdOut" ) );
		scrollAreaWidgetContentsStdOut->setGeometry( QRect( 0, 0, 1270, 242 ) );
		gridLayout_6 = new QGridLayout( scrollAreaWidgetContentsStdOut );
		gridLayout_6->setObjectName(
			QString::fromUtf8( "gridLayout_6" ) );
		textBrowserStdOut = new QTextBrowser( scrollAreaWidgetContentsStdOut );
		textBrowserStdOut->setObjectName(
			QString::fromUtf8( "textBrowserStdOut" ) );
		textBrowserStdOut->setFrameShape( QFrame::WinPanel );
		textBrowserStdOut->setFrameShadow( QFrame::Raised );

		gridLayout_6->addWidget( textBrowserStdOut, 0, 0, 1, 1 );

		scrollAreaStdOut->setWidget( scrollAreaWidgetContentsStdOut );

		gridLayout_5->addWidget( scrollAreaStdOut, 0, 0, 1, 1 );

		gridLayout_2->addLayout( gridLayout_5, 0, 0, 1, 1 );

		tabWidget->addTab( tabStdOut, QString() );
		tabStdError = new QWidget();
		tabStdError->setObjectName(
			QString::fromUtf8( "tabStdError" ) );
		gridLayout_8 = new QGridLayout( tabStdError );
		gridLayout_8->setObjectName(
			QString::fromUtf8( "gridLayout_8" ) );
		gridLayout_7 = new QGridLayout();
		gridLayout_7->setObjectName(
			QString::fromUtf8( "gridLayout_7" ) );
		scrollAreaStdError = new QScrollArea( tabStdError );
		scrollAreaStdError->setObjectName(
			QString::fromUtf8( "scrollAreaStdError" ) );
		scrollAreaStdError->setWidgetResizable( true );
		scrollAreaWidgetContentsStdError = new QWidget();
		scrollAreaWidgetContentsStdError->setObjectName( QString::fromUtf8(
			"scrollAreaWidgetContentsStdError" ) );
		scrollAreaWidgetContentsStdError->setGeometry( QRect( 0, 0, 99, 99 ) );
		gridLayout_9 = new QGridLayout( scrollAreaWidgetContentsStdError );
		gridLayout_9->setObjectName(
			QString::fromUtf8( "gridLayout_9" ) );
		textBrowserStdError =
			new QTextBrowser( scrollAreaWidgetContentsStdError );
		textBrowserStdError->setObjectName(
			QString::fromUtf8( "textBrowserStdError" ) );

		gridLayout_9->addWidget( textBrowserStdError, 0, 0, 1, 1 );

		scrollAreaStdError->setWidget( scrollAreaWidgetContentsStdError );

		gridLayout_7->addWidget( scrollAreaStdError, 0, 0, 1, 1 );

		gridLayout_8->addLayout( gridLayout_7, 0, 0, 1, 1 );

		tabWidget->addTab( tabStdError, QString() );

		gridLayout_groupBoxOutput->addWidget( tabWidget, 0, 0, 1, 1 );

		gridLayout_4->addLayout( gridLayout_groupBoxOutput, 0, 0, 1, 1 );

		gridLayout_ToolBox->addWidget( groupBox_Output, 1, 0, 1, 1 );

		verticalSpacer =
			new QSpacerItem( 20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding );

		gridLayout_ToolBox->addItem( verticalSpacer, 0, 0, 1, 1 );

		gridLayout_Central->addLayout( gridLayout_ToolBox, 2, 0, 1, 1 );

		gridLayout->addLayout( gridLayout_Central, 0, 2, 1, 1 );

		MainWindow->setCentralWidget( centralWidget );
		menuBar = new QMenuBar( MainWindow );
		menuBar->setObjectName( QString::fromUtf8( "menuBar" ) );
		menuBar->setGeometry( QRect( 0, 0, 1330, 30 ) );
		menuFile = new QMenu( menuBar );
		menuFile->setObjectName( QString::fromUtf8( "menuFile" ) );
		menuHelp = new QMenu( menuBar );
		menuHelp->setObjectName( QString::fromUtf8( "menuHelp" ) );
		MainWindow->setMenuBar( menuBar );
		mainToolBar = new QToolBar( MainWindow );
		mainToolBar->setObjectName(
			QString::fromUtf8( "mainToolBar" ) );
		MainWindow->addToolBar( Qt::TopToolBarArea, mainToolBar );
		statusBar = new QStatusBar( MainWindow );
		statusBar->setObjectName( QString::fromUtf8( "statusBar" ) );
		MainWindow->setStatusBar( statusBar );

		menuBar->addAction( menuFile->menuAction() );
		menuBar->addAction( menuHelp->menuAction() );
		menuFile->addAction( actionQuit );
		menuHelp->addAction( actionAbout );

		retranslateUi( MainWindow );

		tabWidget->setCurrentIndex( 0 );

		QMetaObject::connectSlotsByName( MainWindow );
	}    // setupUi

	void retranslateUi( QMainWindow *MainWindow )
	{
		MainWindow->setWindowTitle(
			QCoreApplication::translate( "MainWindow",
						     "FinderMainWindow",
						     nullptr ) );
		actionQuit->setText(
			QCoreApplication::translate( "MainWindow", "Quit", nullptr ) );
		actionAbout->setText(
			QCoreApplication::translate( "MainWindow", "About", nullptr ) );
		groupBox_Buttons->setTitle(
			QCoreApplication::translate( "MainWindow",
						     "Symbol name and options",
						     nullptr ) );
		checkBox->setText( QCoreApplication::translate(
			"MainWindow",
			"Advanced Option Handling:",
			nullptr ) );
		pbtnClear->setText(
			QCoreApplication::translate( "MainWindow", "Clear / Cancel", nullptr ) );
		pbtnSearch->setText(
			QCoreApplication::translate( "MainWindow", "Search", nullptr ) );
		groupBox_Output->setTitle(
			QCoreApplication::translate( "MainWindow", "Ouput", nullptr ) );
		tabWidget->setTabText(
			tabWidget->indexOf( tabStdOut ),
			QCoreApplication::translate( "MainWindow", "Tab 1", nullptr ) );
		tabWidget->setTabText(
			tabWidget->indexOf( tabStdError ),
			QCoreApplication::translate( "MainWindow", "Tab 2", nullptr ) );
		menuFile->setTitle(
			QCoreApplication::translate( "MainWindow", "File", nullptr ) );
		menuHelp->setTitle(
			QCoreApplication::translate( "MainWindow", "Help", nullptr ) );
	}    // retranslateUi
};

namespace Ui {
class MainWindow: public Ui_MainWindow
{
};
}    // namespace Ui

QT_END_NAMESPACE

#endif	  // UI_FINDERMAINWINDOW_H
