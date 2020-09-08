/*
 * File: unistd.c
 *
 *     Unix standard.
 *     ... and maybe posix stuff.
 * 
 * History:
 *     2019 - Created by Fred Nora.
 *     2020 - New functions.
 */


#include <sys/types.h>  
#include <sys/socket.h>
#include <sys/mman.h>

#include <fcntl.h>
#include <sys/stat.h>   

#include <fcntl.h>
#include <unistd.h>
#include <limits.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <pty.h>
#include <utmp.h>

#include <sys/ioctl.h>
#include <sys/ioctls.h>

#include <termios.h>
#include <sys/utsname.h>


// System calls.
#include <stubs/gramado.h> 




#define  UNISTD_SYSTEMCALL_FORK     71  
#define  UNISTD_SYSTEMCALL_EXIT     70
#define  UNISTD_SYSTEMCALL_GETPID   85
#define  UNISTD_SYSTEMCALL_GETPPID  81
//#define	UNISTD_SYSTEMCALL_GETGID ??
// ...


    //
    // Error.
    //

// Number of last error.
// Maybe errno.c is a better place for this. 
int errno = 0;


// The <unistd.h> header shall declare 
// the following external variables:
char *optarg;
int opterr, optind, optopt;



// unistd ?
/* 
pid_t tcgetpgrp(int fd)
{
    return ioctl(fd, TIOCGPGRP);
}
*/

// unistd ?
/*
int tcsetpgrp(int fd, pid_t pgid)
{
    return ioctl(fd, TIOCSPGRP, pgid);
} 
*/ 




/*
 ************************************************
 * execv:
 * 
 */

// #todo
// Testar essa rotina usando a variável **environ. 

char *__execv_environ[] = { NULL, NULL, NULL };

int execv (const char *path, char *const argv[] )
{
    // #bugbug: Falta a tipagem do último argumento??
    return execve ( path, (char **) argv, __execv_environ );
    //return execve ( path, (char **) argv, (char **) __execv_environ );
    //return execve ( path, (char **) argv, environ ); //#todo: use this one.
}



/*
 ******************************* 
 * execve:
 * 
 */

int 
execve ( 
    const char *path, 
    char *const argv[], 
    char *const envp[] )
{
    int __ret = -1;


    __ret = (int) gramado_system_call ( 248, 
                      (unsigned long) path, 
                      (unsigned long) argv,   
                      (unsigned long) envp );  

    //Error.
    if (__ret < 0)
    {
        // errno = -__ret;  //#todo: Enable this thing.
        return (-1);
    } 

    return (__ret);
}



ssize_t read_tty (int fd, const void *buf, size_t count)
{
    if (fd<0)
        return -1;

    return (ssize_t) gramado_system_call ( 272, 
                         (unsigned long) fd,      // dispositivo.
                         (unsigned long) buf, 
                         (unsigned long) count ); 
}


// o descritor seleciona uma tty em ttyList[]
ssize_t write_tty (int fd, const void *buf, size_t count)
{
    if (fd<0)
        return -1;

    return (ssize_t) gramado_system_call ( 273, 
                         (unsigned long) fd,      // dispositivo.
                         (unsigned long) buf, 
                         (unsigned long) count ); 
}




// read on virtual console!
// range: 0 ~ 3
ssize_t read_VC (int fd, const void *buf, size_t count)
{
    if (fd<0)
        return -1;

    return (ssize_t) gramado_system_call ( 262, 
                         (unsigned long) fd,      // dispositivo.
                         (unsigned long) buf, 
                         (unsigned long) count ); 

}


// write on virtual console!
// range: 0 ~ 3
ssize_t write_VC (int fd, const void *buf, size_t count)
{
    if (fd<0)
        return -1;

    return (ssize_t) gramado_system_call ( 263, 
                         (unsigned long) fd,      // dispositivo.
                         (unsigned long) buf, 
                         (unsigned long) count ); 
}



/*
 ********************************
 * read:
 *     Standard read() function.
 */
// Usam a lista de arquivos abertos do processo.
ssize_t read (int fd, const void *buf, size_t count){

    if (fd<0){
        debug_print ("read: fd\n");
        return -1;
    }

    return (ssize_t) gramado_system_call ( 18, 
                         (unsigned long) fd,
                         (unsigned long) buf, 
                         (unsigned long) count ); 
}



/*
 ********************************************
 * write: 
 *     Standard write() function. 
 */
// Usam a lista de arquivos abertos do processo. 
ssize_t write (int fd, const void *buf, size_t count){

    if (fd<0){
        debug_print ("write: fd\n");
        return -1;
    }

    return (ssize_t) gramado_system_call ( 19, 
                         (unsigned long) fd,
                         (unsigned long) buf, 
                         (unsigned long) count ); 
}


