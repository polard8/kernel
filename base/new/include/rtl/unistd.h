// unistd.h

#ifndef __UNISTD_H
#define __UNISTD_H    1

// FreeBSD stuff
#define  STDIN_FILENO   0  /* standard input file descriptor */
#define  STDOUT_FILENO  1  /* standard output file descriptor */
#define  STDERR_FILENO  2  /* standard error file descriptor */

// Process IDentifier. (posix)
typedef int    pid_t;

//
// prototypes ======================
//

int __gethostname (char *buffer);
int __sethostname (const char *new_hostname);

long fpathconf (int fildes, int name);
long pathconf (const char *pathname, int name);

off_t sys_lseek (int fd, off_t offset, int whence);


// See:
// sys.c
unsigned long sys_alarm(unsigned long seconds);

#endif    



