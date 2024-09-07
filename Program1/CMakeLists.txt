cmake_minimum_required(VERSION 3.10)
project(Program1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_COMPILER "/usr/bin/g++")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

include_directories(
    include
)

add_executable(Program1
    src/Main.cpp
    src/PragmaFirst.cpp
    src/Socket.cpp
    src/ThreadFirst.cpp
    src/ThreadSecond.cpp
    src/WorkingWithString.cpp
)

target_link_libraries(Program1 PRIVATE pthread)