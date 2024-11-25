#include <string>
#include <fstream>
#include <iostream>
#include "lexer.h"
using namespace std;

Lexer* lexer = nullptr;

extern "C" int yylex() {
    if (lexer != nullptr) {
        return lexer->yylex();
    }
    return 0;
}

//constructor: open the source file
Lexer::Lexer(string name){
    infile.open(name, ios::in); 
    if (!infile) {
    cerr << "unable to open file" << endl;
    }
}

//To read the next character
void Lexer::nextcharacter(){
     current_char = infile.get();
}

//to judge whether current character is a letter or not
bool Lexer::IsLetter(char ch){
    if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')){
        return true;
    }
	return false;
}  

//to judge whether current character is a digit or not
bool Lexer::IsDigit(char ch){
    if (ch >= '0'&& ch <= '9'){
        return true;
    }
	return false;
}

//skip a set of blankspace
void Lexer::blankSpace(){  
    while (current_char==' ') {
        nextcharacter();
    }
}

//to judge whether current character is a number or not
int Lexer::IsNumber(){
    string num_str;
    
    //judge possible Hexadecimal or Octal
    if (current_char == '0') {
        if (IsHexadecimal() != -1) return IsHexadecimal();
        if (IsOctal() != -1) return IsOctal();
    }

    // to read valid a string of digits
    while (IsDigit(current_char)) {
        num_str += current_char;
        nextcharacter();
    }
    
    // convert into integer type and send it to yylval in bison
    yylval.int_val = std::stoi(num_str);
    return INT_CONST;
}

// to judge whether block of character is a octalNumber or not
int Lexer::IsOctal() {
    string octal_str;
    if (current_char == '0') {
        octal_str += current_char;
        nextcharacter();
        while (current_char >= '0' && current_char <= '7') {
            octal_str += current_char;
            nextcharacter();
        }
        yylval.int_val = std::stoi(octal_str, nullptr, 8); 
        return INT_CONST; 
    }
    return -1; 
}

// to judge whether block of character is a hexadecimalNumber or not
int Lexer::IsHexadecimal() {
    string hex_str;
    if (current_char == '0') {
        hex_str += current_char;
        nextcharacter();
        if (current_char == 'x' || current_char == 'X') {
            hex_str += current_char;
            nextcharacter();
            while ((current_char >= '0' && current_char <= '9') || 
                   (current_char >= 'a' && current_char <= 'f') || 
                   (current_char >= 'A' && current_char <= 'F')) {
                hex_str += current_char;
                nextcharacter();
            }
            yylval.int_val = std::stoi(hex_str, nullptr, 16); 
            return INT_CONST; 
        } else {
            infile.putback(current_char);
            current_char = '0';
        }
    }
    return -1;
}

//to judge whether block of character is a identifier or not
int Lexer::IsIdentifierOrKeyword(){
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

    if (identifier == "if") {
        return IF;
    }

    if (identifier == "else") {
        return ELSE;
    }

    if (identifier == "while") {
        return WHILE;
    }

    if (identifier == "const") {
        return CONST;
    }

    if (identifier == "break") {
        return BREAK;
    }

    if (identifier == "continue") {
        return CONTINUE;
    }

    // if (identifier == "putint") {
    //     return PUTINT;
    // }

    if (identifier == "void") {
        return VOID;
    }

    // send it to yylval in bison
    yylval.str_val = new std::string(identifier);
    return IDENT;
}

//to judge whether it is a possible dualsign
int Lexer::IsdualSign(){
    for (int j = 0; j < 6; j++){
        if (current_char == DualTable[j]){
            return DualTable[j];
        }
	}
    return -1;
}

//to judge whether  block of character is a possible dual
int Lexer::IsDual(){
    int LEGENE[3][2]={{1,GE},{2,LE},{5,NE}};
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

//to skip comment(single/block)
void Lexer::skipcomment() {
    if (current_char == '/') {
        nextcharacter();
        if(current_char=='/'){
            while(current_char!= '/n'&&current_char!=EOF){
                nextcharacter();
            }
        }else if(current_char == '*'){
            while(true){
                if(current_char==EOF){
                    cout<<"error! uncompleted loop"<<endl;
                }else if(current_char=='*'){
                        nextcharacter();
                        if(current_char=='/'){
                            nextcharacter();
                            break;
                        }
                    }else{
                        nextcharacter();
                    }              
            }
        }else{
            infile.putback(current_char);
            current_char = '/';
        }
    }
}

//the main function that bison receives
int Lexer::yylex() {
    // skip a set of blankspace
    blankSpace();
    
    //check whether is a comment
    skipcomment();

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