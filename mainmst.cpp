#include <iostream>
#include <string>
#include "mySymboltable.h"
using namespace std;

int main() {
    Scope scopeManager;

    // 全局作用域
    mySymboltable globalScope;
    globalScope.insertSymbol("x", "int", "10","koopa1");
    globalScope.insertSymbol("y", "float", "3.14","koopa2");
    //重复插入y会报错
    globalScope.insertSymbol("y", "float", "3.14","koopa2");
    scopeManager.insertScope(globalScope);

    // 打印全局作用域
    cout << "Initial Scope:"<<endl;
    scopeManager.printSymbolTable();

    // 进入新作用域 比如说遇到if while语句的时候
    mySymboltable localScope1;
    localScope1.insertSymbol("z", "const", "16","koopa3");
    scopeManager.insertScope(localScope1);

    // 打印当前作用域
    cout << "\nAfter entering a new scope:"<<endl;
    scopeManager.printSymbolTable();

    // 全局查询符号x
    cout << "\nSymbol lookup test:"<<endl;
    //symbol 是存optional<shared_ptr<Symbol>>的容器，symbol.value（）是一个智能指针
    auto symbol = scopeManager.lookupSymbol("x"); 
    if (symbol.has_value()) {
        cout << "Found symbol: Type = " << symbol.value()->type
             << ", Value = " << symbol.value()->value <<", Koopa = " << symbol.value()->KoopalR << endl;
    } else {
        cout << "Symbol 'x' not found.\n";
    }

    // 进入另一个新作用域
    mySymboltable localScope2;
    localScope2.insertSymbol("x", "int", "20","koopa4"); // 局部变量 x
    scopeManager.insertScope(localScope2);

    cout << "\nAfter entering another scope:"<<endl;
    scopeManager.printSymbolTable();

    // 查询覆盖的变量 x
    //symbol2 是存optional<shared_ptr<Symbol>>的容器，symbol2.value（）是一个智能指针
    auto symbol2 = scopeManager.lookupSymbol("x");
    if (symbol2.has_value()) {
        cout << "Found symbol: Type = " << symbol2.value()->type
             << ", Value = " << symbol2.value()->value <<", Koopa = " << symbol.value()->KoopalR << endl;
    } else {
        cout << "Symbol 'x' not found."<<endl;
    }

    // 退出当前作用域
    scopeManager.exitScope();
    cout << "\nAfter exiting the current scope:"<<endl;
    scopeManager.printSymbolTable();

    //retrieveValue 函数的用法 ，输入name，找值
    auto value =localScope1.retrieveValue("z");
    cout<<value.value()<<endl;

    //lookupSymbol 功能覆盖了retrieveValue，除了获取值，还可以获取type，获取koopa，不过写起来繁琐一点，如果retrieveValue用不太到删掉也OK
    auto value2 =localScope1.lookupSymbol("z");
    cout<<value2.value()->value<<endl;

    return 0;
}