ssize_t pread (int fd, void *buf, size_t count, off_t offset)
{
    debug_print ("pread: [TODO]\n");

    if (fd<0){
        debug_print ("pread: fd\n");
        return -1;
    }

    return -1;

    /*   
    // Credits: Serenity OS. 
    // FIXME: This is not thread safe and should be implemented in the kernel instead.
    off_t old_offset = lseek(fd, 0, SEEK_CUR);
    lseek(fd, offset, SEEK_SET);
    ssize_t nread = read(fd, buf, count);
    lseek(fd, old_offset, SEEK_SET);
    return nread;
    */
}


ssize_t 
pwrite (
    int fd, 
    const void *buf, 
    size_t count, 
    off_t offset )
{

    if (fd<0){
        debug_print ("pwrite: fd\n");
        return -1;
    }

    debug_print ("pwrite: [TODO]\n");
    return -1;
}



int truncate(const char *path, off_t length)
{ 
    debug_print ("truncate: [TODO]\n");
    return -1;
}


int ftruncate (int fd, off_t length)
{ 

    if (fd<0){
        debug_print ("ftruncate: fd\n");
        return -1;
    }
        
    debug_print ("ftrucate: [TODO]\n");
    return -1;
}


/*
 *************************************
 * exit:
 *     Torna zombie a thread atual.
 *     Mas o propósito é terminar sair do 
 *     programa, terminando o processo e
 *     liberar os recursos que o processo estava usando.
 *     #importante:
 *     @todo: se o status for (1) devemos imprimir o conteúdo 
 * de stderr na tela.
 * ?? Essa função também pertence à unistd
 */

// cause normal process termination


// Remember: The parent process called wait().
// The exit() function causes normal process termination and the value
// of status & 0xFF is returned to the parent.

void exit (int status)
{

    debug_print ("exit:\n");

    // #todo
    // Chamar rotina para finalizar a biblioteca.
    // Liberando os recursos usados.

    // #importante:
    // #todo: 
    
    // ??
    // Se o status for (1) devemos imprimir o conteúdo 
    // de stderr na tela.

    //if(status==1)
        //printf(stderr);


    // 70
    gramado_system_call ( UNISTD_SYSTEMCALL_EXIT, 
        (unsigned long) status, 
        (unsigned long) status, 
        (unsigned long) status );
    

    // Wait forever.

    while (1){ asm ("pause"); };
}




/*
 **************
 * fork:
 *     #define  UNISTD_SYSTEMCALL_FORK     71  
 */

pid_t fork (void)
{
    pid_t __ret = -1;

    debug_print("fork: \n");

    __ret = (pid_t) gramado_system_call ( UNISTD_SYSTEMCALL_FORK, 
                        0, 0, 0 );
    
    if (__ret<0)
    {
        debug_print("fork: [FAIL]\n");
        //errno = -__ret;
        return (__ret);
    }

    debug_print("fork: Done\n");
    return (__ret);
}





/*
 * setuid:
 *
 */

// SVr4,  POSIX.1-2001.   
// Not quite	compatible with	the 4.4BSD call, which
// sets all	of the real, saved, and	effective user IDs.	  

int setuid ( uid_t uid ){
	
	//#todo: ainda não temos a suystem call.
	//SYSTEMCALL_SETCURRENTUSERID
	return (uid_t) gramado_system_call ( 151, 0, 0, 0 );
}


uid_t getuid (void)
{
    return (uid_t) gramado_system_call ( 152, 0, 0, 0 );
}


uid_t geteuid (void)
{
    debug_print ("geteuid: [TODO]\n");
    return -1;
	//return (uid_t) gramado_system_call ( ?, 0, 0, 0 );
} 




/*
 * getpid:
 *
 */

pid_t getpid (void){
	
	return (pid_t) gramado_system_call ( UNISTD_SYSTEMCALL_GETPID, 0, 0, 0 );
}


/*
 * getppid:
 *
 */

pid_t getppid (void){

	return (pid_t) gramado_system_call ( UNISTD_SYSTEMCALL_GETPPID, 0, 0, 0 );
}



/*
The function tcgetpgrp() returns the process group ID of the 
foreground process group on the terminal associated to fd, 
which must be the controlling terminal of the calling process. 
See: https://linux.die.net/man/3/tcsetpgrp
*/
pid_t tcgetpgrp (int fd){

    int s=0;

    //#todo: work in ring0 to implement this.
    if ( ioctl(fd, TIOCGPGRP, &s) < 0 ){
        debug_print ("tcgetpgrp: error\n");
        return ((pid_t)-1);
    }

    return ((pid_t) s);
}


