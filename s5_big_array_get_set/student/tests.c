// CTester template
#include "student_code.h"
#include "../../course/common/student/CTester/CTester.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <errno.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/uio.h>

#include <fcntl.h>

int get_value_by_index(int i){
    return (i*i*(i/2))%20000;
}

/*
 * Generate a file named "file.txt".
 * The content is n int following the formula defined above.
 */
void gen_file(int n){
    int fd = open("file.txt",O_WRONLY|O_CREAT|O_TRUNC, S_IRUSR|S_IWUSR);
    if(fd == -1) {
        CU_FAIL("Error, can not initialise test file");
    }
    int array[n];
    int i = 0;
    for (i = 0; i < n; i++){
        array[i] = get_value_by_index(i);
        if (write(fd, (void *) &array[i], sizeof(int)) == -1){
            CU_FAIL("Error, can not initialise test file");
        }
    }
    if (close(fd) == -1)
        CU_FAIL("Error, can not initialise test file");
}

int flag_get = 1;
void test_get() {
    set_test_metadata("q1", _("Test with normal file"), 2);
    gen_file(1000);
    
    system("cp file.txt file_copy.txt");
    
    int should_count_mmap = 0;
    monitored.mmap = true; 
    monitored.open = true; 
    monitored.close = true;
    monitored.munmap = true; 
    monitored.fstat = true; 
    for(int i = 0; i < 1000; i+=50){
        should_count_mmap++;
        int ret = 0;
        int err = 0;
        
        stats.open.called = 0;
        stats.close.called = 0;
        stats.fstat.called = 0;
        SANDBOX_BEGIN;
        ret = get("file.txt", i);
        SANDBOX_END;
        
        if(ret != get_value_by_index(i)){
	    flag_get = 0;
            push_info_msg(_("You do not return the correct value."));
            CU_FAIL(); 
            err++;
        }   
        
        if (stats.open.called != 1) {
	    flag_get = 0;
            push_info_msg(_("The number of calls to open() isn't 1."));
            CU_FAIL(); 
            err++;
        }
        if (stats.close.called != 1) {
	    flag_get = 0;
            push_info_msg(_("The number of calls to close() isn't 1."));
            CU_FAIL(); 
            err++;
        }
        if (stats.fstat.called < 1) {
	    flag_get = 0;
            push_info_msg(_("fstat() should at least be called once."));
            CU_FAIL(); 
            err++;
        }
        
        if (err)
            return;
    }
    if(stats.mmap.called > should_count_mmap){
	flag_get = 0;
        push_info_msg(_("You perform too many mmap()."));
        CU_FAIL();  
    }
    if(stats.munmap.called != stats.mmap.called){
	flag_get = 0;
	push_info_msg(_("Don't forget to munmap."));
	CU_FAIL();
    }
    
    if(system("diff file.txt file_copy.txt") != 0){
	flag_get = 0;
        push_info_msg(_("You have modified the file when reading it..."));
        CU_FAIL();
    }
}

int flag_set = 1;

void test_set() {
    set_test_metadata("q2", _("Test with normal file"), 2);
    gen_file(1000);
   
    int should_count_mmap = 0;
    monitored.mmap = true; 
    monitored.open = true; 
    monitored.close = true;
    monitored.munmap = true; 
    monitored.fstat = true; 
    for(int i = 0; i < 1000; i+=50){ 
        should_count_mmap++;
        SANDBOX_BEGIN;
        set("file.txt", i, 2222+i);
        SANDBOX_END;  
    }
    
    if(stats.mmap.called > should_count_mmap){
	flag_set = 0;
        push_info_msg(_("You perform too many mmap()."));
        CU_FAIL();  
    }
    
    int fd = open("file.txt", O_RDONLY);
    if(fd == -1) {
	flag_set = 0;
        CU_FAIL("Error, can not initialise test file");
    }
    for(int i = 0; i < 1000; i+=50){
        lseek(fd, (off_t) i*sizeof(int), SEEK_SET);
        int res;
        read(fd, (void *) &res, sizeof(int));
       if (res != 2222+i){
	    flag_set = 0;
            push_info_msg(_("You do not set the correct values in the file."));
            CU_FAIL();
            break;
        }
    }
    for(int i = 0; i < 1000; i++){
        if (i % 50 != 0){

        	lseek(fd, (off_t) i*sizeof(int), SEEK_SET);
        	int res;
        	read(fd, (void *) &res, sizeof(int));
        	if (res != get_value_by_index(i)){
	        flag_set =0;
            	push_info_msg(_("You have modified some wrong elements in the array"));
            	CU_FAIL();
                break;
        	}
        }
    }
    close(fd);
}


