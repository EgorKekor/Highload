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
include CMakeFiles/Highload.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Highload.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Highload.dir/flags.make

CMakeFiles/Highload.dir/src/main.cpp.o: CMakeFiles/Highload.dir/flags.make
CMakeFiles/Highload.dir/src/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kekos/aaaa/Highload/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Highload.dir/src/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Highload.dir/src/main.cpp.o -c /home/kekos/aaaa/Highload/src/main.cpp

CMakeFiles/Highload.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Highload.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kekos/aaaa/Highload/src/main.cpp > CMakeFiles/Highload.dir/src/main.cpp.i

CMakeFiles/Highload.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Highload.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kekos/aaaa/Highload/src/main.cpp -o CMakeFiles/Highload.dir/src/main.cpp.s

CMakeFiles/Highload.dir/src/server.cpp.o: CMakeFiles/Highload.dir/flags.make
CMakeFiles/Highload.dir/src/server.cpp.o: ../src/server.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kekos/aaaa/Highload/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Highload.dir/src/server.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Highload.dir/src/server.cpp.o -c /home/kekos/aaaa/Highload/src/server.cpp

CMakeFiles/Highload.dir/src/server.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Highload.dir/src/server.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kekos/aaaa/Highload/src/server.cpp > CMakeFiles/Highload.dir/src/server.cpp.i

CMakeFiles/Highload.dir/src/server.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Highload.dir/src/server.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kekos/aaaa/Highload/src/server.cpp -o CMakeFiles/Highload.dir/src/server.cpp.s

CMakeFiles/Highload.dir/src/epollEngine.cpp.o: CMakeFiles/Highload.dir/flags.make
CMakeFiles/Highload.dir/src/epollEngine.cpp.o: ../src/epollEngine.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kekos/aaaa/Highload/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/Highload.dir/src/epollEngine.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Highload.dir/src/epollEngine.cpp.o -c /home/kekos/aaaa/Highload/src/epollEngine.cpp

CMakeFiles/Highload.dir/src/epollEngine.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Highload.dir/src/epollEngine.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kekos/aaaa/Highload/src/epollEngine.cpp > CMakeFiles/Highload.dir/src/epollEngine.cpp.i

CMakeFiles/Highload.dir/src/epollEngine.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Highload.dir/src/epollEngine.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kekos/aaaa/Highload/src/epollEngine.cpp -o CMakeFiles/Highload.dir/src/epollEngine.cpp.s

CMakeFiles/Highload.dir/src/config.cpp.o: CMakeFiles/Highload.dir/flags.make
CMakeFiles/Highload.dir/src/config.cpp.o: ../src/config.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kekos/aaaa/Highload/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/Highload.dir/src/config.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Highload.dir/src/config.cpp.o -c /home/kekos/aaaa/Highload/src/config.cpp

CMakeFiles/Highload.dir/src/config.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Highload.dir/src/config.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kekos/aaaa/Highload/src/config.cpp > CMakeFiles/Highload.dir/src/config.cpp.i

CMakeFiles/Highload.dir/src/config.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Highload.dir/src/config.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kekos/aaaa/Highload/src/config.cpp -o CMakeFiles/Highload.dir/src/config.cpp.s

CMakeFiles/Highload.dir/src/stringHolder.cpp.o: CMakeFiles/Highload.dir/flags.make
CMakeFiles/Highload.dir/src/stringHolder.cpp.o: ../src/stringHolder.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kekos/aaaa/Highload/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/Highload.dir/src/stringHolder.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Highload.dir/src/stringHolder.cpp.o -c /home/kekos/aaaa/Highload/src/stringHolder.cpp

CMakeFiles/Highload.dir/src/stringHolder.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Highload.dir/src/stringHolder.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kekos/aaaa/Highload/src/stringHolder.cpp > CMakeFiles/Highload.dir/src/stringHolder.cpp.i

