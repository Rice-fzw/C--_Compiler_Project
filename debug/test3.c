int 
main() 
{
  const int c = 20;
  putint(c);puts("\n");
  int a = 1, 
    b = 100, sum = 0;
  while ((a = a + 2) < ++b) sum++;
  putint(sum);puts("\n");
}