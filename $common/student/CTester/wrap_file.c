// wrapper for the file operations, open, read, write

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include "wrap.h"

int __real_open(const char *pathname, int flags, mode_t mode);
int __real_creat(const char *pathname, mode_t mode);
int __real_close(int fd);
ssize_t __real_read(int fd, void *buf, size_t count);
ssize_t __real_write(int fd, const void *buf, size_t count);
void * __real_mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset);
int __real_munmap(void *addr, size_t length);
int __real_msync(void *addr, size_t length, int flags);
int __real_ftruncate(int fd, off_t length);
void * __real_memcpy(void *dest, const void* src, size_t n);
int __real_stat(const char* path, struct stat *buf);
int __real_fstat(int fd, struct stat *buf);
int __real_lstat(const char* path, struct stat *buf);
ssize_t __real_pread(int fd, void *buf, size_t count, off_t offset);
ssize_t __real_pwrite(int fd, const void *buf, size_t count, off_t offset);
off_t __real_lseek(int fd, off_t offset, int whence);

extern bool wrap_monitoring;
extern struct wrap_stats_t stats;
extern struct wrap_monitor_t monitored;
extern struct wrap_fail_t failures;
extern struct wrap_log_t logs;

int __wrap_open(char *pathname, int flags, mode_t mode) {

  if(!wrap_monitoring || !monitored.open) {
    return __real_open(pathname,flags,mode); 
  }
  stats.open.called++;
  stats.open.last_params.pathname=pathname;
  stats.open.last_params.flags=flags;
  stats.open.last_params.mode=mode;
  
  if (FAIL(failures.open)) {
    failures.open=NEXT(failures.open);
    errno=failures.open_errno;
    stats.open.last_return=failures.open_ret;
    return failures.open_ret;
  }
  failures.open=NEXT(failures.open);
  // did not fail
  int ret=__real_open(pathname, flags, mode);
  stats.open.last_return=ret;
  return ret;

}

int __wrap_creat(char *pathname, mode_t mode) {


  if(!wrap_monitoring || !monitored.creat) {
    return __real_creat(pathname,mode); 
  }
  stats.creat.called++;
  stats.creat.last_params.pathname=pathname;
  stats.creat.last_params.mode=mode;
  
  if (FAIL(failures.creat)) {
    failures.creat=NEXT(failures.creat);
    errno=failures.creat_errno;
    stats.creat.last_return=failures.creat_ret;
    return failures.creat_ret;
  }
  failures.creat=NEXT(failures.creat);
  // did not fail
  int ret=__real_creat(pathname, mode);
  stats.creat.last_return=ret;
  return ret;

}

int __wrap_close(int fd){

  if(!wrap_monitoring || !monitored.close) {
    return __real_close(fd); 
  }
  stats.close.called++;
  stats.close.last_params.fd=fd;
  
  if (FAIL(failures.close)) {
    failures.close=NEXT(failures.close);
    errno=failures.close_errno;
    stats.close.last_return=failures.close_ret;
    return failures.close_ret;
  }
  failures.close=NEXT(failures.close);
  // did not fail
  int ret=__real_close(fd);
  stats.close.last_return=ret;
  return ret;

}

int __wrap_read(int fd, void *buf, size_t count){

  if(!wrap_monitoring || !monitored.read) {
    return __real_read(fd,buf,count); 
  }
  stats.read.called++;
  stats.read.last_params.fd=fd;
  stats.read.last_params.buf=buf;
  stats.read.last_params.count=count;
  
  if (FAIL(failures.read)) {
    failures.read=NEXT(failures.read);
    errno=failures.read_errno;
    stats.read.last_return=failures.read_ret;
    return failures.read_ret;
  }
  failures.read=NEXT(failures.read);
  // did not fail
  int ret=__real_read(fd,buf,count);
  stats.read.last_return=ret;
  return ret;

}


