cmake_minimum_required(VERSION 3.10)
project(Program2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_COMPILER "/usr/bin/g++")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

include_directories(
    include
)

add_executable(Program2
    src/Main.cpp
    src/PragmaSecond.cpp
    src/Client.cpp
)

target_link_libraries(Program2 PRIVATE pthread)