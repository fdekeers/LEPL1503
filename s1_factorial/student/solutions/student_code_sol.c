#include<stdio.h>
#include<stdlib.h>

int factorialsol(int n)
{
	if (n<=1)
		return 1;
	return n*factorialsol(n-1);
}


