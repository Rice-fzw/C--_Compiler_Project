#ifndef _RISVC_H_
#define _RISVC_H_

#include "simplified_llvm.h"

// assume all the memory size of pointers and values are i32 (4 bytes)

int AllocateStackForVariable(const koopa_raw_value_t& var);
void StackSize(const koopa_raw_function_t &funs);
int TypeSize(const koopa_raw_type_t& ty);

void Visit(const koopa_raw_program_t &raw);
void Visit(const koopa_raw_slice_t &slice);
void Visit(const koopa_raw_function_t &func);
void Visit(const koopa_raw_basic_block_t &bb);
std::pair<int,std::string> Visit(const koopa_raw_value_t &value);
std::string Visit(const koopa_raw_load_t &load);
void Visit(const koopa_raw_store_t &store);
void Visit(const koopa_raw_return_t &ret);
std::string Visit(const koopa_raw_binary_t &bin);
void Visit(const koopa_raw_branch_t &bran);
void Visit(const koopa_raw_call_t &call);
std::pair<std::string,int> Visit(const koopa_raw_global_alloc_t &glo);
int Visit(const koopa_raw_aggregate_t &agg);
std::string Visit(const koopa_raw_get_elem_ptr_t &ptr);

std::string ValueToReg(std::pair<int,std::string> ini);
void WriteToAddress(std::string reg, int addr);
void ReadFromAddress(std::string reg, int addr);
std::string New_reg();
bool ValidStack(int sta);


#endif