set(SRC_DIR ${CMAKE_SOURCE_DIR}/../../..)

set(VARIABLES_IN_HPP_INP	"src/functions/variables.hpp.in")
set(VARIABLES_HPP_OUT		"src/functions/variables.hpp")
#message(STATUS	"${SRC_DIR}/${VARIABLES_IN_HPP_INP}")

set(ABOUT_IN_HPP_INP	"src/AboutDialog/about.hpp.in")
set(ABOUT_HPP_OUT	"src/AboutDialog/about.hpp")
#message(STATUS	"${SRC_DIR}/${ABOUT_IN_HPP_INP}")

set(MATERIALS_PATH_INP	"src/dialog/materials/path.hpp.in")
set(MATERIALS_PATH_OUTP	"src/dialog/materials/path.hpp")

configure_file("${SRC_DIR}/${VARIABLES_IN_HPP_INP}"
	"${SRC_DIR}/${VARIABLES_HPP_OUT}")

configure_file("${SRC_DIR}/${ABOUT_IN_HPP_INP}"
	"${SRC_DIR}/${ABOUT_HPP_OUT}")

configure_file("${SRC_DIR}/${MATERIALS_PATH_INP}"
	"${SRC_DIR}/${MATERIALS_PATH_OUTP}")

set(CLEAN_NO_CUSTOM FALSE)
