#ifndef AST_H
#define AST_H

#include <memory>
#include <string>
#include <iostream>
#include <sstream>
#include <cassert>
#include <vector>

static int symbol_num = 0;

// 辅助函数：打印缩进
inline void indent(int level) {
  for (int i = 0; i < level; ++i) {
    std::cout << "  ";
  }
}

enum class PrimaryExpType {
  exp, //Expression : 1 + 2 * 3
  LVal, // Reference : int a = 1; a <---
  number  // Number : 4
};

enum class StmtType {
  Return, // return x
  Assign, // a = 1
  Exp,  // 1 + 2
  Block,  // { xxxxxxx }
};

// Define Option template class
template<typename T>
class Option {
private:
    bool has_value;
    T value;

public:
    Option() : has_value(false) {}
    Option(T val) : has_value(true), value(std::move(val)) {}

    bool hasValue() const { return has_value; }
    const T& getValue() const { 
        assert(has_value);
        return value;
    }
    T&& takeValue() && {
        assert(has_value);
        has_value = false;  // value is gone
        return std::move(value);
    }
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
    std::vector<std::unique_ptr<BaseAST>> items;

    void Dump(int level = 0) const override {
        indent(level);
        std::cout << "Block {\n";
        for (const auto& item : items) {
            item->Dump(level + 1);
        }
        indent(level);
        std::cout << "}\n";
    }

    //Claude写的DumpIR
    std::string dumpIR(int& tempVarCounter) const override {
        std::string last_result;
        for (const auto& item : items) {
            last_result = item->dumpIR(tempVarCounter);
        }
        return last_result;
    }

    //之前的DumpIR
    // std::string dumpIR(int& tempVarCounter) const override {
    // return stmt->dumpIR(tempVarCounter);  // 返回语句的 IR 表达
    // }
};

// Variable Reference AST Node : int a = 1
//                               return a <--- 
class LValAST : public BaseAST {
public:
    std::string ident;  // variable name 

    // Constructor 
    LValAST(std::string name) : ident(name) {}

    void Dump(int level = 0) const override {
        indent(level);
        std::cout << "LValAST {\n";
        indent(level + 1);
        std::cout << "ident: " << ident << "\n";
        indent(level);
        std::cout << "}\n";
    }

    std::string dumpIR(int& tempVarCounter) const override {
        // 获取变量的值
        std::string var_ptr = "@" + ident;  // 变量的地址
        std::string temp_var = "%" + std::to_string(tempVarCounter++);
        std::cout << "  " << temp_var << " = load " << var_ptr << "\n";
        return temp_var;
    }
};

class StmtAST : public BaseAST {
public:
    StmtType type;
    Option<std::unique_ptr<BaseAST>> exp;
    Option<std::unique_ptr<BaseAST>> lval;
    Option<std::unique_ptr<BlockAST>> block;

    // StmtAST can only be constructed by makeXXX
    explicit StmtAST(StmtType type) : type(type) {}

    //Constructor for return
    static BaseAST* makeReturn(BaseAST* exp = nullptr) {
        auto stmt = new StmtAST(StmtType::Return);
        if (exp) stmt->exp = Option(std::unique_ptr<BaseAST>(exp));
        return stmt;
    }

    //Constructor for assignment
    static BaseAST* makeAssign(BaseAST* lval, BaseAST* exp) {
        auto stmt = new StmtAST(StmtType::Assign);
        stmt->lval = Option(std::unique_ptr<BaseAST>(lval));
        stmt->exp = Option(std::unique_ptr<BaseAST>(exp));
        return stmt;
    }

    //Constructor for expression
    static BaseAST* makeExpression(BaseAST* exp = nullptr) {
        auto stmt = new StmtAST(StmtType::Exp);
        if (exp) stmt->exp = Option(std::unique_ptr<BaseAST>(exp));
        return stmt;
    }

    //Constructor for block
    static BaseAST* makeBlock(BaseAST* block) {
        auto stmt = new StmtAST(StmtType::Block);
        auto block_ast = dynamic_cast<BlockAST*>(block);
        stmt->block = Option(std::unique_ptr<BlockAST>(block_ast));
        return stmt;
    }

