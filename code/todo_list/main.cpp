//
// Created by guan on 2025/10/5.
//
#include "service.h"
#include <print>
int main() {
    try {
        auto todo=prepare();
        run(todo);
        save(todo);
        std::println("成功保存");
    }catch(const std::exception& e) {
        std::println("{}",e.what());
    }

}