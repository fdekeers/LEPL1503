#include "module_b.h"

static char* str_a = "Coucou";
char* str_b = "Hello";

static void func_b() {
  static int a = 0;
  int b = 0;
  printf("%s (a = %d; b = %d)\n", str_a, a, b);
  a++;
  b++;
}

void func_c() {
  func_b();
}
