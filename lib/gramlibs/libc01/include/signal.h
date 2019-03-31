
//signal.h 
//signal - ANSI C signal handling
//credits: 
//http://man7.org/linux/man-pages/man2/signal.2.html
//http://man7.org/linux/man-pages/man2/sigaction.2.html
//...


#ifndef _SIGNAL_H_
#define _SIGNAL_H_

#include <sys/types.h>

/* Cygwin defines it's own sigset_t in include/cygwin/signal.h */
//#ifndef __CYGWIN__
//typedef unsigned long sigset_t;
//#endif

typedef unsigned int sigset_t;

/* Type of a signal handler.  */
typedef void (*sighandler_t)(int);

typedef sighandler_t __sighandler_t;
typedef sighandler_t sig_t;
//...



//============


/* Type for data associated with a signal.  */
/* Data passed with notification */
typedef union sigval {          
     int     sival_int;         /* Integer value */
     void   *sival_ptr;         /* Pointer value */
}sigval_t;

typedef sigval_t __sigval_t;
//...

struct sigevent 
{
    int          sigev_notify; /* Notification method */
    int          sigev_signo;  /* Notification signal */
    
	union sigval sigev_value;  /* Data passed with
                                         notification */
    void       (*sigev_notify_function) (union sigval);
                            /* Function used for thread
                               notification (SIGEV_THREAD) */
    void        *sigev_notify_attributes;
                            /* Attributes for notification thread
                               (SIGEV_THREAD) */
    pid_t        sigev_notify_thread_id;
                           /* ID of thread to signal (SIGEV_THREAD_ID) */
};

typedef struct siginfo {
    int      si_signo;     /* Signal number */
    int      si_errno;     /* An errno value */
    int      si_code;      /* Signal code */
    int      si_trapno;    /* Trap number that caused hardware-generated signal (unused on most architectures) */
    pid_t    si_pid;       /* Sending process ID */
    uid_t    si_uid;       /* Real user ID of sending process */
    int      si_status;    /* Exit value or signal */
    clock_t  si_utime;     /* User time consumed */
    clock_t  si_stime;     /* System time consumed */
    sigval_t si_value;     /* Signal value */
    int      si_int;       /* POSIX.1b signal */
    void    *si_ptr;       /* POSIX.1b signal */
    int      si_overrun;   /* Timer overrun count;
                                         POSIX.1b timers */
    int      si_timerid;   /* Timer ID; POSIX.1b timers */
    void    *si_addr;      /* Memory location which caused fault */
    long     si_band;      /* Band event (was int in
                                         glibc 2.3.2 and earlier) */
    int      si_fd;        /* File descriptor */
    short    si_addr_lsb;  /* Least significant bit of address
                                         (since Linux 2.6.32) */
    void    *si_lower;     /* Lower bound when address violation
                                         occurred (since Linux 3.19) */
    void    *si_upper;     /* Upper bound when address violation
                                         occurred (since Linux 3.19) */
    int      si_pkey;      /* Protection key on PTE that caused
                                         fault (since Linux 4.6) */
    void    *si_call_addr; /* Address of system call instruction
                                         (since Linux 3.5) */
    int      si_syscall;   /* Number of attempted system call
                                         (since Linux 3.5) */
    unsigned int si_arch;  /* Architecture of attempted system call
                                         (since Linux 3.5) */
}siginfo_t ;


typedef struct sigaction {
	
    void  (*sa_handler)(int);
    void  (*sa_sigaction)(int, siginfo_t *, void *);
    sigset_t  sa_mask;
    int  sa_flags;
    void  (*sa_restorer)(void);
}sigaction_t;

#ifndef _POSIX_SOURCE
#define SA_ONSTACK	0x0001	/* take signal on signal stack */
#define SA_RESTART	0x0002	/* do not restart system on signal return */
#endif
#define SA_NOCLDSTOP	0x0004	/* do not generate SIGCHLD on child stop */

/*
 * Flags for sigprocmask:
 */
#define	SIG_BLOCK	1	/* block specified signal set */
#define	SIG_UNBLOCK	2	/* unblock specified signal set */
#define	SIG_SETMASK	3	/* set specified signal set */




#ifndef _POSIX_SOURCE
/*
 * 4.3 compatibility:
 * Signal vector "template" used in sigvec call.
 */
struct	sigvec {
	void	(*sv_handler)();	/* signal handler */
	int	sv_mask;		/* signal mask to apply */
	int	sv_flags;		/* see signal options below */
};

#define SV_ONSTACK	SA_ONSTACK
#define SV_INTERRUPT	SA_RESTART	/* same bit, opposite sense */
#define sv_onstack sv_flags	/* isn't compatibility wonderful! */

/*
 * Structure used in sigaltstack call.
 */
struct	sigaltstack {
	char	*ss_base;		/* signal stack base */
	int	ss_len;			/* signal stack length */
	int	ss_onstack;		/* current status */
};

/*
 * Structure used in sigstack call.
 */
struct	sigstack {
	char	*ss_sp;			/* signal stack pointer */
	int	ss_onstack;		/* current status */
};

/*
 * Information pushed on stack when a signal is delivered.
 * This is used by the kernel to restore state following
 * execution of the signal handler.  It is also made available
 * to the handler to allow it to restore state properly if
 * a non-standard exit is performed.
 */
struct	sigcontext {
	int	sc_onstack;		/* sigstack state to restore */
	int	sc_mask;		/* signal mask to restore */
	int	sc_sp;			/* sp to restore */
	int	sc_fp;			/* fp to restore */
	int	sc_ap;			/* ap to restore */
	int	sc_pc;			/* pc to restore */
	int	sc_ps;			/* psl to restore */
};

/*
 * Macro for converting signal number to a mask suitable for
 * sigblock().
 */
#define sigmask(m)	(1 << ((m)-1))

#define	BADSIG		(void (*)())-1
#endif	/* _POSIX_SOURCE */

//POSIX.1-2001, POSIX.1-2008, C89, C99.
sighandler_t signal (int signum, sighandler_t handler);

int sigaction ( int signum, const struct sigaction *act,
                struct sigaction *oldact );

#endif

