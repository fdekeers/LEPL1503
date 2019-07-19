// CTester template

#include <stdlib.h>
#include "student_code.h"
#include "solutions/student_code_sol.h"
#include "../../course/common/student/CTester/CTester.h"

void test_myfunc_ret()
{
	set_test_metadata("q1", _("Test the function palindrome"), 1);

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

	struct timespec *before = (struct timespec *) malloc(sizeof(struct timespec));
	struct timespec *after =  (struct timespec *) malloc(sizeof(struct timespec));
	time_t sec1 = 0;
	long nano1 = 0;
	int flag = 1;

	SANDBOX_BEGIN;
	int clockerr = clock_gettime(CLOCK_PROCESS_CPUTIME_ID, before);
	ret1 = pal(str1);
	ret2 = pal(str2);
	ret3 = pal(str3);
	ret4 = pal(str4);
	ret5 = pal(str5);
	ret6 = pal(NULL);
	ret7 = pal(str6);
	ret8 = pal(str7);
	int clockerr2 = clock_gettime(CLOCK_PROCESS_CPUTIME_ID, after);
	if (clockerr ==0 && clockerr2 == 0){
		sec1 = after->tv_sec - before->tv_sec;
		nano1 = after->tv_nsec - before->tv_nsec;
	}
	SANDBOX_END;

	time_t secsol = 0;
	long nanosol = 0;
	int clockerr = clock_gettime(CLOCK_PROCESS_CPUTIME_ID, before);
	int temp;/* = pal_sol(str1);
	temp = pal_sol(str2);
	temp = pal_sol(str3);
	temp = pal_sol(str4);
	temp = pal_sol(str5);
	temp = pal_sol(NULL);
	temp = pal_sol(str6);
	temp = pal_sol(str7);*/
	(void)temp;
	int clockerr2 = clock_gettime(CLOCK_PROCESS_CPUTIME_ID, after);
	if (clockerr ==0 && clockerr2 == 0){
		secsol = after->tv_sec - before->tv_sec;
		nanosol = after->tv_nsec - before->tv_nsec;
	}

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
	if (ret2!=1) {
		flag = 0;
		push_info_msg(_("Your function does not work correctly for strings that are palindromes and contain spaces (remember to first remove spaces from your string) "));
    }
    if (ret1!=0 || ret4!=0 || ret8!=0){
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

	if(flag){
		set_tag("q1");
		char *timetpl = _("the test with your implementation took %d sec and %d nsec while our solution took %d sec and %d nsec");
		char timemsg[strlen(timetpl+30)];
		sprintf(timemsg, timetpl, sec1, nano1, secsol, nanosol);
		push_info_msg(timemsg);
	}

	free(before);
	free(after);
}

int main(int argc,char** argv)
{
	BAN_FUNCS();
	RUN(test_myfunc_ret);
}

