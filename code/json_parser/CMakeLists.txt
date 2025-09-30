cmake_minimum_required(VERSION 3.28.3)

# 定义子项目名称（可选，增强可读性）
project(json_parser LANGUAGES CXX)

set(GTEST_ROOT "/usr/lib/cmake/GTest")  # 固定指向WSL系统安装的gtest
# 1. 构建JSON解析器核心库（静态库，便于主程序或其他子项目链接）
add_library(json_parser STATIC
        src/parser.cpp
        src/value.cpp
        src/error.cpp
)

# 2. 设置头文件路径（PUBLIC表示依赖此库的目标也能访问这些头文件）
target_include_directories(json_parser PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include  # 公开接口头文件（如json/json.h）
)

# 3. 确保遵循顶层CMake设置的C++标准（无需重复设置，继承自顶层）
# 如需额外特性，可添加：target_compile_features(json_parser PUBLIC cxx_std_23)

# 4. 子项目专属编译选项（不影响顶层和其他子项目）
target_compile_options(json_parser PRIVATE
        -Wall
        -Wextra
        -Wpedantic
        # 可添加子项目特有的选项，如：-Wno-sign-compare（视需要）
)

# 5. 构建示例程序（可选，演示如何使用该库）
add_executable(json_example
        example/example.cpp
)
# 链接JSON解析器库
target_link_libraries(json_example PRIVATE json_parser)

# 6. 构建测试程序（仅改这部分：添加gtest查找，确保链接时能找到gtest）
if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/test)
    # 查找gtest（核心：让CMake找到系统/Linux下的gtest库）
    find_package(GTest REQUIRED)
    # 进入测试子目录（子目录内处理具体链接）
    add_subdirectory(test)
endif()