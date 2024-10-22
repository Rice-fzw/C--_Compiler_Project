#ifndef TOKEN_TYPES_H
#define TOKEN_TYPES_H

enum class TokenType {
    KEYWORD,
    REGISTER,
    INTEGER,
    LABEL,
    COMMA,
    IDENTIFIER,
    WHITESPACE,
    COMMENT,
    STRING,
    DIRECTIVE,
    LINEBREAK,
    UNKNOWN,
};

#endif