#ifndef AST_H
#define AST_H

#include <memory>
#include <string>
#include <iostream>
#include <sstream>
#include <cassert>
#include <vector>
#include <map>
#include "mySymboltable.h"

static int if_num = 0;
static int while_num = 0;
static std::map<std::string, std::string> chk;
static std::map<std::string, int> var_num;
static Scope scopeManager;
static std::vector<int> while_stack;

// Auxiliary function: Print indentation
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
  Break,  // break
  Continue, // continue
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

// All basis AST
class BaseAST {
public:
  virtual ~BaseAST() = default;
  virtual void Dump(int level = 0) const = 0;
  virtual std::string dumpIR(int& tempVarCounter) const = 0;  // Modify to IR method with temporary variable counter
  virtual int Calc() const { assert(false); return -1; }
};

class CompUnitAST : public BaseAST {
public:
  std::unique_ptr<BaseAST> func_def;

  CompUnitAST(std::unique_ptr<BaseAST> func_def) 
      : func_def(std::move(func_def)) {}

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

  FuncDefAST(std::unique_ptr<BaseAST> func_type, std::string ident, std::unique_ptr<BaseAST> block)
      : func_type(std::move(func_type)), ident(ident), block(std::move(block)) {}

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
    // Output the IR code defined by the function
    std::cout << "fun @" << ident << "()";
    if (func_type->dumpIR(tempVarCounter) == "int") {
      std::cout << ": i32 ";
    }
    std::cout << "{\n";
    std::cout << "%entry:\n";
    // Obtain the IR expression of the block
    std::string block_ir = block->dumpIR(tempVarCounter); 
    if (block_ir != "ret") {
      std::cout << "  ret 0\n";  // Default return 0
    }
    std::cout << "}\n";
    return "";
  }
};

class FuncTypeAST : public BaseAST {
public:
  std::string type;

  FuncTypeAST(std::string type) : type(type) {}

  void Dump(int level = 0) const override {
    indent(level);
    std::cout << "FuncType: " << type << "\n";
  }

  std::string dumpIR(int& tempVarCounter) const override {
    return type;  // Return type information, such as' int 'or' void '
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

    std::string dumpIR(int& tempVarCounter) const override {
        std::string last_result;
        mySymboltable newtbl;
        scopeManager.insertScope(newtbl);
        for (const auto& item : items) {
            last_result = item->dumpIR(tempVarCounter);
            if(last_result == "ret" || last_result == "break" || last_result == "cont") break;
        }
        scopeManager.exitScope();
        return last_result;
    }

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
        // obatain the value of variable
        auto varpit = scopeManager.lookupSymbol(ident);
        std::string var_type= varpit.value() -> type;
        std::string var_nam= varpit.value() -> KoopalR;
        if (var_type == "int"){
        //  std::cout<< chk[ident] << " " << ident << std::endl;
          std::string var_ptr = "@" + ident;  // address of variable
//          std::string var_nam=var_ptr + "_" + std::to_string(var_num[var_ptr]++);
          std::string temp_var = "%" + std::to_string(tempVarCounter++);
          std::cout << "  " << temp_var << " = load " << var_nam << "\n";
          return temp_var;
        }
        return var_nam;
    }
};

class StmtAST : public BaseAST {
public:
    StmtType type;
    Option<std::unique_ptr<BaseAST>> exp;
    Option<std::string> lval;
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
    static BaseAST* makeAssign(std::string* lval, BaseAST* exp) {
        auto stmt = new StmtAST(StmtType::Assign);
        stmt->lval = Option<std::string>(*lval);
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

    //Constructor for break
    static BaseAST* makeBreak() {
        return new StmtAST(StmtType::Break);
    }

    // Constructor for continue
    static BaseAST* makeContinue() {
        return new StmtAST(StmtType::Continue);
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
                    indent(level + 2);
                    std::cout << "ident: " << lval.getValue() << "\n";
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
            
            case StmtType::Break:
                std::cout << "break\n";
                break;
                
            case StmtType::Continue:
                std::cout << "continue\n";
                break;
        }
        
        indent(level);
        std::cout << "}\n";
    }

