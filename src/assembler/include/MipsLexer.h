#ifndef MIPS_LEXER_H
#define MIPS_LEXER_H

#include "TokenTypes.h"
#include "Token.h"
#include <vector>
#include <regex>
#include <utility>

class MipsLexer {
private:
    std::vector<std::pair<TokenType, std::regex>> tokenPatterns;
    std::string tokenTypeToString(TokenType type) const;

public:
    // 构造函数
    MipsLexer();

    // 文件处理
    std::vector<Token> tokenizeFile(const std::string& filename);
    
    // 内容处理
    std::vector<Token> tokenizeContent(const std::string& input);
    
    // 打印功能
    void printTokens(const std::vector<Token>& tokens) const;
};

#endif