#!/bin/bash
cmake -DCMAKE_BUILD_TYPE=Debug -B build
cmake --build build
./build/compiler -riscv debug/test9_3.c -o hello.S
rm -rf build