#ifndef IR_H
#define IR_H

#include <memory>
#include <string>
#include <iostream>
#include <sstream>
#include <cassert>
#include <vector>
#include <map>
#include "Symboltable.h"

extern int fl;
static int fl_void;
static int if_num = 0;
static int while_num = 0;
static std::string IR = "";
static std::string glb_IR = "";
static std::map<std::string, std::string> chk;
static std::map<std::string, std::string> fun_type;
static std::map<std::string, int> var_num;
static std::vector<std::string> fun_var;
static std::vector<int> while_stack;
static std::vector<int> for_stack;
static std::vector<int> for_or_whi;
static std::vector<std::string> list_nam; 
static std::vector<int> list_length; 
static std::map<std::string, bool> fun_nam;
static std::map<std::string, std::string> bel;
static std::map<std::string, int> erary;
static std::map<std::string, int> ervar;
static Scope scopeManager;

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

enum class UnaryExpType {
    Unary_op,    // +, -, ! 
    Function,   // 
    Primary      // PrimaryExp
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
  virtual int Calc() const { 
    std::cout << glb_IR  <<IR;
    assert(false); return -1; }
};

class CompUnitAST : public BaseAST {
public:
    std::vector<std::unique_ptr<BaseAST>> decls;    // Store all declaraions
    std::vector<std::unique_ptr<BaseAST>> funcdefs; // Store all function definitions

    CompUnitAST() = default;
    
    void addDecl(BaseAST* decl) {
        decls.push_back(std::unique_ptr<BaseAST>(decl));
    }
    
    void addFuncDef(BaseAST* funcdef) {
        funcdefs.push_back(std::unique_ptr<BaseAST>(funcdef));
    }

    void Dump(int level = 0) const override {
        indent(level);
        std::cout << "CompUnit {\n";
        
        // Only print declarations when it is not empty
        if (!decls.empty()) {
            indent(level + 1);
            std::cout << "Declarations:\n";
            for (const auto& decl : decls) {
                decl->Dump(level + 2);
            }
        }
        
        // Only print function defs when it is not empty
        if (!funcdefs.empty()) {
            indent(level + 1);
            std::cout << "Functions:\n";
            for (const auto& func : funcdefs) {
                func->Dump(level + 2);
            }
        }
        
        indent(level);
        std::cout << "}\n";
    }

    std::string dumpIR(int& tempVarCounter) const override {
        glb_IR += "decl @getint(): i32\n";
        glb_IR += "decl @getch(): i32\n";
        glb_IR += "decl @getarray(*i32): i32\n";
        glb_IR += "decl @putint(i32)\n";
        glb_IR += "decl @putch(i32)\n";
        glb_IR += "decl @putarray(i32, *i32)\n";
        glb_IR += "decl @starttime()\n";
        glb_IR += "decl @stoptime()\n\n";
        fun_type["getint"] = "int";
        fun_type["getch"] = "int";
        fun_type["getarray"] = "int";
        fun_type["putint"] = "void";
        fun_type["putch"] = "void";
        fun_type["putarray"] = "void";
        fun_type["starttime"] = "void";
        fun_type["stoptime"] = "void";
        fun_type["puts"] = "void";
        fun_nam["puts"] = 1;
        fun_nam["getint"] = 1;
        fun_nam["getch"] = 1;
        fun_nam["getarray"] = 1;
        fun_nam["putint"] = 1;
        fun_nam["putch"] = 1;
        fun_nam["putarray"] = 1;
        fun_nam["starttime"] = 1;
        fun_nam["stoptime"] = 1;
//        Deal with declarations first
        if(!decls.empty()){
            mySymboltable newtbl;
            scopeManager.insertScope(newtbl);
        }
        for (const auto& decl : decls) {
          //  std::cout<<"qwq";
            decl->Calc();
        }
        // Deal with function defs
        for (const auto& func : funcdefs) {
            fl_void = 0;
            func->dumpIR(tempVarCounter);
        //    std::cout<<glb_IR+IR;
        }
        if (!fl) std::cout << glb_IR << IR;
        return "";
    }
};

// AST Node for parameter list
class FuncFParamAST : public BaseAST {
public:
    std::string btype;  // parameter type
    std::string ident;  // parameter name

    FuncFParamAST(std::string type, std::string name) 
        : btype(type), ident(name) {}

    void Dump(int level = 0) const override {
        indent(level);
        std::cout << "FuncFParam {\n";
        indent(level + 1);
        std::cout << "type: " << btype << "\n";
        indent(level + 1);
        std::cout << "ident: " << ident << "\n";
        indent(level);
        std::cout << "}\n";
    }

    std::string dumpIR(int& tempVarCounter) const override {
        std::string param_ptr = "@" + ident;
      //  std::string param_name = param_ptr + "_param";
      //  mySymboltable* topscope = scopeManager.top();
      //  topscope->insertSymbol(ident, btype, "2", param_ptr);
        fun_var.push_back(ident);
        return param_ptr;
    }
};

// Complete Function parameter list: (int x, int y)
class FuncFParamListAST : public BaseAST {
public:
    std::vector<std::unique_ptr<FuncFParamAST>> params;  // Parameter list

    FuncFParamListAST(std::vector<std::unique_ptr<FuncFParamAST>> params_list)
        : params(std::move(params_list)) {}

    void Dump(int level = 0) const override {
        indent(level);
        std::cout << "FuncFParamList {\n";
        indent(level + 1);
        std::cout << "params: [\n";
        for (const auto& param : params) {
            param->Dump(level + 2);
        }
        indent(level + 1);
        std::cout << "]\n";
        indent(level);
        std::cout << "}\n";
    }

    std::string dumpIR(int& tempVarCounter) const override {
        std::string result = "";
        for (size_t i = 0; i < params.size(); ++i) {
            if (i > 0) result += ", ";
            result += params[i]->dumpIR(tempVarCounter) + ": i32";
        }
        return result;
    }
};

// Function call parameter list: f(1 + 2, 3 * 4)
class FuncRParamsAST : public BaseAST {
public:
    std::vector<std::unique_ptr<BaseAST>> params;  // Parameter list
    std::vector<std::string> str_params;  // String parameter list

    FuncRParamsAST(std::vector<std::unique_ptr<BaseAST>> params_list)
        : params(std::move(params_list)) {}
        
    FuncRParamsAST(std::vector<std::string> str_list)
        : str_params(std::move(str_list)) {}

    void Dump(int level = 0) const override {
        indent(level);
        std::cout << "FuncRParams {\n";
        if (params.size() != 0 ){
            indent(level + 1);
            std::cout << "params: [\n";
            for (const auto& param : params) {
                param->Dump(level + 2);
             }
        }
        if(str_params.size() != 0){
            indent(level + 1);
            std::cout << "str_params: [\n";
            for (const auto& string : str_params) {
                indent(level + 2);
                std::cout << string << "\n";
            }
        }
        indent(level + 1);
        std::cout << "]\n";
        indent(level);
        std::cout << "}\n";
    }

