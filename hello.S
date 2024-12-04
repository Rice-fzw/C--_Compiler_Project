  .data
  .global var_0
var_0:
  .zero 4

  .data
  .global var_1
var_1:
  .zero 120000

  .data
  .global var_2
var_2:
  .zero 120000

  .text
  .global rand
rand:
  addi sp, sp, -64
  la t0, var_0
  lw t0, 0(t0)
  sw t0, 60(sp)
  lw t0, 60(sp)
  li t1, 214013
  mul t2, t0, t1
  sw t2, 56(sp)
  lw t0, 56(sp)
  li t1, 2531011
  add t2, t0, t1
  sw t2, 52(sp)
  lw t0, 52(sp)
  li t1, 1073741824
  rem t2, t0, t1
  sw t2, 48(sp)
  la t0, var_0
  lw t0, 0(t0)
  sw t0, 44(sp)
  lw t0, 48(sp)
  la t1, var_0
  sw t0, 0(t1)
  la t0, var_0
  lw t0, 0(t0)
  sw t0, 40(sp)
  lw t0, 40(sp)
  slt t1, t0, x0
  sw t1, 36(sp)
  lw t0, 36(sp)
  bnez t0, then_0
  j end_0
then_0:
  la t0, var_0
  lw t0, 0(t0)
  sw t0, 32(sp)
  lw t0, 32(sp)
  sub t1, x0, t0
  sw t1, 28(sp)
  la t0, var_0
  lw t0, 0(t0)
  sw t0, 24(sp)
  lw t0, 28(sp)
  la t1, var_0
  sw t0, 0(t1)
  j end_0
end_0:
  la t0, var_0
  lw t0, 0(t0)
  sw t0, 20(sp)
  lw t0, 20(sp)
  li t1, 65536
  div t2, t0, t1
  sw t2, 16(sp)
  lw t0, 16(sp)
  li t1, 32768
  rem t2, t0, t1
  sw t2, 12(sp)
  lw a0, 12(sp)
  addi sp, sp, 64
  ret

  .text
  .global get_neighbor
get_neighbor:
  addi sp, sp, -96
  sw a0, 92(sp)
  sw a1, 88(sp)
  sw a2, 84(sp)
  lw t0, 84(sp)
  sw t0, 80(sp)
  lw t0, 80(sp)
  xor t1, t0, x0
  seqz t1, t1
  sw t1, 76(sp)
  lw t0, 76(sp)
  bnez t0, then_1
  j else_1
then_1:
  lw t0, 92(sp)
  sw t0, 72(sp)
  lw t0, 72(sp)
  xor t1, t0, x0
  seqz t1, t1
  sw t1, 68(sp)
  lw t0, 68(sp)
  bnez t0, then_2
  j end_2
else_1:
  lw t0, 84(sp)
  sw t0, 64(sp)
  lw t0, 64(sp)
  li t1, 1
  xor t2, t0, t1
  seqz t2, t2
  sw t2, 60(sp)
  lw t0, 60(sp)
  bnez t0, then_3
  j else_3
then_2:
  li a0, 0
  addi sp, sp, 96
  ret

end_2:
  li a0, 1
  addi sp, sp, 96
  ret

then_3:
  lw t0, 92(sp)
  sw t0, 56(sp)
  li t0, 100
  li t1, 1
  sub t2, t0, t1
  sw t2, 52(sp)
  lw t0, 56(sp)
  lw t1, 52(sp)
  xor t2, t0, t1
  seqz t2, t2
  sw t2, 48(sp)
  lw t0, 48(sp)
  bnez t0, then_4
  j end_4
else_3:
  lw t0, 84(sp)
  sw t0, 44(sp)
  lw t0, 44(sp)
  li t1, 2
  xor t2, t0, t1
  seqz t2, t2
  sw t2, 40(sp)
  lw t0, 40(sp)
  bnez t0, then_5
  j else_5
then_4:
  li a0, 0
  addi sp, sp, 96
  ret

end_4:
  li a0, 1
  addi sp, sp, 96
  ret

then_5:
  lw t0, 88(sp)
  sw t0, 36(sp)
  lw t0, 36(sp)
  xor t1, t0, x0
  seqz t1, t1
  sw t1, 32(sp)
  lw t0, 32(sp)
  bnez t0, then_6
  j end_6
else_5:
  lw t0, 84(sp)
  sw t0, 28(sp)
  lw t0, 28(sp)
  li t1, 3
  xor t2, t0, t1
  seqz t2, t2
  sw t2, 24(sp)
  lw t0, 24(sp)
  bnez t0, then_7
  j end_7
then_6:
  li a0, 0
  addi sp, sp, 96
  ret

end_6:
  li a0, 1
  addi sp, sp, 96
  ret

then_7:
  lw t0, 88(sp)
  sw t0, 20(sp)
  li t0, 100
  li t1, 1
  sub t2, t0, t1
  sw t2, 16(sp)
  lw t0, 20(sp)
  lw t1, 16(sp)
  xor t2, t0, t1
  seqz t2, t2
  sw t2, 12(sp)
  lw t0, 12(sp)
  bnez t0, then_8
  j end_8
end_7:
  j end_5
then_8:
  li a0, 0
  addi sp, sp, 96
  ret

end_8:
  li a0, 1
  addi sp, sp, 96
  ret

