cmake_minimum_required(VERSION 4.1) #指定cmake的最低版本
set(CMAKE_CXX_STANDARD 23)
project(cmake_test CXX) #设置项目名称和项目语言
add_executable(cmake_test1 test1.cpp )  # 设置可执行文件和相应源文件
add_library(my_lib STATIC library.cpp) #静态可连接库
target_link_libraries(cmake_test1 my_lib)
include_directories(${PROJECT_SOURCE_DIR}/include)
