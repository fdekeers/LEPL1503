#include "module_a.h"

char* str_a = "Bonjour";
static char* str_b = "Salut";

static void func_a() {
  printf("%s\n", str_b);
}

void func_b() {
  func_a();
}

static void func_c() {
  printf("Ciao");
}
