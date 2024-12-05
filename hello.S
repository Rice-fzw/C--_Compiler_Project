  .text
  .global main
main:
  addi sp, sp, -48
  li t0, 1
  sw t0, 44(sp)
  li t0, 100
  sw t0, 40(sp)
  j while_entry_0
while_entry_0:
  lw t0, 44(sp)
  sw t0, 36(sp)
  lw t0, 36(sp)
  li t1, 2
  add t2, t0, t1
  sw t2, 32(sp)
  lw t0, 44(sp)
  sw t0, 28(sp)
  lw t0, 32(sp)
  sw t0, 44(sp)
  lw t0, 44(sp)
  sw t0, 24(sp)
  lw t0, 40(sp)
  sw t0, 20(sp)
  lw t0, 20(sp)
  li t1, 1
  add t2, t0, t1
  sw t2, 16(sp)
  lw t0, 16(sp)
  sw t0, 40(sp)
  lw t0, 24(sp)
  lw t1, 16(sp)
  slt t2, t0, t1
  sw t2, 12(sp)
  lw t0, 12(sp)
  bnez t0, while_body_0
  j while_end_0
while_body_0:
  j while_entry_0
while_end_0:
  li a0, 0
  addi sp, sp, 48
  ret

