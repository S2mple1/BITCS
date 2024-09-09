
void print3(int a, int b, int c) {
  println_int(a);
  println_int(b);
  println_int(c);
}
void print4(int a, int b, int c, int d) {
  println_int(a);
  println_int(b);
  println_int(c);
  println_int(d);
}

int main() {
  int a=114,b=-114,c=514,d=-514;
  print4(a,b,c,d);
  print4(-a,-b,-c,-d);
  print4(~a,~b,~c,~d);
  a=1;
  b=0;
  c=-1;
  print3(a,b,c);
  print3(-a,-b,-c);
  print3(~a,~b,~c);

  return 0;
}
