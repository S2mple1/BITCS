int opplus(int a, int b) { return a + b; }
int opminus(int a, int b) { return a - b; }
int opmul(int a, int b) { return a * b; }
int opdiv(int a, int b) { return a / b; }
int opmod(int a, int b) { return a % b; }
int opand(int a, int b) { return a & b; }
int opor(int a, int b) { return a | b; }
int opxor(int a, int b) { return a ^ b; }
int opplus_114514(int _0, int arg, int _1, int _2) {
  int l_0 = _0, l_1 = _1, l_2 = _2;
  return arg + 114514;
}

int main() {
  int literal1, literal2, vminus, vmul, vadd, vdiv, vmod, vand, vor, vxor;

  literal1 = 114;
  literal2 = 514;
  vadd = opplus(literal1, literal2);
  vminus = opminus(literal1, literal2);
  vmul = opmul(literal1, literal2);
  vdiv = opdiv(literal1, literal2);
  vmod = opmod(literal1, literal2);
  vand = opand(literal1, literal2);
  vor = opor(literal1, literal2);
  vxor = opxor(literal1, literal2);

  int var;
  var = opplus_114514(1, 2, 3, 4);

  println_int(literal1);
  println_int(literal2);
  println_int(vadd);
  println_int(vminus);
  println_int(vmul);
  println_int(vdiv);
  println_int(vmod);
  println_int(vand);
  println_int(vor);
  println_int(vxor);
  println_int(var);

  return 0;
}
