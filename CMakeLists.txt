cmake_minimum_required(VERSION 3.17)
project(Assignment1)

set(CMAKE_CXX_STANDARD 14)

include_directories(headers)

add_executable(Assignment1
        headers/Agent.h
        headers/Graph.h
        headers/Session.h
        headers/Tree.h
        src/main.cpp src/Tree.cpp src/Session.cpp src/Agent.cpp src/Graph.cpp)
