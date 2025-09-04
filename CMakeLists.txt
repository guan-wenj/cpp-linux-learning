cmake_minimum_required(VERSION 4.0)
project(cpp_linux_learning)

set(CMAKE_CXX_STANDARD 23)

add_executable(cpp_linux_learning main.cpp
)

add_subdirectory(code/sep25)

include_directories(.)