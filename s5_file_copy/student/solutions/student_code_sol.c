#include "student_code_sol.h"

int myfunc_sol(char* file_name, char* new_file_name){
	int fd = open(file_name,O_RDONLY);
	if(fd==-1){
		return -1;
	}
	struct stat buf;
	int check = fstat(fd,&buf);
	if(check==-1){
		close(fd);
		return -1;
	}
	int fd2 = open(new_file_name,O_RDWR|O_TRUNC|O_CREAT,buf.st_mode);
	if(fd2==-1){
		close(fd);
		return -1;
	}
	check = ftruncate(fd2, buf.st_size);
	if(check==-1){
		close(fd);
		close(fd2);
		return -1;
	}
	void* addr1 = mmap(NULL,buf.st_size,PROT_READ,MAP_SHARED,fd,0);
	if(addr1==MAP_FAILED){
		close(fd);
		close(fd2);
		return -1;
	}
	void* addr2 = mmap(NULL,buf.st_size,PROT_READ|PROT_WRITE,MAP_SHARED,fd2,0);
	if(addr2==MAP_FAILED){
		close(fd);
		close(fd2);
		munmap(addr1,buf.st_size);
		return -1;
	}
	check = close(fd);
	if(check==-1){
		close(fd2);
		munmap(addr1,buf.st_size);
		munmap(addr2,buf.st_size);
		return -1;
	}
	check = close(fd2);
	if(check==-1){
		munmap(addr1,buf.st_size);
		munmap(addr2,buf.st_size);
		return -1;
	}
	memcpy(addr2,addr1,buf.st_size);
	check = msync(addr2,buf.st_size,MS_SYNC);
	if(check==-1){
		munmap(addr1,buf.st_size);
		munmap(addr2,buf.st_size);
		return -1;
	}
	check = munmap(addr1,buf.st_size);
	if(check==-1){
		munmap(addr2,buf.st_size);
		return -1;
	}
	check = munmap(addr2,buf.st_size);
	if(check==-1){
		return -1;
	}
	return 0;
}
