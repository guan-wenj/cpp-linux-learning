//
// Created by guan on 2025/10/4.
//

#ifndef CPP_LINUX_LEARNING_JSON_H
#define CPP_LINUX_LEARNING_JSON_H

#pragma once
#include <string>
#include <vector>
#include <map>
namespace mercury {
    namespace json {

        class Json {
        public:
            enum Type {
                json_null=0,
                json_bool,
                json_int,
                json_double,
                json_string,
                json_array,
                json_object
            };

            Json();
            Json(bool value);
            Json(int value);
            Json(double value);
            Json(const std::string& value);
            Json(const char* value);
            Json(Type type);
            Json(const Json& other);

            operator bool();
            operator int();
            operator double();
            operator std::string();

            Json& operator[](int index);
            Json& operator[](const char* key);
            Json& operator[](const std::string&  key);
            void operator=(const Json& other);
            void copy(const Json& other);
            void append(const Json& other);

            std::string to_string() const;
            void clear();

            typedef  std::vector<Json>::iterator  iterator;
            iterator begin() {
                return m_value.m_array->begin();
            }
            iterator end() {
                return m_value.m_array->end();
            }

            bool operator==(const Json& other);
            bool operator!=(const Json& other);

        private:
            union Value {
                bool m_bool;
                int m_int;
                double m_double;
                std::string* m_string;
                std::vector<Json>* m_array;
                std::map<std::string, Json>* m_object;
            };

            Type m_type;
            Value m_value;
        };


    }
}





#endif //CPP_LINUX_LEARNING_JSON_H