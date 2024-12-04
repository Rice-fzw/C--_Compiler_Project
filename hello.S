  .data
  .global var_0
var_0:
  .zero 4

  .data
  .global var_1
var_1:
  .zero 4

  .data
  .global var_2
var_2:
  .zero 4

  .data
  .global var_3
var_3:
  .zero 4

  .data
  .global var_4
var_4:
  .zero 4

  .data
  .global var_5
var_5:
  .word 1
  .word 2
  .word 4
  .word 8
  .word 16
  .word 32
  .word 64
  .word 128
  .word 256
  .word 512
  .word 1024
  .word 2048
  .word 4096
  .word 8192
  .word 16384
  .word 32768
  .word 65536
  .word 131072
  .word 262144
  .word 524288

  .data
  .global var_6
var_6:
  .word 0
  .word 1
  .word 1
  .word 1
  .word 2
  .word 2
  .word 2
  .word 3
  .word 3
  .word 3
  .word 4
  .word 4
  .word 4
  .word 4
  .word 5
  .word 5
  .word 5
  .word 6
  .word 6
  .word 6

  .data
  .global var_7
var_7:
  .zero 64

  .text
  .global get_index
get_index:
  addi sp, sp, -32
  sw a0, 28(sp)
  sw a1, 24(sp)
  lw t0, 28(sp)
  sw t0, 20(sp)
  lw t0, 20(sp)
  li t1, 4
  mul t2, t0, t1
  sw t2, 16(sp)
  lw t0, 24(sp)
  sw t0, 12(sp)
  lw t0, 16(sp)
  lw t1, 12(sp)
  add t2, t0, t1
  sw t2, 8(sp)
  lw a0, 8(sp)
  addi sp, sp, 32
  ret

  .text
  .global rand
rand:
  addi sp, sp, -64
  la t0, var_4
  lw t0, 0(t0)
  sw t0, 60(sp)
  lw t0, 60(sp)
  li t1, 414047
  mul t2, t0, t1
  sw t2, 56(sp)
  lw t0, 56(sp)
  li t1, 4531063
  add t2, t0, t1
  sw t2, 52(sp)
  lw t0, 52(sp)
  li t1, 1073741824
  rem t2, t0, t1
  sw t2, 48(sp)
  la t0, var_4
  lw t0, 0(t0)
  sw t0, 44(sp)
  lw t0, 48(sp)
  la t1, var_4
  sw t0, 0(t1)
  la t0, var_4
  lw t0, 0(t0)
  sw t0, 40(sp)
  lw t0, 40(sp)
  slt t1, t0, x0
  sw t1, 36(sp)
  lw t0, 36(sp)
  bnez t0, then_0
  j end_0
then_0:
  la t0, var_4
  lw t0, 0(t0)
  sw t0, 32(sp)
  lw t0, 32(sp)
  sub t1, x0, t0
  sw t1, 28(sp)
  la t0, var_4
  lw t0, 0(t0)
  sw t0, 24(sp)
  lw t0, 28(sp)
  la t1, var_4
  sw t0, 0(t1)
  j end_0
end_0:
  la t0, var_4
  lw t0, 0(t0)
  sw t0, 20(sp)
  lw t0, 20(sp)
  li t1, 41489
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
  .global clear_map
clear_map:
  addi sp, sp, -48
  sw x0, 44(sp)
  j while_entry_0
while_entry_0:
  lw t0, 44(sp)
  sw t0, 40(sp)
  li t0, 4
  li t1, 4
  mul t2, t0, t1
  sw t2, 36(sp)
  lw t0, 40(sp)
  lw t1, 36(sp)
  slt t2, t0, t1
  sw t2, 32(sp)
  lw t0, 32(sp)
  bnez t0, while_body_0
  j while_end_0
while_body_0:
  lw t0, 44(sp)
  sw t0, 28(sp)
  la t0, var_7
  lw t1, 28(sp)
  li t2,  4
  mul t2, t2, t1
  add t0, t0, t2
  sw t0, 24(sp)
  lw t0, 24(sp)
  lw t0, 0(t0)
  sw t0, 20(sp)
  lw t0, 24(sp)
  sw x0, 0(t0)
  lw t0, 44(sp)
  sw t0, 16(sp)
  lw t0, 16(sp)
  li t1, 1
  add t2, t0, t1
  sw t2, 12(sp)
  lw t0, 44(sp)
  sw t0, 8(sp)
  lw t0, 12(sp)
  sw t0, 44(sp)
  j while_entry_0
while_end_0:
  addi sp, sp, 48
  ret

  .text
  .global init
init:
  addi sp, sp, -32
  sw ra, 28(sp)
  call clear_map
  la t0, var_0
  lw t0, 0(t0)
  sw t0, 24(sp)
  la t0, var_0
  sw x0, 0(t0)
  la t0, var_1
  lw t0, 0(t0)
  sw t0, 20(sp)
  la t0, var_1
  sw x0, 0(t0)
  la t0, var_2
  lw t0, 0(t0)
  sw t0, 16(sp)
  li t0, 1
  la t1, var_2
  sw t0, 0(t1)
  la t0, var_3
  lw t0, 0(t0)
  sw t0, 12(sp)
  li t0, 1
  la t1, var_3
  sw t0, 0(t1)
  lw ra, 28(sp)
  addi sp, sp, 32
  ret

  .text
  .global print_map
print_map:
  addi sp, sp, -192
  sw ra, 188(sp)
  li a0, 10
  call putch
  li a0, 115
  call putch
  li a0, 116
  call putch
  li a0, 101
  call putch
  li a0, 112
  call putch
  li a0, 58
  call putch
  li a0, 32
  call putch
  la t0, var_1
  lw t0, 0(t0)
  sw t0, 184(sp)
  lw t0, 184(sp)
  mv a0 ,t0
  call putint
  li a0, 10
  call putch
  li a0, 115
  call putch
  li a0, 99
  call putch
  li a0, 111
  call putch
  li a0, 114
  call putch
  li a0, 101
  call putch
  li a0, 58
  call putch
  li a0, 32
  call putch
  la t0, var_0
  lw t0, 0(t0)
  sw t0, 180(sp)
  lw t0, 180(sp)
  mv a0 ,t0
  call putint
  li a0, 10
  call putch
  sw x0, 176(sp)
  j while_entry_1
while_entry_1:
  lw t0, 176(sp)
  sw t0, 172(sp)
  lw t0, 172(sp)
  li t1, 4
  slt t2, t0, t1
  sw t2, 168(sp)
  lw t0, 168(sp)
  bnez t0, while_body_1
  j while_end_1
while_body_1:
  sw x0, 164(sp)
  j while_entry_2
while_end_1:
  lw ra, 188(sp)
  addi sp, sp, 192
  ret

while_entry_2:
  lw t0, 164(sp)
  sw t0, 160(sp)
  lw t0, 160(sp)
  li t1, 4
  slt t2, t0, t1
  sw t2, 156(sp)
  lw t0, 156(sp)
  bnez t0, while_body_2
  j while_end_2
while_body_2:
  lw t0, 176(sp)
  sw t0, 148(sp)
  lw t0, 164(sp)
  sw t0, 144(sp)
  lw t0, 148(sp)
  mv a0 ,t0
  lw t0, 144(sp)
  mv a1 ,t0
  call get_index
  sw a0, 140(sp)
  la t0, var_7
  lw t1, 140(sp)
  li t2,  4
  mul t2, t2, t1
  add t0, t0, t2
  sw t0, 136(sp)
  lw t0, 136(sp)
  lw t0, 0(t0)
  sw t0, 132(sp)
  lw t0, 132(sp)
  sw t0, 152(sp)
  lw t0, 152(sp)
  sw t0, 128(sp)
  lw t0, 128(sp)
  xor t1, t0, x0
  seqz t1, t1
  sw t1, 124(sp)
  lw t0, 124(sp)
  bnez t0, then_1
  j else_1
while_end_2:
  li a0, 10
  call putch
  lw t0, 176(sp)
  sw t0, 120(sp)
  lw t0, 120(sp)
  li t1, 1
  add t2, t0, t1
  sw t2, 116(sp)
  lw t0, 176(sp)
  sw t0, 112(sp)
  lw t0, 116(sp)
  sw t0, 176(sp)
  j while_entry_1
then_1:
  lw t0, 152(sp)
  sw t0, 104(sp)
  la t0, var_6
  lw t1, 104(sp)
  li t2,  4
  mul t2, t2, t1
  add t0, t0, t2
  sw t0, 100(sp)
  lw t0, 100(sp)
  lw t0, 0(t0)
  sw t0, 96(sp)
  lw t0, 96(sp)
  li t1, 1
  add t2, t0, t1
  sw t2, 92(sp)
  lw t0, 92(sp)
  sw t0, 108(sp)
  j while_entry_3
else_1:
  lw t0, 152(sp)
  sw t0, 88(sp)
  la t0, var_5
  lw t1, 88(sp)
  li t2,  4
  mul t2, t2, t1
  add t0, t0, t2
  sw t0, 84(sp)
  lw t0, 84(sp)
  lw t0, 0(t0)
  sw t0, 80(sp)
  lw t0, 80(sp)
  mv a0 ,t0
  call putint
  lw t0, 152(sp)
  sw t0, 72(sp)
  la t0, var_6
  lw t1, 72(sp)
  li t2,  4
  mul t2, t2, t1
  add t0, t0, t2
  sw t0, 68(sp)
  lw t0, 68(sp)
  lw t0, 0(t0)
  sw t0, 64(sp)
  lw t0, 64(sp)
  sw t0, 76(sp)
  j while_entry_4
