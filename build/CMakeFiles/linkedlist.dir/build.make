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
include CMakeFiles/linkedlist.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/linkedlist.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/linkedlist.dir/flags.make

CMakeFiles/linkedlist.dir/linkedlist.c.o: CMakeFiles/linkedlist.dir/flags.make
CMakeFiles/linkedlist.dir/linkedlist.c.o: ../linkedlist.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/max/assignment/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/linkedlist.dir/linkedlist.c.o"
	/bin/gcc-9 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/linkedlist.dir/linkedlist.c.o   -c /home/max/assignment/linkedlist.c

CMakeFiles/linkedlist.dir/linkedlist.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/linkedlist.dir/linkedlist.c.i"
	/bin/gcc-9 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/max/assignment/linkedlist.c > CMakeFiles/linkedlist.dir/linkedlist.c.i

CMakeFiles/linkedlist.dir/linkedlist.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/linkedlist.dir/linkedlist.c.s"
	/bin/gcc-9 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/max/assignment/linkedlist.c -o CMakeFiles/linkedlist.dir/linkedlist.c.s

# Object files for target linkedlist
linkedlist_OBJECTS = \
"CMakeFiles/linkedlist.dir/linkedlist.c.o"

# External object files for target linkedlist
linkedlist_EXTERNAL_OBJECTS =

linkedlist: CMakeFiles/linkedlist.dir/linkedlist.c.o
linkedlist: CMakeFiles/linkedlist.dir/build.make
linkedlist: CMakeFiles/linkedlist.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/max/assignment/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable linkedlist"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/linkedlist.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/linkedlist.dir/build: linkedlist

.PHONY : CMakeFiles/linkedlist.dir/build

CMakeFiles/linkedlist.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/linkedlist.dir/cmake_clean.cmake
.PHONY : CMakeFiles/linkedlist.dir/clean

CMakeFiles/linkedlist.dir/depend:
	cd /home/max/assignment/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/max/assignment /home/max/assignment /home/max/assignment/build /home/max/assignment/build /home/max/assignment/build/CMakeFiles/linkedlist.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/linkedlist.dir/depend

