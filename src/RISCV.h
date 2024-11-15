#include <iostream>
#include <unordered_map>
#include "koopa.h"

void Visit(const koopa_raw_program_t &raw);
void Visit(const koopa_raw_slice_t &slice);
void Visit(const koopa_raw_function_t &funs);
void Visit(const koopa_raw_basic_block_t &bb);
void Visit(const koopa_raw_value_t &value);

void Visit(const koopa_raw_program_t &raw){
/*
    deal with raw IR program
    currently:
        raw program -> functions and global variables
*/
//    std::cout<<"here!"<<std::endl;
    std::cout<<"  "<<".text"<<std::endl;
    Visit(raw.values);//koopa_raw_slice_t, not begin yet
    Visit(raw.funcs);//koopa_raw_slice_t
}

void Visit(const koopa_raw_slice_t &slice){
//    std::cout<<"here1!"<<std::endl;
    switch(slice.kind){
        case KOOPA_RSIK_FUNCTION://functions
            for(size_t i=0;i<slice.len;i++){//list all functions
                Visit(reinterpret_cast<koopa_raw_function_t>(slice.buffer[i]));//reinterpret_cast"允许将指针或引用的类型转换为完全不同的类型，即使两者之间没有关联，且不进行类型检查，而是基于位模式进行转换"
            }
            break;
        case KOOPA_RSIK_BASIC_BLOCK://basic block
            for(size_t i=0;i<slice.len;i++){//list all basic blocks
                Visit(reinterpret_cast<koopa_raw_basic_block_t>(slice.buffer[i]));
            }
            break;
        case KOOPA_RSIK_VALUE://values
            for(size_t i=0;i<slice.len;i++){//list all instructions in this basic block.
                Visit(reinterpret_cast<koopa_raw_value_t>(slice.buffer[i]));
            }
            break;
        default:
            assert(false);//???other types
    }
}

void Visit(const koopa_raw_function_t &func){
/*
    deal with functions
    currently:
        functions-> basic blocks
*/
    std::string func_name = func->name;
    if (!func_name.empty() && func_name[0] == '@') {
        func_name = func_name.substr(1); //remove "@"
    }
    std::cout << "  " << ".globl " << func_name << std::endl;  // output the global tag
    std::cout << func_name << ":" << std::endl;  //output the function name
    Visit(func->bbs);//koopa_raw_slice_t
}

void Visit(const koopa_raw_basic_block_t &bb){
/*
    deal with basic blocks
    currently:
        basic blocks -> values
*/
//    std::cout<<"here3!"<<std::endl;
    Visit(bb->insts);//koopa_raw_slice_t
}

std::unordered_map<koopa_raw_value_t, std::string> value_to_reg;
std::unordered_map<int32_t, std::string> int_to_reg;
int temp_reg = 0;

void Visit(const koopa_raw_value_t &value){
/*
    deal with raw a value
    currently:
        "return": value is represented to the return value(int)
*/
//    std::cout<<"here4!"<<std::endl;
    const auto &kind = value->kind;
    int32_t int_val;
    std::string reg, ret_reg, lhs_reg, rhs_reg;

    switch(kind.tag){
        case KOOPA_RVT_RETURN://return
            if (kind.data.ret.value->kind.tag == KOOPA_RVT_INTEGER){
                std::cout << "  " << "li a0, " << kind.data.ret.value->kind.data.integer.value << std::endl;   
            }
            else{
                Visit(kind.data.ret.value);//get return value
                ret_reg = value_to_reg[kind.data.ret.value];
                std::cout << "  " << "mv a0, " << ret_reg << std::endl; //use the last register
            }
            std::cout << "  "<<"ret" << std::endl; // Return from function
            break;
        case KOOPA_RVT_INTEGER:
            int_val=kind.data.integer.value;
            if (int_val == 0){
                int_to_reg[int_val] = "x0";
                break;
            }else{
                reg = "t" + std::to_string(temp_reg++);
                int_to_reg[int_val] = reg;
                std::cout << "  " << "li " << reg << ", " << int_val << std::endl;
            }
            break;

        case KOOPA_RVT_BINARY:
            if (value_to_reg.find(value) != value_to_reg.end()) {
                // If the value has already been processed, avoid reprocessing
                break;
            }

            Visit(kind.data.binary.lhs);
            Visit(kind.data.binary.rhs);
            if (kind.data.binary.lhs->kind.tag == KOOPA_RVT_INTEGER) {
                lhs_reg = int_to_reg[kind.data.binary.lhs->kind.data.integer.value];
            } else {
                lhs_reg = value_to_reg[kind.data.binary.lhs];
            }
            if (kind.data.binary.rhs->kind.tag == KOOPA_RVT_INTEGER) {
                rhs_reg = int_to_reg[kind.data.binary.rhs->kind.data.integer.value];
            } else {
                rhs_reg = value_to_reg[kind.data.binary.rhs];
            }

            switch (kind.data.binary.op){
                case KOOPA_RBO_ADD://addition operation
                    reg = "t" + std::to_string(temp_reg++);
                    value_to_reg[value] = reg;
                    std::cout << "  " << "add " << reg << ", " << lhs_reg << ", " << rhs_reg << std::endl;
                    break;
                case KOOPA_RBO_SUB://substraction operation
                    reg = "t" + std::to_string(temp_reg++);
                    value_to_reg[value] = reg;                
                    std::cout << "  " << "sub " << reg << ", " << lhs_reg << ", " << rhs_reg << std::endl;
                    break;
                case KOOPA_RBO_MUL://multiplication operation
                    reg = "t" + std::to_string(temp_reg++);
                    value_to_reg[value] = reg;                
                    std::cout << "  " << "mul " << reg << ", " << lhs_reg << ", " << rhs_reg << std::endl;
                    break;
                case KOOPA_RBO_DIV://division operation
                    reg = "t" + std::to_string(temp_reg++);
                    value_to_reg[value] = reg;                
                    std::cout << "  " << "div " << reg << ", " << lhs_reg << ", " << rhs_reg << std::endl;
                    break;
                case KOOPA_RBO_MOD://mod operation
                    reg = "t" + std::to_string(temp_reg++);
                    value_to_reg[value] = reg;                
                    std::cout << "  " << "mod " << reg << ", " << lhs_reg << ", " << rhs_reg << std::endl;
                    break;
                case KOOPA_RBO_EQ://NOT operation
                    reg = "t" + std::to_string(--temp_reg);//compare the same element
                    temp_reg++;
                    value_to_reg[value] = reg;                
                    std::cout << "  " << "xor " << reg << ", " << lhs_reg << ", " << rhs_reg << std::endl;
                    std::cout << "  " << "seqz " << reg << ", " << reg << std::endl;
                    break;
            }
            break;
        
        default:
            std::cout << "Unhandled operation: " << kind.tag << std::endl;
            assert(false);//Unsupported types
            break;
    }
}
