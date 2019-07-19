// CTester template

#include <stdlib.h>
#include <sys/mman.h>
#include "student_code.h"
#include "../../course/common/student/CTester/CTester.h"

int ret = -20;

/*
 * Generate a file named "file.txt".
 * The content is the integers in range [0, n[
 * The sum of integers in the file is returned.
 */
int gen_file(int n){
    int fd = open("file.txt",O_WRONLY|O_CREAT|O_TRUNC, S_IRUSR|S_IWUSR);
    if(fd == -1) {
        CU_FAIL(_("Error, can not initialise test file"));
    }
    int array[n];
    int i = 0;
    int sum = 0;
    for (i = 0; i < n; i++){
        array[i]=i;
        sum+=i;
        if (write(fd, (void *) &array[i], sizeof(int)) == -1){
            CU_FAIL(_("Error, can not initialise test file"));
        }
    }
    if (close(fd) == -1)
        CU_FAIL(_("Error, can not initialise test file"));
    return sum;
}
int flag = 1;
void test_open_fail() {
    set_test_metadata("q1", _("Return -1 when open fails"), 1);
    system("rm file.txt"); //Be sure the file does not exist
    int ret = 0;
    
    //Test with open fail
    monitored.open = true;
    failures.open = FAIL_ALWAYS;
    failures.open_ret = -1;
    
    SANDBOX_BEGIN;
    ret = myfunc("file.txt");
    SANDBOX_END;

    if (ret != -1){ 
	flag = 0;
	set_tag("failure_handling");
        char *errtpl = _("When open() fails, your code does not return -1 but returns %d.");
        char errmsg[strlen(errtpl)];
        sprintf(errmsg, errtpl, ret);
        push_info_msg(errmsg);
        CU_FAIL("");
    }
}
   
void test_count() {
    set_test_metadata("q1", _("Calling open and close"), 1);
    gen_file(13);
    monitored.open = true;
    monitored.close = true;

    SANDBOX_BEGIN;
    ret = myfunc("file.txt");
    SANDBOX_END;
    
    if(stats.open.last_return <= 2){
		flag = 0;
        char *errtpl = _("You didn't call open correctly. For information, your function returned %d.");
        char errmsg[strlen(errtpl)];
        sprintf(errmsg, errtpl, ret);
        push_info_msg(errmsg);
        CU_FAIL("");
        if(!strcasecmp("filename",stats.open.last_params.pathname)){
                push_info_msg(_("filename is a variable that contains the path to your file in a string while \"filename\" is a string containing the word \"filename\" ! You have to use the variable as argument to open to specify where open can find your file in your file system."));
            }
    }
    
    if (stats.open.called != 1) {
	flag = 0;
        char *errtpl = _("Your number of calls to open is not 1. For information, your function returned %d.");
        char errmsg[strlen(errtpl)];
        sprintf(errmsg, errtpl, ret);
        push_info_msg(errmsg);
        CU_FAIL("");
    }
    if (stats.close.called != 1) {
	flag = 0;
        char *errtpl = _("Your number of calls to close is not 1. For information, your function returned %d.");
        char errmsg[strlen(errtpl)];
        sprintf(errmsg, errtpl, ret);
        push_info_msg(errmsg);
        CU_FAIL("");
    }
}

void test_no_integer() {
    set_test_metadata("q1", _("Test without any integers."), 1);
    int sum = gen_file(0); //Empty file
    
    SANDBOX_BEGIN;
    ret = myfunc("file.txt");
    SANDBOX_END;
    
    if (ret != sum){
	flag = 0;
        CU_FAIL("");
        char *errtpl = _("When the file does not contain any integers, your code does not return 0 but returns %d.");
        char errmsg[strlen(errtpl)];
        sprintf(errmsg, errtpl, ret);
        push_info_msg(errmsg);
    }
}

void test_some_integers() {
    set_test_metadata("q1", _("Test with some integers."), 1);
    int sum = gen_file(300);
    
    SANDBOX_BEGIN;
    ret = myfunc("file.txt");
    SANDBOX_END;
    
    if (ret != sum){
	flag = 0;
        char *errtpl = _("When the file contains some integers, your code does not return the correct sum but returns %d.");
        char errmsg[strlen(errtpl)];
        sprintf(errmsg, errtpl, ret);
        push_info_msg(errmsg);
        CU_FAIL("");
    }
}