CMakeFiles/Highload.dir/src/stringHolder.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Highload.dir/src/stringHolder.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kekos/aaaa/Highload/src/stringHolder.cpp -o CMakeFiles/Highload.dir/src/stringHolder.cpp.s

CMakeFiles/Highload.dir/src/request.cpp.o: CMakeFiles/Highload.dir/flags.make
CMakeFiles/Highload.dir/src/request.cpp.o: ../src/request.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kekos/aaaa/Highload/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/Highload.dir/src/request.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Highload.dir/src/request.cpp.o -c /home/kekos/aaaa/Highload/src/request.cpp

CMakeFiles/Highload.dir/src/request.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Highload.dir/src/request.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kekos/aaaa/Highload/src/request.cpp > CMakeFiles/Highload.dir/src/request.cpp.i

CMakeFiles/Highload.dir/src/request.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Highload.dir/src/request.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kekos/aaaa/Highload/src/request.cpp -o CMakeFiles/Highload.dir/src/request.cpp.s

CMakeFiles/Highload.dir/src/httpParser.cpp.o: CMakeFiles/Highload.dir/flags.make
CMakeFiles/Highload.dir/src/httpParser.cpp.o: ../src/httpParser.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kekos/aaaa/Highload/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/Highload.dir/src/httpParser.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Highload.dir/src/httpParser.cpp.o -c /home/kekos/aaaa/Highload/src/httpParser.cpp

CMakeFiles/Highload.dir/src/httpParser.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Highload.dir/src/httpParser.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kekos/aaaa/Highload/src/httpParser.cpp > CMakeFiles/Highload.dir/src/httpParser.cpp.i

CMakeFiles/Highload.dir/src/httpParser.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Highload.dir/src/httpParser.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kekos/aaaa/Highload/src/httpParser.cpp -o CMakeFiles/Highload.dir/src/httpParser.cpp.s

CMakeFiles/Highload.dir/src/pointerStringStream.cpp.o: CMakeFiles/Highload.dir/flags.make
CMakeFiles/Highload.dir/src/pointerStringStream.cpp.o: ../src/pointerStringStream.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kekos/aaaa/Highload/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/Highload.dir/src/pointerStringStream.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Highload.dir/src/pointerStringStream.cpp.o -c /home/kekos/aaaa/Highload/src/pointerStringStream.cpp

CMakeFiles/Highload.dir/src/pointerStringStream.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Highload.dir/src/pointerStringStream.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kekos/aaaa/Highload/src/pointerStringStream.cpp > CMakeFiles/Highload.dir/src/pointerStringStream.cpp.i

CMakeFiles/Highload.dir/src/pointerStringStream.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Highload.dir/src/pointerStringStream.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kekos/aaaa/Highload/src/pointerStringStream.cpp -o CMakeFiles/Highload.dir/src/pointerStringStream.cpp.s

CMakeFiles/Highload.dir/src/cache.cpp.o: CMakeFiles/Highload.dir/flags.make
CMakeFiles/Highload.dir/src/cache.cpp.o: ../src/cache.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kekos/aaaa/Highload/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/Highload.dir/src/cache.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Highload.dir/src/cache.cpp.o -c /home/kekos/aaaa/Highload/src/cache.cpp

CMakeFiles/Highload.dir/src/cache.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Highload.dir/src/cache.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kekos/aaaa/Highload/src/cache.cpp > CMakeFiles/Highload.dir/src/cache.cpp.i

CMakeFiles/Highload.dir/src/cache.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Highload.dir/src/cache.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kekos/aaaa/Highload/src/cache.cpp -o CMakeFiles/Highload.dir/src/cache.cpp.s

CMakeFiles/Highload.dir/src/response.cpp.o: CMakeFiles/Highload.dir/flags.make
CMakeFiles/Highload.dir/src/response.cpp.o: ../src/response.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kekos/aaaa/Highload/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/Highload.dir/src/response.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Highload.dir/src/response.cpp.o -c /home/kekos/aaaa/Highload/src/response.cpp

