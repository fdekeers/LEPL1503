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

	SANDBOX_BEGIN;
	ret1 = strlen2(str1);
	ret2 = strlen2(str2);
	ret3 = strlen2(str3);
	SANDBOX_END;


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
	}

}

int main(int argc,char** argv)
{
	BAN_FUNCS(strlen);
	RUN(test_myfunc_ret);
}