int __wrap_write(int fd, void *buf, size_t count){

  if(!wrap_monitoring || !monitored.write) {
    return __real_write(fd,buf,count); 
  }
  stats.write.called++;
  stats.write.last_params.fd=fd;
  stats.write.last_params.buf=buf;
  stats.write.last_params.count=count;
  
  if (FAIL(failures.write)) {
    failures.write=NEXT(failures.write);
    errno=failures.write_errno;
    stats.write.last_return=failures.write_ret;
    return failures.write_ret;
  }
  failures.write=NEXT(failures.write);
  // did not fail
  int ret=__real_write(fd,buf,count);
  stats.write.last_return=ret;
  return ret;

}

void * __wrap_mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset){

  if(!wrap_monitoring || !monitored.mmap){
    return __real_mmap(addr, length, prot, flags, fd, offset);
  }

  stats.mmap.called++;
  stats.mmap.last_params.addr=addr;
  stats.mmap.last_params.length=length;
  stats.mmap.last_params.prot=prot;
  stats.mmap.last_params.flags=flags;
  stats.mmap.last_params.fd=fd;
  stats.mmap.last_params.offset=offset;
  
  if (FAIL(failures.mmap)) {
    failures.mmap=NEXT(failures.mmap);
    errno=failures.mmap_errno;
    stats.mmap.last_return=failures.mmap_ret;
    return failures.mmap_ret;
  }
  failures.mmap=NEXT(failures.mmap);
  // did not fail
  void *ret=__real_mmap(addr, length, prot, flags, fd, offset);
  stats.mmap.last_return=ret;
  return ret;

}
int __wrap_munmap(void *addr, size_t length){
  if(!wrap_monitoring || !monitored.munmap) {
    return __real_munmap(addr, length); 
  }
  stats.munmap.called++;
  stats.munmap.last_params.addr=addr;
  stats.munmap.last_params.length=length;
  
  if (FAIL(failures.munmap)) {
    failures.munmap=NEXT(failures.munmap);
    errno=failures.munmap_errno;
    stats.munmap.last_return=failures.munmap_ret;
    return failures.munmap_ret;
  }
  failures.munmap=NEXT(failures.munmap);
  // did not fail
  int ret=__real_munmap(addr, length);
  stats.munmap.last_return=ret;
  return ret;
}
int __wrap_msync(void *addr, size_t length, int flags){
  if(!wrap_monitoring || !monitored.msync) {
    return __real_msync(addr, length, flags); 
  }
  stats.msync.called++;
  stats.msync.last_params.addr=addr;
  stats.msync.last_params.length=length;
  stats.msync.last_params.flags=flags;
  
  if (FAIL(failures.msync)) {
    failures.msync=NEXT(failures.msync);
    errno=failures.msync_errno;
    stats.msync.last_return=failures.msync_ret;
    return failures.msync_ret;
  }
  failures.msync=NEXT(failures.msync);
  // did not fail
  int ret=__real_msync(addr, length, flags);
  stats.msync.last_return=ret;
  return ret;
}

int __wrap_ftruncate(int fd, off_t length){

  if(!wrap_monitoring || !monitored.ftruncate) {
    return __real_ftruncate(fd, length);
  }
  stats.ftruncate.called++;
  stats.ftruncate.last_params.fd=fd;
  stats.ftruncate.last_params.length=length;
  
  if (FAIL(failures.ftruncate)) {
    failures.ftruncate=NEXT(failures.ftruncate);
    errno=failures.ftruncate_errno;
    stats.ftruncate.last_return=failures.ftruncate_ret;
    return failures.ftruncate_ret;
  }
  failures.ftruncate=NEXT(failures.ftruncate);
  // did not fail
  int ret= __real_ftruncate(fd, length);
  stats.ftruncate.last_return=ret;
  return ret;

}

void * __wrap_memcpy(void *dest, const void* src, size_t n){

  if(!wrap_monitoring || !monitored.memcpy) {
    return __real_memcpy(dest, src, n); 
  }
  stats.memcpy.called++;
  stats.memcpy.last_params.dest=dest;
  stats.memcpy.last_params.src=src;
  stats.memcpy.last_params.n=n;
  
  if (FAIL(failures.memcpy)) {
    failures.memcpy=NEXT(failures.memcpy);
    stats.memcpy.last_return=failures.memcpy_ret;
    return failures.memcpy_ret;
  }
  failures.memcpy=NEXT(failures.memcpy);
  // did not fail
  void *ret=__real_memcpy(dest, src, n);
  stats.memcpy.last_return=ret;
  return ret;

}

