#include "student_code_sol.h"

int myfunc_sol(char* filename) {
	int fd = open(filename, O_RDONLY); 
	if(fd == -1) {
	    return -1;
	}
	struct stat buf;
	if(fstat(fd, &buf)){
		close(fd);
		return -5;
	}
	int i;
	int sum = 0;
	if(buf.st_size==0){
		close(fd);
		return sum;
	}
	int* addr = (int*) mmap(NULL,buf.st_size,PROT_READ,MAP_SHARED,fd,0);
	if(addr == MAP_FAILED){ 
		close(fd);
	    return -3;
	}
	if (close(fd) < 0){
		munmap((void*) addr, buf.st_size); 
	    return -2;
	}
	for(i = 0; i < (buf.st_size/sizeof(int)); i++){
		sum += addr[i];
	}
	if(munmap((void*) addr, buf.st_size)){
		return -4;
	}	
	return sum;
}
