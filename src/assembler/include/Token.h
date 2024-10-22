#ifndef TOKEN_H
#define TOKEN_H

#include "TokenTypes.h"
#include <string>

struct Token {
    TokenType type;
    std::string value;
    int line;

    Token(TokenType t, const std::string& v, int l) 
        : type(t), value(v), line(l) {}
};

#endif