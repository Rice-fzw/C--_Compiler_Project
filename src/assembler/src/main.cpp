#include "MipsLexer.h"
#include <iostream>
#include <stdexcept>

int main() {
    try {
        MipsLexer lexer;
        std::string filename = "test/mips_test.txt";
        std::cout << "Begin to tokenize" << std::endl;

        std::cout << "Attempting to open file: " << filename << std::endl;
        auto tokens = lexer.tokenizeFile(filename);
        std::cout << "Tokenization complete. Number of tokens: " 
                  << tokens.size() << std::endl;

        std::cout << "\nToken analysis results for file '" 
                  << filename << "':" << std::endl;
        lexer.printTokens(tokens);

        std::cout << "Program completed successfully" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Fatal error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}