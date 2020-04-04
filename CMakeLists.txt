cmake_minimum_required(VERSION 3.13)
project(Highload)

set(CMAKE_CXX_STANDARD 17)
set(GCC_COVERAGE_COMPILE_FLAGS "-pthread")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )

add_executable(
        Highload
        src/main.cpp
        src/server.cpp
        include/server.h
        include/epollEngine.h
        src/epollEngine.cpp
        src/reader.cpp
        include/reader.h
        include/fastList.h
        include/config.h include/stringHolder.h src/stringHolder.cpp include/request.h src/request.cpp include/httpManager.h src/httpManager.cpp)