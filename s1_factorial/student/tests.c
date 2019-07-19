#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "student_code.h"
#include "solutions/student_code_sol.h"
#include "../../course/common/student/CTester/CTester.h"

void test_myfunc_ret() {
	set_test_metadata("facto", _("test the function factorial"), 1);

	srand(time(NULL));
	int i = rand()%12;
	while (i<2)
		i= rand()%12;
	int ret1 = 0;
	int ret2 = 0;
	int ret3 = 0;

	struct timespec *before = (struct timespec *) malloc(sizeof(struct timespec));
	struct timespec *after =  (struct timespec *) malloc(sizeof(struct timespec));
	time_t sec1 = 0;
	long nano1 = 0;

	SANDBOX_BEGIN;
	int clockerr = clock_gettime(CLOCK_PROCESS_CPUTIME_ID, before);
	ret1 = factorial(i);
	ret2 = factorial(0);
	ret3 = factorial(1);
	int clockerr2 = clock_gettime(CLOCK_PROCESS_CPUTIME_ID, after);
	if (clockerr ==0 && clockerr2 == 0){
		sec1 = after->tv_sec - before->tv_sec;
		nano1 = after->tv_nsec - before->tv_nsec;
	}
	SANDBOX_END;

	time_t secsol = 0;
	long nanosol = 0;
	int clockerr = clock_gettime(CLOCK_PROCESS_CPUTIME_ID, before);
	int temp = factorialsol(i);
	temp = factorialsol(0);
	temp = factorialsol(1);
	(void)temp;
	int clockerr2 = clock_gettime(CLOCK_PROCESS_CPUTIME_ID, after);
	if (clockerr ==0 && clockerr2 == 0){
		secsol = after->tv_sec - before->tv_sec;
		nanosol = after->tv_nsec - before->tv_nsec;
	}

	int sol = i;
	for(int j = i-1; j>0; j--)
		sol = sol*j;

	CU_ASSERT_EQUAL(ret1, sol);
	CU_ASSERT_EQUAL(ret2, 1);
	CU_ASSERT_EQUAL(ret3, 1);

	if (sol!=ret1){
		char *errtpl = _("factorial returns the wrong value: you returned %d for %d");
		char errmsg[strlen(errtpl+30)];
		sprintf(errmsg, errtpl, ret1, i);
		push_info_msg(errmsg);
	}
	if (1!=ret2){
		char *errtpl = _("factorial returns the wrong value: you returned %d for %d");
		char errmsg[strlen(errtpl+30)];
		sprintf(errmsg, errtpl, ret2, 0);
		push_info_msg(errmsg);
	}
	if (1!=ret3){
		char *errtpl = _("factorial returns the wrong value: you returned %d for %d");
		char errmsg[strlen(errtpl+30)];
		sprintf(errmsg, errtpl, ret2, 1);
		push_info_msg(errmsg);
	}
	if(sol==ret1 && 1==ret2 && 1==ret3){
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