end_5:
  j end_3
end_3:
  j end_1
end_1:
  li a0, 0
  addi sp, sp, 96
  ret

  .text
  .global remove_wall
remove_wall:
  addi sp, sp, -160
  sw a0, 156(sp)
  sw a1, 152(sp)
  sw a2, 148(sp)
  lw t0, 148(sp)
  sw t0, 144(sp)
  lw t0, 144(sp)
  xor t1, t0, x0
  seqz t1, t1
  sw t1, 140(sp)
  lw t0, 140(sp)
  bnez t0, then_9
  j else_9
then_9:
  lw t0, 152(sp)
  sw t0, 136(sp)
  lw t0, 136(sp)
  li t1, 100
  mul t2, t0, t1
  sw t2, 132(sp)
  lw t0, 156(sp)
  sw t0, 128(sp)
  lw t0, 132(sp)
  lw t1, 128(sp)
  add t2, t0, t1
  sw t2, 124(sp)
  la t0, var_1
  lw t1, 124(sp)
  li t2,  4
  mul t2, t2, t1
  add t0, t0, t2
  sw t0, 120(sp)
  lw t0, 120(sp)
  lw t0, 0(t0)
  sw t0, 116(sp)
  li t0, 1
  lw t1, 120(sp)
  sw t0, 0(t1)
  j end_9
else_9:
  lw t0, 148(sp)
  sw t0, 112(sp)
  lw t0, 112(sp)
  li t1, 1
  xor t2, t0, t1
  seqz t2, t2
  sw t2, 108(sp)
  lw t0, 108(sp)
  bnez t0, then_10
  j else_10
end_9:
  addi sp, sp, 160
  ret

then_10:
  lw t0, 152(sp)
  sw t0, 104(sp)
  lw t0, 104(sp)
  li t1, 100
  mul t2, t0, t1
  sw t2, 100(sp)
  lw t0, 156(sp)
  sw t0, 96(sp)
  lw t0, 96(sp)
  li t1, 1
  add t2, t0, t1
  sw t2, 92(sp)
  lw t0, 100(sp)
  lw t1, 92(sp)
  add t2, t0, t1
  sw t2, 88(sp)
  la t0, var_1
  lw t1, 88(sp)
  li t2,  4
  mul t2, t2, t1
  add t0, t0, t2
  sw t0, 84(sp)
  lw t0, 84(sp)
  lw t0, 0(t0)
  sw t0, 80(sp)
  li t0, 1
  lw t1, 84(sp)
  sw t0, 0(t1)
  j end_10
else_10:
  lw t0, 148(sp)
  sw t0, 76(sp)
  lw t0, 76(sp)
  li t1, 2
  xor t2, t0, t1
  seqz t2, t2
  sw t2, 72(sp)
  lw t0, 72(sp)
  bnez t0, then_11
  j else_11
end_10:
  j end_9
then_11:
  lw t0, 152(sp)
  sw t0, 68(sp)
  lw t0, 68(sp)
  li t1, 1
  sub t2, t0, t1
  sw t2, 64(sp)
  lw t0, 64(sp)
  li t1, 100
  mul t2, t0, t1
  sw t2, 60(sp)
  lw t0, 156(sp)
  sw t0, 56(sp)
  lw t0, 60(sp)
  lw t1, 56(sp)
  add t2, t0, t1
  sw t2, 52(sp)
  la t0, var_1
  lw t1, 52(sp)
  li t2,  4
  mul t2, t2, t1
  add t0, t0, t2
  sw t0, 48(sp)
  lw t0, 48(sp)
  lw t0, 0(t0)
  sw t0, 44(sp)
  li t0, 1
  lw t1, 48(sp)
  sw t0, 0(t1)
  j end_11
else_11:
  lw t0, 148(sp)
  sw t0, 40(sp)
  lw t0, 40(sp)
  li t1, 3
  xor t2, t0, t1
  seqz t2, t2
  sw t2, 36(sp)
  lw t0, 36(sp)
  bnez t0, then_12
  j end_12
end_11:
  j end_10
then_12:
  lw t0, 152(sp)
  sw t0, 32(sp)
  lw t0, 32(sp)
  li t1, 1
  add t2, t0, t1
  sw t2, 28(sp)
  lw t0, 28(sp)
  li t1, 100
  mul t2, t0, t1
  sw t2, 24(sp)
  lw t0, 156(sp)
  sw t0, 20(sp)
  lw t0, 24(sp)
  lw t1, 20(sp)
  add t2, t0, t1
  sw t2, 16(sp)
  la t0, var_1
  lw t1, 16(sp)
  li t2,  4
  mul t2, t2, t1
  add t0, t0, t2
  sw t0, 12(sp)
  lw t0, 12(sp)
  lw t0, 0(t0)
  sw t0, 8(sp)
  li t0, 1
  lw t1, 12(sp)
  sw t0, 0(t1)
  j end_12
end_12:
  j end_11
  .text
  .global gen_maze
