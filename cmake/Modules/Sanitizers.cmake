# In here we declare a function to handle the sanitizers. There are three of them:
# 1) ASan : AdressSanitizer (includes LSan but with additional checks)
# 2) LSan : LeakSanitizer
# 3) MSan : MemorySanitizer
# Not a signle sanitizer from the above must co-exist with any other. So it makes sense
# to configure and use each of them on their own. That's why we implement three cases
# with if. Also MSan is implemented in Clang AFAIK so there is a check for that too.

function(handle_sanitizers NAME_OF_TARGET ASAN LSAN MSAN)

	message(STATUS "Configuring Sanitizers for TARGET: ${NAME_OF_TARGET}")
	if( ("${ASAN}" AND "${LSAN}")
		OR ("${ASAN}" AND "${MSAN}")
		OR ("${MSAN}" AND "${LSAN}"))
		message(WARNING "You have to choose one sanitizer at the time. Disabling all of them.")
		if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
			message(WARNING "Also MSan is currently supported by Clang only.")
		elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
			# using GCC
		elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  			# using Visual Studio C++
		endif()
		set(ASAN OFF PARENT_SCOPE)
		set(LSAN OFF PARENT_SCOPE)
		set(MSAN OFF PARENT_SCOPE)
	endif()

	if("${ASAN}")
		#Build with ASan only in Debug, else...
		if (CMAKE_BUILD_TYPE STREQUAL "Debug")
			# build with sanitizers
			message(WARNING "Be adviced, ASan will slow down the executable.")
			target_compile_options(${NAME_OF_TARGET} PRIVATE -fno-omit-frame-pointer -g -ggdb -fsanitize=address -fno-omit-frame-pointer)
			target_link_options(${NAME_OF_TARGET}	PRIVATE -fno-omit-frame-pointer -g -ggdb -fsanitize=address -fno-omit-frame-pointer)
		else()
			# ...warn the user and disable the feature.
			message(WARNING "ASan is disabled in non-debug builds.")
			set(${ASAN} OFF PARENT_SCOPE)
		endif()
	elseif("${LSAN}")
		#Build with ASan only in Debug, else...
		if (CMAKE_BUILD_TYPE STREQUAL "Debug")
			# build with sanitizers
			message(WARNING "Be adviced, LSan will slow down the executable.")
			target_compile_options(${NAME_OF_TARGET} PRIVATE -fno-omit-frame-pointer -g -ggdb -fsanitize=leak -fno-omit-frame-pointer)
			target_link_options(${NAME_OF_TARGET}	PRIVATE -fno-omit-frame-pointer -g -ggdb -fsanitize=leak -fno-omit-frame-pointer)
		else()
			# ...warn the user and disable the feature.
			message(WARNING "LSan is disabled in non-debug builds.")
			set(${LSAN} OFF PARENT_SCOPE)
		endif()
	elseif("${MSAN}")
		#Build with MSan only in Debug and compiler is Clang, else...
		if ((CMAKE_BUILD_TYPE STREQUAL "Debug") AND (CMAKE_CXX_COMPILER_ID STREQUAL "Clang"))
			# build with sanitizers
			message(WARNING "Be adviced, MSan will slow down the executable.")
			target_compile_options(${NAME_OF_TARGET} PRIVATE -fno-omit-frame-pointer -g -ggdb -fsanitize=memory -fno-omit-frame-pointer)
			target_link_options(${NAME_OF_TARGET}	PRIVATE -fno-omit-frame-pointer -g -ggdb -fsanitize=memory -fno-omit-frame-pointer)
		elseif(NOT CMAKE_CXX_COMPILER_ID MATCHES "Clang")
			message(WARNING "MSan is implemented in Clang only. Disabled.")
		else()
			# ...warn the user and disable the feature.
			message(WARNING "MSan is disabled in non-debug builds.")
			set(${MSAN} OFF PARENT_SCOPE)
		endif()
	endif()

endfunction()
