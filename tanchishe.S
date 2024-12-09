  .text
  .global main
main:
  li t0, -2752
  add t0, t0, sp
  add sp, sp, t0
  li t0, 2748
  add t0, t0, sp
  sw ra, 0(t0)
  lw t0, 732(sp)
  sw t0, 724(sp)
  li t0, 1
  sw t0, 732(sp)
  lw t0, 732(sp)
  sw t0, 720(sp)
  lw t0, 740(sp)
  sw t0, 716(sp)
  li t0, 3
  sw t0, 740(sp)
  lw t0, 740(sp)
  sw t0, 712(sp)
  lw t0, 744(sp)
  sw t0, 708(sp)
  li t0, 4
  sw t0, 744(sp)
  lw t0, 744(sp)
  sw t0, 704(sp)
  lw t0, 728(sp)
  sw t0, 700(sp)
  sw x0, 728(sp)
  lw t0, 728(sp)
  sw t0, 696(sp)
  j while_entry_0
while_entry_0:
  lw t0, 728(sp)
  sw t0, 692(sp)
  lw t0, 692(sp)
  li t1, 400
  slt t2, t0, t1
  sw t2, 688(sp)
  lw t0, 688(sp)
  bnez t0, while_body_0
  j while_end_0
while_body_0:
  lw t0, 728(sp)
  sw t0, 684(sp)
  addi t0, sp, 1148
  lw t1, 684(sp)
  li t2,  4
  mul t2, t2, t1
  add t0, t0, t2
  sw t0, 680(sp)
  lw t0, 680(sp)
  lw t0, 0(t0)
  sw t0, 676(sp)
  lw t0, 680(sp)
  sw x0, 0(t0)
  lw t0, 680(sp)
  lw t0, 0(t0)
  sw t0, 672(sp)
  lw t0, 728(sp)
  sw t0, 668(sp)
  lw t0, 668(sp)
  li t1, 1
  add t2, t0, t1
  sw t2, 664(sp)
  lw t0, 728(sp)
  sw t0, 660(sp)
  lw t0, 664(sp)
  sw t0, 728(sp)
  lw t0, 728(sp)
  sw t0, 656(sp)
  j while_entry_0
while_end_0:
  addi t0, sp, 748
  sw t0, 652(sp)
  lw t0, 652(sp)
  lw t0, 0(t0)
  sw t0, 648(sp)
  li t0, 21
  lw t1, 652(sp)
  sw t0, 0(t1)
  lw t0, 652(sp)
  lw t0, 0(t0)
  sw t0, 644(sp)
  addi t0, sp, 748
  li t1, 1
  li t2,  4
  mul t2, t2, t1
  add t0, t0, t2
  sw t0, 640(sp)
  lw t0, 640(sp)
  lw t0, 0(t0)
  sw t0, 636(sp)
  li t0, 20
  lw t1, 640(sp)
  sw t0, 0(t1)
  lw t0, 640(sp)
  lw t0, 0(t0)
  sw t0, 632(sp)
  addi t0, sp, 748
  li t1, 2
  li t2,  4
  mul t2, t2, t1
  add t0, t0, t2
  sw t0, 628(sp)
  lw t0, 628(sp)
  lw t0, 0(t0)
  sw t0, 624(sp)
  li t0, 19
  lw t1, 628(sp)
  sw t0, 0(t1)
  lw t0, 628(sp)
  lw t0, 0(t0)
  sw t0, 620(sp)
  lw t0, 736(sp)
  sw t0, 616(sp)
  li t0, 156
  sw t0, 736(sp)
  lw t0, 736(sp)
  sw t0, 612(sp)
  lw t0, 736(sp)
  sw t0, 608(sp)
  addi t0, sp, 1148
  lw t1, 608(sp)
  li t2,  4
  mul t2, t2, t1
  add t0, t0, t2
  sw t0, 604(sp)
  lw t0, 604(sp)
  lw t0, 0(t0)
  sw t0, 600(sp)
  li t0, 2
  lw t1, 604(sp)
  sw t0, 0(t1)
  lw t0, 604(sp)
  lw t0, 0(t0)
  sw t0, 596(sp)
  j while_entry_1
while_entry_1:
  lw t0, 732(sp)
  sw t0, 592(sp)
  lw t0, 592(sp)
  bnez t0, while_body_1
  j while_end_1
