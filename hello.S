decl @getint(): i32
decl @getch(): i32
decl @getarray(*i32): i32
decl @putint(i32)
decl @putch(i32)
decl @putarray(i32, *i32)
decl @starttime()
decl @stoptime()

global @garr_0 = alloc [i32, 10], {6, 7, 8, 9, 10, 11, 12, 13, 14, 15}
fun @main(): i32 {
%entry:
 @arr_0 = alloc [i32, 10]
  %0 = getelemptr @arr_0, 0
  store 1, %0
  %1 = getelemptr @arr_0, 1
  store 2, %1
  %2 = getelemptr @arr_0, 2
  store 3, %2
  %3 = getelemptr @arr_0, 3
  store 4, %3
  %4 = getelemptr @arr_0, 4
  store 5, %4
  %5 = getelemptr @arr_0, 5
  store 0, %5
  %6 = getelemptr @arr_0, 6
  store 0, %6
  %7 = getelemptr @arr_0, 7
  store 0, %7
  %8 = getelemptr @arr_0, 8
  store 0, %8
  %9 = getelemptr @arr_0, 9
  store 0, %9
  @i_0 = alloc i32
  store 0, @i_0
  @sum_0 = alloc i32
  store 0, @sum_0
  jump %while_entry_0
%while_entry_0:
  %10 = load @i_0
  %11 = lt %10, 10
  br %11, %while_body_0, %while_end_0
%while_body_0:
  %12 = load @sum_0
  %13 = load @i_0
  %14 = getelemptr @arr_0, %13
  %15 = load %14
  %16 = add %12, %15
  %17 = load @i_0
  %18 = getelemptr @garr_0, %17
  %19 = load %18
  %20 = add %16, %19
  %21 = load @sum_0
  store %20, @sum_0
  %22 = load @i_0
  %23 = add %22, 1
  %24 = load @i_0
  store %23, @i_0
  jump %while_entry_0
%while_end_0:
  %25 = load @sum_0
  ret %25
}

