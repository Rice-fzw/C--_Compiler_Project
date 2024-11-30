#ifndef Symboltable_h
#define Symboltable_h

//this header file include three type: symbol, mySymboltable, Scope 

#include <iostream>
#include <unordered_map>
#include <stack>
#include <string>
#include <memory> 
#include <optional>
#include <vector>

class BaseAST;

    struct Symbol {
        std::string type;    // "int", "const_int", "array", "const_array"
        std::string value; 
        std::string KoopalR; 
        std::vector<int> array_dims;  // 数组维度信息
        bool is_array;       // 是否是数组
        int total_size;      // 数组总大小（所有维度相乘）
        
        // 原来的构造函数
        // Symbol(std::string t,  std::string v,std::string k) : type(t), value(v) ,KoopalR(k){}

        Symbol(std::string t, std::string v, std::string k);
        Symbol(std::string t, const std::vector<std::unique_ptr<BaseAST>>& dims, 
            std::string v, std::string k);

        // 获取指定维度的大小
        int getDimSize(int dim_index) const {
            if (dim_index < 0 || dim_index >= array_dims.size()) {
                return -1; // 错误的维度索引
            }
            return array_dims[dim_index];
        }

        // 获取维度数量
        int getDimCount() const {
            return array_dims.size();
        }

        // 检查数组访问是否合法
        bool checkArrayAccess(const std::vector<int>& indices) const {
            if (!is_array || indices.size() != array_dims.size()) {
                return false;
            }
            for (size_t i = 0; i < indices.size(); i++) {
                if (indices[i] < 0 || indices[i] >= array_dims[i]) {
                    return false;
                }
            }
            return true;
        }
    };

    //representing one scope
    class mySymboltable {

    private:
        std::unordered_map<std::string, std::shared_ptr<Symbol>> Symboltable; 

    public:  
        mySymboltable(){
        }; 

        // insert a type into the current scope
        void insertSymbol(const std::string& name, const std::string& type, const std::string& value,const std::string& koopalR);

        // check whether there is duplicate value, can be used to check whether a identifier has been initialized before insert 
        bool checkSymbolOK(const std::string name);
    
        // print all the symbol in current scope
        void printSymbolTable();

        // look for symbol 
        std::optional<std::shared_ptr<Symbol>> lookupSymbol(const std::string& name);

        //insert array symbol
        void insertArraySymbol(const std::string& name, 
                      const std::string& type,
                      const std::vector<std::unique_ptr<BaseAST>>& dims,
                      const std::string& value, 
                      const std::string& koopalR = "");
    };

    // for implementing nested scope
    class Scope {

    private:
        std::stack<mySymboltable> scopes; 

    public:
        Scope(){

        };

        //to get the most current scope, users should be careful when the scope is empty
        mySymboltable* top();

        // to exit current scope 
        void exitScope() ;

        // to insert a new symboltable, namely, a scope
        void insertScope(const mySymboltable& mst);
    
        // look for symbol from local to global
        std::optional<std::shared_ptr<Symbol>> lookupSymbol(const std::string& name);

        // print all the symbol in all scopes
        void printSymbolTable();

        bool isGlobalScope() const {
        return scopes.size() == 1;
        }
    };

#endif