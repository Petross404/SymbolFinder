cmake_minimum_required(VERSION 3.0)

project("SymbolFinder"
	VERSION		0.0.1
	DESCRIPTION	"Find which library defines or uses a symbol"
	HOMEPAGE_URL	"")

include(GNUInstallDirs)
include(FindDoxygen)
include(FindGSL)
include(CMakeParseArguments)

# Include custom cmake scripts as well
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules")
include("${CMAKE_MODULE_PATH}/Sanitizers.cmake")
include("${CMAKE_MODULE_PATH}/ClangFormat.cmake")
include("${CMAKE_MODULE_PATH}/ClangTidy.cmake")
include("${CMAKE_MODULE_PATH}/IncludeUse.cmake")
include("${CMAKE_MODULE_PATH}/BuildDoc.cmake")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)
# Instruct CMake to create code from Qt designer ui files
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Find the QtWidgets library
find_package(Qt5 COMPONENTS Core Widgets Gui CONFIG REQUIRED)

find_package(GSL REQUIRED)

handle_dependency_clang_format()

set(symbolfinder_SRC
	src/main.cpp
	src/UI/interface.cpp
	src/findermainwindow.cpp
	src/idriver.cpp
	src/nmdriver.cpp
	src/ConnectVerifier/connectverifier.cpp
	src/scanner.cpp
	src/DriverWidgets/argumentslineedit.cpp
	src/DriverWidgets/symbollineedit.cpp
	src/DriverWidgets/messagewidget.cpp
)

set_property(SOURCE src/resources.qrc PROPERTY AUTORCC_OPTIONS "--compress;9")

# Tell CMake to create the helloworld executable
add_executable(symbolfinder ${symbolfinder_SRC} src/resources.qrc)

#############Option to handle the documentation generation#############
option(BUILD_DOC "Build documentation with Doxygen." OFF)
if(BUILD_DOC)
	add_subdirectory(Documentation)
endif(BUILD_DOC)

####################Configure the Sanitizers###########################
option(ENABLE_ASAN "Build with AddressSanitizer (ASan)." OFF)
option(ENABLE_LSAN "Build with LeakSanitizer (LSan)." OFF)
option(ENABLE_MSAN "Build with MemorySanitizer (MSan)." OFF)

handle_sanitizers(symbolfinder
			${ENABLE_ASAN}
			${ENABLE_LSAN}
			${ENABLE_MSAN})

# Use the Widgets module from Qt 5.
target_link_libraries(symbolfinder Qt5::Widgets Qt5::Widgets Qt5::Gui)

# Install the executable
install(TARGETS symbolfinder DESTINATION bin)
