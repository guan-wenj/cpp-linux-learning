/**
  ******************************************************************************
  * @file           : service.cpp
  * @author         : guan
  * @brief          : None
  * @attention      : None
  * @date           : 2025/10/7
  ******************************************************************************
  */
#include <print>
#include "service.h"
#include <iostream>
using my_todo_list::Task;
using my_todo_list::TodoList;
using my_io::check_and_create_file;
using my_io::read_lines_span;
using my_io::write_lines_to_file;

const std::string file_path="tasks.txt";

my_todo_list::TodoList prepare() {
    TodoList todo_list;
    check_and_create_file(file_path);
    auto lines=read_lines_span(file_path);
    for (auto line : lines) {
        if (line.empty()) continue;
        std::string input;
        input.assign(line.begin(), line.end());
        todo_list.add(Task(input));
    }
    todo_list.remove_expired();
    todo_list.date_sort();
    std::println("今日日程");
    auto to_print=todo_list.today_message();
    for (auto& s:to_print) {
        std::println("{}",s);
    }
    return std::move(todo_list);
}

void run(my_todo_list::TodoList& todo) {
    while (true) {
        std::println("请输入你要进行的操作");
        std::println("1  查看所有日程");
        std::println("2  增加新的日程");
        std::println("3  删除已有日程");
        std::println("4  更改已有日程");
        std::println("0  退出程序");
        int op;
        std::cin >> op;
        switch (op) {
            case 1:overlook(todo);break;
            case 2:add(todo);break;
            case 3:erase(todo);break;
            case 4:update(todo);break;
            case 0: goto exit;
            default:
            std::println("未知操作");
            break;
        }
    }
    exit:;
}

void save(my_todo_list::TodoList& todo) {
    todo.remove_expired();
    todo.date_sort();
    auto lines=todo.list_format();
    write_lines_to_file(file_path,lines);
}

void add(my_todo_list::TodoList& todo) {
    std::string message;
    int year,month,day;
    std::println("请输入日程信息");
    std::cin >> message;
    std::println("请输入年");
    std::cin >> year;
    std::println("请输入月");
    std::cin >> month;
    std::println("请输入日");
    std::cin >> day;
    todo.add(Task(message,year,month,day));
}

void update(my_todo_list::TodoList& todo) {
    overlook(todo);
    int id;
    std::println("请输入修改日程的id");
    std::cin >> id;
    std::println("请输入修改位置 1 时间  2  事件");
    auto it=todo.find(id);
    if (it==nullptr) {
        std::println("未找到该id");
        return;
    }
    int op;
    std::cin >> op;
    switch (op) {
        case 1:
            {
                int year,month,day;
                std::println("请输入年");
                std::cin >> year;
                std::println("请输入月");
                std::cin >> month;
                std::println("请输入日");
                std::cin >> day;
                it->set_time(year,month,day);
                return;
            }
        case 2:
            {
                std::string message;
                std::println("请输入事件");
                std::cin >> message;
                it->set_message(message);
                return;
            }
    default:
        std::println("未知操作");
    }

}

void erase(my_todo_list::TodoList& todo) {
    overlook(todo);
    int id;
    std::println("请输入删除日程的id");
    std::cin >> id;
    auto it=todo.find(id);
    if (it==nullptr) {
        std::println("该日程不存在");
        return;
    }
    todo.erase(id);
}

void overlook(my_todo_list::TodoList& todo) {
    auto lines=todo.list_display();
    for (auto line : lines) {
        std::println("{}" ,line);
    }
}
