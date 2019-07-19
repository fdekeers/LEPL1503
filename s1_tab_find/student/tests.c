// CTester template

#include <stdlib.h>
#include "student_code.h"
#include "solutions/student_code_sol.h"
#include "../../course/common/student/CTester/CTester.h"

void test(){
    set_test_metadata("tab_find", _("Test function tab find"), 1);    

    const int size = 10;
    int array[10] = {1,3,5,7,9,0,8,6,4,2};
    int *tab = trap_buffer(size*sizeof(int), TRAP_RIGHT, PROT_WRITE, array);
    int ret = 0;
    
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
    int correct = 1;
    for(int i = -5; i < size+5; i++){
        SANDBOX_BEGIN;
	if(i==-5 && before !=NULL && after != NULL){
		clockerr = clock_gettime(CLOCK_PROCESS_CPUTIME_ID, before);
	}
        ret = tab_find(tab, size, i);
	if(i==-5  && before !=NULL && after != NULL){
		clockerr2 = clock_gettime(CLOCK_PROCESS_CPUTIME_ID, after);
		if (clockerr ==0 && clockerr2 == 0){
			sec1 = after->tv_sec - before->tv_sec;
			nano1 = after->tv_nsec - before->tv_nsec;
		}
	}
        SANDBOX_END;
        
	if(i==-5 && before !=NULL && after != NULL){
		clockerr3 = clock_gettime(CLOCK_PROCESS_CPUTIME_ID, before);
	}
	int sol = tab_find_sol(tab, size, i);
	if(i==-5 && before !=NULL && after != NULL){
		clockerr4 = clock_gettime(CLOCK_PROCESS_CPUTIME_ID, after);
		if (clockerr3 ==0 && clockerr4 == 0){
			secsol = after->tv_sec - before->tv_sec;
			nanosol = after->tv_nsec - before->tv_nsec;
		}
	}
        if(ret != sol){
	    correct = 0;
            push_info_msg(_("Your function does not return the correct index."));
            CU_FAIL();
            break;
        }

    }
	
    if(correct == 1){
	set_tag("q1");
	if(before !=NULL && after != NULL && clockerr==0 && clockerr2==0 && clockerr3==0 && clockerr4==0){
	    char *timetpl = _("The test with your implementation took %d sec and %d nsec while our solution took %d sec and %d nsec.");
	    char timemsg[strlen(timetpl+30)];
	    sprintf(timemsg, timetpl, sec1, nano1, secsol, nanosol);
	    push_info_msg(timemsg);
	}

    }
    
    (void) sec1;
    (void) nano1;
    (void) secsol;
    (void) nanosol;
    (void) clockerr;
    (void) clockerr2;
    (void) clockerr3;
    (void) clockerr4;
    free_trap(tab,size*sizeof(int));
    free(before);
    free(after);
}

int main(int argc,char** argv) {
    BAN_FUNCS(system, set_tag);
    RUN(test);
}

