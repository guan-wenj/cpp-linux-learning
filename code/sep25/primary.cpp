//
// Created by guan on 2025/8/30.
//


#include <iostream>
#include <chrono>
#include <vector>

int main() {
    auto start1 = std::chrono::high_resolution_clock::now();
    std::vector<int> vec1;
    for (int i=0;i<100000000;i++) {
        vec1.push_back(i*3);
    }
    auto end1= std::chrono::high_resolution_clock::now();
    auto duration1 = std::chrono::duration_cast<std::chrono::microseconds>(end1-start1);
    std::cout <<"没reserve:"<< duration1.count() << std::endl;

    auto start = std::chrono::high_resolution_clock::now();
    std::vector<int> vec;
    vec.reserve(1000000);
    for (int i=0;i<100000000;i++) {
        vec.push_back(i*3);
    }
    auto end= std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end-start);
    std::cout <<"reserve:"<< duration.count() << std::endl;

}