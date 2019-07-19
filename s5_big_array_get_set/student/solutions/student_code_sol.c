#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/mman.h>
int get_sol(char* filename, int index){
	int fd = open(filename, O_RDONLY);
	if (fd < 0){
	    return -1;
	}
	struct stat b;
	if (fstat(fd, &b) != 0){
	    close(fd);
	    return -1;
	}
	if (sizeof(int)*index > b.st_size){
	    close(fd);
	    return -2;
	}
	int * ptr = (int *)mmap(NULL, b.st_size, PROT_READ, MAP_SHARED,fd, 0);
	if(ptr == MAP_FAILED){
	    close(fd);
	    return -1;
	}
	int c = *(ptr+index);
	int err = munmap(ptr, b.st_size);
	err = close(fd);
	if(err == -1){
	    return -1;
	}
	return c;
}
void set_sol(char* filename, int index, int value){
	int fd = open(filename, O_RDWR);
	if(fd<0){
	    return;
	}
	struct stat b;
	if (fstat(fd, &b) != 0){
	    close(fd);
	    return;
	}

	if (index*sizeof(int)>b.st_size){
	    close(fd);
	    return;
	}
	int * ptr = (int *)mmap(NULL, b.st_size, PROT_READ | PROT_WRITE, MAP_SHARED,fd, 0);
	if(ptr == MAP_FAILED){
	    close(fd);
	    return;
	}
	ptr[index] = value;
	int err = msync(ptr, b.st_size, MS_SYNC);
	err = munmap(ptr, b.st_size);
	err = close(fd);
	if(err == -1){
	    return;
	}
}

