#ifndef mylexer_h
#define mylexer_h

#define INT 1
#define RETURN 2
#define IDENT 3
#define INT_CONST 4
#define WHILE 5
#define IF 6
#define ELSE 7
#define EQ 8
#define LAND 9
#define LOR 10
#define LE 11
#define GE 12
#define NE 13
#define CONST 14
#define MAIN 15
#define BREAK 16
#define CONTINUE 17



#include <string>
#include <fstream>
#include "sysy.tab.hpp"  // 从bison生成的头文件中获取token定义

class Mylexer{
    public:
        //constructor
        Mylexer(std::string s);
        int yylex();
       

    private:
        bool IsLetter(char ch);   
        bool IsDigit(char ch);  
        int IsdualSign();

        int IsNumber();
        int IsDual();
        
        int IsIdentifierOrKeyword();
        void nextcharacter();
        void blankSpace();

        char current_char = ' '; 
        std::ifstream infile;
      
        const char DualTable[6] = { '=','>','<','&','|','!' };  

};

#endif