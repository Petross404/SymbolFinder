set(SRC_DIR ${CMAKE_SOURCE_DIR}/../../..)

#set(MATERIALS_PATH_INP	"src/dialog/materials/path.hpp.in")
#set(MATERIALS_PATH_OUTP	"src/dialog/materials/path.hpp")

#configure_file("${SRC_DIR}/${MATERIALS_PATH_INP}"
	#"${SRC_DIR}/${MATERIALS_PATH_OUTP}")

set(BUILD_PATH_IN	${SRC_DIR}/src/Scanner/interface/builddir.hpp.in)
set(BUILD_PATH_OUT	${SRC_DIR}/src/Scanner/interface/builddir.hpp)

configure_file("${BUILD_PATH_IN}" "${BUILD_PATH_OUT}")

set(CLEAN_NO_CUSTOM FALSE)
