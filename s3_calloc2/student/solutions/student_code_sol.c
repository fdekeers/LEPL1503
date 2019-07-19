#include "student_code_sol.h"

void* calloc2_sol(size_t nmemb, size_t size){
	char* memory = (char*) malloc(size*nmemb);
	if(memory==NULL){
		return NULL;
	}
	char* tmp = memory;
	int i;
	for(i = 0; i < size*nmemb; i++){
	    *(tmp+i) = '\0';
	}
	return memory;
}