while_body_1:
  li a0, 10
  call putch
  call getint
  sw a0, 588(sp)
  lw t0, 744(sp)
  sw t0, 584(sp)
  lw t0, 588(sp)
  sw t0, 744(sp)
  lw t0, 744(sp)
  sw t0, 580(sp)
  lw t0, 744(sp)
  sw t0, 576(sp)
  lw t0, 576(sp)
  li t1, 1
  xor t2, t0, t1
  seqz t2, t2
  sw t2, 572(sp)
  lw t0, 572(sp)
  bnez t0, then_0
  j else_0
while_end_1:
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
  li a0, 79
  call putch
  li a0, 118
  call putch
  li a0, 101
  call putch
  li a0, 114
  call putch
  li a0, 33
  call putch
  li a0, 0
  li t0, 2748
  add t0, t0, sp
  lw ra, 0(t0)
  li t0, 2752
  add t0, t0, sp
  add sp, sp, t0
  ret

then_0:
  addi t0, sp, 748
  sw t0, 568(sp)
  lw t0, 568(sp)
  lw t0, 0(t0)
  sw t0, 564(sp)
  lw t0, 564(sp)
  li t1, 20
  sub t2, t0, t1
  sw t2, 560(sp)
  addi t0, sp, 748
  sw t0, 556(sp)
  lw t0, 556(sp)
  lw t0, 0(t0)
  sw t0, 552(sp)
  lw t0, 560(sp)
  lw t1, 556(sp)
  sw t0, 0(t1)
  lw t0, 556(sp)
  lw t0, 0(t0)
  sw t0, 548(sp)
  j end_0
else_0:
  lw t0, 744(sp)
  sw t0, 544(sp)
  lw t0, 544(sp)
  li t1, 2
  xor t2, t0, t1
  seqz t2, t2
  sw t2, 540(sp)
  lw t0, 540(sp)
  bnez t0, then_1
  j else_1
end_0:
  addi t0, sp, 748
  sw t0, 536(sp)
  lw t0, 536(sp)
  lw t0, 0(t0)
  sw t0, 532(sp)
  lw t0, 736(sp)
  sw t0, 528(sp)
  lw t0, 532(sp)
  lw t1, 528(sp)
  xor t2, t0, t1
  seqz t2, t2
  sw t2, 524(sp)
  lw t0, 524(sp)
  bnez t0, then_4
  j else_4
then_1:
  addi t0, sp, 748
  sw t0, 520(sp)
  lw t0, 520(sp)
  lw t0, 0(t0)
  sw t0, 516(sp)
  lw t0, 516(sp)
  li t1, 20
  add t2, t0, t1
  sw t2, 512(sp)
  addi t0, sp, 748
  sw t0, 508(sp)
  lw t0, 508(sp)
  lw t0, 0(t0)
  sw t0, 504(sp)
  lw t0, 512(sp)
  lw t1, 508(sp)
  sw t0, 0(t1)
  lw t0, 508(sp)
  lw t0, 0(t0)
  sw t0, 500(sp)
  j end_1
else_1:
  lw t0, 744(sp)
  sw t0, 496(sp)
  lw t0, 496(sp)
  li t1, 3
  xor t2, t0, t1
  seqz t2, t2
  sw t2, 492(sp)
  lw t0, 492(sp)
  bnez t0, then_2
  j else_2
then_4:
  lw t0, 740(sp)
  sw t0, 488(sp)
  lw t0, 488(sp)
  li t1, 1
  add t2, t0, t1
  sw t2, 484(sp)
  lw t0, 740(sp)
  sw t0, 480(sp)
  lw t0, 484(sp)
  sw t0, 740(sp)
  lw t0, 740(sp)
  sw t0, 476(sp)
  lw t0, 736(sp)
  sw t0, 472(sp)
  lw t0, 472(sp)
  li t1, 31
  add t2, t0, t1
  sw t2, 468(sp)
  lw t0, 736(sp)
  sw t0, 464(sp)
  lw t0, 468(sp)
  sw t0, 736(sp)
  lw t0, 736(sp)
  sw t0, 460(sp)
  lw t0, 736(sp)
  sw t0, 456(sp)
  lw t0, 456(sp)
  li t1, 400
  sgt t2, t1, t0
  seqz t2, t2
  sw t2, 452(sp)
  lw t0, 452(sp)
  bnez t0, then_5
  j end_5
else_4:
  lw t0, 740(sp)
  sw t0, 448(sp)
  lw t0, 448(sp)
  li t1, 1
  sub t2, t0, t1
  sw t2, 444(sp)
  lw t0, 728(sp)
  sw t0, 440(sp)
  lw t0, 444(sp)
  sw t0, 728(sp)
  lw t0, 728(sp)
  sw t0, 436(sp)
  j while_entry_2
