#add_library(log SHARED IMPORTED) # or STATIC instead of SHARED
#set_target_properties(log PROPERTIES
	#IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/src/Helper/liblog.so"
	#INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_SOURCE_DIR}/src/Helper/"
#)

set(Driver_SRC  idriver.cpp genericdriver.cpp pluginmanager_p.cpp pluginmanager.cpp)

add_library(driver SHARED ${Driver_SRC})
set_target_properties(driver PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(driver PROPERTIES SOVERSION ${PROJECT_VERSION_MAJOR})

target_link_libraries(driver Qt5::Core Qt5::Widgets)
