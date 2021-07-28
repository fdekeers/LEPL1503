#include "module.h"

int a = 0;
static int b = 1;

int func_c() {
  int c = 2;
  return c;
}

int func_d() {
  static int d = 3;
  return d;
}

static int func_e() {
  int e = 4;
  return e;
}

int func_f() {
  int f = 5;
  return f;
}
