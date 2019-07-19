#include <time.h>
#include "student_code.h"
#include "solutions/student_code_sol.h"
#include "../../course/common/student/CTester/CTester.h"

void test_myfunc_ret() {
	set_test_metadata("q1", _("Test for the function strcat"), 1);

	char str1[10];
	char str2[10];
	char str3[10];
	strcpy(str1,"bar");
	strcpy(str2,"bar");
	strcpy(str3,"");
	
	char* str4 = "man";
	char* str5 = "";

	char* ret1;
	char* ret2;
	char* ret3;

	SANDBOX_BEGIN;
	ret1 = strcat2(str1,str4);
	ret2 = strcat2(str2,str5);
	ret3 = strcat2(str3,str4);
	SANDBOX_END;

	CU_ASSERT_STRING_EQUAL(ret1, "barman");
	CU_ASSERT_STRING_EQUAL(ret2, "bar");
	CU_ASSERT_STRING_EQUAL(ret3, "man");

	CU_ASSERT_PTR_EQUAL(ret1,str1);
	CU_ASSERT_PTR_EQUAL(ret2,str2);
	CU_ASSERT_PTR_EQUAL(ret3,str3);

	int flag = 1;
	if(strcmp(ret1,"barman")){
		flag = 0;
		char *errtpl = _("Your function doesn't work for two basic strings");
		char errmsg[strlen(errtpl+30)];
		sprintf(errmsg, errtpl);
		push_info_msg(errmsg);
	}
	if (strcmp(ret2,"bar")){
		flag = 0;
		char *errtpl = _("Your function doesn't work if the src string is an empty string");
		char errmsg[strlen(errtpl+30)];
		sprintf(errmsg, errtpl);
		push_info_msg(errmsg);
	}
	if (strcmp(ret3,"man")){
		flag = 0;
		char *errtpl = _("Your function doesn't work if the dest string is an empty string");
		char errmsg[strlen(errtpl+30)];
		sprintf(errmsg, errtpl);
		push_info_msg(errmsg);
	}
	if(ret1!=str1 || ret2!=str2 || ret3!=str3){
		flag = 0;
		char *errtpl = _("You do not return the correct pointer");
		char errmsg[strlen(errtpl+30)];
		sprintf(errmsg, errtpl);
		push_info_msg(errmsg);
	}
	if(flag){
		set_tag("q1");
	}
}

int main(int argc,char** argv)
{
	BAN_FUNCS(strcat);
	RUN(test_myfunc_ret);
}

