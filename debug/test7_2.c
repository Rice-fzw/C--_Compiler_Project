int sum(int a0, int a1, int a2, int a3, int a4, int a5, int a6, int a7) {
  return a0 + a1 + a2 + a3 + a4 + a5 + a6 + a7;
}
int sum2(int a0, int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8,
         int a9, int a10, int a11, int a12, int a13, int a14, int a15) {
  return a0 + a1 + a2 + a3 + a4 + a5 + a6 + a7 + a8 + a9 + a10 + a11 + a12 +
         a13 + a14 + a15;
}
int e0[2] = {22, 33}, f0[6], g0[9] = {85, 0, 1, 29};
int x, y;
int t() {
  x = x + 1;
  return 1;
}
int f() {
  y = y + 1;
  return !t();
}
int main() {
  int ssum = 0;
  int lis[20] = {(f() || f()) & 3, x + y * 2, sum(1, 4 * 2 - f() + t(), 3, f(), 5, 6, f(), 8)};
  x = sum(1, 2, 3, 4, 5, 6, 7, 8);
  y = sum2(1, 2, 3, 4, 5, 6, 7, x, 9, 10, 11, 12, sum(1, 2, 2, 4, 5, 6, 6, 8), 14, 15, 16);
  while (1) {
    int a = 1, b = 2;
    {
      ssum = ssum + (f() || f()) & 3 + 6 | 13 / sum(1, 4 * 2 - f() + t(), 3, f(), 5, 6, f(), 8);
      if (a == 1) {
        for (;a < b;) {
          while (a < b || b - 1 == 0) {
            a = a + 1;
          }
          b = 1;
          a = a + 1;
          if (3) continue;
        }
      } else if (b == 6) {
        break;
      }
      int b = 6;
      if (b == 6) return 8 * (10 || b);
      else while (0);
    }
  }
  return -1;
}