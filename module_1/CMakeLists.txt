cmake_minimum_required(VERSION 3.0.0)
project(module_1 VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()


set(CMAKE_CXX_FLAGS -fsanitize=leak)

set(SOURCE_FILES src/task_1_4.cpp src/task_2_1.cpp src/task_3_1.cpp src/task_4_1.cpp)

set(HEADER_FILES include/helpers.cpp)

add_executable(module_1 main.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
