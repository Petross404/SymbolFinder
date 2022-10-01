function(handle_qt CMAKE_AUTOMOC CMAKE_AUTOUIC CMAKE_AUTORCC)
	############## Find the Qt5 library ####################
	find_package(Qt5 COMPONENTS Core Widgets Gui CONFIG REQUIRED)
	if(Qt5Core_FOUND AND Qt5Widgets_FOUND AND Qt5Gui_FOUND)
		# QT5 found, is it the minimum required version?
		if(Qt5_VERSION VERSION_GREATER 5.4)
			# This policy prefers sets OpenGL_GL_PREFERENCE to "GLVND"
			if (POLICY CMP0072)
				cmake_policy (SET CMP0072 NEW)
			endif(POLICY CMP0072)
			## QT is OK, now check for OpenGL
			find_package(OpenGL REQUIRED)
		endif()

		set(Qt5::Core			Qt5Core_LIBRARIES PARENT_SCOPE)
		set(Qt5::Widgets		Qt5Widgets_LIBRARIES PARENT_SCOPE)
		set(Qt5::Gui			Qt5Gui_LIBRARIES PARENT_SCOPE)
		set(Qt5Core_VERSION_MAJOR	Qt5Core_VERSION_MAJOR PARENT_SCOPE)
		set(Qt5Widgets_VERSION_MAJOR	Qt5Widgets_VERSION_MAJOR PARENT_SCOPE)
		set(Qt5Gui_VERSION_MAJOR	Qt5Gui_VERSION_MAJOR PARENT_SCOPE)
	endif()

endfunction()
