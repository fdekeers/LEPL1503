// CTester template

#include <stdlib.h>
#include "student_code.h"
#include "../../course/common/student/CTester/CTester.h"

point_t* gen_struct(int size){
    point_t *tab = malloc(size*sizeof(point_t));
    if (tab == NULL){
        CU_FAIL(_("Error, can not initialise test file"));
        return (point_t*)NULL;
    }
    for (int i = 0; i < size; i++){
        tab[i].x = i+i;
        tab[i].y = i+i+i;
        tab[i].z = i+i*i;
    }
    return tab;
}
int flag = 1;
void _test() {
    int size = 6;
    int ret = 0;
    point_t* tab = gen_struct(size);
    
    monitored.open = true;
    monitored.close = true;
    monitored.mmap = true;
    monitored.munmap = true;
    monitored.msync = true;
    monitored.memcpy = true;
    monitored.ftruncate = true;
    
    SANDBOX_BEGIN;
    ret = save(tab, size, "file.txt");
    SANDBOX_END;

    free(tab);
    tab = NULL;
    
    if (stats.open.called != 1) {
	flag = 0;
        CU_FAIL();
        push_info_msg(_("You should call open() exactly once."));
    }
    if (stats.mmap.called != 1) {
	flag = 0;
        CU_FAIL();
        push_info_msg(_("You should call mmap() exactly once."));

    }
    if (stats.close.called != 1) {
	flag = 0;
        CU_FAIL();
        push_info_msg(_("You should call close() exactly once."));
    }
    if (stats.munmap.called != 1) {
	flag = 0;
        CU_FAIL();
        push_info_msg(_("You should call munmap() exactly once."));
    }
    if (stats.msync.called != 1) {
	flag = 0;
        CU_FAIL();
        push_info_msg(_("You should call msync() exactly once."));
    }
    if (stats.memcpy.called != 1){
        flag = 0;
        CU_FAIL();
        push_info_msg(_("You should call memcpy() exactly once."));
    }
    if (stats.ftruncate.called != 1){
        flag = 0;
        CU_FAIL();
        push_info_msg(_("You should call ftruncate() exactly once."));
    }
    
    //Regenerate the struct in case student modified it
    tab = gen_struct(size);
    int fd = open("file.txt",O_RDONLY); 
    if(fd == -1) { 
	flag = 0;
        CU_FAIL(_("Error, can not initialise test file"));
        push_info_msg(_("You didn't create the file."));
        return;
    }

    point_t s;
    for(int i = 0; i < size; i++){
        if ((int)read(fd, (void *) &s, sizeof(point_t)) < 1){
	    flag = 0;
            push_info_msg(_("You did not write all content of the array in the file."));
            CU_FAIL();
            return;
        }
        else if (tab[i].x != s.x || tab[i].y != s.y || tab[i].z != s.z){
	    flag = 0;
            push_info_msg(_("You did not write the array of struct correctly in the file."));
            CU_FAIL();
            return;
        }
    }
    
    if ((int)read(fd, (void *) &s, 1) > 0) {
	flag = 0;
        CU_FAIL();
        push_info_msg(_("There's data in the file, after the end of the array."));
    }
    free(tab);
    close(fd);
    if(ret != 0){
	flag = 0;
        push_info_msg(_("You did not return 0 when everything should work."));
        CU_FAIL(); 
    }   
}

void test_no_file() {
    set_test_metadata("q1", _("Test writing the struct, no file already created"), 2);
    system("rm file.txt");
    _test();
}

void test_with_file() {
    set_test_metadata("q1", _("Test writing the struct, with file already created"), 1);
    system("rm file.txt");
    system("echo \"INTXINTYINTZINTXINTYINTZINTXINTYINTZINTXINTYINTZINTXINTYINTZINTXINTYINTZINTXINTYINTZINTXINTYINTZ\" > file.txt");
    _test();
}

void test_close() {
    set_test_metadata("q1", _("Test close()."), 1);
    int size = 6;
    point_t* tab = gen_struct(size);
    system("rm file.txt");
    
    monitored.close = true;
    monitored.open = true;
    
    SANDBOX_BEGIN;
    save(tab, size, "file.txt");
    SANDBOX_END;
    
    free(tab);
    tab = NULL;
    
    if (stats.close.called != 1){
	flag = 0;
        push_info_msg(_("You did not close() the file or called close() too many times."));
        CU_FAIL();
    }if(stats.open.last_return != stats.close.last_params.fd){
	flag = 0;
        push_info_msg(_("The close() does not close the file you opened before."));
        CU_FAIL();
    }
    
    
    //We fail the close()
    system("rm file.txt");
    tab = gen_struct(size);
    int ret = 0;
    monitored.close = true;
    failures.close = FAIL_FIRST;
    failures.close_ret = -1;
    SANDBOX_BEGIN;
    ret = save(tab, size, "file.txt");
    SANDBOX_END;
    
    if(ret != -2){
	flag = 0;
        push_info_msg(_("When close() fails, your code does not return -2."));
        CU_FAIL(); 
        set_tag("failure_handling");
    }

    free(tab);
    tab = NULL;
}

