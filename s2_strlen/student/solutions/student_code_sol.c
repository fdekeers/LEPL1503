#include "student_code_sol.h"
size_t strlen_sol(const char* s){
	size_t len = 0;
	while(*s != '\0'){
	    len++;
	    s++;
	}
	return len;
}


