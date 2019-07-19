// CTester template

#include <stdlib.h>
#include "student_code.h"
//#include "solutions/student_code_sol.h"
#include "../../course/common/student/CTester/CTester.h"

void test_swap() {
    set_test_metadata("q1", _("Tests whether swap correctly exchanges the contents of the variables"), 1);
    int i = rand();
    int j = rand();
    while (i==j)//to make sure i!=j
	    j = rand();
    int i_orig = i;
    int j_orig = j;

    struct timespec *before = (struct timespec *) malloc(sizeof(struct timespec));
    struct timespec *after =  (struct timespec *) malloc(sizeof(struct timespec));
    time_t sec1 = 0;
    long nano1 = 0;
    time_t secsol = 0;
    long nanosol = 0;
    int clockerr = 0;
    int clockerr2 = 0;
    int clockerr3 = 0;
    int clockerr4 = 0;

    SANDBOX_BEGIN;
    if(before !=NULL && after !=NULL){
	clockerr = clock_gettime(CLOCK_PROCESS_CPUTIME_ID, before);
    }
    swap(&i, &j);
    if(before !=NULL && after !=NULL){
	clockerr2 = clock_gettime(CLOCK_PROCESS_CPUTIME_ID, after);
	if (clockerr ==0 && clockerr2 == 0){
	sec1 = after->tv_sec - before->tv_sec;
	nano1 = after->tv_nsec - before->tv_nsec;
	}
    }
    SANDBOX_END;

    CU_ASSERT_EQUAL(i,j_orig);
    CU_ASSERT_EQUAL(j,i_orig);
    if (i!=j_orig || j!=i_orig){
        char* err = _("Your fonction did not correctly exchange the content of the variables : * i was %d and * j was %d, after your call * i is %d and * j is %d");
        char errmsg[strlen(err)];
        sprintf(errmsg,err,i_orig,j_orig,i,j);
	    push_info_msg(errmsg);
    }

    else{ 
	set_tag("q1");
	/*if (before !=NULL && after !=NULL){
		clockerr3 = clock_gettime(CLOCK_PROCESS_CPUTIME_ID, before);
		swap_sol(&i, &j);
		clockerr4 = clock_gettime(CLOCK_PROCESS_CPUTIME_ID, after);
		if (clockerr ==0 && clockerr2 == 0 && clockerr3 ==0 && clockerr4 == 0){
			secsol = after->tv_sec - before->tv_sec;
			nanosol = after->tv_nsec - before->tv_nsec;
			char *timetpl = _("the test with your implementation took %d sec and %d nsec while our solution took %d sec and %d nsec");
			char timemsg[strlen(timetpl+30)];
			sprintf(timemsg, timetpl, sec1, nano1, secsol, nanosol);
			push_info_msg(timemsg);
		}
	}*/

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
    RUN(test_swap);
}

