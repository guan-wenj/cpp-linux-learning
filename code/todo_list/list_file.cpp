//
// Created by guan on 2025/10/5.
//

#include "list_file.h"

std::span<const std::string_view> my_io::read_lines_span(const std::string& file_path, bool skip_empty) {
        static std::vector<std::string> buffer;  // 存储实际字符串（生命周期管理）
        static std::vector<std::string_view> lines; // 存储视图（指向buffer中的字符串）
        buffer.clear();
        lines.clear();
        std::ifstream file(file_path, std::ios::binary); // 二进制模式避免自动转换换行符
        if (!file.is_open()) {
            throw std::runtime_error("Failed to open file: " + file_path);
        }
        // 一次性读取整个文件到buffer（减少IO次数，现代文件操作推荐）
        buffer.emplace_back(std::istreambuf_iterator<char>(file),
                           std::istreambuf_iterator<char>());
        std::string_view content(buffer[0]); // 整个文件内容的视图（零拷贝）

        // 按换行符分割内容，生成string_view（不拷贝数据，仅记录指针和长度）
        size_t pos = 0;
        while (pos < content.size()) {
            // 查找下一个换行符（兼容\n和\r\n）
            size_t next = content.find('\n', pos);
            if (next == std::string_view::npos) {
                next = content.size(); // 处理最后一行（无换行符）
            }
            std::string_view line = content.substr(pos, next - pos);
            if (!line.empty() && line.back() == '\r') {
                line = line.substr(0, line.size() - 1);
            }

            if (!skip_empty || !line.empty()) {
                lines.push_back(line);
            }
            pos = next + 1; // 移动到下一行起始位置
        }
        return std::span(lines); // 返回视图的span（零拷贝传递）

}

void my_io::write_lines_to_file(const std::string& file_path, const std::vector<std::string>& lines) {
        // 1. 打开文件：ios::out（输出模式）+ ios::trunc（截断模式，清空原有内容）
        // 不建议用ios::app（追加），也不用endl（会额外刷新缓冲区，降低性能）
        std::ofstream file(file_path, std::ios::out | std::ios::trunc);

        // 2. 检查文件是否成功打开（必须做！避免无效写入）
        if (!file.is_open()) {
            throw std::runtime_error("Failed to open file for writing: " + file_path
                                   + " (可能原因：路径错误/权限不足)");
        }

        // 3. 遍历写入：每个string后补'\n'，确保一行一个元素
        for (const auto& line : lines) { // const引用遍历，避免拷贝
            file << line << '\n'; // 显式加'\n'，替代endl（性能更优）

            // 4. 检查写入过程是否出错（如磁盘满、文件被意外删除）
            if (file.fail()) {
                throw std::runtime_error("Failed to write to file: " + file_path);
            }
        }
        // 5. 无需手动close()：ofstream析构时会自动关闭，且刷新缓冲区
}
