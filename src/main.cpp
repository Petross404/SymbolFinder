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

#include <qapplication.h>    // for QApplication
#include <qnamespace.h>	     // for AA_EnableHighDpiSc...

#include <memory>    // for make_unique, uniqu...

#include "Window/MainWindow/findermainwindow.hpp"    // for MainWindow

int main( int argc, char *argv[] )
{
	QApplication::setAttribute( Qt::AA_ShareOpenGLContexts );
	QApplication::setAttribute( Qt::AA_EnableHighDpiScaling );

	std::unique_ptr<QApplication> app{ std::make_unique<QApplication>( argc, argv ) };

	std::unique_ptr<FinderWindow> w{ std::make_unique<FinderWindow>() };
	w->show();

	return app->exec();
}
