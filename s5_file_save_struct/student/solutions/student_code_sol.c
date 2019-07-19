#include "student_code_sol.h"

int save_sol(point_t *pt, int size, char *filename){
	int fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR);
	if(fd == -1){
		return -1;
	}
	if(ftruncate(fd,size*sizeof(point_t))){
		return -6;
	}
	void* addr = mmap(NULL, size*sizeof(point_t), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if(addr == MAP_FAILED){
		close(fd);
		return -2;
	}
	memcpy(addr, (const void*) pt, size*sizeof(point_t));
	int ret = msync(addr, size*sizeof(point_t), MS_SYNC);
	if(ret==-1){
		munmap(addr, size*sizeof(point_t));
		return -5;
	}
	if(close(fd) == -1){
		munmap(addr,size*sizeof(point_t));
		return -2;
	}
	ret = munmap(addr, size*sizeof(point_t));
	if(ret==-1){
		return -4;
	}
	return 0;
}