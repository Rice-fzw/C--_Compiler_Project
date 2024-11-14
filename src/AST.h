#ifndef AST_H
#define AST_H

#include <memory>
#include <string>
#include <iostream>
#include <sstream>
#include <cassert>

// 辅助函数：打印缩进
inline void indent(int level) {
  for (int i = 0; i < level; ++i) {
    std::cout << "  ";
  }
}

enum class PrimaryExpType {
  exp,
  number
};

// 所有 AST 的基类
class BaseAST {
 public:
  virtual ~BaseAST() = default;
  virtual void Dump(int level = 0) const = 0;
  virtual std::string dumpIR(int& tempVarCounter) const = 0;  // 修改为带临时变量计数器的IR方法
};

class CompUnitAST : public BaseAST {
 public:
  std::unique_ptr<BaseAST> func_def;

  void Dump(int level = 0) const override {
    indent(level);
    std::cout << "CompUnit {\n";
    func_def->Dump(level + 1);
    indent(level);
    std::cout << "}\n";
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

  void Dump(int level = 0) const override {
    indent(level);
    std::cout << "FuncDef {\n";
    func_type->Dump(level + 1);
    indent(level + 1);
    std::cout << "ident: " << ident << "\n";
    block->Dump(level + 1);
    indent(level);
    std::cout << "}\n";
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

  void Dump(int level = 0) const override {
    indent(level);
    std::cout << "FuncType: " << type << "\n";
  }

  std::string dumpIR(int& tempVarCounter) const override {
    return type;  // 返回类型信息，比如 "int" 或 "void"
  }
};

class BlockAST : public BaseAST {
 public:
  std::unique_ptr<BaseAST> stmt;

  void Dump(int level = 0) const override {
    indent(level);
    std::cout << "Block {\n";
    stmt->Dump(level + 1);
    indent(level);
    std::cout << "}\n";
  }

  std::string dumpIR(int& tempVarCounter) const override {
    return stmt->dumpIR(tempVarCounter);  // 返回语句的 IR 表达
  }
};

class StmtAST : public BaseAST {
 public:
  std::string stmt_type;
  std::unique_ptr<BaseAST> exp;

  void Dump(int level = 0) const override {
    indent(level);
    std::cout << "Stmt {\n";
    indent(level + 1);
    std::cout << "type: " << stmt_type << "\n";
    exp->Dump(level + 1);
    indent(level);
    std::cout << "}\n";
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
    void Dump(int level=0) const override
    {
        std::cout << "ExpAST { ";
        l_or_exp->Dump(level + 1);
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

  void Dump(int level = 0) const override {
    indent(level);
    std::cout << "PrimaryExp {\n";
    indent(level + 1);
    switch (type) {
      case PrimaryExpType::number:
        std::cout << "number: " << number << "\n";
        break;
      case PrimaryExpType::exp:
        std::cout << "exp: {\n";
        exp->Dump(level + 2);
        indent(level + 1);
        std::cout << "}\n";
        break;
    }
    indent(level);
    std::cout << "}\n";
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

// UnaryExp 处理 +, -, !
class UnaryExpAST : public BaseAST {
 public:
  std::string op;
  std::unique_ptr<BaseAST> exp;

  void Dump(int level = 0) const override {
    indent(level);
    std::cout << "UnaryExp {\n";
    indent(level + 1);
    std::cout << "op: " << op << "\n";
    exp->Dump(level + 1);
    indent(level);
    std::cout << "}\n";
  }

  std::string dumpIR(int& tempVarCounter) const override {
    std::string ir_exp = exp->dumpIR(tempVarCounter);
    std::string tempVar = "%" + std::to_string(tempVarCounter++);
//    std::cout<<"here";
    if (op == "+") return ir_exp;
    else if (op == "-") {
      std::cout << "  " << tempVar << " = sub 0, " << ir_exp << "\n";
    }
    else if (op == "!") std::cout << "  " << tempVar << " = eq " << ir_exp << ", 0\n";
    else assert(false);
    return tempVar;
  }
};

// AddExp 处理 +, -
class AddExpAST : public BaseAST {
 public:
  std::string op;
  std::unique_ptr<BaseAST> left_AST;
  std::unique_ptr<BaseAST> right_AST;

  AddExpAST(std::unique_ptr<BaseAST> left)
    : op(""), left_AST(std::move(left)), right_AST(nullptr) {}

  AddExpAST(std::string op, std::unique_ptr<BaseAST> left, std::unique_ptr<BaseAST> right)
    : op(op), left_AST(std::move(left)), right_AST(std::move(right)) {}

  void Dump(int level = 0) const override {
    indent(level);
    std::cout << "AddExp {\n";
    if (right_AST) {
      indent(level + 1);
      std::cout << "op: " << op << "\n";
      indent(level + 1);
      std::cout << "left_AST: {\n";
      left_AST->Dump(level + 2);
      indent(level + 1);
      std::cout << "}\n";
      indent(level + 1);
      std::cout << "right_AST: {\n";
      right_AST->Dump(level + 2);
      indent(level + 1);
      std::cout << "}\n";
    } else {
      left_AST->Dump(level + 1);
    }
    indent(level);
    std::cout << "}\n";
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

// MulExp 处理 *, /, %
class MulExpAST : public BaseAST {
 public:
  std::string op;
  std::unique_ptr<BaseAST> left_AST;
  std::unique_ptr<BaseAST> right_AST;

  MulExpAST(std::unique_ptr<BaseAST> left)
    : op(""), left_AST(std::move(left)), right_AST(nullptr) {}

  MulExpAST(std::string op, std::unique_ptr<BaseAST> left, std::unique_ptr<BaseAST> right)
    : op(op), left_AST(std::move(left)), right_AST(std::move(right)) {}

  void Dump(int level = 0) const override {
    indent(level);
    std::cout << "MulExp {\n";
    if (right_AST) {
      indent(level + 1);
      std::cout << "op: " << op << "\n";
      indent(level + 1);
      std::cout << "left_AST: {\n";
      left_AST->Dump(level + 2);
      indent(level + 1);
      std::cout << "}\n";
      indent(level + 1);
      std::cout << "right_AST: {\n";
      right_AST->Dump(level + 2);
      indent(level + 1);
      std::cout << "}\n";
    } else {
      left_AST->Dump(level + 1);
    }
    indent(level);
    std::cout << "}\n";
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

// RelExpAST  处理 <, >, <=, >=
class RelExpAST : public BaseAST {
 public:
  std::string op;
  std::unique_ptr<BaseAST> left_AST;
  std::unique_ptr<BaseAST> right_AST;
  
  RelExpAST(std::unique_ptr<BaseAST> left)
    : op(""), left_AST(std::move(left)), right_AST(nullptr) {}

  RelExpAST(std::string op, std::unique_ptr<BaseAST> left, std::unique_ptr<BaseAST> right)
    : op(op), left_AST(std::move(left)), right_AST(std::move(right)) {}

  void Dump(int level = 0) const override {
    indent(level);
    std::cout << "RelExp {\n";
    if (right_AST) {
      indent(level + 1);
      std::cout << "op: " << op << "\n";
      indent(level + 1);
      std::cout << "left_AST: {\n";
      left_AST->Dump(level + 2);
      indent(level + 1);
      std::cout << "}\n";
      indent(level + 1);
      std::cout << "right_AST: {\n";
      right_AST->Dump(level + 2);
      indent(level + 1);
      std::cout << "}\n";
    } else {
      left_AST->Dump(level + 1);
    }
    indent(level);
    std::cout << "}\n";
  }
};

// EqExpAST 处理 ==, !=
class EqExpAST : public BaseAST {
 public:
  std::string op;
  std::unique_ptr<BaseAST> left_AST;
  std::unique_ptr<BaseAST> right_AST;
  
  EqExpAST(std::unique_ptr<BaseAST> left)
    : op(""), left_AST(std::move(left)), right_AST(nullptr) {}

  EqExpAST(std::string op, std::unique_ptr<BaseAST> left, std::unique_ptr<BaseAST> right)
    : op(op), left_AST(std::move(left)), right_AST(std::move(right)) {}

  void Dump(int level = 0) const override {
    indent(level);
    std::cout << "EqExp {\n";
    if (right_AST) {
      indent(level + 1);
      std::cout << "op: " << op << "\n";
      indent(level + 1);
      std::cout << "left_AST: {\n";
      left_AST->Dump(level + 2);
      indent(level + 1);
      std::cout << "}\n";
      indent(level + 1);
      std::cout << "right_AST: {\n";
      right_AST->Dump(level + 2);
      indent(level + 1);
      std::cout << "}\n";
    } else {
      left_AST->Dump(level + 1);
    }
    indent(level);
    std::cout << "}\n";
  }
};

// LAndExpAST 处理 &&
class LAndExpAST : public BaseAST {
 public:
  std::string op = "&&";
  std::unique_ptr<BaseAST> left_AST;
  std::unique_ptr<BaseAST> right_AST;
  
  LAndExpAST(std::unique_ptr<BaseAST> left)
    : left_AST(std::move(left)), right_AST(nullptr) {}

  LAndExpAST(std::string op, std::unique_ptr<BaseAST> left, std::unique_ptr<BaseAST> right)
    : op(op), left_AST(std::move(left)), right_AST(std::move(right)) {}

  void Dump(int level = 0) const override {
    indent(level);
    std::cout << "LAndExp {\n";
    if (right_AST) {
      indent(level + 1);
      std::cout << "op: " << op << "\n";
      indent(level + 1);
      std::cout << "left_AST: {\n";
      left_AST->Dump(level + 2);
      indent(level + 1);
      std::cout << "}\n";
      indent(level + 1);
      std::cout << "right_AST: {\n";
      right_AST->Dump(level + 2);
      indent(level + 1);
      std::cout << "}\n";
    } else {
      left_AST->Dump(level + 1);
    }
    indent(level);
    std::cout << "}\n";
  }
};

// LOrExpAST 处理 ||
class LOrExpAST : public BaseAST {
 public:
  std::string op = "||";
  std::unique_ptr<BaseAST> left_AST;
  std::unique_ptr<BaseAST> right_AST;
  
  LOrExpAST(std::unique_ptr<BaseAST> left)
    : left_AST(std::move(left)), right_AST(nullptr) {}

  LOrExpAST(std::string op, std::unique_ptr<BaseAST> left, std::unique_ptr<BaseAST> right)
    : op(op), left_AST(std::move(left)), right_AST(std::move(right)) {}

  void Dump(int level = 0) const override {
    indent(level);
    std::cout << "LOrExp {\n";
    if (right_AST) {
      indent(level + 1);
      std::cout << "op: " << op << "\n";
      indent(level + 1);
      std::cout << "left_AST: {\n";
      left_AST->Dump(level + 2);
      indent(level + 1);
      std::cout << "}\n";
      indent(level + 1);
      std::cout << "right_AST: {\n";
      right_AST->Dump(level + 2);
      indent(level + 1);
      std::cout << "}\n";
    } else {
      left_AST->Dump(level + 1);
    }
    indent(level);
    std::cout << "}\n";
  }
};

// 常量声明
class ConstDeclAST : public BaseAST {
 public:
  // 基础类型 (int)
  std::string btype;
  // 常量定义列表
  std::vector<std::unique_ptr<BaseAST>> const_defs;

  void Dump(int level = 0) const override {
    indent(level);
    std::cout << "ConstDecl {\n";
    indent(level + 1);
    std::cout << "btype: " << btype << "\n";
    indent(level + 1);
    std::cout << "const_defs: [\n";
    for (const auto& def : const_defs) {
      def->Dump(level + 2);
    }
    indent(level + 1);
    std::cout << "]\n";
    indent(level);
    std::cout << "}\n";
  }
};

// 常量定义
class ConstDefAST : public BaseAST {
 public:
  std::string ident;
  std::unique_ptr<BaseAST> const_init_val;

  void Dump(int level = 0) const override {
    indent(level);
    std::cout << "ConstDef {\n";
    indent(level + 1);
    std::cout << "ident: " << ident << "\n";
    indent(level + 1);
    std::cout << "const_init_val: {\n";
    const_init_val->Dump(level + 2);
    indent(level + 1);
    std::cout << "}\n";
    indent(level);
    std::cout << "}\n";
  }
};

// 更新BlockAST以支持多个语句
class BlockAST : public BaseAST {
 public:
  std::vector<std::unique_ptr<BaseAST>> items;

  void Dump(int level = 0) const override {
    indent(level);
    std::cout << "Block {\n";
    indent(level + 1);
    std::cout << "items: [\n";
    for (const auto& item : items) {
      item->Dump(level + 2);
    }
    indent(level + 1);
    std::cout << "]\n";
    indent(level);
    std::cout << "}\n";
  }
};

// 左值表达式
class LValAST : public BaseAST {
 public:
  std::string ident;

  explicit LValAST(const std::string& name) : ident(name) {}

  void Dump(int level = 0) const override {
    indent(level);
    std::cout << "LVal {\n";
    indent(level + 1);
    std::cout << "ident: " << ident << "\n";
    indent(level);
    std::cout << "}\n";
  }
};

#endif