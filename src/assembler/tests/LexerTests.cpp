// LexerTests.cpp 示例
#include <cassert>
#include "../include/MipsLexer.h"
#include <iostream>

void testBasicTokenization() {
    MipsLexer lexer;
    std::vector<Token> tokens = lexer.tokenizeContent("add $t0, $t1, $t2");
    
    assert(tokens[0].type == TokenType::KEYWORD);
    assert(tokens[0].value == "add");
    assert(tokens[1].type == TokenType::REGISTER);
    // ... 更多断言
}

int main() {
    std::cout << "Running lexer tests..." << std::endl;
    testBasicTokenization();
    std::cout << "All tests passed!" << std::endl;
    return 0;
}