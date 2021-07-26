#include <stdlib.h>
#include <stdio.h>
#include "module.h"

extern int a;

int main(int argc, char const *argv[]) {
  printf("%d\n", func_e());

  return EXIT_SUCCESS;
}