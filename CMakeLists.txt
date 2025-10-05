cmake_minimum_required(VERSION 3.28.3)
project(cpp_linux_learning)

set(CMAKE_CXX_STANDARD 23)

#add_executable(cpp_linux_learning main.cpp
#)

#add_subdirectory(code/sep25)
#add_subdirectory(code/oct25)
#add_subdirectory(code/json_parser)
add_subdirectory(code/todo_list)

#include_directories(code/sep25)
#include_directories(code/oct25)
#include_directories(code/json_parser)
include_directories(code/todo_list)