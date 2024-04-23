cmake_minimum_required(VERSION 3.28)
project(module_2)

set(CMAKE_CXX_STANDARD 17)
add_compile_options(-fsanitize=leak)

add_executable(module_2 main.cpp
        include/BinaryTree.hpp
        src/task_2_1.cpp)
