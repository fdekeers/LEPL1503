#include <time.h>
#include <string.h>
#include "student_code.h"
#include "solutions/student_code_sol.h"
#include "../../course/common/student/CTester/CTester.h"

void test_myfunc_ret() {
	set_test_metadata("q1", _("Test for the function strlen"), 1);

	char* str1 = "foo";
	char* str2 = "";
	char* str3 = "I love C code";
	
	size_t ret1 = 0;
	size_t ret2 = 0;
	size_t ret3 = 0;

	struct timespec *before = (struct timespec *) malloc(sizeof(struct timespec));
	struct timespec *after =  (struct timespec *) malloc(sizeof(struct timespec));
	time_t sec1 = 0;
	long nano1 = 0;

	SANDBOX_BEGIN;
	int clockerr = clock_gettime(CLOCK_PROCESS_CPUTIME_ID, before);
	ret1 = strlen2(str1);
	ret2 = strlen2(str2);
	ret3 = strlen2(str3);
	int clockerr2 = clock_gettime(CLOCK_PROCESS_CPUTIME_ID, after);
	if (clockerr ==0 && clockerr2 == 0){
		sec1 = after->tv_sec - before->tv_sec;
		nano1 = after->tv_nsec - before->tv_nsec;
	}
	SANDBOX_END;

	time_t secsol = 0;
	long nanosol = 0;
	int clockerr = clock_gettime(CLOCK_PROCESS_CPUTIME_ID, before);
	int temp = strlen_sol(str1);
	temp = strlen_sol(str2);
	temp = strlen_sol(str3);
	(void)temp;
	int clockerr2 = clock_gettime(CLOCK_PROCESS_CPUTIME_ID, after);
	if (clockerr ==0 && clockerr2 == 0){
		secsol = after->tv_sec - before->tv_sec;
		nanosol = after->tv_nsec - before->tv_nsec;
	}

	CU_ASSERT_EQUAL(ret1, 3);
	CU_ASSERT_EQUAL(ret2, 0);
	CU_ASSERT_EQUAL(ret3, 13);

	if (3!=ret1){
		char *errtpl = _("Your function doesn't work for the string \"%s\", it should return 3 but you returned %d");
		char errmsg[strlen(errtpl+30)];
		sprintf(errmsg, errtpl, str1, ret1);
		push_info_msg(errmsg);
	}
	if (0!=ret2){
		char *errtpl = _("Your function doesn't work for an empty string, it should return 0 but you returned %d");
		char errmsg[strlen(errtpl+30)];
		sprintf(errmsg, errtpl, ret2);
		push_info_msg(errmsg);
	}
	if (13!=ret3){
		char *errtpl = _("Your function doesn't work for a string with spaces, don't forget that spaces count as characters");
		char errmsg[strlen(errtpl+30)];
		sprintf(errmsg, errtpl);
		push_info_msg(errmsg);
	}
	if(3==ret1 && 0==ret2 && 13==ret3){
		set_tag("q1");
		char *timetpl = _("The test with your implementation took %d sec and %d nsec while our solution took %d sec and %d nsec");
		char timemsg[strlen(timetpl+30)];
		sprintf(timemsg, timetpl, sec1, nano1, secsol, nanosol);
		push_info_msg(timemsg);
	}

	free(before);
	free(after);
	(void)nanosol;
	(void)secsol;
	(void)nano1;
	(void)sec1;
}

int main(int argc,char** argv)
{
	BAN_FUNCS(strlen);
	RUN(test_myfunc_ret);
}

