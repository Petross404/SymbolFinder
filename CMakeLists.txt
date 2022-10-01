cmake_minimum_required(VERSION 3.0)

project("SymbolFinder"
	VERSION		0.0.1
	DESCRIPTION	"Find which library defines or uses a symbol"
	HOMEPAGE_URL	"https://gitlab.com/Petross404/symbolfinder")

#Set the language standard.
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(GNUInstallDirs)
include(FindDoxygen)
include(FindGSL)
include(CMakeParseArguments)

#Set this variable so it can save the conan.cmake
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules")

# Include custom cmake scripts as well

include(GNUInstallDirs)
include("${CMAKE_MODULE_PATH}/Sanitizers.cmake")
include("${CMAKE_MODULE_PATH}/ClangFormat.cmake")
include("${CMAKE_MODULE_PATH}/ClangTidy.cmake")
include("${CMAKE_MODULE_PATH}/Configure.cmake")
include("${CMAKE_MODULE_PATH}/IncludeUse.cmake")
include("${CMAKE_MODULE_PATH}/BuildDoc.cmake")
include("${CMAKE_MODULE_PATH}/BuildPlugins.cmake")
#include("${CMAKE_MODULE_PATH}/Tl-expected.cmake")

#handle_tl_expected()

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)
# Instruct CMake to create code from Qt ui files
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Find the QtWidgets library
find_package(Qt5 COMPONENTS Core Widgets Gui CONFIG REQUIRED)

find_package(GSL REQUIRED)

find_package(fmt REQUIRED)


#Create a clang_format target.
handle_dependency_clang_format()

##Add libfilename here.
#add_subdirectory(src/Helper)

#Add libscanner here.
add_subdirectory(src/Scanner)

#Add Exceptions here.
#add_subdirectory(src/Exceptions)

#Set source code variables.
set( DriverWidgets_SRC
	src/DriverWidgets/implementation/argumentslineedit_p.cpp
	src/DriverWidgets/implementation/messagewidget_p.cpp
	src/DriverWidgets/implementation/plugincombobox_p.cpp
	src/DriverWidgets/argumentslineedit.cpp
	src/DriverWidgets/symbollineedit.cpp
	src/DriverWidgets/messagewidget.cpp
	src/DriverWidgets/pluginscombobox.cpp
)

set( Helper_SRC
	src/Helper/string.cpp)

set( symbolfinder_SRC
	src/main.cpp
	src/Window/MainWindow/findermainwindow.cpp
	src/Window/MainWindow/implementation/finderwindow_p.cpp
	src/Window/MainWindow/UI/implementation/ui_p.cpp
	src/Window/MainWindow/UI/ui.cpp
	src/ConnectVerifier/connectverifier.cpp
)

#Add Qt's resource file here.
set_property( SOURCE src/resources.qrc PROPERTY AUTORCC_OPTIONS "--compress;9" )

# Tell CMake to create the symbolfinder executable
add_executable( symbolfinder ${symbolfinder_SRC} ${DriverWidgets_SRC} ${Helper_SRC} src/resources.qrc )

handle_in_files(symbolfinder ${CMAKE_SOURCE_DIR})
#handle_tl_expected_dep(symbolfinder)

#############Option to handle the documentation generation#############
option( BUILD_DOC "Build documentation with Doxygen." OFF )
if( BUILD_DOC )
	add_subdirectory(Documentation)
endif( BUILD_DOC )

####################Configure the Sanitizers###########################
option( ENABLE_ASAN "Build with AddressSanitizer (ASan)." OFF )
option( ENABLE_LSAN "Build with LeakSanitizer (LSan)." OFF )
option( ENABLE_MSAN "Build with MemorySanitizer (MSan)." OFF )

handle_sanitizers( symbolfinder
			${ENABLE_ASAN}
			${ENABLE_LSAN}
			${ENABLE_MSAN} )

####################Option to compile with iwyu#######################
option(INCLUDE_USE "Build with iwyu to analyze includes." OFF)
handle_include_use(symbolfinder ${INCLUDE_USE})

# Use the Widgets module from Qt 5.
target_link_libraries( symbolfinder scanner Qt5::Core Qt5::Widgets Qt5::Gui fmt::fmt)

# Install the executable
install( TARGETS symbolfinder
	RUNTIME		DESTINATION ${CMAKE_INSTALL_BINDIR}
	LIBRARY		DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