CMakeFiles/Highload.dir/src/response.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Highload.dir/src/response.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kekos/aaaa/Highload/src/response.cpp > CMakeFiles/Highload.dir/src/response.cpp.i

CMakeFiles/Highload.dir/src/response.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Highload.dir/src/response.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kekos/aaaa/Highload/src/response.cpp -o CMakeFiles/Highload.dir/src/response.cpp.s

CMakeFiles/Highload.dir/src/asyncReader.cpp.o: CMakeFiles/Highload.dir/flags.make
CMakeFiles/Highload.dir/src/asyncReader.cpp.o: ../src/asyncReader.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kekos/aaaa/Highload/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/Highload.dir/src/asyncReader.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Highload.dir/src/asyncReader.cpp.o -c /home/kekos/aaaa/Highload/src/asyncReader.cpp

CMakeFiles/Highload.dir/src/asyncReader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Highload.dir/src/asyncReader.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kekos/aaaa/Highload/src/asyncReader.cpp > CMakeFiles/Highload.dir/src/asyncReader.cpp.i

CMakeFiles/Highload.dir/src/asyncReader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Highload.dir/src/asyncReader.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kekos/aaaa/Highload/src/asyncReader.cpp -o CMakeFiles/Highload.dir/src/asyncReader.cpp.s

# Object files for target Highload
Highload_OBJECTS = \
"CMakeFiles/Highload.dir/src/main.cpp.o" \
"CMakeFiles/Highload.dir/src/server.cpp.o" \
"CMakeFiles/Highload.dir/src/epollEngine.cpp.o" \
"CMakeFiles/Highload.dir/src/config.cpp.o" \
"CMakeFiles/Highload.dir/src/stringHolder.cpp.o" \
"CMakeFiles/Highload.dir/src/request.cpp.o" \
"CMakeFiles/Highload.dir/src/httpParser.cpp.o" \
"CMakeFiles/Highload.dir/src/pointerStringStream.cpp.o" \
"CMakeFiles/Highload.dir/src/cache.cpp.o" \
"CMakeFiles/Highload.dir/src/response.cpp.o" \
"CMakeFiles/Highload.dir/src/asyncReader.cpp.o"

# External object files for target Highload
Highload_EXTERNAL_OBJECTS =

Highload: CMakeFiles/Highload.dir/src/main.cpp.o
Highload: CMakeFiles/Highload.dir/src/server.cpp.o
Highload: CMakeFiles/Highload.dir/src/epollEngine.cpp.o
Highload: CMakeFiles/Highload.dir/src/config.cpp.o
Highload: CMakeFiles/Highload.dir/src/stringHolder.cpp.o
Highload: CMakeFiles/Highload.dir/src/request.cpp.o
Highload: CMakeFiles/Highload.dir/src/httpParser.cpp.o
Highload: CMakeFiles/Highload.dir/src/pointerStringStream.cpp.o
Highload: CMakeFiles/Highload.dir/src/cache.cpp.o
Highload: CMakeFiles/Highload.dir/src/response.cpp.o
Highload: CMakeFiles/Highload.dir/src/asyncReader.cpp.o
Highload: CMakeFiles/Highload.dir/build.make
Highload: CMakeFiles/Highload.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/kekos/aaaa/Highload/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Linking CXX executable Highload"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Highload.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Highload.dir/build: Highload

.PHONY : CMakeFiles/Highload.dir/build

CMakeFiles/Highload.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Highload.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Highload.dir/clean

CMakeFiles/Highload.dir/depend:
	cd /home/kekos/aaaa/Highload/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/kekos/aaaa/Highload /home/kekos/aaaa/Highload /home/kekos/aaaa/Highload/cmake-build-debug /home/kekos/aaaa/Highload/cmake-build-debug /home/kekos/aaaa/Highload/cmake-build-debug/CMakeFiles/Highload.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Highload.dir/depend

