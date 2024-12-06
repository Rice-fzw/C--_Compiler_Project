#include <string>
#include <fstream>
#include <iostream>
#include "lexer.h"
using namespace std;

// 定义全局lexer对象
Mylexer* lexer = nullptr;

// 定义包装函数
extern "C" int yylex() {
    if (lexer != nullptr) {
        return lexer->yylex();
    }
    return 0;
}

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

// to judge whether block of character is a octalNumber or not
int Mylexer::IsOctal() {
    string octal_str;
    if (current_char == '0') {
        octal_str += current_char;
        nextcharacter();
        while (current_char >= '0' && current_char <= '7') {
            octal_str += current_char;
            nextcharacter();
        }
        yylval.int_val = std::stoi(octal_str, nullptr, 8); // 转换为整数，基数为8
        return INT_CONST; 
    }
    return -1; 
}

int Mylexer::IsHexadecimal() {
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
            yylval.int_val = std::stoi(hex_str, nullptr, 16); // 转换为整数，基数为16
            return INT_CONST; 
        } else {
            infile.putback(current_char);
            current_char = '0';
        }
    }
    return -1; 
}

//to judge whether current character is a number or not
int Mylexer::IsNumber(){
    string num_str;

    if (current_char == '0') {
        int result = IsHexadecimal();
        if (result != -1) return result;

        int result2 = IsOctal();
        if (result2 != -1) return result2;
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

    if (identifier == "void") {
        return VOID;
    }

    if (identifier == "for") {
        return FOR;
    }
    
    
    // send it to yylval in bison
    yylval.str_val = new std::string(identifier);
    return IDENT;
}

//check whether is a dualsign
int Mylexer::IsdualSign(){
    for (int j = 0; j < 11; j++){
        if (current_char == DualTable[j]){
            return DualTable[j];
        }
	}
    return -1;
}

//check whether is a dualsign
int Mylexer::IsDual(){
    

    int DUAL[7][2]={{0,EQ},{1,SAR},{2,SHL},{3,LAND},{4,LOR},{6,AA},{7,MM}};
    int LEGENE[8][2]={{5,NE},{1,GE},{2,LE},{8,UE},{9,DE},{6,AE},{7,ME},{10,OE}};

    for (int i = 0; i < 7; i++){
        if(IsdualSign()==DualTable[DUAL[i][0]]){
            nextcharacter();
            if (IsdualSign()==DualTable[DUAL[i][0]]){
                nextcharacter();
                return DUAL[i][1];
            }else{
                if(current_char=='='){
                    nextcharacter();
                    return LEGENE[i][1];
                } 
                return DualTable[DUAL[i][0]];
                } 
        }    
    }
 
    for (int i = 0; i < 8; i++){
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
    return 0;

}

void Mylexer::skipcomment() {
    if (current_char == '/') {
        nextcharacter();
        if(current_char=='/'){
            while(current_char!= '\n'&&current_char!=EOF){
                nextcharacter();
            }
        }else if(current_char == '*'){
            while(true){
                if(current_char==EOF){
                    cout<<"error! uncompleted bracket"<<endl;
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

int Mylexer::IsString() {
    std::string str;
    nextcharacter();
    
    while (current_char != '"' && current_char != EOF) {
        str += current_char;
        nextcharacter();
    }
    
    if (current_char == EOF) {
        std::cerr << "Error: Unterminated string literal" << std::endl;
        return 0;
    }
    
    nextcharacter();
    yylval.str_val = new std::string(str);
    return STRING_LITERAL;
}

int Mylexer::yylex() {
    // skip a set of blankspace
    blankSpace();

    skipcomment();
    
    // end of mylex work
    if (current_char == EOF) {
        return 0;
    }
    
    // check whether is a identifier or keyword
    if (IsLetter(current_char) || current_char == '_' ||current_char == '$') {
        return IsIdentifierOrKeyword();
    }
    
    // check whether is a string
    if (current_char == '"') {
        return IsString();
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
        case '%': return '%';

        case '(': return '(';
        case ')': return ')';
        case '{': return '{';
        case '}': return '}';
        case ';': return ';';
        case ',': return ',';

        case '^': return '^';        
        case '[': return '[';
        case ']': return ']';
        // default:
        //     return 0;
    }

    // to invalid character case，just ignore until read the next valid character
    return yylex(); 
}