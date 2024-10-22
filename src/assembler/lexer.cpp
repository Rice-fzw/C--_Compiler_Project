#include <string>
#include <vector>
#include <regex>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <stdexcept>
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
    LINEBREAK,
    UNKNOWN,
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
            case TokenType::LINEBREAK: return "LINEBREAK";
            case TokenType::UNKNOWN: return "UNKNOWN";
            default: return "UNDEFINED";
        }
    }

public:
    MipsLexer() {
        try {
            tokenPatterns = {
                {TokenType::DIRECTIVE, regex("^\\.[a-zA-Z]+")},
                {TokenType::KEYWORD, regex("^(add|sub|lw|sw|beq|j)")},
                {TokenType::REGISTER, regex("^\\$[a-zA-Z0-9]+")},
                {TokenType::INTEGER, regex("^-?\\d+")},
                {TokenType::LABEL, regex("^[a-zA-Z_][a-zA-Z0-9_]*:")},
                {TokenType::COMMA, regex("^,")},
                {TokenType::IDENTIFIER, regex("^[a-zA-Z_][a-zA-Z0-9_]*")},
                {TokenType::WHITESPACE, regex("^[\\s&&[^\n]]+")},
                {TokenType::LINEBREAK, regex("^\\n")},
                {TokenType::COMMENT, regex("^\\#[a-zA-Z0-9]+")}
            };
        } catch (const regex_error& e) {
            cerr << "Regex error: " << e.what() << endl;
            throw;
        }
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

    vector<Token> tokenizeContent(const string& input) {
        vector<Token> tokens;
        string remainingInput = input;
        int lineNumber = 1;
        int tokenCount = 0;

        cout << "Starting tokenization process..." << endl;

        try {
            while (!remainingInput.empty()) {
                bool matched = false;
                for (const auto& pattern : tokenPatterns) {
                    smatch match;
                    if (regex_search(remainingInput, match, pattern.second, regex_constants::match_continuous)) {
                        if (pattern.first != TokenType::WHITESPACE) {
                            tokens.push_back({pattern.first, match.str(), lineNumber});
                            tokenCount++;
                            cout << "Token " << tokenCount << " found: Type=" << tokenTypeToString(pattern.first) 
                                 << ", Value=" << match.str() << ", Line=" << lineNumber << endl;
                        }

                        string matchedString = match.str();
                        size_t newlines = count(matchedString.begin(), matchedString.end(), '\n');
                        lineNumber += newlines;

                        if(newlines == 0 && pattern.first == TokenType::LINEBREAK){
                            lineNumber++;
                        }
                        remainingInput = match.suffix().str();
                        matched = true;
                        break;
                    }
                }

                if (!matched) {
                    cout << "Unmatched character at position " << (input.length() - remainingInput.length()) 
                         << ": '" << remainingInput[0] << "'" << endl;
                    tokens.push_back({TokenType::UNKNOWN, string(1, remainingInput[0]), lineNumber});
                    tokenCount++;
                    remainingInput = remainingInput.substr(1);
                }

                if (tokenCount % 10 == 0) {
                    cout << tokenCount << " tokens processed..." << endl;
                }
            }
        } catch (const exception& e) {
            cerr << "Exception in tokenizeContent: " << e.what() << endl;
            throw;
        }

        cout << "Tokenization complete. Total tokens: " << tokenCount << endl;
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
    try {
        MipsLexer lexer;
        string filename = "mips_test.txt";
        cout << "Begin to tokenize" << endl;

        cout << "Attempting to open file: " << filename << endl;
        ifstream file(filename);
        if (!file.is_open()) {
            throw runtime_error("Unable to open file " + filename);
        }
        cout << "File opened successfully" << endl;

        string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
        cout << content << endl;
        file.close();
        cout << "File content read. Content length: " << content.length() << endl;

        cout << "Tokenizing content..." << endl;
        auto tokens = lexer.tokenizeContent(content);
        cout << "Tokenization complete. Number of tokens: " << tokens.size() << endl;

        cout << "\nToken analysis results for file '" << filename << "':" << endl;
        lexer.printTokens(tokens);

        cout << "Program completed successfully" << endl;
    } catch (const exception& e) {
        cerr << "Fatal error: " << e.what() << endl;
        return 1;
    }

    return 0;
}