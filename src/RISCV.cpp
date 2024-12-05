#include <iostream>
#include <unordered_map>
#include <assert.h>
#include "simplified_llvm.h"
#include "RISCV.h"

// assume all the memory size of pointers and values are i32 (4 bytes)

const int PARAM_NUM = 8;//the number of params that can be stored in the registers
int glo_var_num;//the number of global variables
std::unordered_map<koopa_raw_value_t, std::string> glo_var_offset;//mapping from global values to stack addresses
std::unordered_map<koopa_raw_value_t, int> glo_array_offset;//mapping from global arrays to the lengths
struct Memory{
/*
    @ l_ocal: memory (bytes) of local parameters
    @ r_a: memory of return address, 0 or 4 (bytes)
    @ c_all: memory (bytes) of parameters in called functions, counting from the 9th parameter for each function 
    @ f_inall: total memory (16 based)
    @ used_mem: used memory in the stack
    @ var_offset: mapping from values to stack addresses.
    @ array_offset: mapping from arrays to the lengths
    @ param_offset: mapping from this function's parameters to the addresses that store paras
*/
    int l_ocal, r_a, c_all, f_inal, used_mem;
    std::unordered_map<koopa_raw_value_t, int> var_offset;
    std::unordered_map<koopa_raw_value_t, int> array_offset;
    std::unordered_map<koopa_raw_value_t, std::pair<int,std::string> > param_offset;
    // Memory(int local,int ra,int call,int final=0,int cnt=0):
        // l_ocal(local),r_a(ra),c_all(call),f_inal(final),used_mem(cnt){}
    void init(){//initial
        l_ocal = r_a = c_all = f_inal = used_mem = 0;
        var_offset.clear();
        param_offset.clear();
    }
    void F(){//calculate the f_inal and used_mem
        f_inal = ((l_ocal+r_a+c_all + 15) / 16) * 16;
        used_mem = r_a? f_inal-4: f_inal;
    }
    void print(){
        std::cerr << l_ocal << " " << r_a << " " << c_all << " " << f_inal << " " << used_mem << std::endl;
    }
}fun_mem;

int temp_reg = 0;

