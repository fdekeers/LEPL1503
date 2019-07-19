// CTester template

#include <stdlib.h>
#include "student_code.h"
#include "../../course/common/student/CTester/CTester.h"

int flag = 1;
void test_exist_not() {
    set_test_metadata("q1", _("Test file does not exist"), 1);

    // We run multiples times the test to avoid student returning randomly 1 or 0.
    for(int i = 0; i < 4; i++){
        int ret = 0;

        system("rm file.txt");
        SANDBOX_BEGIN;
        ret = file_exists("file.txt");
        SANDBOX_END;
    
        if(ret != -1){
	    flag = 0;
            CU_FAIL();
            push_info_msg(_("When the file does not exist, you do not return -1"));
            return;
        }
    }
}

void test_exist() {
    set_test_metadata("q1", _("Test file exists"), 1);
        int stop = 0;
    // We run multiples times the test to avoid student returning randomly 1 or 0.
    for(int i = 0; i < 4 && stop == 0; i++){
        int ret = 0;
	stop = 0;
        system("touch file.txt");
        monitored.close = true;
        monitored.open = true;
        SANDBOX_BEGIN;
        ret = file_exists("file.txt");
        SANDBOX_END;
        monitored.close = false;
        monitored.open = false;
    
        if(ret != 0){
	    	flag = 0;
            CU_FAIL();
            stop++;
            push_info_msg(_("When the file exist, you do not return 0"));
            if(!strcasecmp("filename",stats.open.last_params.pathname)){
                push_info_msg(_("filename is a variable that contains the path to your file in a string while \"filename\" is a string containing the word \"filename\" ! You have to use the variable as argument to open to specify where open can find your file in your file system."));
            }
        }
        
        char* err = "%d";
        char errmsg[strlen(err)];
        sprintf(errmsg,err,stats.open.last_return);
        push_info_msg(errmsg);
        
        if ((stats.open.called > 0 && stats.close.called == 0) || stats.close.last_params.fd != stats.open.last_return){
	    flag = 0;
            stop++;
            push_info_msg(_("You did not close() the file when the file exists or you passed the wrong file descriptor to close()"));
            CU_FAIL();
        }
    }

    if (flag ) {
	set_tag("q1");
    }
}

int main(int argc,char** argv){
    BAN_FUNCS(system, fopen, fread, fwrite, fclose, stat);
    RUN(test_exist_not, test_exist);
}
