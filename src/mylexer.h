#ifndef mylexer_h
#define mylexer_h

#include <string>
#include <fstream>
#include "sysy.tab.hpp"  // 从bison生成的头文件中获取token定义

extern YYSTYPE yylval;  // 声明yylval

class Mylexer{
    public:
        //constructor
        Mylexer(std::string s);
        int yylex();
       

    private:
        bool IsLetter(char ch);   
        bool IsDigit(char ch);  
         
       
        int IsNumber();
        int IsDual();
        
        int IsIdentifierOrKeyword();
        void nextcharacter();
        void blankSpace();

        int IsdualSign();

        char current_char = ' '; 
        std::ifstream infile;
      
        const char DualTable[6] = { '=','>','<','&','|','!' };  

};

// 声明全局lexer对象
extern Mylexer* lexer;

// 声明包装函数
extern "C" {
    int yylex();
}

#endif