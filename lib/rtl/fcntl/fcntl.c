/*
 * File: fcntl.c
 * 
 * 2020 - Created by Fred Nora.
 */

#include <sys/ioctl.h>
#include <stdarg.h>
#include <stddef.h>
#include <types.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/file.h>

#include <stdio.h>
#include <rtl/gramado.h>


int fcntl ( int fd, int cmd, ... )
{
    int __ret = -1;

    if (fd<0) {
        debug_print("fcntl: fd\n");
        return -1;
    }

    //++
    va_list ap;
    va_start(ap, cmd);
    unsigned arg = va_arg(ap,int);

    //__ret = (int) gramado_system_call ( 8001,
    //                  (unsigned long) fd,
    //                  (unsigned long) cmd,
    //                  (unsigned long) arg );

    // # This way we're gonna have full access 
    // to the ring 0 data structures.

    __ret = (int) sc82 ( 
                      8001,
                      (unsigned long) fd,
                      (unsigned long) cmd,
                      (unsigned long) arg );

    va_end(ap);
    //--    

    // #todo Error.
    if (__ret < 0)
    {
        //errno = -__ret;
        return (-1);
    }

    return (int) (__ret);
}

// openat - open a file relative to a directory file descriptor 
// See: https://linux.die.net/man/2/openat

int openat (int dirfd, const char *pathname, int flags)
{
    int __ret = -1;

    // The directory
    if ( dirfd < 0 ){ 
        debug_print("openat: [FAIL] dirfd\n");
        return -1; 
    }
    
    // path
    if (!pathname) {
        debug_print("openat: [FAIL] pathname\n");
        //errno = EFAULT;
        return -1;
    }
    
    // Carrega um arquivo dado o nome e um modo.

    __ret = (int) gramado_system_call ( 
                      246, 
                      (unsigned long) dirfd, 
                      (unsigned long) pathname, 
                      (unsigned long) flags ); 

    if ( __ret < 0 ){ 
        debug_print("openat: [FAIL]\n");
        //errno = EFAULT;
        return -1; 
    }

    return (int) __ret;
}


/*
 **********************
 * open:
 *
 */

// #obs
// Isso precisa abrir um arquivo, colocar o ponteiro na 
// lista de arquivos abertos e retornar o índice. 

int open (const char *pathname, int flags, mode_t mode)
{
    int fd = -1;
    char tmp_path[64];

    // #importante
    // adaptando para fat16.
    // #todo: devemos fazer isso em ring0, não aqui.
    // isso funcionou.

    stdio_fntos( (char *) pathname );
    sprintf(tmp_path,pathname);

//
// Size
//

    // Get file size.
    // Limits: 1MB.
    
    /*
    FileSize = (size_t) gramado_system_call ( 178, 
                            (unsigned long) tmp_path, 0, 0 );

    if ( FileSize <= 0 || FileSize >= (1024*1024) )
    {
        printf ("open: [FAIL] FileSize\n");
        return (int) (-1);
    }
    */


    // Load the file into the address.
    // O arquivo será carregado no buffer em ring0,
    // A chamada não oferecerá um endereço em ring3,
    // pois não dá pra confiar na biblioteca,
    // o kernel não pode confiar na qualidade da libc.

    // IN: 
    // service, pathname, flags, mode 

    fd = (int) gramado_system_call ( 
                   16,  
                   (unsigned long) tmp_path, 
                   (unsigned long) flags, 
                   (unsigned long) mode );

    if (fd < 0){
        printf ("open: [FAIL]\n");
        return (int) (-1);
    }

    // fopen() needs this. 
    return (int) fd;
}


//#test
/*
int __open2(const char* path, int options, ...);
int __open2(const char* path, int options, ...)
{
    if (!path) {
        errno = EFAULT;
        return -1;
    }
    
    va_list ap;
    va_start(ap, options);
    auto mode = (mode_t)va_arg(ap, unsigned);
    va_end(ap);
    
    return openat ( path, options );
}
*/


/*
 **********************************
 * creat:
 *     Linux klibc style.
 */

int creat (const char *pathname, mode_t mode)
{
    return (int) open (pathname, O_CREAT|O_WRONLY|O_TRUNC, mode);
}


/*
// MINIX 3
int flock(int fd, int mode);
int flock(int fd, int mode)
{
  struct flock lck;

  memset((void *) &lck, 0, sizeof(struct flock));
  switch (mode & ~LOCK_NB) {
  case LOCK_SH: lck.l_type = F_RDLCK; break;
  case LOCK_EX: lck.l_type = F_WRLCK; break;
  case LOCK_UN: lck.l_type = F_UNLCK; break;
  default: errno = EINVAL; return -1;
  }
  return fcntl(fd, mode & LOCK_NB ? F_SETLK : F_SETLKW, &lck);
}
*/


/*
 ********************
 * flock:
 * 
 * 
 */
 
// #todo: It's a wrapper.
// Lock operation using fcntl()
// See: sys/file.h
int flock (int fd, int operation)
{
    debug_print("flock: [TODO]\n");
    return -1;
}


//
// End.
//

