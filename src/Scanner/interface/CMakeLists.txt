set(Driver_SRC  idriver.cpp genericdriver.cpp pluginmanager_p.cpp pluginmanager.cpp)

add_library(driver SHARED ${Driver_SRC})
set_target_properties(driver PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(driver PROPERTIES SOVERSION ${PROJECT_VERSION_MAJOR})

target_link_libraries(driver Qt5::Core Qt5::Widgets)

install(TARGETS		driver
	LIBRARY		DESTINATION "${CMAKE_INSTALL_LIBDIR}/${PROJECT_NAME}"
)
