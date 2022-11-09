set(Scanner_SRC
	scanner.cpp
)

add_subdirectory(interface/)

add_library(scanner SHARED ${Scanner_SRC})
set_target_properties(scanner PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(scanner PROPERTIES SOVERSION ${PROJECT_VERSION_MAJOR})

target_link_libraries(scanner driver Qt5::Core Qt5::Widgets)

install(TARGETS		scanner
	LIBRARY		DESTINATION "${CMAKE_INSTALL_LIBDIR}/${PROJECT_NAME}"
)