while_entry_3:
  lw t0, 108(sp)
  sw t0, 60(sp)
  la t0, var_2
  lw t0, 0(t0)
  sw t0, 56(sp)
  lw t0, 60(sp)
  lw t1, 56(sp)
  sgt t2, t0, t1
  seqz t2, t2
  sw t2, 52(sp)
  lw t0, 52(sp)
  bnez t0, while_body_3
  j while_end_3
while_entry_4:
  lw t0, 76(sp)
  sw t0, 48(sp)
  la t0, var_2
  lw t0, 0(t0)
  sw t0, 44(sp)
  lw t0, 48(sp)
  lw t1, 44(sp)
  sgt t2, t0, t1
  seqz t2, t2
  sw t2, 40(sp)
  lw t0, 40(sp)
  bnez t0, while_body_4
  j while_end_4
while_body_3:
  li a0, 95
  call putch
  lw t0, 108(sp)
  sw t0, 36(sp)
  lw t0, 36(sp)
  li t1, 1
  add t2, t0, t1
  sw t2, 32(sp)
  lw t0, 108(sp)
  sw t0, 28(sp)
  lw t0, 32(sp)
  sw t0, 108(sp)
  j while_entry_3
while_end_3:
  li a0, 32
  call putch
  j end_1
while_body_4:
  li a0, 32
  call putch
  lw t0, 76(sp)
  sw t0, 24(sp)
  lw t0, 24(sp)
  li t1, 1
  add t2, t0, t1
  sw t2, 20(sp)
  lw t0, 76(sp)
  sw t0, 16(sp)
  lw t0, 20(sp)
  sw t0, 76(sp)
  j while_entry_4
while_end_4:
  j end_1
end_1:
  lw t0, 164(sp)
  sw t0, 12(sp)
  lw t0, 12(sp)
  li t1, 1
  add t2, t0, t1
  sw t2, 8(sp)
  lw t0, 164(sp)
  sw t0, 4(sp)
  lw t0, 8(sp)
  sw t0, 164(sp)
  j while_entry_2
  .text
  .global move_one_line
move_one_line:
  addi sp, sp, -1296
  sw ra, 1292(sp)
  sw a0, 1288(sp)
  sw a1, 1284(sp)
  sw x0, 1280(sp)
  lw t0, 1284(sp)
  sw t0, 1244(sp)
  lw t0, 1244(sp)
  xor t1, t0, x0
  seqz t1, t1
  sw t1, 1240(sp)
  lw t0, 1240(sp)
  bnez t0, then__2
  j else__2
then__2:
  li t0, 1
  sw t0, 1236(sp)
  j end__2
else__2:
  lw t0, 1284(sp)
  sw t0, 1232(sp)
  lw t0, 1232(sp)
  li t1, 1
  xor t2, t0, t1
  seqz t2, t2
  sw t2, 1228(sp)
  lw t0, 1228(sp)
  xor t1, t0, x0
  snez t1, t1
  sw t1, 1224(sp)
  lw t0, 1224(sp)
  sw t0, 1236(sp)
  j end__2
end__2:
  lw t0, 1236(sp)
  sw t0, 1220(sp)
  lw t0, 1220(sp)
  bnez t0, then_3
  j else_3
then_3:
  lw t0, 1288(sp)
  sw t0, 1216(sp)
  li a0, 0
  lw t0, 1216(sp)
  mv a1 ,t0
  call get_index
  sw a0, 1212(sp)
  lw t0, 1260(sp)
  sw t0, 1208(sp)
  lw t0, 1212(sp)
  sw t0, 1260(sp)
  lw t0, 1288(sp)
  sw t0, 1204(sp)
  li a0, 1
  lw t0, 1204(sp)
  mv a1 ,t0
  call get_index
  sw a0, 1200(sp)
  lw t0, 1256(sp)
  sw t0, 1196(sp)
  lw t0, 1200(sp)
  sw t0, 1256(sp)
  lw t0, 1288(sp)
  sw t0, 1192(sp)
  li a0, 2
  lw t0, 1192(sp)
  mv a1 ,t0
  call get_index
  sw a0, 1188(sp)
  lw t0, 1252(sp)
  sw t0, 1184(sp)
  lw t0, 1188(sp)
  sw t0, 1252(sp)
  lw t0, 1288(sp)
  sw t0, 1180(sp)
  li a0, 3
  lw t0, 1180(sp)
  mv a1 ,t0
  call get_index
  sw a0, 1176(sp)
  lw t0, 1248(sp)
  sw t0, 1172(sp)
  lw t0, 1176(sp)
  sw t0, 1248(sp)
  j end_3
else_3:
  lw t0, 1288(sp)
  sw t0, 1168(sp)
  lw t0, 1168(sp)
  mv a0 ,t0
  li a1, 0
  call get_index
  sw a0, 1164(sp)
  lw t0, 1260(sp)
  sw t0, 1160(sp)
  lw t0, 1164(sp)
  sw t0, 1260(sp)
  lw t0, 1288(sp)
  sw t0, 1156(sp)
  lw t0, 1156(sp)
  mv a0 ,t0
  li a1, 1
  call get_index
  sw a0, 1152(sp)
  lw t0, 1256(sp)
  sw t0, 1148(sp)
  lw t0, 1152(sp)
  sw t0, 1256(sp)
  lw t0, 1288(sp)
  sw t0, 1144(sp)
  lw t0, 1144(sp)
  mv a0 ,t0
  li a1, 2
  call get_index
  sw a0, 1140(sp)
  lw t0, 1252(sp)
  sw t0, 1136(sp)
  lw t0, 1140(sp)
  sw t0, 1252(sp)
  lw t0, 1288(sp)
  sw t0, 1132(sp)
  lw t0, 1132(sp)
  mv a0 ,t0
  li a1, 3
  call get_index
  sw a0, 1128(sp)
  lw t0, 1248(sp)
  sw t0, 1124(sp)
  lw t0, 1128(sp)
  sw t0, 1248(sp)
  j end_3
end_3:
  lw t0, 1260(sp)
  sw t0, 1120(sp)
  la t0, var_7
  lw t1, 1120(sp)
  li t2,  4
  mul t2, t2, t1
  add t0, t0, t2
  sw t0, 1116(sp)
  lw t0, 1116(sp)
  lw t0, 0(t0)
  sw t0, 1112(sp)
  lw t0, 1276(sp)
  sw t0, 1108(sp)
  lw t0, 1112(sp)
  sw t0, 1276(sp)
  lw t0, 1256(sp)
  sw t0, 1104(sp)
  la t0, var_7
  lw t1, 1104(sp)
  li t2,  4
  mul t2, t2, t1
  add t0, t0, t2
  sw t0, 1100(sp)
  lw t0, 1100(sp)
  lw t0, 0(t0)
  sw t0, 1096(sp)
  lw t0, 1272(sp)
  sw t0, 1092(sp)
  lw t0, 1096(sp)
  sw t0, 1272(sp)
  lw t0, 1252(sp)
  sw t0, 1088(sp)
  la t0, var_7
  lw t1, 1088(sp)
  li t2,  4
  mul t2, t2, t1
  add t0, t0, t2
  sw t0, 1084(sp)
  lw t0, 1084(sp)
  lw t0, 0(t0)
  sw t0, 1080(sp)
  lw t0, 1268(sp)
  sw t0, 1076(sp)
  lw t0, 1080(sp)
  sw t0, 1268(sp)
  lw t0, 1248(sp)
  sw t0, 1072(sp)
  la t0, var_7
  lw t1, 1072(sp)
  li t2,  4
  mul t2, t2, t1
  add t0, t0, t2
  sw t0, 1068(sp)
  lw t0, 1068(sp)
  lw t0, 0(t0)
  sw t0, 1064(sp)
  lw t0, 1264(sp)
  sw t0, 1060(sp)
  lw t0, 1064(sp)
  sw t0, 1264(sp)
  lw t0, 1284(sp)
  sw t0, 1056(sp)
  lw t0, 1056(sp)
  xor t1, t0, x0
  seqz t1, t1
  sw t1, 1052(sp)
  lw t0, 1052(sp)
  bnez t0, then__4
  j else__4
then__4:
  li t0, 1
  sw t0, 1048(sp)
  j end__4
else__4:
  lw t0, 1284(sp)
  sw t0, 1044(sp)
  lw t0, 1044(sp)
  li t1, 2
  xor t2, t0, t1
  seqz t2, t2
  sw t2, 1040(sp)
  lw t0, 1040(sp)
  xor t1, t0, x0
  snez t1, t1
  sw t1, 1036(sp)
  lw t0, 1036(sp)
  sw t0, 1048(sp)
  j end__4
end__4:
  lw t0, 1048(sp)
  sw t0, 1032(sp)
  lw t0, 1032(sp)
  bnez t0, then_5
  j else_5
then_5:
  lw t0, 1276(sp)
  sw t0, 1028(sp)
  lw t0, 1028(sp)
  xor t1, t0, x0
  seqz t1, t1
  sw t1, 1024(sp)
  lw t0, 1024(sp)
  bnez t0, then_6
  j end_6
