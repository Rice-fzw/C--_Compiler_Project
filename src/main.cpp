#include <cassert>
#include <cstdio>
#include <iostream>
#include <memory>
#include <string>
#include <fstream>
#include <sstream>
#include "AST.h"
#include "koopa.h"
#include "RISCV.h"
<<<<<<< HEAD
=======
#include "mylexer.h"
>>>>>>> IR-Generation

using namespace std;

extern int yyparse(unique_ptr<BaseAST> &ast);

int main(int argc, const char *argv[]) {
  assert(argc == 5);
  auto mode = argv[1];
  auto input = argv[2];
  auto output = argv[4];

  lexer = new Mylexer(input);
  assert(lexer);

  unique_ptr<BaseAST> ast;
  auto ret = yyparse(ast);
  assert(!ret);

  int tempVarCounter = 0;
<<<<<<< HEAD
  if (string(mode) == "-koopa") ast->dumpIR(tempVarCounter);
  else if (string(mode) == "-riscv" || string(mode) == "-perf")
  {
=======
  if (string(mode) == "-koopa") {
    stringstream ss;
    streambuf* cout_buf = cout.rdbuf();
    cout.rdbuf(ss.rdbuf());
    ast->dumpIR(tempVarCounter);
    string ir_str = ss.str();
    const char *ir = ir_str.data();
    cout.rdbuf(cout_buf);
  //  std :: cout << ir ;
    ofstream out_file(output);  // open the output file
    out_file << ir_str;         // write the IR string to the file
    out_file.close();
  }
  else if (string(mode) == "-riscv" || string(mode) == "-perf") {
>>>>>>> IR-Generation
    stringstream ss;
    streambuf* cout_buf = cout.rdbuf();
    cout.rdbuf(ss.rdbuf());
    ast->dumpIR(tempVarCounter);
    string ir_str = ss.str();
    const char *ir = ir_str.data();
    cout.rdbuf(cout_buf);
    std :: cout << "IR is:"<<ir<<endl ;
    koopa_program_t program;
    koopa_error_code_t ret = koopa_parse_from_string(ir, &program);
    assert(ret == KOOPA_EC_SUCCESS);
    koopa_raw_program_builder_t builder = koopa_new_raw_program_builder();
    koopa_raw_program_t raw = koopa_build_raw_program(builder, program);
    koopa_delete_program(program);
    Visit(raw);//deal with raw IR program
    koopa_delete_raw_program_builder(builder);
<<<<<<< HEAD

  }

=======
  }
  delete lexer;
>>>>>>> IR-Generation
  return 0;
}