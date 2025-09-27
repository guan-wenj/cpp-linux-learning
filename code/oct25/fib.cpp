//
// Created by guan on 2025/9/18.
//

#include <print>
#include <chrono>
extern constexpr int fib_const(const int n) {
    if (n==1 || n==2) {
        return 1;
    }
    return fib_const(n-1)+fib_const(n-2);
}
int fib(const int n) {
    if (n==1 || n==2) {
        return 1;
    }
    return fib(n-1)+fib(n-2);
}


int main() {
    auto start=std::chrono::steady_clock::now();
    for (int i=0;i<1000;i++) {
        int n=fib(30);
    }
    auto end=std::chrono::steady_clock::now();
    auto duration1=std::chrono::duration<double>(end-start);

    start=std::chrono::steady_clock::now();
    for (int i=0;i<1000;i++) {
        int n=fib_const(30);
    }
    end=std::chrono::steady_clock::now();
    auto duration2=std::chrono::duration<double>(end-start);

    std::println("{}",duration1);
    std::println("const:{}",duration2);
    std::println("{}倍",duration1/duration2);
    return 0;
}
