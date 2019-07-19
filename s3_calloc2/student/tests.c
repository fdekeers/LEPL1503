#include <stdlib.h>
#include <time.h>
#include "student_code.h"
#include "../../course/common/student/CTester/CTester.h"

int flag = 1;
void test_calloc2_1() {
	set_test_metadata("calloc2", _("Allocated memory : test calloc2"), 1);
	void* ret = NULL;

	    monitored.malloc = true;
	    failures.malloc = FAIL_NEVER;

	    size_t  start = stats.memory.used;

	    SANDBOX_BEGIN;
	    ret = calloc2(16,4);
	    if (ret == NULL) {
		    flag = 0;
		    CU_FAIL("Erreur lors l'allocation de la mémoire.");
		    return;
	    }
	    SANDBOX_END;

	    size_t used_size = stats.memory.used - start;

	    CU_ASSERT_EQUAL(used_size, 16*4);
	    if (used_size != 16*4){
		flag = 0;
		set_tag("wrong_alloc_size");	
		push_info_msg(_("You allocated more memory than required."));
	    }

	    CU_ASSERT_PTR_NOT_NULL(ret);
		
	    CU_ASSERT_TRUE(malloced(ret));
	    if(!malloced(ret) || ret == NULL){
		flag = 0;
	    }
	    CU_ASSERT_EQUAL(stats.malloc.called,1)
	    if(stats.malloc.called != 1){
		flag = 0;
		set_tag("not_malloc_once");
		push_info_msg(_("Why didn't you call malloc exactly once?"));
	    }
    

    free(ret);
}
void test_calloc2_2(void) {
	set_test_metadata("calloc2", _("Initialised memory : test calloc2"), 1);
   	 void *ptr;
	SANDBOX_BEGIN;
	ptr = calloc2(42, 1);
	if (ptr == NULL) {
		flag = 0;
		CU_FAIL("Erreur lors l'allocation de la mémoire.");
		return;
	}
	SANDBOX_END;
    CU_ASSERT_EQUAL(*(char*)(ptr+10), 0);
    if(*(char*)(ptr+10)!=0){
	flag = 0;
	push_info_msg(_("You didn't initialise the allocated memory."));
    }
    free(ptr);
}
void test_calloc2_3() {
	set_test_metadata("calloc2", _("Fail of malloc : test calloc2"), 1);
	monitored.malloc = true;
	failures.malloc = FAIL_ALWAYS;
	failures.malloc_ret = NULL;

	void *ptr = NULL;
	SANDBOX_BEGIN;
	ptr = calloc2(42,42);
	SANDBOX_END;
	CU_ASSERT_PTR_NULL(ptr);
	if (ptr != NULL){
		flag = 0;
		set_tag("malloc_fail_handling");
		push_info_msg(_("Don't forget that malloc can fail sometimes."));
	}
	if (flag){
		set_tag("q1");
	}
	free(ptr);
}
int main(int argc,char** argv)
{

	BAN_FUNCS();
	RUN(test_calloc2_1,test_calloc2_2,test_calloc2_3);
}

