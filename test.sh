#!/bin/bash
cmake -DCMAKE_BUILD_TYPE=Debug -B build
cmake --build build
./build/compiler -riscv debug/test.c -o test.S
rm -rf build