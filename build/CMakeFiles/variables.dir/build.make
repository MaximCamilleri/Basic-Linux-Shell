# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/max/assignment

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/max/assignment/build

# Include any dependencies generated for this target.
include CMakeFiles/variables.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/variables.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/variables.dir/flags.make

CMakeFiles/variables.dir/variables.c.o: CMakeFiles/variables.dir/flags.make
CMakeFiles/variables.dir/variables.c.o: ../variables.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/max/assignment/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/variables.dir/variables.c.o"
	/bin/gcc-9 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/variables.dir/variables.c.o   -c /home/max/assignment/variables.c

CMakeFiles/variables.dir/variables.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/variables.dir/variables.c.i"
	/bin/gcc-9 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/max/assignment/variables.c > CMakeFiles/variables.dir/variables.c.i

CMakeFiles/variables.dir/variables.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/variables.dir/variables.c.s"
	/bin/gcc-9 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/max/assignment/variables.c -o CMakeFiles/variables.dir/variables.c.s

# Object files for target variables
variables_OBJECTS = \
"CMakeFiles/variables.dir/variables.c.o"

# External object files for target variables
variables_EXTERNAL_OBJECTS =

variables: CMakeFiles/variables.dir/variables.c.o
variables: CMakeFiles/variables.dir/build.make
variables: CMakeFiles/variables.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/max/assignment/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable variables"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/variables.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/variables.dir/build: variables

.PHONY : CMakeFiles/variables.dir/build

CMakeFiles/variables.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/variables.dir/cmake_clean.cmake
.PHONY : CMakeFiles/variables.dir/clean

CMakeFiles/variables.dir/depend:
	cd /home/max/assignment/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/max/assignment /home/max/assignment /home/max/assignment/build /home/max/assignment/build /home/max/assignment/build/CMakeFiles/variables.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/variables.dir/depend
