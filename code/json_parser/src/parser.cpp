//
// Created by guan on 2025/9/30.
//
#include "parser.h"
#include <cctype>  // 用于isdigit等函数

namespace json {

    // 解析null
    std::unique_ptr<Value> Parser::parse_null() {
        // 检查是否为"null"
        if (input_.substr(pos_, 4) == "null") {
            pos_ += 4;
            column_ += 4;
            return std::make_unique<Value>(None{});  // 返回null类型的Value
        } else {
            set_error(ErrorCode::UNEXPECTED_CHARACTER, "Invalid null literal", line_, column_);
            return nullptr;
        }
    }

    // 解析boolean（true/false）
    std::unique_ptr<Value> Parser::parse_boolean() {
        if (input_.substr(pos_, 4) == "true") {
            pos_ += 4;
            column_ += 4;
            return std::make_unique<Value>(true);
        } else if (input_.substr(pos_, 5) == "false") {
            pos_ += 5;
            column_ += 5;
            return std::make_unique<Value>(false);
        } else {
            set_error(ErrorCode::UNEXPECTED_CHARACTER, "Invalid boolean literal", line_, column_);
            return nullptr;
        }
    }

    // 其他解析方法（parse_string、parse_number等）后续逐步实现...
    std::unique_ptr<Value> Parser::parse_object() {
        //todo()
    }

    std::unique_ptr<Value> Parser::parse_array() {
        //todo()

    }

    std::unique_ptr<Value> Parser::parse_string() {
        //todo()

    }

    std::unique_ptr<Value> Parser::parse_number() {
        //todo()
    }
}  // namespace json