else_5:
  lw t0, 1264(sp)
  sw t0, 1020(sp)
  lw t0, 1020(sp)
  xor t1, t0, x0
  seqz t1, t1
  sw t1, 1016(sp)
  lw t0, 1016(sp)
  bnez t0, then_21
  j end_21
then_6:
  lw t0, 1272(sp)
  sw t0, 1012(sp)
  lw t0, 1276(sp)
  sw t0, 1008(sp)
  lw t0, 1012(sp)
  sw t0, 1276(sp)
  lw t0, 1268(sp)
  sw t0, 1004(sp)
  lw t0, 1272(sp)
  sw t0, 1000(sp)
  lw t0, 1004(sp)
  sw t0, 1272(sp)
  lw t0, 1264(sp)
  sw t0, 996(sp)
  lw t0, 1268(sp)
  sw t0, 992(sp)
  lw t0, 996(sp)
  sw t0, 1268(sp)
  lw t0, 1264(sp)
  sw t0, 988(sp)
  sw x0, 1264(sp)
  lw t0, 1276(sp)
  sw t0, 984(sp)
  lw t0, 984(sp)
  xor t1, t0, x0
  snez t1, t1
  sw t1, 980(sp)
  lw t0, 980(sp)
  bnez t0, then_7
  j end_7
end_6:
  lw t0, 1272(sp)
  sw t0, 976(sp)
  lw t0, 976(sp)
  xor t1, t0, x0
  seqz t1, t1
  sw t1, 972(sp)
  lw t0, 972(sp)
  bnez t0, then_8
  j end_8
then_21:
  lw t0, 1268(sp)
  sw t0, 968(sp)
  lw t0, 1264(sp)
  sw t0, 964(sp)
  lw t0, 968(sp)
  sw t0, 1264(sp)
  lw t0, 1272(sp)
  sw t0, 960(sp)
  lw t0, 1268(sp)
  sw t0, 956(sp)
  lw t0, 960(sp)
  sw t0, 1268(sp)
  lw t0, 1276(sp)
  sw t0, 952(sp)
  lw t0, 1272(sp)
  sw t0, 948(sp)
  lw t0, 952(sp)
  sw t0, 1272(sp)
  lw t0, 1276(sp)
  sw t0, 944(sp)
  sw x0, 1276(sp)
  lw t0, 1264(sp)
  sw t0, 940(sp)
  lw t0, 940(sp)
  xor t1, t0, x0
  snez t1, t1
  sw t1, 936(sp)
  lw t0, 936(sp)
  bnez t0, then_22
  j end_22
end_21:
  lw t0, 1268(sp)
  sw t0, 932(sp)
  lw t0, 932(sp)
  xor t1, t0, x0
  seqz t1, t1
  sw t1, 928(sp)
  lw t0, 928(sp)
  bnez t0, then_23
  j end_23
then_7:
  lw t0, 1280(sp)
  sw t0, 924(sp)
  li t0, 1
  sw t0, 1280(sp)
  j end_7
end_7:
  j end_6
then_8:
  lw t0, 1268(sp)
  sw t0, 920(sp)
  lw t0, 1272(sp)
  sw t0, 916(sp)
  lw t0, 920(sp)
  sw t0, 1272(sp)
  lw t0, 1264(sp)
  sw t0, 912(sp)
  lw t0, 1268(sp)
  sw t0, 908(sp)
  lw t0, 912(sp)
  sw t0, 1268(sp)
  lw t0, 1264(sp)
  sw t0, 904(sp)
  sw x0, 1264(sp)
  lw t0, 1272(sp)
  sw t0, 900(sp)
  lw t0, 900(sp)
  xor t1, t0, x0
  snez t1, t1
  sw t1, 896(sp)
  lw t0, 896(sp)
  bnez t0, then_9
  j end_9
end_8:
  lw t0, 1268(sp)
  sw t0, 892(sp)
  lw t0, 892(sp)
  xor t1, t0, x0
  seqz t1, t1
  sw t1, 888(sp)
  lw t0, 888(sp)
  bnez t0, then_10
  j end_10
then_22:
  lw t0, 1280(sp)
  sw t0, 884(sp)
  li t0, 1
  sw t0, 1280(sp)
  j end_22
end_22:
  j end_21
then_23:
  lw t0, 1272(sp)
  sw t0, 880(sp)
  lw t0, 1268(sp)
  sw t0, 876(sp)
  lw t0, 880(sp)
  sw t0, 1268(sp)
  lw t0, 1276(sp)
  sw t0, 872(sp)
  lw t0, 1272(sp)
  sw t0, 868(sp)
  lw t0, 872(sp)
  sw t0, 1272(sp)
  lw t0, 1276(sp)
  sw t0, 864(sp)
  sw x0, 1276(sp)
  lw t0, 1268(sp)
  sw t0, 860(sp)
  lw t0, 860(sp)
  xor t1, t0, x0
  snez t1, t1
  sw t1, 856(sp)
  lw t0, 856(sp)
  bnez t0, then_24
  j end_24
end_23:
  lw t0, 1272(sp)
  sw t0, 852(sp)
  lw t0, 852(sp)
  xor t1, t0, x0
  seqz t1, t1
  sw t1, 848(sp)
  lw t0, 848(sp)
  bnez t0, then_25
  j end_25
then_9:
  lw t0, 1280(sp)
  sw t0, 844(sp)
  li t0, 1
  sw t0, 1280(sp)
  j end_9
end_9:
  j end_8
then_10:
  lw t0, 1264(sp)
  sw t0, 840(sp)
  lw t0, 1268(sp)
  sw t0, 836(sp)
  lw t0, 840(sp)
  sw t0, 1268(sp)
  lw t0, 1264(sp)
  sw t0, 832(sp)
  sw x0, 1264(sp)
  lw t0, 1268(sp)
  sw t0, 828(sp)
  lw t0, 828(sp)
  xor t1, t0, x0
  snez t1, t1
  sw t1, 824(sp)
  lw t0, 824(sp)
  bnez t0, then_11
  j end_11
end_10:
  lw t0, 1276(sp)
  sw t0, 820(sp)
  lw t0, 1272(sp)
  sw t0, 816(sp)
  lw t0, 820(sp)
  lw t1, 816(sp)
  xor t2, t0, t1
  seqz t2, t2
  sw t2, 812(sp)
  lw t0, 812(sp)
  bnez t0, then__12
  j else__12
then_24:
  lw t0, 1280(sp)
  sw t0, 804(sp)
  li t0, 1
  sw t0, 1280(sp)
  j end_24
end_24:
  j end_23
then_25:
  lw t0, 1276(sp)
  sw t0, 800(sp)
  lw t0, 1272(sp)
  sw t0, 796(sp)
  lw t0, 800(sp)
  sw t0, 1272(sp)
  lw t0, 1276(sp)
  sw t0, 792(sp)
  sw x0, 1276(sp)
  lw t0, 1272(sp)
  sw t0, 788(sp)
  lw t0, 788(sp)
  xor t1, t0, x0
  snez t1, t1
  sw t1, 784(sp)
  lw t0, 784(sp)
  bnez t0, then_26
  j end_26
end_25:
  lw t0, 1264(sp)
  sw t0, 780(sp)
  lw t0, 1268(sp)
  sw t0, 776(sp)
  lw t0, 780(sp)
  lw t1, 776(sp)
  xor t2, t0, t1
  seqz t2, t2
  sw t2, 772(sp)
  lw t0, 772(sp)
  bnez t0, then__27
  j else__27
then_11:
  lw t0, 1280(sp)
  sw t0, 764(sp)
  li t0, 1
  sw t0, 1280(sp)
  j end_11
end_11:
  j end_10
then__12:
  lw t0, 1276(sp)
  sw t0, 760(sp)
  lw t0, 760(sp)
  xor t1, t0, x0
  snez t1, t1
  sw t1, 756(sp)
  lw t0, 756(sp)
  xor t1, t0, x0
  snez t1, t1
  sw t1, 752(sp)
  lw t0, 752(sp)
  sw t0, 808(sp)
  j end__12
else__12:
  sw x0, 808(sp)
  j end__12
then_26:
  lw t0, 1280(sp)
  sw t0, 748(sp)
  li t0, 1
  sw t0, 1280(sp)
  j end_26
end_26:
  j end_25
then__27:
  lw t0, 1264(sp)
  sw t0, 744(sp)
  lw t0, 744(sp)
  xor t1, t0, x0
  snez t1, t1
  sw t1, 740(sp)
  lw t0, 740(sp)
  xor t1, t0, x0
  snez t1, t1
  sw t1, 736(sp)
  lw t0, 736(sp)
  sw t0, 768(sp)
  j end__27
else__27:
  sw x0, 768(sp)
  j end__27
end__12:
  lw t0, 808(sp)
  sw t0, 732(sp)
  lw t0, 732(sp)
  bnez t0, then_13
  j end_13
end__27:
  lw t0, 768(sp)
  sw t0, 728(sp)
  lw t0, 728(sp)
  bnez t0, then_28
  j end_28