/*
The function tcsetpgrp() makes the process group with process 
group ID pgrp the foreground process group on the terminal 
associated to fd, which must be the controlling terminal 
of the calling process, and still be associated with its session. 
Moreover, pgrp must be a (nonempty) process group belonging 
to the same session as the calling process.   
See: https://linux.die.net/man/3/tcsetpgrp 
 */
int tcsetpgrp (int fd, pid_t pgrp){

    int s=0;
    s = pgrp;

    //#todo: work in ring0 to implement this.
    return ( ioctl(fd, TIOCSPGRP, &s) );
}

int setpgid(pid_t pid, pid_t pgid)
{
    debug_print ("setpgid: [TODO]\n");

    if(pid<0)
        debug_print ("setpgid: pid\n");
        
    return -1;
}


pid_t getpgid(pid_t pid)
{
    debug_print ("getpgid: [TODO]\n");

    if(pid<0)
        debug_print ("getpgid: pid\n");
        
    return -1;
}



/*
 * getgid:
 *
 */

gid_t getgid (void)
{
	//SYSTEMCALL_GETCURRENTGROUPID

    return (gid_t) gramado_system_call ( 154, 0, 0, 0 );
}



/* POSIX.1 version */
pid_t getpgrp(void)
{
    debug_print ("getpgrp: [TODO]\n");
    return -1;
}


/* BSD version */
pid_t bsd_getpgrp(pid_t pid)
{
    debug_print ("bsd_getpgrp: [TODO]\n");

    if(pid<0)
        debug_print ("bsd_getpgrp: pid\n");
    
    return -1;
}


char *getcwd(char *buf, size_t size)
{
    debug_print ("getcwd: [TODO]\n");

    /*
    if (!buffer) {
        size = size ? size : PATH_MAX;
        buffer = (char*)malloc(size);
    }
    */
        
    return (char *) 0;
}


char *getwd(char *buf)
{
    debug_print ("getwd: [TESTING]\n");
    
    char *p = getcwd(buf, PATH_MAX);
    
    return (char *) p;
}


char *get_current_dir_name(void)
{
    debug_print ("get_current_dir_name: [TODO]\n");
    return (char *) 0;
}



/*
int gettid()
{
    //todo: use syscall!!
}
*/


/*
void sysbeep()
{
    //todo: use syscall!!
}
*/



/*
 *************************************
 * dup:
 *
 */

int dup (int oldfd){

    //if ( oldfd < 0 ) 
        //return -1;

    return (int) gramado_system_call ( (unsigned long) oldfd, 
                     0, 0, 0 );
}


/*
 * dup2:
 *
 */

int dup2 (int oldfd, int newfd){

    //if ( oldfd < 0 ) 
        //return -1;

    return (int) gramado_system_call ( (unsigned long) oldfd, 
                     (unsigned long) newfd, 0, 0 );
}


/*
 * dup3:
 *
 */

int dup3 (int oldfd, int newfd, int flags){

    //if ( oldfd < 0 ) 
        //return -1;

    //if ( newfd < 0 ) 
        //return -1;

    return (int) gramado_system_call ( (unsigned long) oldfd, 
                     (unsigned long) newfd, 
                     (unsigned long) flags, 
                     0 );
}


// See: sys/resource.h
int getpriority (int which, id_t who)
{
    debug_print ("getpriority: [TODO]\n");
    return -1;
}


// See: sys/resource.h
int setpriority (int which, id_t who, int prio)
{
    debug_print ("setpriority: [TODO]\n");
    return -1;
}



/*
 ************************************
 * nice:
 *     Change process priority.
 */

// #todo:
// It looks very wasy to implement.

int nice (int inc)
{
    debug_print ("nice: [TODO]\n");
    return -1;    //#todo

    //#todo
    /*
    int prio;
	errno = 0;
	prio = getpriority(PRIO_PROCESS, 0);
	if (prio == -1 && errno)
		return -1;
	if (setpriority(PRIO_PROCESS, 0, prio + incr) == -1) {
		if (errno == EACCES)
			errno = EPERM;
		return -1;
	}
	return getpriority(PRIO_PROCESS, 0);
	*/
}


/*
 * pause:
 *
 */

int pause (void)
{
    debug_print ("pause: [TODO]\n");
    return -1; //#todo
}


/*
 * mkdir:
 *
 */

int mkdir (const char *pathname, mode_t mode)
{
    int __ret=0;


    debug_print ("mkdir: [TODO]\n");

    //gde_enter_critical_section();
    
    __ret = (int) gramado_system_call ( 44, 
                      (unsigned long) pathname, 0, 0);

    //gde_exit_critical_section();    

    return (int) __ret;
}