    std::string dumpIR(int& tempVarCounter) const override {
        switch (type) {
            case StmtType::Return: {
                if (exp.hasValue()) {
                    // Generate the IR of the expression and obtain the result
                    std::string exp_result = exp.getValue()->dumpIR(tempVarCounter);
                    std::cout << "  ret " << exp_result << "\n";
                } else {
                    // handle empty return
                    std::cout << "  ret 0\n";
                }
                return "ret";
            }

            case StmtType::Assign: {
                if (lval.hasValue() && exp.hasValue()) {
                    std::string exp_result = exp.getValue()->dumpIR(tempVarCounter);
                    std::string var_ptr = "@" + lval.getValue();

                    auto varpit = scopeManager.lookupSymbol(lval.getValue());
                    std::string var_nam= varpit.value() -> KoopalR;
                    std::cout << "  store " << exp_result << ", " << var_nam << "\n";
                }
                return "";
            }

            case StmtType::Exp: {
                if (exp.hasValue()) {
                    // Just need to generate the IR of the expression, no need to store the result
                    exp.getValue()->dumpIR(tempVarCounter);
                }
                return "";
            }

            case StmtType::Block: {
                if (block.hasValue()) {
                    // Recursive generation of IR for all statements in the block
                    return block.getValue()->dumpIR(tempVarCounter);
                }
                return "";
            }

            case StmtType::Break: {
                // Jump to the end tag of the current loop
                int while_nb=while_stack.back();
                std::cout << "  jump %while_end_" << while_nb - 1 << "\n";
                return "break";
            }

            case StmtType::Continue: {
                // Jump to the conditional judgment label of the current loop
                int while_nb=while_stack.back();
                std::cout << "  jump %while_entry_" << while_nb - 1 << "\n";
                return "cont";
            }
            
            default:
                assert(false && "Unknown statement type");
                return "";
        }
    }
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

    std::string dumpIR(int& tempVarCounter) const override {
        // Generate code for conditional judgment
        std::string cond_result = cond->dumpIR(tempVarCounter);
        
        // create the sign
        std::string then_label = "%then_" + std::to_string(if_num);
        std::string else_label = "%else_" + std::to_string(if_num);
        std::string end_label = "%end_" + std::to_string(if_num++);

        // check whether having "else"
        std::cout << "  br " << cond_result << ", " << then_label << ", ";
        if (else_stmt.hasValue()) {
            std::cout << else_label << "\n";
        } else {
            std::cout << end_label << "\n";
        }

        // then branches
        std::cout << then_label << ":\n";
        std::string not_if = then_stmt->dumpIR(tempVarCounter);
        if (not_if != "ret" && not_if != "break" && not_if != "cont") {
          std::cout << "  jump " << end_label << "\n";
        }
        std::string not_else = "";
        // else branches(if exits)
        if (else_stmt.hasValue()) {
            std::cout << else_label << ":\n";
            not_else = else_stmt.getValue()->dumpIR(tempVarCounter);
            if (not_else != "ret" && not_else != "break" &&
                not_else != "cont")
                std::cout << "\tjump " << end_label << std::endl;
            if((not_if == "ret" || not_if == "break" || not_if == "cont" ) && 
              (not_else == "ret" || not_else == "break" || not_else == "cont")) return "ret";
        }
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

    std::string dumpIR(int& tempVarCounter) const override {
        // Generate unique labels for the loop
        std::string entry_label = "%while_entry_" + std::to_string(while_num);
        std::string body_label = "%while_body_" + std::to_string(while_num);
        std::string end_label = "%while_end_" + std::to_string(while_num++);
        while_stack.push_back(while_num);
        // Jump to entry block
        std::cout << "  jump " << entry_label << "\n";
        
        // Entry block: evaluate condition
        std::cout << entry_label << ":\n";
        std::string cond_result = cond->dumpIR(tempVarCounter);
        std::cout << "  br " << cond_result << ", " << body_label << ", " << end_label << "\n";
        
        // Body block: execute loop body
        std::cout << body_label << ":\n";
        std::string not_ret = body->dumpIR(tempVarCounter);
        if (not_ret != "ret" && not_ret != "break" && not_ret != "cont")
            std::cout << "  jump " << entry_label << "\n";
        
        // End block
        std::cout << end_label << ":\n";
        while_stack.pop_back();
        return "";
    }
};

class ExpAST : public BaseAST {
public:
    std::unique_ptr<BaseAST> l_or_exp;

