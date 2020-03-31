/*
 * File: signal.c
 *
 */


#include <sys/types.h>
#include <errno.h>

#include <signal.h>
//system calls.
#include <stubs/gramado.h> 



const char *sys_siglist[NSIG] = {
    "Invalid signal number",
    "Hangup",
    "Interrupt",
    "Quit",
    "Illegal instruction",
    "Trap",
    "Aborted",
    "Bus error",
    "Division by zero",
    "Killed",
    "User signal 1",
    "Segmentation violation",
    "User signal 2",
    "Broken pipe",
    "Alarm clock",
    "Terminated",
    "Stack fault",
    "Child exited",
    "Continued",
    "Stopped (signal)",
    "Stopped",
    "Stopped (tty input)",
    "Stopped (tty output)",
    "Urgent I/O condition)",
    "CPU limit exceeded",
    "File size limit exceeded",
    "Virtual timer expired",
    "Profiling timer expired",
    "Window changed",
    "I/O possible",
    "Power failure",
    "Bad system call",
};




/*
 **************************
 * signal:
 *     POSIX.1-2001, POSIX.1-2008, C89, C99.
 */

    //#todo
    
sighandler_t signal (int signum, sighandler_t handler){

    sighandler_t __ret;


    debug_print ("signal: [TODO] \n");

    /*
    ret = (sighandler_t) gramado_system_call ( ?, ?, ?, ? );

    if (ret == SIG_ERR)
	{
		errno = EINVAL;
		return (SIG_ERR);
	}
	
	return (ret);
	*/

    return handler;  //#todo
}


/*
 * sigaction:
 *
 */

int 
sigaction ( 
    int signum, 
    const struct sigaction *act,
    struct sigaction *oldact )
{
    debug_print ("sigaction: [TODO] \n");
    return -1; //#todo
}


// #todo
// Sends a signal to a process or a process group.
int kill (pid_t pid, int sig){


    debug_print ("kill: [TODO] \n");

	// #todo
	/*
	int ret;
	
	ret = (int) gramado_system_call ( ?, ?, ?, ? );
	
    if (ret < 0)
	{
		errno = -ret;
		return (-1);
	}
	
	return (ret);
	*/
	
	return -1;
}


int raise (int sig)
{
    // FIXME: Support multi-threaded programs.
    return kill ( getpid(), sig);
}



int sigismember (const sigset_t* set, int signum){

    if (signum < 1 || signum > 32) {
        errno = EINVAL;
        return -1;
    }

    if (*set & (1 << (signum - 1)))
        return 1;

    return 0;
}


int killpg (int pgrp, int sig)
{
    debug_print ("killpg: [TODO] \n");
	return -1;
}


// ?? 
int sigemptyset (sigset_t *set)
{
    *set = 0;
    return 0;
}


// ??
int sigfillset (sigset_t *set)
{
    *set = 0xffffffff;
    return 0;
}



int sigaddset (sigset_t *set, int signum){

    if (signum < 1 || signum > 32) {
        errno = EINVAL;
        return -1;
    }

    *set |= 1 << (signum - 1);

    return 0;
} 



int sigdelset (sigset_t *set, int signum){

    if (signum < 1 || signum > 32) {
        errno = EINVAL;
        return -1;
    }
    *set &= ~(1 << (signum - 1));
    return 0;
}



/*
void psignal(int sig, const char *s);
void psignal(int sig, const char *s)
{}
*/



/*
void psiginfo (const siginfo_t *si, const char *s);
void psiginfo (const siginfo_t *si, const char *s)
{
    psignal (si->si_signo, s);
}
*/



//
// End.
//