/*
 * rmdir:
 *
 */

int rmdir (const char *pathname)
{
    debug_print ("rmdir: [TODO]\n");
    return -1; //#todo
}


/*
 * link:
 *
 */

//Links a name to a file.

int link (const char *oldpath, const char *newpath)
{
    debug_print ("link: [TODO]\n");
	return -1; //#todo
}


//#todo.
int unlink (const char *pathname)
{
    debug_print ("unlink: [TODO]\n");
    return (int) (-1);
}


/*
 * mlock:
 *
 */

int mlock (const void *addr, size_t len)
{
    debug_print ("mlock: [TODO]\n");
	return -1; //#todo
}


/*
 * munlock:
 *
 */

int munlock (const void *addr, size_t len)
{
    debug_print ("munlock: [TODO]\n");
    return -1; //#todo
}


/*
 * mlockall:
 *
 */

int mlockall (int flags)
{
    debug_print ("mlockall: [TODO]\n");
    return -1; //#todo
}


/*
 * munlockall:
 *
 */

int munlockall (void)
{
    debug_print ("munlockall: [TODO]\n");
    return -1; //#todo
}


/*
 * sysconf:
 *
 */

long sysconf (int name)
{
    debug_print ("sysconf: [TODO]\n");
    return -1; //#todo
}


/*
 * fsync:
 *
 */

int fsync (int fd)
{
    debug_print ("fsync: [TODO]\n");
    
    if (fd<0){
        debug_print ("fsync: fd\n");
        return -1;
    }    
    
    return -1;    //#todo
}


/*
 * fdatasync:
 *
 */

int fdatasync (int fd)
{
    debug_print ("fdatasync: [TODO]\n");

    if (fd<0){
        debug_print ("fdatasync: fd\n");
        return -1;
    }    
    return -1; //#todo
}



// commit buffer cache to disk 
void sync(void)
{
    debug_print ("sync: [TODO]\n");
	//todo: use syscall!!
}


// commit buffer cache to disk 
int syncfs(int fd)
{
    debug_print ("syncfs: [TODO]\n");

    if (fd<0){
        debug_print ("syncfs: fd\n");
        return -1;
    }    
    
    return -1;
}





/*
 *****************************************
 * close:
 *    SVr4, 4.3BSD, POSIX.1-2001.
 */

// #obs
// Isso deve fechar o arquivo na lista de arquivo abertos.

// See:
// https://man7.org/linux/man-pages/man2/close.2.html

int close (int fd){

    int __ret = -1;


    
    if (fd<0){
        debug_print ("close: fd\n");
        return -1;
    }    
    
    __ret = (int) gramado_system_call ( 17, 
                     (unsigned long) fd, 
                     (unsigned long) fd, 
                     (unsigned long) fd );

    // #test
    if (__ret<0)
        errno = __ret;


    return (int) __ret;
}



int pipe2 ( int pipefd[2], int flags )
{
    return (int) gramado_system_call ( 247, 
                     (unsigned long) pipefd, 
                     (unsigned long) flags, 
                     (unsigned long) 0 );
}


/*
 ****************************************
 * pipe:
 *
 */

int pipe (int pipefd[2])
{
    return (int) pipe2(pipefd,0);
}


long fpathconf (int fildes, int name)
{
    debug_print ("fpathconf: [TODO]\n");
    return -1;
}


long pathconf (const char *pathname, int name)
{
    debug_print ("pathconf: [TODO]\n");
    return -1;
} 



/*
 **********************************
 * __gethostname:
 * 
 */

char __Hostname_buffer[64];
char *__gethostname (void)
{
    gramado_system_call ( 801, 
       (unsigned long) &__Hostname_buffer[0],
       (unsigned long) &__Hostname_buffer[0],
       (unsigned long) &__Hostname_buffer[0] );


    return __Hostname_buffer;
}


/*
 ******************************
 * gethostname
 * 
 * 
 */
 
//char *my__p;
//See: http://man7.org/linux/man-pages/man2/sethostname.2.html

// Passando para o kernel o buffer que está no app.

int gethostname (char *name, size_t len){

    int len_ret = -1;
    
    len_ret = (int) gramado_system_call ( 38, 
                        (unsigned long) name,
                        (unsigned long) name,
                        (unsigned long) name );
     
     return (int) len_ret;
}



//See: http://man7.org/linux/man-pages/man2/sethostname.2.html
int sethostname (const char *name, size_t len){

    return (int) gramado_system_call ( 39, 
                    (unsigned long) name,
                    (unsigned long) name,
                    (unsigned long) name );
}


