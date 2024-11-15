#include <string>
#include <fstream>
#include <iostream>
#include "mylexer.h"
using namespace std;

//constructor: open the source file
Mylexer::Mylexer(string name){
    infile.open(name, ios::in); // open file 
    if (!infile) {
    cerr << "unable to open file" << endl;
    }
}

//To read the next character
void Mylexer::nextcharacter(){
     current_char = infile.get();
}

//to judge whether current character is a letter or not
bool Mylexer::IsLetter(char ch){
    if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')){
        return true;
    }
	return false;
}  

//to judge whether current character is a digit or not
bool Mylexer::IsDigit(char ch){
    if (ch >= '0'&& ch <= '9'){
        return true;
    }
	return false;
}

//skip a set of blankspace
void Mylexer::blankSpace(){
    
    while (current_char==' ') {
        nextcharacter();
    }
}

//to judge whether block of character is a number or not
int Mylexer::IsNumber(){
     std::string num_str;
    
    // to read valid a string of digits
    while (IsDigit(current_char)) {
        num_str += current_char;
        nextcharacter();
    }
    
    // convert into integer type and send it to yylval in bison
    yylval.int_val = std::stoi(num_str);
    return INT_CONST;
}


//to judge whether current character is a identifier or keyword
int Mylexer::IsIdentifierOrKeyword(){
    string identifier;

    //read the identifier
    while (IsDigit(current_char)||IsLetter(current_char) || current_char == '_'|| current_char == '$') {
        identifier += current_char;
        nextcharacter();
    }
    
    // check whether it is a keyword
    if (identifier == "int") {
        return INT;
    }

    if (identifier == "return") {
        return RETURN;
    }

    // if (identifier == "if") {
    //     return IF;
    // }

    // if (identifier == "else") {
    //     return ELSE;
    // }

    // if (identifier == "while") {
    //     return WHILE;
    // }

    // if (identifier == "const") {
    //     return CONST;
    // }

      // if (identifier == "main") {
    //     return MAIN;
    // }

     // if (identifier == "break") {
    //     return BREAK;
    // }

     // if (identifier == "continue") {
    //     return CONTINUE;
    // }
    
    
    // send it to yylval in bison
    yylval.str_val = new std::string(identifier);
    return IDENT;
}

//to judge whether current character is a possible dualsign or not
int Mylexer::IsdualSign(){
    for (int j = 0; j < 6; j++){
        if (current_char == DualTable[j]){
            return DualTable[j];
        }
	}
    return -1;
}


//to judge whether  block of character is a dual number
int Mylexer::IsDual(){
    int LEGENE[3][2]={{1,LE},{2,GE},{5,NE}};

    for (int i = 0; i < 3; i++){
        if(IsdualSign()==DualTable[LEGENE[i][0]]){
            nextcharacter();
            if (IsdualSign()=='='){
                nextcharacter();
                return LEGENE[i][1];
            }else{
                return DualTable[LEGENE[i][0]];
                } 
        }    
    }

    int EqualAndOr[3][2]={{0,EQ},{3,LAND},{4,LOR}};

    for (int i = 0; i < 3; i++){
        if(IsdualSign()==DualTable[EqualAndOr[i][0]]){
            nextcharacter();
            if (IsdualSign()==DualTable[EqualAndOr[i][0]]){
                nextcharacter();
                return EqualAndOr[i][1];
            }else{
                return '=';
                } 
        }    
    }
    return 0;

}

//the main function that bison receives
int Mylexer::yylex() {
    // skip a set of blankspace
    blankSpace();
    
    // end of mylex work
    if (current_char == EOF) {
        return 0;
    }
    
    // check whether is a identifier or keyword
    if (IsLetter(current_char) || current_char == '_' ||current_char == '$') {
        return IsIdentifierOrKeyword();
    }
    
    // check whether is a integer
    if (IsDigit(current_char)) {
        return IsNumber();
    }
    
    //check whether is a dualsign
    if (IsdualSign()!=-1) {
        return IsDual();
    }
    
    // for single digit charater
    int c = current_char;  
    nextcharacter();
    switch (c) {
        case '+': return '+';
        case '-': return '-';
        case '*': return '*';
        case '/': return '/';
        case '%': return '%';

        case '(': return '(';
        case ')': return ')';
        case '{': return '{';
        case '}': return '}';
        case ';': return ';';
        case ',': return ',';
        // default:
        //     return 0;
    }
    // to invalid character case，just ignore until read the next valid character
    return yylex(); 
}