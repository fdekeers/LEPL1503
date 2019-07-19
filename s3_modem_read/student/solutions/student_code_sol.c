#include<stdio.h>
#include<stdlib.h>
#include "student_code_sol.h"
void modem_read_sol(void* buffer, int* buf_len){
    *buf_len = 64;
}

int has_42_sol() {
    void * buf = malloc(256);
    if (!buf) return -1;
    int a = 0;
    modem_read_sol(buf,&a);
    int i, res;
    int8_t* b = (int8_t*) buf;
    for(i = 0 ; i < a; i ++){
        if(( res = *(b + i)) == 42) {
            free(buf);
            return 1;
        }
    }
    free(buf);
    return 0;
}
