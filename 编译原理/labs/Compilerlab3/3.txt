void myprint(int a, int b, int c) {
  println_int(a);
  println_int(b);
  println_int(c);
}

int main() {
  int a = 1, b = 2;
  int c = a + b;
  myprint(a, b, c);
  return 0;
}