/*
// minix 3
int __getlogin(char *logname, size_t sz);
int __getlogin(char *logname, size_t sz)
{
  struct passwd *pw_entry;

  pw_entry = getpwuid(getuid());

  if (pw_entry == (struct passwd *)NULL)
    return 0; 
    
  strncpy(logname, pw_entry->pw_name, sz);
  return sz;
}
*/




/*
 * getlogin: 
 * 
 */

char __Login_buffer[64];
char *getlogin (void)
{

    gramado_system_call ( 803, 
        (unsigned long) &__Login_buffer[0],
        (unsigned long) &__Login_buffer[0],
        (unsigned long) &__Login_buffer[0] );


    return __Login_buffer;
}



int setlogin (const char *name){

    //#todo: pegar retorno da função
    //return (int) 

    gramado_system_call ( 804, 
        (unsigned long) name,
        (unsigned long) name,
        (unsigned long) name );
       
    
    return 0; //poderia retornar o size.
}


/*
 **************************** 
 * getusername 
 * 
 */
 
// #todo
// usar  setlogin 
 
int getusername (char *name, size_t len){

    int __len_ret;


    if ( len < 0 || len > HOST_NAME_MAX )
    {
	    printf ("getusername: len\n");
	    return -1;
    }


    //coloca no buffer interno
    __len_ret = (int) gramado_system_call ( 40, 
                        (unsigned long) name,
                        (unsigned long) name,
                        (unsigned long) name );

	if ( __len_ret < 0 || __len_ret > HOST_NAME_MAX )
	{
	    printf ("getusername: __len_ret\n");
	    return -1;
	}

    if ( __len_ret > len ){
        __len_ret = len;
    }


    return 0;
}



/*
 **************************** 
 * setusername 
 * 
 */

// Um pequeno buffer foi passado pelo aplicativo.
// O limite precisa ser respeitado. 
 
// #todo
//usar  setlogin
 
int setusername (const char *name, size_t len){

    size_t __name_len = strlen(name) + 1;


    // Limite dado pelo sistema.
    if (len < 0 || len >= HOST_NAME_MAX )
    {
        printf ("setusername: *len\n");
        return 1;
    }


    // Tamanho indicado pelo aplicativo.
    if ( __name_len > len ){
        printf ("setusername: len\n");
        return 1;     
    }


    return (int) gramado_system_call ( 41, 
                    (unsigned long) name,
                    (unsigned long) name,
                    (unsigned long) name );
}




/*
 ************** 
 * ttyname:
 * 
 */
 
//POSIX.1-2001, POSIX.1-2008, 4.2BSD.
//ttyname, ttyname_r - return name of a terminal
//If the file descriptor filedes is associated with a terminal device, 
//the ttyname function returns a pointer to a statically-allocated, 
//null-terminated string containing the file name of the terminal file.
//The value is a null pointer if the file descriptor isn't associated 
//with a terminal, or the file name cannot be determined. 

// ok
// então o buffer para esse nome deve ficar aqui na libc em ring3
// Onde o app pode ler.
// Chamremos o kernel e diremos, coloque o nome aqui nesse buffer.
//char __ttyname_buffer[64];

char *ttyname (int fd){

    static char buf[PATH_MAX];
    int rv=0;
    
    if (fd<0){
        debug_print ("ttyname: fd\n");
        return (char *) 0;
    }    

    rv = (int) ttyname_r (fd, buf, sizeof(buf));

    if (rv != 0){
        errno = rv;
        return NULL;
    }


    return buf;
}


// POSIX.1-2001, POSIX.1-2008, 4.2BSD.
// ttyname, ttyname_r - return name of a terminal
int ttyname_r(int fd, char *buf, size_t buflen)
{ 
    debug_print ("ttyname_r: [TODO]\n");
    return -1; 
}


// #todo
// ??
/*
int ttyslot (void);
int ttyslot (void)
{
   return -1;
}
*/



/*
// Credits: Fred Nora
// Coloca a tty do processo no seguinte slot de arquivos abertos.
int ttyto( int fd);
int ttyto( int fd)
{
    return (int) gramado_system_call ( ?, 
                    (unsigned long) fd,
                    (unsigned long) fd,
                    (unsigned long) fd );
}
*/


// POSIX.1-2001, POSIX.1-2008, SVr4, 4.3BSD.
// isatty - test whether a file descriptor refers to a terminal
// This function returns 1 if filedes is a file descriptor associated 
// with an open terminal device, and 0 otherwise. 

int isatty (int fd)
{ 
    struct termios t;
    return ( tcgetattr(fd, &t) != -1 ); 
    //return ( tcgetattr(fd, &t) == 0);
}


int 
getopt (
    int argc, 
    char *const argv[], 
    const char *optstring )
{
    debug_print ("getopt: [TODO]\n");
    return -1;
}


