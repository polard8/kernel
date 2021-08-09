
// ioctl.c

#include <sys/ioctl.h>
#include <stdarg.h>

#include <stdio.h>

#include <rtl/gramado.h>


/*
  The ioctl() system call manipulates the 
  underlying device parameters of special files.  
  In particular, many operating characteristics of
  character special files (e.g., terminals) may be controlled with
  ioctl() requests. 
 */


/*
 *************************************************
 * ioctl:
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

int ioctl (int fd, unsigned long request, ...)
{
    int __ret = -1;

    if (fd<0) {
        debug_print("ioctl: fd\n");
        return -1;
    }

    //++
    va_list ap;
    va_start(ap, request);
    unsigned arg = va_arg(ap, unsigned long);
    

    //__ret = (int) gramado_system_call ( 8000,
    //                  (unsigned long) fd,
    //                  (unsigned long) request,
    //                  (unsigned long) arg );
    
    // # Using this syscall to have full access to the ring0 data.

    __ret = (int) sc82 ( 
                      8000,
                      (unsigned long) fd,
                      (unsigned long) request,
                      (unsigned long) arg );

    va_end (ap);
    //--

    // #todo Error.
    if (__ret < 0)
    {
        //errno = -__ret;
        return (-1);
    }

    return (int) (__ret);
}

