//
// Created by guan on 2025/9/27.
//

#include <cassert>  // 标准库断言头文件
#include <iostream>


int fib(int n);

int main() {
    // 用 assert 测试，条件不满足时会直接报错并显示位置
    assert(fib(1) == 1 && "fib(1) 结果错误");    // 测试 n=1
    assert(fib(5) == 5 && "fib(5) 结果错误");    // 测试 n=5
    assert(fib(10) == 55 && "fib(10) 结果错误");  // 测试 n=10

    std::cout << "所有 fib 测试通过！\n";
    return 0;
}