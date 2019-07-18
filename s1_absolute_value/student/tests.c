#include <stdlib.h>
#include <time.h>
#include "student_code.h"
#include "solutions/student_code_sol.h"
#include "../../course/common/student/CTester/CTester.h"

void test_absval_ret() {
	set_test_metadata("absval", _("test the function absval"), 1);

	srand(time(NULL));
	int i = rand();
	while (!i)
		i = rand();
	int ret1 = 0;
	int ret2 = 0;
	int ret3 = 567;
	
	struct timespec *before = (struct timespec *) malloc(sizeof(struct timespec));
	struct timespec *after =  (struct timespec *) malloc(sizeof(struct timespec));
	time_t sec1 = 0;
	long nano1 = 0;
	time_t secsol = 0;
	long nanosol = 0;
	int clockerr = 0;
	int clockerr2 = 0;
	int clockerr3 = 0;
	int clockerr4 = 0;

	SANDBOX_BEGIN;
	clockerr = clock_gettime(CLOCK_PROCESS_CPUTIME_ID, before);
	ret1 = absval(i);
	ret2 = absval(-i);
	ret3 = absval(0);
	clockerr2 = clock_gettime(CLOCK_PROCESS_CPUTIME_ID, after);
	if (clockerr ==0 && clockerr2 == 0){
		sec1 = after->tv_sec - before->tv_sec;
		nano1 = after->tv_nsec - before->tv_nsec;
	}
	SANDBOX_END;

	
	clockerr3 = clock_gettime(CLOCK_PROCESS_CPUTIME_ID, before);
	int temp = absval_sol(i);
	temp = absval_sol(-i);
	temp = absval_sol(0);
	(void)temp;
	clockerr4 = clock_gettime(CLOCK_PROCESS_CPUTIME_ID, after);
	if (clockerr3 ==0 && clockerr4 == 0){
		secsol = after->tv_sec - before->tv_sec;
		nanosol = after->tv_nsec - before->tv_nsec;
	}

	CU_ASSERT_EQUAL(ret1, i);
	CU_ASSERT_EQUAL(ret2, i);
	CU_ASSERT_EQUAL(ret3, 0);
	if (i!=ret2){
		char *errtpl = _("absval returns the wrong value: you returned %d for %d");
		char errmsg[strlen(errtpl+30)];
		sprintf(errmsg, errtpl, ret2, i);
		push_info_msg(errmsg);
	}
	if (i!=ret1){
		char *errtpl = _("absval returns the wrong value: you returned %d for %d");
		char errmsg[strlen(errtpl+30)];
		sprintf(errmsg, errtpl, ret1, i);
		push_info_msg(errmsg);
	}
	if (0!=ret3){
		char *errtpl = _("absval returns the wrong value: you returned %d for %d");
		char errmsg[strlen(errtpl+30)];
		sprintf(errmsg, errtpl, ret3, 0);
		push_info_msg(errmsg);
	}
	if (i==ret2 && i== ret1 && 0==ret3){
		set_tag("q1");
		if(clockerr==0 && clockerr2==0 && clockerr3==0 && clockerr4==0){
			char *timetpl = _("the test with your implementation took %d sec and %d nsec while our solution took %d sec and %d nsec");
			char timemsg[strlen(timetpl+30)];
			sprintf(timemsg, timetpl, sec1, nano1, secsol, nanosol);
			push_info_msg(timemsg);
		}
	}
	(void)sec1;
	(void)nano1;
	(void)secsol;
	(void)nanosol;
	(void)clockerr;
	(void)clockerr2;
	(void)clockerr3;
	(void)clockerr4;
	if(before !=NULL)
	free(before);
	if(after !=NULL)
	free(after);
}

int main(int argc,char** argv)
{
	BAN_FUNCS();
	RUN(test_absval_ret);
}

