#include "TokenTypes.h"
#include "Token.h"
#include "MipsLexer.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <stdexcept>

std::string MipsLexer::tokenTypeToString(TokenType type) const {
    switch (type) {
        case TokenType::KEYWORD: return "KEYWORD";
        case TokenType::REGISTER: return "REGISTER";
        case TokenType::INTEGER: return "INTEGER";
        case TokenType::LABEL: return "LABEL";
        case TokenType::COMMA: return "COMMA";
        case TokenType::IDENTIFIER: return "IDENTIFIER";
        case TokenType::WHITESPACE: return "WHITESPACE";
        case TokenType::COMMENT: return "COMMENT";
        case TokenType::STRING: return "STRING";
        case TokenType::DIRECTIVE: return "DIRECTIVE";
        case TokenType::LINEBREAK: return "LINEBREAK";
        case TokenType::UNKNOWN: return "UNKNOWN";
        default: return "UNDEFINED";
    }
}

MipsLexer::MipsLexer() {
    try {
        tokenPatterns = {
            {TokenType::DIRECTIVE, std::regex("^\\.[a-zA-Z]+")},
            {TokenType::KEYWORD, std::regex("^(add|sub|lw|sw|beq|jr|la|li|j|syscall)")},
            {TokenType::REGISTER, std::regex("^\\$[a-zA-Z0-9]+")},
            {TokenType::INTEGER, std::regex("^-?\\d+")},
            {TokenType::LABEL, std::regex("^[a-zA-Z_][a-zA-Z0-9_]*:")},
            {TokenType::COMMA, std::regex("^,")},
            {TokenType::STRING, std::regex(R"(^"(?:\\[nrt]|[^"\\])*")")},
            {TokenType::IDENTIFIER, std::regex("^[a-zA-Z_][a-zA-Z0-9_]*")},
            {TokenType::WHITESPACE, std::regex("^[[:space:]]+")},
            {TokenType::LINEBREAK, std::regex("^\\n")},
            {TokenType::COMMENT, std::regex("^#[^\n]*")}
        };
    } catch (const std::regex_error& e) {
        std::cerr << "Regex error: " << e.what() << std::endl;
        throw;
    }
}

std::vector<Token> MipsLexer::tokenizeFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Unable to open file " + filename);
    }

    std::string content((std::istreambuf_iterator<char>(file)), 
                        std::istreambuf_iterator<char>());
    file.close();

    return tokenizeContent(content);
}

std::vector<Token> MipsLexer::tokenizeContent(const std::string& input) {
    std::vector<Token> tokens;
    std::string remainingInput = input;
    int lineNumber = 1;
    int tokenCount = 0;

    std::cout << "Starting tokenization process..." << std::endl;

    try {
        while (!remainingInput.empty()) {
            bool matched = false;
            for (const auto& pattern : tokenPatterns) {
                std::smatch match;
                if (std::regex_search(remainingInput, match, pattern.second, 
                                    std::regex_constants::match_continuous)) {
                    std::string matchedString = match.str();

                    if (pattern.first != TokenType::WHITESPACE ||
                        (pattern.first == TokenType::WHITESPACE && 
                         matchedString.find('\n') != std::string::npos)) {
                        tokens.emplace_back(pattern.first, matchedString, lineNumber);
                        tokenCount++;
                        std::cout << "Token " << tokenCount << " found: Type=" 
                                 << tokenTypeToString(pattern.first) 
                                 << ", Value=" << matchedString 
                                 << ", Line=" << lineNumber << std::endl;
                    }

                    size_t newlines = std::count(matchedString.begin(), 
                                               matchedString.end(), '\n');
                    if(newlines > 0 || pattern.first == TokenType::LINEBREAK) {
                        lineNumber += newlines;
                    }

                    remainingInput = match.suffix().str();
                    matched = true;
                    break;
                }
            }

            if (!matched) {
                std::cout << "Unmatched character at position " 
                         << (input.length() - remainingInput.length()) 
                         << ": '" << remainingInput[0] << "'" << std::endl;
                tokens.emplace_back(TokenType::UNKNOWN, 
                                  std::string(1, remainingInput[0]), lineNumber);
                tokenCount++;
                remainingInput = remainingInput.substr(1);
            }

            if (tokenCount % 10 == 0) {
                std::cout << tokenCount << " tokens processed..." << std::endl;
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Exception in tokenizeContent: " << e.what() << std::endl;
        throw;
    }

    std::cout << "Tokenization complete. Total tokens: " << tokenCount << std::endl;
    return tokens;
}

void MipsLexer::printTokens(const std::vector<Token>& tokens) const {
    std::cout << std::left << std::setw(15) << "Token Type" 
              << std::setw(30) << "Token Value" 
              << "Line Number" << std::endl;
    std::cout << std::string(50, '-') << std::endl;

    for (const Token& token : tokens) {
        if (token.type != TokenType::WHITESPACE) {
            std::cout << std::left << std::setw(15) 
                     << tokenTypeToString(token.type) 
                     << std::setw(30) 
                     << (token.value.length() > 20 ? 
                         token.value.substr(0, 20) + "..." : token.value)
                     << token.line << std::endl;
        }
    }
}