gen_maze:
  addi sp, sp, -416
  sw ra, 412(sp)
  sw a0, 408(sp)
  sw a1, 404(sp)
  lw t0, 404(sp)
  sw t0, 400(sp)
  lw t0, 400(sp)
  li t1, 100
  mul t2, t0, t1
  sw t2, 396(sp)
  lw t0, 408(sp)
  sw t0, 392(sp)
  lw t0, 396(sp)
  lw t1, 392(sp)
  add t2, t0, t1
  sw t2, 388(sp)
  la t0, var_1
  lw t1, 388(sp)
  li t2,  4
  mul t2, t2, t1
  add t0, t0, t2
  sw t0, 384(sp)
  lw t0, 384(sp)
  lw t0, 0(t0)
  sw t0, 380(sp)
  lw t0, 384(sp)
  sw x0, 0(t0)
  addi t0, sp, 364
  sw t0, 360(sp)
  lw t0, 360(sp)
  sw x0, 0(t0)
  addi t0, sp, 364
  li t1, 1
  li t2,  4
  mul t2, t2, t1
  add t0, t0, t2
  sw t0, 356(sp)
  li t0, 1
  lw t1, 356(sp)
  sw t0, 0(t1)
  addi t0, sp, 364
  li t1, 2
  li t2,  4
  mul t2, t2, t1
  add t0, t0, t2
  sw t0, 352(sp)
  li t0, 2
  lw t1, 352(sp)
  sw t0, 0(t1)
  addi t0, sp, 364
  li t1, 3
  li t2,  4
  mul t2, t2, t1
  add t0, t0, t2
  sw t0, 348(sp)
  li t0, 3
  lw t1, 348(sp)
  sw t0, 0(t1)
  sw x0, 344(sp)
  j while_entry_0
while_entry_0:
  lw t0, 344(sp)
  sw t0, 340(sp)
  lw t0, 340(sp)
  li t1, 4
  slt t2, t0, t1
  sw t2, 336(sp)
  lw t0, 336(sp)
  bnez t0, while_body_0
  j while_end_0
while_body_0:
  call rand
  sw a0, 328(sp)
  lw t0, 328(sp)
  li t1, 4
  rem t2, t0, t1
  sw t2, 324(sp)
  lw t0, 324(sp)
  sw t0, 332(sp)
  lw t0, 344(sp)
  sw t0, 316(sp)
  addi t0, sp, 364
  lw t1, 316(sp)
  li t2,  4
  mul t2, t2, t1
  add t0, t0, t2
  sw t0, 312(sp)
  lw t0, 312(sp)
  lw t0, 0(t0)
  sw t0, 308(sp)
  lw t0, 308(sp)
  sw t0, 320(sp)
  lw t0, 332(sp)
  sw t0, 304(sp)
  addi t0, sp, 364
  lw t1, 304(sp)
  li t2,  4
  mul t2, t2, t1
  add t0, t0, t2
  sw t0, 300(sp)
  lw t0, 300(sp)
  lw t0, 0(t0)
  sw t0, 296(sp)
  lw t0, 344(sp)
  sw t0, 292(sp)
  addi t0, sp, 364
  lw t1, 292(sp)
  li t2,  4
  mul t2, t2, t1
  add t0, t0, t2
  sw t0, 288(sp)
  lw t0, 288(sp)
  lw t0, 0(t0)
  sw t0, 284(sp)
  lw t0, 296(sp)
  lw t1, 288(sp)
  sw t0, 0(t1)
  lw t0, 320(sp)
  sw t0, 280(sp)
  lw t0, 332(sp)
  sw t0, 276(sp)
  addi t0, sp, 364
  lw t1, 276(sp)
  li t2,  4
  mul t2, t2, t1
  add t0, t0, t2
  sw t0, 272(sp)
  lw t0, 272(sp)
  lw t0, 0(t0)
  sw t0, 268(sp)
  lw t0, 280(sp)
  lw t1, 272(sp)
  sw t0, 0(t1)
  lw t0, 344(sp)
  sw t0, 264(sp)
  lw t0, 264(sp)
  li t1, 1
  add t2, t0, t1
  sw t2, 260(sp)
  lw t0, 344(sp)
  sw t0, 256(sp)
  lw t0, 260(sp)
  sw t0, 344(sp)
  j while_entry_0
while_end_0:
  sw x0, 252(sp)
  j while_entry_1
while_entry_1:
  lw t0, 252(sp)
  sw t0, 248(sp)
  lw t0, 248(sp)
  li t1, 4
  slt t2, t0, t1
  sw t2, 244(sp)
  lw t0, 244(sp)
  bnez t0, while_body_1
  j while_end_1
while_body_1:
  lw t0, 408(sp)
  sw t0, 236(sp)
  lw t0, 236(sp)
  sw t0, 240(sp)
  lw t0, 404(sp)
  sw t0, 228(sp)
  lw t0, 228(sp)
  sw t0, 232(sp)
  lw t0, 240(sp)
  sw t0, 224(sp)
  lw t0, 232(sp)
  sw t0, 220(sp)
  lw t0, 252(sp)
  sw t0, 216(sp)
  addi t0, sp, 364
  lw t1, 216(sp)
  li t2,  4
  mul t2, t2, t1
  add t0, t0, t2
  sw t0, 212(sp)
  lw t0, 212(sp)
  lw t0, 0(t0)
  sw t0, 208(sp)
  lw t0, 224(sp)
  mv a0 ,t0
  lw t0, 220(sp)
  mv a1 ,t0
  lw t0, 208(sp)
  mv a2 ,t0
  call get_neighbor
  sw a0, 204(sp)
  lw t0, 204(sp)
  bnez t0, then__13
  j else__13
