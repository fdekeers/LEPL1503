#include "student_code.h"
#include "solutions/student_code_sol.h"
#include "../../course/common/student/CTester/CTester.h"
#include <math.h>
void int_to_binary(uint8_t d, char *p){
	int h = pow(2,7);
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
void test_get_3_leftmost_bits(void)
{
	set_test_metadata("q1", _("Test of function test_get_3_leftmost_bits"), 1);
	uint32_t binaryNumber = 0b01000000000010101111011101101111;
	uint32_t binaryNumber2 = random();
	uint8_t leftMostBitsReturned = 0;
	uint8_t leftMost2 = 0;

	struct timespec *before = (struct timespec *) malloc(sizeof(struct timespec));
	struct timespec *after =  (struct timespec *) malloc(sizeof(struct timespec));
	time_t sec1 = 0;
	long nano1 = 0;

	SANDBOX_BEGIN;
	int clockerr = clock_gettime(CLOCK_PROCESS_CPUTIME_ID, before);
	leftMostBitsReturned = get_3_leftmost_bits(binaryNumber);
	leftMost2 = get_3_leftmost_bits(binaryNumber2);
	int clockerr2 = clock_gettime(CLOCK_PROCESS_CPUTIME_ID, after);
	if (clockerr ==0 && clockerr2 == 0){
		sec1 = after->tv_sec - before->tv_sec;
		nano1 = after->tv_nsec - before->tv_nsec;
	}
	SANDBOX_END;

	time_t secsol = 0;
	long nanosol = 0;
	int clockerr = clock_gettime(CLOCK_PROCESS_CPUTIME_ID, before);
	uint8_t temp;/* = get_3_leftmost_bits_sol(binaryNumber);
	temp = get_3_leftmost_bits_sol(binaryNumber2);*/
	(void)temp;
	int clockerr2 = clock_gettime(CLOCK_PROCESS_CPUTIME_ID, after);
	if (clockerr ==0 && clockerr2 == 0){
		secsol = after->tv_sec - before->tv_sec;
		nanosol = after->tv_nsec - before->tv_nsec;
	}

	CU_ASSERT_EQUAL(leftMostBitsReturned,0b010);
	CU_ASSERT_EQUAL(leftMost2,temp);
	if ( leftMostBitsReturned!=0b010|| leftMost2 != temp){
		char str[] = "azertyui";
		char str2[] = "azertyui";
		char str3[] = "azertyui";
		int_to_binary(leftMostBitsReturned, &str[0]);
		int_to_binary(leftMost2, &str2[0]);
		int_to_binary(temp, &str3[0]);
		char *errtpl = _("get_3_leftmost_bits returns the wrong value. Case 1 : Returned : 0b%s. Expected : 0b00000010. Case 2 : Returned 0b%s. Expected : 0b%s.");
		char errmsg[strlen(errtpl)];
		sprintf(errmsg, errtpl, str, str2, str3);
		push_info_msg(errmsg);
	}
	else{
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
	RUN(test_get_3_leftmost_bits);
}

