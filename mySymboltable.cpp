#include <iostream>
#include <unordered_map>
#include <stack>
#include <string>
#include <memory> 
#include <optional>
#include "mySymboltable.h"
using namespace std;


    void mySymboltable::insertSymbol(const string& name, const string& type, const string& value,const string& koopalR){
        if(!checkSymbolOK(name)){
            cout<<"error! "<<name<<" has been declared"<<endl;
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

    void mySymboltable::printSymbolTable() {
        if (Symboltable.empty()) {
            cout << "  (Empty Scope)"<<endl;
            return;
        }

        for (const auto& [name, symbol] : Symboltable) {
            cout << "  Name: " << name << ", Type: " << symbol->type
                << ", Value: " << symbol->value
                << ", koopa: " << symbol->KoopalR
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





    



    
 