    void Dump(int level = 0) const override {
        indent(level);
        std::cout << "Stmt {\n";
        indent(level + 1);
        std::cout << "type: ";
    
        switch (type) {
            case StmtType::Return:
                std::cout << "return\n";
                if (exp.hasValue()) {
                    indent(level + 1);
                    std::cout << "exp: {\n";
                    exp.getValue()->Dump(level + 2);
                    indent(level + 1);
                    std::cout << "}\n";
                }
                break;
                
            case StmtType::Assign:
                std::cout << "assign\n";
                if (lval.hasValue()) {
                    indent(level + 1);
                    std::cout << "lval: {\n";
                    lval.getValue()->Dump(level + 2);
                    indent(level + 1);
                    std::cout << "}\n";
                }
                if (exp.hasValue()) {
                    indent(level + 1);
                    std::cout << "exp: {\n";
                    exp.getValue()->Dump(level + 2);
                    indent(level + 1);
                    std::cout << "}\n";
                }
                break;
                
            case StmtType::Exp:
                std::cout << "expression\n";
                if (exp.hasValue()) {
                    indent(level + 1);
                    std::cout << "exp: {\n";
                    exp.getValue()->Dump(level + 2);
                    indent(level + 1);
                    std::cout << "}\n";
                }
                break;
                
            case StmtType::Block:
                std::cout << "block\n";
                if (block.hasValue()) {
                    block.getValue()->Dump(level + 1);
                }
                break;
        }
        
        indent(level);
        std::cout << "}\n";
    }

    // Claude写的DumpIR
    std::string dumpIR(int& tempVarCounter) const override {
        switch (type) {
            case StmtType::Return: {
                if (exp.hasValue()) {
                    // 生成表达式的IR并获取结果
                    std::string exp_result = exp.getValue()->dumpIR(tempVarCounter);
                    std::cout << "  ret " << exp_result << "\n";
                } else {
                    // 处理空return
                    std::cout << "  ret 0\n";
                }
                return "ret";
            }

            case StmtType::Assign: {
                if (lval.hasValue() && exp.hasValue()) {
                    // 先计算右侧表达式
                    std::string exp_result = exp.getValue()->dumpIR(tempVarCounter);
                    
                    // 获取左值的变量名（假设是LValAST类型）
                    auto lval_ast = dynamic_cast<const LValAST*>(lval.getValue().get());
                    if (lval_ast) {
                        std::string var_ptr = "@" + lval_ast->ident;
                        // 生成store指令
                        std::cout << "  store " << exp_result << ", " << var_ptr << "\n";
                    }
                }
                return "";
            }

            case StmtType::Exp: {
                if (exp.hasValue()) {
                    // 只需要生成表达式的IR，不需要存储结果
                    exp.getValue()->dumpIR(tempVarCounter);
                }
                return "";
            }

            case StmtType::Block: {
                if (block.hasValue()) {
                    // 递归生成块中所有语句的IR
                    return block.getValue()->dumpIR(tempVarCounter);
                }
                return "";
            }

            default:
                assert(false && "Unknown statement type");
                return "";
        }
    }

    //之前的DumpIR
    // std::string dumpIR(int& tempVarCounter) const override {
    //   if (type == StmtType::Return) {
    //    //      std::cout<<"here"<<"\n";
    //      std::string IRR=exp->dumpIR(tempVarCounter);
    //      std::cout <<"  " << "ret " << IRR << "\n";  // 生成返回语句的 IR
    //      return "ret";
    //     }
    //    return "";
    // }
};

// IfStmt for representing if-else
class IfStmtAST : public BaseAST {
public:
    std::unique_ptr<BaseAST> cond;    // condition
    std::unique_ptr<BaseAST> then_stmt; // if branch
    Option<std::unique_ptr<BaseAST>> else_stmt; // else branch (option)

    // Constructor for if without else
    IfStmtAST(BaseAST* cond, BaseAST* then_stmt) 
        : cond(std::unique_ptr<BaseAST>(cond)), 
          then_stmt(std::unique_ptr<BaseAST>(then_stmt)) {}

    // Constructor for if-else
    IfStmtAST(BaseAST* cond, BaseAST* then_stmt, BaseAST* else_stmt)
        : cond(std::unique_ptr<BaseAST>(cond)), 
          then_stmt(std::unique_ptr<BaseAST>(then_stmt)),
          else_stmt(Option(std::unique_ptr<BaseAST>(else_stmt))) {}

