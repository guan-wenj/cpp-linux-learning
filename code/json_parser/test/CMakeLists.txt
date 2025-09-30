cmake_minimum_required(VERSION 3.28.3)

# 查找系统中的GTest（如果顶层已配置，这里会继承）
find_package(GTest REQUIRED)

# 测试可执行文件
add_executable(json_tests
        test_basic.cpp
        test_types.cpp
        test_errors.cpp
        # 其他测试文件
)

# 链接依赖：JSON库和GTest
target_link_libraries(json_tests PRIVATE
        json_parser
        GTest::GTest
        GTest::Main
        pthread  # 新增：Linux下gtest强制依赖线程库，否则编译失败
)

# 测试专属编译选项
target_compile_options(json_tests PRIVATE
        -Wall
        -Werror  # 测试代码严格检查
)

# 将测试添加到CTest（与顶层enable_testing配合）
add_test(NAME json_tests COMMAND json_tests)
