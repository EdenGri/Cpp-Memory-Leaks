cmake_minimum_required(VERSION 3.17)
project(Assignment1)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

add_executable(Assignment1
        include/Agent.h
        include/Graph.h
        include/Session.h
        include/Tree.h
        src/main.cpp src/Tree.cpp src/Session.cpp src/Agent.cpp src/Graph.cpp)
