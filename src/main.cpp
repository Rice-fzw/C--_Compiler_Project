#include <cassert>
#include <cstdio>
#include <iostream>
#include <memory>
#include <string>
#include "AST.h"
#include "mylexer.h"

using namespace std;

extern int yyparse(unique_ptr<BaseAST> &ast);

int main(int argc, const char *argv[]) {
  assert(argc == 5);
  auto mode = argv[1];
  auto input = argv[2];
  auto output = argv[4];

  lexer = new Mylexer(input);

  unique_ptr<BaseAST> ast;
  auto ret = yyparse(ast);
  assert(!ret);

  ast->Dump();
  cout<<endl;

  delete lexer;
  return 0;
}
