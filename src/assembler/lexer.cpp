#include <string>
#include <vector>
#include <regex>
#include <iostream>
#include <iomanip>

enum class TokenType {
    KEYWORD,
    REGISTER,
    INTEGER,
    LABEL,
    COMMA,
    IDENTIFIER,
    WHITESPACE,
    UNKNOWN
};

struct Token {
    TokenType type;
    std::string value;
};

class MipsLexer {
private:
    std::vector<std::pair<TokenType, std::regex>> tokenPatterns;

public:
    MipsLexer() {
        // 初始化token模式
        tokenPatterns = {
            {TokenType::KEYWORD, std::regex("^(add|sub|lw|sw|beq|j)")},
            {TokenType::REGISTER, std::regex("^\\$[a-zA-Z0-9]+")},
            {TokenType::INTEGER, std::regex("^-?\\d+")},
            {TokenType::LABEL, std::regex("^[a-zA-Z_][a-zA-Z0-9_]*:")},
            {TokenType::COMMA, std::regex("^,")},
            {TokenType::IDENTIFIER, std::regex("^[a-zA-Z_][a-zA-Z0-9_]*")},
            {TokenType::WHITESPACE, std::regex("^\\s+")} // 新增：处理空白字符
        };
    }

    std::vector<Token> tokenize(const std::string& input) {
        std::vector<Token> tokens;
        std::string remainingInput = input;

        while (!remainingInput.empty()) {
            bool matched = false;
            for (const auto& pattern : tokenPatterns) {
                std::smatch match;
                if (std::regex_search(remainingInput, match, pattern.second, std::regex_constants::match_continuous)) {
                    if (pattern.first != TokenType::WHITESPACE) { // 忽略空白字符
                        tokens.push_back({pattern.first, match.str()});
                    }
                    remainingInput = match.suffix();
                    matched = true;
                    break;
                }
            }

            if (!matched) {
                // 处理未知字符序列直到下一个空白字符
                int pos = remainingInput.find_first_of(" \t\n\r");
                if (pos == std::string::npos) {
                    // 如果没有找到空白字符，处理剩余的所有字符
                    tokens.push_back({TokenType::UNKNOWN, remainingInput});
                    remainingInput.clear();
                } else {
                    // 处理到下一个空白字符之前的所有字符
                    tokens.push_back({TokenType::UNKNOWN, remainingInput.substr(0, pos)});
                    remainingInput = remainingInput.substr(pos);
                }
            }
        }

        return tokens;
    }

        std::string tokenTypeToString(TokenType type) const {
        switch (type) {
            case TokenType::KEYWORD: return "KEYWORD";
            case TokenType::REGISTER: return "REGISTER";
            case TokenType::INTEGER: return "INTEGER";
            case TokenType::LABEL: return "LABEL";
            case TokenType::COMMA: return "COMMA";
            case TokenType::IDENTIFIER: return "IDENTIFIER";
            case TokenType::WHITESPACE: return "WHITESPACE";
            case TokenType::UNKNOWN: return "UNKNOWN";
            default: return "UNDEFINED";
        }
    }
    std::string printTokens(const std::vector<Token>& tokens) const {
        std::cout << std::left << std::setw(15) << "Token Type" << "Token Value" << std::endl;
        std::cout << std::string(40, '-') << std::endl;

        for (const Token& token : tokens ){
            if(token.type != TokenType::WHITESPACE){
                std::cout << std::left << std::setw(15) 
                << tokenTypeToString(token.type) 
                << token.value << std::endl;
            }
        }
    }
};