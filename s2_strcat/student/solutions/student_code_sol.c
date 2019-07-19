#include "student_code_sol.h"
char* strcat_sol(char* dest, const char* src){
	char* tmp = dest;
	while(*dest != '\0'){
	    dest++;
	}
	while(*src != '\0'){
	    *dest = *src;
	    dest++;
	    src++;
	}
	*dest = '\0';
	return tmp;
}


