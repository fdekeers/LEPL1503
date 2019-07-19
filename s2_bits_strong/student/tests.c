#include <stdlib.h>
#include "student_code.h"
#include "solutions/student_code_sol.h"
#include "../../course/common/student/CTester/CTester.h"
#include <math.h>
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
void test_myfunc_ret() {
	set_test_metadata("q1", _("Test reset_highestorder_bits"), 1);

	uint32_t binaryNumber = 0b1011011101;
	uint32_t binaryNumberReturned;
	uint32_t binaryNumber2 = 0b00000001;
	uint32_t binaryNumberReturned2;
	uint32_t binaryNumber3 = 0b00000000;
	uint32_t binaryNumberReturned3;

	struct timespec *before = (struct timespec *) malloc(sizeof(struct timespec));
	struct timespec *after =  (struct timespec *) malloc(sizeof(struct timespec));
	time_t sec1 = 0;
	long nano1 = 0;

	SANDBOX_BEGIN;
	int clockerr = clock_gettime(CLOCK_PROCESS_CPUTIME_ID, before);
	binaryNumberReturned = reset_highestorder_bit(binaryNumber);
	binaryNumberReturned2 = reset_highestorder_bit(binaryNumber2);
	binaryNumberReturned3 = reset_highestorder_bit(binaryNumber3);
	int clockerr2 = clock_gettime(CLOCK_PROCESS_CPUTIME_ID, after);
	if (clockerr ==0 && clockerr2 == 0){
		sec1 = after->tv_sec - before->tv_sec;
		nano1 = after->tv_nsec - before->tv_nsec;
	}
	SANDBOX_END;

	time_t secsol = 0;
	long nanosol = 0;
	int clockerr = clock_gettime(CLOCK_PROCESS_CPUTIME_ID, before);
	uint32_t temp = unset_strong_bit_sol(binaryNumber);
	uint32_t temp2 = unset_strong_bit_sol(binaryNumber2);
	uint32_t temp3 = unset_strong_bit_sol(binaryNumber3);
	(void)temp;
	int clockerr2 = clock_gettime(CLOCK_PROCESS_CPUTIME_ID, after);
	if (clockerr ==0 && clockerr2 == 0){
		secsol = after->tv_sec - before->tv_sec;
		nanosol = after->tv_nsec - before->tv_nsec;
	}

	CU_ASSERT_EQUAL(binaryNumberReturned,temp);
	if ( binaryNumberReturned!=temp) {
		char str[] = "azertyuiazertyuiazertyuiazertyui";
		char str2[] = "azertyuiazertyuiazertyuiazertyui";
		int_to_binary(binaryNumberReturned, &str[0]);
		int_to_binary(temp, &str2[0]);
		char *errtpl = _("reset_highestorder_bits does not return the correct value when its input is 0b0...01011011101. Returned : 0b%s. Expected : 0b%s.");
		char errmsg[strlen(errtpl)];
		sprintf(errmsg, errtpl, str, str2);
		push_info_msg(errmsg);
    }

	CU_ASSERT_EQUAL(binaryNumberReturned2,temp2);
	if ( binaryNumberReturned2!=temp2) {
		char str[] = "azertyuiazertyuiazertyuiazertyui";
		char str2[] = "azertyuiazertyuiazertyuiazertyui";
		int_to_binary(binaryNumberReturned, &str[0]);
		int_to_binary(temp3, &str2[0]);
		char *errtpl = _("reset_highestorder_bits does not return the correct value when its input is 0b0...0000001. Returned : 0b%s. Expected : 0b%s.");
		char errmsg[strlen(errtpl)];
		sprintf(errmsg, errtpl, str, str2);
		push_info_msg(errmsg);
    }

	CU_ASSERT_EQUAL(binaryNumberReturned3,temp3);
	if ( binaryNumberReturned3!=temp3) {
		char str[] = "azertyuiazertyuiazertyuiazertyui";
		char str2[] = "azertyuiazertyuiazertyuiazertyui";
		int_to_binary(binaryNumberReturned, &str[0]);
		int_to_binary(temp3, &str2[0]);
		char *errtpl = _("reset_highestorder_bits does not return the correct value when its input is 0b0...0000000. Returned : 0b%s. Expected : 0b%s.");
		char errmsg[strlen(errtpl)];
		sprintf(errmsg, errtpl, str, str2);
		push_info_msg(errmsg);
    }

    if (unset_strong_bit_sol(binaryNumber)==binaryNumberReturned && unset_strong_bit_sol(binaryNumber2)==binaryNumberReturned2 && unset_strong_bit_sol(binaryNumber3)==binaryNumberReturned3){
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

