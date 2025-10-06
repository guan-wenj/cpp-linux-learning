//
// Created by guan on 2025/10/5.
//
#include <print>
#include "entity.h"
#include "list_file.h"
using my_todo_list::Task;
using my_todo_list::TodoList;
using namespace my_io;

int main() {
    try {
        TodoList list;
        const std::string file_path="tasks.txt";
        check_and_create_file(file_path);
        auto lines = read_lines_span(file_path);
        for (std::string_view line : lines) {
            if (line.empty()) continue;
            std::string input;
            input.assign(line.begin(), line.end());
            Task task(input);
            list.add(task);
        }
        list.date_sort();
        write_lines_to_file(file_path,list.list_format());
    }catch(const std::exception& e) {
        std::println("{}",e.what());
    }

}