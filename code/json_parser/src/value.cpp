//
// Created by guan on 2025/9/30.
//

#include "value.h"
#include <stdexcept>

namespace json {
    const Value& Value::operator[](size_t index) const {
        if (!is_array()) {
            throw std::runtime_error("Value is not array");
        }
        const auto& arr=get_array();
        if (index >= arr.size()) {
            throw std::runtime_error("Value index is out of range");
        }
        return arr[index];
    }

    const Value& Value::operator[](const std::string& key) const {
        if (!is_object()) {
            throw std::runtime_error("Value is not object");
        }
        const auto& obj=get_object();
        auto it = obj.find(key);
        if (it == obj.end()) {
            throw std::runtime_error("Key not found");
        }
        return it->second;
    }
}

