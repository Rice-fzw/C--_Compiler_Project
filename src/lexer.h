#ifndef lexer_h
#define lexer_h

#include <string>
#include <fstream>
#include "c--.tab.hpp"  

extern YYSTYPE yylval;  

class Mylexer{
    public:
        //constructor
        Mylexer(std::string s);
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
        void skipcomment();
        void blankSpace();

        int IsdualSign();
        int IsString();

        char current_char = ' '; 
        std::ifstream infile;
      
        const char DualTable[11] = { '=','>','<','&','|','!','+','-','*','/', '%'};   

};

extern Mylexer* lexer;

extern "C" {
    int yylex();
}

#endif