decl @getint(): i32
decl @getch(): i32
decl @getarray(*i32): i32
decl @putint(i32)
decl @putch(i32)
decl @putarray(i32, *i32)
decl @starttime()
decl @stoptime()

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
  jump %while_entry_0
%while_entry_0:
  %10 = load @i_0
  %11 = lt %10, 10
  br %11, %while_body_0, %while_end_0
%while_body_0:
  @x_0 = alloc [i32, 10]
  %12 = getelemptr @x_0, 0
  store 0, %12
  %13 = getelemptr @x_0, 1
  store 0, %13
  %14 = getelemptr @x_0, 2
  store 0, %14
  %15 = getelemptr @x_0, 3
  store 0, %15
  %16 = getelemptr @x_0, 4
  store 0, %16
  %17 = getelemptr @x_0, 5
  store 0, %17
  %18 = getelemptr @x_0, 6
  store 0, %18
  %19 = getelemptr @x_0, 7
  store 0, %19
  %20 = getelemptr @x_0, 8
  store 0, %20
  %21 = getelemptr @x_0, 9
  store 0, %21
  %22 = load @i_0
  %23 = getelemptr @arr_0, %22
  %24 = load %23
  %25 = load @i_0
  %26 = add %24, %25
  %27 = load @i_0
  %28 = getelemptr @x_0, %27
  %29 = load %28
  %30 = add %26, %29
  %31 = load @i_0
  %32 = getelemptr @arr_0, %31
  %33 = load %32
  store %30, 
  %34 = load @i_0
  %35 = getelemptr @arr_0, %34
  %36 = load %35
  %37 = load @i_0
  %38 = getelemptr @x_0, %37
  %39 = load %38
  store %36, 
  %40 = load @i_0
  %41 = add %40, 1
  %42 = load @i_0
  store %41, @i_0
  jump %while_entry_0
%while_end_0:
  %43 = getelemptr @arr_0, 9
  %44 = load %43
  ret %44
}

