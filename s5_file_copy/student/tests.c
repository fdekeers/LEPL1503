// CTester template

#include <stdlib.h>
#include "student_code.h"
#include "../../course/common/student/CTester/CTester.h"

/*
 * Generate a file named "file.txt".
 * The content is the bytes in range [0, n[
 */
void gen_file(int n){
    system("rm newfile.txt");
    int fd = open("file.txt",O_WRONLY|O_CREAT|O_TRUNC, S_IRUSR|S_IWUSR);
    if(fd == -1) {
        CU_FAIL("Error, can not initialise test file");
    }
    char array[n];
    int i = 0;
    for (i = 0; i < n; i++){
        array[i] = i;
        if (write(fd, (void *) &array[i], sizeof(char)) == -1){
            CU_FAIL("Error, can not initialise test file");
        }
    }
    if (close(fd) == -1)
        CU_FAIL("Error, can not initialise test file");
}
int flag = 1;
/*
 * Test with open fail
 */
void test_fail_open() {
    set_test_metadata("q1", _("Test when open() fails"), 1);
    int ret = 0;
    
    monitored.open = true;
    failures.open = FAIL_TWICE;
    failures.open_ret = -1;
    
    SANDBOX_BEGIN;
    ret = myfunc("file_that_does_not_exists.txt", "newfile_that_should_not_be_create.txt");
    SANDBOX_END;

    if (ret != -1){
	flag = 0;
        push_info_msg(_("When the open() function fails, your code does not return -1."));
        CU_FAIL();
    }
}


/*
 * Test with an empty file
 */
void test_empty_file() {
    set_test_metadata("q1", _("Test with empty file"), 1);
    gen_file(0);
    
    SANDBOX_BEGIN;
    myfunc("file.txt", "newfile.txt");
    SANDBOX_END;
    
    system("chmod 644 newfile.txt"); //If student does not set permission correctly, we set it to avoid test error
    if (system("diff file.txt newfile.txt") != 0){
	flag = 0;
        push_info_msg(_("You copy is not identical."));
        CU_FAIL();
    }
}


/*
 * Test permission
 */
void test_file_permission() {
    set_test_metadata("q1", _("Test if permissions are equal"), 1);
    gen_file(122);
    
    SANDBOX_BEGIN;
    myfunc("file.txt", "newfile.txt");
    SANDBOX_END;
    
    system("ls -al file.txt | head -c 10 > PERM_A.txt");
    system("ls -al newfile.txt | head -c 10 > PERM_B.txt");
    if (system("diff PERM_A.txt PERM_B.txt") != 0){
	flag = 0;
        push_info_msg(_("The permission of the two files are not equals."));
        CU_FAIL();
    }
}



/*
 * Test with some bytes in the file
 */
void test_file() {
    set_test_metadata("q1", _("Test with non-empty file"), 2);
    gen_file(122);
    int ret = 0;
    monitored.memcpy = true;
    
    SANDBOX_BEGIN;
    ret = myfunc("file.txt", "newfile.txt");
    SANDBOX_END;
    
    monitored.memcpy = false;
    
    system("chmod 644 newfile.txt"); //If student does not set permission correctly, we set it to avoid test error
    // S_IRUSR|S_IWUSR = 644
    if (system("diff file.txt newfile.txt") != 0){
	flag = 0;
        push_info_msg(_("You copy is not identical."));
        CU_FAIL();
    }
    if (ret != 0){
	flag = 0;
        push_info_msg(_("You do not return 0 when the copy should be successful. Check the permissions you specified and the hint above related to permissions."));
        CU_FAIL();
    }
    if (stats.memcpy.called != 1){
        flag = 0;
        push_info_msg(_("You didn't call memcpy() exactly once"));
        CU_FAIL();
    }
}

/*
 * Test with some bytes in the file
 */
void test_file_mmap_fail() {
    set_test_metadata("q1", _("Test with normal file (with mmap failures)"), 1);
    gen_file(125);
    int ret = 0;
    
    monitored.mmap = true;
    failures.mmap = FAIL_FIRST;
    failures.mmap_ret = MAP_FAILED;
    
    SANDBOX_BEGIN;
    ret = myfunc("file.txt", "newfile.txt");
    SANDBOX_END;

    if (ret != -1){
	flag = 0;
        push_info_msg(_("You do not return -1 when a fail occurs with mmap()"));
        set_tag("failure_handling");
        CU_FAIL();
    }
}
/*
 * Test with some bytes in the file
 */
