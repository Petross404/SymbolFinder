function(handle_plugins ${BUILD_PLUGINS})
	if(BUILD_PLUGINS)
		add_subdirectory(${CMAKE_SOURCE_DIR}/src/Scanner/plugins)
	endif()
endfunction()
