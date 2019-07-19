#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include "student_code_sol.h"

int file_exists_sol(char* filename){
	int fd = open(filename, O_RDONLY); 
	if(fd == -1) {
	    return -1;
	}
	close(fd);
	return 0;
}


