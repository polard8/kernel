

#ifndef ____FCNTL_H
#define ____FCNTL_H    1



/* These values are used for cmd in fcntl().  POSIX Table 6-1.  */
#define F_DUPFD            0	/* duplicate file descriptor */
#define F_GETFD            1	/* get file descriptor flags */
#define F_SETFD            2	/* set file descriptor flags */
#define F_GETFL            3	/* get file status flags */
#define F_SETFL            4	/* set file status flags */
#define F_GETLK            5	/* get record locking information */
#define F_SETLK            6	/* set record locking information */
#define F_SETLKW           7	/* set record locking info; wait if blocked */
#define F_FREESP           8	/* free a section of a regular file */
// ...


/* File descriptor flags used for fcntl().  POSIX Table 6-2. */
#define FD_CLOEXEC         1	/* close on exec flag for third arg of fcntl */


/* L_type values for record locking with fcntl().  POSIX Table 6-3. */
#define F_RDLCK            1	/* shared or read lock */
#define F_WRLCK            2	/* exclusive or write lock */
#define F_UNLCK            3	/* unlock */


//
//  O_
//

// 'O_' flags.
// #atention:
// It needs to have same value found in the libc03.


/* File access modes for open() and fcntl().  POSIX Table 6-6. */
#define O_RDONLY           0	/* open(name, O_RDONLY) opens read only */
#define O_WRONLY           1	/* open(name, O_WRONLY) opens write only */
#define O_RDWR             2	/* open(name, O_RDWR) opens read/write */

/* Mask for use with file access modes.  POSIX Table 6-7. */
#define O_ACCMODE         03	/* mask for file access modes */



// #define	O_NONBLOCK	0x00000004	/* no delay */
// #define	O_APPEND	0x00000008	/* set append mode */
//#define	O_SHLOCK	0x00000010	/* open with shared file lock */
//#define	O_EXLOCK	0x00000020	/* open with exclusive file lock */
#define  O_ASYNC  0x00000040	/* signal pgrp when data ready */
// #define	O_SYNC		0x00000080	/* synchronous writes */


/* don't follow symlinks on the last */
/* path component */
//#define	O_NOFOLLOW	0x00000100	


/* Oflag values for open().  POSIX Table 6-4. */
#define O_CREAT        00100	/* creat file if it doesn't exist */
#define O_EXCL         00200	/* exclusive use flag */
#define O_NOCTTY       00400	/* do not assign a controlling terminal */
#define O_TRUNC        01000	/* truncate flag */

/* File status flags for open() and fcntl().  POSIX Table 6-5. */
#define O_APPEND       02000	/* set append mode */
#define O_NONBLOCK     04000	/* no delay */

/* automatically re-open device after driver restart */
#define O_REOPEN      010000

#define	O_ALT_IO	0x00040000	/* use alternate i/o semantics */
#define	O_DIRECT	0x00080000	/* direct I/O hint */


#define  O_DIRECTORY  0x00200000  /* fail if not a directory */
#define  O_CLOEXEC    0x00400000  /* set close on exec */


/* Struct used for locking.  POSIX Table 6-8. */

struct flock {

    short l_type;    // type: F_RDLCK, F_WRLCK, or F_UNLCK 
    short l_whence;  // flag for starting offset 
    off_t l_start;   // relative offset in bytes 
    off_t l_len;     // size; if 0, then until EOF 
    pid_t l_pid;     // process id of the locks' owner 

};




#endif  //____FCNTL_H


//
// End.
//










