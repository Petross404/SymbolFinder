set(Nm_SRC nmdriver.cpp)

add_library(nmplugin MODULE ${Nm_SRC})
set_target_properties(nmplugin PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(nmplugin PROPERTIES SOVERSION ${PROJECT_VERSION_MAJOR})

target_link_libraries(nmplugin driver Qt5::Core Qt5::Widgets)

set(Scanelf_SRC scanelfdriver.cpp)

add_library(scanelfplugin MODULE ${Scanelf_SRC})
set_target_properties(scanelfplugin PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(scanelfplugin PROPERTIES SOVERSION ${PROJECT_VERSION_MAJOR})

target_link_libraries(scanelfplugin driver Qt5::Core Qt5::Widgets)
