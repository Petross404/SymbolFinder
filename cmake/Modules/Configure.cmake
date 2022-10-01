function(handle_in_files NAME_OF_TARGET SRC_DIR)
	set(POLICY CMP0115)
	add_custom_command(OUTPUT file_
		COMMAND		${CMAKE_COMMAND} -P ${SRC_DIR}/cmake/Modules/scripts/ConfigScript.cmake
		ARGS		S{CMAKE_CURRENT_BINARY_DIR}

		BYPRODUCTS	${VARIABLES_HPP_OUT}
		WORKING_DIRECTORY ${SRC_DIR}/cmake/Modules/scripts
		COMMENT		"Configuring *.in files."
		VERBATIM)

	add_custom_target(config_files
		DEPENDS	file_
		WORKING_DIRECTORY ${SRC_DIR}
		SOURCES ${SRC_DIR}/src/Scanner/interface/builddir.hpp.in ${SRC_DIR}/src/Scanner/interface/builddir.hpp )

	add_dependencies(${NAME_OF_TARGET} config_files)
endfunction()
