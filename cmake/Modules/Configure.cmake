function(handle_in_files NAME_OF_TARGET SRC_DIR)
	add_custom_command(OUTPUT file_
		COMMAND		${CMAKE_COMMAND} -P ${SRC_DIR}/cmake/Modules/scripts/ConfigScript.cmake

		BYPRODUCTS	${VARIABLES_HPP_OUT}
		WORKING_DIRECTORY ${SRC_DIR}/cmake/Modules/scripts
		COMMENT		"Configuring *.in files."
		VERBATIM)

	add_custom_target(config_files
		DEPENDS file_
		WORKING_DIRECTORY ${SRC_DIR}
		SOURCES ${SRC_DIR}/src/AboutDialog/about.hpp ${SRC_DIR}/src/functions/variables.hpp ${SRC_DIR}/src/dialog/materials/path.hpp)

	add_dependencies(${NAME_OF_TARGET} config_files)
endfunction()
