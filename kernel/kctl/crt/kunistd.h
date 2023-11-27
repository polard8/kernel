// kunistd.h

#ifndef __KUNISTD_H
#define __KUNISTD_H    1

#define STDIN_FILENO   0  // Standard input file descriptor
#define STDOUT_FILENO  1  // Standard output file descriptor
#define STDERR_FILENO  2  // Standard error file descriptor

// Process IDentifier. (posix)
typedef int    pid_t;

//
// prototypes ======================
//

int __gethostname(char *buffer);
int __sethostname(const char *new_hostname);

long fpathconf(int fildes, int name);
long pathconf(const char *pathname, int name);

off_t sys_lseek(int fd, off_t offset, int whence);

// See: sys.c
unsigned long sys_alarm(unsigned long seconds);

#endif    