while_end_1:
  lw ra, 412(sp)
  addi sp, sp, 416
  ret

then__13:
  lw t0, 232(sp)
  sw t0, 196(sp)
  lw t0, 196(sp)
  li t1, 100
  mul t2, t0, t1
  sw t2, 192(sp)
  lw t0, 240(sp)
  sw t0, 188(sp)
  lw t0, 192(sp)
  lw t1, 188(sp)
  add t2, t0, t1
  sw t2, 184(sp)
  la t0, var_1
  lw t1, 184(sp)
  li t2,  4
  mul t2, t2, t1
  add t0, t0, t2
  sw t0, 180(sp)
  lw t0, 180(sp)
  lw t0, 0(t0)
  sw t0, 176(sp)
  lw t0, 176(sp)
  xor t1, t0, x0
  snez t1, t1
  sw t1, 172(sp)
  lw t0, 172(sp)
  xor t1, t0, x0
  snez t1, t1
  sw t1, 168(sp)
  lw t0, 168(sp)
  sw t0, 200(sp)
  j end__13
else__13:
  sw x0, 200(sp)
  j end__13
end__13:
  lw t0, 200(sp)
  sw t0, 164(sp)
  lw t0, 164(sp)
  bnez t0, then_14
  j end_14
then_14:
  lw t0, 408(sp)
  sw t0, 160(sp)
  lw t0, 404(sp)
  sw t0, 156(sp)
  lw t0, 252(sp)
  sw t0, 152(sp)
  addi t0, sp, 364
  lw t1, 152(sp)
  li t2,  4
  mul t2, t2, t1
  add t0, t0, t2
  sw t0, 148(sp)
  lw t0, 148(sp)
  lw t0, 0(t0)
  sw t0, 144(sp)
  lw t0, 160(sp)
  mv a0 ,t0
  lw t0, 156(sp)
  mv a1 ,t0
  lw t0, 144(sp)
  mv a2 ,t0
  call remove_wall
  lw t0, 252(sp)
  sw t0, 140(sp)
  addi t0, sp, 364
  lw t1, 140(sp)
  li t2,  4
  mul t2, t2, t1
  add t0, t0, t2
  sw t0, 136(sp)
  lw t0, 136(sp)
  lw t0, 0(t0)
  sw t0, 132(sp)
  lw t0, 132(sp)
  xor t1, t0, x0
  seqz t1, t1
  sw t1, 128(sp)
  lw t0, 128(sp)
  bnez t0, then_15
  j else_15
end_14:
  lw t0, 252(sp)
  sw t0, 124(sp)
  lw t0, 124(sp)
  li t1, 1
  add t2, t0, t1
  sw t2, 120(sp)
  lw t0, 252(sp)
  sw t0, 116(sp)
  lw t0, 120(sp)
  sw t0, 252(sp)
  j while_entry_1
then_15:
  lw t0, 240(sp)
  sw t0, 112(sp)
  lw t0, 112(sp)
  li t1, 1
  sub t2, t0, t1
  sw t2, 108(sp)
  lw t0, 240(sp)
  sw t0, 104(sp)
  lw t0, 108(sp)
  sw t0, 240(sp)
  j end_15
else_15:
  lw t0, 252(sp)
  sw t0, 100(sp)
  addi t0, sp, 364
  lw t1, 100(sp)
  li t2,  4
  mul t2, t2, t1
  add t0, t0, t2
  sw t0, 96(sp)
  lw t0, 96(sp)
  lw t0, 0(t0)
  sw t0, 92(sp)
  lw t0, 92(sp)
  li t1, 1
  xor t2, t0, t1
  seqz t2, t2
  sw t2, 88(sp)
  lw t0, 88(sp)
  bnez t0, then_16
  j else_16
end_15:
  lw t0, 240(sp)
  sw t0, 84(sp)
  lw t0, 232(sp)
  sw t0, 80(sp)
  lw t0, 84(sp)
  mv a0 ,t0
  lw t0, 80(sp)
  mv a1 ,t0
  call gen_maze
  j end_14
then_16:
  lw t0, 240(sp)
  sw t0, 76(sp)
  lw t0, 76(sp)
  li t1, 1
  add t2, t0, t1
  sw t2, 72(sp)
  lw t0, 240(sp)
  sw t0, 68(sp)
  lw t0, 72(sp)
  sw t0, 240(sp)
  j end_16
else_16:
  lw t0, 252(sp)
  sw t0, 64(sp)
  addi t0, sp, 364
  lw t1, 64(sp)
  li t2,  4
  mul t2, t2, t1
  add t0, t0, t2
  sw t0, 60(sp)
  lw t0, 60(sp)
  lw t0, 0(t0)
  sw t0, 56(sp)
  lw t0, 56(sp)
  li t1, 2
  xor t2, t0, t1
  seqz t2, t2
  sw t2, 52(sp)
  lw t0, 52(sp)
  bnez t0, then_17
  j else_17
end_16:
  j end_15
then_17:
  lw t0, 232(sp)
  sw t0, 48(sp)
  lw t0, 48(sp)
  li t1, 1
  sub t2, t0, t1
  sw t2, 44(sp)
  lw t0, 232(sp)
  sw t0, 40(sp)
  lw t0, 44(sp)
  sw t0, 232(sp)
  j end_17
