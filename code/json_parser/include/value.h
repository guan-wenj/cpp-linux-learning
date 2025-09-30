//
// Created by guan on 2025/9/30.
//

#ifndef CPP_LINUX_LEARNING_VALUE_H
#define CPP_LINUX_LEARNING_VALUE_H
#include <cstdint>
#include <map>
#include <string>
#include <variant>
#include <vector>

//该文件定义json会出现的元素 int double 字符串  bool  null  array  object
namespace json {


    class Value;
    using None=std::monostate;
    using Boolean=bool;
    using Integer=int64_t;
    using Double=double;
    using String=std::string;
    using Array=std::vector<Value>;
    using Object=std::map<std::string, Value>;

    inline constexpr None none{};  // 👈 新增：表示 null 的常量值
    class Value {
    private:
        std::variant<None,Boolean,Integer,Double,String,Array,Object> data_;
    public:
        //各种类型的构造函数
        Value():data_(none){}
        Value(None):data_(none){}
        Value(Boolean b):data_(b){}
        Value(Integer i):data_(i){}
        Value(Double d):data_(d){}
        Value(String s):data_(s){}
        Value(Array a):data_(a){}
        Value(Object o):data_(o){}


        //判断类型的方法
        bool is_none() const { return std::holds_alternative<None>(data_); }
        bool is_boolean() const { return std::holds_alternative<Boolean>(data_); }
        bool is_integer() const { return std::holds_alternative<Integer>(data_); }
        bool is_double() const { return std::holds_alternative<Double>(data_); }
        bool is_string() const { return std::holds_alternative<String>(data_); }
        bool is_array() const { return std::holds_alternative<Array>(data_); }
        bool is_object() const { return std::holds_alternative<Object>(data_); }

        //取值方法   需要确定类型
        Boolean get_boolean() const { return std::get<Boolean>(data_); }
        Integer get_integer() const { return std::get<Integer>(data_); }
        Double get_double() const { return std::get<Double>(data_); }
        const String& get_string() const { return std::get<String>(data_); }
        const Array& get_array() const { return std::get<Array>(data_); }
        const Object& get_object() const { return std::get<Object>(data_); }

        //数组和对象的便捷访问
        const Value& operator[](size_t index) const;
        const Value& operator[](const std::string& key) const;
    };




}






#endif //CPP_LINUX_LEARNING_VALUE_H