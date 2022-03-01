function(handle_clazy_dep NAME_OF_TARGET SRC_DIR)

	if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
		set(CLAZY_COMMAND "clazy.exe")
	elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
		set(CLAZY_COMMAND "clazy-standalone")
	endif()

	set(CMAKE_CXX_COMPILER "${CLAZY_COMMAND}")
	set(CMAKE_C_COMPILER "clang")

	add_custom_target(clazy
		DEPENDS ${NAME_OF_TARGET}
		WORKING_DIRECTORY ${SRC_DIR})

	add_dependencies(${NAME_OF_TARGET} config_files)
endfunction()