else_17:
  lw t0, 252(sp)
  sw t0, 36(sp)
  addi t0, sp, 364
  lw t1, 36(sp)
  li t2,  4
  mul t2, t2, t1
  add t0, t0, t2
  sw t0, 32(sp)
  lw t0, 32(sp)
  lw t0, 0(t0)
  sw t0, 28(sp)
  lw t0, 28(sp)
  li t1, 3
  xor t2, t0, t1
  seqz t2, t2
  sw t2, 24(sp)
  lw t0, 24(sp)
  bnez t0, then_18
  j end_18
end_17:
  j end_16
then_18:
  lw t0, 232(sp)
  sw t0, 20(sp)
  lw t0, 20(sp)
  li t1, 1
  add t2, t0, t1
  sw t2, 16(sp)
  lw t0, 232(sp)
  sw t0, 12(sp)
  lw t0, 16(sp)
  sw t0, 232(sp)
  j end_18
end_18:
  j end_17
  .text
  .global render
render:
  addi sp, sp, -336
  sw x0, 332(sp)
  j while_entry_2
while_entry_2:
  lw t0, 332(sp)
  sw t0, 328(sp)
  lw t0, 328(sp)
  li t1, 100
  slt t2, t0, t1
  sw t2, 324(sp)
  lw t0, 324(sp)
  bnez t0, while_body_2
  j while_end_2
while_body_2:
  sw x0, 320(sp)
  j while_entry_3
while_end_2:
  lw t0, 332(sp)
  sw t0, 316(sp)
  sw x0, 332(sp)
  j while_entry_4
while_entry_3:
  lw t0, 320(sp)
  sw t0, 312(sp)
  lw t0, 312(sp)
  li t1, 100
  slt t2, t0, t1
  sw t2, 308(sp)
  lw t0, 308(sp)
  bnez t0, while_body_3
  j while_end_3
while_entry_4:
  lw t0, 332(sp)
  sw t0, 304(sp)
  li t0, 100
  li t1, 2
  mul t2, t0, t1
  sw t2, 300(sp)
  lw t0, 300(sp)
  li t1, 1
  add t2, t0, t1
  sw t2, 296(sp)
  lw t0, 304(sp)
  lw t1, 296(sp)
  slt t2, t0, t1
  sw t2, 292(sp)
  lw t0, 292(sp)
  bnez t0, while_body_4
  j while_end_4
while_body_3:
  lw t0, 332(sp)
  sw t0, 288(sp)
  lw t0, 288(sp)
  li t1, 100
  mul t2, t0, t1
  sw t2, 284(sp)
  lw t0, 320(sp)
  sw t0, 280(sp)
  lw t0, 284(sp)
  lw t1, 280(sp)
  add t2, t0, t1
  sw t2, 276(sp)
  la t0, var_1
  lw t1, 276(sp)
  li t2,  4
  mul t2, t2, t1
  add t0, t0, t2
  sw t0, 272(sp)
  lw t0, 272(sp)
  lw t0, 0(t0)
  sw t0, 268(sp)
  lw t0, 268(sp)
  li t1, 1
  xor t2, t0, t1
  seqz t2, t2
  sw t2, 264(sp)
  lw t0, 264(sp)
  bnez t0, then_19
  j end_19
while_end_3:
  lw t0, 332(sp)
  sw t0, 260(sp)
  lw t0, 260(sp)
  li t1, 1
  add t2, t0, t1
  sw t2, 256(sp)
  lw t0, 332(sp)
  sw t0, 252(sp)
  lw t0, 256(sp)
  sw t0, 332(sp)
  j while_entry_2
while_body_4:
  lw t0, 332(sp)
  sw t0, 248(sp)
  li t0, 100
  li t1, 2
  mul t2, t0, t1
  sw t2, 244(sp)
  lw t0, 244(sp)
  li t1, 1
  add t2, t0, t1
  sw t2, 240(sp)
  lw t0, 248(sp)
  lw t1, 240(sp)
  mul t2, t0, t1
  sw t2, 236(sp)
  li t0, 100
  li t1, 2
  mul t2, t0, t1
  sw t2, 232(sp)
  lw t0, 236(sp)
  lw t1, 232(sp)
  add t2, t0, t1
  sw t2, 228(sp)
  la t0, var_2
  lw t1, 228(sp)
  li t2,  4
  mul t2, t2, t1
  add t0, t0, t2
  sw t0, 224(sp)
  lw t0, 224(sp)
  lw t0, 0(t0)
  sw t0, 220(sp)
  li t0, 1
  lw t1, 224(sp)
  sw t0, 0(t1)
  lw t0, 332(sp)
  sw t0, 216(sp)
  lw t0, 216(sp)
  li t1, 1
  add t2, t0, t1
  sw t2, 212(sp)
  lw t0, 332(sp)
  sw t0, 208(sp)
  lw t0, 212(sp)
  sw t0, 332(sp)
  j while_entry_4
while_end_4:
  sw x0, 204(sp)
  j while_entry_5
