function(handle_dependency_clang_format)
	find_program(CLANG_FORMAT "clang-format")

	if(CLANG_FORMAT)
		#file(GLOB_RECURSE ALL_CXX_SOURCE_FILES
			#${PROJECT_SOURCE_DIR}/*.[ch]pp)

		add_custom_command(OUTPUT clang_format_
			COMMAND		${CMAKE_SOURCE_DIR}/tools/clang-format.sh
			WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
			COMMENT		"Running clang-format.sh. Please wait until this job is finished.")

		add_custom_target(clang_format
			DEPENDS clang_format_
			WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
	else()
		message(WARNING "CMake failed to create a target for clang-format. Is clang-format installed?")
	endif()

endfunction()
