void fun(){
  int a=11;
  if(a>10){
    if(3 < a){
      a+=10;
      return;
      a-=10;
    }
    a+=10;
  }
  return;
}
int main() {
  fun();
  int x = 10, y = 1 + 2;
  y = y + 10;
  x = x + y;
  return x;
}