void test_open() {
    set_test_metadata("q1", _("Test open()."), 1);
    int size = 6;
    point_t* tab = gen_struct(size);
    int ret = 0;
    system("rm file.txt");
    
    monitored.open = true;
    failures.open = FAIL_FIRST;
    failures.open_ret = -1;
    SANDBOX_BEGIN;
    ret = save(tab, size, "file.txt");
    SANDBOX_END;
    
    free(tab);
    tab = NULL;

    if(ret != -1){
	flag = 0;
        push_info_msg(_("You do not return -1 when open() fails."));
        CU_FAIL();
        set_tag("failure_handling");
    }
    
    //Test if open() return a correct file descriptor.
    system("rm file.txt");
    tab = gen_struct(size);
    monitored.open = true;
    SANDBOX_BEGIN;
    ret = save(tab, size, "file.txt");
    SANDBOX_END;

    if(stats.open.last_return <= 2 && flag){
	flag = 0;
        push_info_msg(_("When the open() should be fine, your code returns -1."));
        CU_FAIL();
    }

    free(tab);
    tab = NULL;
}
void test_munmap_fail() {
    set_test_metadata("q1", _("Test munmap() fail."), 1);
    int size = 6;
    point_t* tab = gen_struct(size);
    int ret = 0;
    system("rm file.txt");
    
    monitored.munmap = true;
    failures.munmap = FAIL_ALWAYS;
    failures.munmap_ret = -1;
    SANDBOX_BEGIN;
    ret = save(tab, size, "file.txt");
    SANDBOX_END;
    
    free(tab);
    tab = NULL;
    
    if(ret != -4){
	flag = 0;
        push_info_msg(_("You do not return -4 when munmap() fails."));
        set_tag("failure_handling");
        CU_FAIL();
    }

}
void test_msync_fail() {
    set_test_metadata("q1", _("Test msync() fail."), 1);
    int size = 6;
    point_t* tab = gen_struct(size);
    int ret = 0;
    system("rm file.txt");
    
    monitored.msync = true;
    failures.msync = FAIL_ALWAYS;
    failures.msync_ret = -1;
    SANDBOX_BEGIN;
    ret = save(tab, size, "file.txt");
    SANDBOX_END;
    
    free(tab);
    tab = NULL;
    
    if(ret != -5){
	flag = 0;
        push_info_msg(_("You do not return -5 when msync() fails."));
        set_tag("failure_handling");
        CU_FAIL();
    }

}
void test_ftruncate_fail() {
    set_test_metadata("q1", _("Test ftruncate() fail."), 1);
    int size = 6;
    point_t* tab = gen_struct(size);
    int ret = 0;
    system("rm file.txt");
    
    monitored.ftruncate = true;
    failures.ftruncate = FAIL_ALWAYS;
    failures.ftruncate_ret = -1;
    SANDBOX_BEGIN;
    ret = save(tab, size, "file.txt");
    SANDBOX_END;
    
    free(tab);
    tab = NULL;
    
    if(ret != -6){
	flag = 0;
        push_info_msg(_("You do not return -6 when ftruncate() fails."));
        set_tag("failure_handling");
        CU_FAIL();
    }

}
void test_mmap_fail() {
    set_test_metadata("q1", _("Test mmap() fail."), 1);
    int size = 6;
    point_t* tab = gen_struct(size);
    int ret = 0;
    system("rm file.txt");
    
    monitored.mmap = true;
    failures.mmap = FAIL_ALWAYS;
    failures.mmap_ret = MAP_FAILED;
    SANDBOX_BEGIN;
    ret = save(tab, size, "file.txt");
    SANDBOX_END;
    
    free(tab);
    tab = NULL;
    
    if(ret != -3){
	flag = 0;
        push_info_msg(_("You do not return -3 when mmap() fails."));
        set_tag("failure_handling");
        CU_FAIL();
    }
    if(flag){
	set_tag("q1");
    }
}

int main(int argc,char** argv){
    BAN_FUNCS(system, fopen, fread, fwrite, fclose, read, write);
    RUN(test_no_file, test_with_file, test_close, test_open, test_mmap_fail, test_munmap_fail, test_msync_fail, test_ftruncate_fail);
}
