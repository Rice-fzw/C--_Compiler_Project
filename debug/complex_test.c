int sum(int a0, int a1, int a2, int a3, int a4, int a5, int a6, int a7);

int sum2(int a0, int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8,
        int a9, int a10, int a11, int a12, int a13, int a14, int a15);

int t();

int f();

int sum(int a0, int a1, int a2, int a3, int a4, int a5, int a6, int a7) {
  return a0 + a1 + a2 + a3 + a4 + a5 + a6 + a7;
}

int sum2(int a0, int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8,
         int a9, int a10, int a11, int a12, int a13, int a14, int a15) {
  int a[2300] = {sum(1,2,2,3,3,4,5,6), 667 || 10 - 324};
  return a0 + a1 + a2 + a3 + a4 + a5 + a6 + a7 + a8 + a9 + a10 + a11 + a12 +
         a13 + a14 + a15;
}

int e0[2] = {22, 33}, f0[6];
const int g0[9] = {85,  4<<1, 5/43, 6>>2, 7, 8};
const int aa = 7 / 2 + 6 & 1 && (3 >> 1) | 4 + 8 ^ 142; 
int x, y;

int t() {
  x = x + 1;
  return sum(1, x + 2, 3, f0[4], 5, !6, g0[7], 8 / aa);
}

int f() {
  y = y + 1;
  return !t();
}

int main() {
  int ssum = 0;
  int lis[20] = {(f() || f()) & 3, x + y * 2, sum(1, 4 * 2 - f() + t() || 0, 3, f(), 5, 6 ^ 4, f(), 8)};
  x = sum(1, 2, 3, f0[4], sum(1, 2, 3, g0[3], 6, 7, 8 >> 1, 8 ^ 23), !6, 7, 8);
  y = sum2(1, 2, 3, g0[4], 5, 6, 7, x, 9, 10 % 3, 11, 12, sum(1, 2, e0[2], 4, 5, aa + 6, 6, 8), 14, 15, 16);
  for(int j = 1; j<=10; ++j) {
    int a = 1, b = 2;
    {
      ssum = ssum + (f() || f()) & 3 + 6 / aa | 13 * j / sum(1, 4 * 2 - f() + t(), 3, f(), 5, aa + 6, f(), 8);
      f0[j/2] = ssum << 1 /6 + 8 ^ j;
      if (a ==1) {
        for (;a < b;) {
          for(;x < y; x += 2);
          while (a < b || b - 1 == 0) {
            a = a + 1;
            e0[j/2] = a + 1;
            if (a + 3 /5 - aa >=20) break;
          }
          for (int i=1; i<=10;++i){
            ssum = ssum + i ^ 234 >> 2 ;
            if(ssum >=20000) break;
          }
          b = 1;
          a = a + 1;
          if (3) continue;
          a = a - 1;
        }
      } else if (b == 6) {
        break;
      }
      int b = 6;
    //  if (b == 6) return 8 * (10 || b);
    /*  else while (0); */
    }
    putint(f0[j/2]);puts("\n");
  }
  return -1;
}