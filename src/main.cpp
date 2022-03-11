#include <qapplication.h>    // for QApplication

#include "findermainwindow.hpp"	   // for MainWindow

int main( int argc, char *argv[] )
{
	QApplication app( argc, argv );
	MainWindow   w;
	w.show();

	return app.exec();
}