void test_some_integers_fail_fstat() {
    set_test_metadata("q1", _("Test when fstat() fails"), 1);
    gen_file(9);
    
    monitored.fstat = true;
    failures.fstat = FAIL_FIRST;
    failures.fstat_ret = -1;
    
    SANDBOX_BEGIN;
    ret = myfunc("file.txt");
    SANDBOX_END;
    
    if (ret != -5){
	flag = 0;
        char *errtpl = _("When fstat() fails, your code does not return -5 but returns %d.");
        char errmsg[strlen(errtpl)];
        sprintf(errmsg, errtpl, ret);
        push_info_msg(errmsg);
        set_tag("failure_handling");
        CU_FAIL();
    }
}

void test_some_integers_fail_mmap() {
    set_test_metadata("q1", _("Test when mmap() fails"), 1);
    gen_file(9);
    
    monitored.mmap = true;
    failures.mmap = FAIL_FIRST;
    failures.mmap_ret = MAP_FAILED;
    
    SANDBOX_BEGIN;
    ret = myfunc("file.txt");
    SANDBOX_END;
    
    if (ret != -3){
	flag = 0;
        char *errtpl = _("When mmap() fails, your code does not return -3 but returns %d.");
        char errmsg[strlen(errtpl)];
        sprintf(errmsg, errtpl, ret);
        push_info_msg(errmsg);
        set_tag("failure_handling");
        CU_FAIL();
    }
}

void test_some_integers_fail_munmap() {
    set_test_metadata("q1", _("Test when munmap() fails"), 1);
    gen_file(9);
    
    monitored.munmap = true;
    failures.munmap = FAIL_FIRST;
    failures.munmap_ret = -1;
    
    SANDBOX_BEGIN;
    ret = myfunc("file.txt");
    SANDBOX_END;
    
    if (ret != -4){
	flag = 0;
        char *errtpl = _("When munmap() fails, your code does not return -4 but returns %d.");
        char errmsg[strlen(errtpl)];
        sprintf(errmsg, errtpl, ret);
        push_info_msg(errmsg);
        set_tag("failure_handling");
        CU_FAIL();
    }
}

void test_close() {
    set_test_metadata("q1", _("Test close()"), 1);
    gen_file(0);
    
    monitored.close = true;
    monitored.open = true;
    SANDBOX_BEGIN;
    ret = myfunc("file.txt");
    SANDBOX_END;
    
    if (stats.close.called == 0){
	flag = 0;
        char *errtpl = _("You did not close() the file. For info, your function returned %d.");
        char errmsg[strlen(errtpl)];
        sprintf(errmsg, errtpl, ret);
        push_info_msg(errmsg);
        CU_FAIL();
    }
    if(stats.open.last_return != stats.close.last_params.fd){
	flag = 0;
        char *errtpl = _("The close() does not close the file you opened before. For info, your function returned %d.");
        char errmsg[strlen(errtpl)];
        sprintf(errmsg, errtpl, ret);
        push_info_msg(errmsg);
        CU_FAIL();
    }
    
    //We fail the close()
    gen_file(2);
    int ret = 0;
    monitored.close = true;
    failures.close = FAIL_FIRST;
    failures.close_ret = -1;
    SANDBOX_BEGIN;
    ret = myfunc("file.txt");
    SANDBOX_END;
    
    if(ret != -2){
	flag = 0;
        char *errtpl = _("When close() fails, your code does not return -2 but returns %d.");
        char errmsg[strlen(errtpl)];
        sprintf(errmsg, errtpl, ret);
        push_info_msg(errmsg);
	set_tag("failure_handling");
        CU_FAIL(); 
    }
    if(flag){
        set_tag("q1");
    }
}

int main(int argc,char** argv){
    BAN_FUNCS(system, fopen, fread, fwrite, fclose, read, write);
    RUN(test_count, test_open_fail, test_no_integer, test_some_integers, test_some_integers_fail_mmap, test_close, test_some_integers_fail_munmap, test_some_integers_fail_fstat);
}