    std::string dumpIR(int& tempVarCounter) const override {
        std::string result= "";
        for (size_t i = 0; i < params.size(); ++i) {
            if (i > 0) result += ", ";
            result += params[i]->dumpIR(tempVarCounter);
        }
        int lfl = 0;
        for (size_t i = 0; i < str_params.size(); ++i) {
            for (char c : str_params[i]){
                if (c == '\\'){
                  lfl = 1; 
                  continue;
                }
                if (c == 'n' && lfl == 1){
                  result += "  call @putch(10)\n";
                  lfl=0;continue;
                }
                result += "  call @putch(" + std::to_string(static_cast<int>(c)) + ")\n";
            }
          //  if (i > 0 || !params.empty()) result += ", ";
        }
        return result;
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

class FuncDefAST : public BaseAST {
public:
  std::unique_ptr<BaseAST> func_type;
  std::string ident;
  Option<std::unique_ptr<FuncFParamListAST>> params;  
  std::unique_ptr<BaseAST> block;

  // Constructor for function without parameters
  FuncDefAST(std::unique_ptr<BaseAST> func_type, std::string ident, std::unique_ptr<BaseAST> block)
      : ident(ident), block(std::move(block)) {
    // Convert BType to FuncType if needed
    if (auto* btype = dynamic_cast<std::string*>(func_type.get())) {
      this->func_type = std::unique_ptr<BaseAST>(new FuncTypeAST(*btype));
    } else {
      this->func_type = std::move(func_type);
    }
  }

  // Constructor for function with parameters
  FuncDefAST(std::unique_ptr<BaseAST> func_type, std::string ident, 
             std::unique_ptr<FuncFParamListAST> params, std::unique_ptr<BaseAST> block)
      : ident(ident), 
        params(Option<std::unique_ptr<FuncFParamListAST>>(std::move(params))), 
        block(std::move(block)) {
    // Convert BType to FuncType if needed
    if (auto* btype = dynamic_cast<std::string*>(func_type.get())) {
      this->func_type = std::unique_ptr<BaseAST>(new FuncTypeAST(*btype));
    } else {
      this->func_type = std::move(func_type);
    }
  }

  void Dump(int level = 0) const override {
    indent(level);
    std::cout << "FuncDef {\n";
    func_type->Dump(level + 1);
    indent(level + 1);
    std::cout << "ident: " << ident << "\n";
    if (params.hasValue()) {
      params.getValue()->Dump(level + 1);
    }
    block->Dump(level + 1);
    indent(level);
    std::cout << "}\n";
  }

  std::string dumpIR(int& tempVarCounter) const override {
    mySymboltable newtbl;
    scopeManager.insertScope(newtbl);
    fun_nam[ident] = 1;
    auto u = scopeManager.lookupSymbol(ident);
    if (u.has_value()) {
        fl = 1;
        std::cout << "Error! The function name " + ident + " and variable name are duplicated\n";
    }
    IR += "fun @" + ident + "(";
    if (params.hasValue()) {
        IR += params.getValue()->dumpIR(tempVarCounter);
    }
    IR += ")";
    std::string return_type = func_type->dumpIR(tempVarCounter);
    fun_type[ident] = return_type;
    if (return_type == "int") {
      IR += ": i32";
    }
    IR += " {\n%entry:\n";
    for(const auto& var : fun_var){
      std::string name = "%" + var;
      IR += "  " + name + " = alloc i32\n";
//            std::cout << types[i] << std::endl;
      IR += "  store @" + var + ", " + name + "\n";
      mySymboltable* topscope = scopeManager.top();
      topscope->insertSymbol(var, "int", "2", name);
    }
    std::string block_ir = block->dumpIR(tempVarCounter);
    if (block_ir != "ret" && return_type != "void") {
      IR += "  ret 0\n";
    }
    else if (return_type == "void") IR += "  ret\n";
    IR += "}\n\n";
    fun_var.clear();
    scopeManager.exitScope();
    return "";
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
        if (varpit == std::nullopt){
          if(!ervar[ident]) std::cout << "Error! variable " << ident << " is not defined.\n";
          fl = 1; ervar[ident] = 1;
          return "%0";
        }
        std::string var_type = varpit.value() -> type;
        std::string var_val = varpit.value() -> value;
        std::string var_nam = varpit.value() -> address;
        if (var_type == "int"){
//          IR += var_val;
          if(var_val == "2"){
            std::string temp_var = "%" + std::to_string(tempVarCounter++);
            IR += "  " +  temp_var + " = load " + var_nam + "\n";
            bel[temp_var] =var_nam;
            return temp_var;
          }
        //  std::cout<< chk[ident] << " " << ident << std::endl;
          std::string var_ptr = "@" + ident;  // address of variable
//          std::string var_nam=var_ptr + "_" + std::to_string(var_num[var_ptr]++);
          std::string temp_var = "%" + std::to_string(tempVarCounter++);
          IR += "  " + temp_var + " = load " + var_nam + "\n";
          bel[temp_var] =var_nam;
          return temp_var;
        }
        return var_nam;
    }

    virtual int Calc() const override{
//        std::cout<<"here";
      auto varpit = scopeManager.lookupSymbol(ident);
      if (varpit == std::nullopt) return 0;
      std::string var_nam = varpit.value() -> address;
      return std::stoi(var_nam);
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
                    if(exp.getValue()){
                      std::string exp_result = exp.getValue()->dumpIR(tempVarCounter);
                      IR += "  ret " + exp_result + "\n";
                    }
                }
                else if(fl_void == 1) IR += "  ret\n";
                return "ret";
            }

            case StmtType::Assign: {
                if (lval.hasValue() && exp.hasValue()) {
                    std::string exp_result = exp.getValue()->dumpIR(tempVarCounter);
                    // std::string var_ptr = "@" + lval.getValue()->ident; 

                    // auto varpit = scopeManager.lookupSymbol(lval.getValue()->ident);
                    // std::string var_nam= varpit.value() -> address;
                    // IR += "  store " + exp_result + ", " + var_nam + "\n";
                    std::string store_location = lval.getValue()->dumpIR(tempVarCounter);
                
                    // For array access, store_location is already the correct address
                    // For regular variables, store_location is the variable name or temporary variable
                    IR += "  store " + exp_result + ", " + bel[store_location] + "\n";
                    std::string temp_var = "%" + std::to_string(tempVarCounter++);
                    IR += "  " + temp_var + " = load " + bel[store_location] + "\n";
                    return temp_var;
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
                int chkk = for_or_whi.back();
                if (chkk == 1){
                    int while_nb=while_stack.back();
                    IR += "  jump %while_end_" + std::to_string(while_nb - 1) + "\n";
                }
                else{
                    int for_nb=for_stack.back();
                    IR += "  jump %for_end_" + std::to_string(for_nb - 1) + "\n";
                }
                return "break";
            }

            case StmtType::Continue: {
                // Jump to the conditional judgment label of the current loop
                int chkk = for_or_whi.back();
                if (chkk == 1){
                    int while_nb=while_stack.back();
                    IR += "  jump %while_entry_" + std::to_string(while_nb - 1) + "\n";
                }
                else{
                    int for_nb=for_stack.back();
                    IR += "  jump %for_entry_" + std::to_string(for_nb - 1) + "\n";
                }
                return "cont";
            }
            
            default:
                assert(false && "Unknown statement type");
                return "";
        }
    }