void test_close_q1(){
    set_test_metadata("q1", _("Test close"), 1);
    monitored.close = true;
    monitored.open = true;
    SANDBOX_BEGIN;
    get("file.txt", 0);
    SANDBOX_END;
    if (stats.close.called != 1){
	flag_get = 0;
        push_info_msg(_("You did not close the file."));
        CU_FAIL();
    }
    if(stats.close.last_params.fd != stats.open.last_return){
        flag_get = 0;
        push_info_msg(_("You did not close the correct file descriptor. You have to close the file you opened."));
        CU_FAIL();
    }
    
    failures.close = FAIL_FIRST;
    failures.close_ret = -1;
    int ret = 0;
    gen_file(10);
    SANDBOX_BEGIN;
    ret = get("file.txt",2);
    SANDBOX_END;
    
    if(ret!=-1){
        flag_get = 0;
        push_info_msg(_("You do not return -1 when close() fails."));
        set_tag("failure_handling");
        CU_FAIL();
    }
    monitored.close = false;
    monitored.open = false;
}

void test_open_q2_fail(){
    set_test_metadata("q2", _("Test open fails"), 1);
    monitored.open = true;
    failures.open=FAIL_FIRST;
    failures.open_ret = -1;   
    gen_file(10);
    SANDBOX_BEGIN;
    set("file.txt", 0, 100);
    SANDBOX_END;
    monitored.open = false;
    
    int fd = open("file.txt",O_RDONLY);
    if(fd==-1){
        flag_set = 0;
        CU_FAIL("Error, can not initialise test file");
    }
    int check;
    read(fd,&check,sizeof(int));
    close(fd);
    
    if(check==100){
        flag_set = 0;
        push_info_msg(_("You modify the file when open() fails, this should not happen."));
        CU_FAIL();
        set_tag("failure_handling");
    }
}

void test_mmap_q2_fail(){
    set_test_metadata("q2", _("Test mmap fails"), 1);
    monitored.mmap = true;
    failures.mmap=FAIL_FIRST;
    failures.mmap_ret = MAP_FAILED;   
    gen_file(10);
    SANDBOX_BEGIN;
    set("file.txt", 0, 100);
    SANDBOX_END;
    monitored.mmap = false;
    
    int fd = open("file.txt",O_RDONLY);
    if(fd==-1){
        flag_set = 0;
        CU_FAIL("Error, can not initialise test file");
    }
    int check;
    read(fd,&check,sizeof(int));
    close(fd);
    
    if(check==100){
        flag_set = 0;
        push_info_msg(_("You modify the file when mmap() fails, this should not happen."));
        CU_FAIL();
        set_tag("failure_handling");
    }
}

void test_fstat_q2_fail(){
    set_test_metadata("q2", _("Test fstat fails"), 1);
    monitored.fstat = true;
    failures.fstat=FAIL_FIRST;
    failures.fstat_ret = -1;   
    gen_file(10);
    SANDBOX_BEGIN;
    set("file.txt", 0, 100);
    SANDBOX_END;
    monitored.fstat = false;
    
    int fd = open("file.txt",O_RDONLY);
    if(fd==-1){
        flag_set = 0;
        CU_FAIL("Error, can not initialise test file");
    }
    int check;
    read(fd,&check,sizeof(int));
    close(fd);
    
    if(check==100){
        flag_set = 0;
        push_info_msg(_("You modify the file when fstat() fails, this should not happen."));
        CU_FAIL();
        set_tag("failure_handling");
    }
}