    ExpAST(std::unique_ptr<BaseAST> l_or_exp): l_or_exp(std::move(l_or_exp)) {}

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
    virtual int Calc() const override
    {
//        std::cout<<"here";
        return l_or_exp->Calc();
    }
};

class PrimaryExpAST : public BaseAST {
 public:
  PrimaryExpType type;
  std::unique_ptr<BaseAST> exp;
  int number;
  std::string LVal;

  PrimaryExpAST(int val) : type(PrimaryExpType::number), number(val), exp(nullptr), LVal("") {}
  PrimaryExpAST(std::unique_ptr<BaseAST> e)
    : type(PrimaryExpType::exp), number(0), exp(std::move(e)) {}
  PrimaryExpAST(std::string* l, bool isLVal) 
    : type(PrimaryExpType::LVal), LVal(*l), number(0), exp(nullptr) {}

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
        indent(level + 2);
        std::cout << "ident: " << LVal << "\n";
        indent(level + 1);
        std::cout << "}\n";
        break;
    }
    indent(level);
    std::cout << "}\n";
  }

  std::string dumpIR(int& tempVarCounter) const override {
    if (type == PrimaryExpType::number) {
      return std::to_string(number);
    } else if (type == PrimaryExpType::exp) {
      return exp->dumpIR(tempVarCounter);
    } else if (type == PrimaryExpType::LVal) {
      auto varpit = scopeManager.lookupSymbol(LVal);
      std::string var_type= varpit.value() -> type;
      std::string var_nam= varpit.value() -> KoopalR;
      if (var_type == "int"){
        //    std::cout<< chk[LVal] << " " << LVal << std::endl;
            std::string var_ptr = "@" + LVal;  // variable's address
  //          std::string var_nam=var_ptr + "_" + std::to_string(var_num[var_ptr]++);
            std::string temp_var = "%" + std::to_string(tempVarCounter++);
            std::cout << "  " << temp_var << " = load " << var_nam << "\n";
            return temp_var;
      }
      return var_nam;
    }
    return "";
  }

  virtual int Calc() const override{
    if (type == PrimaryExpType::number) {
      return number;
    } else if (type == PrimaryExpType::exp) {
      return exp->Calc();
    } else if (type == PrimaryExpType::LVal) {
      auto varpit = scopeManager.lookupSymbol(LVal);
      std::string var_type= varpit.value() -> type;
      std::string var_nam= varpit.value() -> value;
      if (var_type == "int"){
          return std::stoi(var_nam);
      }
      return std::stoi(var_nam);
    }
    assert(false);
  }
};

// UnaryExp handel +, -, !
class UnaryExpAST : public BaseAST {
 public:
  std::string op;
  std::unique_ptr<BaseAST> exp;

  UnaryExpAST(std::string op, std::unique_ptr<BaseAST> exp)
    : op(op), exp(std::move(exp)) {}

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

  virtual int Calc() const override{
    int result = exp->Calc();
    if (op == "-") result = -result;
    if (op == "+") result = result;
    if (op == "!") result = !result;
    return result;
  }
};

// AddExp handel +, -
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

  virtual int Calc() const override{
    int result = 1;
    if (!right_AST) result = left_AST->Calc();
    else{
      int left_result = left_AST->Calc();
      int right_result = right_AST->Calc();
      if (op == "+") result = left_result + right_result;
      if (op == "-") result = left_result - right_result;
    }
    return result;
  }
};

// MulExp handle *, /, %
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

  virtual int Calc() const override{
    int result = 1;
    if (!right_AST) result = left_AST->Calc();
    else{
      int left_result = left_AST->Calc();
      int right_result = right_AST->Calc();
      if (op == "*") result = left_result * right_result;
      if (op == "/") result = left_result / right_result;
      if (op == "%") result = left_result % right_result;
    }
    return result;
  }
};

