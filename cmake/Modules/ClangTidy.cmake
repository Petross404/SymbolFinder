function(handle_dependency_clang_tidy)
	find_program(CLANG_TIDY "clang-tidy")

	if(CLANG_TIDY)
    		file(GLOB_RECURSE ALL_CXX_SOURCE_FILES
        		${PROJECT_SOURCE_DIR}/src/*.[ch]pp
        		${PROJECT_SOURCE_DIR}/src/*.[ch]
        		${PROJECT_SOURCE_DIR}/include/*.[h]pp
        		${PROJECT_SOURCE_DIR}/include/*.[h]
    		)

    		add_custom_target(clang_tidy
        		COMMAND clang-tidy
        		${ALL_CXX_SOURCE_FILES}
        		-format-style=file
        		--
        		-std=c++17
        		-I{PROJECT_ROOT_DIR}/include
    		)
	endif()

endfunction()