    virtual int Calc() const override{
//        std::cout<<"here";
        if(exp.hasValue()) return exp.getValue()->Calc();
        return 0;
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
        IR += "  br " + cond_result + ", " + then_label + ", ";
        if (else_stmt.hasValue()) {
            IR += else_label + "\n";
        } else {
            IR += end_label + "\n";
        }

        // then branches
        IR += then_label + ":\n";
        fl_void = 1; 
        std::string not_if = then_stmt->dumpIR(tempVarCounter);
        fl_void = 0;
        if (not_if != "ret" && not_if != "break" && not_if != "cont") {
          IR += "  jump " + end_label + "\n";
        }
        std::string not_else = "";
        // else branches(if exits)
        if (else_stmt.hasValue()) {
            IR += else_label + ":\n";
            fl_void = 1;
            not_else = else_stmt.getValue()->dumpIR(tempVarCounter);
            fl_void = 0;
            if (not_else != "ret" && not_else != "break" &&
                not_else != "cont")
                IR += "  jump " + end_label + "\n";
            if(not_if == "ret") fl_void = 1;
            if((not_if == "ret" || not_if == "break" || not_if == "cont" ) && 
              (not_else == "ret" || not_else == "break" || not_else == "cont")) return "ret";
        }
        IR += end_label + ":\n";
        return "";
    }
};

// WhileStmt for representing while loop
class WhileStmtAST : public BaseAST {
public:
    std::unique_ptr<BaseAST> cond;     // condition
    std::unique_ptr<BaseAST> body;     // loop body

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
        for_or_whi.push_back(1);
        std::string entry_label = "%while_entry_" + std::to_string(while_num);
        std::string body_label = "%while_body_" + std::to_string(while_num);
        std::string end_label = "%while_end_" + std::to_string(while_num++);
        while_stack.push_back(while_num);
        // Jump to entry block
        IR += "  jump " + entry_label + "\n";
        
        // Entry block: evaluate condition
        IR += entry_label + ":\n";
        std::string cond_result = cond->dumpIR(tempVarCounter);
        IR += "  br " + cond_result + ", " + body_label + ", " + end_label + "\n";
        
        // Body block: execute loop body
        IR += body_label + ":\n";
        fl_void = 1;
        std::string not_ret = body->dumpIR(tempVarCounter);
        fl_void = 0;
        if (not_ret != "ret" && not_ret != "break" && not_ret != "cont")
            IR += "  jump " + entry_label + "\n";
        
        // End block
        IR += end_label + ":\n";
        while_stack.pop_back();
        for_or_whi.pop_back();
        return "";
    }
};

class ForStmtAST : public BaseAST {
public:
    Option<std::unique_ptr<BaseAST>> init;    // Initialization (Optional)
    Option<std::unique_ptr<BaseAST>> cond;    // Condition (Optional)
    Option<std::unique_ptr<BaseAST>> update;  // Update (Optional)
    std::unique_ptr<BaseAST> body;            // Body

    ForStmtAST(BaseAST* init, BaseAST* cond, BaseAST* update, BaseAST* body)
        : body(std::unique_ptr<BaseAST>(body)) {
        if (init) this->init = Option(std::unique_ptr<BaseAST>(init));
        if (cond) this->cond = Option(std::unique_ptr<BaseAST>(cond));
        if (update) this->update = Option(std::unique_ptr<BaseAST>(update));
    }

    void Dump(int level = 0) const override {
        indent(level);
        std::cout << "ForStmt {\n";
        
        if (init.hasValue()) {
            indent(level + 1);
            std::cout << "init: {\n";
            init.getValue()->Dump(level + 2);
            indent(level + 1);
            std::cout << "}\n";
        }
        
        if (cond.hasValue()) {
            indent(level + 1);
            std::cout << "condition: {\n";
            cond.getValue()->Dump(level + 2);
            indent(level + 1);
            std::cout << "}\n";
        }
        
        if (update.hasValue()) {
            indent(level + 1);
            std::cout << "update: {\n";
            update.getValue()->Dump(level + 2);
            indent(level + 1);
            std::cout << "}\n";
        }
        
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
        std::string entry_label = "%for_entry_" + std::to_string(while_num);
        std::string body_label = "%for_body_" + std::to_string(while_num);
        std::string update_label = "%for_update_" + std::to_string(while_num);
        std::string end_label = "%for_end_" + std::to_string(while_num++);
        for_or_whi.push_back(0);
        for_stack.push_back(while_num);
        std::string last_result;
        mySymboltable newtbl;
        scopeManager.insertScope(newtbl);
        // Initialize if exists
        if (init.hasValue()) {
            init.getValue()->dumpIR(tempVarCounter);
        }
        // Jump to entry block
        IR += "  jump " + entry_label + "\n";
        
        // Entry block: evaluate condition
        IR += entry_label + ":\n";
        std::string cond_result = "1"; // If no condition, loop forever
        if (cond.hasValue()) {
            cond_result = cond.getValue()->dumpIR(tempVarCounter);
        }
        IR += "  br " + cond_result + ", " + body_label + ", " + end_label + "\n";
        
        // Body block
        IR += body_label + ":\n";
        std::string not_ret = body->dumpIR(tempVarCounter);
        if (not_ret != "ret" && not_ret != "break" && not_ret != "cont") {
            IR += "  jump " + update_label + "\n";
        }
        
        // Update block
        IR += update_label + ":\n";
        if (update.hasValue()) {
            update.getValue()->dumpIR(tempVarCounter);
        }
        IR += "  jump " + entry_label + "\n";
        
        // End block
        IR += end_label + ":\n";
        for_stack.pop_back();
        for_or_whi.pop_back();
        scopeManager.exitScope();
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
  std::unique_ptr<BaseAST> lval; 

  PrimaryExpAST(int val) 
      : type(PrimaryExpType::number), number(val), exp(nullptr) {}

  PrimaryExpAST(std::unique_ptr<BaseAST> e)
      : type(PrimaryExpType::exp), number(0), exp(std::move(e)) {}

  PrimaryExpAST(BaseAST* l)
    : type(PrimaryExpType::LVal), number(0), exp(nullptr),
      lval(std::unique_ptr<BaseAST>(l)) {}

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
        lval->Dump(level + 2);
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
      // auto varpit = scopeManager.lookupSymbol(LVal);
      // std::string var_type= varpit.value() -> type;
      // std::string var_val = varpit.value() -> value;
      // std::string var_nam= varpit.value() -> address;
      // if (var_type == "int"){
      //   if(var_val == "2"){
      //       std::string temp_var = "%" + std::to_string(tempVarCounter++);
      //       IR += "  " +  temp_var + " = load " + var_nam + "\n";
      //       return temp_var;
      //   }
      //   //  std::cout<< chk[LVal] << " " << LVal << std::endl;
      //     std::string var_ptr = "@" + LVal;  // variable's address
      //   //  std::string var_nam=var_ptr + "_" + std::to_string(var_num[var_ptr]++);
      //     std::string temp_var = "%" + std::to_string(tempVarCounter++);
      //     IR += "  " + temp_var + " = load " + var_nam + "\n";
      //     return temp_var;
      // }
      // return var_nam;
        // Directly use dumpIR() method of lval, rather than look up in symbol table
        return lval->dumpIR(tempVarCounter);
    }
    return "";
  }

  virtual int Calc() const override{
    if (type == PrimaryExpType::number) {
      return number;
    } else if (type == PrimaryExpType::exp) {
      return exp->Calc();
    } else if (type == PrimaryExpType::LVal) {
      // auto varpit = scopeManager.lookbupSymbol(LVal);
      // std::string var_type= varpit.value() -> type;
      // std::string var_nam= varpit.value() -> address;
      // return std::stoi(var_nam);
      // Directly use Calc() method of lval
        return lval->Calc();
    }
    assert(false);
  }
};

