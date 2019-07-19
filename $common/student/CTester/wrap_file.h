#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

// basic structure to record the parameters of the last open call


struct params_open_t {
  char *pathname;
  int flags;
  mode_t mode;
}; 

// basic statistics for the utilisation of the open system call

struct stats_open_t {
  int called;  // number of times the open system call has been issued
  struct params_open_t last_params; // parameters for the last call issued
  int last_return;   // return value of the last open call issued
};


struct params_creat_t {
  char *pathname;
  mode_t mode;
}; 

// basic statistics for the utilisation of the creat system call

struct stats_creat_t {
  int called;  // number of times the open system call has been issued
  struct params_creat_t last_params; // parameters for the last call issued
  int last_return;   // return value of the last open call issued
};


struct params_close_t {
  int fd;
}; 

// basic statistics for the utilisation of the close system call

struct stats_close_t {
  int called;  // number of times the open system call has been issued
  struct params_close_t last_params; // parameters for the last call issued
  int last_return;   // return value of the last open call issued
};

struct params_read_t {
  int fd;
  void *buf;
  ssize_t count;
}; 

// basic statistics for the utilisation of the read system call

struct stats_read_t {
  int called;  // number of times the read system call has been issued
  struct params_read_t last_params; // parameters for the last call issued
  int last_return;   // return value of the last read call issued
};

struct params_write_t {
  int fd;
  void *buf;
  ssize_t count;
}; 

// basic statistics for the utilisation of the write system call

struct stats_write_t {
  int called;  // number of times the write system call has been issued
  struct params_write_t last_params; // parameters for the last call issued
  int last_return;   // return value of the last write call issued
};

struct params_mmap_t {
  void *addr;
  size_t length;
  int prot;
  int flags;
  int fd;
  off_t offset;
}; 

// basic statistics for the utilisation of the mmap system call

struct stats_mmap_t{
  int called; // number of times the mmap system call has been issued
  struct params_mmap_t last_params; // parameters for the last call issued
  void *last_return;   // return value of the last mmap call issued
};

struct params_munmap_t {
  void *addr;
  size_t length;
}; 

// basic statistics for the utilisation of the munmap system call

struct stats_munmap_t{
  int called; // number of times the munmap system call has been issued
  struct params_munmap_t last_params; // parameters for the last call issued
  int last_return;   // return value of the last munmap call issued
};

struct params_msync_t {
  void *addr;
  size_t length;
  int flags;
}; 

// basic statistics for the utilisation of the msync system call

struct stats_msync_t{
  int called; // number of times the msync system call has been issued
  struct params_msync_t last_params; // parameters for the last call issued
  int last_return;   // return value of the last msync call issued
};

struct params_ftruncate_t {
  int fd;
  off_t length;
}; 

// basic statistics for the utilisation of the ftruncate system call

struct stats_ftruncate_t {
  int called;  // number of times the ftruncate system call has been issued
  struct params_ftruncate_t last_params; // parameters for the last call issued
  int last_return;   // return value of the last call issued
};

struct params_memcpy_t {
  void *dest;
  const void *src;
  size_t n;
}; 

// basic statistics for the utilisation of the memcpy system call

struct stats_memcpy_t {
  int called;  // number of times the memcpy system call has been issued
  struct params_memcpy_t last_params; // parameters for the last call issued
  void *last_return;   // return value of the last memcpy call issued
};
struct params_stat_t {
  char *path;
  struct stat *buf;
}; 

// basic statistics for the utilisation of the stat system call

struct stats_stat_t {
  int called;  // number of times the stat system call has been issued
  struct params_stat_t last_params; // parameters for the last call issued
  int last_return;   // return value of the last stat call issued
  struct stat returned_stat; // last returned stat structure
};


struct params_fstat_t {
  int fd;
  struct stat *buf;
}; 

// basic statistics for the utilisation of the fstat system call

struct stats_fstat_t {
  int called;  // number of times the fstat system call has been issued
  struct params_fstat_t last_params; // parameters for the last call issued
  int last_return;   // return value of the last fstat call issued
  struct stat returned_stat; // last returned stat structure
};


struct params_lseek_t {
  int fd;
  off_t offset;
  int whence;
}; 

// basic statistics for the utilisation of the fstat system call

struct stats_lseek_t {
  int called;  // number of times the lseek system call has been issued
  struct params_lseek_t last_params; // parameters for the last call issued
  int last_return;   // return value of the last lseek call issued
};
