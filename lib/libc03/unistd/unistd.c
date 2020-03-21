/*
 * File: unistd.c
 *
 *     Unix standard.
 * 
 * History:
 *     2019 - Created by Fred Nora.
 */


#include <sys/types.h>  
#include <sys/socket.h>
#include <sys/mman.h>

//#include <sys/stat.h>   

#include <fcntl.h>
#include <unistd.h>

#include <limits.h>

//#todo
//nice() precisa disso.
#include <sys/time.h>
#include <sys/resource.h>


//#test
#include <pty.h>
#include <utmp.h>
#include <termios.h>

#include <sys/utsname.h>

//system calls.
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
execve ( const char *path, 
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



/*
 * read_ttyList:
 *    Special case of read(), where it reads from a
 *  fd present in a list calle ttyList[fd].
 */
 
ssize_t read_ttyList (int fd, const void *buf, size_t count)
{
    if (fd<0)
        return -1;

    return (ssize_t) gramado_system_call ( 268, 
                         (unsigned long) fd,      // dispositivo.
                         (unsigned long) buf, 
                         (unsigned long) count ); 
}


/*
 * write_ttyList:
 *    Special case of write(), where it writes into a
 *  fd present in a list calle ttyList[fd].
 */

// o descritor seleciona uma tty em ttyList[]
ssize_t write_ttyList (int fd, const void *buf, size_t count)
{
    if (fd<0)
        return -1;

    return (ssize_t) gramado_system_call ( 269, 
                         (unsigned long) fd,      // dispositivo.
                         (unsigned long) buf, 
                         (unsigned long) count ); 
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
 * read:
 *     Standard read() function.
 */
//usam a lista de arquivos abertos do processo.
ssize_t read (int fd, const void *buf, size_t count)
{
    if (fd<0)
        return -1;

    return (ssize_t) gramado_system_call ( 18, 
                         (unsigned long) fd,
                         (unsigned long) buf, 
                         (unsigned long) count ); 
}


/*
 * write: 
 *     Standard write() function. 
 */
// usam a lista de arquivos abertos do processo. 
ssize_t write (int fd, const void *buf, size_t count)
{
    if (fd<0)
        return -1;

    return (ssize_t) gramado_system_call ( 19, 
                         (unsigned long) fd,
                         (unsigned long) buf, 
                         (unsigned long) count ); 
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

void exit (int status){


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
 *
 */

pid_t fork (void)
{
    pid_t __ret = -1;
    
    __ret = (pid_t) gramado_system_call( UNISTD_SYSTEMCALL_FORK, 
                        0, 0, 0 );
    
    if(__ret<0)
    {
         //errno = -__ret;
         return (-1);
    }
    
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


uid_t getuid (void){
	
	return (uid_t) gramado_system_call ( 152, 0, 0, 0 );
}


uid_t geteuid (void){
	
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
 * getgid:
 *
 */

gid_t getgid (void)
{
	//SYSTEMCALL_GETCURRENTGROUPID

	return (gid_t) gramado_system_call ( 154, 0, 0, 0 );
}



/*
char* getwd(char* buf)
{
    auto* p = getcwd(buf, PATH_MAX);
    return p;
}
*/


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
 * dup:
 *
 */

int dup (int oldfd){
	
    return (int) gramado_system_call ( (unsigned long) oldfd, 0, 0, 0 );
}


/*
 * dup2:
 *
 */

int dup2 (int oldfd, int newfd){

    return (int) gramado_system_call ( (unsigned long) oldfd, 
                     (unsigned long) newfd, 
                     0, 
                     0 );
}


/*
 * dup3:
 *
 */

int dup3 (int oldfd, int newfd, int flags){

    return (int) gramado_system_call ( (unsigned long) oldfd, 
                     (unsigned long) newfd, 
                     (unsigned long) flags, 
                     0 );
}



//see: sys/resource.h
int getpriority(int which, id_t who)
{
	return -1;
}

//see: sys/resource.h
int setpriority(int which, id_t who, int prio)
{
	return -1;
}



/*
 * nice:
 *     Change process priority.
 */

int nice (int inc)
{
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

int pause (void){
	
	return -1; //#todo
}


/*
 * mkdir:
 *
 */

int mkdir (const char *pathname, mode_t mode){
	
	return -1; //#todo
}


/*
 * rmdir:
 *
 */

int rmdir (const char *pathname){
	
	return -1; //#todo
}	


/*
 * link:
 *
 */

//Links a name to a file.

int link (const char *oldpath, const char *newpath){
	
	return -1; //#todo
}


//#todo.
int unlink(const char *pathname)
{
    return (int) (-1);
}


/*
 * mlock:
 *
 */

int mlock (const void *addr, size_t len){
	
	return -1; //#todo
}


/*
 * munlock:
 *
 */

int munlock (const void *addr, size_t len){
	
	return -1; //#todo
}


/*
 * mlockall:
 *
 */

int mlockall (int flags){
	
	return -1; //#todo
}


/*
 * munlockall:
 *
 */

int munlockall (void){
	
	return -1; //#todo
}


/*
 * sysconf:
 *
 */

long sysconf (int name){
	
	return -1; //#todo
}


/*
 * fsync:
 *
 */

int fsync (int fd){
	
	return -1;    //#todo
}


/*
 * fdatasync:
 *
 */

int fdatasync (int fd){
	
	return -1; //#todo
}



// commit buffer cache to disk 
void sync(void)
{
	//todo: use syscall!!
}

// commit buffer cache to disk 
int syncfs(int fd)
{
    return -1;
}





/*
 *****************************************
 * close:
 *    SVr4, 4.3BSD, POSIX.1-2001.
 */

// #obs
// Isso deve fechar o arquivo na lista de arqquivo abertos.

int close (int fd){

    return (int) gramado_system_call ( 17, 
                     (unsigned long) fd, 
                     (unsigned long) fd, 
                     (unsigned long) fd );
}


/*
 **************************************************
 * pipe:
 *
 */

// good!

int pipe ( int pipefd[2] )
{
    return (int) gramado_system_call ( 247, 
                     (unsigned long) pipefd, 
                     (unsigned long) pipefd, 
                     (unsigned long) pipefd );
}


/*
int pipe(int pipefd[2])
{
    return pipe2(pipefd, 0);
}
*/



long fpathconf (int fildes, int name)
{
    return -1;
}


long pathconf (const char *pathname, int name)
{
    return -1;
} 


//deletar.
//static char   __libc_hostname[HOST_NAME_MAX];
//static char   __libc_username[HOST_NAME_MAX];




/*
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
 
int getusername (char *name, size_t len)
{
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

	if ( __len_ret > len )
	{
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
    if ( __name_len > len )
    {
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

char *ttyname(int fd)
{
	static char buf[PATH_MAX];
	int rv;
	
	rv = ttyname_r (fd, buf, sizeof(buf));
	
	if (rv != 0)
	{
		errno = rv;
		return NULL;
	}

	return buf;
}


//POSIX.1-2001, POSIX.1-2008, 4.2BSD.
//ttyname, ttyname_r - return name of a terminal
int ttyname_r(int fd, char *buf, size_t buflen)
{ 
	return -1; 
}


//#todo
/*
int ttyslot (void);
int ttyslot (void)
{
   return -1;
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
}

/*
int isatty(int fd)
{
    struct termios dummy;
    return tcgetattr(fd, &dummy) == 0;
}
*/


int getopt (int argc, char * const argv[], const char *optstring)
{
	return -1;
}


//sys/stat.h
/*
int fstat(int fd, struct stat *buf);
int fstat(int fd, struct stat *buf)
{
	return -1;
}
*/


//sys/stat.h
/*
int lstat(const char *path, struct stat *buf);
int lstat(const char *path, struct stat *buf)
{
	return (int) stat (path, buf);
}
*/


//sys/stat.h
/*
int stat(const char *path, struct stat *buf);
int stat(const char *path, struct stat *buf)
{
	int i = open(path, 0);
	int ret = fstat(i, buf);
	close(i);
	return ret;
}
*/


//POSIX.1-2001, POSIX.1-2008, SVr4, 4.3BSD.
unsigned int alarm(unsigned int seconds)
{
	return 0;
}




int brk(void *addr)
{
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




int execvp (const char *file, char *const argv[])
{
	return -1;
    //return = execvpe ( file, argv, environ );
}


int 
execvpe ( const char *file, 
          char *const argv[],
          char *const envp[] )
{
	return -1;
}



int chown(const char *pathname, uid_t owner, gid_t group)
{
	return -1; 
}




int fchown(int fd, uid_t owner, gid_t group)
{
	return -1; 
}




int lchown(const char *pathname, uid_t owner, gid_t group)
{
	return -1; 
}




int chdir(const char *path)
{
	return -1; 
}



int fchdir(int fd)
{
	return -1; 
}
       

//sleep - sleep for a specified number of seconds
unsigned int sleep(unsigned int seconds)
{
	return 0;
}


//todo
void _exit (int status)
{
    //improvisando
    exit(0);
}



void swab_w (const short *from, short *to, ssize_t n)
{
	
	n /= 2;
	while (--n >= 0) {
		*to++ = (*from << 8) + ((*from >> 8) & 0377);
		from++;
	}
}

void swab (const void *from, void *to, ssize_t n)
{
    swab_w ( (const short *) from, (short *) to, (ssize_t) n );
}



// #todo
off_t lseek(int fd, off_t offset, int whence)
{ 
	return 0;
}


off_t tell(int fildes)
{
	return lseek(fildes, 0, SEEK_CUR);
	//return(lseek(fildes, 0, 1));
}



int access(const char *pathname, int mode)
{
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

    int i;

    i = 0;

l:
    if (a[i] != b[i])
        return (0);

    if (a[i++] == '\0')
        return (1);

    goto l;
}







// pega uma label em uma linha do arquivo
// para comparar strings;
int getlin(char s[]){

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
int compar(char *s1, char *s2){

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
xxx_todo_int133 ( unsigned long ax, 
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





//
// End.
//










