//
// Created by guan on 2025/9/18.
//
#include <print>
#include <map>
#include <iostream>
template<typename T,typename ...Args>
void my_print(T t,Args... a) {
    std::print("{}  ",t);
    if constexpr(sizeof...(a)>0) {
        my_print(a...);
    }
}


template<typename ...Args>
void you_print(Args... a) {
    (std::print("{}  ",a),...);
}


template<typename ...Args>
auto average(Args ...a) {
    if constexpr(sizeof...(a)==0) {
        return 0.0;
    }else {
        return static_cast<double>((a+...))/sizeof...(a);
    }
}


template <typename Key, typename Value, typename F>
void update(std::map<Key, Value>& m, F foo) {
    for (auto&[k,v]:m) v=foo(k);

}
int main() {
    // std::map<std::string, long long int> m {
    // {"a", 1},
    // {"b", 2},
    // {"c", 3}
    // };
    // update(m, [](std::string key) {
    // return std::hash<std::string>{}(key);
    // });
    // for (auto&& [key, value] : m)
    //     std::cout << key << ":" << value << std::endl;
    double res=average();
    std::println("{}",res);
}

// int main() {
//     my_print("hello",2,34,"uu",'a');
//     std::println();
//     you_print(2,34,"uu",'a');
// }