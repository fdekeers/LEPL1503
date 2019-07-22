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

	SANDBOX_BEGIN;
	leftMostBitsReturned = get_3_leftmost_bits(binaryNumber);
	leftMost2 = get_3_leftmost_bits(binaryNumber2);
	SANDBOX_END;

	uint8_t sol = get_3_leftmost_bits_sol(binaryNumber2);

	CU_ASSERT_EQUAL(leftMostBitsReturned,0b010);
	CU_ASSERT_EQUAL(leftMost2,sol);
	if ( leftMostBitsReturned!=0b010|| leftMost2 != sol){
		char str[] = "azertyui";
		char str2[] = "azertyui";
		char str3[] = "azertyui";
		int_to_binary(leftMostBitsReturned, &str[0]);
		int_to_binary(leftMost2, &str2[0]);
		int_to_binary(sol, &str3[0]);
		char *errtpl = _("get_3_leftmost_bits returns the wrong value. Case 1 : Returned : 0b%s. Expected : 0b00000010. Case 2 : Returned 0b%s. Expected : 0b%s.");
		char errmsg[strlen(errtpl)];
		sprintf(errmsg, errtpl, str, str2, str3);
		push_info_msg(errmsg);
	}
	else{
		set_tag("q1");
	}
}

int main(int argc,char** argv)
{
	BAN_FUNCS();
	RUN(test_get_3_leftmost_bits);
}

