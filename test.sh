./build/compiler -riscv debug/test8_3.c -o hello.S
clang hello.S -c -o hello.o -target riscv32-unknown-linux-elf -march=rv32im -mabi=ilp32
ld.lld hello.o -L/workspace/opt/lib/riscv32 -lsysy -o hello
qemu-riscv32-static hello
echo $?