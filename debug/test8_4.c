int a = 10;

int inc() {
  a = a + 1;
  return a;
}

void print_a() {
  putint(a);
  putch(10);
  putch("sdaas");
  putch("asd");
}

int main() {
  int i = 0;
  while (i < 10) {
    inc();
    int a = 1;
    a = a + 2;
    putint(a);
    putch(10);
    print_a();
    i = i + 1;
  }
  return 0;
}