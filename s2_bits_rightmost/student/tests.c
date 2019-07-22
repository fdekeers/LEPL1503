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
void test_get_4_rightmost_bits(void)
{
	set_test_metadata("q1", _("Test the function get_4_rightmost_bits"), 1);

	uint32_t binaryNumberA = 0b0111010110110101010001011;
    uint32_t binaryNumberB = 0b0111010110110101010001110;
	uint32_t binaryNumberC = 0b0111010110110101010011001;


	uint8_t rightMostBitsReturnedA;
	uint8_t rightMostBitsReturnedB;
	uint8_t rightMostBitsReturnedC;


	SANDBOX_BEGIN;
	rightMostBitsReturnedA = get_4_rightmost_bits(binaryNumberA);
	rightMostBitsReturnedB = get_4_rightmost_bits(binaryNumberB);
	rightMostBitsReturnedC = get_4_rightmost_bits(binaryNumberC);
	SANDBOX_END;
    
	CU_ASSERT_EQUAL(rightMostBitsReturnedA,0b1011);
	CU_ASSERT_EQUAL(rightMostBitsReturnedB,0b1110);
	CU_ASSERT_EQUAL(rightMostBitsReturnedC,0b1001);
	if (rightMostBitsReturnedC==0b1001 && rightMostBitsReturnedB==0b1110 && rightMostBitsReturnedA==0b1011){
		set_tag("q1");
	}
	else{
		char str[] = "azertyui";
		char str2[] = "azertyui";
		char str3[] = "azertyui";
		int_to_binary(rightMostBitsReturnedA, &str[0]);
		int_to_binary(rightMostBitsReturnedB, &str2[0]);
		int_to_binary(rightMostBitsReturnedC, &str3[0]);
		char *errtpl = _("get_3_leftmost_bits returns the wrong value. Case 1 : Returned : 0b%s. Expected : 0b00001011. Case 2 : Returned 0b%s. Expected : 0b00001110. Case 3 : Returned 0b%s. Expected : 0b00001001.");
		char errmsg[strlen(errtpl)];
		sprintf(errmsg, errtpl, str, str2, str3);
		push_info_msg(errmsg);
	}
}

int main(int argc,char** argv)
{
	BAN_FUNCS(set_tag);
	RUN(test_get_4_rightmost_bits);
}