void test_file_munmap_fail() {
    set_test_metadata("q1", _("Test with normal file (with munmap failures)"), 1);
    gen_file(125);
    int ret = 0;
    
    monitored.munmap = true;
    failures.munmap = FAIL_FIRST;
    failures.munmap_ret = -1;
    
    SANDBOX_BEGIN;
    ret = myfunc("file.txt", "newfile.txt");
    SANDBOX_END;

    if (ret != -1){
	flag = 0;
        push_info_msg(_("You do not return -1 when a fail occurs with munmap()"));
        set_tag("failure_handling");
        CU_FAIL();
    }
}
/*
 * Test with some bytes in the file
 */
void test_file_msync_fail() {
    set_test_metadata("q1", _("Test with normal file (with msync failures)"), 1);
    gen_file(125);
    int ret = 0;
    
    monitored.msync = true;
    failures.msync = FAIL_FIRST;
    failures.msync_ret = -1;
    
    SANDBOX_BEGIN;
    ret = myfunc("file.txt", "newfile.txt");
    SANDBOX_END;

    if (ret != -1){
	flag = 0;
        push_info_msg(_("You do not return -1 when a fail occurs with msync()"));
        set_tag("failure_handling");
        CU_FAIL();
    }
}
void test_file_ftruncate_fail() {
    set_test_metadata("q1", _("Test with normal file (with ftruncate failures)"), 1);
    gen_file(125);
    int ret = 0;
    
    monitored.ftruncate = true;
    failures.ftruncate = FAIL_FIRST;
    failures.ftruncate_ret = -1;
    
    SANDBOX_BEGIN;
    ret = myfunc("file.txt", "newfile.txt");
    SANDBOX_END;

    if (ret != -1){
	flag = 0;
        push_info_msg(_("You do not return -1 when a fail occurs with ftruncate()"));
        set_tag("failure_handling");
        CU_FAIL();
    }
}
void test_stat_fail() {
    set_test_metadata("q1", _("Test return value when fstat() fails"), 1);
    gen_file(125);
    int ret = 0;
    
    monitored.fstat = true;
    failures.fstat = FAIL_ALWAYS;
    failures.fstat_ret = -1;
    
    SANDBOX_BEGIN;
    ret = myfunc("file.txt", "newfile.txt");
    SANDBOX_END;

    if (ret != -1){
	flag = 0;
        push_info_msg(_("You do not return -1 when a fail occurs with fstat()"));
        set_tag("failure_handling");
        CU_FAIL();
    }
}

/*
 * Test with some bytes in the file with close()
 */
void test_close() {
    set_test_metadata("q1", _("Test close()."), 1);
    gen_file(2);
    
    monitored.close = true;
    monitored.open = true;
    SANDBOX_BEGIN;
    myfunc("file.txt", "newfile.txt");
    SANDBOX_END;
    
    if (stats.close.called != 2){
	flag = 0;
        push_info_msg(_("You did not close() the two files."));

        CU_FAIL();
    }
    
    //We fail a close()
    gen_file(3);
    int ret = 0;
    monitored.close = true;
    failures.close = FAIL_TWICE;
    failures.close_ret = -1;
    SANDBOX_BEGIN;
    ret = myfunc("file.txt", "newfile.txt");
    SANDBOX_END;
    
    if(ret != -1){
	flag = 0;
        push_info_msg(_("When close() fails, your code does not return -1."));

        CU_FAIL(); 
    }
    if(flag){
	set_tag("q1");
    }

}


/*
 * Test original file not modified (content and permissions)
 */
void test_original_integrity() {
    set_test_metadata("q1", _("Test original file not modified"), 1);
    gen_file(70);
    system("cp file.txt file_original.txt");
    system("ls -al file.txt | head -c 10 > PERM_FILE_1.txt");
    
    SANDBOX_BEGIN;
    myfunc("file.txt", "newfile.txt");
    SANDBOX_END;
    
    if (system("diff file.txt file_original.txt") != 0){
	flag = 0;
        push_info_msg(_("You can not modify the original file"));
        CU_FAIL();

    }
    system("ls -al file.txt | head -c 10 > PERM_FILE_2.txt");
    if (system("diff PERM_FILE_1.txt PERM_FILE_2.txt") != 0){
	flag = 0;
        push_info_msg(_("You can not modify the permissions of the original file."));
        CU_FAIL();

    }

}

int main(int argc,char** argv){
    BAN_FUNCS(system, set_tag, fopen, fread, fwrite, fclose, read, write);
    RUN(test_fail_open, test_empty_file, test_file_permission, test_file, test_file_ftruncate_fail,test_file_mmap_fail,test_file_munmap_fail,test_file_msync_fail, test_stat_fail, test_original_integrity, test_close);
}
