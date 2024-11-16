#ifndef AST_H
#define AST_H

#include <memory>
#include <string>
#include <iostream>
#include <sstream>
#include <cassert>

static int symbol_num = 0;

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
  std::string dumpIR(int& tempVarCounter) const override {
    std::string left_result = right_AST->dumpIR(tempVarCounter);
    std::string right_result = left_AST->dumpIR(tempVarCounter);
    std::string tempVar="%" + std::to_string(++tempVarCounter);
    if (op == "<"){
      std::cout << '\t' << tempVar << " = lt" << left_result << ", " << right_result << "\n";
    }
    else if (op == ">"){
      std::cout << '\t' << tempVar << " = gt" << left_result << ", " << right_result << "\n";
    }
    else if (op=="<="){
      std::cout << '\t' << tempVar << " = le" << left_result << ", " << right_result << "\n";
    }
    else if (op==">="){
      std::cout << '\t' << tempVar << " = ge" << left_result << ", " << right_result << "\n";
    }
    else assert(false);
    return tempVar;
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
  std::string dumpIR(int& tempVarCounter) const override {
    std::string left_result = right_AST->dumpIR(tempVarCounter);
    std::string right_result = left_AST->dumpIR(tempVarCounter);
    std::string tempVar= "%" + std::to_string(++tempVarCounter);
    if (op == "=="){
      std::cout << '\t' << tempVar << " = eq" << left_result << ", " << right_result << "\n";
    }
    else if (op == "!="){
      std::cout << '\t' << tempVar << " = ne" << left_result << ", " << right_result << "\n";
    }
    else assert(false);
    return tempVar;
  }
};

// LAndExpAST 处理 && *still have some problem
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

  std::string dumpIR(int& tempVarCounter) const override {
    std::string result_var = "";
    std::cout << ("hear!!\n");
    if (!right_AST) {
      result_var = left_AST->dumpIR(tempVarCounter);
    } else {
      // Left and right operands exist, generate code for logical AND (&&)
      std::string left_result = left_AST->dumpIR(tempVarCounter);

      // Generate unique labels for control flow
      std::string then_label = "%then__" + std::to_string(tempVarCounter);
      std::string else_label = "%else__" + std::to_string(tempVarCounter);
      std::string end_label = "%end__" + std::to_string(tempVarCounter++);
      std::string result_var_ptr = "%" + std::to_string(symbol_num++);

      // Allocate memory for the result of the logical AND
      std::cout << '\t' << result_var_ptr << " = alloc i32" << std::endl;

      // Perform branching based on the result of the left operand
      std::cout << "\tbr " << left_result << ", " << then_label << ", " << else_label << std::endl;

      // Then block: evaluate the right operand if left is true
      std::cout << then_label << ":" << std::endl;
      std::string right_result = right_AST->dumpIR(tempVarCounter);
      std::string tmp_result_var = "%" + std::to_string(symbol_num++);
      std::cout << '\t' << tmp_result_var << " = ne " << right_result << ", 0" << std::endl;

      // Store the result of right operand evaluation
      std::cout << "\tstore " << tmp_result_var << ", " << result_var_ptr << std::endl;
      std::cout << "\tjump " << end_label << std::endl;

      // Else block: if left is false, set the result to false (0)
      std::cout << else_label << ":" << std::endl;
      std::cout << "\tstore 0, " << result_var_ptr << std::endl;
      std::cout << "\tjump " << end_label << std::endl;

      // End label: load the final result
      std::cout << end_label << ":" << std::endl;
      result_var = "%" + std::to_string(symbol_num++);
      std::cout << '\t' << result_var << " = load " << result_var_ptr << std::endl;
    }
    return result_var;
  }
};

// LOrExpAST 处理 || *still have some problem
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

  std::string dumpIR(int& tempVarCounter) const override {
    std::string result_var = "";

    if (!right_AST) {
      // If there's no right operand, just dump the IR for the left operand
      result_var = left_AST->dumpIR(tempVarCounter);
    } else {
      // Generate IR for logical OR (||), with both left and right operands

      // First, get the IR for the left operand
      std::string left_result = left_AST->dumpIR(tempVarCounter);

      // Generate unique labels for control flow
      std::string then_label = "%then__" + std::to_string(tempVarCounter);
      std::string else_label = "%else__" + std::to_string(tempVarCounter);
      std::string end_label = "%end__" + std::to_string(tempVarCounter++);
      std::string result_var_ptr = "%" + std::to_string(symbol_num++);

      // Allocate memory for storing the result of the logical OR
      std::cout << '\t' << result_var_ptr << " = alloc i32" << std::endl;

      // Conditional branching based on the result of the left operand
      std::cout << "\tbr " << left_result << ", " << then_label << ", " << else_label << std::endl;

      // Then block: if the left operand is non-zero (true), store 1
      std::cout << then_label << ":" << std::endl;
      std::cout << "\tstore 1, " << result_var_ptr << std::endl;
      std::cout << "\tjump " << end_label << std::endl;

      // Else block: if the left operand is zero (false), evaluate the right operand
      std::cout << else_label << ":" << std::endl;
      std::string tmp_result_var = "%" + std::to_string(symbol_num++);
      std::string right_result = right_AST->dumpIR(tempVarCounter);
      std::cout << '\t' << tmp_result_var << " = ne " << right_result << ", 0" << std::endl;

      // Store the result of the right operand evaluation (1 if true, 0 if false)
      std::cout << "\tstore " << tmp_result_var << ", " << result_var_ptr << std::endl;
      std::cout << "\tjump " << end_label << std::endl;

      // End block: load the final result (either 1 or 0) into the result variable
      std::cout << end_label << ":" << std::endl;
      result_var = "%" + std::to_string(symbol_num++);
      std::cout << '\t' << result_var << " = load " << result_var_ptr << std::endl;
    }
    return result_var;
  }
};

#endif