// UnaryExp handel +, -, !
class UnaryExpAST : public BaseAST {
 public:
  UnaryExpType type;
  std::string op;
  std::unique_ptr<BaseAST> exp;
  std::string ident;
  Option<std::unique_ptr<FuncRParamsAST>> rparams;

  UnaryExpAST(std::string op, std::unique_ptr<BaseAST> exp)
      : type(UnaryExpType::Unary_op), op(op), exp(std::move(exp)) {}

  UnaryExpAST(std::unique_ptr<BaseAST> primary)
      : type(UnaryExpType::Primary), exp(std::move(primary)) {}

  UnaryExpAST(std::string name)
      : type(UnaryExpType::Function), ident(name) {}

  UnaryExpAST(std::string name, std::unique_ptr<FuncRParamsAST> params)
      : type(UnaryExpType::Function), ident(name), 
        rparams(Option<std::unique_ptr<FuncRParamsAST>>(std::move(params))) {}

  void Dump(int level = 0) const override {
      indent(level);
      std::cout << "UnaryExp {\n";
      indent(level + 1);

      switch (type) {
          case UnaryExpType::Unary_op:
              std::cout << "op: " << op << "\n";
              exp->Dump(level + 1);
              break;

          case UnaryExpType::Primary:
              exp->Dump(level + 1);
              break;

          case UnaryExpType::Function:
              std::cout << "function: " << ident << "\n";
              if (rparams.hasValue()) {
                  rparams.getValue()->Dump(level + 1);
              }
              break;
      }

      indent(level);
      std::cout << "}\n";
  }

  std::string dumpIR(int& tempVarCounter) const override {
      switch (type) {
          case UnaryExpType::Unary_op: {
              // Deal with post++ / post-- first
              if (op == "post++" || op == "post--") {
                  // get current value of variable
                  std::string expr_ir = exp->dumpIR(tempVarCounter);
                  
                  // store original value for return
                  std::string orig_val = "%" + std::to_string(tempVarCounter++);
                  IR += "  " + orig_val + " = add " + expr_ir + ", 0\n";  // copy original value
                  
                  // Compute new value
                  std::string new_val = "%" + std::to_string(tempVarCounter++);
                  if (op == "post++") {
                      IR += "  " + new_val + " = add " + expr_ir + ", 1\n";
                  } else { // post--
                      IR += "  " + new_val + " = sub " + expr_ir + ", 1\n";
                  }
                  
                  if (bel.find(expr_ir) == bel.end()) {
                      std::cerr << "Error! Self increasing and decreasing operations can only be used for variables" << std::endl;
                      fl = 1;
                      return "";
                  }
                //  std::cout<<"!!!ident: "<<ident<<std::endl;
                  // look up variable and store new value
              //    std::cout<<"here\n"<<expr_ir<<"\n"<<ident;
            //      auto var_sym = scopeManager.lookupSymbol(ident);
                //  auto var_sym = scopeManager.lookupSymbol(exp->dumpIR(tempVarCounter));
                //  if (!var_sym.has_value()) {
                  //    std::cerr << "Error: Undefined variable" << std::endl;
                    //  fl = 1;
                      //return "";
                  //}
                  
                  IR += "  store " + new_val + ", " + bel[expr_ir]/*var_sym.value()->address*/ + "\n";
                  return orig_val;  // retuen original value
              }
              // Deal with pre++ /pre --
              else if (op == "++" || op == "--") {
                  // get the current value of variable
                  std::string expr_ir = exp->dumpIR(tempVarCounter);
                  
                  // Compute new value
                  std::string new_val = "%" + std::to_string(tempVarCounter++);
                  if (op == "++") {
                      IR += "  " + new_val + " = add " + expr_ir + ", 1\n";
                  } else { // --
                      IR += "  " + new_val + " = sub " + expr_ir + ", 1\n";
                  }
                  
                  // ensure exp is a lval
                /*  auto var = dynamic_cast<const LValAST*>(exp.get());
                  if (!var) {
                      // std::cerr << "Error: ++/-- can only be used upon variables" << std::endl;
                      fl = 1;
                      return "";
                  }
                  
                  // look up variable and store new value
                  auto var_sym = scopeManager.lookupSymbol(var->ident);
                  if (!var_sym.has_value()) {
                      std::cerr << "Error: Undefined variables" << std::endl;
                      fl = 1;
                      return "";
                  }
                  */
                 if (bel.find(expr_ir) == bel.end()) {
                      std::cerr << "Error! Self increasing and decreasing operations can only be used for variables" << std::endl;
                      fl = 1;
                      return "";
                  }
                  IR += "  store " + new_val + ", " + bel[expr_ir]/*var_sym.value()->address*/ + "\n";
                  return new_val;  // return new value
              }
              // deal with other unary operators
              else {
                  std::string expr_ir = exp->dumpIR(tempVarCounter);
                  if (op == "+") return expr_ir;
                      
                  std::string temp_var = "%" + std::to_string(tempVarCounter++);
                  if (op == "-") {
                      IR += "  " + temp_var + " = sub 0, " + expr_ir + "\n";
                  } else if (op == "!") {
                      IR += "  " + temp_var + " = eq " + expr_ir + ", 0\n";
                  }
                  return temp_var;
              }
          }

          case UnaryExpType::Function: {
              std::string mid_var = "";
              std::string temp_var = "%" + std::to_string(tempVarCounter);
              if (!fun_nam[ident]){
                std::cout<<"Error! The function name " + ident + " is undefined\n";
                fl = 1;
              }
              if (rparams.hasValue())
                mid_var = rparams.getValue()->dumpIR(tempVarCounter);
              if(fun_type[ident] == "int" ){
                temp_var = "%" + std::to_string(tempVarCounter++);
                IR += "  " + temp_var + " = call @" + ident + "(";
              }
              else{
                if (ident != "puts") IR += "  call @" + ident + "(";
              }
              if (rparams.hasValue()) {
                  IR += mid_var;
              }
                  
              if (ident != "puts") IR += ")\n";
              return temp_var;
          }

          case UnaryExpType::Primary:
              return exp->dumpIR(tempVarCounter);
      }
          
      assert(false);
      return "";
  }

