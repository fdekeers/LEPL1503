#include <stdlib.h>
#include <unistd.h>
#include <strings.h>
#include "student_code.h"
#include "solutions/student_code_sol.h"
#include "../../course/common/student/CTester/CTester.h"

void test_myfunc_ret()
{
    set_test_metadata("q1", _("Test the task main_argc"), 1);

    int ret1 = 1;
    int ret2 = 1;
    int ret3 = 1;
    int ret4 = 1;
    int ret5 = 1;

    char *str1 ="tests";
    char *str2 ="a";
    char *str3 ="b";
    char *str4 ="ihuqfiudshfsi";
    char *str5 ="kujsvglqiu";
    char *argv1[5] = {str1, str2, str3, str4, str5};
    char *argv2[4] = {str1, str2, str3, str5};
    char *argv3[1] = {str1};
    char *argv4[3] = {str1, str2, str3};
    char *argv5[2] = {str1, str5};
    char buf[16];

    struct timespec *before = (struct timespec *) malloc(sizeof(struct timespec));
    struct timespec *after =  (struct timespec *) malloc(sizeof(struct timespec));
    time_t sec1 = 0;
    long nano1 = 0;
    time_t secsol = 0;
    long nanosol = 0;
    int clockerr;
    int clockerr2;
    int clockerr3;
    int clockerr4;
    int flag = 1;

    SANDBOX_BEGIN;
    clockerr = clock_gettime(CLOCK_PROCESS_CPUTIME_ID, before);
    ret1 = main2(5, argv1);
    clockerr2 = clock_gettime(CLOCK_PROCESS_CPUTIME_ID, after);
    if (clockerr ==0 && clockerr2 == 0){
        sec1 = after->tv_sec - before->tv_sec;
        nano1 = after->tv_nsec - before->tv_nsec;
    }
    SANDBOX_END;

    read(stdout_cpy, buf, 16);
    if (!strncmp("a ihuqfiudshfsi ", buf, 16)) {
        flag = 0;
        CU_FAIL("");
        push_info_msg(_("Your function output the wrong string when 5 arguments are provided. Be sure not to have a space after the last argument"));
    }
    else if (strncmp("a ihuqfiudshfsi\n", buf, 16)){
        flag = 0;
        CU_FAIL("");
        char* err = "Arguments : '%s %s %s %s %s', expected : 'a ihuqfiudshfsi\\\\n', your answer : '%s'";
        char error_msg[200];
        sprintf(error_msg, err, str1, str2, str3, str4, str5, buf);
        push_info_msg(error_msg);
        if(!strncmp(buf,"tests",5)){
            push_info_msg(_("Don't forget that the first argument (index 0) is the name of the program ! myProg in this case !"));
        }
    }
    else
        CU_PASS("");

    clockerr3 = clock_gettime(CLOCK_PROCESS_CPUTIME_ID, before);
    int temp;
    //int temp = main_sol(5, argv1);
    clockerr4 = clock_gettime(CLOCK_PROCESS_CPUTIME_ID, after);
    if (clockerr3 ==0 && clockerr4 == 0){
        secsol = after->tv_sec - before->tv_sec;
        nanosol = after->tv_nsec - before->tv_nsec;
    }
    (void)temp;

    SANDBOX_BEGIN;
    ret2 = main2(4, argv2);
    SANDBOX_END;

    read(stdout_cpy, buf, 13);
    if (!strncmp("a kujsvglqiu ", buf, 13)) {
        flag = 0;
        CU_FAIL("");
        push_info_msg(_("Your function output the wrong string when 3 arguments are provided. Be sure not to have a space after the last argument"));
    }
    else if (strncmp("a kujsvglqiu\n", buf, 13)){
        flag = 0;
        CU_FAIL("");
        char error_msg[200];
        sprintf(error_msg, _("Arguments : '%s %s %s %s', expected : 'a kujsvglqiu\\\\n', your answer : '%s'"), str1, str2, str3, str5, buf);
        push_info_msg(error_msg);
        if(!strncmp(buf,"tests",5)){
            push_info_msg(_("Don't forget that the first argument (index 0) is the name of the program ! myProg in this case !"));
        }
    }
    else
        CU_PASS("");

    SANDBOX_BEGIN;
    ret3 = main2(1, argv3);
    SANDBOX_END;
    read(stdout_cpy, buf, 1);
    if (strncmp("\n", buf, 1)){
        CU_FAIL("");
        char error_msg[200];
        sprintf(error_msg, _("Arguments : '%s', expected : '\\\\n', your answer : '%s'"), str1, buf);
        push_info_msg(error_msg);
    }
    else
        CU_PASS("");

    SANDBOX_BEGIN;
    ret4 = main2(3, argv4);
    SANDBOX_END;

    read(stdout_cpy, buf, 2);
    if (!strncmp("a ", buf, 2)) {
        flag = 0;
        CU_FAIL("");
        push_info_msg(_("Your function output the wrong string when 2 arguments are provided. Be sure not to have a space after the last argument"));
    }
    else if (strncmp("a\n", buf, 2)){
        flag = 0;
        CU_FAIL("");
        char error_msg[200];
        sprintf(error_msg, _("Arguments : '%s %s %s', expected : 'a\\\\n', your answer : '%s'"), str1, str2, str3, buf);
        push_info_msg(error_msg);
        if(!strncmp(buf,"tests",5)){
            push_info_msg(_("Don't forget that the first argument (index 0) is the name of the program ! myProg in this case !"));
        }
    }
    else
        CU_PASS("");

    SANDBOX_BEGIN;
    ret5 = main2(2, argv5);
    SANDBOX_END;

    read(stdout_cpy, buf, 11);
    if (!strncmp("kujsvglqiu ", buf, 11)) {
        flag = 0;
        CU_FAIL("");
        push_info_msg(_("Your function output the wrong string when 1 arguments are provided. Be sure not to have a space after the last argument"));
    }
    if (strncmp("kujsvglqiu\n", buf, 11)){
        flag = 0;
        CU_FAIL("");
        char error_msg[200];
        sprintf(error_msg, _("Arguments : '%s %s', expected : 'kujsvglqiu\\\\n', your answer : '%s'"), str1, str5, buf);
        push_info_msg(error_msg);
        if(!strncmp(buf,"tests",5)){
            push_info_msg(_("Don't forget that the first argument (index 0) is the name of the program ! myProg in this case !"));
        }
    }
    else
        CU_PASS("");

    CU_ASSERT_EQUAL(ret1,0);
    CU_ASSERT_EQUAL(ret2,0);
    CU_ASSERT_EQUAL(ret3,0);
    CU_ASSERT_EQUAL(ret4,0);
    CU_ASSERT_EQUAL(ret5,0);
    if (ret1||ret2||ret3||ret4||ret5){
        flag = 0;
        push_info_msg(_("Your function didn't return 0"));
    }

    if (flag){
	set_tag("q1");
	if(clockerr==0 && clockerr2==0 && clockerr3==0 && clockerr4==0){
		char *timetpl = _("the test with your implementation took %d sec and %d nsec while our solution took %d sec and %d nsec");
		char timemsg[strlen(timetpl+30)];
		sprintf(timemsg, timetpl, sec1, nano1, secsol, nanosol);
		push_info_msg(timemsg);
	}
    }
    (void)sec1;
    (void)nano1;
    (void)secsol;
    (void)nanosol;
    (void)clockerr;
    (void)clockerr2;
    (void)clockerr3;
    (void)clockerr4;
    if(before !=NULL)
    free(before);
    if(after !=NULL)
    free(after);
}

int main(int argc,char** argv)
{
    BAN_FUNCS();
    RUN(test_myfunc_ret);
}







