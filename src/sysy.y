%code requires {
  #include <memory>
  #include <string>
  #include <iostream>
  #include <vector>
  #include "AST.h"
}

%{
#include <memory>
#include <string>
#include <iostream>
#include <vector>
#include "AST.h"

// 声明 lexer 函数和错误处理函数
int yylex();
void yyerror(std::unique_ptr<BaseAST> &ast, const char *s);

using namespace std;

%}

%parse-param { std::unique_ptr<BaseAST> &ast }

%union {
  std::string *str_val; 
  int int_val;
  BaseAST *ast_val;
}

//关键字Token
%token INT RETURN CONST
//比较运算符Token
%token LE GE EQ NE
//逻辑运算符Token
%token LAND LOR
//优先级
%left LOR           // 最低优先级
%left LAND
%left EQ NE
%left '<' '>' LE GE
%left '+' '-'
%left '*' '/' '%'
%right '!'          // 最高优先级

%token <str_val> IDENT
%token <int_val> INT_CONST

%type <ast_val> FuncDef FuncType Block Stmt BlockItem BlockItems
%type <ast_val> Exp UnaryExp PrimaryExp MulExp AddExp
%type <ast_val> RelExp EqExp LAndExp LOrExp

%type <str_val> UnaryOp Mulop Addop
%type <int_val> Number
%type <ast_val> ConstDecl ConstDef ConstDefList ConstInitVal Decl ConstExp LVal
%type <ast_val> VarDecl VarDefList VarDef InitVal
%type <str_val> BType


%%

CompUnit
  : FuncDef {
    auto comp_unit = make_unique<CompUnitAST>();
    comp_unit->func_def = unique_ptr<BaseAST>($1);
    ast = move(comp_unit);
  }
  ;

FuncDef
  : FuncType IDENT '(' ')' Block {
    auto ast = new FuncDefAST();
    ast->func_type = unique_ptr<BaseAST>($1);
    ast->ident = *unique_ptr<string>($2);
    ast->block = unique_ptr<BaseAST>($5);
    $$ = ast;
  }
  ;

FuncType
  : INT {
    auto ast = new FuncTypeAST();
    ast->type = "int";
    $$ = ast;
  }
  ;

Block
  : '{' BlockItems '}' {
    $$ = $2;
  }
  | '{' '}' {  // deal with empty block
    $$ = new BlockAST();
  }
  ;

Stmt
  : RETURN Exp ';' {
    $$ = new StmtAST("return", unique_ptr<BaseAST>($2));
  }
  | LVal '=' Exp ';' {
    $$ = new StmtAST("assign", unique_ptr<BaseAST>($1), unique_ptr<BaseAST>($3));
  }
  ;

Number
  : INT_CONST {
    $$ = $1;
  }
  ;

Exp
  : LOrExp {
    $$ = $1;
  }
  ;

LOrExp
  : LAndExp {
    $$ = new LOrExpAST(unique_ptr<BaseAST>($1));
  }
  | LOrExp LOR LAndExp {
    $$ = new LOrExpAST("||", unique_ptr<BaseAST>($1), unique_ptr<BaseAST>($3));
  }
  ;

LAndExp
  : EqExp {
    $$ = new LAndExpAST(unique_ptr<BaseAST>($1));
  }
  | LAndExp LAND EqExp {
    $$ = new LAndExpAST("&&", unique_ptr<BaseAST>($1), unique_ptr<BaseAST>($3));
  }
  ;
  
EqExp
  : RelExp {
    $$ = new EqExpAST(unique_ptr<BaseAST>($1));
  }
  | EqExp EQ RelExp {
    $$ = new EqExpAST("==", unique_ptr<BaseAST>($1), unique_ptr<BaseAST>($3));
  }
  | EqExp NE RelExp {
    $$ = new EqExpAST("!=", unique_ptr<BaseAST>($1), unique_ptr<BaseAST>($3));
  }
  ;

RelExp
  : AddExp {
    $$ = new RelExpAST(unique_ptr<BaseAST>($1));
  }
  | RelExp '<' AddExp {
    $$ = new RelExpAST("<", unique_ptr<BaseAST>($1), unique_ptr<BaseAST>($3));
  }
  | RelExp '>' AddExp {
    $$ = new RelExpAST(">", unique_ptr<BaseAST>($1), unique_ptr<BaseAST>($3));
  }
  | RelExp LE AddExp {
    $$ = new RelExpAST("<=", unique_ptr<BaseAST>($1), unique_ptr<BaseAST>($3));
  }
  | RelExp GE AddExp {
    $$ = new RelExpAST(">=", unique_ptr<BaseAST>($1), unique_ptr<BaseAST>($3));
  }
  ;

