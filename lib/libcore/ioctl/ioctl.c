 
 
//#include <sys/types.h>   
#include <sys/ioctl.h>

#include <stdarg.h>

//#include <termios.h>


/*
  The ioctl() system call manipulates the underlying device parameters
       of special files.  In particular, many operating characteristics of
       character special files (e.g., terminals) may be controlled with
       ioctl() requests. 
 */


/*
 *************************************************
 * ioctl:
 *     #importante.
 */

//See: http://man7.org/linux/man-pages/man2/ioctl.2.html

/*
    EBADF  fd is not a valid file descriptor.
    EFAULT argp references an inaccessible memory area.
    EINVAL request or argp is not valid.
    ENOTTY fd is not associated with a character special device.
    ENOTTY The specified request does not apply to the kind of object
              that the file descriptor fd references.
*/

//int ioctl ( int d, int request, ... )
int ioctl (int fd, unsigned long request, ...){

	//printf ("ioctl: todo\n");
    //return -1;
    
    va_list ap;
    va_start(ap, request);
    unsigned arg = va_arg(ap, unsigned long);
    
    //kvprintf ( fmt, xxxputchar, NULL, 10, ap );
    
    gramado_system_call ( 8000,
        (unsigned long) fd,
        (unsigned long) request,
        (unsigned long) arg );
    
    va_end (ap);
    
    
    //#todo: pegar o retorno da systemcall
    //errno = 0;
    return 0;
}


/*
 * Credits: Serenity OS;
int ioctl(int fd, unsigned request, ...);
int ioctl(int fd, unsigned request, ...)
{
    va_list ap;
    va_start(ap, request);
    unsigned arg = va_arg(ap, unsigned);
    int rc = syscall(SC_ioctl, fd, request, arg);
    __RETURN_WITH_ERRNO(rc, rc, -1);
}
*/



 
 
 
