cmake_minimum_required(VERSION 3.13)
project(Highload)

set(CMAKE_CXX_STANDARD 17)

add_executable(
        Highload
        src/main.cpp
        src/server.cpp
        include/server.h
        include/epollEngine.h
        src/epollEngine.cpp
)