    void Dump(int level = 0) const override {
        indent(level);
        std::cout << "IfStmt {\n";
        
        indent(level + 1);
        std::cout << "cond: {\n";
        cond->Dump(level + 2);
        indent(level + 1);
        std::cout << "}\n";
        
        indent(level + 1);
        std::cout << "if branch: {\n";
        then_stmt->Dump(level + 2);
        indent(level + 1);
        std::cout << "}\n";

        if (else_stmt.hasValue()) {
            indent(level + 1);
            std::cout << "else branch: {\n";
            else_stmt.getValue()->Dump(level + 2);
            indent(level + 1);
            std::cout << "}\n";
        }
        
        indent(level);
        std::cout << "}\n";
    }

    //Claude's DumpIR
    std::string dumpIR(int& tempVarCounter) const override {
        // 生成条件判断的代码
        std::string cond_result = cond->dumpIR(tempVarCounter);
        
        // 生成唯一的标签
        std::string then_label = "%then_" + std::to_string(symbol_num);
        std::string else_label = "%else_" + std::to_string(symbol_num);
        std::string end_label = "%end_" + std::to_string(symbol_num++);

        // 条件跳转
        std::cout << "  br " << cond_result << ", " << then_label << ", ";
        if (else_stmt.hasValue()) {
            std::cout << else_label << "\n";
        } else {
            std::cout << end_label << "\n";
        }

        // then分支
        std::cout << then_label << ":\n";
        then_stmt->dumpIR(tempVarCounter);
        std::cout << "  jump " << end_label << "\n";

        // else分支(如果存在)
        if (else_stmt.hasValue()) {
            std::cout << else_label << ":\n";
            else_stmt.getValue()->dumpIR(tempVarCounter);
            std::cout << "  jump " << end_label << "\n";
        }

        // 结束标签
        std::cout << end_label << ":\n";
        
        return "";
    }
};

// WhileStmt for representing while loop
class WhileStmtAST : public BaseAST {
public:
    std::unique_ptr<BaseAST> cond;     // condition
    std::unique_ptr<BaseAST> body;     // loop body

    // Constructor
    WhileStmtAST(BaseAST* condition, BaseAST* loop_body) 
        : cond(std::unique_ptr<BaseAST>(condition)), 
          body(std::unique_ptr<BaseAST>(loop_body)) {}

    void Dump(int level = 0) const override {
        indent(level);
        std::cout << "WhileStmt {\n";
        
        indent(level + 1);
        std::cout << "condition: {\n";
        cond->Dump(level + 2);
        indent(level + 1);
        std::cout << "}\n";
        
        indent(level + 1);
        std::cout << "body: {\n";
        body->Dump(level + 2);
        indent(level + 1);
        std::cout << "}\n";
        
        indent(level);
        std::cout << "}\n";
    }