AddExp
  : MulExp {
    $$ = new AddExpAST(unique_ptr<BaseAST>($1));
  }
  | AddExp Addop MulExp {
    $$ = new AddExpAST(*$2, unique_ptr<BaseAST>($1), unique_ptr<BaseAST>($3));
  }
  ;

MulExp
  : UnaryExp {
    $$ = new MulExpAST(unique_ptr<BaseAST>($1));
  }
  | MulExp Mulop UnaryExp {
    $$ = new MulExpAST(*$2, unique_ptr<BaseAST>($1), unique_ptr<BaseAST>($3));
  }
  ;

UnaryExp
  : PrimaryExp {
    $$ = $1;
  }
  | UnaryOp UnaryExp {
    auto ast = new UnaryExpAST();
    ast->op = *unique_ptr<string>($1);
    ast->exp = unique_ptr<BaseAST>($2);
    $$ = ast;
  }
  ;

PrimaryExp
: '(' Exp ')' {
  $$ = new PrimaryExpAST(unique_ptr<BaseAST>($2));
}
| Number {
  $$ = new PrimaryExpAST($1);
}
| LVal {
  $$ = new PrimaryExpAST(unique_ptr<BaseAST>($1), true); 
}

UnaryOp
  : '+' {
    $$ = new string("+");
  }
  | '-' {
    $$ = new string("-");
  }
  | '!' {
    $$ = new string("!");
  }

Addop
  : '+' {
    $$ = new string("+");
  }
  | '-' {
    $$ = new string("-");
  }
  ;

Mulop
  : '*' {
    $$ = new string("*");
  }
  | '/' {
    $$ = new string("/");
  }
  | '%' {
    $$ = new string("%");
  }
  ;

BlockItems
  : BlockItem {
    auto block = new BlockAST();
    block->items.push_back(unique_ptr<BaseAST>($1));
    $$ = block;
  }
  | BlockItems BlockItem {
    auto block = static_cast<BlockAST*>($1);
    block->items.push_back(unique_ptr<BaseAST>($2));
    $$ = block;
  }
  ;

BlockItem
  : Decl {
    $$ = $1;
  }
  | Stmt {
    $$ = $1;
  }
  ;

Decl
  : ConstDecl {
    $$ = $1;
  }
  | VarDecl {
    $$ = $1;
  }
  ;

ConstDecl
  :ConstDefList ';' {
    $$ = $1;  // Use ConstDefList as AST
  }
  ;

ConstDefList
  : CONST BType ConstDef {  // single variable: const int x = 1;
    std::vector<std::unique_ptr<ConstDefAST>> defs;
    defs.push_back(std::unique_ptr<ConstDefAST>(static_cast<ConstDefAST*>($3)));
    $$ = new ConstDeclAST(*$2, std::move(defs));
  }
  | ConstDefList ',' ConstDef {  // Multiple variables: const int x = 1, y = 2;
    auto decl = static_cast<ConstDeclAST*>($1);
    decl->const_defs.push_back(std::unique_ptr<ConstDefAST>(static_cast<ConstDefAST*>($3)));
    $$ = decl;
  }
  ;
BType
  : INT {
    $$ = new string("int");
  }
  ;

ConstDef
  : IDENT '=' ConstInitVal {
    $$ = new ConstDefAST("=", *$1, std::unique_ptr<BaseAST>($3));
  }
  ;

ConstInitVal 
  : ConstExp {
    $$ = $1;
  }
  ;

ConstExp
  : Exp {
    $$ = $1;
  }
  ;


LVal
  : IDENT {
    $$ = new LValAST(*$1);
  }
  ;

VarDecl
    : VarDefList ';' {
        $$ = $1; // Use VarDefList as AST
    }
    ;

VarDefList
    : BType VarDef { // Single variable: int x; int x = 1;
        std::vector<std::unique_ptr<VarDefAST>> defs;
        defs.push_back(std::unique_ptr<VarDefAST>(static_cast<VarDefAST*>($2)));
        $$ = new VarDeclAST(*$1, std::move(defs));
    }
    | VarDefList ',' VarDef { //Multiple variables: int x = 1, y = 2;
        auto decl = static_cast<VarDeclAST*>($1);
        decl->var_defs.push_back(std::unique_ptr<VarDefAST>(static_cast<VarDefAST*>($3)));
        $$ = decl;
    }
    ;

VarDef
    : IDENT {
        $$ = new VarDefAST(*$1);
    }
    | IDENT '=' InitVal {
        $$ = new VarDefAST("=", *$1, std::unique_ptr<BaseAST>($3));
    }
    ;

InitVal
    : Exp {
        $$ = $1;
    }
    ;
%%

void yyerror(unique_ptr<BaseAST> &ast, const char *s) {
  cerr << "error: " << s << endl;
}
