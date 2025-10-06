//
// Created by guan on 2025/10/5.
//
#include <print>
#include "entity.h"
using my_todo_list::Task;
using my_todo_list::TodoList;

int main() {
    try {
        Task t1("1 2025-9-18 开会");
        Task t2("2 2025-12-12 双12购物");
        Task t3("吃饭",2024,5,8);
        // std::println("{}",t3.display());
        // t1.set_message("勿忘国耻");
        // std::println("{}",t1.format());
        // t1.set_time(2024,9,18);
        // std::println("{}",t1.format());
        //
        // std::println("{}",t1.is_expired());
        // std::println("{}",t1<t2);
        // std::println("{}",t1<t3);
        // std::println("{}",t1.early_than_other(t3));
        // std::println("{}",t1.early_than(2024,9,18));
        // std::println("{}",t1.early_than(2024,9,19));
        //
        // t2.set_time(2028,2,29);
        Task t4("中秋佳节",2025,10,6);

        TodoList todo;
        todo.add(std::move(t1));
        todo.add(std::move(t2));
        todo.add(std::move(t3));
        todo.add(std::move(t4));
        auto out1=todo.list_format();
        // for (const auto& s:out1) {
        //     std::println("{}",s);
        // }

        todo.update_message(2,"但愿人长久");
        todo.update_time(2,2025,10,6);
        auto out2=todo.today_message();
        for (const auto& s:out2) {
            std::println("{}",s);
        }







    }catch(const std::exception& e) {
        std::println("{}",e.what());
    }

}