then_19:
  lw t0, 332(sp)
  sw t0, 200(sp)
  lw t0, 200(sp)
  li t1, 2
  mul t2, t0, t1
  sw t2, 196(sp)
  lw t0, 196(sp)
  li t1, 1
  add t2, t0, t1
  sw t2, 192(sp)
  li t0, 100
  li t1, 2
  mul t2, t0, t1
  sw t2, 188(sp)
  lw t0, 188(sp)
  li t1, 1
  add t2, t0, t1
  sw t2, 184(sp)
  lw t0, 192(sp)
  lw t1, 184(sp)
  mul t2, t0, t1
  sw t2, 180(sp)
  lw t0, 320(sp)
  sw t0, 176(sp)
  lw t0, 176(sp)
  li t1, 2
  mul t2, t0, t1
  sw t2, 172(sp)
  lw t0, 180(sp)
  lw t1, 172(sp)
  add t2, t0, t1
  sw t2, 168(sp)
  la t0, var_2
  lw t1, 168(sp)
  li t2,  4
  mul t2, t2, t1
  add t0, t0, t2
  sw t0, 164(sp)
  lw t0, 164(sp)
  lw t0, 0(t0)
  sw t0, 160(sp)
  li t0, 1
  lw t1, 164(sp)
  sw t0, 0(t1)
  lw t0, 332(sp)
  sw t0, 156(sp)
  lw t0, 156(sp)
  li t1, 2
  mul t2, t0, t1
  sw t2, 152(sp)
  li t0, 100
  li t1, 2
  mul t2, t0, t1
  sw t2, 148(sp)
  lw t0, 148(sp)
  li t1, 1
  add t2, t0, t1
  sw t2, 144(sp)
  lw t0, 152(sp)
  lw t1, 144(sp)
  mul t2, t0, t1
  sw t2, 140(sp)
  lw t0, 320(sp)
  sw t0, 136(sp)
  lw t0, 136(sp)
  li t1, 2
  mul t2, t0, t1
  sw t2, 132(sp)
  lw t0, 132(sp)
  li t1, 1
  add t2, t0, t1
  sw t2, 128(sp)
  lw t0, 140(sp)
  lw t1, 128(sp)
  add t2, t0, t1
  sw t2, 124(sp)
  la t0, var_2
  lw t1, 124(sp)
  li t2,  4
  mul t2, t2, t1
  add t0, t0, t2
  sw t0, 120(sp)
  lw t0, 120(sp)
  lw t0, 0(t0)
  sw t0, 116(sp)
  li t0, 1
  lw t1, 120(sp)
  sw t0, 0(t1)
  j end_19
end_19:
  lw t0, 332(sp)
  sw t0, 112(sp)
  lw t0, 112(sp)
  li t1, 2
  mul t2, t0, t1
  sw t2, 108(sp)
  li t0, 100
  li t1, 2
  mul t2, t0, t1
  sw t2, 104(sp)
  lw t0, 104(sp)
  li t1, 1
  add t2, t0, t1
  sw t2, 100(sp)
  lw t0, 108(sp)
  lw t1, 100(sp)
  mul t2, t0, t1
  sw t2, 96(sp)
  lw t0, 320(sp)
  sw t0, 92(sp)
  lw t0, 92(sp)
  li t1, 2
  mul t2, t0, t1
  sw t2, 88(sp)
  lw t0, 96(sp)
  lw t1, 88(sp)
  add t2, t0, t1
  sw t2, 84(sp)
  la t0, var_2
  lw t1, 84(sp)
  li t2,  4
  mul t2, t2, t1
  add t0, t0, t2
  sw t0, 80(sp)
  lw t0, 80(sp)
  lw t0, 0(t0)
  sw t0, 76(sp)
  li t0, 1
  lw t1, 80(sp)
  sw t0, 0(t1)
  lw t0, 320(sp)
  sw t0, 72(sp)
  lw t0, 72(sp)
  li t1, 1
  add t2, t0, t1
  sw t2, 68(sp)
  lw t0, 320(sp)
  sw t0, 64(sp)
  lw t0, 68(sp)
  sw t0, 320(sp)
  j while_entry_3
while_entry_5:
  lw t0, 204(sp)
  sw t0, 60(sp)
  li t0, 100
  li t1, 2
  mul t2, t0, t1
  sw t2, 56(sp)
  lw t0, 56(sp)
  li t1, 1
  add t2, t0, t1
  sw t2, 52(sp)
  lw t0, 60(sp)
  lw t1, 52(sp)
  slt t2, t0, t1
  sw t2, 48(sp)
  lw t0, 48(sp)
  bnez t0, while_body_5
  j while_end_5
while_body_5:
  li t0, 100
  li t1, 2
  mul t2, t0, t1
  sw t2, 44(sp)
  li t0, 100
  li t1, 2
  mul t2, t0, t1
  sw t2, 40(sp)
  lw t0, 40(sp)
  li t1, 1
  add t2, t0, t1
  sw t2, 36(sp)
  lw t0, 44(sp)
  lw t1, 36(sp)
  mul t2, t0, t1
  sw t2, 32(sp)
  lw t0, 204(sp)
  sw t0, 28(sp)
  lw t0, 32(sp)
  lw t1, 28(sp)
  add t2, t0, t1
  sw t2, 24(sp)
  la t0, var_2
  lw t1, 24(sp)
  li t2,  4
  mul t2, t2, t1
  add t0, t0, t2
  sw t0, 20(sp)
  lw t0, 20(sp)
  lw t0, 0(t0)
  sw t0, 16(sp)
  li t0, 1
  lw t1, 20(sp)
  sw t0, 0(t1)
  lw t0, 204(sp)
  sw t0, 12(sp)
  lw t0, 12(sp)
  li t1, 1
  add t2, t0, t1
  sw t2, 8(sp)
  lw t0, 204(sp)
  sw t0, 4(sp)
  lw t0, 8(sp)
  sw t0, 204(sp)
  j while_entry_5
