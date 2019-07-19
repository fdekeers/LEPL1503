#include <stdlib.h>
#include <stdio.h>
#include "student_code_sol.h"

int first_sol(void* ptr){
    int *p = (int *)ptr;
    p = p+3;

    return *p;
}

char second_sol(void* ptr){
    char *p = (char *)ptr;
    p = p+6;

    return *p;
}

int third_sol(void* ptr){
    char *p = (char *)ptr;
    p = p+45;

    return *(int *)p;
}
