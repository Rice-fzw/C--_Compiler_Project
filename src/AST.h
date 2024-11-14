#ifndef AST_H
#define AST_H

#include <memory>
#include <string>
#include <iostream>
#include <sstream>
#include <cassert>

enum class PrimaryExpType {
  exp,
  number
};

// 所有 AST 的基类
class BaseAST {
 public:
  virtual ~BaseAST() = default;
  virtual void Dump() const = 0;
  virtual std::string dumpIR(int& tempVarCounter) const = 0;  // 修改为带临时变量计数器的IR方法
};

class CompUnitAST : public BaseAST {
 public:
  std::unique_ptr<BaseAST> func_def;

  void Dump() const override {
    std::cout << "CompUnitAST { ";
    func_def->Dump();
    std::cout << " }";
  }

  std::string dumpIR(int& tempVarCounter) const override {
    return func_def->dumpIR(tempVarCounter);
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

  std::string dumpIR(int& tempVarCounter) const override {
    // 输出函数定义的 IR 代码
    std::cout << "fun @" << ident << "()";
    if (func_type->dumpIR(tempVarCounter) == "int") {
      std::cout << ": i32 ";
    }
    std::cout << "{\n";    // 函数体开始
    std::cout << "%entry:\n";
    std::string block_ir = block->dumpIR(tempVarCounter);  // 获取 block 的 IR 表达
    if (block_ir != "ret") {
      std::cout << "  ret 0\n";  // 默认返回0
    }
    std::cout << "}\n";          // 函数体结束
    return "";
  }
};

class FuncTypeAST : public BaseAST {
 public:
  std::string type;

  void Dump() const override {
    std::cout << "FuncTypeAST { " << type << " }";      
  }

  std::string dumpIR(int& tempVarCounter) const override {
    return type;  // 返回类型信息，比如 "int" 或 "void"
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

  std::string dumpIR(int& tempVarCounter) const override {
    return stmt->dumpIR(tempVarCounter);  // 返回语句的 IR 表达
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

  std::string dumpIR(int& tempVarCounter) const override {
    if (stmt_type == "return") {
//      std::cout<<"here"<<"\n";
      std::string IRR=exp->dumpIR(tempVarCounter);
      std::cout <<"  " << "ret " << IRR << "\n";  // 生成返回语句的 IR
      return "ret";
    }
    return "";
  }
};

class ExpAST : public BaseAST {
public:
    std::unique_ptr<BaseAST> l_or_exp;
    void Dump() const override
    {
        std::cout << "ExpAST { ";
        l_or_exp->Dump();
        std::cout << " } ";
    }
    std::string dumpIR(int& tempVarCounter) const override
    {
//        std::cout<<"here";
        return l_or_exp->dumpIR(tempVarCounter);
    }
};

class PrimaryExpAST : public BaseAST {
 public:
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
  }

  std::string dumpIR(int& tempVarCounter) const override {
//    std::cout<<"here"<<"\n";
    if (type == PrimaryExpType::number) {
//      std::cout<<"ret"<<" ";
      return std::to_string(number);
    } else if (type == PrimaryExpType::exp) {
    //  std::string u=exp->dumpIR(tempVarCounter);
    //  std::cout << "!!!!\n"<<"\n";
      return exp->dumpIR(tempVarCounter);  // 如果是表达式，递归调用其 `dumpIR`
    }
    return "";
  } 
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

  std::string dumpIR(int& tempVarCounter) const override {
    std::string ir_exp = exp->dumpIR(tempVarCounter);
    std::string tempVar = "%" + std::to_string(tempVarCounter++);
//    std::cout<<"here";
    if (op == "+") return ir_exp;
    else if (op == "-") {
      std::cout << "  " << tempVar << " = sub 0, " << ir_exp << "\n";
    }
    else if (op == "!") std::cout << "  " << tempVar << " = eq " << ir_exp <<"\n";
    else assert(false);
    return tempVar;
  }
};

// 加法和减法表达式
class AddExpAST : public BaseAST {
 public:
  std::string op;
  std::unique_ptr<BaseAST> left_AST;
  std::unique_ptr<BaseAST> right_AST;

  AddExpAST(std::unique_ptr<BaseAST> left)
    : op(""), left_AST(std::move(left)), right_AST(nullptr) {}

  AddExpAST(std::string op, std::unique_ptr<BaseAST> left, std::unique_ptr<BaseAST> right)
    : op(op), left_AST(std::move(left)), right_AST(std::move(right)) {}

  void Dump() const override {
    std::cout << "AddExpAST { ";
    if (right_AST) {
      std::cout << "op: " << op << ", ";
      left_AST->Dump();
      std::cout << ", ";
      right_AST->Dump();
    } else {
      left_AST->Dump();
    }
    std::cout << " }";
  }

  std::string dumpIR(int& tempVarCounter) const override {
    std::string left_ir = left_AST->dumpIR(tempVarCounter);
    if (right_AST) {
      std::string right_ir = right_AST->dumpIR(tempVarCounter);
      std::string tempVar = "%" + std::to_string(tempVarCounter++);
      if(op=="+"){
        std::cout << "  " << tempVar << " = add " << left_ir << ", " << right_ir << "\n";
      }
      else if(op=="-"){
        std::cout << "  " << tempVar << " = sub " << left_ir << ", " << right_ir << "\n";
      }
      else assert(false);
//      std::cout << "!!!!\n"<<tempVar<<"\n";
      return tempVar;
    }
//    std::cout<<"asdf\n";
    return left_ir;
  }
};

// 乘法和除法表达式
class MulExpAST : public BaseAST {
 public:
  std::string op;
  std::unique_ptr<BaseAST> left_AST;
  std::unique_ptr<BaseAST> right_AST;

  MulExpAST(std::unique_ptr<BaseAST> left)
    : op(""), left_AST(std::move(left)), right_AST(nullptr) {}

  MulExpAST(std::string op, std::unique_ptr<BaseAST> left, std::unique_ptr<BaseAST> right)
    : op(op), left_AST(std::move(left)), right_AST(std::move(right)) {}

  void Dump() const override {
    std::cout << "MulExpAST { ";
    if (right_AST) {
      std::cout << "op: " << op << ", ";
      left_AST->Dump();
      std::cout << ", ";
      right_AST->Dump();
    } else {
      left_AST->Dump();
    }
    std::cout << " }";
  }

  std::string dumpIR(int& tempVarCounter) const override {
    std::string left_ir = left_AST->dumpIR(tempVarCounter);
    if (right_AST) {
      std::string right_ir = right_AST->dumpIR(tempVarCounter);
//      std::cout<<"here";
      std::string tempVar = "%" + std::to_string(tempVarCounter++);
      if(op=="*"){
        std::cout << "  " << tempVar << " = mul " << left_ir << ", " << right_ir << "\n";
      }
      else if(op=="/"){
        std::cout << "  " << tempVar << " = div " << left_ir << ", " << right_ir << "\n";
      }
      else if(op=="%"){
        std::cout << "  " << tempVar << " = mod " << left_ir << ", " << right_ir << "\n";
      }
      else assert(false);
      return tempVar;
    }
    return left_ir;
  }
};

#endif