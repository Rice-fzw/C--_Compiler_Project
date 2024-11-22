#!/bin/bash
cmake -DCMAKE_BUILD_TYPE=Debug -B build
cmake --build build
./build/compiler -riscv debug/test4_2_3.c -o hello.s
rm -rf build