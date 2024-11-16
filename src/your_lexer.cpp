// your_lexer.cpp
#include "your_lexer.h"
#include <cctype>
#include <string>
#include <cstdlib>

FILE* yyin = nullptr;

// 当前读取的字符
static int current_char = ' ';

// 读取下一个字符
static void next_char() {
    current_char = fgetc(yyin);
}

// 跳过空白字符
static void skip_whitespace() {
    while (isspace(current_char)) {
        next_char();
    }
}

// 处理标识符或关键字
static int handle_identifier() {
    std::string identifier;
    
    // 读取整个标识符
    while (isalnum(current_char) || current_char == '_') {
        identifier += current_char;
        next_char();
    }
    
    // 检查是否是关键字
    if (identifier == "int") {
        return INT;
    }
    if (identifier == "return") {
        return RETURN;
    }
    
    // 如果不是关键字，那就是普通标识符
    yylval.str_val = new std::string(identifier);
    return IDENT;
}

// 处理数字
static int handle_number() {
    std::string num_str;
    
    // 读取整个数字
    while (isdigit(current_char)) {
        num_str += current_char;
        next_char();
    }
    
    // 转换为整数并保存在yylval中
    yylval.int_val = std::stoi(num_str);
    return INT_CONST;
}

// 主要的词法分析函数
int yylex() {
    // 跳过空白字符
    skip_whitespace();
    
    // 处理文件结束
    if (current_char == EOF) {
        return 0;
    }
    
    // 处理标识符和关键字
    if (isalpha(current_char) || current_char == '_') {
        return handle_identifier();
    }
    
    // 处理数字
    if (isdigit(current_char)) {
        return handle_number();
    }
    
    // 处理单字符符号
    int c = current_char;
    next_char();
    switch (c) {
        case '+': return '+';
        case '-': return '-';
        case '*': return '*';
        case '/': return '/';
        case '(': return '(';
        case ')': return ')';
        case '{': return '{';
        case '}': return '}';
        case ';': return ';';
        // 可以继续添加其他符号
    }
    
    // 对于无法识别的字符，可以报错或者忽略
    return yylex(); // 继续读取下一个token
}