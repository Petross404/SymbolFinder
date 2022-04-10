set(Driver_SRC  idriver.cpp driver.cpp driverfactory.cpp pluginmanager.cpp)

add_library(driver SHARED ${Driver_SRC})
set_target_properties(driver PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(driver PROPERTIES SOVERSION ${PROJECT_VERSION_MAJOR})

target_link_libraries(driver Qt5::Core Qt5::Widgets)
