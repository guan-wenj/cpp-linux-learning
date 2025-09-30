//
// Created by guan on 2025/9/30.
//

#ifndef CPP_LINUX_LEARNING_ERROR_H
#define CPP_LINUX_LEARNING_ERROR_H
#include <string>

#include "value.h"


//定义各种错误
namespace json {
    enum class ErrorCode {
        NO_ERROR,
        UNEXPECTED_CHARACTER,  // 意外字符
        UNTERMINATED_STRING,   // 字符串未闭合
        INVALID_NUMBER,        // 无效数字格式
        UNTERMINATED_OBJECT,   // 对象未闭合
        UNTERMINATED_ARRAY     // 数组未闭合
    };

    class Error {
        ErrorCode code_=ErrorCode::NO_ERROR;
        std::string _message_;
        //发生错误的行列
        size_t line_=0;
        size_t column_=0;

    public:
        Error()=default;
        Error(ErrorCode code, const String& message, const size_t line, const size_t column):
        code_(code),_message_(message),line_(line),column_(column){}

        bool has_error() const { return code_!=ErrorCode::NO_ERROR; }
        ErrorCode get_code() const { return code_; }
        const String& get_message() const { return _message_; }
        size_t get_line() const { return line_; }
        size_t get_column() const { return column_; }

        std::string to_string() const {
            if (!has_error())
                return "No error";
            return "Error("+std::to_string(line_)+","+std::to_string(column_)+"):"+_message_;
        }


    };

}

#endif //CPP_LINUX_LEARNING_ERROR_H