int __wrap_stat(char *path, struct stat *buf) {
  
  if(!wrap_monitoring || !monitored.stat) {
return __real_stat(path,buf); 
  }
  stats.stat.called++;
  stats.stat.last_params.path=path;
  stats.stat.last_params.buf=buf;
  
  if (FAIL(failures.stat)) {
    failures.stat=NEXT(failures.stat);
    errno=failures.stat_errno;
    stats.stat.last_return=failures.stat_ret;
    return failures.stat_ret;
  }
  failures.stat=NEXT(failures.stat);
  // did not fail
  int ret=__real_stat(path,buf);
  stats.stat.returned_stat.st_dev=buf->st_dev;
  stats.stat.returned_stat.st_ino=buf->st_ino;
  stats.stat.returned_stat.st_mode=buf->st_mode;
  stats.stat.returned_stat.st_nlink=buf->st_nlink;
  stats.stat.returned_stat.st_uid=buf->st_uid;
  stats.stat.returned_stat.st_gid=buf->st_gid;
  stats.stat.returned_stat.st_rdev=buf->st_rdev;
  stats.stat.returned_stat.st_size=buf->st_size;
  stats.stat.returned_stat.st_blksize=buf->st_blksize;
  stats.stat.returned_stat.st_blocks=buf->st_blocks;
  stats.stat.returned_stat.st_atime=buf->st_atime;
  stats.stat.returned_stat.st_mtime=buf->st_mtime;
  stats.stat.returned_stat.st_ctime=buf->st_ctime;
  stats.stat.last_return=ret;
  return ret;

}

int __wrap_fstat(int fd, struct stat *buf) {

  if(!wrap_monitoring || !monitored.fstat) {
    return __real_fstat(fd,buf);
  }
  stats.fstat.called++;
  stats.fstat.last_params.fd=fd;
  stats.fstat.last_params.buf=buf;
  
  if (FAIL(failures.fstat)) {
    failures.fstat=NEXT(failures.fstat);
    errno=failures.fstat_errno;
    return failures.fstat_ret;
  }
  failures.fstat=NEXT(failures.fstat);
  // did not fail
  int ret=__real_fstat(fd,buf);
  stats.fstat.returned_stat.st_dev=buf->st_dev;
  stats.fstat.returned_stat.st_ino=buf->st_ino;
  stats.fstat.returned_stat.st_mode=buf->st_mode;
  stats.fstat.returned_stat.st_nlink=buf->st_nlink;
  stats.fstat.returned_stat.st_uid=buf->st_uid;
  stats.fstat.returned_stat.st_gid=buf->st_gid;
  stats.fstat.returned_stat.st_rdev=buf->st_rdev;
  stats.fstat.returned_stat.st_size=buf->st_size;
  stats.fstat.returned_stat.st_blksize=buf->st_blksize;
  stats.fstat.returned_stat.st_blocks=buf->st_blocks;
  stats.fstat.returned_stat.st_atime=buf->st_atime;
  stats.fstat.returned_stat.st_mtime=buf->st_mtime;
  stats.fstat.returned_stat.st_ctime=buf->st_ctime;

  stats.fstat.last_return=ret;
  return ret;

}

off_t __wrap_lseek(int fd, off_t offset, int whence) {
  
  if(!wrap_monitoring || !monitored.lseek) {
    return __real_lseek(fd,offset,whence);
  }
  stats.lseek.called++;
  stats.lseek.last_params.fd=fd;
  stats.lseek.last_params.offset=offset;
  stats.lseek.last_params.whence=whence;

  if (FAIL(failures.lseek)) {
    failures.lseek=NEXT(failures.lseek);
    errno=failures.lseek_errno;
    return failures.lseek_ret;
  }
  failures.lseek=NEXT(failures.lseek);
  // did not fail
  off_t ret=__real_lseek(fd,offset,whence);
  stats.lseek.last_return=ret;
  return ret;
}
