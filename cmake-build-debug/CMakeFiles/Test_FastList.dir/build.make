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
CMAKE_SOURCE_DIR = /home/kekos/aaaa/Highload

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/kekos/aaaa/Highload/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Test_FastList.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Test_FastList.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Test_FastList.dir/flags.make

CMakeFiles/Test_FastList.dir/tests/fastList/fastList_test.cpp.o: CMakeFiles/Test_FastList.dir/flags.make
CMakeFiles/Test_FastList.dir/tests/fastList/fastList_test.cpp.o: ../tests/fastList/fastList_test.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kekos/aaaa/Highload/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Test_FastList.dir/tests/fastList/fastList_test.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Test_FastList.dir/tests/fastList/fastList_test.cpp.o -c /home/kekos/aaaa/Highload/tests/fastList/fastList_test.cpp

CMakeFiles/Test_FastList.dir/tests/fastList/fastList_test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Test_FastList.dir/tests/fastList/fastList_test.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kekos/aaaa/Highload/tests/fastList/fastList_test.cpp > CMakeFiles/Test_FastList.dir/tests/fastList/fastList_test.cpp.i

CMakeFiles/Test_FastList.dir/tests/fastList/fastList_test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Test_FastList.dir/tests/fastList/fastList_test.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kekos/aaaa/Highload/tests/fastList/fastList_test.cpp -o CMakeFiles/Test_FastList.dir/tests/fastList/fastList_test.cpp.s

# Object files for target Test_FastList
Test_FastList_OBJECTS = \
"CMakeFiles/Test_FastList.dir/tests/fastList/fastList_test.cpp.o"

# External object files for target Test_FastList
Test_FastList_EXTERNAL_OBJECTS =

Test_FastList: CMakeFiles/Test_FastList.dir/tests/fastList/fastList_test.cpp.o
Test_FastList: CMakeFiles/Test_FastList.dir/build.make
Test_FastList: CMakeFiles/Test_FastList.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/kekos/aaaa/Highload/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Test_FastList"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Test_FastList.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Test_FastList.dir/build: Test_FastList

.PHONY : CMakeFiles/Test_FastList.dir/build

CMakeFiles/Test_FastList.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Test_FastList.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Test_FastList.dir/clean

CMakeFiles/Test_FastList.dir/depend:
	cd /home/kekos/aaaa/Highload/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/kekos/aaaa/Highload /home/kekos/aaaa/Highload /home/kekos/aaaa/Highload/cmake-build-debug /home/kekos/aaaa/Highload/cmake-build-debug /home/kekos/aaaa/Highload/cmake-build-debug/CMakeFiles/Test_FastList.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Test_FastList.dir/depend

