#ifndef mylexer_h
#define mylexer_h

#define typeString 1
#define typeInteger 2
#define typeDouble 3
#define typeInteger 4


#include <string>
#include <vector>
#include "storestruct.h"

class Mylexer{
    public:
        //constructor
        Mylexer();

        bool IsLetter(char ch);   
        bool IsDigit(char ch);   
        void scan(std::string s);  
        void readfile(std::string d) ;
        bool IsNumber(std::string k,int i);
        std::vector<std::vector<Tokens>> ReturnToken();
    
    private:
        std::vector<std::vector<Tokens>> store;
        std::string KeyWord[12];
        int symbol;  //再看要有.h吗
        std::string tokenvalue;

};


#endif