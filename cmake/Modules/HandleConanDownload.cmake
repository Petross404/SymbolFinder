
function(handle_conan_download)
	#Download conan cmake
	if( NOT EXISTS "${CMAKE_MODULE_PATH}/conan.cmake")
		message( STATUS "Downloading conan.cmake" )
		file( DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/develop/conan.cmake"
			"${CMAKE_MODULE_PATH}/conan.cmake"
			SHOW_PROGRESS
			TIMEOUT 30
			TLS_VERIFY ON )
	endif()
endfunction()
