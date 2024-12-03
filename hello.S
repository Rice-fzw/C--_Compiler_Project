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
  @a_0 = alloc i32
  store 10, @a_0
  %0 = load @a_0
  %1 = add %0, 1
  store %1, @a_0
  %2 = load @a_0
  %3 = sub %2, 1
  store %3, @a_0
  %4 = load @a_0
  %5 = add %4, 1
  store %5, @a_0
  call @putint(%5)
  %6 = load @a_0
  %7 = add %6, 0
  %8 = add %6, 1
  store %8, @a_0
  call @putint(%7)
  %9 = load @a_0
  ret %9
}