while_end_5:
  addi sp, sp, 336
  ret

  .text
  .global main
main:
  addi sp, sp, -368
  sw ra, 364(sp)
  la t0, var_0
  lw t0, 0(t0)
  sw t0, 360(sp)
  li t0, 12345678
  la t1, var_0
  sw t0, 0(t1)
  li t0, 2
  sw t0, 356(sp)
  call rand
  sw a0, 352(sp)
  lw t0, 352(sp)
  li t1, 100
  rem t2, t0, t1
  sw t2, 348(sp)
  call rand
  sw a0, 344(sp)
  lw t0, 344(sp)
  li t1, 100
  rem t2, t0, t1
  sw t2, 340(sp)
  lw t0, 348(sp)
  mv a0 ,t0
  lw t0, 340(sp)
  mv a1 ,t0
  call gen_maze
  call render
  li a0, 80
  call putch
  li a0, 51
  call putch
  li a0, 10
  call putch
  li t0, 100
  li t1, 2
  mul t2, t0, t1
  sw t2, 336(sp)
  lw t0, 336(sp)
  li t1, 1
  add t2, t0, t1
  sw t2, 332(sp)
  lw t0, 356(sp)
  sw t0, 328(sp)
  lw t0, 332(sp)
  lw t1, 328(sp)
  mul t2, t0, t1
  sw t2, 324(sp)
  lw t0, 324(sp)
  mv a0 ,t0
  call putint
  li a0, 32
  call putch
  li t0, 100
  li t1, 2
  mul t2, t0, t1
  sw t2, 320(sp)
  lw t0, 320(sp)
  li t1, 1
  add t2, t0, t1
  sw t2, 316(sp)
  lw t0, 356(sp)
  sw t0, 312(sp)
  lw t0, 316(sp)
  lw t1, 312(sp)
  mul t2, t0, t1
  sw t2, 308(sp)
  lw t0, 308(sp)
  mv a0 ,t0
  call putint
  li a0, 10
  call putch
  li a0, 255
  call putint
  li a0, 10
  call putch
  sw x0, 304(sp)
  j while_entry_6
while_entry_6:
  lw t0, 304(sp)
  sw t0, 300(sp)
  li t0, 100
  li t1, 2
  mul t2, t0, t1
  sw t2, 296(sp)
  lw t0, 296(sp)
  li t1, 1
  add t2, t0, t1
  sw t2, 292(sp)
  lw t0, 356(sp)
  sw t0, 288(sp)
  lw t0, 292(sp)
  lw t1, 288(sp)
  mul t2, t0, t1
  sw t2, 284(sp)
  lw t0, 300(sp)
  lw t1, 284(sp)
  slt t2, t0, t1
  sw t2, 280(sp)
  lw t0, 280(sp)
  bnez t0, while_body_6
  j while_end_6
while_body_6:
  sw x0, 276(sp)
  j while_entry_7
while_end_6:
  li a0, 0
  lw ra, 364(sp)
  addi sp, sp, 368
  ret

while_entry_7:
  lw t0, 276(sp)
  sw t0, 272(sp)
  li t0, 100
  li t1, 2
  mul t2, t0, t1
  sw t2, 268(sp)
  lw t0, 268(sp)
  li t1, 1
  add t2, t0, t1
  sw t2, 264(sp)
  lw t0, 356(sp)
  sw t0, 260(sp)
  lw t0, 264(sp)
  lw t1, 260(sp)
  mul t2, t0, t1
  sw t2, 256(sp)
  lw t0, 272(sp)
  lw t1, 256(sp)
  slt t2, t0, t1
  sw t2, 252(sp)
  lw t0, 252(sp)
  bnez t0, while_body_7
  j while_end_7
