#include <iostream>
#include <unordered_map>
#include "koopa.h"


const int PARAM_NUM=8;
int glo_var_num;
std::unordered_map<koopa_raw_value_t, std::string> glo_var_offset;
struct Memory{
/*
    @ l_ocal: memory (bytes) of local parameters
    @ r_a: memory of return address, 0 or 4 (bytes)
    @ c_all: memory (bytes) of parameters in called functions, counting from the 9th parameter for each function 
    @ f_inall: total memory (16 based)
    @ koo_reg_num: used memory in the stack
    @ var_offset: mapping from values to stack addresses
*/
    int l_ocal,r_a,c_all,f_inal,koo_reg_num;
    std::unordered_map<koopa_raw_value_t, int> var_offset;
    std::unordered_map<koopa_raw_value_t, std::pair<int,std::string> > param_offset;
    // Memory(int local,int ra,int call,int final=0,int cnt=0):
        // l_ocal(local),r_a(ra),c_all(call),f_inal(final),koo_reg_num(cnt){}
    void init(){//initial
        l_ocal=r_a=c_all=f_inal=koo_reg_num=0;
        var_offset.clear();
        param_offset.clear();
    }
    void F(){//calculate the f_inal and koo_reg_num
        f_inal=((l_ocal+r_a+c_all + 15) / 16) * 16;
        koo_reg_num=r_a?f_inal-8:f_inal-4;
    }
    void print(){
        std::cerr<<l_ocal<<" "<<r_a<<" "<<c_all<<" "<<f_inal<<" "<<koo_reg_num<<std::endl;
    }
}fun_mem;

int temp_reg = 0;

int AllocateStackForVariable(const koopa_raw_value_t& var){
/*
    allocate stack memory. i32 as defalut.
    @ var: variables
    @ return: the position偏移量 in the stack
*/
    if (fun_mem.var_offset.find(var) == fun_mem.var_offset.end()) {
        fun_mem.var_offset[var] = fun_mem.koo_reg_num;
        // std::cerr << "ALLO: "<< fun_mem.koo_reg_num << std::endl;
        fun_mem.koo_reg_num -= 4; //each variable or register will be assigned 4 bytes
        return fun_mem.koo_reg_num+4;
    }
    else
        return fun_mem.var_offset[var];
}

void StackSize(const koopa_raw_function_t &funs){
/*
    calculate stack size, assuming all variables are stored in the stack.
    @ funs: the current function
*/
    fun_mem.init();
    for(size_t i=0;i<(funs->bbs).len;i++){
        auto ptr = (funs->bbs).buffer[i];
        koopa_raw_basic_block_t bb =reinterpret_cast<koopa_raw_basic_block_t>(ptr);
        for(size_t j=0;j<(bb->insts).len;j++){
            ptr = (bb->insts).buffer[j];
            koopa_raw_value_t value = reinterpret_cast<koopa_raw_value_t>(ptr);
            if (value->ty->tag != KOOPA_RTT_UNIT)
                fun_mem.l_ocal+=4;
            if(value->kind.tag==KOOPA_RVT_CALL)
            {
                fun_mem.r_a=4;
                fun_mem.c_all=std::max(fun_mem.c_all,(int)value->kind.data.call.args.len-PARAM_NUM);
            }
        }
    }
    fun_mem.F();
}

void Visit(const koopa_raw_program_t &raw);
void Visit(const koopa_raw_slice_t &slice);
void Visit(const koopa_raw_function_t &func);
void Visit(const koopa_raw_basic_block_t &bb);
std::pair<int,std::string> Visit(const koopa_raw_value_t &value);
std::string Visit(const koopa_raw_load_t &load);
std::pair<int,std::string> Visit(const koopa_raw_store_t &store);
void Visit(const koopa_raw_return_t &ret);
std::string Visit(const koopa_raw_binary_t &bin);
void Visit(const koopa_raw_branch_t &bran);
void Visit(const koopa_raw_call_t &call);
std::string Decode(std::pair<int,std::string> ini);
std::string Glo_to_reg(std::string glo);

void Visit(const koopa_raw_program_t &raw){
/*
    deal with raw IR program
    @ raw: the whole raw IR code
    currently:
        raw program -> functions and global variables
*/
    Visit(raw.values);//koopa_raw_slice_t
    Visit(raw.funcs);//koopa_raw_slice_t

}

