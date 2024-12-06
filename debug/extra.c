int f(int x){
  x = x + 1;
  return x;
}
int main() {
  int a = 10;
  ++a;
  --a;
  puts("hhhhasf");
  putint(++a);
  putint(f(a));
  putint(a++);
  a--;
  +(++a);
  a += 1;
  a -= 1;
  a *= 1;
  a /= 1;
  putint(a);puts("\n");
  a %= 5;
  return a;
}