function(handle_conan_expected_dep NAME_OF_TARGET)
	conan_cmake_configure(REQUIRES tl-expected/20190710
			GENERATORS cmake_find_package)

	conan_cmake_autodetect(settings)

	conan_add_remote(NAME "cci"
		INDEX 1
		URL "https://center.conan.io"
		VERIFY_SSL True)

	set(THIRD_PARTY "${CMAKE_SOURCE_DIR}/3rdparty")

	conan_cmake_install(PATH_OR_REFERENCE .
                    #BUILD missing
                    REMOTE cci
                    SETTINGS ${settings}
                    INSTALL_FOLDER "${THIRD_PARTY}"
                    OUTPUT_FOLDER "${THIRD_PARTY}"
                    UPDATE)

	set(CMAKE_MODULE_PATH "${THIRD_PARTY}")

	# Iterate over every path in CMAKE_MODULE_PATH to find it.
	foreach(PATH "${CMAKE_MODULE_PATH}")
		if(EXISTS "${PATH}/Findtl-expected.cmake")
			include("${PATH}/Findtl-expected.cmake")
		endif()
	endforeach()

	find_package(tl-expected REQUIRED)

	message(STATUS ${tl_expected_INCLUDE_DIRS})
	target_include_directories("${NAME_OF_TARGET}" PRIVATE "${tl_expected_INCLUDE_DIRS}")
	target_link_directories("${NAME_OF_TARGET}" PRIVATE "${tl_expected_INCLUDE_DIRS}")

endfunction()
