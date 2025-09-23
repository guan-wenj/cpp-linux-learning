//
// Created by guan on 2025/9/23.
//
#include <memory>
#include <print>
struct A;
struct B;


struct A {
    std::shared_ptr<B> pointer;
    A() {
        std::println("创建了A");
    }
    ~A() {
        std::println("销毁了A");
    }
};

struct B {
    // std::shared_ptr<A> pointer;
    std::weak_ptr<A> pointer;

    B() {
        std::println("创建了B");
    }
    ~B() {
        std::println("销毁了B");
    }
};

int main() {
    auto a=std::make_shared<A>();
    auto b=std::make_shared<B>();
    a->pointer=b;
    b->pointer=a;
}