then_13:
  lw t0, 1276(sp)
  sw t0, 724(sp)
  lw t0, 724(sp)
  li t1, 1
  add t2, t0, t1
  sw t2, 720(sp)
  lw t0, 1276(sp)
  sw t0, 716(sp)
  lw t0, 720(sp)
  sw t0, 1276(sp)
  lw t0, 1268(sp)
  sw t0, 712(sp)
  lw t0, 1272(sp)
  sw t0, 708(sp)
  lw t0, 712(sp)
  sw t0, 1272(sp)
  lw t0, 1264(sp)
  sw t0, 704(sp)
  lw t0, 1268(sp)
  sw t0, 700(sp)
  lw t0, 704(sp)
  sw t0, 1268(sp)
  lw t0, 1264(sp)
  sw t0, 696(sp)
  sw x0, 1264(sp)
  lw t0, 1280(sp)
  sw t0, 692(sp)
  li t0, 1
  sw t0, 1280(sp)
  la t0, var_0
  lw t0, 0(t0)
  sw t0, 688(sp)
  lw t0, 1276(sp)
  sw t0, 684(sp)
  la t0, var_5
  lw t1, 684(sp)
  li t2,  4
  mul t2, t2, t1
  add t0, t0, t2
  sw t0, 680(sp)
  lw t0, 680(sp)
  lw t0, 0(t0)
  sw t0, 676(sp)
  lw t0, 688(sp)
  lw t1, 676(sp)
  add t2, t0, t1
  sw t2, 672(sp)
  la t0, var_0
  lw t0, 0(t0)
  sw t0, 668(sp)
  lw t0, 672(sp)
  la t1, var_0
  sw t0, 0(t1)
  lw t0, 1276(sp)
  sw t0, 664(sp)
  la t0, var_6
  lw t1, 664(sp)
  li t2,  4
  mul t2, t2, t1
  add t0, t0, t2
  sw t0, 660(sp)
  lw t0, 660(sp)
  lw t0, 0(t0)
  sw t0, 656(sp)
  la t0, var_2
  lw t0, 0(t0)
  sw t0, 652(sp)
  lw t0, 656(sp)
  lw t1, 652(sp)
  slt t2, t1, t0
  sw t2, 648(sp)
  lw t0, 648(sp)
  bnez t0, then_14
  j end_14
end_13:
  lw t0, 1272(sp)
  sw t0, 644(sp)
  lw t0, 1268(sp)
  sw t0, 640(sp)
  lw t0, 644(sp)
  lw t1, 640(sp)
  xor t2, t0, t1
  seqz t2, t2
  sw t2, 636(sp)
  lw t0, 636(sp)
  bnez t0, then__15
  j else__15
then_28:
  lw t0, 1264(sp)
  sw t0, 628(sp)
  lw t0, 628(sp)
  li t1, 1
  add t2, t0, t1
  sw t2, 624(sp)
  lw t0, 1264(sp)
  sw t0, 620(sp)
  lw t0, 624(sp)
  sw t0, 1264(sp)
  lw t0, 1272(sp)
  sw t0, 616(sp)
  lw t0, 1268(sp)
  sw t0, 612(sp)
  lw t0, 616(sp)
  sw t0, 1268(sp)
  lw t0, 1276(sp)
  sw t0, 608(sp)
  lw t0, 1272(sp)
  sw t0, 604(sp)
  lw t0, 608(sp)
  sw t0, 1272(sp)
  lw t0, 1276(sp)
  sw t0, 600(sp)
  sw x0, 1276(sp)
  lw t0, 1280(sp)
  sw t0, 596(sp)
  li t0, 1
  sw t0, 1280(sp)
  la t0, var_0
  lw t0, 0(t0)
  sw t0, 592(sp)
  lw t0, 1264(sp)
  sw t0, 588(sp)
  la t0, var_5
  lw t1, 588(sp)
  li t2,  4
  mul t2, t2, t1
  add t0, t0, t2
  sw t0, 584(sp)
  lw t0, 584(sp)
  lw t0, 0(t0)
  sw t0, 580(sp)
  lw t0, 592(sp)
  lw t1, 580(sp)
  add t2, t0, t1
  sw t2, 576(sp)
  la t0, var_0
  lw t0, 0(t0)
  sw t0, 572(sp)
  lw t0, 576(sp)
  la t1, var_0
  sw t0, 0(t1)
  lw t0, 1264(sp)
  sw t0, 568(sp)
  la t0, var_6
  lw t1, 568(sp)
  li t2,  4
  mul t2, t2, t1
  add t0, t0, t2
  sw t0, 564(sp)
  lw t0, 564(sp)
  lw t0, 0(t0)
  sw t0, 560(sp)
  la t0, var_2
  lw t0, 0(t0)
  sw t0, 556(sp)
  lw t0, 560(sp)
  lw t1, 556(sp)
  slt t2, t1, t0
  sw t2, 552(sp)
  lw t0, 552(sp)
  bnez t0, then_29
  j end_29
end_28:
  lw t0, 1268(sp)
  sw t0, 548(sp)
  lw t0, 1272(sp)
  sw t0, 544(sp)
  lw t0, 548(sp)
  lw t1, 544(sp)
  xor t2, t0, t1
  seqz t2, t2
  sw t2, 540(sp)
  lw t0, 540(sp)
  bnez t0, then__30
  j else__30
then_14:
  lw t0, 1276(sp)
  sw t0, 532(sp)
  la t0, var_6
  lw t1, 532(sp)
  li t2,  4
  mul t2, t2, t1
  add t0, t0, t2
  sw t0, 528(sp)
  lw t0, 528(sp)
  lw t0, 0(t0)
  sw t0, 524(sp)
  la t0, var_2
  lw t0, 0(t0)
  sw t0, 520(sp)
  lw t0, 524(sp)
  la t1, var_2
  sw t0, 0(t1)
  j end_14
end_14:
  j end_13
then__15:
  lw t0, 1272(sp)
  sw t0, 516(sp)
  lw t0, 516(sp)
  xor t1, t0, x0
  snez t1, t1
  sw t1, 512(sp)
  lw t0, 512(sp)
  xor t1, t0, x0
  snez t1, t1
  sw t1, 508(sp)
  lw t0, 508(sp)
  sw t0, 632(sp)
  j end__15
else__15:
  sw x0, 632(sp)
  j end__15
then_29:
  lw t0, 1264(sp)
  sw t0, 504(sp)
  la t0, var_6
  lw t1, 504(sp)
  li t2,  4
  mul t2, t2, t1
  add t0, t0, t2
  sw t0, 500(sp)
  lw t0, 500(sp)
  lw t0, 0(t0)
  sw t0, 496(sp)
  la t0, var_2
  lw t0, 0(t0)
  sw t0, 492(sp)
  lw t0, 496(sp)
  la t1, var_2
  sw t0, 0(t1)
  j end_29
end_29:
  j end_28
then__30:
  lw t0, 1268(sp)
  sw t0, 488(sp)
  lw t0, 488(sp)
  xor t1, t0, x0
  snez t1, t1
  sw t1, 484(sp)
  lw t0, 484(sp)
  xor t1, t0, x0
  snez t1, t1
  sw t1, 480(sp)
  lw t0, 480(sp)
  sw t0, 536(sp)
  j end__30
else__30:
  sw x0, 536(sp)
  j end__30
end__15:
  lw t0, 632(sp)
  sw t0, 476(sp)
  lw t0, 476(sp)
  bnez t0, then_16
  j end_16
end__30:
  lw t0, 536(sp)
  sw t0, 472(sp)
  lw t0, 472(sp)
  bnez t0, then_31
  j end_31
then_16:
  lw t0, 1272(sp)
  sw t0, 468(sp)
  lw t0, 468(sp)
  li t1, 1
  add t2, t0, t1
  sw t2, 464(sp)
  lw t0, 1272(sp)
  sw t0, 460(sp)
  lw t0, 464(sp)
  sw t0, 1272(sp)
  lw t0, 1264(sp)
  sw t0, 456(sp)
  lw t0, 1268(sp)
  sw t0, 452(sp)
  lw t0, 456(sp)
  sw t0, 1268(sp)
  lw t0, 1264(sp)
  sw t0, 448(sp)
  sw x0, 1264(sp)
  lw t0, 1280(sp)
  sw t0, 444(sp)
  li t0, 1
  sw t0, 1280(sp)
  la t0, var_0
  lw t0, 0(t0)
  sw t0, 440(sp)
  lw t0, 1272(sp)
  sw t0, 436(sp)
  la t0, var_5
  lw t1, 436(sp)
  li t2,  4
  mul t2, t2, t1
  add t0, t0, t2
  sw t0, 432(sp)
  lw t0, 432(sp)
  lw t0, 0(t0)
  sw t0, 428(sp)
  lw t0, 440(sp)
  lw t1, 428(sp)
  add t2, t0, t1
  sw t2, 424(sp)
  la t0, var_0
  lw t0, 0(t0)
  sw t0, 420(sp)
  lw t0, 424(sp)
  la t1, var_0
  sw t0, 0(t1)
  lw t0, 1272(sp)
  sw t0, 416(sp)
  la t0, var_6
  lw t1, 416(sp)
  li t2,  4
  mul t2, t2, t1
  add t0, t0, t2
  sw t0, 412(sp)
  lw t0, 412(sp)
  lw t0, 0(t0)
  sw t0, 408(sp)
  la t0, var_2
  lw t0, 0(t0)
  sw t0, 404(sp)
  lw t0, 408(sp)
  lw t1, 404(sp)
  slt t2, t1, t0
  sw t2, 400(sp)
  lw t0, 400(sp)
  bnez t0, then_17
  j end_17
