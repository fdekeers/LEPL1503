#include "student_code_sol.h"
int pal_sol(char *str)
{
	if (str==NULL)
		return -1;
	int len = strlen(str);
	if (!len)
		return 1;
	for (char *end = str+len-1; str<end; ){
		if (*str==' ')
			str++;
		else if (*end==' ')
			end --;
		else if (*str!=*end)
			return 0;
		else{
			str++;
			end--;
		}
	}
	return 1;
}