end_1:
  j end_0
then_2:
  addi t0, sp, 748
  sw t0, 432(sp)
  lw t0, 432(sp)
  lw t0, 0(t0)
  sw t0, 428(sp)
  lw t0, 428(sp)
  li t1, 1
  sub t2, t0, t1
  sw t2, 424(sp)
  addi t0, sp, 748
  sw t0, 420(sp)
  lw t0, 420(sp)
  lw t0, 0(t0)
  sw t0, 416(sp)
  lw t0, 424(sp)
  lw t1, 420(sp)
  sw t0, 0(t1)
  lw t0, 420(sp)
  lw t0, 0(t0)
  sw t0, 412(sp)
  j end_2
else_2:
  lw t0, 744(sp)
  sw t0, 408(sp)
  lw t0, 408(sp)
  li t1, 4
  xor t2, t0, t1
  seqz t2, t2
  sw t2, 404(sp)
  lw t0, 404(sp)
  bnez t0, then_3
  j end_3
then_5:
  lw t0, 736(sp)
  sw t0, 400(sp)
  lw t0, 400(sp)
  li t1, 399
  sub t2, t0, t1
  sw t2, 396(sp)
  lw t0, 736(sp)
  sw t0, 392(sp)
  lw t0, 396(sp)
  sw t0, 736(sp)
  lw t0, 736(sp)
  sw t0, 388(sp)
  j end_5
end_5:
  lw t0, 736(sp)
  sw t0, 384(sp)
  addi t0, sp, 1148
  lw t1, 384(sp)
  li t2,  4
  mul t2, t2, t1
  add t0, t0, t2
  sw t0, 380(sp)
  lw t0, 380(sp)
  lw t0, 0(t0)
  sw t0, 376(sp)
  li t0, 2
  lw t1, 380(sp)
  sw t0, 0(t1)
  lw t0, 380(sp)
  lw t0, 0(t0)
  sw t0, 372(sp)
  j end_4
while_entry_2:
  lw t0, 728(sp)
  sw t0, 368(sp)
  lw t0, 368(sp)
  slt t1, x0, t0
  sw t1, 364(sp)
  lw t0, 364(sp)
  bnez t0, while_body_2
  j while_end_2
end_2:
  j end_1
then_3:
  addi t0, sp, 748
  sw t0, 360(sp)
  lw t0, 360(sp)
  lw t0, 0(t0)
  sw t0, 356(sp)
  lw t0, 356(sp)
  li t1, 1
  add t2, t0, t1
  sw t2, 352(sp)
  addi t0, sp, 748
  sw t0, 348(sp)
  lw t0, 348(sp)
  lw t0, 0(t0)
  sw t0, 344(sp)
  lw t0, 352(sp)
  lw t1, 348(sp)
  sw t0, 0(t1)
  lw t0, 348(sp)
  lw t0, 0(t0)
  sw t0, 340(sp)
  j end_3
end_3:
  j end_2
end_4:
  addi t0, sp, 748
  sw t0, 336(sp)
  lw t0, 336(sp)
  lw t0, 0(t0)
  sw t0, 332(sp)
  lw t0, 332(sp)
  slt t1, t0, x0
  sw t1, 328(sp)
  lw t0, 328(sp)
  bnez t0, then_6
  j end_6
while_body_2:
  lw t0, 728(sp)
  sw t0, 324(sp)
  lw t0, 324(sp)
  li t1, 1
  sub t2, t0, t1
  sw t2, 320(sp)
  addi t0, sp, 748
  lw t1, 320(sp)
  li t2,  4
  mul t2, t2, t1
  add t0, t0, t2
  sw t0, 316(sp)
  lw t0, 316(sp)
  lw t0, 0(t0)
  sw t0, 312(sp)
  lw t0, 728(sp)
  sw t0, 308(sp)
  addi t0, sp, 748
  lw t1, 308(sp)
  li t2,  4
  mul t2, t2, t1
  add t0, t0, t2
  sw t0, 304(sp)
  lw t0, 304(sp)
  lw t0, 0(t0)
  sw t0, 300(sp)
  lw t0, 312(sp)
  lw t1, 304(sp)
  sw t0, 0(t1)
  lw t0, 304(sp)
  lw t0, 0(t0)
  sw t0, 296(sp)
  lw t0, 728(sp)
  sw t0, 292(sp)
  lw t0, 292(sp)
  li t1, 1
  sub t2, t0, t1
  sw t2, 288(sp)
  lw t0, 728(sp)
  sw t0, 284(sp)
  lw t0, 288(sp)
  sw t0, 728(sp)
  lw t0, 728(sp)
  sw t0, 280(sp)
  j while_entry_2
