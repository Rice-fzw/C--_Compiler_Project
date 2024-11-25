#ifndef lexer_h
#define lexer_h

#include <string>
#include <fstream>
#include "sysy.tab.hpp"  // 从bison生成的头文件中获取token定义

extern YYSTYPE yylval;  // 声明yylval

class Lexer{
    public:
        //constructor
        Lexer(std::string s);
        int yylex();
       

    private:
        bool IsLetter(char ch);   
        bool IsDigit(char ch);  
         
       
        int IsNumber();
        int IsOctal();
        int IsHexadecimal();
        int IsDual();
        
        int IsIdentifierOrKeyword();
        void nextcharacter();
        void blankSpace();
        void skipcomment();

        int IsdualSign();

        char current_char = ' '; 
        std::ifstream infile;
        const char DualTable[6] = { '=','>','<','&','|','!' };  

};

extern Lexer* lexer;

extern "C" {
    int yylex();
}

#endif