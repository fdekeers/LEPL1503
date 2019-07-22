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

    SANDBOX_BEGIN;
    swap(&i, &j);
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
    }
    
}

int main(int argc,char** argv)
{
    RUN(test_swap);
}