void test_close_q2(){
    set_test_metadata("q2", _("Test close"), 1);
    monitored.close = true;   
    monitored.open = true;
    SANDBOX_BEGIN;
    set("file.txt", 0,0);
    SANDBOX_END;
    if (stats.close.called != 1){
	flag_set = 0;
        push_info_msg(_("You did not close the file."));
        CU_FAIL();
    }
    if(stats.close.last_params.fd != stats.open.last_return){
        flag_set = 0;
        push_info_msg(_("You did not close the correct file descriptor. You have to close the file you opened."));
        CU_FAIL();
    }
    
    monitored.close = false;
    monitored.open = false;
    
    if(flag_set){
	set_tag("q2");
    }
}

void test_get_oob() {
    set_test_metadata("q1", _("Test get out of bound"), 1);
    gen_file(10);    
    int ret = 0;
        
    SANDBOX_BEGIN;
    ret = get("file.txt", 200);
    SANDBOX_END;
        
    if(ret != -2){
	flag_get = 0;
        push_info_msg(_("You do not return -2 when index is bigger than the size of the array."));
        CU_FAIL(); 
    }   
}

void test_mmap_q1_fail() {
    set_test_metadata("q1", _("Test mmap fails"), 1);
    gen_file(100);    
    int ret = 0;
    
    monitored.mmap = true;
    failures.mmap=FAIL_FIRST;
    failures.mmap_ret = MAP_FAILED;
    SANDBOX_BEGIN;
    ret = get("file.txt", 50);
    SANDBOX_END;
    if(ret != -1){
	flag_get = 0;
        push_info_msg(_("You do not return -1 when the mmap() function fails."));
        CU_FAIL(); 
        set_tag("failure_handling");
    }   
}

void test_open_q1_fail(){
    set_test_metadata("q1", _("Test open fails"), 1);
    monitored.open = true;
    failures.open=FAIL_FIRST;
    failures.open_ret = -1;   
    int ret = 0;
    SANDBOX_BEGIN;
    ret = get("file_no_exits.txt", 3);
    SANDBOX_END;
    
    if (ret != -1){
	flag_get = 0;
        push_info_msg(_("You do not return -1 when open() fails."));
        CU_FAIL();
        set_tag("failure_handling");
    }
}

void test_fstat_q1_fail(){
    set_test_metadata("q1", _("Test fstat fails"), 1);
    monitored.fstat = true;
    failures.fstat=FAIL_FIRST;
    failures.fstat_ret = -1;   
    int ret = 0;
    gen_file(10);
    SANDBOX_BEGIN;
    ret = get("file.txt", 3);
    SANDBOX_END;
    
    if (ret != -1){
	flag_get = 0;
        push_info_msg(_("You do not return -1 when fstat() fails."));
        set_tag("failure_handling");
        CU_FAIL();
    }
}
void test_munmap_q1_fail(){
    set_test_metadata("q1", _("Test munmap fails"), 1);
    monitored.fstat = true;
    failures.fstat=FAIL_FIRST;
    failures.fstat_ret = -1;   
    int ret = 0;
    gen_file(10);
    SANDBOX_BEGIN;
    ret = get("file.txt", 3);
    SANDBOX_END;
    
    if (ret != -1){
	flag_get = 0;
        push_info_msg(_("You do not return -1 when munmap() fails."));
        set_tag("failure_handling");
        CU_FAIL();
    }
    if(flag_get){
	set_tag("q1");
    }
}
int main(int argc, char** argv){
    BAN_FUNCS(system, set_tag, fopen, fread, fwrite, read, write, fclose);
    RUN(test_get, test_set, test_close_q1, test_get_oob, test_mmap_q1_fail, test_open_q1_fail, test_fstat_q1_fail, test_munmap_q1_fail, test_mmap_q2_fail, test_open_q2_fail, test_fstat_q2_fail, test_close_q2);
}