  virtual int Calc() const override {
      switch (type) {
          case UnaryExpType::Unary_op: {
              int result = exp->Calc();
              if (op == "-") result = -result;
              if (op == "+") result = result;
              if (op == "!") result = !result;
              return result;
          }

          case UnaryExpType::Function:
              // Function calls cannot be evaluated at compile time
              assert(false);
              return 0;

          case UnaryExpType::Primary:
              return exp->Calc();
      }

      assert(false);
      return 0;
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
        IR += "  " + tempVar + " = add " + left_ir + ", " + right_ir + "\n";
      } else if(op=="-"){
        IR += "  " + tempVar + " = sub " + left_ir + ", " + right_ir + "\n";
      }
      else assert(false);
//      std::cout << "!!!!\n"<<tempVar<<"\n";
      return tempVar;
    }
  //  std::cout<<"asdf\n";
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
        IR += "  " + tempVar + " = mul " + left_ir + ", " + right_ir + "\n";
      } else if(op=="/"){
        IR += "  " + tempVar + " = div " + left_ir + ", " + right_ir + "\n";
      } else if(op=="%"){
        IR += "  " + tempVar + " = mod " + left_ir + ", " + right_ir + "\n";
      }/*
      else if(op == "&"){
          IR += "  " + tempVar + " = and " + left_ir + ", " + right_ir + "\n";
      } else if(op == "|"){
          IR += "  " + tempVar + " = or " + left_ir + ", " + right_ir + "\n";
      } else if(op == "^"){
          IR += "  " + tempVar + " = xor " + left_ir + ", " + right_ir + "\n";
      } else if(op == "<<"){
          IR += "  " + tempVar + " = shl " + left_ir + ", " + right_ir + "\n";
      } else if(op == ">>"){
          IR += "  " + tempVar + " = sar " + left_ir + ", " + right_ir + "\n";
      }*/
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
        IR += "  " + tempVar + " = lt " + left_result + ", " + right_result + "\n";
      } else if (op == ">"){
        IR += "  " + tempVar + " = gt " + left_result + ", " + right_result + "\n";
      } else if (op=="<="){
        IR += "  " + tempVar + " = le " + left_result + ", " + right_result + "\n";
      } else if (op==">="){
        IR += "  " + tempVar + " = ge " + left_result + ", " + right_result + "\n";
      } else assert(false);
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
        IR += "  " + tempVar + " = eq " + left_result + " , " + right_result + "\n";
      } else if (op == "!="){
        IR += "  " + tempVar + " = ne " + left_result + " , " + right_result + "\n";
      } else assert(false);
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
      IR += "  " + result_var_ptr + " = alloc i32" + "\n";

      // Perform branching based on the result of the left operand
      IR += "  br " + left_result + ", " + then_label + ", " + else_label + "\n";

      // Then block: evaluate the right operand if left is true
      IR += then_label + ":" + "\n";
      std::string right_result = right_AST->dumpIR(tempVarCounter);
      std::string tmp_result_var = "%" + std::to_string(tempVarCounter++);
      IR += "  " + tmp_result_var + " = ne " + right_result + ", 0" + "\n";

      // Store the result of right operand evaluation
      IR += "  store " + tmp_result_var + ", " + result_var_ptr + "\n";
      IR += "  jump " + end_label + "\n";

      // Else block: if left is false, set the result to false (0)
      IR += else_label + ":" + "\n";
      IR += "  store 0, " + result_var_ptr + "\n";
      IR += "  jump " + end_label + "\n";

      // End label: load the final result
      IR += end_label + ":" + "\n";
      result_var = "%" + std::to_string(tempVarCounter++);
      IR += "  " + result_var + " = load " + result_var_ptr + "\n";
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
      IR += "  " + result_var_ptr + " = alloc i32" + "\n";

      // Conditional branching based on the result of the left operand
      IR += "  br " + left_result + ", " + then_label + ", " + else_label + "\n";

      // Then block: if the left operand is non-zero (true), store 1
      IR += then_label + ":" + "\n";
      IR += "  store 1, " + result_var_ptr + "\n";
      IR += "  jump " + end_label + "\n";

      // Else block: if the left operand is zero (false), evaluate the right operand
      IR += else_label + ":" + "\n";
      std::string tmp_result_var = "%" + std::to_string(tempVarCounter++);
      std::string right_result = right_AST->dumpIR(tempVarCounter);
      IR += "  " + tmp_result_var + " = ne " + right_result + ", 0" + "\n";

      // Store the result of the right operand evaluation (1 if true, 0 if false)
      IR += "  store " + tmp_result_var + ", " + result_var_ptr + "\n";
      IR += "  jump " + end_label + "\n";

      // End block: load the final result (either 1 or 0) into the result variable
      IR += end_label + ":" + "\n";
      result_var = "%" + std::to_string(tempVarCounter++);
      IR += "  " + result_var + " = load " + result_var_ptr + "\n";
    }
    return result_var;
  }

  virtual int Calc() const override{
    int result = 1;
    if (!right_AST) result = left_AST->Calc();
    else{
      int left_result = left_AST->Calc();
      if (left_result) return 1;
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
        int init_val_ir = init_val->Calc();
        if (fun_nam[ident]){
            fl=1;
            std::cout << "Error! The const name " << ident << " and function name are duplicated\n";
        }
        if (ident == "main"){
            fl=1;
            std::cout << "The const name cannot be 'main'\n";
        }
        mySymboltable* topscope = scopeManager.top();
        topscope -> insertSymbol(ident, "const", "1", std::to_string(init_val_ir));
        //chk[ident] = init_val_ir;
        return std::to_string(init_val_ir);
    }

    virtual int Calc() const override{
    //  std::cout<<"herer";
      int init_val_ir = init_val->Calc();
      if (fun_nam[ident]){
            fl=1;
            std::cout << "Error! The const name " << ident << " and function name are duplicated\n";
      }
      if (ident == "main"){
            fl=1;
            std::cout << "The const name cannot be 'main'\n";
        }
      mySymboltable* topscope = scopeManager.top();
      topscope -> insertSymbol(ident, "const", "1", std::to_string(init_val_ir));
      return init_val_ir;
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
   //     std::cout<<"\n\n\n\n\n\n\n\n\n\n\n"<<const_defs.size()<<"\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
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

    virtual int Calc() const override{
      //  std::cout<<glb_IR+IR;
      //  std::cout<<"\n\n\n\n\n\n\n\n\n\n\n"<<const_defs.size()<<"\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
        for (const auto& def : const_defs) {
          //  std::cout << "here";
            def->Calc();
        }
        return 0;
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
        IR += "  " + var_nam + " = alloc i32\n";
        if (fun_nam[ident]){
            fl=1;
            std::cout << "Error! The variable name " << ident << " and function name are duplicated\n";
        }
        if (ident == "main"){
            fl=1;
            std::cout << "Variable name cannot be 'main'\n";
        }
        mySymboltable* topscope = scopeManager.top();
        topscope -> insertSymbol(ident, "int", "1", var_nam);
        if (has_init) {
            std::string init_val_ir = init_val->dumpIR(tempVarCounter);
            IR += "  store " + init_val_ir + ", " + var_nam + "\n";
        }
        
        return var_ptr;
    }

    virtual int Calc() const override{
        std::string var_ptr = "@" + ident;
        std::string var_nam = var_ptr + "_" + std::to_string(var_num[var_ptr]++);
        glb_IR += "global  " + var_nam + " = alloc i32, ";
        if (fun_nam[ident]){
            fl=1;
            std::cout << "Error! The variable name " << ident << " and function name are duplicated\n";
        }
        if (ident == "main"){
            fl=1;
            std::cout << "Variable name cannot be 'main'\n";
        }
        mySymboltable* topscope = scopeManager.top();
        topscope -> insertSymbol(ident, "int", "1", var_nam);
        if (has_init) {
            int var_val = init_val -> Calc();
            if(var_val != 0) glb_IR += std::to_string(var_val) + "\n";
            else glb_IR += "zeroinit\n";
        }
        else glb_IR += "zeroinit\n";
        glb_IR += "\n";
        return 0;
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
// ShiftExpAST handle <<, >>
class ShiftExpAST : public BaseAST {
 public:
  std::string op;
  std::unique_ptr<BaseAST> left_AST;
  std::unique_ptr<BaseAST> right_AST;

  ShiftExpAST(std::unique_ptr<BaseAST> left)
    : op(""), left_AST(std::move(left)), right_AST(nullptr) {}

  ShiftExpAST(std::string op, std::unique_ptr<BaseAST> left, std::unique_ptr<BaseAST> right)
    : op(op), left_AST(std::move(left)), right_AST(std::move(right)) {}

  void Dump(int level = 0) const override {
      indent(level);
      std::cout << "ShiftExp {\n";
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
      
      if(op == "<<"){
        IR += "  " + tempVar + " = shl " + left_ir + ", " + right_ir + "\n";
      }
      else if(op == ">>"){
        IR += "  " + tempVar + " = sar " + left_ir + ", " + right_ir + "\n";
      }
      return tempVar;
    }
    return left_ir;
  }

  virtual int Calc() const override {
    if (!right_AST) return left_AST->Calc();
    int left_val = left_AST->Calc();
    int right_val = right_AST->Calc();
    if (op == "<<") return left_val << right_val;
    if (op == ">>") return left_val >> right_val;
    assert(false);
    return 0;
  }
};

// BitExpAST handle &, |, ^
class BitExpAST : public BaseAST {
 public:
  std::string op;
  std::unique_ptr<BaseAST> left_AST;
  std::unique_ptr<BaseAST> right_AST;

  BitExpAST(std::unique_ptr<BaseAST> left)
    : op(""), left_AST(std::move(left)), right_AST(nullptr) {}

  BitExpAST(std::string op, std::unique_ptr<BaseAST> left, std::unique_ptr<BaseAST> right)
    : op(op), left_AST(std::move(left)), right_AST(std::move(right)) {}

  void Dump(int level = 0) const override {
      indent(level);
      std::cout << "BitExp {\n";
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
      if(op == "&"){
        IR += "  " + tempVar + " = and " + left_ir + ", " + right_ir + "\n";
      } else if(op == "|"){
        IR += "  " + tempVar + " = or " + left_ir + ", " + right_ir + "\n";
      } else if(op == "^"){
        IR += "  " + tempVar + " = xor " + left_ir + ", " + right_ir + "\n";
      } else assert(false);
      return tempVar;
    }
    return left_ir;
  }

  virtual int Calc() const override {
    if (!right_AST) return left_AST->Calc();
    int left_val = left_AST->Calc();
    int right_val = right_AST->Calc();
    if (op == "&") return left_val & right_val;
    if (op == "|") return left_val | right_val;
    if (op == "^") return left_val ^ right_val;
    assert(false);
    return 0;
  }
};

class ArrayTypeAST : public BaseAST {
public:
    std::vector<std::unique_ptr<BaseAST>> dims;  // expressions for each dimension
    std::string base_type;                       // int

    ArrayTypeAST(std::string type, std::vector<std::unique_ptr<BaseAST>> dimensions)
        : base_type(type), dims(std::move(dimensions)) {}

    void Dump(int level = 0) const override {
        indent(level);
        std::cout << "ArrayType {\n";
        indent(level + 1);
        std::cout << "base_type: " << base_type << "\n";
        indent(level + 1);
        std::cout << "dimensions: [\n";
        for (const auto& dim : dims) {
            dim->Dump(level + 2);
        }
        indent(level + 1);
        std::cout << "]\n";
        indent(level);
        std::cout << "}\n";
    }

    std::string dumpIR(int& tempVarCounter) const override {
        // Check if in global scope
        
        // Compute total size and sizes for different dimensions
        std::vector<int> dim_sizes;
        int total_size = 1;
        for(const auto& dim : dims) {
            int size = dim->Calc();
            dim_sizes.push_back(size);
            total_size *= size;
        }
        // Generate type string
        std::string type_str = "[i32";
        for(const auto& size : dim_sizes) {
            type_str += ", " + std::to_string(size);
        }
        type_str += "]";
        
        return type_str;
    }
};

class ArrayInitValAST : public BaseAST {
public:
    std::vector<std::unique_ptr<BaseAST>> elements;
    bool is_const;

    ArrayInitValAST(std::vector<std::unique_ptr<BaseAST>>&& elems, bool is_constant = false)
        : elements(std::move(elems)), is_const(is_constant) {}

    void Dump(int level = 0) const override {
        indent(level);
        std::cout << "ArrayInitVal {\n";
        indent(level + 1);
        std::cout << "elements: [\n";
        for (const auto& elem : elements) {
            elem->Dump(level + 2);
        }
        indent(level + 1);
        std::cout << "]\n";
        indent(level);
        std::cout << "}\n";
    }

    std::string dumpIR(int& tempVarCounter) const override {
      //  std::cout<<"hqweqe\n";
        std::string ident = list_nam.back();
        std::string arr_ptr = ident + "_" + std::to_string(var_num[list_nam.back()]-1);  // Get array base address
        if(is_const) {
            std::vector <int> ele;
            // Constant array initialization must use constant expressions
            if(elements.empty()) {
                for(int i=0; i<list_length.back(); ++i) {
                    ele.push_back(0);
                }
                mySymboltable* topscope = scopeManager.top();
                topscope->insertSymbol(ident, "array", "2", arr_ptr, ele);
                IR += "zeroinit\n";
                return "zeroinit";
            }
          //  std::string init_str = "{";
            for(size_t i = 0; i < elements.size(); ++i) {
          //      if(i > 0) init_str += ", ";
                int u = elements[i]->Calc();
                // For constant array, directly compute its value
          //      init_str += std::to_string(u);
                ele.push_back(u);
            }
            for(int i = elements.size(); i < list_length.back(); ++i) {
          //      std::string elem_ptr = "%" + std::to_string(tempVarCounter++);
          //      IR += "  " + elem_ptr + " = getelemptr " + arr_ptr + ", " + std::to_string(i) + "\n";
           //     IR += "  store 0, " + elem_ptr + "\n";
                  ele.push_back(0);
            }
         //   init_str += "}";
          //  IR += init_str + "\n";
            mySymboltable* topscope = scopeManager.top();
            topscope->insertSymbol(ident, "array", "2", arr_ptr, ele);
            return std::to_string(elements.size());
        } else {
          // For variable arrays, generate multiple store instructions
          //  int length = stoi(elements[0]->dumpIR(tempVarCounter));
          //  std::string arr_ptr = list_nam.back() + "_" + std::to_string(var_num[list_nam.back()]-1);;  // Get array base address
            for(size_t i = 0; i < elements.size(); ++i) {
                auto array_sym = scopeManager.lookupSymbol(ident);
                std::string elem_ptr = "%" + std::to_string(tempVarCounter++);
                IR += "  " + elem_ptr + " = getelemptr " + arr_ptr + ", " + std::to_string(i) + "\n";
                std::string u = elements[i]->dumpIR(tempVarCounter);
                IR += "  store " + u + ", " + elem_ptr + "\n";
            }
          //  std::cout<<"here";
          //  IR += std::to_string(list_length.back())+"haqadsfasdf\n";
            for(int i=elements.size();i<=list_length.back()-1;++i){
                std::string elem_ptr = "%" + std::to_string(tempVarCounter++);
                IR += "  " + elem_ptr + " = getelemptr " + arr_ptr + ", " + std::to_string(i) + "\n";
                IR += "  store 0, " + elem_ptr + "\n";
            }
            
          //  mySymboltable* topscope = scopeManager.top();
          //  topscope->insertSymbol(ident, "array", "2", arr_ptr);
            return std::to_string(elements.size());
        }
    }

    virtual int Calc() const override {
        if(is_const) {
            std::string ident = list_nam.back();
            std::string arr_ptr = ident + "_" + std::to_string(var_num[list_nam.back()]-1);  // Get array base address
            std::vector <int> ele;
            for(size_t i = 0; i < elements.size(); ++i) {
                int u = elements[i]->Calc();
                ele.push_back(u);
            }
            for(int i = elements.size(); i < list_length.back(); ++i) {
                  ele.push_back(0);
            }
            mySymboltable* topscope = scopeManager.top();
            topscope->insertSymbol(ident, "const_array", "2", arr_ptr, ele);
            return elements.size();
        } else {
            // For variable arrays, generate multiple store instructions
            IR += "{";
            for(size_t i = 0; i < elements.size(); ++i) {
                int u = elements[i]->Calc();
                IR +=  std::to_string(u) ;
                if (i != elements.size()-1) IR += ", ";
            }
            for(int i=elements.size(); i<=list_length.back()-1; ++i){
                if(i != list_length.back()) IR += ", ";
                int numb = 0;
                IR += std::to_string(numb);
            }
            IR += "}\n";
            return 0;
        }
    }

};

class ArrayAccessAST : public BaseAST {
public:
    std::string ident;
    std::vector<std::unique_ptr<BaseAST>> indices;

    ArrayAccessAST(std::string name, std::vector<std::unique_ptr<BaseAST>> idx)
        : ident(name), indices(std::move(idx)) {}

    void Dump(int level = 0) const override {
        indent(level);
        std::cout << "ArrayAccess {\n";
        indent(level + 1);
        std::cout << "array: " << ident << "\n";
        indent(level + 1);
        std::cout << "indices: [\n";
        for (const auto& idx : indices) {
            idx->Dump(level + 2);
        }
        indent(level + 1);
        std::cout << "]\n";
        indent(level);
        std::cout << "}\n";
    }

    std::string dumpIR(int& tempVarCounter) const override {
      //  IR += "\n12312313\n";
    //  std::cout<<glb_IR+IR;
        std::string u= "@" + ident;
        auto array_sym = scopeManager.lookupSymbol(u);
      /*  if(!array_sym.has_value() || !array_sym.value()->is_array) {
            std::cerr << "Error: Invalid array access" << std::endl;
            fl = 1;  // Set wrong flag
            return "";
        }
        
        // Check if the number of dimensions matches
        if(indices.size() != array_sym.value()->array_dims.size()) {
            std::cerr << "Error: Array dimension mismatch" << std::endl;
            fl = 1;
            return "";
        }*/
        
          // Generate IR code for array access
          if (array_sym == std::nullopt){
            if(!erary[ident]) std::cout << "Error! array " << ident << " is not defined.\n";
            fl = 1; erary[ident] = 1;
            return "%0";
          }
          std::string type =array_sym.value() -> type;
          std::string current_ptr = array_sym.value() -> address;
      //  std::string type =array_sym.value() -> type;
      //  IR += "12312313" + current_ptr + "\n";
    //  std::cout<<glb_IR+IR;
  //    std::cout<<"here!!\n\n";
        if (type == "array" || type == "const_array"){
      //      std::cout<<"here!!\n\n";
          //  std::cout<<glb_IR+IR;
            for(const auto& index : indices) {
             //   std::cout<<glb_IR+IR;
                std::string idx_val = index->dumpIR(tempVarCounter);
               // std::cout<<glb_IR+IR;
                std::string elem_ptr = "%" + std::to_string(tempVarCounter++);
                IR += "  " + elem_ptr + " = getelemptr " + current_ptr + ", " + idx_val + "\n";
                current_ptr = elem_ptr;
            }
            
            // Load array element value
            std::string result = "%" + std::to_string(tempVarCounter++);
            IR += "  " + result + " = load " + current_ptr + "\n";
            bel[result] = current_ptr;
            return result;
        }
        else if (type == "const_array"){
          //  std::cout<<"hhhhhh\n";
            int idx_val = indices[0]->Calc();
            std::vector<int> elee = array_sym.value() -> ele;
          //  std::cout<<idx_val<<"asdfasdfas\n";
            return "";
           // return std::to_string(elee[std::stoi(idx_val)]);
        }
     //   std::cout<<glb_IR+IR;
    }
};

// Common base class for array declarations
class ArrayDefBaseAST : public BaseAST {
public:
    std::string ident;                          // name
    std::vector<std::unique_ptr<BaseAST>> dims; // expressions for each dimension

    ArrayDefBaseAST(std::string name, std::vector<std::unique_ptr<BaseAST>> dimensions)
        : ident(name), dims(std::move(dimensions)) {}

    virtual void Dump(int level = 0) const override {
        indent(level);
        std::cout << "ArrayDef {\n";
        indent(level + 1);
        std::cout << "ident: " << ident << "\n";
        indent(level + 1);
        std::cout << "dimensions: [\n";
        for(const auto& dim : dims) {
            dim->Dump(level + 2);
        }
        indent(level + 1);
        std::cout << "]\n";
    }
};

// AST Node for Constant Array Def
class ConstArrayDefAST : public ArrayDefBaseAST {
public:
    std::unique_ptr<BaseAST> init_val;  // Initial value

    ConstArrayDefAST(std::string name, 
                    std::vector<std::unique_ptr<BaseAST>> dimensions,
                    std::unique_ptr<BaseAST> init)
        : ArrayDefBaseAST(name, std::move(dimensions)), 
          init_val(std::move(init)) {}

    void Dump(int level = 0) const override {
        ArrayDefBaseAST::Dump(level);  // Call base dump()
        indent(level + 1);
        std::cout << "init_val: {\n";
        if(init_val) {
            init_val->Dump(level + 2);
        }
        indent(level + 1);
        std::cout << "}\n";
        indent(level);
        std::cout << "}\n";
    }

    std::string dumpIR(int& tempVarCounter) const override {
        std::string total_size = "1";
        for(const auto& dim : dims) {
            int dim_size = dim->Calc();  // Use Calc() to get constant dimension size
            total_size = std::to_string(std::stoi(total_size) * dim_size);
        }
        
        // Generate IR for array allocation and initialization
        std::string var_ptr = "@" + ident;
        std::string var_nam = var_ptr + "_" + std::to_string(var_num[var_ptr]++);
        IR += " " + var_nam + " = alloc [i32, " + total_size + "]\n";
        
        mySymboltable* topscope = scopeManager.top();
        topscope->insertSymbol(var_ptr, "array", "1", var_nam);
        topscope->insertSymbol(ident, "check", "3", var_nam);
        if (fun_nam[ident]){
            fl=1;
            std::cout << "Error! The const array's name " << ident << " and function name are duplicated\n";
        }
        if (ident == "main"){
            fl=1;
            std::cout << "Error! The const array's name cannot be 'main'\n";
        }

     //   if(has_init) {
            list_nam.push_back(var_ptr);
            list_length.push_back(std::stoi(total_size));
            init_val->dumpIR(tempVarCounter);
          //  IR += nmb;
            // TODO: Deal with Initialization
            // Need to traverse init_val and generate corresponding store instructions
     //   }
      //  else{
      //    IR += "zeroinit\n";
      //  }
        return var_ptr;
    }

    virtual int Calc() const override{
        std::string total_size = "1";
        for(const auto& dim : dims) {
            int dim_size = dim->Calc();  // Use Calc() to get constant dimension size
            total_size = std::to_string(std::stoi(total_size) * dim_size);
        }
        
        // Generate IR for array allocation and initialization
        std::string var_ptr = "@" + ident;
        std::string var_nam = var_ptr + "_" + std::to_string(var_num[var_ptr]++);
        IR += "global " + var_nam + " = alloc [i32, " + total_size + "], ";
        
        mySymboltable* topscope = scopeManager.top();
        topscope->insertSymbol(var_ptr, "array", "1", var_nam);
        topscope->insertSymbol(ident, "check", "3", var_nam);
        if (fun_nam[ident]){
            fl=1;
            std::cout << "Error! The const array's name " << ident << " and function name are duplicated\n";
        }
        if (ident == "main"){
            fl=1;
            std::cout << "Error! The const array's name cannot be 'main'\n";
        }

      //  if(has_init) {
            list_nam.push_back(var_ptr);
            list_length.push_back(std::stoi(total_size));
            init_val->Calc();
          //  IR += nmb;
            // TODO: Deal with Initialization
            // Need to traverse init_val and generate corresponding store instructions
     //   }
     //   else{
      //    IR += "zeroinit\n";
      //  }
        return 0;
    }
};

// AST Node for Array Def
class VarArrayDefAST : public ArrayDefBaseAST {
public:
    std::unique_ptr<BaseAST> init_val;  // Optional initial value
    bool has_init;                      // Whether have initial value

    VarArrayDefAST(std::string name, 
                  std::vector<std::unique_ptr<BaseAST>> dimensions)
        : ArrayDefBaseAST(name, std::move(dimensions)), 
          has_init(false) {}

    VarArrayDefAST(std::string name, 
                  std::vector<std::unique_ptr<BaseAST>> dimensions,
                  std::unique_ptr<BaseAST> init)
        : ArrayDefBaseAST(name, std::move(dimensions)), 
          init_val(std::move(init)),
          has_init(true) {}

    void Dump(int level = 0) const override {
        ArrayDefBaseAST::Dump(level);  // Call base Dump()
        if(has_init) {
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
        // Compute total size of array
        std::string total_size = "1";
        for(const auto& dim : dims) {
            int dim_size = dim->Calc();  // Use Calc() to get constant dimension size
//            std::cout << dim_size <<" endl\n";
            total_size = std::to_string(std::stoi(total_size) * dim_size);
        }
        
        // Generate IR for array allocation and initialization
        std::string var_ptr = "@" + ident;
        std::string var_nam = var_ptr + "_" + std::to_string(var_num[var_ptr]++);
        IR += "  " + var_nam + " = alloc [i32, " + total_size + "]\n";
        
        mySymboltable* topscope = scopeManager.top();
        topscope->insertSymbol(var_ptr, "array", "1", var_nam);
        topscope->insertSymbol(ident, "check", "3", var_nam);
        if (fun_nam[ident]){
            fl=1;
            std::cout << "Error! The array's name " << ident << " and function name are duplicated\n";
        }
        if (ident == "main"){
            fl=1;
            std::cout << "Error! The array's name cannot be 'main'\n";
        }

        if(has_init) {
            if(init_val){
                list_nam.push_back(var_ptr);
                list_length.push_back(std::stoi(total_size));
              //  std::cout<<glb_IR+IR;
                std::string nmb = init_val->dumpIR(tempVarCounter);
            }
            else{
                std::string arr_ptr = var_nam;
                for(int i=0; i < std::stoi(total_size); ++i){
                    std::string elem_ptr = "%" + std::to_string(tempVarCounter++);
                    IR += "  " + elem_ptr + " = getelemptr " + arr_ptr + ", " + std::to_string(i) + "\n";
                    IR += "  store 0, " + elem_ptr + "\n";
                }
                mySymboltable* topscope = scopeManager.top();
                topscope->insertSymbol(var_ptr, "array", "2", arr_ptr);
            }
          /*  for(int i=std::stoi(nmb)+1;i<=std::stoi(total_size);++i){
                std::string elem_ptr = "%" + std::to_string(tempVarCounter++);
                IR += "  " + elem_ptr + " = getelemptr " + var_nam + ", " + std::to_string(i-1) + "\n";
                IR += "  store 0, " + elem_ptr + "\n";
            }*/
          //  IR += nmb;
            // TODO: Deal with initialization
            // Need to traverse init_val and generate corresponding store instructions
        }
        return var_ptr;
    }

    virtual int Calc() const override{
        // Compute total size of array
        std::string total_size = "1";
        for(const auto& dim : dims) {
            int dim_size = dim->Calc();  // Use Calc() to get constant dimension size
            total_size = std::to_string(std::stoi(total_size) * dim_size);
        }
        
        // Generate IR for array allocation and initialization
        std::string var_ptr = "@" + ident;
        std::string var_nam = var_ptr + "_" + std::to_string(var_num[var_ptr]++);
        IR += "global " + var_nam + " = alloc [i32, " + total_size + "], ";
        
        mySymboltable* topscope = scopeManager.top();
        topscope->insertSymbol(var_ptr, "array", "1", var_nam);
        topscope->insertSymbol(ident, "check", "3", var_nam);
        if (fun_nam[ident]){
            fl=1;
            std::cout << "Error! The array's name " << ident << " and function name are duplicated\n";
        }
        if (ident == "main"){
            fl=1;
            std::cout << "Error! The array's name cannot be 'main'\n";
        }

        if(has_init) {
            list_nam.push_back(var_ptr);
            list_length.push_back(std::stoi(total_size));
            init_val->Calc();
          //  IR += nmb;
            // TODO: Deal with initialization
            // Need to traverse init_val and generate corresponding store instructions
        }
        else{
          IR += "zeroinit\n";
        }
        return 0;
    }
};
#endif