    //Claude's DumpIR
    std::string dumpIR(int& tempVarCounter) const override {
        // Generate unique labels for the loop
        std::string entry_label = "%while_entry_" + std::to_string(symbol_num);
        std::string body_label = "%while_body_" + std::to_string(symbol_num);
        std::string end_label = "%while_end_" + std::to_string(symbol_num++);

        // Jump to entry block
        std::cout << "  jump " << entry_label << "\n";
        
        // Entry block: evaluate condition
        std::cout << entry_label << ":\n";
        std::string cond_result = cond->dumpIR(tempVarCounter);
        std::cout << "  br " << cond_result << ", " << body_label << ", " << end_label << "\n";
        
        // Body block: execute loop body
        std::cout << body_label << ":\n";
        body->dumpIR(tempVarCounter);
        std::cout << "  jump " << entry_label << "\n";
        
        // End block
        std::cout << end_label << ":\n";
        
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
  std::unique_ptr<BaseAST> LVal;

  PrimaryExpAST(int val) : type(PrimaryExpType::number), number(val), exp(nullptr) {}
  PrimaryExpAST(std::unique_ptr<BaseAST> e)
    : type(PrimaryExpType::exp), number(0), exp(std::move(e)) {}
  PrimaryExpAST(std::unique_ptr<BaseAST> l, bool isLVal) 
    : type(PrimaryExpType::LVal), LVal(std::move(l)), number(0), exp(nullptr) {}

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
      case PrimaryExpType::LVal:
        std::cout << "LVal: {\n";
        LVal->Dump(level + 2);
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
    std::string left_result = left_AST->dumpIR(tempVarCounter);
    if (right_AST) {
      std::string right_result = right_AST->dumpIR(tempVarCounter);
//      std::string right_result = left_AST->dumpIR(tempVarCounter);
      std::string tempVar="%" + std::to_string(tempVarCounter++);
      if (op == "<"){
        std::cout << "  " << tempVar << " = lt " << left_result << ", " << right_result << "\n";
      }
      else if (op == ">"){
        std::cout << "  " << tempVar << " = gt " << left_result << ", " << right_result << "\n";
      }
      else if (op=="<="){
        std::cout << "  " << tempVar << " = le " << left_result << ", " << right_result << "\n";
      }
      else if (op==">="){
        std::cout << "  " << tempVar << " = ge " << left_result << ", " << right_result << "\n";
      }
      else assert(false);
      return tempVar;
    }
    return left_result;
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
    std::string left_result = left_AST->dumpIR(tempVarCounter);
    if (right_AST){
      std::string right_result = right_AST->dumpIR(tempVarCounter);
      std::string tempVar= "%" + std::to_string(tempVarCounter++);
      if (op == "=="){
        std::cout << "  " << tempVar << " = eq " << left_result << " , " << right_result << "\n";
      }
      else if (op == "!="){
        std::cout << "  " << tempVar << " = ne " << left_result << " , " << right_result << "\n";
      }
      else assert(false);
      return tempVar;
    }
    return left_result;
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
    if (!right_AST) {
      result_var = left_AST->dumpIR(tempVarCounter);
    } else {
      // Left and right operands exist, generate code for logical AND (&&)
      std::string left_result = left_AST->dumpIR(tempVarCounter);
      // Generate unique labels for control flow
      std::string then_label = "%then__" + std::to_string(symbol_num);
      std::string else_label = "%else__" + std::to_string(symbol_num);
      std::string end_label = "%end__" + std::to_string(symbol_num++);
      std::string result_var_ptr = "%" + std::to_string(tempVarCounter++);
      // Allocate memory for the result of the logical AND
      std::cout << "  " << result_var_ptr << " = alloc i32" << std::endl;

      // Perform branching based on the result of the left operand
      std::cout << "  br " << left_result << ", " << then_label << ", " << else_label << std::endl;

      // Then block: evaluate the right operand if left is true
      std::cout << then_label << ":" << std::endl;
      std::string right_result = right_AST->dumpIR(tempVarCounter);
      std::string tmp_result_var = "%" + std::to_string(tempVarCounter++);
      std::cout << "  " << tmp_result_var << " = ne " << right_result << ", 0" << std::endl;

      // Store the result of right operand evaluation
      std::cout << "  store " << tmp_result_var << ", " << result_var_ptr << std::endl;
      std::cout << "  jump " << end_label << std::endl;

      // Else block: if left is false, set the result to false (0)
      std::cout << else_label << ":" << std::endl;
      std::cout << "  store 0, " << result_var_ptr << std::endl;
      std::cout << "  jump " << end_label << std::endl;

      // End label: load the final result
      std::cout << end_label << ":" << std::endl;
      result_var = "%" + std::to_string(tempVarCounter++);
      std::cout << "  " << result_var << " = load " << result_var_ptr << std::endl;
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
      std::string then_label = "%then__" + std::to_string(symbol_num);
      std::string else_label = "%else__" + std::to_string(symbol_num);
      std::string end_label = "%end__" + std::to_string(symbol_num++);
      std::string result_var_ptr = "%" + std::to_string(tempVarCounter++);

      // Allocate memory for storing the result of the logical OR
      std::cout << "  " << result_var_ptr << " = alloc i32" << std::endl;

      // Conditional branching based on the result of the left operand
      std::cout << "  br " << left_result << ", " << then_label << ", " << else_label << std::endl;

      // Then block: if the left operand is non-zero (true), store 1
      std::cout << then_label << ":" << std::endl;
      std::cout << "  store 1, " << result_var_ptr << std::endl;
      std::cout << "  jump " << end_label << std::endl;

      // Else block: if the left operand is zero (false), evaluate the right operand
      std::cout << else_label << ":" << std::endl;
      std::string tmp_result_var = "%" + std::to_string(tempVarCounter++);
      std::string right_result = right_AST->dumpIR(tempVarCounter);
      std::cout << "  " << tmp_result_var << " = ne " << right_result << ", 0" << std::endl;

      // Store the result of the right operand evaluation (1 if true, 0 if false)
      std::cout << "  store " << tmp_result_var << ", " << result_var_ptr << std::endl;
      std::cout << "  jump " << end_label << std::endl;

      // End block: load the final result (either 1 or 0) into the result variable
      std::cout << end_label << ":" << std::endl;
      result_var = "%" + std::to_string(tempVarCounter++);
      std::cout << "  " << result_var << " = load " << result_var_ptr << std::endl;
    }
    return result_var;
  }
};

