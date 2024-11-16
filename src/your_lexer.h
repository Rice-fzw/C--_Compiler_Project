// your_lexer.h
#ifndef YOUR_LEXER_H
#define YOUR_LEXER_H

#include <cstdio>
#include <string>
#include "sysy.tab.hpp"  // 从bison生成的头文件中获取token定义

extern FILE* yyin;       // 输入文件

int yylex();            // 主要的lexer函数
void init_lexer();      // 初始化lexer

#endif