void Visit(const koopa_raw_slice_t &slice){
/*
    deal with different slices(listed below).
    @ slice: what is needed to translate
*/
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
                temp_reg=0;
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
    if(func->bbs.len==0)//function declaration or external function
        return ;
    std::cout << "  " << ".text" << std::endl;
    std::string func_name = func->name;
    if (!func_name.empty() && func_name[0] == '@') {
        func_name = func_name.substr(1); //remove "@"
    }
    std::cout << "  " << ".global " << func_name << std::endl;  // output the global tag
    std::cout << func_name << ":" << std::endl;  //output the function name
    StackSize(func);
    // fun_mem.print();
    if(fun_mem.f_inal){
        std::cout << "  " << "addi " <<  "sp, " << "sp, " << "-" << fun_mem.f_inal << std::endl;
        if(fun_mem.r_a)
            std::cout << "  sw ra, " << fun_mem.f_inal-4 << "(sp)" << std::endl;
    }
    int para_num=0;
    for(size_t i=0;i<func->params.len;i++){
        auto ptr = func->params.buffer[i];
        koopa_raw_value_t param = reinterpret_cast<koopa_raw_value_t>(ptr);
        std::pair<int,std::string> pi(-1,"");
        if(i<PARAM_NUM){
            pi.second="a"+std::to_string(i);
        }
        else{
            pi.first=fun_mem.f_inal+para_num;
            para_num+=4;
        }
        fun_mem.param_offset[param]=pi;
    }
    Visit(func->bbs);//koopa_raw_slice_t
}

void Visit(const koopa_raw_basic_block_t &bb){
/*
    deal with basic blocks
    currently:
        basic blocks -> values
*/
//    std::cerr<<"here3!"<<std::endl;
    std::string bb_name = bb->name;
    if (!bb_name.empty() && bb_name[0] == '%'){
        bb_name = bb_name.substr(1); //remove "%"
    }
    if(bb_name !="entry")std::cout << bb_name << ":" << std::endl;  //output the basic block name
    Visit(bb->insts);//koopa_raw_slice_t
}

std::string Visit(const koopa_raw_load_t &load){
/*
    deal with load operation.
    @ load: the operation
    @ return: the registry that stored the need value
*/
    std::pair<int,std::string> src_reg=Visit(load.src);
    std::string reg=Decode(src_reg);
    reg=Glo_to_reg(reg);
    return reg;
}

std::pair<int,std::string> Visit(const koopa_raw_store_t &store){
/*
    deal with store operation.
    @ store: the operatiron
    @ return: the address that stored the need value
*/
    std::pair<int,std::string> var_sto=Visit(store.value);
    std::string var_reg=Decode(var_sto);
    var_reg=Glo_to_reg(var_reg);
    std::pair<int,std::string> dest_sto=Visit(store.dest);
    if(store.dest->kind.tag==KOOPA_RVT_GLOBAL_ALLOC){
        std::cout << "  " << "sw " << var_reg + ", " << dest_sto.second << std::endl;
    }
    else{
        assert(dest_sto.first!=-1);
        std::cout << "  " << "sw " << var_reg + ", " << dest_sto.first << "(sp)" << std::endl;
    }
    return dest_sto;
}

void Visit(const koopa_raw_return_t &ret){
/*
    deal with return operation.
    @ ret: the operation
*/
    if(ret.value==NULL);
    else if(ret.value->kind.tag == KOOPA_RVT_INTEGER){//simple interger
        std::cout << "  " << "li " << "a0, " <<ret.value->kind.data.integer.value << std::endl;   
    }else{
        std::pair<int,std::string> ret_val=Visit(ret.value);//get return value
        if(ret_val.first==-1){//in the register
            std::cout << "  " << "mv " << "a0, " << ret_val.second << std::endl;
        }
        else if(ret.value->kind.tag == KOOPA_RVT_GLOBAL_ALLOC){//global variable
            std::cout << "  " << "lw " << "a0, " << ret_val.second << std::endl;
        }
        else//in the stack
            std::cout << "  " << "lw " << "a0, " << ret_val.first << "(sp)" << std::endl;
    }

    if(fun_mem.f_inal){//restore the stack pointer
        if(fun_mem.r_a)//restore the ra
            std::cout << "  lw ra, " << fun_mem.f_inal-4 << "(sp)" << std::endl;
        std::cout << "  " << "addi " <<  "sp, " << "sp, " << fun_mem.f_inal << std::endl;
    }
    std::cout << "  "<<"ret" << std::endl << std::endl; //Return expression
}

