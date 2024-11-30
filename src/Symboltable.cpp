#include <iostream>
#include <unordered_map>
#include <stack>
#include <string>
#include <memory> 
#include <optional>
#include "Symboltable.h"
#include "AST.h"
using namespace std;

    int fl = 0;

    Symbol::Symbol(std::string t, std::string v, std::string k) 
    : type(t), value(v), KoopalR(k), is_array(false), total_size(0) {}

    Symbol::Symbol(std::string t, const std::vector<std::unique_ptr<BaseAST>>& dims, 
                std::string v, std::string k) 
        : type(t), value(v), KoopalR(k), is_array(true) {
        total_size = 1;
        for(const auto& dim : dims) {
            int dim_size = dim->Calc();  // 现在可以调用Calc()了
            array_dims.push_back(dim_size);
            total_size *= dim_size;
        }
    }

    void mySymboltable::insertSymbol(const string& name, const string& type, const string& value,const string& koopalR){
        if(!checkSymbolOK(name)){
            cout<<"error! "<<name<<" has been declared"<<endl;
            fl = 1;
            return;
        }
       // shared_ptr<Symbol> ptr = make_shared<Symbol>(type,value,koopalR);
        Symboltable[name] = make_shared<Symbol>(type, value, koopalR); 
        
    }

    bool mySymboltable::checkSymbolOK(string name){
        for (auto it = Symboltable.begin(); it != Symboltable.end(); ++it) {
            if (it->first == name) {
                return false;
            }
        }
        return true;
    }

    optional<shared_ptr<Symbol>> mySymboltable::lookupSymbol(const string& name) {
        auto it = Symboltable.find(name);
        if (it != Symboltable.end()) {
            return it->second;
        }
        return nullopt;
    }

    // void mySymboltable::printSymbolTable() {
    //     if (Symboltable.empty()) {
    //         cout << "  (Empty Scope)"<<endl;
    //         return;
    //     }

    //     for (const auto& [name, symbol] : Symboltable) {
    //         cout << "  Name: " << name << ", Type: " << symbol->type
    //             << ", Value: " << symbol->value
    //             << ", koopa: " << symbol->KoopalR
    //             << endl;
    //     }
    // }

    void mySymboltable::printSymbolTable() {
    if (Symboltable.empty()) {
        cout << "  (Empty Scope)" << endl;
        return;
    }

    for (const auto& [name, symbol] : Symboltable) {
        cout << "  Name: " << name << ", Type: " << symbol->type
            << ", Value: " << symbol->value
            << ", koopa: " << symbol->KoopalR;
        if (symbol->is_array) {
            cout << ", Dims: [";
            for (size_t i = 0; i < symbol->array_dims.size(); ++i) {
                if (i > 0) cout << ", ";
                cout << symbol->array_dims[i];
            }
            cout << "]";
        }
        cout << endl;
    }
}

    void mySymboltable::insertArraySymbol(const std::string& name, 
                                        const std::string& type,
                                        const std::vector<std::unique_ptr<BaseAST>>& dims,
                                        const std::string& value, 
                                        const std::string& koopalR) {
        if (!checkSymbolOK(name)) {
            std::cout << "error! " << name << " has been declared" << std::endl;
            fl = 1;
            return;
        }
        
        // 验证数组维度的合法性
        for (const auto& dim : dims) {
            int size = dim->Calc();
            if (size <= 0) {
                std::cout << "error! Array size must be positive" << std::endl;
                fl = 1;
                return;
            }
        }
        
        Symboltable[name] = std::make_shared<Symbol>(type, dims, value, koopalR);
    }


    void Scope::insertScope(const mySymboltable& mst){
        scopes.push(mst);
    }

   mySymboltable* Scope::top() {
    if (scopes.empty()) {
        throw std::runtime_error("Stack is empty. Cannot top.");
    }
    mySymboltable* topScope = &scopes.top(); 
    return topScope; 
}

    void Scope::exitScope(){
        if (!scopes.empty()) {
            scopes.pop();
        } else {
            cout << "Error: No scope to exit."<<endl;
        }
    }

    void Scope::printSymbolTable() {
    cout << "SymbolTable (from top to bottom):"<<endl;
    stack<mySymboltable> tempScopes = scopes; 

    int scopeLevel = 0;
    while (!tempScopes.empty()) {
        mySymboltable currentScope = tempScopes.top(); 
        cout << "Scope Level " << scopeLevel++ << ":"<<endl;

        currentScope.printSymbolTable();

        tempScopes.pop(); 
    }
    cout << "-----------------"<<endl;
}

    optional<shared_ptr<Symbol>> Scope::lookupSymbol(const string& name) {
        stack<mySymboltable> tempScopes = scopes; 

        while (!tempScopes.empty()) {
            mySymboltable currentScope = tempScopes.top();
            tempScopes.pop();

            auto result = currentScope.lookupSymbol(name);
            if (result.has_value()) {
                return result;
            }
        }

        return nullopt; 
    }