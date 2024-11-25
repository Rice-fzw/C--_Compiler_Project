#!/bin/bash
cmake -DCMAKE_BUILD_TYPE=Debug -B build
cmake --build build
./build/compiler -riscv debug/test6_1_1.c -s test.S
rm -rf build