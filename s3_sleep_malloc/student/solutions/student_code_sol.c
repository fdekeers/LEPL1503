#include "student_code_sol.h"

void * sleep_malloc_sol(size_t s){
    int count = 0;
    void* p = NULL;
    while(!p && count < 10){
        p = malloc(s);
        if(p) return p;
        sleep(5);
        count ++;
    }
    return NULL;
}
