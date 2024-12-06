#!/bin/bash

# The address of the program you want to compile
filename=$(basename "./debug/maze.c" .c)

./build/compiler -riscv debug/${filename}.c -o ${filename}.S
if [ -f "./${filename}.S" ]; then
    clang ${filename}.S -c -o ${filename}.o -target riscv32-unknown-linux-elf -march=rv32im -mabi=ilp32
    ld.lld ${filename}.o -L/workspace/opt/lib/riscv32 -lsysy -o ${filename}
    qemu-riscv32-static ${filename}
    echo $?
fi
rm -rf ${filename}.S
rm -rf ${filename}.o
#rm -rf ${filename}