#ifndef AST_H
#define AST_H

#include <memory>
#include <string>
#include <iostream>

enum class PrimaryExpType {
  exp,
  number
};

// 所有 AST 的基类
class BaseAST {
 public:
  virtual ~BaseAST() = default;
  virtual void Dump() const = 0;
};

class CompUnitAST : public BaseAST {
 public:
  std::unique_ptr<BaseAST> func_def;

  void Dump() const override {
    std::cout << "CompUnitAST { ";
    func_def->Dump();
    std::cout << " }";
  }
};

class FuncDefAST : public BaseAST {
 public:
  std::unique_ptr<BaseAST> func_type;
  std::string ident;
  std::unique_ptr<BaseAST> block;

  void Dump() const override {
    std::cout << "FuncDefAST { ";
    func_type->Dump();
    std::cout << ", " << ident << ", ";
    block->Dump();
    std::cout << " }";
  }
};

class FuncTypeAST : public BaseAST {
  public:
    std::string type;

    void Dump() const override {
      std::cout << "FuncTypeAST { " << type << " }";      
    }
};

class BlockAST : public BaseAST {
  public:
    std::unique_ptr<BaseAST> stmt;

    void Dump() const override {
      std::cout << "BlockAST { ";
      stmt->Dump();
      std::cout << " }";
    }
};

class StmtAST : public BaseAST {
  public:
    std::string stmt_type;
    std::unique_ptr<BaseAST> exp;

    void Dump() const override {
      std::cout << "StmtAST { ";
      std::cout << "stmt_type:" << stmt_type << " , ";
      exp->Dump();
      std::cout << " }";
    }
};

class PrimaryExpAST : public BaseAST {
  public:
    //使用enum类来表示类型(exp/number)
    PrimaryExpType type;
    std::unique_ptr<BaseAST> exp;
    int number;

    PrimaryExpAST(int val) : type(PrimaryExpType::number), number(val), exp(nullptr) {}
    PrimaryExpAST(std::unique_ptr<BaseAST> e)
      : type(PrimaryExpType::exp), number(0), exp(std::move(e)) {}

    void Dump() const override {
      std::cout << "PrimaryExpAST { ";
      switch (type){
        case PrimaryExpType::number:
          std::cout << "number: " << number;
          break;
        case PrimaryExpType::exp:
          std::cout << "exp: ";
          exp->Dump();
          break;
      }
      std::cout << " }";
    };  
};

class UnaryExpAST : public BaseAST {
  public:
    std::string op;
    std::unique_ptr<BaseAST> exp;
    
    void Dump() const override {
      std::cout << "UnaryExpAST { ";
      std::cout << "op: " << op << ", ";
      exp->Dump();
      std::cout << " }";
    }
};
#endif