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
            case TokenType::UNKNOWN: return "UNKNOWN";
            default: return "UNDEFINED";
        }
    }

public:
    MipsLexer() {
        // 初始化token patterns
        tokenPatterns = {
            {TokenType::KEYWORD, regex("^(add|sub|lw|sw|beq|j)")},
            {TokenType::REGISTER, regex("^\\$[a-zA-Z0-9]+")},
            {TokenType::INTEGER, regex("^-?\\d+")},
            {TokenType::LABEL, regex("^[a-zA-Z_][a-zA-Z0-9_]*:")},
            {TokenType::COMMA, regex("^,")},
            {TokenType::IDENTIFIER, regex("^[a-zA-Z_][a-zA-Z0-9_]*")},
            {TokenType::WHITESPACE, regex("^\\s+")} // 新增：处理空白字符
        };
    }

    vector<Token> tokenizeFile (const string& filename){
        vector<Token> tokens;
        ifstream file(filename);

        if (!file.is_open()){
            throw runtime_error("Unable to open file " + filename);
        }

        string line;
        int lineNumber = 1;

        while(getline(file, line)){
            auto lineTokens = tokenizeLine(line, lineNumber);
            tokens.insert(tokens.end(), lineTokens.begin(),lineTokens.end());
            lineNumber++;
        }

        file.close();
        return tokens;
    }
    vector<Token> tokenizeLine(const string& input, int lineNumber) {
        vector<Token> tokens;
        string remainingInput = input;

        while (!remainingInput.empty()) {
            bool matched = false;
            for (const auto& pattern : tokenPatterns) {
                smatch match;
                if (std::regex_search(remainingInput, match, pattern.second, regex_constants::match_continuous)) {
                    if (pattern.first != TokenType::WHITESPACE) { // 忽略空白字符
                        tokens.push_back({pattern.first, match.str(), lineNumber});
                    }
                    remainingInput = match.suffix();
                    matched = true;
                    break;
                }
            }

            if (!matched) {
                // 处理未知字符序列直到下一个空白字符
                int pos = remainingInput.find_first_of(" \t\n\r");
                if (pos == string::npos) {
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

    void printTokens(const vector<Token>& tokens) const {
        cout << left << setw(15) << "Token Type" 
        << setw(15) << "Token Value" 
        << "Line Number" << endl;
        cout << string(50, '-') << endl;

        for (const Token& token : tokens ){
            if(token.type != TokenType::WHITESPACE){
                cout << left << setw(15) << tokenTypeToString(token.type) 
                << setw(15) << token.value 
                << token.line << endl;
            }
        }
    }
};

int main() {
    MipsLexer lexer;
    std::string filename = "mips_test.txt";  // 假设MIPS代码保存在这个文件中

    try {
        auto tokens = lexer.tokenizeFile(filename);
        std::cout << "文件 '" << filename << "' 的词法分析结果：" << std::endl << std::endl;
        lexer.printTokens(tokens);
    } catch (const std::exception& e) {
        std::cerr << "错误: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}