std::string Visit(const koopa_raw_binary_t &bin){
/*
    deal with binary operation.
    @ bin: the operation
    @ return: register that stored the result
*/
    std::pair<int,std::string> lhs_bin=Visit(bin.lhs);
    std::string lhs_reg=Decode(lhs_bin);
    lhs_reg=Glo_to_reg(lhs_reg);
    std::pair<int,std::string> rhs_bin=Visit(bin.rhs);
    std::string rhs_reg=Decode(rhs_bin);
    rhs_reg=Glo_to_reg(rhs_reg);
    std::string reg = "t" + std::to_string(temp_reg++);
    switch (bin.op){
        case KOOPA_RBO_ADD://addition operation
            std::cout << "  " << "add " << reg + ", " << lhs_reg + ", " << rhs_reg << std::endl;
            break;
        case KOOPA_RBO_SUB://substraction operation
            std::cout << "  " << "sub " << reg + ", " << lhs_reg + ", " << rhs_reg << std::endl;
            break;
        case KOOPA_RBO_MUL://multiplication operation
            std::cout << "  " << "mul " << reg + ", " << lhs_reg + ", " << rhs_reg << std::endl;
            break;
        case KOOPA_RBO_DIV://division operation
            std::cout << "  " << "div " << reg + ", " << lhs_reg + ", " << rhs_reg << std::endl;
            break;      
        case KOOPA_RBO_MOD://mod operation
            std::cout << "  " << "rem " << reg + ", " << lhs_reg + ", " << rhs_reg << std::endl;
            break;
        case KOOPA_RBO_EQ://equal operation
            std::cout << "  " << "xor " << reg + ", " << lhs_reg + ", " << rhs_reg << std::endl;
            std::cout << "  " << "seqz " << reg + ", " << reg << std::endl;
            break;
        case KOOPA_RBO_NOT_EQ://not equal operation
            std::cout << "  " << "xor " << reg + ", " << lhs_reg + ", " << rhs_reg << std::endl;
            std::cout << "  " << "snez " << reg + ", " << reg << std::endl;
            break;
        case KOOPA_RBO_LT://less than operation
            std::cout << "  " << "slt " << reg + ", " << lhs_reg + ", " << rhs_reg << std::endl;
            break;
        case KOOPA_RBO_LE://greater than or equal to operation
            std::cout << "  " << "sgt " << reg + ", " << lhs_reg + ", " << rhs_reg << std::endl;
            std::cout << "  " << "seqz " << reg + ", " << reg << std::endl;
            break;
        case KOOPA_RBO_GT://greater than operation
            std::cout << "  " << "slt " << reg + ", " << rhs_reg + ", " << lhs_reg << std::endl;
            break;
        case KOOPA_RBO_GE://greater than or equal to operation
            std::cout << "  " << "sgt " << reg + ", " << rhs_reg + ", " << lhs_reg << std::endl;
            std::cout << "  " << "seqz " << reg + ", " << reg << std::endl;
            break;
        case KOOPA_RBO_AND:
            std::cout << "  " << "and " << reg + ", " << rhs_reg + ", " << lhs_reg << std::endl;
            break;
        case KOOPA_RBO_OR:
            std::cout << "  " << "or " << reg + ", " << rhs_reg + ", " << lhs_reg << std::endl;
            break;
        case KOOPA_RBO_XOR:
            std::cout << "  " << "xor " << reg + ", " << rhs_reg + ", " << lhs_reg << std::endl;
            break;
        case KOOPA_RBO_SHL:
            std::cout << "  " << "sll " << reg + ", " << rhs_reg + ", " << lhs_reg << std::endl;
            break;
        case KOOPA_RBO_SHR:
            std::cout << "  " << "srl " << reg + ", " << rhs_reg + ", " << lhs_reg << std::endl;
            break;
        default:
            std::cout << "Unhandled binary: " << bin.op << std::endl;
            break;
    }
    return reg;
}

