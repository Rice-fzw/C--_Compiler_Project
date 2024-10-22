// tests/LexerTests.cpp - 测试文件
#include <gtest/gtest.h>
#include "MipsLexer.h"

class MipsLexerTest : public ::testing::Test {
protected:
    MipsLexer lexer;
};

// 测试基本指令识别
TEST_F(MipsLexerTest, BasicInstructionTest) {
    std::string input = "add $t0, $t1, $t2";
    auto tokens = lexer.tokenizeContent(input);
    
    // 验证token数量（指令 + 3个寄存器 + 2个逗号）
    ASSERT_EQ(tokens.size(), 6);
    
    // 验证指令token
    EXPECT_EQ(tokens[0].type, TokenType::KEYWORD);
    EXPECT_EQ(tokens[0].value, "add");
    
    // 验证第一个寄存器
    EXPECT_EQ(tokens[1].type, TokenType::REGISTER);
    EXPECT_EQ(tokens[1].value, "$t0");
}

// 测试标签识别
TEST_F(MipsLexerTest, LabelTest) {
    std::string input = "loop:";
    auto tokens = lexer.tokenizeContent(input);
    
    ASSERT_EQ(tokens.size(), 1);
    EXPECT_EQ(tokens[0].type, TokenType::LABEL);
    EXPECT_EQ(tokens[0].value, "loop:");
}

// 测试注释识别
TEST_F(MipsLexerTest, CommentTest) {
    std::string input = "add $t0, $t1, $t2 # This is a comment";
    auto tokens = lexer.tokenizeContent(input);
    
    // 找到注释token
    bool hasComment = false;
    for (const auto& token : tokens) {
        if (token.type == TokenType::COMMENT) {
            hasComment = true;
            EXPECT_EQ(token.value, "# This is a comment");
            break;
        }
    }
    EXPECT_TRUE(hasComment);
}

// 测试数字识别
TEST_F(MipsLexerTest, NumberTest) {
    std::string input = "li $t0, 42";
    auto tokens = lexer.tokenizeContent(input);
    
    bool hasNumber = false;
    for (const auto& token : tokens) {
        if (token.type == TokenType::INTEGER) {
            hasNumber = true;
            EXPECT_EQ(token.value, "42");
            break;
        }
    }
    EXPECT_TRUE(hasNumber);
}

// 测试错误处理
TEST_F(MipsLexerTest, InvalidTokenTest) {
    std::string input = "add $t0, @, $t2";  // @ 是无效字符
    auto tokens = lexer.tokenizeContent(input);
    
    bool hasInvalid = false;
    for (const auto& token : tokens) {
        if (token.type == TokenType::UNKNOWN) {
            hasInvalid = true;
            EXPECT_EQ(token.value, "@");
            break;
        }
    }
    EXPECT_TRUE(hasInvalid);
}