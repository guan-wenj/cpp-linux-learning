//
// Created by guan on 2025/9/4.
//

#ifndef CPP_LINUX_LEARNING_RVALUE_H
#define CPP_LINUX_LEARNING_RVALUE_H
#include <iostream>
#include <string>
class NewString {
    std::string str;
    public:
    NewString(const std::string& s1) : str(s1) {}
    NewString(std::string && s2) : str(std::move(s2)) {}
    void display() {
        std::cout << str<<std::endl;
    }
};

//移动语义示意
// #include "rvalue.h"
// #include <iostream>
// int main() {
//     auto s1=NewString("hello");
//     std::string ss="hi";
//     auto s2=NewString(std::move(ss));
//     s1.display();
//     s2.display();
//
// }


#endif //CPP_LINUX_LEARNING_RVALUE_H