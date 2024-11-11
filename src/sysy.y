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

%token INT RETURN LE GE EQ NE LAND LOR
%token <str_val> IDENT
%token <int_val> INT_CONST

%type <ast_val> FuncDef FuncType Block Stmt
%type <ast_val> Exp UnaryExp PrimaryExp MulExp AddExp
%type <ast_val> RelExp EqExp LAndExp LOrExp
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
  : LOrExp {
    $$ = $1;
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

LOrExp
  : LAndExp {
    $$ = new LOrExpAST(unique_ptr<BaseAST>($1));
  }
  | LOrExp LOR LAndExp {
    $$ = new LOrExpAST(unique_ptr<BaseAST>($1), unique_ptr<BaseAST>($3));
  }
  ;

LAndExp
  : EqExp {
    $$ = new LAndExpAST(unique_ptr<BaseAST>($1));
  }
  | LAndExp LAND EqExp {
    $$ = new LAndExpAST(unique_ptr<BaseAST>($1), unique_ptr<BaseAST>($3));
  }
  ;
%%

void yyerror(unique_ptr<BaseAST> &ast, const char *s) {
  cerr << "error: " << s << endl;
}
