#include <string>
#include <vector>
#include <regex>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
using namespace std;

enum class TokenType {
    KEYWORD,
    REGISTER,
    INTEGER,
    LABEL,
    COMMA,
    IDENTIFIER,
    WHITESPACE,
    COMMENT,
    DIRECTIVE,
    UNKNOWN
};

struct Token {
    TokenType type;
    string value;
    int line;
};

class MipsLexer {
private:
    vector<pair<TokenType, regex>> tokenPatterns;

    string tokenTypeToString(TokenType type) const {
        switch (type) {
            case TokenType::KEYWORD: return "KEYWORD";
            case TokenType::REGISTER: return "REGISTER";
            case TokenType::INTEGER: return "INTEGER";
            case TokenType::LABEL: return "LABEL";
            case TokenType::COMMA: return "COMMA";
            case TokenType::IDENTIFIER: return "IDENTIFIER";
            case TokenType::WHITESPACE: return "WHITESPACE";
            case TokenType::COMMENT: return "COMMENT";
            case TokenType::DIRECTIVE: return "DIRECTIVE";
            case TokenType::UNKNOWN: return "UNKNOWN";
            default: return "UNDEFINED";
        }
    }

public:
    MipsLexer() {
        // 初始化token patterns
        tokenPatterns = {
            {TokenType::COMMENT, regex("^(#.*$|/\\*[\\s\\S]*?\\*/)")},  // 单行注释和多行注释
            {TokenType::DIRECTIVE, regex("^\\.[a-zA-Z]+")},  // Directives
            {TokenType::KEYWORD, regex("^(add|sub|lw|sw|beq|j)")},
            {TokenType::REGISTER, regex("^\\$[a-zA-Z0-9]+")},
            {TokenType::INTEGER, regex("^-?\\d+")},
            {TokenType::LABEL, regex("^[a-zA-Z_][a-zA-Z0-9_]*:")},
            {TokenType::COMMA, regex("^,")},
            {TokenType::IDENTIFIER, regex("^[a-zA-Z_][a-zA-Z0-9_]*")},
            {TokenType::WHITESPACE, regex("^\\s+")}
        };
    }

    vector<Token> tokenizeFile(const string& filename) {
        vector<Token> tokens;
        ifstream file(filename);

        if (!file.is_open()) {
            throw runtime_error("Unable to open file " + filename);
        }

        string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
        file.close();

        tokens = tokenizeContent(content);
        return tokens;
    }

    vector<Token> tokenizeContent(const string& content) {
        vector<Token> tokens;
        string remainingInput = content;
        int lineNumber = 1;

        while (!remainingInput.empty()) {
            bool matched = false;
            for (const auto& pattern : tokenPatterns) {
                smatch match;
                if (regex_search(remainingInput, match, pattern.second, regex_constants::match_continuous)) {
                    if (pattern.first != TokenType::WHITESPACE) {
                        tokens.push_back({pattern.first, match.str(), lineNumber});
                    }
                    // 更新行号
                    lineNumber += count(match.str().begin(), match.str().end(), '\n');
                    remainingInput = match.suffix();
                    matched = true;
                    break;
                }
            }

            if (!matched) {
                // 处理未知字符
                tokens.push_back({TokenType::UNKNOWN, string(1, remainingInput[0]), lineNumber});
                remainingInput = remainingInput.substr(1);
            }
        }

        return tokens;
    }

    void printTokens(const vector<Token>& tokens) const {
        cout << left << setw(15) << "Token Type" 
             << setw(20) << "Token Value" 
             << "Line Number" << endl;
        cout << string(50, '-') << endl;

        for (const Token& token : tokens) {
            if (token.type != TokenType::WHITESPACE) {
                cout << left << setw(15) << tokenTypeToString(token.type) 
                     << setw(20) << (token.value.length() > 17 ? token.value.substr(0, 17) + "..." : token.value)
                     << token.line << endl;
            }
        }
    }
};

int main() {
    MipsLexer lexer;
    string filename = "mips_test.txt";  // 假设MIPS代码保存在这个文件中

    try {
        auto tokens = lexer.tokenizeFile(filename);
        cout << "文件 '" << filename << "' 的词法分析结果：" << endl << endl;
        lexer.printTokens(tokens);
    } catch (const exception& e) {
        cerr << "错误: " << e.what() << endl;
        return 1;
    }

    return 0;
}