end_16:
  lw t0, 1268(sp)
  sw t0, 396(sp)
  lw t0, 1264(sp)
  sw t0, 392(sp)
  lw t0, 396(sp)
  lw t1, 392(sp)
  xor t2, t0, t1
  seqz t2, t2
  sw t2, 388(sp)
  lw t0, 388(sp)
  bnez t0, then__18
  j else__18
then_31:
  lw t0, 1268(sp)
  sw t0, 380(sp)
  lw t0, 380(sp)
  li t1, 1
  add t2, t0, t1
  sw t2, 376(sp)
  lw t0, 1268(sp)
  sw t0, 372(sp)
  lw t0, 376(sp)
  sw t0, 1268(sp)
  lw t0, 1276(sp)
  sw t0, 368(sp)
  lw t0, 1272(sp)
  sw t0, 364(sp)
  lw t0, 368(sp)
  sw t0, 1272(sp)
  lw t0, 1276(sp)
  sw t0, 360(sp)
  sw x0, 1276(sp)
  lw t0, 1280(sp)
  sw t0, 356(sp)
  li t0, 1
  sw t0, 1280(sp)
  la t0, var_0
  lw t0, 0(t0)
  sw t0, 352(sp)
  lw t0, 1268(sp)
  sw t0, 348(sp)
  la t0, var_5
  lw t1, 348(sp)
  li t2,  4
  mul t2, t2, t1
  add t0, t0, t2
  sw t0, 344(sp)
  lw t0, 344(sp)
  lw t0, 0(t0)
  sw t0, 340(sp)
  lw t0, 352(sp)
  lw t1, 340(sp)
  add t2, t0, t1
  sw t2, 336(sp)
  la t0, var_0
  lw t0, 0(t0)
  sw t0, 332(sp)
  lw t0, 336(sp)
  la t1, var_0
  sw t0, 0(t1)
  lw t0, 1268(sp)
  sw t0, 328(sp)
  la t0, var_6
  lw t1, 328(sp)
  li t2,  4
  mul t2, t2, t1
  add t0, t0, t2
  sw t0, 324(sp)
  lw t0, 324(sp)
  lw t0, 0(t0)
  sw t0, 320(sp)
  la t0, var_2
  lw t0, 0(t0)
  sw t0, 316(sp)
  lw t0, 320(sp)
  lw t1, 316(sp)
  slt t2, t1, t0
  sw t2, 312(sp)
  lw t0, 312(sp)
  bnez t0, then_32
  j end_32
end_31:
  lw t0, 1272(sp)
  sw t0, 308(sp)
  lw t0, 1276(sp)
  sw t0, 304(sp)
  lw t0, 308(sp)
  lw t1, 304(sp)
  xor t2, t0, t1
  seqz t2, t2
  sw t2, 300(sp)
  lw t0, 300(sp)
  bnez t0, then__33
  j else__33
then_17:
  lw t0, 1272(sp)
  sw t0, 292(sp)
  la t0, var_6
  lw t1, 292(sp)
  li t2,  4
  mul t2, t2, t1
  add t0, t0, t2
  sw t0, 288(sp)
  lw t0, 288(sp)
  lw t0, 0(t0)
  sw t0, 284(sp)
  la t0, var_2
  lw t0, 0(t0)
  sw t0, 280(sp)
  lw t0, 284(sp)
  la t1, var_2
  sw t0, 0(t1)
  j end_17
end_17:
  j end_16
then__18:
  lw t0, 1268(sp)
  sw t0, 276(sp)
  lw t0, 276(sp)
  xor t1, t0, x0
  snez t1, t1
  sw t1, 272(sp)
  lw t0, 272(sp)
  xor t1, t0, x0
  snez t1, t1
  sw t1, 268(sp)
  lw t0, 268(sp)
  sw t0, 384(sp)
  j end__18
else__18:
  sw x0, 384(sp)
  j end__18
then_32:
  lw t0, 1268(sp)
  sw t0, 264(sp)
  la t0, var_6
  lw t1, 264(sp)
  li t2,  4
  mul t2, t2, t1
  add t0, t0, t2
  sw t0, 260(sp)
  lw t0, 260(sp)
  lw t0, 0(t0)
  sw t0, 256(sp)
  la t0, var_2
  lw t0, 0(t0)
  sw t0, 252(sp)
  lw t0, 256(sp)
  la t1, var_2
  sw t0, 0(t1)
  j end_32
end_32:
  j end_31
then__33:
  lw t0, 1272(sp)
  sw t0, 248(sp)
  lw t0, 248(sp)
  xor t1, t0, x0
  snez t1, t1
  sw t1, 244(sp)
  lw t0, 244(sp)
  xor t1, t0, x0
  snez t1, t1
  sw t1, 240(sp)
  lw t0, 240(sp)
  sw t0, 296(sp)
  j end__33
else__33:
  sw x0, 296(sp)
  j end__33
end__18:
  lw t0, 384(sp)
  sw t0, 236(sp)
  lw t0, 236(sp)
  bnez t0, then_19
  j end_19
end__33:
  lw t0, 296(sp)
  sw t0, 232(sp)
  lw t0, 232(sp)
  bnez t0, then_34
  j end_34
then_19:
  lw t0, 1268(sp)
  sw t0, 228(sp)
  lw t0, 228(sp)
  li t1, 1
  add t2, t0, t1
  sw t2, 224(sp)
  lw t0, 1268(sp)
  sw t0, 220(sp)
  lw t0, 224(sp)
  sw t0, 1268(sp)
  lw t0, 1264(sp)
  sw t0, 216(sp)
  sw x0, 1264(sp)
  lw t0, 1280(sp)
  sw t0, 212(sp)
  li t0, 1
  sw t0, 1280(sp)
  la t0, var_0
  lw t0, 0(t0)
  sw t0, 208(sp)
  lw t0, 1268(sp)
  sw t0, 204(sp)
  la t0, var_5
  lw t1, 204(sp)
  li t2,  4
  mul t2, t2, t1
  add t0, t0, t2
  sw t0, 200(sp)
  lw t0, 200(sp)
  lw t0, 0(t0)
  sw t0, 196(sp)
  lw t0, 208(sp)
  lw t1, 196(sp)
  add t2, t0, t1
  sw t2, 192(sp)
  la t0, var_0
  lw t0, 0(t0)
  sw t0, 188(sp)
  lw t0, 192(sp)
  la t1, var_0
  sw t0, 0(t1)
  lw t0, 1268(sp)
  sw t0, 184(sp)
  la t0, var_6
  lw t1, 184(sp)
  li t2,  4
  mul t2, t2, t1
  add t0, t0, t2
  sw t0, 180(sp)
  lw t0, 180(sp)
  lw t0, 0(t0)
  sw t0, 176(sp)
  la t0, var_2
  lw t0, 0(t0)
  sw t0, 172(sp)
  lw t0, 176(sp)
  lw t1, 172(sp)
  slt t2, t1, t0
  sw t2, 168(sp)
  lw t0, 168(sp)
  bnez t0, then_20
  j end_20
end_19:
  j end_5
then_34:
  lw t0, 1272(sp)
  sw t0, 164(sp)
  lw t0, 164(sp)
  li t1, 1
  add t2, t0, t1
  sw t2, 160(sp)
  lw t0, 1272(sp)
  sw t0, 156(sp)
  lw t0, 160(sp)
  sw t0, 1272(sp)
  lw t0, 1276(sp)
  sw t0, 152(sp)
  sw x0, 1276(sp)
  lw t0, 1280(sp)
  sw t0, 148(sp)
  li t0, 1
  sw t0, 1280(sp)
  la t0, var_0
  lw t0, 0(t0)
  sw t0, 144(sp)
  lw t0, 1272(sp)
  sw t0, 140(sp)
  la t0, var_5
  lw t1, 140(sp)
  li t2,  4
  mul t2, t2, t1
  add t0, t0, t2
  sw t0, 136(sp)
  lw t0, 136(sp)
  lw t0, 0(t0)
  sw t0, 132(sp)
  lw t0, 144(sp)
  lw t1, 132(sp)
  add t2, t0, t1
  sw t2, 128(sp)
  la t0, var_0
  lw t0, 0(t0)
  sw t0, 124(sp)
  lw t0, 128(sp)
  la t1, var_0
  sw t0, 0(t1)
  lw t0, 1272(sp)
  sw t0, 120(sp)
  la t0, var_6
  lw t1, 120(sp)
  li t2,  4
  mul t2, t2, t1
  add t0, t0, t2
  sw t0, 116(sp)
  lw t0, 116(sp)
  lw t0, 0(t0)
  sw t0, 112(sp)
  la t0, var_2
  lw t0, 0(t0)
  sw t0, 108(sp)
  lw t0, 112(sp)
  lw t1, 108(sp)
  slt t2, t1, t0
  sw t2, 104(sp)
  lw t0, 104(sp)
  bnez t0, then_35
  j end_35
end_34:
  j end_5
