
void SymbolTable::addSymbol(const std::string& name, SymbolType type, 
                           uint32_t address, DataType dataType, size_t size) {
    if (symbols.find(name) != symbols.end()) {
        throw std::runtime_error("Symbol '" + name + "' already defined");
    }
    
    symbols.emplace(name, Symbol(name, type, address, dataType, size));
    
    // 如果这个符号之前是未定义的，现在已经定义了，就从未定义列表中移除
    auto it = std::find(undefinedSymbols.begin(), undefinedSymbols.end(), name);
    if (it != undefinedSymbols.end()) {
        undefinedSymbols.erase(it);
    }
}

void SymbolTable::setGlobal(const std::string& name) {
    auto it = symbols.find(name);
    if (it == symbols.end()) {
        throw std::runtime_error("Symbol '" + name + "' not found");
    }
    it->second.isGlobal = true;
}

const Symbol& SymbolTable::getSymbol(const std::string& name) const {
    auto it = symbols.find(name);
    if (it == symbols.end()) {
        throw std::runtime_error("Symbol '" + name + "' not found");
    }
    return it->second;
}

bool SymbolTable::exists(const std::string& name) const {
    return symbols.find(name) != symbols.end();
}

uint32_t SymbolTable::getAddress(const std::string& name) const {
    auto it = symbols.find(name);
    if (it == symbols.end()) {
        // 如果符号不存在，添加到未定义符号列表
        if (std::find(undefinedSymbols.begin(), undefinedSymbols.end(), name) 
            == undefinedSymbols.end()) {
            const_cast<SymbolTable*>(this)->undefinedSymbols.push_back(name);
        }
        return 0; // 返回0作为占位符
    }
    return it->second.address;
}

std::vector<std::string> SymbolTable::getUndefinedSymbols() const {
    return undefinedSymbols;
}

void SymbolTable::print() const {
    std::cout << "\nSymbol Table:\n";
    std::cout << std::left << std::setw(20) << "Name" 
              << std::setw(15) << "Type"
              << std::setw(15) << "Address"
              << std::setw(10) << "Size"
              << "Global" << std::endl;
    std::cout << std::string(70, '-') << std::endl;
    
    for (const auto& [name, symbol] : symbols) {
        std::cout << std::left << std::setw(20) << symbol.name;
        
        // 转换SymbolType为字符串
        std::string typeStr;
        switch (symbol.type) {
            case SymbolType::LABEL: typeStr = "LABEL"; break;
            case SymbolType::DATA_LABEL: typeStr = "DATA_LABEL"; break;
            case SymbolType::VARIABLE: typeStr = "VARIABLE"; break;
            case SymbolType::CONSTANT: typeStr = "CONSTANT"; break;
        }
        
        std::cout << std::setw(15) << typeStr
                  << std::setw(15) << std::hex << "0x" << symbol.address
                  << std::dec << std::setw(10) << symbol.size
                  << (symbol.isGlobal ? "Yes" : "No") << std::endl;
    }
    
    if (!undefinedSymbols.empty()) {
        std::cout << "\nUndefined Symbols:\n";
        for (const auto& sym : undefinedSymbols) {
            std::cout << sym << std::endl;
        }
    }
}