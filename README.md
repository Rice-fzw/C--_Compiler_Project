# C-- Compiler

A compiler that translates C-- to RISC-V assembly through intermexdiate output IR.

## Introduction

##### The description of C-- (C minus-minus)： a simplified intermediate c language, which supports the following features:

- Binary operations (e.g., addition, subtraction,  multiplication, division, logical operations)
- Variables
- Functions
- Control flow statements like continue, break, for, and while
- One-dimensional arrays
- Input integer type variable (eg. int a = getint(); )
- Input char type variable (eg. int b = getch(); which returns the ASCALL code of the read character)
- Output the string (eg. puts("C-- Compiler\n"); )

The difference from C language is that it does not have header files, does not support two-dimensional arrays and pointers, has its own unique input and output, and follows the same syntax rules
### Development environment: Docker

- ###### csc3002-dev-environment.tar includes the official Linux image of Docker, and downloads tools such as bison, llvm, cmakes, etc., and pulls them from Docker

### Setup Development Environment

##### The first method to enter Docker (Recommended!)
- For Windows
```bash
load -i csc3002-dev-environment.tar at the command line
docker run it -- rm -- platform Linux/amd64-v Local-file-directory:/workspace - w/workspace csc3002 dev image bash
```
- For Linux or Macos
```bash
load < csc3002-dev-environment.tar at the command line
docker run it -- rm -- platform Linux/amd64-v Local-file-directory:/workspace - w/workspace csc3002 dev image bash
```

##### Another way to setup docker (may encounter network issues)
```bash
docker build -t csc3002-dev-image .
docker run -it --rm --platform linux/amd64 -v Local-file-directory:/workspace -w /workspace csc3002-dev-image bash
```
### How to use our Compiler

##### First, run the following instruction to synthesize the written code into a compiler. (If there is already a build folder, ignore it.)
```bash
sh build.sh
```
##### If the compiler has already been synthesized, change the path of the object code file in test.sh to the object code file you want, save it, and run the following command.
```bash
sh test.sh
```
### Basic Features

1. Compiles C-- programs to IR
2. Translates IR to RISC-V assembly
3. Implements register allocation to optimize performance

### Key Characteristics

- Independently implement the entire process from file reading to assembly output
- Simple and correct implementation
- Recursive processing of nested AST data structures through a single traversal
- Output assembly language through recursive processing
- High accuracy and comprehensive testing coverage


## Compiler Design

#### Main Components

The compiler consists of 3 main modules:
- `lexer.cpp`, `lexer.h` and `c--.y`: Lexical and syntax analysis
- `IR.h`: Compiles C-- source code to IR
- `RISCV.h`: Compiles IR to RISC-V instructions

#### Core Data Structures

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

Input C-- code:
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

Generated IR:
```
decl @getint(): i32
decl @getch(): i32
decl @getarray(*i32): i32
decl @putint(i32)
decl @putch(i32)
decl @putarray(i32, *i32)
decl @starttime()
decl @stoptime()

global  @a_0 = alloc i32, 10

fun @inc(): i32 {
%entry:
  %0 = load @a_0
  %1 = add %0, 1
  %2 = load @a_0
  store %1, @a_0
  %3 = load @a_0
  %4 = load @a_0
  ret %4
}

fun @print_a() {
%entry:
  %5 = load @a_0
  call @putint(%5)
  call @putch(10)
  ret
}

fun @main(): i32 {
%entry:
  @i_0 = alloc i32
  store 0, @i_0
  jump %while_entry_0
%while_entry_0:
  %6 = load @i_0
  %7 = lt %6, 10
  br %7, %while_body_0, %while_end_0
%while_body_0:
  %8 = call @inc()
  @a_1 = alloc i32
  store 1, @a_1
  %9 = load @a_1
  %10 = add %9, 2
  %11 = load @a_1
  store %10, @a_1
  %12 = load @a_1
  %13 = load @a_1
  call @putint(%13)
  call @putch(10)
  call @print_a()
  %14 = load @i_0
  %15 = add %14, 1
  %16 = load @i_0
  store %15, @i_0
  %17 = load @i_0
  jump %while_entry_0
%while_end_0:
  ret 0
}
```

The compiler then generates RISC-V assembly from this IR.

## Key Features

### *Register Allocation

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