while_body_7:
  lw t0, 276(sp)
  sw t0, 244(sp)
  lw t0, 356(sp)
  sw t0, 240(sp)
  lw t0, 244(sp)
  lw t1, 240(sp)
  div t2, t0, t1
  sw t2, 236(sp)
  lw t0, 236(sp)
  sw t0, 248(sp)
  lw t0, 304(sp)
  sw t0, 228(sp)
  lw t0, 356(sp)
  sw t0, 224(sp)
  lw t0, 228(sp)
  lw t1, 224(sp)
  div t2, t0, t1
  sw t2, 220(sp)
  lw t0, 220(sp)
  sw t0, 232(sp)
  lw t0, 232(sp)
  sw t0, 212(sp)
  li t0, 100
  li t1, 2
  mul t2, t0, t1
  sw t2, 208(sp)
  lw t0, 208(sp)
  li t1, 1
  add t2, t0, t1
  sw t2, 204(sp)
  lw t0, 212(sp)
  lw t1, 204(sp)
  mul t2, t0, t1
  sw t2, 200(sp)
  lw t0, 248(sp)
  sw t0, 196(sp)
  lw t0, 200(sp)
  lw t1, 196(sp)
  add t2, t0, t1
  sw t2, 192(sp)
  la t0, var_2
  lw t1, 192(sp)
  li t2,  4
  mul t2, t2, t1
  add t0, t0, t2
  sw t0, 188(sp)
  lw t0, 188(sp)
  lw t0, 0(t0)
  sw t0, 184(sp)
  lw t0, 184(sp)
  li t1, 255
  mul t2, t0, t1
  sw t2, 180(sp)
  lw t0, 276(sp)
  sw t0, 176(sp)
  lw t0, 180(sp)
  lw t1, 176(sp)
  mul t2, t0, t1
  sw t2, 172(sp)
  li t0, 100
  li t1, 2
  mul t2, t0, t1
  sw t2, 168(sp)
  lw t0, 168(sp)
  li t1, 1
  add t2, t0, t1
  sw t2, 164(sp)
  lw t0, 356(sp)
  sw t0, 160(sp)
  lw t0, 164(sp)
  lw t1, 160(sp)
  mul t2, t0, t1
  sw t2, 156(sp)
  lw t0, 172(sp)
  lw t1, 156(sp)
  div t2, t0, t1
  sw t2, 152(sp)
  lw t0, 152(sp)
  sw t0, 216(sp)
  lw t0, 232(sp)
  sw t0, 144(sp)
  li t0, 100
  li t1, 2
  mul t2, t0, t1
  sw t2, 140(sp)
  lw t0, 140(sp)
  li t1, 1
  add t2, t0, t1
  sw t2, 136(sp)
  lw t0, 144(sp)
  lw t1, 136(sp)
  mul t2, t0, t1
  sw t2, 132(sp)
  lw t0, 248(sp)
  sw t0, 128(sp)
  lw t0, 132(sp)
  lw t1, 128(sp)
  add t2, t0, t1
  sw t2, 124(sp)
  la t0, var_2
  lw t1, 124(sp)
  li t2,  4
  mul t2, t2, t1
  add t0, t0, t2
  sw t0, 120(sp)
  lw t0, 120(sp)
  lw t0, 0(t0)
  sw t0, 116(sp)
  lw t0, 116(sp)
  li t1, 255
  mul t2, t0, t1
  sw t2, 112(sp)
  lw t0, 304(sp)
  sw t0, 108(sp)
  lw t0, 112(sp)
  lw t1, 108(sp)
  mul t2, t0, t1
  sw t2, 104(sp)
  li t0, 100
  li t1, 2
  mul t2, t0, t1
  sw t2, 100(sp)
  lw t0, 100(sp)
  li t1, 1
  add t2, t0, t1
  sw t2, 96(sp)
  lw t0, 356(sp)
  sw t0, 92(sp)
  lw t0, 96(sp)
  lw t1, 92(sp)
  mul t2, t0, t1
  sw t2, 88(sp)
  lw t0, 104(sp)
  lw t1, 88(sp)
  div t2, t0, t1
  sw t2, 84(sp)
  lw t0, 84(sp)
  sw t0, 148(sp)
  lw t0, 232(sp)
  sw t0, 76(sp)
  li t0, 100
  li t1, 2
  mul t2, t0, t1
  sw t2, 72(sp)
  lw t0, 72(sp)
  li t1, 1
  add t2, t0, t1
  sw t2, 68(sp)
  lw t0, 76(sp)
  lw t1, 68(sp)
  mul t2, t0, t1
  sw t2, 64(sp)
  lw t0, 248(sp)
  sw t0, 60(sp)
  lw t0, 64(sp)
  lw t1, 60(sp)
  add t2, t0, t1
  sw t2, 56(sp)
  la t0, var_2
  lw t1, 56(sp)
  li t2,  4
  mul t2, t2, t1
  add t0, t0, t2
  sw t0, 52(sp)
  lw t0, 52(sp)
  lw t0, 0(t0)
  sw t0, 48(sp)
  lw t0, 48(sp)
  li t1, 255
  mul t2, t0, t1
  sw t2, 44(sp)
  lw t0, 44(sp)
  sw t0, 80(sp)
  lw t0, 216(sp)
  sw t0, 40(sp)
  lw t0, 40(sp)
  mv a0 ,t0
  call putint
  li a0, 32
  call putch
  lw t0, 148(sp)
  sw t0, 36(sp)
  lw t0, 36(sp)
  mv a0 ,t0
  call putint
  li a0, 32
  call putch
  lw t0, 80(sp)
  sw t0, 32(sp)
  lw t0, 32(sp)
  mv a0 ,t0
  call putint
  li a0, 32
  call putch
  lw t0, 276(sp)
  sw t0, 28(sp)
  lw t0, 28(sp)
  li t1, 1
  add t2, t0, t1
  sw t2, 24(sp)
  lw t0, 276(sp)
  sw t0, 20(sp)
  lw t0, 24(sp)
  sw t0, 276(sp)
  j while_entry_7
while_end_7:
  li a0, 10
  call putch
  lw t0, 304(sp)
  sw t0, 16(sp)
  lw t0, 16(sp)
  li t1, 1
  add t2, t0, t1
  sw t2, 12(sp)
  lw t0, 304(sp)
  sw t0, 8(sp)
  lw t0, 12(sp)
  sw t0, 304(sp)
  j while_entry_6