then_20:
  lw t0, 1268(sp)
  sw t0, 100(sp)
  la t0, var_6
  lw t1, 100(sp)
  li t2,  4
  mul t2, t2, t1
  add t0, t0, t2
  sw t0, 96(sp)
  lw t0, 96(sp)
  lw t0, 0(t0)
  sw t0, 92(sp)
  la t0, var_2
  lw t0, 0(t0)
  sw t0, 88(sp)
  lw t0, 92(sp)
  la t1, var_2
  sw t0, 0(t1)
  j end_20
end_20:
  j end_19
end_5:
  lw t0, 1276(sp)
  sw t0, 84(sp)
  lw t0, 1260(sp)
  sw t0, 80(sp)
  la t0, var_7
  lw t1, 80(sp)
  li t2,  4
  mul t2, t2, t1
  add t0, t0, t2
  sw t0, 76(sp)
  lw t0, 76(sp)
  lw t0, 0(t0)
  sw t0, 72(sp)
  lw t0, 84(sp)
  lw t1, 76(sp)
  sw t0, 0(t1)
  lw t0, 1272(sp)
  sw t0, 68(sp)
  lw t0, 1256(sp)
  sw t0, 64(sp)
  la t0, var_7
  lw t1, 64(sp)
  li t2,  4
  mul t2, t2, t1
  add t0, t0, t2
  sw t0, 60(sp)
  lw t0, 60(sp)
  lw t0, 0(t0)
  sw t0, 56(sp)
  lw t0, 68(sp)
  lw t1, 60(sp)
  sw t0, 0(t1)
  lw t0, 1268(sp)
  sw t0, 52(sp)
  lw t0, 1252(sp)
  sw t0, 48(sp)
  la t0, var_7
  lw t1, 48(sp)
  li t2,  4
  mul t2, t2, t1
  add t0, t0, t2
  sw t0, 44(sp)
  lw t0, 44(sp)
  lw t0, 0(t0)
  sw t0, 40(sp)
  lw t0, 52(sp)
  lw t1, 44(sp)
  sw t0, 0(t1)
  lw t0, 1264(sp)
  sw t0, 36(sp)
  lw t0, 1248(sp)
  sw t0, 32(sp)
  la t0, var_7
  lw t1, 32(sp)
  li t2,  4
  mul t2, t2, t1
  add t0, t0, t2
  sw t0, 28(sp)
  lw t0, 28(sp)
  lw t0, 0(t0)
  sw t0, 24(sp)
  lw t0, 36(sp)
  lw t1, 28(sp)
  sw t0, 0(t1)
  lw t0, 1280(sp)
  sw t0, 20(sp)
  lw a0, 20(sp)
  lw ra, 1292(sp)
  addi sp, sp, 1296
  ret

then_35:
  lw t0, 1272(sp)
  sw t0, 16(sp)
  la t0, var_6
  lw t1, 16(sp)
  li t2,  4
  mul t2, t2, t1
  add t0, t0, t2
  sw t0, 12(sp)
  lw t0, 12(sp)
  lw t0, 0(t0)
  sw t0, 8(sp)
  la t0, var_2
  lw t0, 0(t0)
  sw t0, 4(sp)
  lw t0, 8(sp)
  la t1, var_2
  sw t0, 0(t1)
  j end_35
end_35:
  j end_34
  .text
  .global generate
generate:
  addi sp, sp, -144
  sw ra, 140(sp)
  sw x0, 136(sp)
  sw x0, 132(sp)
  sw x0, 128(sp)
  j while_entry_5
while_entry_5:
  lw t0, 128(sp)
  sw t0, 124(sp)
  li t0, 4
  li t1, 4
  mul t2, t0, t1
  sw t2, 120(sp)
  lw t0, 124(sp)
  lw t1, 120(sp)
  slt t2, t0, t1
  sw t2, 116(sp)
  lw t0, 116(sp)
  bnez t0, while_body_5
  j while_end_5
while_body_5:
  lw t0, 128(sp)
  sw t0, 112(sp)
  la t0, var_7
  lw t1, 112(sp)
  li t2,  4
  mul t2, t2, t1
  add t0, t0, t2
  sw t0, 108(sp)
  lw t0, 108(sp)
  lw t0, 0(t0)
  sw t0, 104(sp)
  lw t0, 104(sp)
  xor t1, t0, x0
  seqz t1, t1
  sw t1, 100(sp)
  lw t0, 100(sp)
  bnez t0, then_36
  j end_36
while_end_5:
  call rand
  sw a0, 92(sp)
  lw t0, 92(sp)
  li t1, 2
  rem t2, t0, t1
  sw t2, 88(sp)
  lw t0, 88(sp)
  li t1, 1
  slt t2, t0, t1
  sw t2, 84(sp)
  lw t0, 84(sp)
  bnez t0, then_38
  j else_38
then_36:
  lw t0, 136(sp)
  sw t0, 80(sp)
  lw t0, 80(sp)
  li t1, 1
  add t2, t0, t1
  sw t2, 76(sp)
  lw t0, 136(sp)
  sw t0, 72(sp)
  lw t0, 76(sp)
  sw t0, 136(sp)
  call rand
  sw a0, 68(sp)
  lw t0, 136(sp)
  sw t0, 64(sp)
  lw t0, 68(sp)
  lw t1, 64(sp)
  rem t2, t0, t1
  sw t2, 60(sp)
  lw t0, 60(sp)
  xor t1, t0, x0
  seqz t1, t1
  sw t1, 56(sp)
  lw t0, 56(sp)
  bnez t0, then_37
  j end_37
end_36:
  lw t0, 128(sp)
  sw t0, 52(sp)
  lw t0, 52(sp)
  li t1, 1
  add t2, t0, t1
  sw t2, 48(sp)
  lw t0, 128(sp)
  sw t0, 44(sp)
  lw t0, 48(sp)
  sw t0, 128(sp)
  j while_entry_5
then_38:
  lw t0, 96(sp)
  sw t0, 40(sp)
  li t0, 1
  sw t0, 96(sp)
  j end_38
else_38:
  lw t0, 96(sp)
  sw t0, 36(sp)
  li t0, 2
  sw t0, 96(sp)
  j end_38
then_37:
  lw t0, 128(sp)
  sw t0, 32(sp)
  lw t0, 132(sp)
  sw t0, 28(sp)
  lw t0, 32(sp)
  sw t0, 132(sp)
  j end_37
end_37:
  j end_36
end_38:
  lw t0, 96(sp)
  sw t0, 24(sp)
  lw t0, 132(sp)
  sw t0, 20(sp)
  la t0, var_7
  lw t1, 20(sp)
  li t2,  4
  mul t2, t2, t1
  add t0, t0, t2
  sw t0, 16(sp)
  lw t0, 16(sp)
  lw t0, 0(t0)
  sw t0, 12(sp)
  lw t0, 24(sp)
  lw t1, 16(sp)
  sw t0, 0(t1)
  lw ra, 140(sp)
  addi sp, sp, 144
  ret

  .text
  .global move
move:
  addi sp, sp, -96
  sw ra, 92(sp)
  sw a0, 88(sp)
  sw x0, 84(sp)
  sw x0, 80(sp)
  j while_entry_6
while_entry_6:
  lw t0, 80(sp)
  sw t0, 76(sp)
  lw t0, 76(sp)
  li t1, 4
  slt t2, t0, t1
  sw t2, 72(sp)
  lw t0, 72(sp)
  bnez t0, while_body_6
  j while_end_6
while_body_6:
  sw x0, 68(sp)
  j for_entry_7
while_end_6:
  lw t0, 84(sp)
  sw t0, 64(sp)
  lw t0, 64(sp)
  xor t1, t0, x0
  seqz t1, t1
  sw t1, 60(sp)
  lw t0, 60(sp)
  bnez t0, then_40
  j end_40
for_entry_7:
  lw t0, 68(sp)
  sw t0, 56(sp)
  lw t0, 56(sp)
  li t1, 4
  slt t2, t0, t1
  sw t2, 52(sp)
  lw t0, 52(sp)
  bnez t0, for_body_7
  j for_end_7
then_40:
  li a0, 73
  call putch
  li a0, 110
  call putch
  li a0, 118
  call putch
  li a0, 97
  call putch
  li a0, 108
  call putch
  li a0, 105
  call putch
  li a0, 100
  call putch
  li a0, 32
  call putch
  li a0, 105
  call putch
  li a0, 110
  call putch
  li a0, 112
  call putch
  li a0, 117
  call putch
  li a0, 116
  call putch
  li a0, 46
  call putch
  li a0, 32
  call putch
  li a0, 84
  call putch
  li a0, 114
  call putch
  li a0, 121
  call putch
  li a0, 32
  call putch
  li a0, 97
  call putch
  li a0, 103
  call putch
  li a0, 97
  call putch
  li a0, 105
  call putch
  li a0, 110
  call putch
  li a0, 46
  call putch
  li a0, 10
  call putch
  lw ra, 92(sp)
  addi sp, sp, 96
  ret

end_40:
  la t0, var_1
  lw t0, 0(t0)
  sw t0, 48(sp)
  lw t0, 48(sp)
  li t1, 1
  add t2, t0, t1
  sw t2, 44(sp)
  la t0, var_1
  lw t0, 0(t0)
  sw t0, 40(sp)
  lw t0, 44(sp)
  la t1, var_1
  sw t0, 0(t1)
  call generate
  call print_map
  lw ra, 92(sp)
  addi sp, sp, 96
  ret

