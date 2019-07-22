// CTester template

#include <stdlib.h>
#include "student_code.h"
#include "solutions/student_code_sol.h"
#include "../../course/common/student/CTester/CTester.h"

int flag = 1;

char* create_long_palindrome(){
    char* alphabet = "abcdefghijklmnopqrstuvwxyz  zyxwvutsrqponmlkjihgfedcba";
    char* str = (char*) malloc(strlen(alphabet)*1000000 + 1000001);
    if(str==NULL){
    	return NULL;        
    }
    char* curr = str;

    for(int i = 0; i < 1000000; i++){
        memcpy(curr,alphabet,strlen(alphabet));
        curr += strlen(alphabet);
        memcpy(curr," ",1);
        curr += 1;
    }
    memcpy(curr,"",1);
    
    return str;
}

void test_myfunc_ret()
{
	set_test_metadata("q1", _("Test the function palindrome"), 9);

	int ret1 = -2;
	int ret2 = -2;
	int ret3 = -2;
	int ret4 = -2;
	int ret5 = -2;
	int ret6 = -2;
	int ret7 = -2;
	int ret8 = -2;

	char *s1="Tityre tu patulae recubans sub tegmine fagi";
	char *s2="tu l as trop ecrase cesar ce port salut";
	char *s3="";
	char *s4="azertyuioppptpoiuytreza";
	char *s5="qsdfghjklmmlkjhgfdsq";
	char *s6="e";
	char *s7="k     oyak";

    
	char *str1 = trap_buffer(strlen(s1)+1, TRAP_RIGHT, PROT_WRITE, s1);
	char *str2 = trap_buffer(strlen(s2)+1, TRAP_RIGHT, PROT_WRITE, s2);
	char *str3 = trap_buffer(strlen(s3)+1, TRAP_RIGHT, PROT_WRITE, s3);
	char *str4 = trap_buffer(strlen(s4)+1, TRAP_RIGHT, PROT_WRITE, s4);
	char *str5 = trap_buffer(strlen(s5)+1, TRAP_RIGHT, PROT_WRITE, s5);
	char *str6 = trap_buffer(strlen(s6)+1, TRAP_RIGHT, PROT_WRITE, s6);
	char *str7 = trap_buffer(strlen(s7)+1, TRAP_RIGHT, PROT_WRITE, s7);

	SANDBOX_BEGIN;
	ret1 = pal(str1);
	ret2 = pal(str2);
	ret3 = pal(str3);
	ret4 = pal(str4);
	ret5 = pal(str5);
	ret6 = pal(NULL);
	ret7 = pal(str6);
	ret8 = pal(str7);
	SANDBOX_END;

	free_trap(str1,44);
	free_trap(str2,40);
	free_trap(str3,1);
	free_trap(str4,25);
	free_trap(str5,22);
	free_trap(str6,2);
	free_trap(str7,11);
	CU_ASSERT_EQUAL(ret1,0);
	CU_ASSERT_EQUAL(ret2,1);
	CU_ASSERT_EQUAL(ret3,1);
	CU_ASSERT_EQUAL(ret4,0);
	CU_ASSERT_EQUAL(ret5,1);
	CU_ASSERT_EQUAL(ret6,-1);
	CU_ASSERT_EQUAL(ret7,1);
	CU_ASSERT_EQUAL(ret8,0);
    CU_ASSERT_STRING_EQUAL(str1,s1);
	if (ret2!=1) {
		flag = 0;
		push_info_msg(_("Your function does not work correctly for strings that are palindromes and contain spaces (remember to first remove spaces from your string) "));
    }
    if(ret8!=0){
       flag = 0;
	   push_info_msg(_("Your function does not work correctly for strings that are not palindromes and contain spaces (remember to first remove spaces from your string) "));
    }
    if (ret1!=0 || ret4!=0){
    	flag = 0;
		push_info_msg(_("Your function does not work correctly for strings that are not palindromes"));
	}

	if ( ret3!=1 || ret5!=1 || ret7!=1){
		flag = 0;
		push_info_msg(_("Your function doesn't work for strings that are palindromes"));
	}

	if (ret6!=-1){
		flag = 0;
		push_info_msg(_("Your function doesn't work for NULL strings"));
	}
    if(strcmp(str1,s1)){
        flag = 0;
        push_info_msg(_("You can't modify the initial string"));
    }
}

void test_CPU(){
    set_test_metadata("q1", _("Test the function palindrome with CPU time"), 1);
    
    struct timespec before;
	struct timespec after;    
    
   char* str = create_long_palindrome();
   if(str==NULL){
        CU_FAIL("Can't initialise memory for the long palindrome");
        push_info_msg(_("The test can't be initialised, please contact your tutor or an administrator."));
        return;
    } 
    
	time_t sec = 0;
	long nano = 0;
    int clockerr;
    int clockerr2;
    int ret;
    
    SANDBOX_BEGIN;
    clockerr = clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &before);
    ret = pal(str);
	clockerr2 = clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &after);
    SANDBOX_END;
    
	if (clockerr == 0 && clockerr2 == 0){
		sec = after.tv_sec - before.tv_sec;
		nano = after.tv_nsec - before.tv_nsec;
	}
    else{
        CU_FAIL("Can't get time used for the CPU_test");
        push_info_msg(_("The test encountered an error, please contact your tutor or an administrator."));
        free(str);
        return;
    }    
    float studtime = ((float) nano)/1000000000 + (float) sec;
    
	clockerr = clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &before);
	int sol = pal_sol(str);
	clockerr2 = clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &after);
    
    free(str);
    
	if (clockerr == 0 && clockerr2 == 0){
		sec = after.tv_sec - before.tv_sec;
		nano = after.tv_nsec - before.tv_nsec;
	}
    else{
        CU_FAIL("Can't get time used for the CPU_test");
        push_info_msg(_("The test encountered an error, please contact your tutor or an administrator."));
        return;
    }
    
    float soltime = ((float) nano)/1000000000 + (float) sec;
    
    if(sol!=ret){
        CU_FAIL();
        push_info_msg(_("Your function doesn't work for a really long palindrome"));
        flag = 0;
    }
    else{
        FILE* file = fopen("cpu.txt", "w+");
        if(file==NULL){
            CU_FAIL("Can't open cpu.txt");
        	push_info_msg(_("The test encountered an error, please contact your tutor or an administrator."));
        	flag = 0;
            return;
        }
        int check = fprintf(file,"%2.6f\n",studtime);
        if(check <= 0){
            CU_FAIL("Can't write to cpu.txt");
        	push_info_msg(_("The test encountered an error, please contact your tutor or an administrator."));
        	flag = 0;
            fclose(file);
            return;
        }
        check = fclose(file);
        if(check==EOF){
            CU_FAIL("Can't close cpu.txt");
        	push_info_msg(_("The test encountered an error, please contact your tutor or an administrator."));
        	flag = 0;
            return;
        }
        
        if(studtime > 2*soltime){
            CU_FAIL();
            flag = 0;
            char* str = _("Your solution seems to take a lot of time compared to our solution. Maybe you should think about a better way to solve the problem because it is really important to save as much CPU time as you can when you write programs. Your solution took %2.6f sec while our solution took %2.6f sec.");
            char strmsg[strlen(str)+30];
            sprintf(strmsg,str,studtime,soltime);
            push_info_msg(strmsg);
        }
        
        CU_PASS();
    }
    
    if(flag){
		set_tag("q1");
	}
}

int main(int argc,char** argv)
{
	BAN_FUNCS();
	RUN(test_myfunc_ret, test_CPU);
}

