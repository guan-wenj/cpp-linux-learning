//
// Created by guan on 2025/9/26.
//

#include <chrono>
#include <iostream>
#include <print>
#include <fstream>
#include <ranges>
#include <span>
#include <sstream>
#include <algorithm>
#include <stdexcept>
#include <cstring>
#include <optional>
/*
 * 定义日志级别
 * 向下逐渐严重
 */
enum class LogLevel {
    DEBUG,
    INFO,
    WARNING,
    ERROR,
    CRITICAL
};

/*
 *日志组成
 *timestamp 时间戳 可以没有
 *level 日志等级
 *message 详细信息
 */
struct LogEntry {
    std::optional<std::chrono::system_clock::time_point> timestamp;
    LogLevel level;
    std::string message;

};


//turn string to level
std::optional<LogLevel> string_to_level(const std::string& level) {
    if (level == "DEBUG") return LogLevel::DEBUG;
    if (level == "INFO") return LogLevel::INFO;
    if (level == "WARNING") return LogLevel::WARNING;
    if (level == "ERROR") return LogLevel::ERROR;
    if (level == "CRITICAL") return LogLevel::CRITICAL;
    return std::nullopt;
}

//提取日志中的时间戳  简单的时间戳格式: [YYYY-MM-DD HH:MM:SS]
std::optional<std::chrono::system_clock::time_point> get_timestamp(const std::string& line) {
    if (line.size()<21 || line[0]!='[' || line[20]!=']') {
        return std::nullopt;
    }
    std::string date_str = line.substr(1, 10);
    std::string time_str = line.substr(12, 8);
    int year,month,day,hour,minute,second;
    char dash1, dash2, colon1, colon2;
    std::istringstream date_stream(date_str);
    date_stream >> year >> dash1 >> month >> dash2>>day;
    std::istringstream time_stream(time_str);
    time_stream>>hour>>colon1>>minute>>colon2>>second;

    if (dash1!='-' || dash2!='-' || colon1!=':' || colon2!=':') {
        return std::nullopt;
    }

    std::tm tm{};
    tm.tm_year=year-1900;
    tm.tm_mon=month-1;
    tm.tm_mday=day;
    tm.tm_hour=hour;
    tm.tm_min=minute;
    tm.tm_sec=second;

    std::time_t tt=std::mktime(&tm);
    if (tt==-1) {
        return std::nullopt;
    }
    return  std::chrono::system_clock::from_time_t(tt);

}

// 解析单条日志
std::optional<LogEntry> parse_log_entry(const std::string& line) {
    auto timestamp=get_timestamp(line);


    size_t pos=0;
    if (timestamp.has_value()) {
        pos=22;
        if (pos>=line.size()) {
            return std::nullopt;
        }
    }
    size_t level_end=line.find(':',pos);
    if (level_end==std::string::npos) {
        return std::nullopt;
    }
    std::string level_str=line.substr(pos,level_end-pos);


    auto level=string_to_level(level_str);
    if (!level.has_value()) {
        return std::nullopt;
    }
     pos=level_end+2;
    if (pos>=line.size()) {
        return LogEntry{timestamp,level.value(),""};
    }
    auto message=line.substr(pos);


    return LogEntry{timestamp,level.value(),message};
}


// 安全处理日志缓冲区
std::vector<std::string_view> split_log_buffer(std::span<char> buffer) {
    std::vector<std::string_view> lines;
    const char* start=buffer.data();
    const char* end=start+buffer.size();
    const char* current=start;
    while (current<end) {
        const char* next=std::find(current,end,'\n');
        if (next>current) {
            lines.emplace_back(current,next-current);
            //lines.emplace_back(current,next);
        }
        current=next+1;
    }
    return lines;
}

//格式化打印log
void print_format(const LogEntry& log) {
    if (log.timestamp.has_value()) {
        auto time = std::chrono::system_clock::to_time_t(log.timestamp.value());
        std::tm tm{};
        localtime_r(&time, &tm);
        char time_str[20];
        std::strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", &tm);
        std::print("[{}]",time_str);
       // std::cout << "[" << time_str << "]";
    } else {
        std::print("[                ]");
       // std::cout << "[                ]";
    }

    switch (log.level) {
    case LogLevel::DEBUG:    std::print("DEBUG:    ");    break;  // 保持原空格对齐
    case LogLevel::INFO:     std::print("INFO:     ");     break;
    case LogLevel::WARNING:  std::print("WARNING:  ");  break;
    case LogLevel::ERROR:    std::print("ERROR:    ");    break;
    case LogLevel::CRITICAL: std::print("CRITICAL: "); break;
    }
    std::println("{}",log.message);
    //std::cout << log.message << "\n";
}

//处理日志文件
void process_log_file(const std::string& filename) {
    std::ifstream file(filename,std::ios::binary | std::ios::ate);
    if (!file) {
        throw std::runtime_error("Can't open log file: "+filename);
    }
    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    //分配缓冲区并读取文件
    std::vector<char> buffer(size);
    if (!file.read(buffer.data(), size)) {
        throw std::runtime_error("Can't read log file: "+filename);
    }

    auto log_lines=split_log_buffer(std::span<char>(buffer));



    auto processed_log = log_lines
        | std::views::transform([](std::string_view sv) {
              return parse_log_entry(std::string(sv));
          })
        | std::views::filter([](const std::optional<LogEntry>& opt) {
              return opt.has_value() &&
                     (opt->level == LogLevel::ERROR || opt->level == LogLevel::CRITICAL);
          })
        | std::views::transform([](const std::optional<LogEntry>& opt) {
              return opt.value(); // 返回LogEntry的值（拷贝）而非引用
          });


    std::println("错误日志条目：");
    for (const auto& line:processed_log) {
        print_format(line);
    }

}

void test_large_log() {
    try {
        constexpr size_t BUFFER_SIZE=10*1024*1024;
        std::vector<char> large_buffer(BUFFER_SIZE, 'x');
        const char* testLogs = "[2023-10-05 14:30:00] ERROR: 测试错误日志\n"
                              "[2023-10-05 14:30:01] CRITICAL: 测试严重错误\n";
        size_t log_len=std::strlen(testLogs);
        if (log_len<BUFFER_SIZE) {
            std::memcpy(large_buffer.data() + (BUFFER_SIZE - log_len),
                       testLogs, log_len);
        }
        auto lines = split_log_buffer(std::span<char>(large_buffer));
        auto errorLines = lines
            | std::views::filter([](auto& line) {
                return line.contains("ERROR") || line.contains("CRITICAL");
              });
        std::println("找到{}个错误",std::ranges::distance(errorLines) );

    } catch (const std::out_of_range& e) {
        std::cerr << "大日志测试 - 边界错误: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "大日志测试 - 错误: " << e.what() << std::endl;
    }
}
int main() {
    try {
        // 处理示例日志文件
        process_log_file("../../../data/test.log");
        // 测试大日志处理
        test_large_log();
    } catch (const std::exception& e) {
        std::cerr << "程序错误: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}