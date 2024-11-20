# SysY Compiler

A compiler that translates SysY (a subset of C language) to RISC-V assembly via Koopa IR. This is a course project for PKU Compiler Principles.

## Introduction

Development environment: [compiler-dev](https://github.com/pku-minic/compiler-dev)

### Setup Development Environment

```bash
docker pull maxxing/compiler-dev
```

### Basic Features

1. Compiles SysY programs to Koopa IR
2. Translates Koopa IR to RISC-V assembly
3. Implements register allocation to optimize performance

### Key Characteristics

- Simple and correct implementation
- Recursively processes nested AST data structures with a single pass
- High correctness with comprehensive test coverage
- Uses tiered register allocation strategy for better performance

## Compiler Design

### Main Components

The compiler consists of 3 main modules:
- `sysy.l` and `sysy.y`: Lexical and syntax analysis
- `AST.h`: Compiles SysY source code to Koopa IR
- `RISCV.h`: Compiles Koopa IR to RISC-V instructions

### Core Data Structures

The most important data structure is the AST (Abstract Syntax Tree). A `CompUnitAST` instance represents the root of the tree, containing all function definitions and global variable definitions. Some key classes include:

- `FuncDefAST`: Function definitions
- `ConstDeclAST` and `ConstDefAST`: Constant declarations and definitions
- `VarDeclAST` and `VarDefAST`: Variable declarations and definitions
- `BlockAST`: Statement blocks
- `StmtAST`: Statements
- `ExpAST`: Expressions

All AST classes inherit from the base class `BaseAST`.

### Example Code Translation

Here's an example showing how the compiler works:

Input SysY code:
```c
int a = 10;

int inc() {
  a = a + 1;
  return a;
}

void print_a() {
  putint(a);
  putch(10);
}

int main() {
  int i = 0;
  while (i < 10) {
    inc();
    int a = 1;
    a = a + 2;
    putint(a);
    putch(10);
    print_a();
    i = i + 1;
  }
  return 0;
}
```

Generated Koopa IR:
```
decl @putint(i32)
decl @putch(i32)

global @COMPILER__a_ = alloc i32, 10
fun @inc(): i32{
%entry:
  %0 = load @COMPILER__a_
  %1 = add %0, 1
  store %1, @COMPILER__a_
  %2 = load @COMPILER__a_
  ret %2
}

fun @print_a(){
%entry:
  %3 = load @COMPILER__a_
  call @putint(%3)
  call @putch(10)
  ret
}

fun @main(): i32{
%entry:
  @COMPILER__i__43_0 = alloc i32
  store 0, @COMPILER__i__43_0
  jump %while_1
  // ... [rest of the main function]
}
```

The compiler then generates RISC-V assembly from this Koopa IR.

## Key Features

### Register Allocation

The compiler uses a simple but effective register allocation strategy:
- Each register has a `reg_stats` value (0, 1, or 2)
- 0: Register is empty or contains unimportant value
- 1: Value might be used later
- 2: Value cannot be replaced (protected)

## Testing

The compiler handles various edge cases including:
- Variable name conflicts between global and local scopes
- Function names as variable names
- Constants/variables named "main"
- Label and variable name conflicts

Example test case:
```c
int x = 3;

int f(int then) {
    return x + then;
}

int main() {
    int f = 2, x = 5;
    if (x > 3) f = 3;
    const int main[2] = {1, 2};
    return f(main[1] + x + f);
}
```

## Known Limitations

- Some advanced compiler optimizations (like graph coloring for register allocation, live variable analysis, available expression analysis) are not implemented
- Limited error handling and diagnostics