for_body_7:
  lw t0, 68(sp)
  sw t0, 36(sp)
  lw t0, 88(sp)
  sw t0, 32(sp)
  lw t0, 36(sp)
  mv a0 ,t0
  lw t0, 32(sp)
  mv a1 ,t0
  call move_one_line
  sw a0, 28(sp)
  lw t0, 28(sp)
  bnez t0, then_39
  j end_39
for_end_7:
  lw t0, 80(sp)
  sw t0, 24(sp)
  lw t0, 24(sp)
  li t1, 1
  add t2, t0, t1
  sw t2, 20(sp)
  lw t0, 80(sp)
  sw t0, 16(sp)
  lw t0, 20(sp)
  sw t0, 80(sp)
  j while_entry_6
then_39:
  lw t0, 84(sp)
  sw t0, 12(sp)
  li t0, 1
  sw t0, 84(sp)
  j end_39
end_39:
  j for_update_7
for_update_7:
  lw t0, 68(sp)
  sw t0, 8(sp)
  lw t0, 8(sp)
  li t1, 1
  add t2, t0, t1
  sw t2, 4(sp)
  lw t0, 4(sp)
  sw t0, 68(sp)
  j for_entry_7
  .text
  .global can_move
can_move:
  addi sp, sp, -208
  sw x0, 204(sp)
  j while_entry_8
while_entry_8:
  lw t0, 204(sp)
  sw t0, 200(sp)
  li t0, 4
  li t1, 4
  mul t2, t0, t1
  sw t2, 196(sp)
  lw t0, 200(sp)
  lw t1, 196(sp)
  slt t2, t0, t1
  sw t2, 192(sp)
  lw t0, 192(sp)
  bnez t0, while_body_8
  j while_end_8
while_body_8:
  lw t0, 204(sp)
  sw t0, 188(sp)
  la t0, var_7
  lw t1, 188(sp)
  li t2,  4
  mul t2, t2, t1
  add t0, t0, t2
  sw t0, 184(sp)
  lw t0, 184(sp)
  lw t0, 0(t0)
  sw t0, 180(sp)
  lw t0, 180(sp)
  xor t1, t0, x0
  seqz t1, t1
  sw t1, 176(sp)
  lw t0, 176(sp)
  bnez t0, then_41
  j end_41
while_end_8:
  lw t0, 204(sp)
  sw t0, 172(sp)
  sw x0, 204(sp)
  j while_entry_9
then_41:
  li a0, 1
  addi sp, sp, 208
  ret

end_41:
  lw t0, 204(sp)
  sw t0, 168(sp)
  lw t0, 168(sp)
  li t1, 1
  add t2, t0, t1
  sw t2, 164(sp)
  lw t0, 204(sp)
  sw t0, 160(sp)
  lw t0, 164(sp)
  sw t0, 204(sp)
  j while_entry_8
while_entry_9:
  lw t0, 204(sp)
  sw t0, 156(sp)
  li t0, 4
  li t1, 4
  mul t2, t0, t1
  sw t2, 152(sp)
  lw t0, 156(sp)
  lw t1, 152(sp)
  slt t2, t0, t1
  sw t2, 148(sp)
  lw t0, 148(sp)
  bnez t0, while_body_9
  j while_end_9
while_body_9:
  lw t0, 204(sp)
  sw t0, 140(sp)
  lw t0, 140(sp)
  li t1, 4
  div t2, t0, t1
  sw t2, 136(sp)
  lw t0, 136(sp)
  sw t0, 144(sp)
  lw t0, 204(sp)
  sw t0, 128(sp)
  lw t0, 128(sp)
  li t1, 4
  rem t2, t0, t1
  sw t2, 124(sp)
  lw t0, 124(sp)
  sw t0, 132(sp)
  lw t0, 132(sp)
  sw t0, 120(sp)
  li t0, 4
  li t1, 1
  sub t2, t0, t1
  sw t2, 116(sp)
  lw t0, 120(sp)
  lw t1, 116(sp)
  slt t2, t0, t1
  sw t2, 112(sp)
  lw t0, 112(sp)
  bnez t0, then__42
  j else__42
while_end_9:
  li a0, 0
  addi sp, sp, 208
  ret

then__42:
  lw t0, 204(sp)
  sw t0, 104(sp)
  la t0, var_7
  lw t1, 104(sp)
  li t2,  4
  mul t2, t2, t1
  add t0, t0, t2
  sw t0, 100(sp)
  lw t0, 100(sp)
  lw t0, 0(t0)
  sw t0, 96(sp)
  lw t0, 204(sp)
  sw t0, 92(sp)
  lw t0, 92(sp)
  li t1, 1
  add t2, t0, t1
  sw t2, 88(sp)
  la t0, var_7
  lw t1, 88(sp)
  li t2,  4
  mul t2, t2, t1
  add t0, t0, t2
  sw t0, 84(sp)
  lw t0, 84(sp)
  lw t0, 0(t0)
  sw t0, 80(sp)
  lw t0, 96(sp)
  lw t1, 80(sp)
  xor t2, t0, t1
  seqz t2, t2
  sw t2, 76(sp)
  lw t0, 76(sp)
  xor t1, t0, x0
  snez t1, t1
  sw t1, 72(sp)
  lw t0, 72(sp)
  sw t0, 108(sp)
  j end__42
else__42:
  sw x0, 108(sp)
  j end__42
end__42:
  lw t0, 108(sp)
  sw t0, 68(sp)
  lw t0, 68(sp)
  bnez t0, then_43
  j end_43
then_43:
  li a0, 1
  addi sp, sp, 208
  ret

end_43:
  lw t0, 144(sp)
  sw t0, 64(sp)
  li t0, 4
  li t1, 1
  sub t2, t0, t1
  sw t2, 60(sp)
  lw t0, 64(sp)
  lw t1, 60(sp)
  slt t2, t0, t1
  sw t2, 56(sp)
  lw t0, 56(sp)
  bnez t0, then__44
  j else__44
then__44:
  lw t0, 204(sp)
  sw t0, 48(sp)
  la t0, var_7
  lw t1, 48(sp)
  li t2,  4
  mul t2, t2, t1
  add t0, t0, t2
  sw t0, 44(sp)
  lw t0, 44(sp)
  lw t0, 0(t0)
  sw t0, 40(sp)
  lw t0, 204(sp)
  sw t0, 36(sp)
  lw t0, 36(sp)
  li t1, 4
  add t2, t0, t1
  sw t2, 32(sp)
  la t0, var_7
  lw t1, 32(sp)
  li t2,  4
  mul t2, t2, t1
  add t0, t0, t2
  sw t0, 28(sp)
  lw t0, 28(sp)
  lw t0, 0(t0)
  sw t0, 24(sp)
  lw t0, 40(sp)
  lw t1, 24(sp)
  xor t2, t0, t1
  seqz t2, t2
  sw t2, 20(sp)
  lw t0, 20(sp)
  xor t1, t0, x0
  snez t1, t1
  sw t1, 16(sp)
  lw t0, 16(sp)
  sw t0, 52(sp)
  j end__44
else__44:
  sw x0, 52(sp)
  j end__44
end__44:
  lw t0, 52(sp)
  sw t0, 12(sp)
  lw t0, 12(sp)
  bnez t0, then_45
  j end_45
then_45:
  li a0, 1
  addi sp, sp, 208
  ret

end_45:
  lw t0, 204(sp)
  sw t0, 8(sp)
  lw t0, 8(sp)
  li t1, 1
  add t2, t0, t1
  sw t2, 4(sp)
  lw t0, 204(sp)
  sw t0, 0(sp)
  lw t0, 4(sp)
  sw t0, 204(sp)
  j while_entry_9
  .text
  .global main
main:
  addi sp, sp, -192
  sw ra, 188(sp)
  li a0, 73
  call putch
  li a0, 110
  call putch
  li a0, 112
  call putch
  li a0, 117
  call putch
  li a0, 116
  call putch
  li a0, 32
  call putch
  li a0, 97
  call putch
  li a0, 32
  call putch
  li a0, 114
  call putch
  li a0, 97
  call putch
  li a0, 110
  call putch
  li a0, 100
  call putch
  li a0, 111
  call putch
  li a0, 109
  call putch
  li a0, 32
  call putch
  li a0, 110
  call putch
  li a0, 117
  call putch
  li a0, 109
  call putch
  li a0, 98
  call putch
  li a0, 101
  call putch
  li a0, 114
  call putch
  li a0, 58
  call putch
  li a0, 32
  call putch
  li a0, 10
  call putch
  call getint
  sw a0, 184(sp)
  la t0, var_4
  lw t0, 0(t0)
  sw t0, 180(sp)
  lw t0, 184(sp)
  la t1, var_4
  sw t0, 0(t1)
  call init
  call generate
  call print_map
  j while_entry_10
while_entry_10:
  la t0, var_3
  lw t0, 0(t0)
  sw t0, 176(sp)
  lw t0, 176(sp)
  bnez t0, while_body_10
  j while_end_10
while_body_10:
  call getch
  sw a0, 168(sp)
  lw t0, 168(sp)
  sw t0, 172(sp)
  lw t0, 172(sp)
  sw t0, 164(sp)
  lw t0, 164(sp)
  li t1, 119
  xor t2, t0, t1
  seqz t2, t2
  sw t2, 160(sp)
  lw t0, 160(sp)
  bnez t0, then_46
  j else_46
