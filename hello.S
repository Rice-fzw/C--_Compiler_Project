  .data
  .global var_0
var_0:
  .word 10

  .text
  .global inc
inc:
  addi sp, sp, -32
  la t0, var_0
  lw t0, 0(t0)
  sw t0, 28(sp)
  lw t0, 28(sp)
  li t1, 1
  add t2, t0, t1
  sw t2, 24(sp)
  la t0, var_0
  lw t0, 0(t0)
  sw t0, 20(sp)
  lw t0, 24(sp)
  la t1, var_0
  sw t0, 0(t1)
  la t0, var_0
  lw t0, 0(t0)
  sw t0, 16(sp)
  la t0, var_0
  lw t0, 0(t0)
  sw t0, 12(sp)
  lw a0, 12(sp)
  addi sp, sp, 32
  ret

  .text
  .global print_a
print_a:
  addi sp, sp, -16
  sw ra, 12(sp)
  la t0, var_0
  lw t0, 0(t0)
  sw t0, 8(sp)
  lw t0, 8(sp)
  mv a0, t0
  call putint
  li a0, 10
  call putch
  lw ra, 12(sp)
  addi sp, sp, 16
  ret

  .text
  .global main
main:
  addi sp, sp, -64
  sw ra, 60(sp)
  sw x0, 56(sp)
  j while_entry_0
while_entry_0:
  lw t0, 56(sp)
  sw t0, 52(sp)
  lw t0, 52(sp)
  li t1, 10
  slt t2, t0, t1
  sw t2, 48(sp)
  lw t0, 48(sp)
  bnez t0, while_body_0
  j while_end_0
while_body_0:
  call inc
  sw a0, 44(sp)
  li t0, 1
  sw t0, 40(sp)
  lw t0, 40(sp)
  sw t0, 36(sp)
  lw t0, 36(sp)
  li t1, 2
  add t2, t0, t1
  sw t2, 32(sp)
  lw t0, 40(sp)
  sw t0, 28(sp)
  lw t0, 32(sp)
  sw t0, 40(sp)
  lw t0, 40(sp)
  sw t0, 24(sp)
  lw t0, 40(sp)
  sw t0, 20(sp)
  lw t0, 20(sp)
  mv a0, t0
  call putint
  li a0, 10
  call putch
  call print_a
  lw t0, 56(sp)
  sw t0, 16(sp)
  lw t0, 16(sp)
  li t1, 1
  add t2, t0, t1
  sw t2, 12(sp)
  lw t0, 56(sp)
  sw t0, 8(sp)
  lw t0, 12(sp)
  sw t0, 56(sp)
  lw t0, 56(sp)
  sw t0, 4(sp)
  j while_entry_0
while_end_0:
  li a0, 0
  lw ra, 60(sp)
  addi sp, sp, 64
  ret

