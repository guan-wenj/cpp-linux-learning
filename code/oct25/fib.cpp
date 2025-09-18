//
// Created by guan on 2025/9/18.
//

#include <print>
constexpr int fib(const int n) {
    if (n==1 || n==2) {
        return 1;
    }
    return fib(n-1)+fib(n-2);
}
int main() {
    std::println("{}",fib(10));
}