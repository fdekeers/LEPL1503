#include <stdlib.h>
#include "student_code.h"
#include "solutions/student_code_sol.h"
#include "../../course/common/student/CTester/CTester.h"
#include <math.h>
#include <string.h>
void int_to_binary(uint32_t d, char *p){
	uint32_t h = pow(2,31);
	while(h>=1){
		if(d>=h){
			*p = '1';
			d = d-h;
		}
		else {
			*p = '0';
		}
		h = h/2;
		p++;
	}
}
void test_myfunc_ret()
{
	set_test_metadata("q1", _("Test the function cycle_bits"), 1);

	uint32_t binaryNumber = 0b10110110101010001101111111111111;
	uint32_t binaryNumberReturned = 0;
	uint32_t ret2 = 0;

	struct timespec *before = (struct timespec *) malloc(sizeof(struct timespec));
	struct timespec *after =  (struct timespec *) malloc(sizeof(struct timespec));
	time_t sec1 = 0;
	long nano1 = 0;

	SANDBOX_BEGIN;
	int clockerr = clock_gettime(CLOCK_PROCESS_CPUTIME_ID, before);
	binaryNumberReturned = cycle_bits(binaryNumber,6);
	ret2 = cycle_bits(binaryNumber,38);
	int clockerr2 = clock_gettime(CLOCK_PROCESS_CPUTIME_ID, after);
	if (clockerr ==0 && clockerr2 == 0){
		sec1 = after->tv_sec - before->tv_sec;
		nano1 = after->tv_nsec - before->tv_nsec;
	}
	SANDBOX_END;

	time_t secsol = 0;
	long nanosol = 0;
	int clockerr = clock_gettime(CLOCK_PROCESS_CPUTIME_ID, before);
	int temp = cycle_bits_sol(binaryNumber,6);
	temp = cycle_bits_sol(binaryNumber,38);
	(void)temp;
	int clockerr2 = clock_gettime(CLOCK_PROCESS_CPUTIME_ID, after);
	if (clockerr ==0 && clockerr2 == 0){
		secsol = after->tv_sec - before->tv_sec;
		nanosol = after->tv_nsec - before->tv_nsec;
	}

	CU_ASSERT_EQUAL(binaryNumberReturned,0b10101010001101111111111111101101);
	CU_ASSERT_EQUAL(ret2,0b10101010001101111111111111101101);
	if ( binaryNumberReturned!=0b10101010001101111111111111101101) {
		char str[] = "azertyuiazertyuiazertyuiazertyui";
		int_to_binary(binaryNumberReturned, &str[0]);
		char *errtpl = _("cycle_bits returns the wrong value. Returned : 0b%s. Expected : 0b10101010001101111111111111101101. and %d");
		char errmsg[strlen(errtpl)];
		sprintf(errmsg, errtpl, str, binaryNumberReturned);
		push_info_msg(errmsg);
	}
	if ( ret2!=0b10101010001101111111111111101101){
		char str[] = "azertyuiazertyuiazertyuiazertyui";
		int_to_binary(ret2, &str[0]);
char *errtpl = _("cycle_bits returns the wrong value for n>32. Returned : 0b%s. Expected : 0b10101010001101111111111111101101.");
		char errmsg[strlen(errtpl)];
		sprintf(errmsg, errtpl, str);
		push_info_msg(errmsg);
	}
	if (0b10101010001101111111111111101101==ret2 && binaryNumberReturned==0b10101010001101111111111111101101){
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

