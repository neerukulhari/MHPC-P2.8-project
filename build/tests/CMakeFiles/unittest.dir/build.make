# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_SOURCE_DIR = /home/neeraj/Desktop/MHPC/MHPC-P2.8-project

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/neeraj/Desktop/MHPC/MHPC-P2.8-project/build

# Utility rule file for unittest.

# Include any custom commands dependencies for this target.
include tests/CMakeFiles/unittest.dir/compiler_depend.make

# Include the progress variables for this target.
include tests/CMakeFiles/unittest.dir/progress.make

tests/CMakeFiles/unittest: tests/GoogleTests
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/neeraj/Desktop/MHPC/MHPC-P2.8-project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Running unit tests"

unittest: tests/CMakeFiles/unittest
unittest: tests/CMakeFiles/unittest.dir/build.make
.PHONY : unittest

# Rule to build all files generated by this target.
tests/CMakeFiles/unittest.dir/build: unittest
.PHONY : tests/CMakeFiles/unittest.dir/build

tests/CMakeFiles/unittest.dir/clean:
	cd /home/neeraj/Desktop/MHPC/MHPC-P2.8-project/build/tests && $(CMAKE_COMMAND) -P CMakeFiles/unittest.dir/cmake_clean.cmake
.PHONY : tests/CMakeFiles/unittest.dir/clean

tests/CMakeFiles/unittest.dir/depend:
	cd /home/neeraj/Desktop/MHPC/MHPC-P2.8-project/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/neeraj/Desktop/MHPC/MHPC-P2.8-project /home/neeraj/Desktop/MHPC/MHPC-P2.8-project/tests /home/neeraj/Desktop/MHPC/MHPC-P2.8-project/build /home/neeraj/Desktop/MHPC/MHPC-P2.8-project/build/tests /home/neeraj/Desktop/MHPC/MHPC-P2.8-project/build/tests/CMakeFiles/unittest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tests/CMakeFiles/unittest.dir/depend

