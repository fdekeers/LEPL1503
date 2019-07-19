#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "student_code.h"
#include "solutions/student_code_sol.h"
#include "../../course/common/student/CTester/CTester.h"

void test_swap()
{
    	set_test_metadata("q1", _("Tests whether swap correctly exchanges the contents of the variables"), 1);
        struct fract_t f1;
        struct fract_t f2;
        int f1num, f1denum, f2num, f2denum;

        srandom(time(NULL));

        f1num = random();
        f1denum = random();
        f2num = random();
        f2denum = random();

        f1.num = f1num;
        f1.denum = f1denum;
        f2.num = f2num;
        f2.denum = f2denum;

	SANDBOX_BEGIN;
        swap(&f1, &f2);
	SANDBOX_END;

	CU_ASSERT_EQUAL(f1.num,f2num);
	CU_ASSERT_EQUAL(f1.denum,f2denum);
	CU_ASSERT_EQUAL(f2.num,f1num);
	CU_ASSERT_EQUAL(f2.denum,f1denum);

	if(f1.num!= f2num || f1.denum!= f2denum ||f2.num!= f1num ||f2.denum!= f1denum ){
		char *errtpl = _("Your fonction did not correctly exchange the content of the variables. Reality : a->num = %d, a->denum = %d, b->num = %d, b->den = %d. Expected : a->num = %d, a->denum = %d, b->num = %d, b->den = %d.");
		char errmsg[strlen(errtpl)];
		sprintf(errmsg, errtpl, f1.num, f1.denum, f2.num, f2.denum, f2num, f2denum, f1num, f1denum);
		push_info_msg(errmsg);
	}
	else {
		set_tag("q1");
	}

}

int main(int argc,char** argv)
{
    RUN(test_swap);
}
