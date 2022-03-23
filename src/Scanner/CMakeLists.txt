set(Scanner_SRC
	scanner.cpp
	Drivers/idriver.cpp
	Drivers/driver.cpp
	Drivers/nmdriver.cpp
	Drivers/scanelfdriver.cpp)

add_library(scanner SHARED ${Scanner_SRC})
set_target_properties(scanner PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(scanner PROPERTIES SOVERSION ${PROJECT_VERSION_MAJOR})
target_link_libraries(scanner Qt5::Core Qt5::Widgets)
