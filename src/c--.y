%debug
%define parse.error verbose 

%code requires {
  #include <memory>
  #include <string>
  #include <iostream>
  #include <vector>
  #include "IR.h"
  #include "lexer.h"
}

%{
#include <memory>
#include <string>
#include <iostream>
#include <vector>
#include "IR.h"
#include "lexer.h"

//Declear lexer function and error function
int yylex();
void yyerror(std::unique_ptr<BaseAST> &ast, const char *s);
extern YYSTYPE yylval;
extern int yydebug;

using namespace std;

%}

%parse-param { std::unique_ptr<BaseAST> &ast }

%union {
  std::string *str_val; 
  int int_val;
  BaseAST *ast_val;
  std::vector<std::unique_ptr<BaseAST>> *vec_val;
}

//Keyword Token
%token INT RETURN CONST VOID
%token IF ELSE WHILE FOR BREAK CONTINUE
//Comparison Operator Tokens
%token LE GE EQ NE
//Logical Operator Tokens
%token LAND LOR
//Bitwise Operator Tokens
%token SHL SAR
//Increment/Decrement Operator Tokens
%token AA MM
// += -= *= /=
%token AE ME UE DE
//Precedence Rules
%right '=' AE ME UE DE OE // = += -= *= /= %=
%left LOR           // ||
%left LAND          // &&
%left '|'
%left '^'
%left '&'
%left EQ NE         // == !=
%left '<' '>' LE GE // <= >=
%left SHL SAR       // << >>
%left '+' '-'       // plus minus 
%left '*' '/' '%'
%right '!'
%nonassoc PRE_AA PRE_MM    // prefix ++/--, no associativity
%nonassoc POST_AA POST_MM   // postfix ++/--, no associativity

%start CompUnit  // specify the start rule

%token <str_val> IDENT
%token <int_val> INT_CONST
%token <str_val> STRING_LITERAL

%type <ast_val> FuncDef FuncType CompUnitItem Block Stmt BlockItem BlockItems
%type <ast_val> Exp AssignExp UnaryExp PrimaryExp MulExp AddExp
%type <ast_val> RelExp EqExp LAndExp LOrExp LVal
%type <ast_val> BitOrExp BitXorExp BitAndExp ShiftExp
%type <ast_val> OptionalExp
%type <ast_val> ForInit
%type <str_val> Mulop Addop
%type <int_val> Number
%type <ast_val> ConstDecl ConstDef ConstDefList ConstInitVal Decl ConstExp
%type <ast_val> VarDecl VarDefList VarDef InitVal
%type <ast_val> FuncFParam FuncFParams FuncRParams
%type <ast_val> InitValList
%type <str_val> BType

%type <vec_val> ConstExpList


%%

CompUnit
  : CompUnitItem {
      auto comp_unit = new CompUnitAST();
      // Add to corresponding vector by type
      if (auto* decl = dynamic_cast<ConstDeclAST*>($1)) {
          comp_unit->addDecl($1);
      } else if (auto* decl = dynamic_cast<VarDeclAST*>($1)) {
          comp_unit->addDecl($1);
      } else {
          comp_unit->addFuncDef($1);
      }
      ast = std::unique_ptr<BaseAST>(comp_unit);
  }
  | CompUnit CompUnitItem {
      auto comp_unit = static_cast<CompUnitAST*>(ast.get());
      // Add to corresponding vector by type
      if (auto* decl = dynamic_cast<ConstDeclAST*>($2)) {
          comp_unit->addDecl($2);
      } else if (auto* decl = dynamic_cast<VarDeclAST*>($2)) {
          comp_unit->addDecl($2);
      } else {
          comp_unit->addFuncDef($2);
      }
  }
  ;

