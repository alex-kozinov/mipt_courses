# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.14

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/alex-kozinov/projects/mipt_courses/computer_graphics

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/alex-kozinov/projects/mipt_courses/computer_graphics/cmake-build-debug

# Include any dependencies generated for this target.
include external/glfw-3.1.2/examples/CMakeFiles/gears.dir/depend.make

# Include the progress variables for this target.
include external/glfw-3.1.2/examples/CMakeFiles/gears.dir/progress.make

# Include the compile flags for this target's objects.
include external/glfw-3.1.2/examples/CMakeFiles/gears.dir/flags.make

external/glfw-3.1.2/examples/CMakeFiles/gears.dir/gears.c.o: external/glfw-3.1.2/examples/CMakeFiles/gears.dir/flags.make
external/glfw-3.1.2/examples/CMakeFiles/gears.dir/gears.c.o: ../external/glfw-3.1.2/examples/gears.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/alex-kozinov/projects/mipt_courses/computer_graphics/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object external/glfw-3.1.2/examples/CMakeFiles/gears.dir/gears.c.o"
	cd /Users/alex-kozinov/projects/mipt_courses/computer_graphics/cmake-build-debug/external/glfw-3.1.2/examples && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/gears.dir/gears.c.o   -c /Users/alex-kozinov/projects/mipt_courses/computer_graphics/external/glfw-3.1.2/examples/gears.c

external/glfw-3.1.2/examples/CMakeFiles/gears.dir/gears.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/gears.dir/gears.c.i"
	cd /Users/alex-kozinov/projects/mipt_courses/computer_graphics/cmake-build-debug/external/glfw-3.1.2/examples && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/alex-kozinov/projects/mipt_courses/computer_graphics/external/glfw-3.1.2/examples/gears.c > CMakeFiles/gears.dir/gears.c.i

external/glfw-3.1.2/examples/CMakeFiles/gears.dir/gears.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/gears.dir/gears.c.s"
	cd /Users/alex-kozinov/projects/mipt_courses/computer_graphics/cmake-build-debug/external/glfw-3.1.2/examples && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/alex-kozinov/projects/mipt_courses/computer_graphics/external/glfw-3.1.2/examples/gears.c -o CMakeFiles/gears.dir/gears.c.s

# Object files for target gears
gears_OBJECTS = \
"CMakeFiles/gears.dir/gears.c.o"

# External object files for target gears
gears_EXTERNAL_OBJECTS =

external/glfw-3.1.2/examples/gears.app/Contents/MacOS/gears: external/glfw-3.1.2/examples/CMakeFiles/gears.dir/gears.c.o
external/glfw-3.1.2/examples/gears.app/Contents/MacOS/gears: external/glfw-3.1.2/examples/CMakeFiles/gears.dir/build.make
external/glfw-3.1.2/examples/gears.app/Contents/MacOS/gears: external/glfw-3.1.2/src/libglfw3.a
external/glfw-3.1.2/examples/gears.app/Contents/MacOS/gears: external/glfw-3.1.2/examples/CMakeFiles/gears.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/alex-kozinov/projects/mipt_courses/computer_graphics/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable gears.app/Contents/MacOS/gears"
	cd /Users/alex-kozinov/projects/mipt_courses/computer_graphics/cmake-build-debug/external/glfw-3.1.2/examples && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/gears.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
external/glfw-3.1.2/examples/CMakeFiles/gears.dir/build: external/glfw-3.1.2/examples/gears.app/Contents/MacOS/gears

.PHONY : external/glfw-3.1.2/examples/CMakeFiles/gears.dir/build

external/glfw-3.1.2/examples/CMakeFiles/gears.dir/clean:
	cd /Users/alex-kozinov/projects/mipt_courses/computer_graphics/cmake-build-debug/external/glfw-3.1.2/examples && $(CMAKE_COMMAND) -P CMakeFiles/gears.dir/cmake_clean.cmake
.PHONY : external/glfw-3.1.2/examples/CMakeFiles/gears.dir/clean

external/glfw-3.1.2/examples/CMakeFiles/gears.dir/depend:
	cd /Users/alex-kozinov/projects/mipt_courses/computer_graphics/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/alex-kozinov/projects/mipt_courses/computer_graphics /Users/alex-kozinov/projects/mipt_courses/computer_graphics/external/glfw-3.1.2/examples /Users/alex-kozinov/projects/mipt_courses/computer_graphics/cmake-build-debug /Users/alex-kozinov/projects/mipt_courses/computer_graphics/cmake-build-debug/external/glfw-3.1.2/examples /Users/alex-kozinov/projects/mipt_courses/computer_graphics/cmake-build-debug/external/glfw-3.1.2/examples/CMakeFiles/gears.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : external/glfw-3.1.2/examples/CMakeFiles/gears.dir/depend

