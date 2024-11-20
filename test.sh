#!/bin/bash
cmake -DCMAKE_BUILD_TYPE=Debug -B build
cmake --build build
<<<<<<< HEAD
./build/compiler -riscv debug/test.c -o test.S
=======
./build/compiler -koopa debug/test6_1.c -o hello.koopa
>>>>>>> IR-Generation
rm -rf build