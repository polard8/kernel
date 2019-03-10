/*
 * File: unistd.h - standard symbolic constants and types
 * 2018
 */
 
#ifndef _UNISTD_H
#define _UNISTD_H 

#include <sys/types.h>

/*
 In the C and C++ programming languages, unistd.h is the name 
 of the header file that provides access to the POSIX 
 operating system API. It is defined by the POSIX.1 standard, 
 the base of the Single Unix Specification, and should therefore 
 be available in any conforming (or quasi-conforming) 
 operating system/compiler (all official versions of UNIX, 
 including macOS, Linux, etc.).
 
 On Unix-like systems, the interface defined by unistd.h is 
 typically made up largely of system call wrapper functions 
 such as fork, pipe and I/O primitives (read, write, close, etc.).
 
 Credits: Wikipedia
 */
 
 /* NULL must be defined in <unistd.h> according to POSIX Sec. 2.7.1. */
//#define NULL    ((void *)0)

/* FreeBSD stuff */ 
/* IEEE Std 1003.1-90 */
/* These three definitions are required by POSIX Sec. 8.2.1.2. */
#define	STDIN_FILENO	0	/* standard input file descriptor */
#define	STDOUT_FILENO	1	/* standard output file descriptor */
#define	STDERR_FILENO	2	/* standard error file descriptor */


/* MINIX 3 */
/* Values used by access().  POSIX Table 2-8. */
#define F_OK               0	// test if file exists 
#define X_OK               1	// test if file is executable 
#define W_OK               2	// test if file is writable 
#define R_OK               4	// test if file is readable 

/* MINIX 3 */
/* Values used for whence in lseek(fd, offset, whence).  POSIX Table 2-9. */
#define SEEK_SET           0	/* offset is absolute  */
#define SEEK_CUR           1	/* offset is relative to current position */
#define SEEK_END           2	/* offset is relative to end of file */

//#todo kkk
/* This value is required by POSIX Table 2-10. */
//#define _POSIX_VERSION 199009L	/* which standard is being conformed to */


/*bsd*/
#define F_ULOCK		0
#define F_LOCK		1
#define F_TLOCK		2
#define F_TEST		3

 
/* MINIX 3 */ 
/* The following relate to configurable system variables. POSIX Table 4-2. */
#define _SC_ARG_MAX	   1
#define _SC_CHILD_MAX	   2
#define _SC_CLOCKS_PER_SEC 3
#define _SC_CLK_TCK	   3
#define _SC_NGROUPS_MAX	   4
#define _SC_OPEN_MAX	   5
#define _SC_JOB_CONTROL	   6
#define _SC_SAVED_IDS	   7
#define _SC_VERSION	   8
#define _SC_STREAM_MAX	   9
#define _SC_TZNAME_MAX    10
#define _SC_PAGESIZE	  11
#define _SC_PAGE_SIZE	  _SC_PAGESIZE

/* MINIX 3 */ 
/* The following relate to configurable pathname variables. POSIX Table 5-2. */
#define _PC_LINK_MAX	   1	/* link count */
#define _PC_MAX_CANON	   2	/* size of the canonical input queue */
#define _PC_MAX_INPUT	   3	/* type-ahead buffer size */
#define _PC_NAME_MAX	   4	/* file name size */
#define _PC_PATH_MAX	   5	/* pathname size */
#define _PC_PIPE_BUF	   6	/* pipe size */
#define _PC_NO_TRUNC	   7	/* treatment of long name components */
#define _PC_VDISABLE	   8	/* tty disable */
#define _PC_CHOWN_RESTRICTED 9	/* chown restricted or not */
 

/* 
 Process IDentifier 
 posix.  
 */


#ifndef __UID_T
#define __UID_T 
typedef int uid_t;
#endif 

#ifndef __PID_T
#define __PID_T 
typedef int pid_t;
#endif

#ifndef __GID_T
#define __GID_T 
typedef int gid_t;
#endif



//#todo:
//tem um monte de função pra fazer aqui.

int execve ( const char *filename, 
             const char *argv[], 
             const char *envp[] );  
void exit(int status);			 		 
int fork();


int setuid ( uid_t uid );

// POSIX.1-2001, 4.3BSD, SVr4.
pid_t getpid(void);
pid_t getppid(void);

gid_t getgid(void);


int dup(int oldfd);
int dup2(int oldfd, int newfd);
int dup3(int oldfd, int newfd, int flags);

// nice - change process priority
int nice(int inc);

int pause(void);


//SVr4, BSD, POSIX.1-2001.
int mkdir(const char *pathname, mode_t mode);

//rmdir - delete a	directory
// SVr4, 4.3BSD, POSIX.1-2001.
int rmdir(const char *pathname);

//link - make a new name for a file
// SVr4, 4.3BSD, POSIX.1-2001 (but see NOTES).
int link(const char *oldpath, const char *newpath);


//sysconf - get configuration information at run time
//  POSIX.1-2001.
long sysconf(int name);

// fsync,  fdatasync  -  synchronize  a  file's in-core state with storage device
//4.3BSD, POSIX.1-2001.
int fsync(int fd);
int fdatasync(int fd);

//fpathconf, pathconf - get configuration values for files
//POSIX.1-2001.
long fpathconf(int fd, int name);
long pathconf(char *path, int name);

//SVr4, 4.3BSD, POSIX.1-2001.
int close (int fd);

//POSIX.1-2001, POSIX.1-2008.
int pipe ( int pipefd[2] );





#endif /* _UNISTD_H */