// Single constant definition: x = 1
class ConstDefAST : public BaseAST {
public:
    std::string op = "=";  // oprator
    std::string ident;  // name
    std::unique_ptr<BaseAST> init_val;  // initial value 

    // Constructor
    ConstDefAST(std::string op, std::string ident, std::unique_ptr<BaseAST> init) 
        : op(op), ident(ident), init_val(std::move(init)) {}

    void Dump(int level = 0) const override {
        indent(level);
        std::cout << "ConstDef {\n";
        indent(level + 1);
        std::cout << "ident: " << ident << "\n";
        indent(level + 1);
        std::cout << "init_val: {\n";
        init_val->Dump(level + 2);
        indent(level + 1);
        std::cout << "}\n";
        indent(level);
        std::cout << "}\n";
    }

    std::string dumpIR(int& tempVarCounter) const override {
        std::string init_val_ir = init_val->dumpIR(tempVarCounter);
        // 为常量分配全局变量名
        std::string constName = "@" + ident;
        std::cout << "global " << constName << " = alloc i32, " << init_val_ir << "\n";
        return constName;
    }
};

// Whole sentence for declearing constants: const int x = 1, y = 2;
class ConstDeclAST : public BaseAST {
public:
    std::string btype;                                  // Type(int) 
    std::vector<std::unique_ptr<ConstDefAST>> const_defs;  // Constant List

    // Constructor 
    ConstDeclAST(std::string btype, std::vector<std::unique_ptr<ConstDefAST>> defs)
        : btype(btype), const_defs(std::move(defs)) {}

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

    std::string dumpIR(int& tempVarCounter) const override {
        for (const auto& def : const_defs) {
            def->dumpIR(tempVarCounter);
        }
        return "";
    }
};

// Variable declaration: int x; int x = 1;
class VarDefAST : public BaseAST {
public:
    std::string op = "="; //operator
    std::string ident;  // Variable name
    std::unique_ptr<BaseAST> init_val;  // Initial value (optional)
    bool has_init;  // Whether has initial value

    // Constructor for declaration without initialization
    VarDefAST(std::string name) 
        : ident(name), init_val(nullptr), op(""), has_init(false) {}
    
    // Constructor for declaration with initialization
    VarDefAST(std::string op, std::string name, std::unique_ptr<BaseAST> init) 
        : op("="), ident(name), init_val(std::move(init)), has_init(true) {}

    void Dump(int level = 0) const override {
        indent(level);
        std::cout << "VarDef {\n";
        indent(level + 1);
        std::cout << "ident: " << ident << "\n";
        if (has_init) {
            indent(level + 1);
            std::cout << "init_val: {\n";
            init_val->Dump(level + 2);
            indent(level + 1);
            std::cout << "}\n";
        }
        indent(level);
        std::cout << "}\n";
    }

    //Claude's DumpIR
    std::string dumpIR(int& tempVarCounter) const override {
        std::string var_ptr = "@" + ident;
        std::cout << "  " << var_ptr << " = alloc i32\n";
        
        if (has_init) {
            std::string init_val_ir = init_val->dumpIR(tempVarCounter);
            std::cout << "  store " << init_val_ir << ", " << var_ptr << "\n";
        }
        
        return var_ptr;
    }
};

// Complete variable declaration: int x = 1, y = 2;
class VarDeclAST : public BaseAST {
public:
    std::string btype;  // Type (int)
    std::vector<std::unique_ptr<VarDefAST>> var_defs;  // Variable definitions

    VarDeclAST(std::string type, std::vector<std::unique_ptr<VarDefAST>> defs)
        : btype(type), var_defs(std::move(defs)) {}

    void Dump(int level = 0) const override {
        indent(level);
        std::cout << "VarDecl {\n";
        indent(level + 1);
        std::cout << "btype: " << btype << "\n";
        indent(level + 1);
        std::cout << "var_defs: [\n";
        for (const auto& def : var_defs) {
            def->Dump(level + 2);
        }
        indent(level + 1);
        std::cout << "]\n";
        indent(level);
        std::cout << "}\n";
    }

    //Claude's DumpIR
    std::string dumpIR(int& tempVarCounter) const override {
        for (const auto& def : var_defs) {
            def->dumpIR(tempVarCounter);
        }
        return "";
    }
};

#endif