// parser.h
#ifndef PARSER_H
#define PARSER_H

#include <memory>
#include <vector>
#include <string>
#include "token.h" // 需要Scanner提供的Token定义

// 抽象语法树节点基类
class ASTNode {
public:
    virtual ~ASTNode() = default;
    // 可以添加访问者模式接口
    // virtual void accept(ASTVisitor& visitor) = 0;
};

// 表达式节点基类
class Expression : public ASTNode {
public:
    virtual ~Expression() = default;
};

// 语句节点基类
class Statement : public ASTNode {
public:
    virtual ~Statement() = default;
};

// 二元操作符表达式节点
class BinaryExpression : public Expression {
public:
    std::unique_ptr<Expression> left;
    std::string op;  // 操作符
    std::unique_ptr<Expression> right;
    
    BinaryExpression(std::unique_ptr<Expression> l, const std::string& op_, std::unique_ptr<Expression> r)
        : left(std::move(l)), op(op_), right(std::move(r)) {}
};

// 变量声明节点
class VariableDeclaration : public Statement {
public:
    std::string type;
    std::string name;
    std::unique_ptr<Expression> initializer;
    
    VariableDeclaration(const std::string& t, const std::string& n, 
                       std::unique_ptr<Expression> init = nullptr)
        : type(t), name(n), initializer(std::move(init)) {}
};

// Parser类
class Parser {
private:
    std::vector<Token> tokens;
    size_t current = 0;  // 当前处理的token位置

    // 辅助方法
    Token peek();        // 查看当前token
    Token advance();     // 移动到下一个token
    bool match(TokenType type);  // 检查当前token类型是否匹配
    bool isAtEnd();     // 是否到达结尾

    // 递归下降解析方法
    std::unique_ptr<Expression> parseExpression();
    std::unique_ptr<Expression> parseTerm();
    std::unique_ptr<Expression> parseFactor();
    std::unique_ptr<Statement> parseStatement();
    std::unique_ptr<Statement> parseVariableDeclaration();
    std::unique_ptr<Statement> parseIfStatement();
    std::unique_ptr<Statement> parseWhileStatement();
    std::unique_ptr<Statement> parseForStatement();

public:
    explicit Parser(std::vector<Token> tokens_) : tokens(std::move(tokens_)) {}
    
    // 主解析方法
    std::vector<std::unique_ptr<ASTNode>> parse();
};

#endif // PARSER_H