// RelExpAST handle <, >, <=, >=
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

  virtual int Calc() const override{
    int result = 1;
    if (!right_AST) result = left_AST->Calc();
    else{
      int left_result = left_AST->Calc();
      int right_result = right_AST->Calc();
      if (op == ">") result = left_result > right_result;
      if (op == ">=") result = left_result >= right_result;
      if (op == "<") result = left_result < right_result;
      if (op == "<=") result = left_result <= right_result;
    }
    return result;
  }
};

// EqExpAST handle ==, !=
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

  virtual int Calc() const override{
    int result = 1;
    if (!right_AST) result = left_AST->Calc();
    else{
      int left_result = left_AST->Calc();
      int right_result = right_AST->Calc();
      if (op == "==") result = left_result == right_result;
      if (op == "!=") result = left_result != right_result;
    }
    return result;
  }
};

// LAndExpAST handle &&
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
      std::string then_label = "%then__" + std::to_string(if_num);
      std::string else_label = "%else__" + std::to_string(if_num);
      std::string end_label = "%end__" + std::to_string(if_num++);
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
  virtual int Calc() const override{
    int result = 1;
    if (!right_AST) result = left_AST->Calc();
    else{
      int left_result = left_AST->Calc();
      if (left_result == 0) return 0;
      result = right_AST->Calc() != 0;
    }
    return result;
  }
};

// LOrExpAST handle ||
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
      std::string then_label = "%then__" + std::to_string(if_num);
      std::string else_label = "%else__" + std::to_string(if_num);
      std::string end_label = "%end__" + std::to_string(if_num++);
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

  virtual int Calc() const override{
    int result = 1;
    if (!right_AST) result = left_AST->Calc();
    else{
      int left_result = left_AST->Calc();
      if (left_result)return 1;
      result = right_AST->Calc() != 0;
    }
    return result;
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
        mySymboltable* topscope = scopeManager.top();
        topscope -> insertSymbol(ident, "const", "1", init_val_ir);
        //chk[ident] = init_val_ir;
        return init_val_ir;
    }

    virtual int Calc() const override{
      int init_val_ir = init_val->Calc();
      return 0;
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

    std::string dumpIR(int& tempVarCounter) const override {
        std::string var_ptr = "@" + ident;
        std::string var_nam = var_ptr + "_" + std::to_string(var_num[var_ptr]++);
        std::cout << "  " << var_nam << " = alloc i32\n";
        mySymboltable* topscope = scopeManager.top();
        topscope -> insertSymbol(ident, "int", "1", var_nam);
        if (has_init) {
            std::string init_val_ir = init_val->dumpIR(tempVarCounter);
            std::cout << "  store " << init_val_ir << ", " << var_nam << "\n";
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


    std::string dumpIR(int& tempVarCounter) const override {
        for (const auto& def : var_defs) {
            def->dumpIR(tempVarCounter);
        }
        return "";
    }

    virtual int Calc() const override{
        for (const auto& def : var_defs) {
            def->Calc();
        }
        return 0;
    }
};

class PutintAST : public BaseAST {
public:
    std::unique_ptr<BaseAST> exp;  // 要打印的表达式

    // Constructor
    PutintAST(BaseAST* exp) : exp(std::unique_ptr<BaseAST>(exp)) {}

    void Dump(int level = 0) const override {
        indent(level);
        std::cout << "Putint {\n";
        exp->Dump(level + 1);
        indent(level);
        std::cout << "}\n";
    }

    std::string dumpIR(int& tempVarCounter) const override {
        // 先计算表达式的值
        std::string exp_result = exp->dumpIR(tempVarCounter);
        
        // 生成 putint 调用
        std::cout << "  call @putint(" << exp_result << ")\n";
        
        // putint的返回值（如果需要的话）
        std::string result = "%" + std::to_string(tempVarCounter++);
        std::cout << "  " << result << " = ret\n";
        return result;
    }
};

#endif