#include <cassert>
#include <cstdio>
#include <iostream>
#include <memory>
#include <string>
#include <fstream>
#include <sstream>
#include "IR.h"
#include "RISCV.h"
#include "lexer.h"

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
  if (ret) printf("Your code has syntax errors\n");
  assert(!ret);

  int tempVarCounter = 0;

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
  else if (string(mode) == "-riscv") {
    stringstream ss;
    streambuf* cout_buf = cout.rdbuf();
    cout.rdbuf(ss.rdbuf());
    ast->dumpIR(tempVarCounter);
    string ir_str = ss.str();
    const char *ir = ir_str.data();
    cout.rdbuf(cout_buf);
    if (fl == 1){
    //  ofstream out_file(output);  // open the output file
    //  out_file << ir_str;         // write the error message to the file
    //  out_file.close();
      std::cout << ir_str;
      delete lexer;
      return 0;
    }
  //  std :: cout << "IR is:\n"<<ir<<endl ;

    koopa_program_t program;
    koopa_error_code_t ret = koopa_parse_from_string(ir, &program);
    assert(ret == KOOPA_EC_SUCCESS);
    koopa_raw_program_builder_t builder = koopa_new_raw_program_builder();
    koopa_raw_program_t raw = koopa_build_raw_program(builder, program);
    koopa_delete_program(program);

    streambuf* cout_buf_riscv = cout.rdbuf();//store the current "cout" cache pointer
    stringstream ss_riscv;
    cout.rdbuf(ss_riscv.rdbuf());//redirect the "cout"

    Visit(raw);//deal with raw IR program
    koopa_delete_raw_program_builder(builder);

    string riscv_str = ss_riscv.str();
    const char *riscv = riscv_str.data();
    cout.rdbuf(cout_buf_riscv);//restore the "cout"
  //  std :: cout << riscv ;
    ofstream out_file(output);  // open the output file
    out_file << riscv_str;
    out_file.close();
  }
  else if (string(mode) == "-test") ast->Dump();
  delete lexer;
  return 0;
}