int AllocateStackForVariable(const koopa_raw_value_t& var){
/*
    allocate stack memory
    @ var: variables
    @ return: the address in the stack
*/
    if (fun_mem.var_offset.find(var) == fun_mem.var_offset.end()) {
        int value = 4;//memory size
        if(fun_mem.array_offset.find(var) != fun_mem.array_offset.end())//array
            value = fun_mem.array_offset[var]*4;
        fun_mem.used_mem -= value;
        // std::cerr << "ALLO: "<< fun_mem.used_mem <<"  "<<value<< std::endl;
        fun_mem.var_offset[var] = fun_mem.used_mem;
        return fun_mem.used_mem;
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
    for(size_t i=0; i<(funs->bbs).len; i++){
        auto ptr = (funs->bbs).buffer[i];
        koopa_raw_basic_block_t bb = reinterpret_cast<koopa_raw_basic_block_t>(ptr);
        for(size_t j=0; j<(bb->insts).len; j++){
            ptr = (bb->insts).buffer[j];
            koopa_raw_value_t value = reinterpret_cast<koopa_raw_value_t>(ptr);//an instruction
            koopa_raw_type_t ty = value->ty;
            if (ty->tag != KOOPA_RTT_UNIT)// not void
            {
                if(value->kind.tag==KOOPA_RVT_ALLOC && ty->tag==KOOPA_RTT_POINTER){//array
                    int size = TypeSize(ty->data.pointer.base);
                    fun_mem.l_ocal += size;
                    fun_mem.array_offset[value] = size/4;
                }
                else
                    fun_mem.l_ocal += 4;
            }
            if(value->kind.tag == KOOPA_RVT_CALL)
            {
                fun_mem.r_a = 4;
                fun_mem.c_all = std::max(fun_mem.c_all, (int)value->kind.data.call.args.len-PARAM_NUM);
            }
        }
    }
    fun_mem.F();
}

int TypeSize(const koopa_raw_type_t& ty){
/*
    calculate memory size. e.g. alloc [i32, x],{1,2,3};
    @ ty: the current variable
    @ return: memory size
*/
    int ret = 4;
    switch(ty->tag){
        case KOOPA_RTT_INT32://int
        case KOOPA_RTT_POINTER://poiners
            ret = 4;
            break;
        case KOOPA_RTT_UNIT://void
            ret = 0;
            break;
        case KOOPA_RTT_ARRAY://array
            ret = TypeSize(ty->data.array.base)*(ty->data.array.len);
            break;
        case KOOPA_RTT_FUNCTION://function
            ret = 4 ;
            break;
        default:
            assert(false);//other types
    }
    return ret;
}


void Visit(const koopa_raw_program_t &raw){
/*
    deal with raw IR program
    @ raw: the whole raw IR code
*/
    Visit(raw.values);//koopa_raw_slice_t, global variables
    Visit(raw.funcs);//koopa_raw_slice_t, functions

}

void Visit(const koopa_raw_slice_t &slice){
/*
    deal with different slices(listed below).
    @ slice: what is needed to translate
*/
    switch(slice.kind){
        case KOOPA_RSIK_FUNCTION://functions
            for(size_t i=0; i<slice.len; i++){//list all functions
                Visit(reinterpret_cast<koopa_raw_function_t>(slice.buffer[i]));//reinterpret_cast
            }
            break;
        case KOOPA_RSIK_BASIC_BLOCK://basic block
            for(size_t i=0; i<slice.len; i++){//list all basic blocks
                Visit(reinterpret_cast<koopa_raw_basic_block_t>(slice.buffer[i]));
            }
            break;
        case KOOPA_RSIK_VALUE://values
            for(size_t i=0; i<slice.len; i++){//list all instructions in this basic block.
                temp_reg = 0;
                Visit(reinterpret_cast<koopa_raw_value_t>(slice.buffer[i]));
            }
            break;
        default:
            assert(false);//other types
    }
}

void Visit(const koopa_raw_function_t &func){
/*
    deal with a function
    params are guaranteed to be restored.
*/
    if(func->bbs.len==0)//function declaration or external function
        return ;
    std::cout << "  " << ".text" << std::endl;
    std::string func_name = func->name;
    if (!func_name.empty() && func_name[0] == '@') {
        func_name = func_name.substr(1); //remove "@"
    }
    std::cout << "  " << ".global " << func_name << std::endl;  //output the global tag
    std::cout << func_name << ":" << std::endl;  //output the function name
    StackSize(func);
    // fun_mem.print();
    if(fun_mem.f_inal){
        if(ValidStack(-fun_mem.f_inal))
            std::cout << "  " << "addi " <<  "sp, " << "sp, " << "-" << fun_mem.f_inal << std::endl;
        else{// operand must be a symbol with %lo/ %pcrel_lo/ %tprel_lo modifier or an integer in the range [-2048, 2047]
            std::string reg = New_reg();
            std::cout << "  " << "li " << reg + ", " << -fun_mem.f_inal << std::endl;
            std::cout << "  " << "add " << reg + ", " << reg << ", sp" << std::endl;
            std::cout << "  " << "add " <<  "sp, " << "sp, " << reg << std::endl;
            temp_reg--;
        }
        if(fun_mem.r_a)
            WriteToAddress("ra", fun_mem.f_inal-4);
    }
    int para_num = 0;
    for(size_t i=0; i<func->params.len; i++){//used params 
        auto ptr = func->params.buffer[i];
        koopa_raw_value_t param = reinterpret_cast<koopa_raw_value_t>(ptr);
        std::pair<int,std::string> pi(-1,"");
        if(i<PARAM_NUM){
            pi.second = "a" + std::to_string(i);
        }
        else{
            pi.first = fun_mem.f_inal + para_num;
            para_num += 4;
        }
        fun_mem.param_offset[param] = pi;
    }
    assert(temp_reg==0);
    Visit(func->bbs);//koopa_raw_slice_t
}

void Visit(const koopa_raw_basic_block_t &bb){
/*
    deal with basic blocks
*/
    std::string bb_name = bb->name;
    if (!bb_name.empty() && bb_name[0] == '%'){
        bb_name = bb_name.substr(1); //remove "%"
    }
    if(bb_name != "entry")
        std::cout << bb_name << ":" << std::endl;  //output the basic block name
    Visit(bb->insts);//koopa_raw_slice_t
}

std::string Visit(const koopa_raw_load_t &load){
/*
    %x = load %y: read from pointer %y, store value in %x
    %x: not global variables
    %y: not global variables
    @ load: the operation
    @ return: the registry that stored the need value (from %y)
*/
    std::pair<int,std::string> src_reg = Visit(load.src);
    std::string reg = ValueToReg(src_reg);
    if(load.src->kind.tag == KOOPA_RVT_GET_ELEM_PTR){
        std::cout << "  " << "lw " << reg + ", " << "0("+reg+")" << std::endl;
    }
    return reg;
}

void Visit(const koopa_raw_store_t &store){
/*
    store %x, %y: write %x('s value) to the address pointed by pointer %y
    %x: same type as *(%y)
    @ store: the operatiron
*/
    std::pair<int, std::string> var_sto = Visit(store.value);
    std::string var_reg = ValueToReg(var_sto);
    std::pair<int, std::string> dest_sto = Visit(store.dest);
    if(store.dest->kind.tag == KOOPA_RVT_GLOBAL_ALLOC){
        std::cout << "  " << "sw " << var_reg + ", " << dest_sto.second << std::endl;
    }
    else if(store.dest->kind.tag == KOOPA_RVT_GET_ELEM_PTR){
        std::string reg = New_reg();
        ReadFromAddress(reg, dest_sto.first);
        std::cout << "  " << "sw " << var_reg + ", " << "0("+reg+")" << std::endl;
        temp_reg--;
    }
    else{
        assert(dest_sto.first!=-1);
        WriteToAddress(var_reg, dest_sto.first);
    }
}

void Visit(const koopa_raw_return_t &ret){
/*
    ret (%x)
    %x: (if any) are guaranteed to be integers or variables.
    @ ret: the operation
*/
    if(ret.value == NULL);
    else if(ret.value->kind.tag == KOOPA_RVT_INTEGER){//simple interger
        std::cout << "  " << "li " << "a0, " << ret.value->kind.data.integer.value << std::endl;   
    }else{
        std::pair<int,std::string> ret_val = Visit(ret.value);//get return value
        if(ret_val.first == -1){//in the register
            std::cout << "  " << "mv " << "a0, " << ret_val.second << std::endl;
        }
        // else if(ret.value->kind.tag == KOOPA_RVT_GLOBAL_ALLOC){//global variable
        //     std::cout << "  " << "lw " << "a0, " << ret_val.second << std::endl;
        // }
        else{//in the stack
            ReadFromAddress("a0", ret_val.first);
        }
    }

    if(fun_mem.f_inal){//restore the stack pointer
        if(fun_mem.r_a)//restore the ra
            ReadFromAddress("ra", fun_mem.f_inal-4);
        if(ValidStack(fun_mem.f_inal))
            std::cout << "  " << "addi " <<  "sp, " << "sp, " << fun_mem.f_inal << std::endl;
        else{// operand must be a symbol with %lo/%pcrel_lo/%tprel_lo modifier or an integer in the range [-2048, 2047]
            std::string reg = New_reg();
            std::cout << "  " << "li " << reg + ", " << fun_mem.f_inal << std::endl;
            std::cout << "  " << "add " << reg + ", " << reg << ", sp" << std::endl;
            std::cout << "  " << "add " <<  "sp, " << "sp, " << reg << std::endl;
            temp_reg--;
        }
    }
    std::cout << "  "<<"ret" << std::endl << std::endl; //Return expression
}

std::string Visit(const koopa_raw_binary_t &bin){
/*
    %x = op %y, %z
    use and return registers only
    @ bin: the operation
    @ return: register that stored the result
*/
    std::pair<int,std::string> lhs_bin = Visit(bin.lhs);
    std::string lhs_reg = ValueToReg(lhs_bin);
    std::pair<int,std::string> rhs_bin = Visit(bin.rhs);
    std::string rhs_reg = ValueToReg(rhs_bin);
    std::string reg = New_reg();
    switch (bin.op){
        case KOOPA_RBO_ADD://addition operation (+)
            std::cout << "  " << "add " << reg + ", " << lhs_reg + ", " << rhs_reg << std::endl;
            break;
        case KOOPA_RBO_SUB://substraction operation (-)
            std::cout << "  " << "sub " << reg + ", " << lhs_reg + ", " << rhs_reg << std::endl;
            break;
        case KOOPA_RBO_MUL://multiplication operation (*)
            std::cout << "  " << "mul " << reg + ", " << lhs_reg + ", " << rhs_reg << std::endl;
            break;
        case KOOPA_RBO_DIV://division operation (/)
            std::cout << "  " << "div " << reg + ", " << lhs_reg + ", " << rhs_reg << std::endl;
            break;      
        case KOOPA_RBO_MOD://mod operation (%)
            std::cout << "  " << "rem " << reg + ", " << lhs_reg + ", " << rhs_reg << std::endl;
            break;
        case KOOPA_RBO_EQ://equal operation (== or !)
            std::cout << "  " << "xor " << reg + ", " << lhs_reg + ", " << rhs_reg << std::endl;
            std::cout << "  " << "seqz " << reg + ", " << reg << std::endl;
            break;
        case KOOPA_RBO_NOT_EQ://not equal operation (!=)
            std::cout << "  " << "xor " << reg + ", " << lhs_reg + ", " << rhs_reg << std::endl;
            std::cout << "  " << "snez " << reg + ", " << reg << std::endl;
            break;
        case KOOPA_RBO_LT://less than operation (<)
            std::cout << "  " << "slt " << reg + ", " << lhs_reg + ", " << rhs_reg << std::endl;
            break;
        case KOOPA_RBO_LE://less than or equal to operation (<=)
            std::cout << "  " << "sgt " << reg + ", " << lhs_reg + ", " << rhs_reg << std::endl;
            std::cout << "  " << "seqz " << reg + ", " << reg << std::endl;
            break;
        case KOOPA_RBO_GT://greater than operation (>)
            std::cout << "  " << "slt " << reg + ", " << rhs_reg + ", " << lhs_reg << std::endl;
            break;
        case KOOPA_RBO_GE://greater than or equal to operation (>=)
            std::cout << "  " << "sgt " << reg + ", " << rhs_reg + ", " << lhs_reg << std::endl;
            std::cout << "  " << "seqz " << reg + ", " << reg << std::endl;
            break;
        case KOOPA_RBO_AND://and operation (&)
            std::cout << "  " << "and " << reg + ", " << rhs_reg + ", " << lhs_reg << std::endl;
            break;
        case KOOPA_RBO_OR://or operation (|)
            std::cout << "  " << "or " << reg + ", " << rhs_reg + ", " << lhs_reg << std::endl;
            break;
        case KOOPA_RBO_XOR://exclusive or operation (^)
            std::cout << "  " << "xor " << reg + ", " << rhs_reg + ", " << lhs_reg << std::endl;
            break;
        case KOOPA_RBO_SHL://left shift operation (<<)
            std::cout << "  " << "sll " << reg + ", " << rhs_reg + ", " << lhs_reg << std::endl;
            break;
        case KOOPA_RBO_SHR://right shift operation (>>)
            std::cout << "  " << "srl " << reg + ", " << rhs_reg + ", " << lhs_reg << std::endl;
            break;
        default:
            std::cout << "Unhandled binary: " << bin.op << std::endl;//other types
            break;
    }
    return reg;
}

void Visit(const koopa_raw_branch_t &bran){
/*
    e.g. br %0, %then, %else
    @ bran: the operation
*/
    std::pair<int,std::string> cond=Visit(bran.cond);
    std::string reg = ValueToReg(cond);
    std::string true_bb = bran.true_bb->name;
    true_bb = true_bb.substr(1);
    std::string false_bb = bran.false_bb->name;
    false_bb = false_bb.substr(1);
    std::cout << "  " << "bnez " << reg + ", " << true_bb << std::endl;
    std::cout << "  " << "j " << false_bb << std::endl;
}

void Visit(const koopa_raw_call_t &call){
/*
    (%x =) call(a,b,c,...)
    deal with the call part only, exclude %x = ...
    the parameters are guaranteed to be integers or variables. No array currently.
    @ call: the operation
*/
    int para_num = 0;
    for(size_t i=0; i<call.args.len; i++){
        auto ptr = call.args.buffer[i];
        koopa_raw_value_t arg = reinterpret_cast<koopa_raw_value_t>(ptr);
        int reg_num = temp_reg;
        if(i<PARAM_NUM){
            if(arg->kind.tag == KOOPA_RVT_INTEGER)
                std::cout << "  " << "li a" << i << ", " << arg->kind.data.integer.value << std::endl;  
            else{
                std::pair<int, std::string> arg_ret = Visit(arg);
                std::string arg_reg = ValueToReg(arg_ret);
                std::cout << "  mv a" << i << ", " << arg_reg << std::endl;
            }
        }
        else{
            std::pair<int, std::string> arg_ret = Visit(arg);
            std::string arg_reg = ValueToReg(arg_ret);
            WriteToAddress(arg_reg, para_num);
            para_num += 4;
        }
        temp_reg = reg_num;
    }
    std::string fun_name = call.callee->name;
    fun_name = fun_name.substr(1);
    std::cout << "  " << "call " << fun_name << std::endl;
}

std::pair<std::string,int> Visit(const koopa_raw_global_alloc_t &glo){
/*
    global @var_n = alloc ...
    if not initialized by user, array is guaranteed to either filling 0 or zeroinit
    @ glo: the variable
    @ return: (variable name(new), array length(0 otherwise))
*/
    std::cout << "  " << ".data" << std::endl;
    std::string glo_name = "var_"+std::to_string(glo_var_num++);
    std::cout << "  " << ".global " << glo_name << std::endl;  // output the global variable
    std::cout << glo_name << ":" << std::endl;  //output the variable name
    int len=0;//array length (if any)
    switch(glo.init->kind.tag){
        case KOOPA_RVT_INTEGER:
            std::cout << "  " << ".word " << glo.init->kind.data.integer.value << std::endl << std::endl;
            break;
        case KOOPA_RVT_ZERO_INIT:
            if(glo.init->ty->tag == KOOPA_RTT_ARRAY){
                len = TypeSize(glo.init->ty);
                std::cout << "  " << ".zero " << len << std::endl << std::endl;
                len /= 4;
            }
            else
                std::cout << "  " << ".zero " << "4" << std::endl << std::endl;
            break;
        case KOOPA_RVT_AGGREGATE://alloc[i32, n],{1,2,3,...}
            len=Visit(glo.init->kind.data.aggregate);
            std::cout << std::endl;
            break;
        default:
            std::cout << "Global_Unhandble type:" << glo.init->kind.tag << std::endl;//other types
            break;
    }
    return make_pair(glo_name, len);
}

int Visit(const koopa_raw_aggregate_t &agg){
/*
    @ agg: variable (array currently)
    @ return: array length (if any)
*/
    int len = 0;
    for(size_t j=0; j<(agg.elems).len; j++){//agg.elems: koopa_raw_slice_t
        auto ptr = (agg.elems).buffer[j];
        koopa_raw_value_t value = reinterpret_cast<koopa_raw_value_t>(ptr);
        switch(value->kind.tag){
            case KOOPA_RVT_INTEGER:
                len++;
                std::cout << "  " << ".word " << value->kind.data.integer.value << std::endl;
                break;
            case KOOPA_RVT_ZERO_INIT:
                if(value->ty->tag == KOOPA_RTT_ARRAY){
                    int size = TypeSize(value->ty);
                    len += size/4;
                    std::cout << "  " << ".zero " << size << std::endl;
                }
                else{
                    len++;
                    std::cout << "  " << ".zero " << "4" << std::endl;
                }
                break;
            case KOOPA_RVT_AGGREGATE:
                len += Visit(value->kind.data.aggregate);
                break;
            default:
                std::cout << "Global_Unhandble type:" << value->kind.tag << std::endl;//other types
                break;
        }
    }
    return len;
}

std::string Visit(const koopa_raw_get_elem_ptr_t &ptr){
/*
    e.g. %ptr1 = getelemptr @arr, 1
    get the address and stored in the regester
    @ ptr: the array address
    @ return : the regester
*/
    std::string src_reg = New_reg();
    if(ptr.src->kind.tag == KOOPA_RVT_GLOBAL_ALLOC){
        assert(glo_var_offset.find(ptr.src)!=glo_var_offset.end());
        std::string name = glo_var_offset[ptr.src];
        std::cout << "  " << "la " << src_reg + ", " << name << std::endl;
    }
    else{
        std::pair<int,std::string> src = Visit(ptr.src);
        assert(src.first!=-1);
        if(ValidStack(src.first))
            std::cout << "  " << "addi " << src_reg + ", " << "sp, " << src.first << std::endl;
        else{// operand must be a symbol with %lo/%pcrel_lo/%tprel_lo modifier or an integer in the range [-2048, 2047]
            std::string reg = New_reg();
            std::cout << "  " << "li " << reg + ", " << src.first << std::endl;
            std::cout << "  " << "add " << src_reg + ", " << "sp, " << reg << std::endl;
            temp_reg--;
        }
    }

    std::pair<int,std::string> inde=Visit(ptr.index);
    if(inde.second == "x0")
        return src_reg;
    std::string inde_reg = ValueToReg(inde);//?index out of range
    std::string reg = New_reg();
    std::cout << "  " << "li " << reg + ", " << " 4" << std::endl;
    std::cout << "  " << "mul " << reg + ", " << reg + ", " << inde_reg << std::endl;//?offset

    std::cout << "  " << "add " << src_reg + ", " << src_reg + ", " << reg << std::endl;
    temp_reg--;
    return src_reg;
}

std::pair<int,std::string> Visit(const koopa_raw_value_t &value){
/*
    deal with a value
    @ value: the value
    @ return: int: the address if stored in the stack (variable, pointer);
                   -1 otherwise;
              string: register's name if stored in the register (integer);
                      the address + "(tn)" as a pointer (global variable);
                      "" otherwise;
*/
    const auto &kind = value->kind;
    int32_t int_val;
    int sw_sta = -1;//stack address
    std::pair<std::string, int> pi;
    std::string sw_reg = "", reg, name;
    // std::cerr << ",,,"<<kind.tag << std::endl;

    switch(kind.tag){
        case KOOPA_RVT_ALLOC:
            // std::cerr << "HERE ALLOC" << std::endl;
            sw_sta = AllocateStackForVariable(value);
            //std::cerr << value->name << fun_mem.used_mem << std::endl;
            break;

        case KOOPA_RVT_LOAD:
            // std::cerr << "HERE LOAD" << std::endl;
            if (fun_mem.var_offset.find(value) != fun_mem.var_offset.end()) {
                sw_sta = fun_mem.var_offset[value];
                break;
            }
            reg = Visit(kind.data.load);
            sw_sta = AllocateStackForVariable(value);
            WriteToAddress(reg, sw_sta); 
            break; 

        case KOOPA_RVT_STORE:
            // std::cerr << "HERE STORE" << std::endl;
            if (fun_mem.var_offset.find(value) != fun_mem.var_offset.end()) {
                sw_sta = fun_mem.var_offset[value];
                break;
            }
            Visit(kind.data.store);
            break;

        case KOOPA_RVT_RETURN://return
            // std::cerr << "HERE RETURN" << std::endl;
            Visit(kind.data.ret);
            break;

        case KOOPA_RVT_BINARY:
            // std::cerr << "HERE BINARY" << std::endl;
            if (fun_mem.var_offset.find(value) != fun_mem.var_offset.end()) {
                sw_sta = fun_mem.var_offset[value];
                break;
            }
            reg = Visit(kind.data.binary);
            sw_sta = AllocateStackForVariable(value);
            WriteToAddress(reg, sw_sta);
            break;

        case KOOPA_RVT_INTEGER:
            // std::cerr << "HERE INT" << std::endl;
            int_val = kind.data.integer.value;
            if (int_val == 0){
                sw_reg = "x0";
            }else{
                sw_reg = New_reg();
                std::cout << "  " << "li " << sw_reg + ", " << int_val << std::endl;
            }
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
                sw_sta = AllocateStackForVariable(value);
                WriteToAddress("a0", sw_sta);
            }
            break;
        case KOOPA_RVT_GLOBAL_ALLOC:
            // std::cerr << "HERE GLOBAL" << std::endl;
            if (glo_var_offset.find(value) != glo_var_offset.end()) {
                name = glo_var_offset[value];
                sw_reg = New_reg();
                std::cout << "  " << "la " << sw_reg + ", " << name << std::endl;
                sw_reg = "0("+sw_reg+")";
                break;
            }
            pi = Visit(kind.data.global_alloc);
            glo_var_offset[value] = pi.first;
            glo_array_offset[value] = pi.second;
            break;
        case KOOPA_RVT_GET_ELEM_PTR:
            // std::cerr << "HERE ELEM" << std::endl;
            if (fun_mem.var_offset.find(value) != fun_mem.var_offset.end()) {
                sw_sta = fun_mem.var_offset[value];
                break;
            }
            reg = Visit(kind.data.get_elem_ptr);
            sw_sta = AllocateStackForVariable(value);
            WriteToAddress(reg, sw_sta);
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
            sw_reg = Visit(kind.data.aggregate);
            break;
        case KOOPA_RVT_FUNC_ARG_REF:/// Function argument reference.
            // std::cerr << "HERE ARG" << std::endl;
            sw_sta = fun_mem.param_offset[value].first;
            sw_reg = fun_mem.param_offset[value].second;
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


std::string ValueToReg(std::pair<int,std::string> ini){
/*
    get the needed value that stored in the stack or register.
    @ ini: the stored place
    @ return: the register that stored the need value or the address(for global variable);
*/
    if (ini.first!=-1) {//in the stack
        std::string reg = New_reg();
        ReadFromAddress(reg, ini.first);
        return reg;
    }
    int len = ini.second.length();
    if(len >= 4){//global variable
        std::string reg = ini.second.substr(2,len-3);
        std::cout << "  " << "lw " << reg + ", " << ini.second << std::endl;
        return reg;
    }
    return ini.second;//in the register
}

void WriteToAddress(std::string reg, int addr){
/*
    write value stored in register(reg) to the stack address.
*/
    if(ValidStack(addr)){
        std::cout << "  sw " << reg << ", " << addr << "(sp)" << std::endl;
    }
    else{
        std::string reg1 = New_reg();
        std::cout << "  " << "li " << reg1 + ", " << addr << std::endl;
        std::cout << "  " << "add " << reg1 + ", " << reg1 << ", sp" << std::endl;
        std::cout << "  sw " << reg << ", " << "0(" << reg1 << ")" << std::endl;
        temp_reg--;
    }
}

void ReadFromAddress(std::string reg, int addr){
/*
    read value stored the stack address addr and stored in registery reg.
*/
    if(ValidStack(addr))
        std::cout << "  " << "lw " << reg + ", " << addr << "(sp)" << std::endl;
    else{
        std::string reg1 = New_reg();
        std::cout << "  " << "li " << reg1 + ", " << addr << std::endl;
        std::cout << "  " << "add " << reg1 + ", " << reg1 << ", sp" << std::endl;
        std::cout << "  " << "lw " << reg + ", " << "0(" << reg1 << ")" << std::endl;
        temp_reg--;
    }
}

std::string New_reg(){
/*
    @ return: the avaliable register;
*/
    std::string reg = "t" + std::to_string(temp_reg++);
    return reg;
}

bool ValidStack(int sta){
    return sta>=-2048 && sta<2048;
}

