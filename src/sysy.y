%code requires {
  #include <memory>
  #include <string>
  #include "AST.h"
}

%{

#include <iostream>
#include <memory>
#include <string>
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
%token INT RETURN 
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

%type <ast_val> FuncDef FuncType Block Stmt
%type <ast_val> Exp UnaryExp PrimaryExp MulExp AddExp
%type <str_val> UnaryOp Mulop Addop
%type <int_val> Number

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
  : '{' Stmt '}' {
    auto ast = new BlockAST();
    ast->stmt = unique_ptr<BaseAST>($2);
    $$ = ast;
  }
  ;

Stmt
  : RETURN Exp ';' {
    auto ast = new StmtAST();
    ast->stmt_type = "return";
    ast->exp = unique_ptr<BaseAST>($2);
    $$ = ast;
  }
  ;

Number
  : INT_CONST {
    $$ = $1;
  }
  ;

Exp
  : AddExp {
    $$ = $1;
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
%%

void yyerror(unique_ptr<BaseAST> &ast, const char *s) {
  cerr << "error: " << s << endl;
}