cmake_minimum_required(VERSION 3.13)
project(Highload)

set(CMAKE_CXX_STANDARD 17)
set(GCC_COVERAGE_COMPILE_FLAGS "-pthread")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )

find_package(Boost 1.65.1 REQUIRED COMPONENTS system)
include_directories(SYSTEM ${Boost_INCLUDE_DIRS})

add_executable(
        Highload
        src/main.cpp
        src/server.cpp
        include/server.h
        include/epollEngine.h
        src/epollEngine.cpp
        include/fastList.hpp
        include/config.h include/stringHolder.h src/stringHolder.cpp include/request.h src/request.cpp include/httpParser.h src/httpParser.cpp include/pointerStringStream.h src/pointerStringStream.cpp include/defines.h include/conveyorPart.hpp include/reader.hpp include/blockQueue.hpp include/blockMap.hpp include/multiConveyorPart.hpp)