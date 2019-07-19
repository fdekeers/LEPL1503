#include "student_code_sol.h"
/*
 * @str: the string to be counted
 * @length: the length of the string, length > 0
 * @return: the number of occuence of '\0'
 *         -1 in case of error
 */
int counting_zero_sol(char* str, int length){
	if(str==NULL){
		return -1;
	}
    int count = 0;    
    int i;
    for(i = 0; i < length; i++){
        if(str[i] == '\0')
            count++;
    }    
    return count;
}