//sys/stat.h
int fstat(int fd, struct stat *buf)
{
    debug_print ("fstat: [TODO]\n");

    if (fd<0){
        debug_print ("fstat: fd\n");
        return -1;
    }

    return (int) gramado_system_call ( 4005, 
                    (unsigned long) fd,
                    (unsigned long) buf,
                    (unsigned long) buf );
}


//sys/stat.h
int stat(const char *path, struct stat *buf)
{

    debug_print ("stat: [TODO]\n");
    
	int _fd = open(path, 0, 0);
	int ret = fstat(_fd, buf);
	close(_fd);

    return (int) ret;
}


//sys/stat.h
int lstat(const char *path, struct stat *buf)
{
    debug_print ("lstat: [TODO]\n");
    return (int) stat (path, buf);
}



// POSIX.1-2001, POSIX.1-2008, SVr4, 4.3BSD.
unsigned int alarm (unsigned int seconds)
{
    debug_print ("alarm: [TODO]\n");
    return -1;
}



int brk (void *addr)
{
    debug_print ("brk: [TODO]\n");
    return -1;
}


//#todo: definir o tipo intptr_t
/*
void *sbrk(intptr_t increment);
void *sbrk(intptr_t increment)
{
	return NULL;
}
*/


// #todo
// This function use the variable 'environ'.
int execvp (const char *file, char *const argv[])
{
    debug_print ("execvep: [TODO]\n");
    return -1;
    //return = execvpe ( file, argv, environ );
}


int 
execvpe ( 
    const char *file, 
    char *const argv[],
    char *const envp[] )
{
    debug_print ("execvpe: [TODO]\n");
    return -1;
}


// Maybe it is easy.
int chown (const char *pathname, uid_t owner, gid_t group)
{
    debug_print ("chown: [TODO]\n");
    return -1; 
}


// Maybe it is easy.
int fchown(int fd, uid_t owner, gid_t group)
{
    debug_print ("fchown: [TODO]\n");
    return -1; 
}


// Maybe it is easy.
int lchown (const char *pathname, uid_t owner, gid_t group)
{
    debug_print ("lchown: [TODO]\n");
    return -1; 
}




int chdir(const char *path)
{
    debug_print ("chdir: [TODO]\n");
    return -1; 
}



int fchdir(int fd)
{
    debug_print ("fchdir: [TODO]\n");
    return -1; 
}
       

// sleep - sleep for a specified number of seconds
unsigned int sleep(unsigned int seconds)
{
    debug_print ("sleep: [TODO]\n");
    return -1;
}


// ??
// todo
// exit deveria ser o wrapper para _exit ?
void _exit (int status)
{
    debug_print ("_exit: [error=O]\n");
    exit(0);
}



void swab_w (const short *from, short *to, ssize_t n)
{
    n /= 2;

    while (--n >= 0)
    {
        *to++ = (*from << 8) + ((*from >> 8) & 0377);
        from++;
    };
}


void swab (const void *from, void *to, ssize_t n)
{
    swab_w ( (const short *) from, (short *) to, (ssize_t) n );
}



// whence = "De onde ?".
off_t lseek (int fd, off_t offset, int whence)
{ 
    //debug_print ("lseek: [TODO]\n");
 
    // #isso muda o posicionamento dentro do arquivo lá no kernel.
    // isso está certo, pois precisamos disso pra sabermos
    //o tamanho do arquivo.
    return (off_t) gramado_system_call ( 603, 
               (unsigned long) fd,
               (unsigned long) offset,
               (unsigned long) whence );
}


off_t tell (int fildes)
{
    return lseek (fildes, 0, SEEK_CUR);
    //maybe: return(lseek(fildes, 0, 1));
}


int access (const char *pathname, int mode)
{
    debug_print ("access: [TODO]\n");
    
	// #todo
	//struct stat foo;
	//return ( stat(pathname, &foo) );

    return -1;
}


// #see: sys/utsname.h
int uname (struct utsname *buf)
{
    debug_print("uname: TODO\n");
    return (int) gramado_system_call ( 377, 
                     (unsigned long) buf, 0, 0);
}


/*
int getsuf (char s[]);
int getsuf (char s[]){
	
	int c;
	char t, *os;

	c = 0;
	os = s;
	
	while (t = *s++)
		if (t=='/')
			c = 0;
		else
			c++;
	s =- 3;
	if (c<=8 && c>2 && *s++=='.' && *s=='f')
		return('f');
		
	return(0);
}
*/


/*
void setsuf (char s[]);
void setsuf (char s[]){
	
	while (*s++);
	s[-2] = 'o';
}
*/


