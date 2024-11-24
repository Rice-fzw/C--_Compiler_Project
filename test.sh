#!/bin/bash
cmake -DCMAKE_BUILD_TYPE=Debug -B build
cmake --build build
./build/compiler -koopa debug/test5_1.c -o hello.koopa
rm -rf build