while_end_2:
  j end_4
then_6:
  lw t0, 732(sp)
  sw t0, 276(sp)
  sw x0, 732(sp)
  lw t0, 732(sp)
  sw t0, 272(sp)
  j end_6
end_6:
  addi t0, sp, 748
  sw t0, 268(sp)
  lw t0, 268(sp)
  lw t0, 0(t0)
  sw t0, 264(sp)
  lw t0, 264(sp)
  li t1, 400
  sgt t2, t1, t0
  seqz t2, t2
  sw t2, 260(sp)
  lw t0, 260(sp)
  bnez t0, then_7
  j end_7
then_7:
  lw t0, 732(sp)
  sw t0, 256(sp)
  sw x0, 732(sp)
  lw t0, 732(sp)
  sw t0, 252(sp)
  j end_7
end_7:
  addi t0, sp, 748
  sw t0, 248(sp)
  lw t0, 248(sp)
  lw t0, 0(t0)
  sw t0, 244(sp)
  lw t0, 244(sp)
  li t1, 20
  div t2, t0, t1
  sw t2, 240(sp)
  addi t0, sp, 748
  li t1, 1
  li t2,  4
  mul t2, t2, t1
  add t0, t0, t2
  sw t0, 236(sp)
  lw t0, 236(sp)
  lw t0, 0(t0)
  sw t0, 232(sp)
  lw t0, 232(sp)
  li t1, 20
  div t2, t0, t1
  sw t2, 228(sp)
  lw t0, 240(sp)
  lw t1, 228(sp)
  xor t2, t0, t1
  snez t2, t2
  sw t2, 224(sp)
  lw t0, 224(sp)
  bnez t0, then_8
  j end_8
then_8:
  lw t0, 732(sp)
  sw t0, 220(sp)
  sw x0, 732(sp)
  lw t0, 732(sp)
  sw t0, 216(sp)
  j end_8
end_8:
  lw t0, 728(sp)
  sw t0, 212(sp)
  sw x0, 728(sp)
  lw t0, 728(sp)
  sw t0, 208(sp)
  j while_entry_3
while_entry_3:
  lw t0, 728(sp)
  sw t0, 204(sp)
  lw t0, 204(sp)
  li t1, 400
  slt t2, t0, t1
  sw t2, 200(sp)
  lw t0, 200(sp)
  bnez t0, while_body_3
  j while_end_3
while_body_3:
  lw t0, 728(sp)
  sw t0, 196(sp)
  addi t0, sp, 1148
  lw t1, 196(sp)
  li t2,  4
  mul t2, t2, t1
  add t0, t0, t2
  sw t0, 192(sp)
  lw t0, 192(sp)
  lw t0, 0(t0)
  sw t0, 188(sp)
  lw t0, 192(sp)
  sw x0, 0(t0)
  lw t0, 192(sp)
  lw t0, 0(t0)
  sw t0, 184(sp)
  lw t0, 728(sp)
  sw t0, 180(sp)
  lw t0, 180(sp)
  li t1, 1
  add t2, t0, t1
  sw t2, 176(sp)
  lw t0, 728(sp)
  sw t0, 172(sp)
  lw t0, 176(sp)
  sw t0, 728(sp)
  lw t0, 728(sp)
  sw t0, 168(sp)
  j while_entry_3
while_end_3:
  lw t0, 728(sp)
  sw t0, 164(sp)
  sw x0, 728(sp)
  lw t0, 728(sp)
  sw t0, 160(sp)
  j while_entry_4
while_entry_4:
  lw t0, 728(sp)
  sw t0, 156(sp)
  lw t0, 740(sp)
  sw t0, 152(sp)
  lw t0, 156(sp)
  lw t1, 152(sp)
  slt t2, t0, t1
  sw t2, 148(sp)
  lw t0, 148(sp)
  bnez t0, while_body_4
  j while_end_4
