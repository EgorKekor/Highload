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
CMAKE_COMMAND = /opt/clion-2020.1.1/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /opt/clion-2020.1.1/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/kekos/Highload

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/kekos/Highload/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/test_strace.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/test_strace.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/test_strace.dir/flags.make

CMakeFiles/test_strace.dir/tests/strace_experiments/test.cpp.o: CMakeFiles/test_strace.dir/flags.make
CMakeFiles/test_strace.dir/tests/strace_experiments/test.cpp.o: ../tests/strace_experiments/test.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kekos/Highload/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/test_strace.dir/tests/strace_experiments/test.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test_strace.dir/tests/strace_experiments/test.cpp.o -c /home/kekos/Highload/tests/strace_experiments/test.cpp

CMakeFiles/test_strace.dir/tests/strace_experiments/test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_strace.dir/tests/strace_experiments/test.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kekos/Highload/tests/strace_experiments/test.cpp > CMakeFiles/test_strace.dir/tests/strace_experiments/test.cpp.i

CMakeFiles/test_strace.dir/tests/strace_experiments/test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_strace.dir/tests/strace_experiments/test.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kekos/Highload/tests/strace_experiments/test.cpp -o CMakeFiles/test_strace.dir/tests/strace_experiments/test.cpp.s

# Object files for target test_strace
test_strace_OBJECTS = \
"CMakeFiles/test_strace.dir/tests/strace_experiments/test.cpp.o"

# External object files for target test_strace
test_strace_EXTERNAL_OBJECTS =

test_strace: CMakeFiles/test_strace.dir/tests/strace_experiments/test.cpp.o
test_strace: CMakeFiles/test_strace.dir/build.make
test_strace: CMakeFiles/test_strace.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/kekos/Highload/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable test_strace"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_strace.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/test_strace.dir/build: test_strace

.PHONY : CMakeFiles/test_strace.dir/build

CMakeFiles/test_strace.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/test_strace.dir/cmake_clean.cmake
.PHONY : CMakeFiles/test_strace.dir/clean

CMakeFiles/test_strace.dir/depend:
	cd /home/kekos/Highload/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/kekos/Highload /home/kekos/Highload /home/kekos/Highload/cmake-build-debug /home/kekos/Highload/cmake-build-debug /home/kekos/Highload/cmake-build-debug/CMakeFiles/test_strace.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/test_strace.dir/depend