CompUnitItem
  : Decl {
      $$ = $1;
  }
  | FuncDef {
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
  | IDENT '[' ConstExp ']' '=' ConstInitVal {
    std::vector<std::unique_ptr<BaseAST>> dims;
    dims.push_back(std::unique_ptr<BaseAST>($3));
    $$ = new ConstArrayDefAST(*$1, std::move(dims), std::unique_ptr<BaseAST>($6));
    delete $1;
  }

  ;

ConstInitVal 
  : ConstExp {
    $$ = $1;
  }
  | '{' '}' {
    std::vector<std::unique_ptr<BaseAST>> empty_elements;
    $$ = new ArrayInitValAST(std::move(empty_elements), true);
  }
  | '{' ConstExpList '}' {
    $$ = new ArrayInitValAST(std::move(*($2)), true);
    delete $2;
  }
  ;

ConstExpList
  : ConstExp {
    auto list = new std::vector<std::unique_ptr<BaseAST>>();
    list->push_back(std::unique_ptr<BaseAST>($1));
    $$ = list;
  }
  | ConstExpList ',' ConstExp {
      $1->push_back(std::unique_ptr<BaseAST>($3));
      $$ = $1;
  }
  | ConstExpList ',' {
      $$ = $1;
  }
  ;

VarDecl
  : BType VarDefList ';' {
      $$ = $2; // Use VarDefList as AST
  }
  ;

VarDefList
  : VarDef { // Single variable: int x; int x = 1;
      std::vector<std::unique_ptr<VarDefAST>> defs;
      defs.push_back(std::unique_ptr<VarDefAST>(static_cast<VarDefAST*>($1)));
      $$ = new VarDeclAST("int", std::move(defs));
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
  | IDENT '[' ConstExp ']' {
      std::vector<std::unique_ptr<BaseAST>> dims;
      dims.push_back(std::unique_ptr<BaseAST>($3));
      $$ = new VarArrayDefAST(*$1, std::move(dims));
      delete $1;
  }
  | IDENT '[' ConstExp ']' '=' InitVal {
      std::vector<std::unique_ptr<BaseAST>> dims;
      dims.push_back(std::unique_ptr<BaseAST>($3));
      $$ = new VarArrayDefAST(*$1, std::move(dims), std::unique_ptr<BaseAST>($6));
      delete $1;
  }
  ;

InitVal
  : Exp {
      $$ = $1;
  }
  | '{' '}' {
    std::vector<std::unique_ptr<BaseAST>> empty_elements;
    $$ = new ArrayInitValAST(std::move(empty_elements), false);
  }
  | '{' InitValList '}' {
    $$ = $2;
  }
  ;

InitValList
  : InitVal {
    std::vector<std::unique_ptr<BaseAST>> elements;
    elements.push_back(std::unique_ptr<BaseAST>($1));
    $$ = new ArrayInitValAST(std::move(elements), false);
  } 
  | InitValList ',' InitVal {
      auto list = static_cast<ArrayInitValAST*>($1);
      list->elements.push_back(std::unique_ptr<BaseAST>($3));
      $$ = list;
  }
  | InitValList ',' {
      $$ = $1;
  }
  ;

FuncDef
  : BType IDENT '(' ')' Block {
    $$ = new FuncDefAST(std::unique_ptr<BaseAST>(new FuncTypeAST(*($1))), *$2, std::unique_ptr<BaseAST>($5));
  }
  | BType IDENT '(' ')' Block ';' {
  $$ = new FuncDefAST(std::unique_ptr<BaseAST>(new FuncTypeAST(*($1))), *$2, std::unique_ptr<BaseAST>($5));
  }
  | BType IDENT '(' FuncFParams ')' Block {
    $$ = new FuncDefAST(std::unique_ptr<BaseAST>(new FuncTypeAST(*($1))), *$2, std::unique_ptr<FuncFParamListAST>(static_cast<FuncFParamListAST*>($4)), std::unique_ptr<BaseAST>($6));
  }
  | BType IDENT '(' FuncFParams ')' Block ';' {
    $$ = new FuncDefAST(std::unique_ptr<BaseAST>(new FuncTypeAST(*($1))), *$2, std::unique_ptr<FuncFParamListAST>(static_cast<FuncFParamListAST*>($4)), std::unique_ptr<BaseAST>($6));
  }
  | VOID IDENT '(' ')' Block {
    $$ = new FuncDefAST(std::unique_ptr<BaseAST>(new FuncTypeAST("void")), *$2, std::unique_ptr<BaseAST>($5));
  }
  | VOID IDENT '(' ')' Block ';' {
    $$ = new FuncDefAST(std::unique_ptr<BaseAST>(new FuncTypeAST("void")), *$2, std::unique_ptr<BaseAST>($5));
  }
  | VOID IDENT '(' FuncFParams ')' Block {
    $$ = new FuncDefAST(std::unique_ptr<BaseAST>(new FuncTypeAST("void")), *$2, std::unique_ptr<FuncFParamListAST>(static_cast<FuncFParamListAST*>($4)), std::unique_ptr<BaseAST>($6));
  }
  | VOID IDENT '(' FuncFParams ')' Block ';' {
    $$ = new FuncDefAST(std::unique_ptr<BaseAST>(new FuncTypeAST("void")), *$2, std::unique_ptr<FuncFParamListAST>(static_cast<FuncFParamListAST*>($4)), std::unique_ptr<BaseAST>($6));
  }
  | BType IDENT '(' ')' ';' {
    auto empty_block = new BlockAST();
    $$ = new FuncDefAST(std::unique_ptr<BaseAST>(new FuncTypeAST(*($1))), *$2, std::unique_ptr<BaseAST>(empty_block));
  }
  | BType IDENT '(' FuncFParams ')' ';' {
    auto empty_block = new BlockAST();
    $$ = new FuncDefAST(std::unique_ptr<BaseAST>(new FuncTypeAST(*($1))), *$2, std::unique_ptr<FuncFParamListAST>(static_cast<FuncFParamListAST*>($4)), std::unique_ptr<BaseAST>(empty_block));
  }
  | VOID IDENT '(' ')' ';' {
    auto empty_block = new BlockAST();
    $$ = new FuncDefAST(std::unique_ptr<BaseAST>(new FuncTypeAST("void")), *$2, std::unique_ptr<BaseAST>(empty_block));
  }
  | VOID IDENT '(' FuncFParams ')' ';' {
    auto empty_block = new BlockAST();
    $$ = new FuncDefAST(std::unique_ptr<BaseAST>(new FuncTypeAST("void")), *$2, std::unique_ptr<FuncFParamListAST>(static_cast<FuncFParamListAST*>($4)), std::unique_ptr<BaseAST>(empty_block));
  }
  ;

FuncType
  : INT {
    $$ = new FuncTypeAST("int");
  }
  | VOID {
    $$ = new FuncTypeAST("void");
  }
  ;

FuncFParams
  : FuncFParam {
      auto param_list = new FuncFParamListAST(std::vector<std::unique_ptr<FuncFParamAST>>());
      param_list->params.push_back(std::unique_ptr<FuncFParamAST>(static_cast<FuncFParamAST*>($1)));
      $$ = param_list;
  }
  | FuncFParams ',' FuncFParam {
      auto param_list = static_cast<FuncFParamListAST*>($1);
      param_list->params.push_back(std::unique_ptr<FuncFParamAST>(static_cast<FuncFParamAST*>($3)));
      $$ = param_list;
  }
  ;

FuncFParam
  : BType IDENT {
      $$ = new FuncFParamAST(*$1, *$2);
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

Stmt
  : RETURN OptionalExp ';' {
      $$ = StmtAST::makeReturn($2);
  }
  | LVal '=' Exp ';' {
      $$ = StmtAST::makeAssign($1, $3);
  }
  | OptionalExp ';' {
      $$ = StmtAST::makeExpression($1);
  }
  | Block {
      $$ = StmtAST::makeBlock($1);
  }
  | IF '(' Exp ')' Stmt {  // if without else
      $$ = new IfStmtAST($3, $5);
  }
  | IF '(' Exp ')' Stmt ELSE Stmt {  // if with else
      $$ = new IfStmtAST($3, $5, $7);
  }
  | WHILE '(' Exp ')' Stmt {
  $$ = new WhileStmtAST($3, $5);
  }
  | BREAK ';' {
      $$ = StmtAST::makeBreak();
  }
  | CONTINUE ';' {
      $$ = StmtAST::makeContinue();
  }
  | FOR '(' ForInit OptionalExp ';' OptionalExp ')' Stmt {
    $$ = new ForStmtAST($3, $4, $6, $8);
  }
  ;

ForInit
  : OptionalExp ';'{
      $$ = $1;
  }
  | Decl {
      $$ = $1;
  }
  ;

OptionalExp
  : /* empty */ {
      $$ = nullptr;
  }
  | Exp {
      $$ = $1;
  }
  ;

Exp
  : LOrExp {
    $$ = $1;
  }
  | AssignExp {
    $$ = $1;
  }
  ;

AssignExp
  : LVal '=' Exp {
    $$ = StmtAST::makeAssign($1, $3);
  }
  | LVal AE Exp {
    auto lval_copy = new LValAST(static_cast<LValAST*>($1)->ident);
    auto add_exp = new AddExpAST("+", std::unique_ptr<BaseAST>(lval_copy), std::unique_ptr<BaseAST>($3));
    $$ = StmtAST::makeAssign($1, add_exp);
  }
  | LVal ME Exp {
    auto lval_copy = new LValAST(static_cast<LValAST*>($1)->ident);
    auto sub_exp = new AddExpAST("-", std::unique_ptr<BaseAST>(lval_copy), std::unique_ptr<BaseAST>($3));
    $$ = StmtAST::makeAssign($1, sub_exp);
  }
  | LVal UE Exp {
    auto lval_copy = new LValAST(static_cast<LValAST*>($1)->ident);
    auto mul_exp = new MulExpAST("*", std::unique_ptr<BaseAST>(lval_copy), std::unique_ptr<BaseAST>($3));
    $$ = StmtAST::makeAssign($1, mul_exp);
  }
  | LVal DE Exp {
    auto lval_copy = new LValAST(static_cast<LValAST*>($1)->ident);
    auto div_exp = new MulExpAST("/", std::unique_ptr<BaseAST>(lval_copy), std::unique_ptr<BaseAST>($3));
    $$ = StmtAST::makeAssign($1, div_exp);
  }
  | LVal OE Exp {
  auto lval_copy = new LValAST(static_cast<LValAST*>($1)->ident);
  auto mod_exp = new MulExpAST("%", std::unique_ptr<BaseAST>(lval_copy), std::unique_ptr<BaseAST>($3));
  $$ = StmtAST::makeAssign($1, mod_exp);
  }
  ;

LVal
  : IDENT {
    $$ = new LValAST(*$1);
    delete $1;
  }
  | IDENT '[' Exp ']' { /* Visiting one demension array */
    std::vector<std::unique_ptr<BaseAST>> indices;
    indices.push_back(std::unique_ptr<BaseAST>($3));
    $$ = new ArrayAccessAST(*$1, std::move(indices));
    delete $1;
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
    $$ = new PrimaryExpAST($1); 
  }
  ;

Number
  : INT_CONST {
    $$ = $1;
  }
  ;

UnaryExp
  : PrimaryExp {
    $$ = $1;
  }
  | '+' UnaryExp %prec '!' {  // precedence same as !
    $$ = new UnaryExpAST("+", std::unique_ptr<BaseAST>($2));
  }
  | '-' UnaryExp %prec '!' {  // precedence same as !
    $$ = new UnaryExpAST("-", std::unique_ptr<BaseAST>($2));
  }
  | '!' UnaryExp {
    $$ = new UnaryExpAST("!", std::unique_ptr<BaseAST>($2));
  }
  | AA UnaryExp %prec PRE_AA {
    $$ = new UnaryExpAST("++", std::unique_ptr<BaseAST>($2));
  }
  | MM UnaryExp %prec PRE_MM {
    $$ = new UnaryExpAST("--", std::unique_ptr<BaseAST>($2));
  }
  | UnaryExp AA %prec POST_AA {
    $$ = new UnaryExpAST("post++", std::unique_ptr<BaseAST>($1));
  }
  | UnaryExp MM %prec POST_MM {
    $$ = new UnaryExpAST("post--", std::unique_ptr<BaseAST>($1));
  }
  | IDENT '(' FuncRParams ')' {
      $$ = new UnaryExpAST(*$1, std::unique_ptr<FuncRParamsAST>(static_cast<FuncRParamsAST*>($3)));
  }
  | IDENT '(' ')' { 
      $$ = new UnaryExpAST(*$1); 
  }
  ;

FuncRParams
  : Exp {
      // single parameter
      auto params = new FuncRParamsAST(std::vector<std::unique_ptr<BaseAST>>());
      params->params.push_back(std::unique_ptr<BaseAST>($1));
      $$ = params;
  }
  | STRING_LITERAL {
    auto params = new FuncRParamsAST(std::vector<std::string>());
    params->str_params.push_back(*$1);
    delete $1;
    $$ = params;
  }
  | FuncRParams ',' Exp {
      // Multiple parameter
      auto params = static_cast<FuncRParamsAST*>($1);
      params->params.push_back(std::unique_ptr<BaseAST>($3));
      $$ = params;
  }
  | FuncRParams '+' STRING_LITERAL {
      auto params = static_cast<FuncRParamsAST*>($1);
      params->str_params.push_back(*$3);
      $$ = params;
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

AddExp
  : MulExp {
    $$ = new AddExpAST(unique_ptr<BaseAST>($1));
  }
  | AddExp Addop MulExp {
    $$ = new AddExpAST(*$2, unique_ptr<BaseAST>($1), unique_ptr<BaseAST>($3));
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

ShiftExp
  : AddExp {
    $$ = new ShiftExpAST(unique_ptr<BaseAST>($1));
  }
  | ShiftExp SHL AddExp {
    $$ = new ShiftExpAST("<<", unique_ptr<BaseAST>($1), unique_ptr<BaseAST>($3));
  }
  | ShiftExp SAR AddExp {
    $$ = new ShiftExpAST(">>", unique_ptr<BaseAST>($1), unique_ptr<BaseAST>($3));
  }
  ;

RelExp
  : ShiftExp {
    $$ = new RelExpAST(unique_ptr<BaseAST>($1));
  }
  | RelExp '<' ShiftExp {
    $$ = new RelExpAST("<", unique_ptr<BaseAST>($1), unique_ptr<BaseAST>($3));
  }
  | RelExp '>' ShiftExp {
    $$ = new RelExpAST(">", unique_ptr<BaseAST>($1), unique_ptr<BaseAST>($3));
  }
  | RelExp LE ShiftExp {
    $$ = new RelExpAST("<=", unique_ptr<BaseAST>($1), unique_ptr<BaseAST>($3));
  }
  | RelExp GE ShiftExp {
    $$ = new RelExpAST(">=", unique_ptr<BaseAST>($1), unique_ptr<BaseAST>($3));
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

BitAndExp
  : EqExp {
    $$ = new BitExpAST(unique_ptr<BaseAST>($1));
  }
  | BitAndExp '&' EqExp {
    $$ = new BitExpAST("&", unique_ptr<BaseAST>($1), unique_ptr<BaseAST>($3));
  }
  ;

BitXorExp
  : BitAndExp {
    $$ = new BitExpAST(unique_ptr<BaseAST>($1));
  }
  | BitXorExp '^' BitAndExp {
    $$ = new BitExpAST("^", unique_ptr<BaseAST>($1), unique_ptr<BaseAST>($3));
  }
  ;

BitOrExp
  : BitXorExp {
    $$ = new BitExpAST(unique_ptr<BaseAST>($1));
  }
  | BitOrExp '|' BitXorExp {
    $$ = new BitExpAST("|", unique_ptr<BaseAST>($1), unique_ptr<BaseAST>($3));
  }
  ;

LAndExp
  : BitOrExp {
    $$ = new LAndExpAST(unique_ptr<BaseAST>($1));
  }
  | LAndExp LAND BitOrExp {
    $$ = new LAndExpAST("&&", unique_ptr<BaseAST>($1), unique_ptr<BaseAST>($3));
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

ConstExp
  : Exp {
    $$ = $1;
  }
  ;
%%

void yyerror(unique_ptr<BaseAST> &ast, const char *s) {
  cerr << "error: " << s << endl;
}