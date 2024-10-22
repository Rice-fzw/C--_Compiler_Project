#ifndef TOKEN_H
#define TOKEN_H
#include <string>
#include <map>
#include <vector>
#include <stdexcept>

enum class SymbolType {
    LABEL,          // 代码标签
    DATA_LABEL,     // 数据段标签
    VARIABLE,       // 变量
    CONSTANT        // 常量
};

enum class DataType {
    WORD,           // .word
    HALF,           // .half
    BYTE,           // .byte
    ASCII,          // .ascii
    ASCIIZ,         // .asciiz
    SPACE          // .space
};

struct Symbol {
    std::string name;
    SymbolType type;
    uint32_t address;     // 符号的地址
    DataType dataType;    // 如果是数据，存储其类型
    size_t size;         // 数据的大小（字节数）
    bool isGlobal;       // 是否是全局符号
    
    Symbol(std::string n, SymbolType t, uint32_t addr, 
           DataType dt = DataType::WORD, size_t s = 4, bool global = false)
        : name(std::move(n)), type(t), address(addr), 
          dataType(dt), size(s), isGlobal(global) {}
};

class SymbolTable {
public:
    SymbolTable() = default;
    
    // 添加新符号
    void addSymbol(const std::string& name, SymbolType type, uint32_t address,
                  DataType dataType = DataType::WORD, size_t size = 4);
    
    // 设置符号为全局
    void setGlobal(const std::string& name);
    
    // 查找符号
    const Symbol& getSymbol(const std::string& name) const;
    
    // 检查符号是否存在
    bool exists(const std::string& name) const;
    
    // 获取符号地址
    uint32_t getAddress(const std::string& name) const;
    
    // 获取所有未解析的符号
    std::vector<std::string> getUndefinedSymbols() const;
    
    // 打印符号表（用于调试）
    void print() const;

private:
    std::map<std::string, Symbol> symbols;
    std::vector<std::string> undefinedSymbols;
};

#endif