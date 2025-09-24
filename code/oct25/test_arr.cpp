//
// Created by guan on 2025/9/24.
//

#include <print>
#include "dynamic_arr.h"
#include <memory>
#include <vector>
void test_alloc() {
    try {
        auto ptr1 = std::make_unique<std::vector<int>>(1000000);
        std::println("success:{}",ptr1->size());
    }catch(std::exception& e) {
        std::println("fail:{}",e.what());
    }

    try {
        auto ptr2 = std::unique_ptr<std::vector<int>>(new std::vector<int>(100000));
        std::println("success:{}",ptr2->size());
    }catch(std::exception& e) {
        std::println("fail:{}",e.what());
    }
}

void test_lambda() {
    DynamicArr<int> arr;
    for (int i=0;i<10;i++) {
        arr.push_back(i);
    }
    int sum=arr.calculate([](int a,int b){return a+b;},0 );
    int product=arr.calculate([](int a,int b){return a*b;},1 );
    std::println("sum:{}",sum);
    std::println("product:{}",product);
    DynamicArr<double> arr2;
    for (int i=0;i<6;i++) {
        arr2.push_back(1.5);
    }
    double sum2=arr2.calculate([](double a,double b){return a+b;},0 );
    double product2=arr2.calculate([](double a,double b){return a*b;},1 );
    std::println("sum:{}",sum2);
    std::println("product:{}",product2);
}

void test_template() {
    std::println("{}",expand_factor<int>);
    std::println("{}",expand_factor<double>);
    std::println("{}",expand_factor<float>);
}
int main() {
    test_alloc();
    test_lambda();
    test_template();
}