while_body_4:
  lw t0, 728(sp)
  sw t0, 144(sp)
  addi t0, sp, 748
  lw t1, 144(sp)
  li t2,  4
  mul t2, t2, t1
  add t0, t0, t2
  sw t0, 140(sp)
  lw t0, 140(sp)
  lw t0, 0(t0)
  sw t0, 136(sp)
  addi t0, sp, 1148
  lw t1, 136(sp)
  li t2,  4
  mul t2, t2, t1
  add t0, t0, t2
  sw t0, 132(sp)
  lw t0, 132(sp)
  lw t0, 0(t0)
  sw t0, 128(sp)
  li t0, 1
  lw t1, 132(sp)
  sw t0, 0(t1)
  lw t0, 132(sp)
  lw t0, 0(t0)
  sw t0, 124(sp)
  lw t0, 728(sp)
  sw t0, 120(sp)
  lw t0, 120(sp)
  li t1, 1
  add t2, t0, t1
  sw t2, 116(sp)
  lw t0, 728(sp)
  sw t0, 112(sp)
  lw t0, 116(sp)
  sw t0, 728(sp)
  lw t0, 728(sp)
  sw t0, 108(sp)
  j while_entry_4
while_end_4:
  lw t0, 736(sp)
  sw t0, 104(sp)
  addi t0, sp, 1148
  lw t1, 104(sp)
  li t2,  4
  mul t2, t2, t1
  add t0, t0, t2
  sw t0, 100(sp)
  lw t0, 100(sp)
  lw t0, 0(t0)
  sw t0, 96(sp)
  li t0, 2
  lw t1, 100(sp)
  sw t0, 0(t1)
  lw t0, 100(sp)
  lw t0, 0(t0)
  sw t0, 92(sp)
  lw t0, 728(sp)
  sw t0, 88(sp)
  sw x0, 728(sp)
  lw t0, 728(sp)
  sw t0, 84(sp)
  j while_entry_5
while_entry_5:
  lw t0, 728(sp)
  sw t0, 80(sp)
  lw t0, 80(sp)
  li t1, 400
  slt t2, t0, t1
  sw t2, 76(sp)
  lw t0, 76(sp)
  bnez t0, while_body_5
  j while_end_5
while_body_5:
  lw t0, 728(sp)
  sw t0, 72(sp)
  addi t0, sp, 1148
  lw t1, 72(sp)
  li t2,  4
  mul t2, t2, t1
  add t0, t0, t2
  sw t0, 68(sp)
  lw t0, 68(sp)
  lw t0, 0(t0)
  sw t0, 64(sp)
  lw t0, 64(sp)
  xor t1, t0, x0
  seqz t1, t1
  sw t1, 60(sp)
  lw t0, 60(sp)
  bnez t0, then_9
  j else_9
while_end_5:
  li a0, 83
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
  lw t0, 740(sp)
  sw t0, 56(sp)
  lw t0, 56(sp)
  li t1, 3
  sub t2, t0, t1
  sw t2, 52(sp)
  lw t0, 52(sp)
  mv a0, t0
  call putint
  li a0, 10
  call putch
  j while_entry_1
then_9:
  li a0, 46
  call putch
  j end_9
else_9:
  lw t0, 728(sp)
  sw t0, 48(sp)
  addi t0, sp, 1148
  lw t1, 48(sp)
  li t2,  4
  mul t2, t2, t1
  add t0, t0, t2
  sw t0, 44(sp)
  lw t0, 44(sp)
  lw t0, 0(t0)
  sw t0, 40(sp)
  lw t0, 40(sp)
  li t1, 1
  xor t2, t0, t1
  seqz t2, t2
  sw t2, 36(sp)
  lw t0, 36(sp)
  bnez t0, then_10
  j else_10
end_9:
  lw t0, 728(sp)
  sw t0, 32(sp)
  lw t0, 32(sp)
  li t1, 1
  add t2, t0, t1
  sw t2, 28(sp)
  lw t0, 28(sp)
  li t1, 20
  rem t2, t0, t1
  sw t2, 24(sp)
  lw t0, 24(sp)
  xor t1, t0, x0
  seqz t1, t1
  sw t1, 20(sp)
  lw t0, 20(sp)
  bnez t0, then_11
  j end_11
then_10:
  li a0, 79
  call putch
  j end_10
else_10:
  li a0, 88
  call putch
  j end_10
then_11:
  li a0, 10
  call putch
  j end_11
end_11:
  lw t0, 728(sp)
  sw t0, 16(sp)
  lw t0, 16(sp)
  li t1, 1
  add t2, t0, t1
  sw t2, 12(sp)
  lw t0, 728(sp)
  sw t0, 8(sp)
  lw t0, 12(sp)
  sw t0, 728(sp)
  lw t0, 728(sp)
  sw t0, 4(sp)
  j while_entry_5
end_10:
  j end_9
