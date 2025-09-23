//
// Created by guan on 2025/9/20.
//

#include <functional>
#include <print>
#include <iostream>
auto average(int x,int y,int z,int e) {
    return static_cast<double>(x+y+z+e)/4;
}
template<typename T>
auto make(T&& t) {
    std::println("right value");
}


template<typename T>
auto make(T& t) {
    std::println("left value");
}

class A {
    int id_;
    public:
    A(int id):id_(id){}
    void hello() {
        std::println("my id is {}",id_);
    }
};


template<typename T>
auto hello(T& t) {
    t.hello();
}



int main() {
    // auto a=std::bind(average,std::placeholders::_1,std::placeholders::_2,4,4);
    // double b=a(4,8);
    // std::println("{}",b);

    // std::string s="hello";
    // make(s);
    // make("hello");
    // make(std::move(s));
    // make(std::string("hello"));
    // make(std::forward<std::string>(s));
    // int n;
    A a{1};
    hello(a);



}