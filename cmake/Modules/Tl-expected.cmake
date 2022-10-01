function(handle_tl_expected)
	include(FetchContent)

	FetchContent_Declare(tl-expected
                     GIT_REPOSITORY https://github.com/TartanLlama/expected.git
	)

	FetchContent_GetProperties(tl-expected)
	if(NOT "${tl-expected_POPULATED}")
		FetchContent_Populate(tl-expected)
		add_subdirectory(${tl-expected_SOURCE_DIR} ${tl-expected_BINARY_DIR})
	endif()

	set(tl-expected_DIR "${CMAKE_BINARY_DIR}/_deps/tl-expected-build/")

	find_package(tl-expected CONFIG REQUIRED)

endfunction()

function(handle_tl_expected_dep NAME_OF_TARGET)
	set_target_properties("${NAME_OF_TARGET}" PROPERTIES
		INCLUDE_DIRECTORIES	"${tl_expected_INCLUDE_DIR}"
		LINK_LIBRARIES		"${tl_expected_LIBRARIES}"
		)
endfunction()
