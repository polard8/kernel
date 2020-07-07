/*
 * File: fcntl.c
 * 
 * 2020 - Created by Fred Nora.
 */


#include <stddef.h>
#include <types.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
// ...

//used for flock()
#include <sys/file.h>



/*
 ******************************
 * fcntl:
 *
 */

int fcntl ( int fd, int cmd, ... )
{
    debug_print("fcntl: [TODO]\n");


    if (fd<0) {
        debug_print("fcntl: fd\n");
        return -1;
    }

    //#todo:
    
    /*
    va_list ap;
    va_start(ap, options);
    //x = va_arg (ap, unsigned);
    va_end(ap);
    
    return gramado_system_call ( ?, fd, cmd,  0 );
    */
  
    return -1; //#todo
}



int openat (int dirfd, const char *pathname, int flags){

    int __ret = -1;


    // #todo:
    // firfd, Flags.
    
    //todo
    //if ( dirfd < 0 ){ return -1; }
    
    
    if (!pathname) {
        //errno = EFAULT;
        return -1;
    }
    
    // Carrega um arquivo dado o nome e um modo.
   __ret = (int) gramado_system_call ( 246, 
                     (unsigned long) pathname, 
                     (unsigned long) flags,      // ??mode
                     (unsigned long) flags );    // ??mode

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

int open (const char *pathname, int flags, mode_t mode){

    int __fd = -1;


    //#bugbug
    // desse jeito não teremos um buffer em ring3. ??
    //return (int) gramado_system_call ( 16, 
      //               (unsigned long) pathname, 
      //               (unsigned long) flags, 
      //               (unsigned long) mode );
      

    //
    // size
    //
    
    stdio_fntos( (char *) pathname);
    
    // get file size
    size_t s = (size_t) gramado_system_call ( 178, 
                            (unsigned long) pathname,
                            0,
                            0 );
    
    
    if ( s <= 0 || s > 1024*1024 ){
        printf ("open: size\n");
        return -1;
    }


    // load the file into the address.
    // O arquivo será carregado no buffer em ring0,
    // A chamada não oferecerá um endereço em ring3,
    // pois não dá pra confiar na biblioteca,
    // o kernel não pode confiar na qualidade da libc.
    
    
    //IN: service, name, address, 0, 0 

    __fd = (int) gramado_system_call ( 3,  
                     (unsigned long) pathname, 
                     (unsigned long) flags,  
                     (unsigned long) mode );

    if (__fd < 0){
        printf ("open: Couldn't load the file. fd fail.\n");
        return -1;
    }


     // retornamos o fd do arquivo para fopen usar e colocar
     // numa stream ?
     
     return (int) __fd;
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
    return open (pathname, O_CREAT|O_WRONLY|O_TRUNC, mode);
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






