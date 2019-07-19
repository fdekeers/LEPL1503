#include "student_code_sol.h"
char *buf_strcpy_sol(const char *src){
  int len = strlen(src) + 1, i;
  char * ret = (char*) malloc(sizeof(char)*len);
  if (!ret)
    return NULL;

  for(i = 0; i < len; i++)
    *(ret+i) = *(src+i);

  return ret;
}
