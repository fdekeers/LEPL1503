#include "student_code_sol.h"
int strcasecmp_sol(const char *s1, const char *s2){
	int i;
	char c1;
	char c2;
	for(i = 0; s1[i]!='\0' && s2[i]!='\0'; i++){
	    c1 = s1[i];
	    c2 = s2[i];
	    if(c1>=65 && c1<=90){
	        c1 += 32;
	    }
	    if(c2>=65 && c2<=90){
	        c2 += 32;
	    }
	    if(c1!=c2){
	        return c1-c2;
	    }
	}
	if(s1[i]=='\0' && s2[i]=='\0'){
	    return 0;
	}
	else if(s1[i]=='\0'){
	    return -1;
	}
	else{
	    return 1;
	}
}