/*
int nodup ( char *l[], char s[]);
int nodup ( char *l[], char s[]){
	
	char *t, *os, c;

	os = s;
	
	while (t = *l++)
	{
		s = os;
		while(c = *s++)
			if (c != *t++) goto ll;
		if (*t++ == '\0') return (0);
ll:;
	}
	return (1);
}
*/




/*
//???
char *nxtarg ( int ap, int	ac, char **av );
char *nxtarg ( int ap, int	ac, char **av ){

	if (ap>ac)
	    return ( 0*ap++ );
	    
	return ( av[ap++] );
}
*/



/*
// ?? tipos
int tio ( int a, int f);
int tio ( int a, int f){

	a = open (a,f);
	
	if (a>=0)
	{
		close (a);
		return(1);
	}
	
	return(0);
}
*/



/* ??
int tcreat ( int a)
{
	return(1);
}
*/




int eq (char *a, char *b){

    int i=0;

l:
    if (a[i] != b[i])
        return (0);

    if (a[i++] == '\0')
        return (1);

    goto l;
}







// pega uma label em uma linha do arquivo
// para comparar strings;
int getlin (char s[]){

    int ch, i;

    i = 0;
l:

    // Se acabou a string.
    if ( ( ch=getc() ) == '\0' ) 
        return (1);


    // Se não for o marcador de label.
    if ( ch != ':' )
    {
        // Avançamos até o fim da linha ou até o fim da string;
        while ( ch != '\n' && ch != '\0' )
            ch = getc();

        goto l;
    }

    // Nesse momento ja encontramos o ':'.
    // Vamos colocar o que segue dentro do array.
    // Não queremos os espaços.

    // Pulamos os espaços.
    while ((ch=getc())==' ');

    
    while ( ch != ' ' && ch != '\n' && ch != '\0' ) 
    {
        s[i++] = ch;
        ch = getc();
    }

    s[i] = '\0';

    return(0);
}


/*
//label?
int unix_getlin ( char s[] )
{
    int ch, i;

	i = 0;


l:
    if ( (ch=getc())=='\0' ) 
        return(1);


	if (ch != ':') 
	{
		while ( ch != '\n' && ch != '\0' )
			ch = getc();
		
		goto l;
	}

	while ( (ch=getc()) == ' ' );


	while ( ch != ' '  && 
	        ch != '\n' && 
	        ch != '\0' )
	{
		s[i++] = ch;
		
		ch = getc();
	}
	
	s[i] = '\0';
	
	return(0);
}
*/



/*
void printn ( int n, int b);
void printn ( int n, int b){
	
	//extern putchar;
	//auto a;
    int a;
    
    if ( b == 0 )
        return;

	if(a=n/b)    //assignment, not test for equality
		printn (a, b);    //recursive 
		
		
	//if (b == 0)
	    //return;
	    	
	putchar (n%b + '0');
}
*/





/*
int match ( char *s, char *p );
int match ( char *s, char *p ){
	
	if (*s=='.' && *p!='.') 
	    return (0);
	    
	return ( amatch(s, p) );
}
*/


/*
int amatch (char *s, char *p);
int amatch (char *s, char *p){
	
	int c, cc, ok, lc, scc;

	scc = *s;
	
	lc = 077777;
	
	switch (c = *p) {

	case '[':
		ok = 0;
		while (cc = *++p) 
		{
			switch (cc) 
			{
			    case ']':
				    if (ok)
					    return ( amatch(++s, ++p) );
				    else
					    return(0);

			    case '-':
				    ok =| lc <= scc & scc <= (cc=p[1]); //?? 
			}
			if (scc==(lc=cc)) ok++;
		}
		return(0);


	case '?':
	
	    caseq: //label
		    if(scc) return(amatch(++s, ++p));
		    return(0);
		
	case '*':
		return(umatch(s, ++p));
		
	case 0:
		return(!scc);
	}
	
	if (c==scc) 
	    goto caseq;
	
	return(0);
}
*/

/*
int umatch(char *s, char *p);
int umatch(char *s, char *p){
	
	if( *p == 0 ) 
	    return (1);
	    
	while (*s)
		if ( amatch(s++,p) ) return (1);
		
	return(0);
}
*/



// Compare
// Not tested yet.
int compar (char *s1, char *s2){

    int c1, c2;

loop:

    if ((c1 = *s1++) == 0) 
        return(0);
        
    if ((c2 = *s2++) == 0) 
        return(1);

    if (c1==c2) 
        goto loop;


    return (c1 > c2);
}




/*
//copy
char *copy (char *s1);
char *copy (char *s1)
{
	char *ts;

	ts = string;
	while(*string++ = *s1++);
	return(ts);
}
*/

