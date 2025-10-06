//
// Created by guan on 2025/10/5.
//

#ifndef CPP_LINUX_LEARNING_LIST_FILE_H
#define CPP_LINUX_LEARNING_LIST_FILE_H


#include <fstream>
#include <vector>
#include <string>
#include <span>       // C++20 span
#include <string_view> // 字符串视图（零拷贝）
#include <stdexcept>  // 异常处理
#include <ranges>     // C++20 范围库
#include <algorithm>  // 辅助算法
#include <filesystem>  // C++17 文件系统库（现代C++推荐）
#include <iostream>
namespace my_io {
    std::span<const std::string_view> read_lines_span(const std::string& file_path, bool skip_empty = true);
    void write_lines_to_file(const std::string& file_path, const std::vector<std::string>& lines);
    void check_and_create_file(const std::string& file_path) ;
}








#endif //CPP_LINUX_LEARNING_LIST_FILE_H