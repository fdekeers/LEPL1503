#include <stdlib.h>
#include <stdio.h>
#include "module_a.h"
#include "module_b.h"

extern char* str_a;
extern char* str_b;

void func_a() {
  printf("%s\n", str_a);
  printf("%s\n", str_b);
  func_c();
}

int main(int argc, char const *argv[]) {
  func_a();
  func_b();
  func_c();
  return EXIT_SUCCESS;
}
