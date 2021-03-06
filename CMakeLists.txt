cmake_minimum_required(VERSION 3.13)
project(Highload)
project(Experiment)
project(Cache)
project(Test_strace)
project(Test_FastList)

set(CMAKE_CXX_STANDARD 17)
set(GCC_COVERAGE_COMPILE_FLAGS "-pthread")

set(CMAKE_CXX_STANDARD_LIBRARIES "-lrt -lboost_filesystem -lboost_system")
#set(CMAKE_CXX_STANDARD_LIBRARIES -lboost_filesystem)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )

find_package(Boost 1.6.0 REQUIRED COMPONENTS system)
include_directories(SYSTEM ${Boost_INCLUDE_DIRS})

add_executable(
        Highload
        src/main.cpp
        src/server.cpp
        include/server.h
        include/epollEngine.h
        src/epollEngine.cpp
        include/fastList.hpp
        include/config.h
        src/config.cpp
        include/stringHolder.h
        src/stringHolder.cpp
        include/request.h
        src/request.cpp
        include/httpParser.h
        src/httpParser.cpp
        include/pointerStringStream.h
        src/pointerStringStream.cpp
        include/defines.h
        include/simpleConveyorPart.hpp
        include/reader.hpp
        include/blockQueue.hpp
        include/blockMap.hpp
        include/spreadConveyorPart.hpp
        include/responseMaker.hpp
        include/cache.h
        src/cache.cpp
        src/response.cpp
        include/response.h
        include/asyncReader.h
        include/writer.hpp
        src/asyncReader.cpp
)

add_executable(
        test_cache
        tests/cache/cache_test.cpp
        include/cache.h
        src/cache.cpp)

add_executable(
        test_strace
        tests/strace_experiments/test.cpp)

add_executable(
        Experiment
        tests/async_io_speed_experiments/experiment.cpp
        tests/async_io_speed_experiments/syscalls.h
)

add_executable(
        Test_FastList
        include/fastList.hpp
        tests/fastList/fastList_test.cpp
)
