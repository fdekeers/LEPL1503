#include <time.h>
#include <limits.h>
#include "student_code.h"
#include "solutions/student_code_sol.h"
#include "../../course/common/student/CTester/CTester.h"

int flag = 1;

void test_myfunc_ret() {
	set_test_metadata("q1", _("Test for the function strcasecmp"), 1);

	char* str1 = "fAlSe";
	char* str2 = "trUe";
	char* str3 = "true";
	char* str4 = "false";
	char* str5 = "truestory";
	char* str6 = "falseOrTrue";
	
	int ret1 = 0;
	int ret2 = 0;
	int ret3 = 0;
	int ret4 = 0;
	int ret5 = 0;
	int ret6 = 0;
	int ret7 = 0;


	SANDBOX_BEGIN;
	ret1 = strcasecmp2(str1,str2);
	ret2 = strcasecmp2(str3,str3);
	ret3 = strcasecmp2(str1,str4);
	ret4 = strcasecmp2(str2,str3);
	ret5 = strcasecmp2(str3,str4);
	ret6 = strcasecmp2(str3,str5);
	ret7 = strcasecmp2(str6,str1);
	SANDBOX_END;

	CU_ASSERT(ret1 < 0);
	CU_ASSERT(ret2==0);
	CU_ASSERT(ret3==0);
	CU_ASSERT(ret4==0);
	CU_ASSERT(ret5 > 0);
	CU_ASSERT(ret6 < 0);
	CU_ASSERT(ret7 > 0);

	int flag = 1;

	if (ret1 >= 0){
		flag = 0;
		char *errtpl = _("Your function doesn't work if s1 is before s2");
		char errmsg[strlen(errtpl+30)];
		sprintf(errmsg, errtpl);
		push_info_msg(errmsg);
	}
	if (ret2!=0){
		flag = 0;
		char *errtpl = _("Your function doesn't work if s1 exactly matches s2");
		char errmsg[strlen(errtpl+30)];
		sprintf(errmsg, errtpl);
		push_info_msg(errmsg);
	}
	if (0!=ret3){
		flag = 0;
		char *errtpl = _("Your function doesn't work if s1 matches s2 but the cases of the characters are different");
		char errmsg[strlen(errtpl+30)];
		sprintf(errmsg, errtpl);
		push_info_msg(errmsg);
	}
	if (0!=ret4 && flag){
		flag = 0;
		char *errtpl = _("Your function doesn't work if s1 matches s2 but the cases of the characters are different");
		char errmsg[strlen(errtpl+30)];
		sprintf(errmsg, errtpl);
		push_info_msg(errmsg);
	}
	if (ret5 <= 0){
		flag = 0;
		char *errtpl = _("Your function doesn't work if s1 is after s2");
		char errmsg[strlen(errtpl+30)];
		sprintf(errmsg, errtpl);
		push_info_msg(errmsg);
	}
	if(ret6 >= 0){
		flag = 0;
		char *errtpl = _("Your function doesn't work if s1 is a prefix of s2");
		char errmsg[strlen(errtpl+30)];
		sprintf(errmsg, errtpl);
		push_info_msg(errmsg);
	}
	if(ret7 <= 0){
		flag = 0;
		char *errtpl = _("Your function doesn't work if s2 is a prefix of s1");
		char errmsg[strlen(errtpl+30)];
		sprintf(errmsg, errtpl);
		push_info_msg(errmsg);
	}
	if(flag){
        	set_tag("q1");
	}

}

void test_segfault() {
	set_test_metadata("q1", _("Test if out of bounds"), 1);

	char* str1 = "sinf1252";
    char* str2 = "sinf1252";
    
    int ret = -1;

    char* p = (char*) trap_buffer(sizeof(char)*9,TRAP_RIGHT,PROT_READ,(void*) str2);
    char* q = (char*) trap_buffer(sizeof(char)*9,TRAP_RIGHT,PROT_READ,(void*) str1);
    
    SANDBOX_BEGIN;
    ret = strcasecmp2(q,p);
    SANDBOX_END;
    
    CU_ASSERT(ret == 0);
    
    if(ret != 0){
        flag = 0;
        push_info_msg("Your function doesn't work when s1 and s2 are exactly the same. Don't forget to stop iterating when you encounter the NULL character !");
    }
    
    free_trap(p,sizeof(char)*9);
    free_trap(q,sizeof(char)*9);
}

int main(int argc,char** argv)
{
	BAN_FUNCS(strcasecmp,tolower);
	RUN(test_segfault, test_myfunc_ret);
}