void Visit(const koopa_raw_branch_t &bran){
/*
    deal with branch operation.
    @ bran: the operation
*/
    std::pair<int,std::string> cond=Visit(bran.cond);
    std::string reg = Decode(cond);
    reg=(Glo_to_reg(reg));
    std::string true_bb = bran.true_bb->name;
    true_bb = true_bb.substr(1);
    std::string false_bb = bran.false_bb->name;
    false_bb = false_bb.substr(1);
    std::cout << "  " << "bnez " << reg + ", " << true_bb << std::endl;
    std::cout << "  " << "j " << false_bb << std::endl;
}

void Visit(const koopa_raw_call_t &call){
/*
    deal with call_function operation.
    @ call: the operation
*/
    int para_num=0;
    for(size_t i=0;i<call.args.len;i++){
        auto ptr = call.args.buffer[i];
        koopa_raw_value_t arg =reinterpret_cast<koopa_raw_value_t>(ptr);
        int reg_num=temp_reg;
        if(i<PARAM_NUM){
            if(arg->kind.tag == KOOPA_RVT_INTEGER)
                std::cout << "  " << "li a" << i << ", " <<arg->kind.data.integer.value << std::endl;  
            else{
                std::pair<int,std::string> arg_ret=Visit(arg);
                std::string arg_reg=Decode(arg_ret);
                std::cout << "  mv a" << i << " ," << arg_reg << std::endl;
            }
        }
        else{
            std::pair<int,std::string> arg_ret=Visit(arg);
            std::string arg_reg=Decode(arg_ret);
            std::cout << "  sw " << arg_reg<<  " ," << para_num << "(sp)" << std::endl;
            para_num+=4;
        }
        temp_reg=reg_num;
    }
    std::string fun_name=call.callee->name;
    fun_name = fun_name.substr(1);
    std::cout << "  " << "call " << fun_name << std::endl;
}


std::string Visit(const koopa_raw_global_alloc_t &glo){
/*
    deal with global variable.
    @ glo: the variable
*/
    std::cout << "  " << ".data" << std::endl;
    std::string func_name = "var_"+std::to_string(glo_var_num++);
    std::cout << "  " << ".global " << func_name << std::endl;  // output the global variable
    std::cout << func_name << ":" << std::endl;  //output the variable name
    switch(glo.init->kind.tag){
        case KOOPA_RVT_ZERO_INIT:
            std::cout << "  " << ".zero " << "4" << std::endl << std::endl;
            break;
        case KOOPA_RVT_INTEGER:
            std::cout << "  " << ".word " << glo.init->kind.data.integer.value << std::endl << std::endl;
            break;
        default:
            std::cout << "Global_Unhandble type:" << glo.init->kind.tag << std::endl;
            break;
    }
    return func_name;
}

