//
// Created by guan on 2025/9/19.
//
#include <print>
class Student {
    std::string name;
    std::string gender;
    int age;
    public:
    Student(std::string name, std::string gender, int age):name(name),gender(gender),age(age){}
    void introduce(){
        std::println("hello, my name is {}, {} years old, i im a {}", name, age,gender);
    }
};

int main() {
    Student s{"john","boy",22};
    s.introduce();
}