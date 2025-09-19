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
    std::tuple<std::string,std::string,int> to_tuple() {
        return std::make_tuple(name,gender,age);
    }
};

auto add14=[](auto x,auto y){
    return x+y;
};

auto add20(auto x,auto y) {
    return x+y;
}




int main() {
    Student s{"john","boy",22};
    s.introduce();
    auto [x,y,z] = s.to_tuple();
    std::println("age is {}",z);
    auto a=add14(11,25.1);
    auto b=add20(11,25.1);
    std::println("{} {}",a,b);



}