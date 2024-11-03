#ifndef AST_NODES_H
#define AST_NODES_H

#include <memory>
#include <vector>
#include <string>

// 所有可能的节点类型枚举
enum class NodeType {
    PROGRAM,
    FUNCTION_DEF,
    VAR_DECLARATION,
    IF_STATEMENT,
    BINARY_EXPR,
    NUMBER_LITERAL,
    VARIABLE_REF,
    RETURN_STMT
};

// 基础节点
class ASTNode {
public:
    NodeType type;
    virtual ~ASTNode() = default;
};

// 程序根节点
class Program : public ASTNode {
public:
    std::vector<std::unique_ptr<ASTNode>> functions;
    Program() { type = NodeType::PROGRAM; }
};

// 函数定义节点
class FunctionDef : public ASTNode {
public:
    std::string returnType;
    std::string name;
    std::vector<std::unique_ptr<ASTNode>> body;
    
    FunctionDef() { type = NodeType::FUNCTION_DEF; }
};

// 变量声明节点
class VarDeclaration : public ASTNode {
public:
    std::string varType;
    std::string name;
    std::unique_ptr<ASTNode> initializer;
    
    VarDeclaration() { type = NodeType::VAR_DECLARATION; }
};

// If语句节点
class IfStatement : public ASTNode {
public:
    std::unique_ptr<ASTNode> condition;
    std::vector<std::unique_ptr<ASTNode>> thenBlock;
    std::vector<std::unique_ptr<ASTNode>> elseBlock;
    
    IfStatement() { type = NodeType::IF_STATEMENT; }
};

// 二元表达式节点
class BinaryExpr : public ASTNode {
public:
    std::unique_ptr<ASTNode> left;
    std::string op;
    std::unique_ptr<ASTNode> right;
    
    BinaryExpr() { type = NodeType::BINARY_EXPR; }
};

// 数字字面量节点
class NumberLiteral : public ASTNode {
public:
    int value;
    
    NumberLiteral() { type = NodeType::NUMBER_LITERAL; }
};

// 变量引用节点
class VariableRef : public ASTNode {
public:
    std::string name;
    
    VariableRef() { type = NodeType::VARIABLE_REF; }
};

#endif ASTAST_NODES_H