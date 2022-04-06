set(Execptions_SRC
	connectexception.cpp
)

add_library(exceptions SHARED ${Nm_SRC})
set_target_properties(exceptions PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(exceptions PROPERTIES SOVERSION ${PROJECT_VERSION_MAJOR})

target_link_libraries(exceptions Qt5::Core)