std::pair<int,std::string> Visit(const koopa_raw_value_t &value){
/*
    deal with a value
    @ value: the value
    @ return: int: the position偏移量 if stored in the stack; -1 otherwise;
              string: register's name if stored in the register; "" otherwise;
*/
    const auto &kind = value->kind;
    int32_t int_val;
    int sw_sta=-1;
    std::string sw_reg="",reg,name;
    std::pair<int,std::string> pi;
    // std::cerr << ",,,"<<kind.tag << std::endl;

    switch(kind.tag){
        case KOOPA_RVT_ALLOC:
            // std::cerr << "HERE ALLOC" << std::endl;
            sw_sta=AllocateStackForVariable(value);
            //std::cerr << value->name << fun_mem.koo_reg_num << std::endl;
            break;

        case KOOPA_RVT_LOAD:
            // std::cerr << "HERE LOAD" << std::endl;
            if (fun_mem.var_offset.find(value) != fun_mem.var_offset.end()) {
                sw_sta = fun_mem.var_offset[value];
                break;
            }
            reg=Visit(kind.data.load);
            sw_sta=AllocateStackForVariable(value);
            std::cout << "  " << "sw " << reg << ", " << sw_sta << "(sp)" << std::endl; 
            break; 

        case KOOPA_RVT_STORE:
            // std::cerr << "HERE STORE" << std::endl;
            if (fun_mem.var_offset.find(value) != fun_mem.var_offset.end()) {
                sw_sta = fun_mem.var_offset[value];
                break;
            }
            pi=Visit(kind.data.store);
            sw_sta=pi.first,sw_reg=pi.second;
            break;

        case KOOPA_RVT_RETURN://return
            // std::cerr << "HERE RETURN" << std::endl;
            Visit(kind.data.ret);
            break;

        case KOOPA_RVT_INTEGER:
            // std::cerr << "HERE INT" << std::endl;
            int_val=kind.data.integer.value;
            if (int_val == 0){
                sw_reg = "x0";
            }else{
                sw_reg = "t" + std::to_string(temp_reg++);
                std::cout << "  " << "li " << sw_reg + ", " << int_val << std::endl;
            }
            break;

        case KOOPA_RVT_BINARY:
            // std::cerr << "HERE BINARY" << std::endl;
            if (fun_mem.var_offset.find(value) != fun_mem.var_offset.end()) {
                sw_sta = fun_mem.var_offset[value];
                break;
            }
            reg=Visit(kind.data.binary);
            sw_sta=AllocateStackForVariable(value);
            std::cout << "  " << "sw " << reg + ", " << sw_sta << "(sp)" << std::endl;
            break;
        
        case KOOPA_RVT_BRANCH:
            // std::cerr << "HERE BRANCH" << std::endl;
            Visit(kind.data.branch);
            break;
        case KOOPA_RVT_JUMP:
            // std::cerr << "HERE JUMP" << std::endl;
            name = kind.data.jump.target->name;
            name = name.substr(1);
            std::cout << "  " << "j " << name << std::endl;
            break;
        case KOOPA_RVT_CALL:
            // std::cerr << "HERE CALL" << std::endl;
            if (fun_mem.var_offset.find(value) != fun_mem.var_offset.end()) {
                sw_sta = fun_mem.var_offset[value];
                break;
            }
            Visit(kind.data.call);
            if (value->ty->tag != KOOPA_RTT_UNIT){ // has return value,???how about multiple return values?
                sw_sta=AllocateStackForVariable(value);
                std::cout << "  " << "sw a0, " << sw_sta << "(sp)" << std::endl;
            }
            break;
        case KOOPA_RVT_GLOBAL_ALLOC:
            // std::cerr << "HERE GLOBAL" << std::endl;
            if (glo_var_offset.find(value) != glo_var_offset.end()) {
                name = glo_var_offset[value];
                sw_reg = "t" + std::to_string(temp_reg++);
                std::cout << "  " << "la " << sw_reg + ", " << name << std::endl;
                sw_reg = "0("+sw_reg+")";
                break;
            }
            glo_var_offset[value]=Visit(kind.data.global_alloc);
            break;
        case KOOPA_RVT_GET_ELEM_PTR:
                // std::cerr << "HERE ELEM" << std::endl;
            break;
        case KOOPA_RVT_GET_PTR:
                // std::cerr << "HERE PTR" << std::endl;
            break;
        case KOOPA_RVT_ZERO_INIT:/// Zero initializer.
                // std::cerr << "HERE ZERO" << std::endl;
            sw_reg = "x0";
            break;
        case KOOPA_RVT_AGGREGATE:/// Aggregate constant.
                // std::cerr << "HERE AGGREGATE" << std::endl;
            break;
        case KOOPA_RVT_FUNC_ARG_REF:/// Function argument reference.
            // std::cerr << "HERE ARG" << std::endl;
            sw_sta=fun_mem.param_offset[value].first;
            sw_reg=fun_mem.param_offset[value].second;
            break;
        case KOOPA_RVT_BLOCK_ARG_REF:/// Basic block argument reference.
                // std::cerr << "HERE BLOCK" << std::endl;
            break;
        default:
            std::cout << "Unhandled operation: " << kind.tag << std::endl;
            assert(false);//Unsupported types
            break;
    }
    return make_pair(sw_sta,sw_reg);
}

std::string Decode(std::pair<int,std::string> ini){
/*
    get the needed value that stored in the stack or register.
    @ ini: the stored place
    @ return: the register that stored the need value or the address(for global variable);
*/
    if (ini.first==-1) {//in the register
        return ini.second;
    }
    else{//in the stack
        std::string reg = "t" + std::to_string(temp_reg++);
        std::cout << "  " << "lw " << reg + ", " << ini.first << "(sp)" << std::endl;
        return reg;
    }
}
std::string Glo_to_reg(std::string glo){
/*
    get the register that stored the global variable from the address.
    @ glo: the address
    @ return: the register;
*/
    if(glo.length()!=2){//global variable
        std::cout << "  " << "lw " << glo.substr(2,2) + ", " << glo << std::endl;
        glo=glo.substr(2,2);//get the rigester
    }
    return glo;
}
