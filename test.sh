#!/bin/bash
cmake -DCMAKE_BUILD_TYPE=Debug -B build
cmake --build build
./build/compiler -koopa debug/extra.c -o hello.S
rm -rf build