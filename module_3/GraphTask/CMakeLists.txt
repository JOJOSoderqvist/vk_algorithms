cmake_minimum_required(VERSION 3.28)
project(GraphTask)

set(CMAKE_CXX_STANDARD 17)

add_executable(GraphTask main.cpp
        include/IGraph.hpp
        include/ListGraph.hpp
        src/ListGraph.cpp
        include/MatrixGraph.hpp
        src/MatrixGraph.cpp
        include/SetGraph.hpp
        src/SetGraph.cpp
        include/ArcGraph.hpp
        src/ArcGraph.cpp)
