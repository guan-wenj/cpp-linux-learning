//
// Created by guan on 2025/10/5.
//
#include "entity.h"
#include <ctime>
#include <chrono>
#include <utility>

std::tuple<int, int, int, int, std::string> parse_file_line(const std::string& input) {
    std::istringstream iss(input);
    int id, year, month, day;
    std::string dateStr, message;
    // 提取id和日期字符串
    iss >> id >> dateStr;
    // 解析日期（yyyy-m-d）
    std::istringstream dateIss(dateStr);
    char dash1, dash2; // 用于接收 '-' 分隔符
    dateIss >> year >> dash1 >> month >> dash2 >> day;
    // 提取剩余部分作为消息（包含空格）
    std::getline(iss >> std::ws, message);
    return {id, year, month, day, message};
}
//获取时间戳id
int generate_id() {
    auto now = std::chrono::system_clock::now();
    auto ms = std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch());
    return static_cast<int>(ms.count());
}

bool time_is_valid(int year,int month,int day) {
    if (month < 1 || month > 12)
        return false;
    if (day < 1 )
        return false;
    const int maxDays[] = {31,28,31,30,31,30,31,31,30,31,30,31};
    int max_day = maxDays[month - 1];
    if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))) {
        max_day = 29;
    }

    if (day > max_day) {
        return false;
    }
    return true;
}

bool my_todo_list::Task::early_than(int year, int month, int day) const {
    if (year_<year) {
        return true;
    }
    if (year==year_ &&month_<month) {
        return true;
    }
    if (year==year_&& month==month_&&day_ < day) {
        return true;
    }

    return false;
}

bool my_todo_list::Task::early_than_other(const Task& other) const{
    return early_than(other.year_,other.month_,other.day_);
}


my_todo_list::Task::Task(std::string  message, int year, int month, int day)
    :id_(generate_id()), message_(std::move(message)){
    if (!time_is_valid(year,month,day) ) {
        throw std::invalid_argument("invalid  date");
    }
    year_ = year;
    month_ = month;
    day_ = day;

}

bool my_todo_list::Task::is_expired() {
    std::time_t now = std::time(nullptr);
    std::tm* local_time = std::localtime(&now);
    // 转换为标准格式（年=1900+tm_year, 月=tm_mon+1, 日=tm_mday）
    int year = local_time->tm_year + 1900;
    int month = local_time->tm_mon + 1;
    int day = local_time->tm_mday;
    return early_than(year, month, day);

}

std::string my_todo_list::Task::display() {
    std::stringstream ss;
    ss << "ID: " << id_ <<std::endl<< "Message: " << message_<<std::endl;
    ss<<year_<<'-'<<month_<<"-"<<day_;
    return ss.str();
}

my_todo_list::Task::Task(std::string input) {
    auto[id,year,month,day,message] = parse_file_line(input);
    id_=id;
    year_=year;
    month_=month;
    day_=day;
    message_ = message;
}

std::string my_todo_list::Task::format() {
    std::stringstream ss;
    ss<<id_<<' '<<year_<<'-'<<month_<<'-'<<day_<<' '<<message_;
    return ss.str();
}

void my_todo_list::Task::set_message(const std::string& message) {
    message_ = message;
}

void my_todo_list::Task::set_time(int year, int month, int day) {
    if (!time_is_valid(year,month,day)) {
        throw std::invalid_argument("invalid  date");
    }
    year_ = year;
    month_ = month;
    day_ = day;
}

bool my_todo_list::Task::operator<(const Task& other) const {
    return early_than_other(other);
}
