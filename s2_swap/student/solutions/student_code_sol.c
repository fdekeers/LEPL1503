#include "student_code_sol.h"
void swap_sol(struct fract_t* a, struct fract_t* b){
	struct fract_t tmp = *b;
	*b = *a;
	*a = tmp;
}


