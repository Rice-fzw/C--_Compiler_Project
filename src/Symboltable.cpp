#include <iostream>
#include <unordered_map>
#include <stack>
#include <string>
#include <memory> 
#include <optional>
#include "Symboltable.h"
#include <IR.h>
using namespace std;

int fl = 0;

    void mySymboltable::insertSymbol(const string& name, const string& type, const string& value,const string& address){
        if(!checkSymbolOK(name)){
            cout<<"Error! "<<name<<" has been declared"<<endl;
            fl = 1;
            return;
        }
       // shared_ptr<Symbol> ptr = make_shared<Symbol>(type,value,address);
        Symboltable[name] = make_shared<Symbol>(type, value, address); 
        
    }

    void mySymboltable::insertSymbol(const string& name, const string& type, const string& value, const string& address, const std::vector<int>& ele) {
        if (!checkSymbolOK(name)) {
            cout << "Error! " << name << " has been declared" << endl;
            fl = 1;
            return;
        }
        Symboltable[name] = make_shared<Symbol>(type, value, address, ele);
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

    void mySymboltable::printSymbolTable() {
        if (Symboltable.empty()) {
            cout << "  (Empty Scope)"<<endl;
            return;
        }

        for (const auto& [name, symbol] : Symboltable) {
            cout << "  Name: " << name << ", Type: " << symbol->type
                << ", Value: " << symbol->value
                << ", address: " << symbol->address
                << endl;
        }
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