/*
// concatenate
char *cat ( char *s1, char *s2);
char *cat ( char *s1, char *s2){
	
	char *ts;

	ts = string;
	while(*string++ = *s1++);
	string--;
	while(*string++ = *s2++);
	return(ts);
}
*/



/*
int __dup ( char **l, char s[] );
int __dup ( char **l, char s[] ){

	char *t, *os, c;

	os = s;
	
	while (t = *l++) 
	{
		s = os;
		
		while (c = *s++)
			if (c != *t++)
				break;
		if (*t++ == '\0') 
			return (1);
	}
	
	return (0);
}
*/


/*
 **************************
 * xxx_todo_int133:
 *     Isso é uma systemcall especial.
 *     #todo: mudar o retorno.
 */

pid_t 
xxx_todo_int133 ( 
    unsigned long ax, 
    unsigned long bx, 
    unsigned long cx, 
    unsigned long dx )
{
    pid_t Ret = 0;


    asm volatile ( " int %1 \n"
                 : "=a"(Ret)
                 : "i"(133), "a"(ax), "b"(bx), "c"(cx), "d"(dx) );

    return (pid_t) Ret;
}




    
//Count occurrences of a char.
int 
StrOcc (
    unsigned char *src, 
    int ch )
{
 
    int i=0;
  
    if (!src) 
        return 0; 

    while (*src)
        if (*src++==ch)
            i++;
    return (int) i;
}


	
//Point to 1st occurrence of marker set in str.
unsigned char *
StrFirstOcc (
	unsigned char *src,
	unsigned char *marker )
{

    int ch;

    while ( (ch=*src++) && !StrOcc(marker,ch) );
    if (ch)
       return src-1;
    else
        return NULL;
}



	
//Point to last occurrence of market set in str.
unsigned char *
StrLastOcc (
	unsigned char *src,
	unsigned char *marker)
{

    int ch;

    unsigned char *res=NULL;
    
    while (ch=*src++)
        if (StrOcc(marker,ch))
            res=src-1;
   return res;
}


#include <spawn.h>


// See:
// https://man7.org/linux/man-pages/man3/posix_spawn.3.html

int 
posix_spawn (
    pid_t *pid, 
    const char *path,
    const posix_spawn_file_actions_t *file_actions,
    const posix_spawnattr_t *attrp,
    char *const argv[], 
    char *const envp[] )
{
    debug_print ("posix_spawn: [FIXME] It's a work in progress.\n"); 
    return (int) gramado_system_call ( 900, (unsigned long) path, 0, 0 );
}

int 
posix_spawnp (
    pid_t *pid, 
    const char *file,
    const posix_spawn_file_actions_t *file_actions,
    const posix_spawnattr_t *attrp,
    char *const argv[], 
    char *const envp[] )
{
    debug_print ("posix_spawn: [FIXME] It's a work in progress.\n"); 
    return (int) gramado_system_call ( 900, (unsigned long) file, 0, 0 );
}



/*
pid_t 
spawn ( 
    const char * path,
    int fd_count, 
    const int fd_map[ ], 
    const struct inheritance * inherit, 
    char * const argv[ ], 
    char * const envp[ ] );
pid_t 
spawn ( 
    const char * path,
    int fd_count, 
    const int fd_map[ ], 
    const struct inheritance * inherit, 
    char * const argv[ ], 
    char * const envp[ ] )
{
    return -1;
}
*/



int spawnv(int mode, char *cmd, char **argv)
{
    debug_print ("spawnv: [FIXME] It's a work in progress.\n"); 
    return (int) gramado_system_call ( 900, (unsigned long) cmd, 0, 0 );
}



int spawnve(int mode, char *path, char *argv[], char *envp[])
{
    debug_print ("spawnv: [FIXME] It's a work in progress.\n"); 
    return (int) gramado_system_call ( 900, (unsigned long) path, 0, 0 );
}



int spawnvp(int mode, char *path, char *argv[])
{
    debug_print ("spawnv: [FIXME] It's a work in progress.\n"); 
    return (int) gramado_system_call ( 900, (unsigned long) path, 0, 0 );
}



int spawnvpe(int mode, char *path, char *argv[], char *envp[])
{
    debug_print ("spawnv: [FIXME] It's a work in progress.\n"); 
    return (int) gramado_system_call ( 900, (unsigned long) path, 0, 0 );
}



int spawnveg(const char* command, char** argv, char** envv, pid_t pgid)
{
    debug_print ("spawnv: [FIXME] It's a work in progress.\n"); 
    return (int) gramado_system_call ( 900, (unsigned long) command, 0, 0 );
}






 


//
// End.
//



