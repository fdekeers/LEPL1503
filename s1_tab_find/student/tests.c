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
    
    int correct = 1;
    for(int i = -5; i < size+5; i++){
        SANDBOX_BEGIN;
        ret = tab_find(tab, size, i);
        SANDBOX_END;
        
        int sol = tab_find_sol(tab,size,i);
        
        if(ret != sol){
	    	correct = 0;
            push_info_msg(_("Your function does not return the correct index."));
            CU_FAIL();
            break;
        }
    }
	
    if(correct == 1){
		set_tag("q1");
    }
}

int main(int argc,char** argv) {
    BAN_FUNCS(system, set_tag);
    RUN(test);
}

