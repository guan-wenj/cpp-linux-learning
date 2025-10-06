//
// Created by guan on 2025/10/5.
//
#include "entity.h"

#include <algorithm>
#include <ctime>
#include <chrono>
#include <utility>
/*
 * 从文件读取的input字符串直接构建task    1 2025 4 5 好天气
 * 返回 一个tuple 包含时间的三个int 和 信息
 */


std::tuple<int, int, int, int, std::string> parse_file_line(const std::string& input) {
    std::istringstream iss(input);
    int id, year, month, day;
    std::string dateStr, message;
    // 提取id和日期字符串
    iss >> id >> year>>month>>day;
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

std::tuple<int,int,int> get_today_date() {
    std::time_t now = std::time(nullptr);
    std::tm* local_time = std::localtime(&now);
    // 转换为标准格式（年=1900+tm_year, 月=tm_mon+1, 日=tm_mday）
    int year = local_time->tm_year + 1900;
    int month = local_time->tm_mon + 1;
    int day = local_time->tm_mday;
    return {year, month, day};
}


/*
 * 时间的合法性检查
 */
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


/*
 * task的时间是否早于提供的时间
 */
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

/**
 *
 * @param other
 * @return 是否早于other
 */
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

bool my_todo_list::Task::is_expired() const {
    std::time_t now = std::time(nullptr);
    std::tm* local_time = std::localtime(&now);
    // 转换为标准格式（年=1900+tm_year, 月=tm_mon+1, 日=tm_mday）
    int year = local_time->tm_year + 1900;
    int month = local_time->tm_mon + 1;
    int day = local_time->tm_mday;
    return early_than(year, month, day);

}

/**
 *
 * @return 在控制台上展示的字符串
 */
std::string my_todo_list::Task::display() const {
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

/**
 * @return 在文件中写入的字符串
 */
std::string my_todo_list::Task::format() const{
    std::stringstream ss;
    ss<<id_<<' '<<year_<<' '<<month_<<' '<<day_<<' '<<message_;
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

int my_todo_list::Task::get_id() const {
    return id_;
}

bool my_todo_list::Task::is_today() const {
    auto[year,month,day]=get_today_date();
    if (year==year_ && month==month_ && day==day_) {
        return true;
    }
    return false;
}

/**
 *
 * @param other
 * @return 类似:early_than_other的小于号重载 方便之后排序
 */
bool my_todo_list::Task::operator<(const Task& other) const {
    return early_than_other(other);
}


my_todo_list::TodoList::TodoList() = default;

bool my_todo_list::TodoList::empty() const {
    return list_.empty();
}

int my_todo_list::TodoList::size() const {
    return static_cast<int>(list_.size());
}

void my_todo_list::TodoList::add(const Task& task) {
    list_.push_back(std::make_unique<Task>(task));
}

void my_todo_list::TodoList::add(Task&& task) {
    list_.push_back(std::make_unique<Task>(std::move(task)));

}

void my_todo_list::TodoList::erase(int id) {
    for (auto it=list_.begin(); it!=list_.end();++it) {
        if ((*it)->get_id()==id) {
            list_.erase(it);
            return;
        }
    }
    throw std::invalid_argument("id not found");
}

my_todo_list::Task* my_todo_list::TodoList::find(int id) {
    for (auto& task : list_) {
        if (task->get_id()==id) {
            return task.get();
        }
    }
    return nullptr;
}

void my_todo_list::TodoList::update_time(int id, int year, int month, int day) {
    auto it =find(id);
    if (it==nullptr) {
        throw std::invalid_argument("id not found");
    }
    it->set_time(year, month, day);
}

void my_todo_list::TodoList::update_message(int id, const std::string& message) {
    auto it =find(id);
    if (it==nullptr) {
        throw std::invalid_argument("id not found");
    }
    it->set_message(message);
}

void my_todo_list::TodoList::date_sort() {
    std::sort(list_.begin(), list_.end(), [](std::unique_ptr<Task>& first,std::unique_ptr<Task>& second) {
        return *first<*second;
    });
}

void my_todo_list::TodoList::remove_expired() {
    list_.erase(
        std::remove_if(list_.begin(), list_.end(),
            [](const std::unique_ptr<Task>& task) {
                return task->is_expired();
            }),
            list_.end()
        );
}

std::vector<std::string> my_todo_list::TodoList::today_message() const {
    std::vector<std::string> ss;
    for (auto& task : list_) {
        if (task->is_today()) {
            ss.push_back(task->get_message());
        }
    }
    return ss;
}

std::string my_todo_list::Task::get_message() const {
    return message_;
}

std::vector<std::string> my_todo_list::TodoList::list_display() const {
    std::vector<std::string> ss;
    for (auto& task : list_) {
        ss.push_back(task->display());
    }
    return ss;
}

std::vector<std::string> my_todo_list::TodoList::list_format() const{
    std::vector<std::string> ss;
    for (auto &task : list_) {
        ss.push_back(task->format());
    }
    return ss;
}
