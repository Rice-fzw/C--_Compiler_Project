#include <iostream>
#include <unordered_map>
#include "koopa.h"

int var_flag = 0;
int sp_offset = 0; //sp of the whole stack
int koo_reg_num = 0;
std::unordered_map<std::string, int> var_offset;
std::unordered_map<koopa_raw_value_t, std::string> koo_reg;

int temp_reg = 0;
int val_reg = 0;
int aligned_stack_size = 0;
std::string true_bb, false_bb, target_name;
std::unordered_map<int32_t, std::string> int_to_reg;
std::unordered_map<koopa_raw_value_t, std::string> value_to_reg;

void CalculateStackSize(const koopa_raw_program_t &raw);
void VisitStack(const koopa_raw_slice_t &slice);
void VisitStack(const koopa_raw_function_t &funs);
void VisitStack(const koopa_raw_basic_block_t &bb);
void VisitStack(const koopa_raw_value_t &value);

void AllocateStackForVariable(const std::string& var){
    if (var_offset.find(var) == var_offset.end()) {
        var_offset[var] = sp_offset;
        //std::cout << var << ": " << sp_offset << " bytes" << std::endl;
        sp_offset += 4; //each variable or register will be assigned 4 bytes
    }
}

void CalculateStackSize(const koopa_raw_program_t &raw){
    VisitStack(raw.values);//koopa_raw_slice_t, not begin yet
    VisitStack(raw.funcs);//koopa_raw_slice_t
    koo_reg_num = 0;
    aligned_stack_size = ((sp_offset + 15) / 16) * 16;
}
void VisitStack(const koopa_raw_slice_t &slice){
        switch(slice.kind){
            case KOOPA_RSIK_FUNCTION:
                for(size_t i=0;i<slice.len;i++){
                    VisitStack(reinterpret_cast<koopa_raw_function_t>(slice.buffer[i]));
                }
                break;
            case KOOPA_RSIK_BASIC_BLOCK:
                for(size_t i=0;i<slice.len;i++){
                    VisitStack(reinterpret_cast<koopa_raw_basic_block_t>(slice.buffer[i]));
                }
                break;
            case KOOPA_RSIK_VALUE:
                for(size_t i=0;i<slice.len;i++){
                    VisitStack(reinterpret_cast<koopa_raw_value_t>(slice.buffer[i]));
                }
                break;
            default:
                assert(false);
        }
}
void VisitStack(const koopa_raw_function_t &funs){
    VisitStack(funs->bbs);
}
void VisitStack(const koopa_raw_basic_block_t &bb){
    VisitStack(bb->insts);
}
void VisitStack(const koopa_raw_value_t &value){
    const auto &kind = value->kind;
    std::string reg, val_name;
    switch(kind.tag){
        case KOOPA_RVT_ALLOC:            
            val_name = value->name;
            if (val_name[0] == '%'){
                koo_reg_num++;
            }else if (val_name[0] == '@'){
                var_flag = 1;
            }
            koo_reg[value] = value->name;
            AllocateStackForVariable(val_name);
            break;
        case KOOPA_RVT_LOAD:
        case KOOPA_RVT_BINARY:
            reg = "%" + std::to_string(koo_reg_num++);
            koo_reg[value] = reg;
            AllocateStackForVariable(reg);
            break;
        case KOOPA_RVT_STORE:
        case KOOPA_RVT_RETURN:
        case KOOPA_RVT_BRANCH:
        case KOOPA_RVT_JUMP:
            break;
        default:
            std::cout << "Unhandled visitStack operation: " << kind.tag << std::endl;
            assert(false);//Unsupported types
            break;
    }
}


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
    Visit(raw.values);//koopa_raw_slice_t
    Visit(raw.funcs);//koopa_raw_slice_t

}

