//
// Created by guan on 2025/9/11.
//
#include <chrono>
#include <iostream>
#include <random>
#include <unordered_map>
std::string get_random_string() {
    const std::string charset = "abcdefghijklmnopqrstuvwxyz"
                                "0123456789";
    auto seed=std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine rng(seed);
    std::uniform_int_distribution<int> lengthDist(5, 10);
    int length = lengthDist(rng);
    std::uniform_int_distribution<int> charDist(0, charset.size() - 1);
    std::string result;
    result.reserve(length);  // 预分配内存，提高效率
    for (int i = 0; i < length; ++i) {
        result += charset[charDist(rng)];
    }
    return result;

}


double average_count(std::unordered_map<std::string,int>& map,float factor,std::vector<std::string>& words) {
    map.max_load_factor(factor);
    for (auto &s:words) {
        map[s]++;
    }
    auto start=std::chrono::high_resolution_clock::now();
    for (auto &s:words) {
        int _=map.count(s);
    }
    auto end=std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end-start);
    std::cout << map["99999"] << std::endl;
    return static_cast<double>(duration.count())/words.size();
}





int main() {
    //生成10000条
    std::vector<std::string> words;
    for (int i=0;i<1000000;i++) {
        words.push_back(get_random_string());
    }
    float default_factor=1.0;
    float current_factor=0.02;
    std::unordered_map<std::string,int> map1;
    std::unordered_map<std::string,int> map2;

    auto time1=average_count(map1,default_factor,words);
    auto time2=average_count(map2,current_factor,words);
    std::cout << "time1: " << time1 << "\n";
    std::cout << "time2: " << time2 << "\n";

}