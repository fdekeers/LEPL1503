#include <stdlib.h>
#include "student_code.h"
#include "solutions/student_code_sol.h"
#include "../../course/common/student/CTester/CTester.h"

void test_myfunc_ret() {
	set_test_metadata("q1", _("Test the function nbits"), 1);
	int ret1 = -1;
	int ret2 = -1;
	int ret3 = -1;
	int ret4 = -1;

	struct timespec *before = (struct timespec *) malloc(sizeof(struct timespec));
	struct timespec *after =  (struct timespec *) malloc(sizeof(struct timespec));
	time_t sec1 = 0;
	long nano1 = 0;
	

	SANDBOX_BEGIN;
	int clockerr = clock_gettime(CLOCK_PROCESS_CPUTIME_ID, before);
	ret1 = nbits(0b1110110100);
	ret2 = nbits(0b0000010000);
	ret3 = nbits(0b1000000000000000);
	ret4 = nbits(0b0000000000000000);
	int clockerr2 = clock_gettime(CLOCK_PROCESS_CPUTIME_ID, after);
	if (clockerr ==0 && clockerr2 == 0){
		sec1 = after->tv_sec - before->tv_sec;
		nano1 = after->tv_nsec - before->tv_nsec;
	}
	SANDBOX_END;

	time_t secsol = 0;
	long nanosol = 0;
	int clockerr = clock_gettime(CLOCK_PROCESS_CPUTIME_ID, before);
	int temp = nbits_sol(0b1110110100);
	temp = nbits_sol(0b0000010000);
	temp = nbits_sol(0b1000000000000000);
	temp = nbits_sol(0b0000000000000000);
	(void)temp;
	int clockerr2 = clock_gettime(CLOCK_PROCESS_CPUTIME_ID, after);
	if (clockerr ==0 && clockerr2 == 0){
		secsol = after->tv_sec - before->tv_sec;
		nanosol = after->tv_nsec - before->tv_nsec;
	}

	CU_ASSERT_EQUAL(6, ret1);
	CU_ASSERT_EQUAL(1, ret2);
	CU_ASSERT_EQUAL(1, ret3);
	CU_ASSERT_EQUAL(0, ret4);
	if ( 6!= ret1) {
		char * errtpl = _("nbits does not return the correct answer when its input is 0b1110110100 : returned %d.");
		char errmsg[strlen(errtpl)];
		sprintf(errmsg, errtpl, ret1);
		push_info_msg(errmsg);
    }
    if ( 1!= ret2 ) {
		char * errtpl = _("nbits does not return the correct answer when its input is 0b0000010000 : returned %d.");
		char errmsg[strlen(errtpl)];
		sprintf(errmsg, errtpl, ret2);
		push_info_msg(errmsg);
    }
    if ( 1!= ret3 ) {
		char * errtpl = _("nbits does not return the correct answer when its input is 0b1000000000000000 : returned %d.");
		char errmsg[strlen(errtpl)];
		sprintf(errmsg, errtpl, ret3);
		push_info_msg(errmsg);
    }
    if ( 0!= ret4) {
		char * errtpl = _("nbits does not return the correct answer when its input is 0b0000000000000000 : returned %d.");
		char errmsg[strlen(errtpl)];
		sprintf(errmsg, errtpl, ret4);
		push_info_msg(errmsg);
    }

    if (6==ret1 && 1==ret2 && 1==ret3 && 0==ret4){
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

