# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.18

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Disable VCS-based implicit rules.
% : %,v


# Disable VCS-based implicit rules.
% : RCS/%


# Disable VCS-based implicit rules.
% : RCS/%,v


# Disable VCS-based implicit rules.
% : SCCS/s.%


# Disable VCS-based implicit rules.
% : s.%


.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/petros/projects/symbolfinder

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/petros/projects/symbolfinder/build

# Include any dependencies generated for this target.
include src/Exceptions/CMakeFiles/exceptions.dir/depend.make

# Include the progress variables for this target.
include src/Exceptions/CMakeFiles/exceptions.dir/progress.make

# Include the compile flags for this target's objects.
include src/Exceptions/CMakeFiles/exceptions.dir/flags.make

src/Exceptions/CMakeFiles/exceptions.dir/exceptions_autogen/mocs_compilation.cpp.o: src/Exceptions/CMakeFiles/exceptions.dir/flags.make
src/Exceptions/CMakeFiles/exceptions.dir/exceptions_autogen/mocs_compilation.cpp.o: src/Exceptions/exceptions_autogen/mocs_compilation.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/petros/projects/symbolfinder/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/Exceptions/CMakeFiles/exceptions.dir/exceptions_autogen/mocs_compilation.cpp.o"
	cd /home/petros/projects/symbolfinder/build/src/Exceptions && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/exceptions.dir/exceptions_autogen/mocs_compilation.cpp.o -c /home/petros/projects/symbolfinder/build/src/Exceptions/exceptions_autogen/mocs_compilation.cpp

src/Exceptions/CMakeFiles/exceptions.dir/exceptions_autogen/mocs_compilation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/exceptions.dir/exceptions_autogen/mocs_compilation.cpp.i"
	cd /home/petros/projects/symbolfinder/build/src/Exceptions && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/petros/projects/symbolfinder/build/src/Exceptions/exceptions_autogen/mocs_compilation.cpp > CMakeFiles/exceptions.dir/exceptions_autogen/mocs_compilation.cpp.i

src/Exceptions/CMakeFiles/exceptions.dir/exceptions_autogen/mocs_compilation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/exceptions.dir/exceptions_autogen/mocs_compilation.cpp.s"
	cd /home/petros/projects/symbolfinder/build/src/Exceptions && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/petros/projects/symbolfinder/build/src/Exceptions/exceptions_autogen/mocs_compilation.cpp -o CMakeFiles/exceptions.dir/exceptions_autogen/mocs_compilation.cpp.s

# Object files for target exceptions
exceptions_OBJECTS = \
"CMakeFiles/exceptions.dir/exceptions_autogen/mocs_compilation.cpp.o"

# External object files for target exceptions
exceptions_EXTERNAL_OBJECTS =

src/Exceptions/libexceptions.so.0.0.1: src/Exceptions/CMakeFiles/exceptions.dir/exceptions_autogen/mocs_compilation.cpp.o
src/Exceptions/libexceptions.so.0.0.1: src/Exceptions/CMakeFiles/exceptions.dir/build.make
src/Exceptions/libexceptions.so.0.0.1: /usr/lib/x86_64-linux-gnu/libQt5Core.so.5.15.2
src/Exceptions/libexceptions.so.0.0.1: src/Exceptions/CMakeFiles/exceptions.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/petros/projects/symbolfinder/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared library libexceptions.so"
	cd /home/petros/projects/symbolfinder/build/src/Exceptions && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/exceptions.dir/link.txt --verbose=$(VERBOSE)
	cd /home/petros/projects/symbolfinder/build/src/Exceptions && $(CMAKE_COMMAND) -E cmake_symlink_library libexceptions.so.0.0.1 libexceptions.so.0 libexceptions.so

src/Exceptions/libexceptions.so.0: src/Exceptions/libexceptions.so.0.0.1
	@$(CMAKE_COMMAND) -E touch_nocreate src/Exceptions/libexceptions.so.0

src/Exceptions/libexceptions.so: src/Exceptions/libexceptions.so.0.0.1
	@$(CMAKE_COMMAND) -E touch_nocreate src/Exceptions/libexceptions.so

# Rule to build all files generated by this target.
src/Exceptions/CMakeFiles/exceptions.dir/build: src/Exceptions/libexceptions.so

.PHONY : src/Exceptions/CMakeFiles/exceptions.dir/build

src/Exceptions/CMakeFiles/exceptions.dir/clean:
	cd /home/petros/projects/symbolfinder/build/src/Exceptions && $(CMAKE_COMMAND) -P CMakeFiles/exceptions.dir/cmake_clean.cmake
.PHONY : src/Exceptions/CMakeFiles/exceptions.dir/clean

src/Exceptions/CMakeFiles/exceptions.dir/depend:
	cd /home/petros/projects/symbolfinder/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/petros/projects/symbolfinder /home/petros/projects/symbolfinder/src/Exceptions /home/petros/projects/symbolfinder/build /home/petros/projects/symbolfinder/build/src/Exceptions /home/petros/projects/symbolfinder/build/src/Exceptions/CMakeFiles/exceptions.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/Exceptions/CMakeFiles/exceptions.dir/depend

