//
// Created by guan on 2025/10/5.
//

#ifndef CPP_LINUX_LEARNING_ENTITY_H
#define CPP_LINUX_LEARNING_ENTITY_H
#include <memory>
#include <string>
#include <vector>

namespace my_todo_list {

class Task {
    int id_;
    std::string message_;
    int year_;
    int month_;
    int day_;

public:
    Task(std::string  message, int year, int month, int day);
    Task(std::string input);
    bool is_expired() const;
    std::string display() const;
    std::string format() const;
    //set
    void set_message(const std::string& message);
    void set_time(int year,int month,int day);

    bool early_than(int year,int month,int day) const;
    bool early_than_other(const Task& other) const ;
    bool operator<(const Task& other) const;
    bool is_today() const;

    int get_id() const;
    std::string get_message() const;

};

class TodoList {
private:
    std::vector<std::unique_ptr<Task>> list_;
public:
    TodoList();
    ~TodoList()=default;
    //crud
    bool empty() const;
    int size() const;
    void add(const Task& task);
    void add( Task&& task);

    void erase(int id);
    Task* find(int id);
    void update_time(int id,int year,int month,int day);
    void update_message(int id,const std::string& message);

    //排序
    void date_sort();
    //过期移除
    void remove_expired();
    //输出今日
    std::vector<std::string> today_message() const ;
    //输出日志格式和展示格式
    std::vector<std::string> list_display() const;
    std::vector<std::string> list_format() const;
};


}

std::tuple<int, int, int, int, std::string> parse_file_line(const std::string& input);
int generate_id();
std::tuple<int,int,int> get_today_date();
bool time_is_valid(int year,int month,int day);






#endif //CPP_LINUX_LEARNING_ENTITY_H