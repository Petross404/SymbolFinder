set(log_SRC filename.cpp)

add_library(log SHARED ${log_SRC})
set_target_properties(log PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(log PROPERTIES SOVERSION ${PROJECT_VERSION_MAJOR})
