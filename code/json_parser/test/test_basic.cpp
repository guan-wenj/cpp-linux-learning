//
// Created by guan on 2025/9/30.
//

#include <gtest/gtest.h>
#include "parser.h"
#include <print>
// 测试null解析
TEST(JsonParserTest, ParseNull) {
    json::Parser parser("null");
    auto value = parser.parse();
    ASSERT_NE(value, nullptr);
    ASSERT_TRUE(value->is_none());
    ASSERT_FALSE(parser.get_error().has_error());
}

// 测试true解析
TEST(JsonParserTest, ParseTrue) {
    json::Parser parser("true");
    auto value = parser.parse();
    ASSERT_NE(value, nullptr);
    ASSERT_TRUE(value->is_boolean());
    ASSERT_TRUE(value->get_boolean());
}

// 测试false解析
TEST(JsonParserTest, ParseFalse) {
    json::Parser parser("false");
    auto value = parser.parse();
    ASSERT_NE(value, nullptr);
    ASSERT_TRUE(value->is_boolean());
    ASSERT_FALSE(value->get_boolean());
}

// 测试空白字符（应忽略）
TEST(JsonParserTest, IgnoreWhitespace) {
    json::Parser parser("  \t\n\rtrue  \n");
    auto value = parser.parse();
    ASSERT_NE(value, nullptr);
    ASSERT_TRUE(value->get_boolean());
}
