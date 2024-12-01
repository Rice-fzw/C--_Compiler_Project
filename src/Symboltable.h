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

    struct Symbol {
        std::string type;  
        std::string value; 
        std::string KoopalR; 
        std::vector<int> ele;
        Symbol(std::string t,  std::string v,std::string k) : type(t), value(v) ,KoopalR(k){}
        Symbol(std::string t, std::string v, std::string k, const std::vector<int>& eleVector) 
        : type(t), value(v), KoopalR(k), ele(eleVector) {}
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
        void insertSymbol(const std::string& name, const std::string& type, const std::string& value, const std::string& koopalR, const std::vector<int>& ele);
        // check whether there is duplicate value, can be used to check whether a identifier has been initialized before insert 
        bool checkSymbolOK(const std::string name);
    
        // print all the symbol in current scope
        void printSymbolTable();

        // look for symbol 
        std::optional<std::shared_ptr<Symbol>> lookupSymbol(const std::string& name) ;
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
    };

#endif