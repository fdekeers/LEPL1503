#define main main2
#include <stdio.h>
#include "student_code_sol.h"
int main_sol(int argc, char **argv)
{
	if (argc == 1){
		printf("\n");
		return 0;
	}
	printf("%s", *(argv+1));
	for (int i = 3; i<argc; i +=2)
		printf(" %s", *(argv+i));
	printf("\n");
	return 0;
}
