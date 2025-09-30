//
// Created by guan on 2025/9/30.
//

#ifndef CPP_LINUX_LEARNING_PARSER_H
#define CPP_LINUX_LEARNING_PARSER_H

#include <memory>

#include "error.h"
#include "value.h"
#include <string>
namespace json {

    class Parser {
        std::string input_;
        size_t pos_ = 0;
        size_t line_= 1;
        size_t column_=1;
        Error error_;
    public:
        explicit Parser(std::string input): input_(std::move(input)) {}
        std::unique_ptr<Value> parse() {
            skip_whitespace();  // 跳过开头的空白字符
            auto value = parse_value();  // 解析根值（JSON只能有一个根值）
            skip_whitespace();

            // 解析完成后如果还有剩余字符，说明有多余内容
            if (pos_ < input_.size()) {
                set_error(ErrorCode::UNEXPECTED_CHARACTER, "Unexpected character after root value", line_, column_);
                return nullptr;
            }
            return value;
        }


        const Error& get_error() const { return error_; }

    private:
        void skip_whitespace() {
            while (pos_ < input_.size()) {
                char c = input_[pos_];
                if (c == ' ' || c == '\t' || c == '\n' || c == '\r') {
                    pos_++;
                    if (c == '\n') {
                        line_++;
                        column_ = 1;
                    } else {
                        column_++;
                    }
                } else {
                    break;
                }
            }
        }

        char current_char() const {
            return (pos_ < input_.size()) ? input_[pos_] : '\0';
        }

        void next_char() {
            if (pos_ < input_.size()) {
                if (input_[pos_] == '\n') {
                    line_++;
                    column_ = 1;
                } else {
                    column_++;
                }
                pos_++;
            }
        }

        std::unique_ptr<Value> parse_value() {
            skip_whitespace();
            char c = current_char();

            switch (c) {
            case '{': return parse_object();   // 对象
            case '[': return parse_array();    // 数组
            case '"': return parse_string();   // 字符串
            case 't': case 'f': return parse_boolean();  // 布尔值
            case 'n': return parse_null();     // null
            case '-': case '0': case '1': case '2': case '3': case '4':
            case '5': case '6': case '7': case '8': case '9':
                return parse_number();         // 数字
            default:
                // 未知字符，记录错误
                set_error(ErrorCode::UNEXPECTED_CHARACTER, "Unexpected character: " + std::string(1, c), line_, column_);
                return nullptr;
            }
        }



        // 以下方法先声明，后续逐步实现
        std::unique_ptr<Value> parse_object();    // 解析对象（{ ... }）
        std::unique_ptr<Value> parse_array();     // 解析数组（[ ... ]）
        std::unique_ptr<Value> parse_string();    // 解析字符串（"..."）
        std::unique_ptr<Value> parse_number();    // 解析数字
        std::unique_ptr<Value> parse_boolean();   // 解析true/false
        std::unique_ptr<Value> parse_null();      // 解析null

        void set_error(ErrorCode code, const std::string& message, size_t line, size_t column) {
            error_ = Error(code, message, line, column);
        }


    };


}







#endif //CPP_LINUX_LEARNING_PARSER_H