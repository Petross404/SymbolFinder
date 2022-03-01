function(handle_docs ${BUILD_DOC})
	if(BUILD_DOC)
		# check if Doxygen is installed
		# Require dot, treat the other components as optional
		find_package(Doxygen REQUIRED dot
			OPTIONAL_COMPONENTS mscgen dia)

		if (DOXYGEN_FOUND)
			# set input and output files
			configure_file("${CMAKE_SOURCE_DIR}/Documentation/Doxyfile.in"
					"${CMAKE_SOURCE_DIR}/Documentation/Doxyfile")

			message(STATUS "Doxygen will compile the docs")

			set(DOXYGEN_GENERATE_HTML YES)
			set(DOXYGEN_GENERATE_LATEX NO)
			set(DOXYGEN_GENERATE_MAN NO)
			set(DOXYGEN_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/Documentation/doc/)
			doxygen_add_docs(doxygen
				${PROJECT_SOURCE_DIR}
				ALL
				COMMENT "Generate documentation")
			#add_dependencies(doxygen configure_files)
		else (DOXYGEN_FOUND)
			message(FATAL_ERROR "Doxygen need to be installed to generate the doxygen documentation")
		endif(DOXYGEN_FOUND)
	endif(BUILD_DOC)
endfunction()