void Visit(const koopa_raw_slice_t &slice){
    switch(slice.kind){
        case KOOPA_RSIK_FUNCTION://functions
            for(size_t i=0;i<slice.len;i++){//list all functions
                Visit(reinterpret_cast<koopa_raw_function_t>(slice.buffer[i]));//reinterpret_cast
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
            assert(false);//other types
    }
}

void Visit(const koopa_raw_function_t &func){
/*
    deal with functions
    currently:
        functions-> basic blocks
*/
    std::cout << "  " << ".text" << std::endl;
    std::string func_name = func->name;
    if (!func_name.empty() && func_name[0] == '@') {
        func_name = func_name.substr(1); //remove "@"
    }
    std::cout << "  " << ".global " << func_name << std::endl;  // output the global tag
    std::cout << func_name << ":" << std::endl;  //output the function name
    if(var_flag == 1){
        //std::cout << "Aligned stack size: " << aligned_stack_size << " bytes" << std::endl;
        //std::cout << "Length of map: " << var_offset.size() << std::endl;
        std::cout << "  " << "addi " <<  "sp, " << "sp, " << "-" + std::to_string(aligned_stack_size) << std::endl;
    }

    Visit(func->bbs);//koopa_raw_slice_t
}

void Visit(const koopa_raw_basic_block_t &bb){
/*
    deal with basic blocks
    currently:
        basic blocks -> values
*/
//    std::cout<<"here3!"<<std::endl;
    std::string bb_name = bb->name;
    if (!bb_name.empty() && bb_name[0] == '%'){
        bb_name = bb_name.substr(1); //remove "%"
    }
    std::cout << bb_name << ":" << std::endl;  //output the basic block name
    Visit(bb->insts);//koopa_raw_slice_t
}

void Visit(const koopa_raw_value_t &value){
/*
    deal with raw a value
    currently:
        "return": value is represented to the return value(int)
*/
//    std::cout<<"here4!"<<std::endl;
    const auto &kind = value->kind;
    int32_t int_val;
    int lw_sta_fra, sw_sta_fra;
    std::string reg, ret_reg, lhs_reg, rhs_reg, lw_sf_reg, sw_sf_reg;

    switch(kind.tag){
        case KOOPA_RVT_ALLOC:
            if(var_flag == 0){
                reg = "t" + std::to_string(temp_reg++);
            }else if(var_flag == 1){
                reg = "t" + std::to_string(val_reg++);
            }
            value_to_reg[value] = reg;
            break;
        case KOOPA_RVT_LOAD:
            if (value_to_reg.find(value) != value_to_reg.end()) {
                // If the value has already been processed, avoid reprocessing
                break;
            }
            //std::cout << "Load from pointer: " << kind.data.load.src->name << std::endl;
            //Visit(kind.data.load.src);
            if(var_flag == 0){
                value_to_reg[value] = "t" + std::to_string(temp_reg++);
            }else if(var_flag == 1){
                value_to_reg[value] = "t" + std::to_string(val_reg++);
            }
            reg = value_to_reg[kind.data.load.src];
            //std::cout << "Register: " << reg << std::endl;
            lw_sf_reg = kind.data.load.src->name;
            lw_sta_fra = var_offset[lw_sf_reg];
            sw_sf_reg = koo_reg[value];
            sw_sta_fra = var_offset[sw_sf_reg];
            std::cout << "  " << "lw " << reg + ", " << std::to_string(lw_sta_fra) << "(sp)" << std::endl;
            std::cout << "  " << "sw " << reg + ", " << std::to_string(sw_sta_fra) << "(sp)" << std::endl;   
            break;
        case KOOPA_RVT_STORE:
            //std::cout << "HERE STORE" << std::endl;
            if (value_to_reg.find(value) != value_to_reg.end()) {
                // If the value has already been processed, avoid reprocessing
                break;
            }
            Visit(kind.data.store.value);
            Visit(kind.data.store.dest);
            reg = value_to_reg[kind.data.store.dest];
            if (kind.data.store.value->kind.tag == KOOPA_RVT_INTEGER) {
                //std::cout << "Storing integer: " << kind.data.store.value->kind.data.integer.value << std::endl;
                int_to_reg[kind.data.store.value->kind.data.integer.value] = kind.data.store.dest->name;
                sw_sf_reg = kind.data.store.dest->name;
                sw_sta_fra = var_offset[sw_sf_reg];
                std::cout << "  " << "sw " << reg + ", " << std::to_string(sw_sta_fra) << "(sp)" << std::endl;
            } else {
                //std::cout << "Storing value from: " << (kind.data.store.value->name ? kind.data.store.value->name : "unnamed value") << std::endl;
                if(var_flag == 0){
                    value_to_reg[kind.data.store.value] = "t" + std::to_string(temp_reg++);
                }else if(var_flag == 1){
                    value_to_reg[kind.data.store.value] = "t" + std::to_string(val_reg++);
                }
                lw_sf_reg = koo_reg[kind.data.store.value];
                lw_sta_fra = var_offset[lw_sf_reg];
                sw_sf_reg = kind.data.store.dest->name;
                sw_sta_fra = var_offset[sw_sf_reg];            
                std::cout << "  " << "lw " << reg + ", " << std::to_string(lw_sta_fra) << "(sp)" << std::endl;
                std::cout << "  " << "sw " << reg + ", " << std::to_string(sw_sta_fra) << "(sp)" << std::endl;
            }
            break;

        case KOOPA_RVT_RETURN://return
            if(var_flag == 0){
                if(kind.data.ret.value->kind.tag == KOOPA_RVT_INTEGER){
                    std::cout << "  " << "li " << "a0, " << kind.data.ret.value->kind.data.integer.value << std::endl;   
                }else{
                    Visit(kind.data.ret.value);//get return value
                    ret_reg = value_to_reg[kind.data.ret.value];
                    std::cout << "  " << "mv " << "a0, " << ret_reg << std::endl; //use the last register
                }
            }
            else if(var_flag == 1){
                Visit(kind.data.ret.value);//get return value
                ret_reg = value_to_reg[kind.data.ret.value];
                std::cout << "  " << "lw " << "a0, " << ret_reg << std::endl;
                std::cout << "  " << "addi " << "sp, " << "sp, " << std::to_string(aligned_stack_size) << std::endl;
            }
            std::cout << "  "<<"ret" << std::endl; //Return expression
            break;
        case KOOPA_RVT_INTEGER:
            int_val=kind.data.integer.value;
            if (int_val == 0){
                int_to_reg[int_val] = "x0";
                break;
            }else{
                if(var_flag == 0){
                    reg = "t" + std::to_string(temp_reg++);
                }else if(var_flag == 1){
                    reg = "t" + std::to_string(val_reg++);
                }                
                int_to_reg[int_val] = reg;
                std::cout << "  " << "li " << reg + ", " << int_val << std::endl;
            }
            break;

        case KOOPA_RVT_BINARY:
            if (value_to_reg.find(value) != value_to_reg.end()) {
                // If the value has already been processed, avoid reprocessing
                break;
            }

            Visit(kind.data.binary.lhs);            
            if (kind.data.binary.lhs->kind.tag == KOOPA_RVT_INTEGER) {
                lhs_reg = int_to_reg[kind.data.binary.lhs->kind.data.integer.value];
            } else {
                lhs_reg = value_to_reg[kind.data.binary.lhs];
                if(var_flag == 1){
                    reg = "t" + std::to_string(val_reg++);
                    lw_sf_reg = koo_reg[kind.data.binary.lhs];
                    lw_sta_fra = var_offset[lw_sf_reg];
                    std::cout << "  " << "lw " << reg + ", " << std::to_string(lw_sta_fra) << "(sp)" << std::endl;
                }
            }
            Visit(kind.data.binary.rhs);
            if (kind.data.binary.rhs->kind.tag == KOOPA_RVT_INTEGER) {
                rhs_reg = int_to_reg[kind.data.binary.rhs->kind.data.integer.value];
            } else {
                rhs_reg = value_to_reg[kind.data.binary.rhs];
                if(var_flag == 1){
                    reg = "t" + std::to_string(val_reg++);                    
                    lw_sf_reg = koo_reg[kind.data.binary.rhs];
                    lw_sta_fra = var_offset[lw_sf_reg];
                    std::cout << "  " << "lw " << reg + ", " << std::to_string(lw_sta_fra) << "(sp)" << std::endl;
                }
            }

            switch (kind.data.binary.op){
                case KOOPA_RBO_ADD://addition operation
                    if(var_flag == 0){
                        reg = "t" + std::to_string(temp_reg++);
                        value_to_reg[value] = reg;
                        std::cout << "  " << "add " << reg + ", " << lhs_reg + ", " << rhs_reg << std::endl;
                        break;
                    }else if(var_flag == 1){
                        reg = "t" + std::to_string(val_reg++);
                        value_to_reg[value] = reg;
                        sw_sf_reg = koo_reg[value];
                        sw_sta_fra = var_offset[sw_sf_reg];
                        std::cout << "  " << "add " << reg + ", " << lhs_reg + ", " << rhs_reg << std::endl;
                        std::cout << "  " << "sw " << reg + ", " << std::to_string(sw_sta_fra) << "(sp)" << std::endl;
                        break;
                    }
                case KOOPA_RBO_SUB://substraction operation
                    if(var_flag == 0){
                        reg = "t" + std::to_string(temp_reg++);
                        value_to_reg[value] = reg;
                        std::cout << "  " << "sub " << reg + ", " << lhs_reg + ", " << rhs_reg << std::endl;
                        break;
                    }else if(var_flag == 1){
                        reg = "t" + std::to_string(val_reg++);
                        value_to_reg[value] = reg;
                        sw_sf_reg = koo_reg[value];
                        sw_sta_fra = var_offset[sw_sf_reg];
                        std::cout << "  " << "sub " << reg + ", " << lhs_reg + ", " << rhs_reg << std::endl;
                        std::cout << "  " << "sw " << reg + ", " << std::to_string(sw_sta_fra) << "(sp)" << std::endl;
                        break;
                    }
                case KOOPA_RBO_MUL://multiplication operation
                    if(var_flag == 0){
                        reg = "t" + std::to_string(temp_reg++);
                        value_to_reg[value] = reg;
                        std::cout << "  " << "mul " << reg + ", " << lhs_reg + ", " << rhs_reg << std::endl;
                        break;
                    }else if(var_flag == 1){
                        reg = "t" + std::to_string(val_reg++);
                        value_to_reg[value] = reg;
                        sw_sf_reg = koo_reg[value];
                        sw_sta_fra = var_offset[sw_sf_reg];
                        std::cout << "  " << "mul " << reg + ", " << lhs_reg + ", " << rhs_reg << std::endl;
                        std::cout << "  " << "sw " << reg + ", " << std::to_string(sw_sta_fra) << "(sp)" << std::endl;
                        break;
                    }                        
                case KOOPA_RBO_DIV://division operation
                    if (var_flag == 0){
                        reg = "t" + std::to_string(temp_reg++);
                        value_to_reg[value] = reg;
                        std::cout << "  " << "div " << reg + ", " << lhs_reg + ", " << rhs_reg << std::endl;
                        break;
                    }else if(var_flag == 1){
                        reg = "t" + std::to_string(val_reg++);
                        value_to_reg[value] = reg;
                        sw_sf_reg = koo_reg[value];
                        sw_sta_fra = var_offset[sw_sf_reg];
                        std::cout << "  " << "div " << reg + ", " << lhs_reg + ", " << rhs_reg << std::endl;
                        std::cout << "  " << "sw " << reg + ", " << std::to_string(sw_sta_fra) << "(sp)" << std::endl;
                        break;                        
                    }
                case KOOPA_RBO_MOD://mod operation
                    if (var_flag == 0){
                        reg = "t" + std::to_string(temp_reg++);
                        value_to_reg[value] = reg;
                        std::cout << "  " << "rem " << reg + ", " << lhs_reg + ", " << rhs_reg << std::endl;
                        break;
                    }else if(var_flag == 1){
                        reg = "t" + std::to_string(val_reg++);
                        value_to_reg[value] = reg;
                        sw_sf_reg = koo_reg[value];
                        sw_sta_fra = var_offset[sw_sf_reg];
                        std::cout << "  " << "rem " << reg + ", " << lhs_reg + ", " << rhs_reg << std::endl;
                        std::cout << "  " << "sw " << reg + ", " << std::to_string(sw_sta_fra) << "(sp)" << std::endl;
                        break;                                  
                    }

                case KOOPA_RBO_EQ://equal operation
                    if (var_flag == 0){
                        reg = "t" + std::to_string(temp_reg++);//compare the same element
                        //val_reg++;
                        value_to_reg[value] = reg;
                        std::cout << "  " << "xor " << reg + ", " << lhs_reg + ", " << rhs_reg << std::endl;
                        std::cout << "  " << "seqz " << reg + ", " << reg << std::endl;
                        break;
                    }else if (var_flag == 1){
                        reg = "t" + std::to_string(val_reg++);
                        value_to_reg[value] = reg;
                        sw_sf_reg = koo_reg[value];
                        sw_sta_fra = var_offset[sw_sf_reg];
                        std::cout << "  " << "xor " << reg + ", " << lhs_reg + ", " << rhs_reg << std::endl;
                        std::cout << "  " << "seqz " << reg + ", " << reg << std::endl;
                        std::cout << "  " << "sw " << reg + ", " << std::to_string(sw_sta_fra) << "(sp)" << std::endl;
                        break;                            
                    }
                case KOOPA_RBO_NOT_EQ://not equal operation
                    if (var_flag == 0){
                        reg = "t" + std::to_string(temp_reg++);//compare the same element
                        value_to_reg[value] = reg;
                        std::cout << "  " << "xor " << reg + ", " << lhs_reg + ", " << rhs_reg << std::endl;
                        std::cout << "  " << "snez " << reg + ", " << reg << std::endl;
                        break;
                    }else if(var_flag == 1){
                        reg = "t" + std::to_string(val_reg++);
                        value_to_reg[value] = reg;
                        sw_sf_reg = koo_reg[value];
                        sw_sta_fra = var_offset[sw_sf_reg];
                        std::cout << "  " << "xor " << reg + ", " << lhs_reg + ", " << rhs_reg << std::endl;
                        std::cout << "  " << "snez " << reg + ", " << reg << std::endl;
                        std::cout << "  " << "sw " << reg + ", " << std::to_string(sw_sta_fra) << "(sp)" << std::endl;
                        break;                         
                    }
                    
                case KOOPA_RBO_LT://less than operation
                    if (var_flag == 0){
                        reg = "t" + std::to_string(temp_reg++);//compare the same element
                        //val_reg++;
                        value_to_reg[value] = reg;
                        std::cout << "  " << "slt " << reg + ", " << lhs_reg + ", " << rhs_reg << std::endl;
                        break;
                    }else if(var_flag == 1){
                        reg = "t" + std::to_string(val_reg++);
                        value_to_reg[value] = reg;
                        sw_sf_reg = koo_reg[value];
                        sw_sta_fra = var_offset[sw_sf_reg];
                        std::cout << "  " << "slt " << reg + ", " << lhs_reg + ", " << rhs_reg << std::endl;
                        std::cout << "  " << "sw " << reg + ", " << std::to_string(sw_sta_fra) << "(sp)" << std::endl;
                        break;     
                    }
                case KOOPA_RBO_LE://greater than or equal to operation
                    if (var_flag == 0){
                        reg = "t" + std::to_string(temp_reg++);//compare the same element
                        //val_reg++;
                        value_to_reg[value] = reg;
                        std::cout << "  " << "sgt " << reg + ", " << lhs_reg + ", " << rhs_reg << std::endl;
                        std::cout << "  " << "seqz " << reg + ", " << reg << std::endl;
                        break;
                    }else if(var_flag == 1){
                        reg = "t" + std::to_string(val_reg++);
                        value_to_reg[value] = reg;
                        sw_sf_reg = koo_reg[value];
                        sw_sta_fra = var_offset[sw_sf_reg];
                        std::cout << "  " << "sgt " << reg + ", " << lhs_reg + ", " << rhs_reg << std::endl;
                        std::cout << "  " << "seqz " << reg + ", " << reg << std::endl;
                        std::cout << "  " << "sw " << reg + ", " << std::to_string(sw_sta_fra) << "(sp)" << std::endl;
                        break;   
                    }
                case KOOPA_RBO_GT://greater than operation
                    if (var_flag == 0){
                        reg = "t" + std::to_string(temp_reg++);//compare the same element
                        //val_reg++;
                        value_to_reg[value] = reg;
                        std::cout << "  " << "slt " << reg + ", " << rhs_reg + ", " << lhs_reg << std::endl;
                        break;
                    }else if(var_flag == 1){
                        reg = "t" + std::to_string(val_reg++);
                        value_to_reg[value] = reg;
                        sw_sf_reg = koo_reg[value];
                        sw_sta_fra = var_offset[sw_sf_reg];
                        std::cout << "  " << "slt " << reg + ", " << rhs_reg + ", " << lhs_reg << std::endl;
                        std::cout << "  " << "sw " << reg + ", " << std::to_string(sw_sta_fra) << "(sp)" << std::endl;
                        break;
                    }
                case KOOPA_RBO_GE://greater than or equal to operation
                    if (var_flag == 0){
                        reg = "t" + std::to_string(temp_reg++);//compare the same element
                        //val_reg++;
                        value_to_reg[value] = reg;
                        std::cout << "  " << "sgt " << reg + ", " << rhs_reg + ", " << lhs_reg << std::endl;
                        std::cout << "  " << "seqz " << reg + ", " << reg << std::endl;
                        break;
                    }else if(var_flag == 1){
                        reg = "t" + std::to_string(val_reg++);
                        value_to_reg[value] = reg;
                        sw_sf_reg = koo_reg[value];
                        sw_sta_fra = var_offset[sw_sf_reg];
                        std::cout << "  " << "sgt " << reg + ", " << rhs_reg + ", " << lhs_reg << std::endl;
                        std::cout << "  " << "seqz " << reg + ", " << reg << std::endl;
                        std::cout << "  " << "sw " << reg + ", " << std::to_string(sw_sta_fra) << "(sp)" << std::endl;
                        break;
                    }
            }
            break;
        
        case KOOPA_RVT_BRANCH:
            Visit(kind.data.branch.cond);
            true_bb = kind.data.branch.true_bb->name;
            true_bb = true_bb.substr(1);
            false_bb = kind.data.branch.false_bb->name;
            false_bb = false_bb.substr(1);
            if (var_flag == 1){
                if (kind.data.branch.cond->kind.tag == KOOPA_RVT_INTEGER){
                    reg = int_to_reg[kind.data.branch.cond->kind.data.integer.value];
                }else{
                    reg = value_to_reg[kind.data.branch.cond];
                }
                lw_sf_reg = koo_reg[kind.data.branch.cond];
                lw_sta_fra = var_offset[lw_sf_reg];
                //std::cout << "  " << "lw " << reg + ", " << std::to_string(lw_sta_fra) << "(sp)" << std::endl;
                std::cout << "  " << "bnez " << reg + ", " << true_bb << std::endl;
                std::cout << "  " << "j " << false_bb << std::endl;
                break;
            }
        case KOOPA_RVT_JUMP:
            target_name = kind.data.jump.target->name;
            target_name = target_name.substr(1);
            if (var_flag == 1){
                std::cout << std::left;
                std::cout << "  " << "j " << target_name << std::endl;
                break;
            }
        default:
            std::cout << "Unhandled operation: " << kind.tag << std::endl;
            assert(false);//Unsupported types
            break;
    }
}