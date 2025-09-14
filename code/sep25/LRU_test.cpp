//
// Created by guan on 2025/9/14.
//
#include "LRU.h"

#include <iostream>
#include <string>

int main() {
    try {
        // 创建一个容量为3的LRU缓存
        LRU_cache<int, std::string> cache(3);

        // 测试插入操作
        cache.put(1, "Apple");
        cache.put(2, "Banana");
        cache.put(3, "Cherry");
        std::cout << "缓存大小: " << cache.size() << ", 容量: " << cache.capacity() << std::endl;

        // 测试获取操作
        std::cout << "获取键1的值: " << cache.get(1) << std::endl;  // Apple

        // 插入第四个元素，会淘汰最久未使用的2
        cache.put(4, "Date");
        std::cout << "插入键4后，缓存是否包含键2: " << (cache.contains(2) ? "是" : "否") << std::endl;  // 否

        // 测试更新操作
        cache.put(3, "Cherry Updated");
        std::cout << "更新后键3的值: " << cache.get(3) << std::endl;  // Cherry Updated

        // 测试contains方法
        std::cout << "缓存是否包含键4: " << (cache.contains(4) ? "是" : "否") << std::endl;  // 是

        // 测试清空缓存
        cache.clear();
        std::cout << "清空后缓存大小: " << cache.size() << std::endl;  // 0

        // 测试异常情况（容量为0）
        LRU_cache<int, int> bad_cache(0);
    }
    catch (const std::exception& e) {
        std::cout << "捕获到异常: " << e.what() << std::endl;  // 应该输出容量必须大于0的异常
    }

    return 0;
}