while_end_10:
  li a0, 0
  lw ra, 188(sp)
  addi sp, sp, 192
  ret

then_46:
  li a0, 0
  call move
  j end_46
else_46:
  lw t0, 172(sp)
  sw t0, 156(sp)
  lw t0, 156(sp)
  li t1, 97
  xor t2, t0, t1
  seqz t2, t2
  sw t2, 152(sp)
  lw t0, 152(sp)
  bnez t0, then_47
  j else_47
end_46:
  call can_move
  sw a0, 148(sp)
  lw t0, 148(sp)
  xor t1, t0, x0
  seqz t1, t1
  sw t1, 144(sp)
  lw t0, 144(sp)
  bnez t0, then_57
  j end_57
then_47:
  li a0, 2
  call move
  j end_47
else_47:
  lw t0, 172(sp)
  sw t0, 140(sp)
  lw t0, 140(sp)
  li t1, 115
  xor t2, t0, t1
  seqz t2, t2
  sw t2, 136(sp)
  lw t0, 136(sp)
  bnez t0, then_48
  j else_48
then_57:
  li a0, 71
  call putch
  li a0, 97
  call putch
  li a0, 109
  call putch
  li a0, 101
  call putch
  li a0, 32
  call putch
  li a0, 111
  call putch
  li a0, 118
  call putch
  li a0, 101
  call putch
  li a0, 114
  call putch
  li a0, 33
  call putch
  li a0, 10
  call putch
  j while_end_10
end_57:
  j while_entry_10
end_47:
  j end_46
then_48:
  li a0, 1
  call move
  j end_48
else_48:
  lw t0, 172(sp)
  sw t0, 132(sp)
  lw t0, 132(sp)
  li t1, 100
  xor t2, t0, t1
  seqz t2, t2
  sw t2, 128(sp)
  lw t0, 128(sp)
  bnez t0, then_49
  j else_49
end_48:
  j end_47
then_49:
  li a0, 3
  call move
  j end_49
else_49:
  lw t0, 172(sp)
  sw t0, 124(sp)
  lw t0, 124(sp)
  li t1, 104
  xor t2, t0, t1
  seqz t2, t2
  sw t2, 120(sp)
  lw t0, 120(sp)
  bnez t0, then_50
  j else_50
end_49:
  j end_48
then_50:
  li a0, 119
  call putch
  li a0, 44
  call putch
  li a0, 32
  call putch
  li a0, 97
  call putch
  li a0, 44
  call putch
  li a0, 32
  call putch
  li a0, 115
  call putch
  li a0, 44
  call putch
  li a0, 32
  call putch
  li a0, 100
  call putch
  li a0, 58
  call putch
  li a0, 32
  call putch
  li a0, 109
  call putch
  li a0, 111
  call putch
  li a0, 118
  call putch
  li a0, 101
  call putch
  li a0, 10
  call putch
  li a0, 104
  call putch
  li a0, 58
  call putch
  li a0, 32
  call putch
  li a0, 112
  call putch
  li a0, 114
  call putch
  li a0, 105
  call putch
  li a0, 110
  call putch
  li a0, 116
  call putch
  li a0, 32
  call putch
  li a0, 116
  call putch
  li a0, 104
  call putch
  li a0, 105
  call putch
  li a0, 115
  call putch
  li a0, 32
  call putch
  li a0, 104
  call putch
  li a0, 101
  call putch
  li a0, 108
  call putch
  li a0, 112
  call putch
  li a0, 10
  call putch
  li a0, 113
  call putch
  li a0, 58
  call putch
  li a0, 32
  call putch
  li a0, 113
  call putch
  li a0, 117
  call putch
  li a0, 105
  call putch
  li a0, 116
  call putch
  li a0, 10
  call putch
  li a0, 112
  call putch
  li a0, 58
  call putch
  li a0, 32
  call putch
  li a0, 112
  call putch
  li a0, 114
  call putch
  li a0, 105
  call putch
  li a0, 110
  call putch
  li a0, 116
  call putch
  li a0, 32
  call putch
  li a0, 116
  call putch
  li a0, 104
  call putch
  li a0, 101
  call putch
  li a0, 32
  call putch
  li a0, 109
  call putch
  li a0, 97
  call putch
  li a0, 112
  call putch
  li a0, 10
  call putch
  j end_50
else_50:
  lw t0, 172(sp)
  sw t0, 116(sp)
  lw t0, 116(sp)
  li t1, 113
  xor t2, t0, t1
  seqz t2, t2
  sw t2, 112(sp)
  lw t0, 112(sp)
  bnez t0, then__51
  j else__51
end_50:
  j end_49
then__51:
  li t0, 1
  sw t0, 108(sp)
  j end__51
else__51:
  lw t0, 172(sp)
  sw t0, 104(sp)
  li t0, 1
  sub t1, x0, t0
  sw t1, 100(sp)
  lw t0, 104(sp)
  lw t1, 100(sp)
  xor t2, t0, t1
  seqz t2, t2
  sw t2, 96(sp)
  lw t0, 96(sp)
  xor t1, t0, x0
  snez t1, t1
  sw t1, 92(sp)
  lw t0, 92(sp)
  sw t0, 108(sp)
  j end__51
end__51:
  lw t0, 108(sp)
  sw t0, 88(sp)
  lw t0, 88(sp)
  bnez t0, then_52
  j else_52
then_52:
  li a0, 71
  call putch
  li a0, 97
  call putch
  li a0, 109
  call putch
  li a0, 101
  call putch
  li a0, 32
  call putch
  li a0, 111
  call putch
  li a0, 118
  call putch
  li a0, 101
  call putch
  li a0, 114
  call putch
  li a0, 33
  call putch
  li a0, 10
  call putch
  li a0, 0
  lw ra, 188(sp)
  addi sp, sp, 192
  ret

else_52:
  lw t0, 172(sp)
  sw t0, 84(sp)
  lw t0, 84(sp)
  li t1, 112
  xor t2, t0, t1
  seqz t2, t2
  sw t2, 80(sp)
  lw t0, 80(sp)
  bnez t0, then_53
  j else_53
then_53:
  li a0, 10
  call putch
  call print_map
  j end_53
else_53:
  lw t0, 172(sp)
  sw t0, 76(sp)
  lw t0, 76(sp)
  li t1, 32
  xor t2, t0, t1
  seqz t2, t2
  sw t2, 72(sp)
  lw t0, 72(sp)
  bnez t0, then__54
  j else__54
end_53:
  j end_52
then__54:
  li t0, 1
  sw t0, 68(sp)
  j end__54
else__54:
  lw t0, 172(sp)
  sw t0, 64(sp)
  lw t0, 64(sp)
  li t1, 10
  xor t2, t0, t1
  seqz t2, t2
  sw t2, 60(sp)
  lw t0, 60(sp)
  xor t1, t0, x0
  snez t1, t1
  sw t1, 56(sp)
  lw t0, 56(sp)
  sw t0, 68(sp)
  j end__54
end_52:
  j end_50
end__54:
  lw t0, 68(sp)
  sw t0, 52(sp)
  lw t0, 52(sp)
  bnez t0, then__55
  j else__55
then__55:
  li t0, 1
  sw t0, 48(sp)
  j end__55
else__55:
  lw t0, 172(sp)
  sw t0, 44(sp)
  lw t0, 44(sp)
  li t1, 13
  xor t2, t0, t1
  seqz t2, t2
  sw t2, 40(sp)
  lw t0, 40(sp)
  xor t1, t0, x0
  snez t1, t1
  sw t1, 36(sp)
  lw t0, 36(sp)
  sw t0, 48(sp)
  j end__55
end__55:
  lw t0, 48(sp)
  sw t0, 32(sp)
  lw t0, 32(sp)
  bnez t0, then_56
  j else_56
then_56:
  j while_entry_10
else_56:
  li a0, 73
  call putch
  li a0, 110
  call putch
  li a0, 118
  call putch
  li a0, 97
  call putch
  li a0, 108
  call putch
  li a0, 105
  call putch
  li a0, 100
  call putch
  li a0, 32
  call putch
  li a0, 105
  call putch
  li a0, 110
  call putch
  li a0, 112
  call putch
  li a0, 117
  call putch
  li a0, 116
  call putch
  li a0, 46
  call putch
  li a0, 32
  call putch
  li a0, 84
  call putch
  li a0, 114
  call putch
  li a0, 121
  call putch
  li a0, 32
  call putch
  li a0, 97
  call putch
  li a0, 103
  call putch
  li a0, 97
  call putch
  li a0, 105
  call putch
  li a0, 110
  call putch
  li a0, 46
  call putch
  li a0, 10
  call putch
  la t0, var_4
  lw t0, 0(t0)
  sw t0, 28(sp)
  lw t0, 172(sp)
  sw t0, 24(sp)
  lw t0, 28(sp)
  lw t1, 24(sp)
  add t2, t0, t1
  sw t2, 20(sp)
  lw t0, 20(sp)
  li t1, 1073741824
  rem t2, t0, t1
  sw t2, 16(sp)
  la t0, var_4
  lw t0, 0(t0)
  sw t0, 12(sp)
  lw t0, 16(sp)
  la t1, var_4
  sw t0, 0(t1)
  j end_56
end_56:
  j end_53
