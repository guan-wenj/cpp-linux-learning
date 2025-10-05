//
// Created by guan on 2025/10/5.
//
#include <print>
#include "entity.h"
using my_todo_list::Task;
int main() {
    try {
        Task t1("1 2025-9-18 开会");
        Task t2("2 2025-12-12 双12购物");
        Task t3("吃饭",2024,5,8);
        std::println("{}",t1.format());
        std::println("{}",t3.display());
        t1.set_message("勿忘国耻");
        std::println("{}",t1.format());
        t1.set_time(2024,9,18);
        std::println("{}",t1.format());

        std::println("{}",t1.is_expired());
        std::println("{}",t1<t2);
        std::println("{}",t1<t3);
        std::println("{}",t1.early_than_other(t3));
        std::println("{}",t1.early_than(2024,9,18));
        std::println("{}",t1.early_than(2024,9,19));

        t2.set_time(2028,2,29);






    }catch(const std::exception& e) {
        std::println("{}",e.what());
    }

}