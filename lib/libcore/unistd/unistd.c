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

//system calls.
#include <stubs/gramado.h> 



#define	UNISTD_SYSTEMCALL_FORK     71  
#define	UNISTD_SYSTEMCALL_EXIT     70
#define	UNISTD_SYSTEMCALL_GETPID   85
#define	UNISTD_SYSTEMCALL_GETPPID  81
//...


//
//  ## TEST ##
//

int errno;


//The <unistd.h> header shall declare the following external variables:
char  *optarg;
int    opterr, optind, optopt;


//#todo
//#define	UNISTD_SYSTEMCALL_GETGID ??

/*
//protótipo de função interna.
void *unistd_system_call ( unsigned long ax, 
                           unsigned long bx, 
                           unsigned long cx, 
                           unsigned long dx );
*/


/*
 ********************
 * unistd_system_call:
 *     System call usada pelo módulo stdio.  
 *     Função interna. 
 *     As funções padrão de stdio chamarão recursos do kernel atravéz dessa 
 * rotina.
 *     Interrupção de sistema, número 200, personalizada para stdio.
 *     Chama vários serviços do Kernel com a mesma interrupção.
 *     Essa é a chamada mais simples.
 *
 * Argumentos:
 *    eax = arg1, o Número do serviço.
 *    ebx = arg2. 
 *    ecx = arg3.
 *    edx = arg4.
 */

/*
void *unistd_system_call ( unsigned long ax, 
                           unsigned long bx, 
                           unsigned long cx, 
                           unsigned long dx )
{
    int Ret = 0;	

	//System interrupt.

	asm volatile ( " int %1 \n"
		           : "=a"(Ret)	
		           : "i"(0x80), "a"(ax), "b"(bx), "c"(cx), "d"(dx) );

	return (void *) Ret; 
}
*/



 


/*
 * execv:
 * 
 */
 
// #todo: Trabalhar o environment.
// #isso é um teste

char *__execv_environ[] = { NULL, NULL, NULL };

int execv (const char *path, char *const argv[] )
{
    return execve ( path, (char **) argv, __execv_environ );
}

 
 
 
//padrão libc.
//int execve ( const char *path, char *const argv[], char *const envp[] );  

int 
execve ( const char *filename, 
         char *argv[], 
         char *envp[] )	
{
	//erro.

    int Status = 1;

	//unsigned long arg_address = (unsigned long) &argv[0];

	// suprimindo dot-slash
	// The dot is the current directory and the 
	// slash is a path delimiter.
	//if( filename[0] == '.' && filename[1] == '/' )
	//{ 
	//    filename++;
	//    filename++; 
	//    goto translate;	
	//};


	//suprimindo a barra.
	//if( *arg1 == '/' || 
	//    *arg1 == '\\' )
	//{ 
	//    arg1++; 
	//};


translate:

	//
	// ## BUG BUG
	//
	// Talvez nesse momento, ao transformar a string ele 
	// corrompa o espaço reservado para o argumento seguinte.
	// vamos fazer um teste no quan a rotina não precise 
	// acrescentar zeros.
	//
	
	//
	// correto é isso mesmo,
	// para não corromper o espaço dos argumentos no vetor,
	// teremos que transformar somente lá no kernel, pouco antes 
	// de carregarmos o arquivo.
	//
	
	//Isso faz uma conversão de 'test.bin' em 'TEST    BIN'.
	//Ok funcionou.
	//shell_fntos( (char *) arg1);
	
	//const char* isso não foi testado.
	//shell_fntos(filename);


	// #importante:
	// Isso deve chamar gramado_core_init_execve() na api.
								
	
	// #obs:
	// isso chamará uma rotina especial de execve, somente  
	// usada no ambiente gramado core. 
	// Essa é uma rotina alternativa que roda um processo usando os recursos 
	// do processo init.
	
execve:

	// Obs: 
	// Se retornar o número do processo então podemos esperar por ele 
	// chamando wait (ret);

	//#todo:
	// mudaremos esse número de chamada pra uma
	// que use o processo atual e não o init.

    Status = (int) gramado_system_call ( 248, 
                       (unsigned long) filename,    // Nome
                       (unsigned long) argv,        // arg (endereço da linha de comando)
                       (unsigned long) envp );      // env

    if ( Status == 0 )
    {
		//Não houve erro. O aplicativo irá executar.

		// Nesse momento devemos usar um novo procedimento de janela.
		// Que vai enviar as mensagens de caractere para um terminal 
		// específico, para que aplicativos que user aquele terminal 
		// possam pegar essas mensgens de caractere.


//#ifdef SHELL_VERBOSE
        //printf ("execve: Aplicativo inicializado\n");
//#endif

		//
		// ## teste ##
		//
		// saindo do shell.
		//
		
		// getpid...
		// waitforpid(?);
		
		//die("Exiting shell.bin\n");
		
		//Saindo sem erro.
		//exit(0);
		
		//Saída elegante, retornando para o crt0.
		//ShellFlag = SHELLFLAG_EXIT;
		//ShellFlag = SHELLFLAG_FEEDTERMINAL;
		
		goto done;
	}else{
		
		// Se estamos aqui é porque ouve erro 
		// ainda não sabemos o tipo de erro. 
		// Status indica o tipo de erro.
		// Se falhou significa que o aplicativo não vai executar,
		// então não mais o que fazer.
		
		//#importante: Error message.
		printf ("execve: O aplicativo nao foi inicializado\n");
		
		//ShellFlag = SHELLFLAG_COMMANDLINE;
		goto fail;
	};

	//fail.
	
	// Retornaremos. 
	// Quem chamou essa rotina que tome a decisão 
	// se entra em wait ou não.

fail:

    Status = -1;
    
	//#importante: Error message.
	
    printf ("execve: fail \n");
	
done:

    return (int) Status;
}


ssize_t read_ttyList (int fd, const void *buf, size_t count)
{
    if (fd<0)
        return -1;

    return (ssize_t) gramado_system_call ( 268, 
                         (unsigned long) fd,      // dispositivo.
                         (unsigned long) buf, 
                         (unsigned long) count ); 
}


// o descritor seleciona uma tty em ttyList
ssize_t write_ttyList (int fd, const void *buf, size_t count)
{
    if (fd<0)
        return -1;

    return (ssize_t) gramado_system_call ( 269, 
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




//usam a lista de arquivos abertos do processo. p->Streams[i]
ssize_t read (int fd, const void *buf, size_t count)
{
    if (fd<0)
        return -1;

    return (ssize_t) gramado_system_call ( 18, 
                         (unsigned long) fd,      // dispositivo.
                         (unsigned long) buf, 
                         (unsigned long) count ); 
}

//usam a lista de arquivos abertos do processo. p->Streams[i]
ssize_t write (int fd, const void *buf, size_t count)
{
    if (fd<0)
        return -1;

    return (ssize_t) gramado_system_call ( 19, 
                         (unsigned long) fd,      // dispositivo.
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

void exit (int status){
	
	//#importante:
    //     @todo: se o status for (1) devemos imprimir o conteúdo 
    // de stderr na tela.

 
    //stdlib_system_call ( UNISTD_SYSTEMCALL_EXIT, (unsigned long) status, 
	//    (unsigned long) status, (unsigned long) status );
	
    gramado_system_call ( UNISTD_SYSTEMCALL_EXIT, (unsigned long) status, 
	    (unsigned long) status, (unsigned long) status );
    
	
	// Wait forever.
	
    while (1){ asm ("pause"); };
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

gid_t getgid (void){
	
	//SYSTEMCALL_GETCURRENTGROUPID
	return (gid_t) gramado_system_call ( 154, 0, 0, 0 );
}


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
				    (unsigned long) newfd, 0, 0 );
}


/*
 * dup3:
 *
 */

int dup3 (int oldfd, int newfd, int flags){
	
    return (int) gramado_system_call ( (unsigned long) oldfd, 
				    (unsigned long) newfd, (unsigned long) flags, 0 );
}


/*
 * fcntl:
 *
 */

int fcntl ( int fd, int cmd, ... ){

    //if (cmd == F_GETFD || cmd == F_SETFD) { return 0; }

	return -1; //#todo
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






/*
// linux-like 0.01
int __open (const char * filename, int flag, ...);
int __open (const char * filename, int flag, ...)
{
    register int res;
    va_list arg;

    va_start (arg,flag);


	//__asm__("int $0x80"
		//:"=a" (res)
		//:"0" (__NR_open),"b" (filename),"c" (flag),
		//"d" ( va_arg(arg,int)) );

    res = gramado_system_call ( ? , 
              (unsigned long) pathname, 
              (unsigned long) flags, 
               unsigned long) va_arg(arg,int)) );

    if (res>=0)
        return res;

    errno = -res;

    return -1;
}
*/


/*
 **********************
 * open:
 *
 */

// open, openat, creat - open and possibly create a file 
 
// See: 
// fcntl.h
// http://man7.org/linux/man-pages/man2/open.2.html
// ...

int open (const char *pathname, int flags, mode_t mode){

    return (int) gramado_system_call ( 16, 
                     (unsigned long) pathname, 
                     (unsigned long) flags, 
                     (unsigned long) mode );
}


/*
 *****************************************
 * close:
 *    SVr4, 4.3BSD, POSIX.1-2001.
 */

int close (int fd){

    return (int) gramado_system_call ( 17, (unsigned long) fd, 
                     (unsigned long) fd, (unsigned long) fd );
}


/*
 **************************************************
 * pipe:
 *
 */

int pipe ( int pipefd[2] ){

    return (int) gramado_system_call ( 247, 
                     (unsigned long) pipefd, 
                     (unsigned long) pipefd, 
                     (unsigned long) pipefd );
}


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


char __Hostname_buffer[64];

//isso funciona.
char *__gethostname (void)
{
    gramado_system_call ( 801, 
       (unsigned long) &__Hostname_buffer[0],
       (unsigned long) &__Hostname_buffer[0],
       (unsigned long) &__Hostname_buffer[0] );


    return __Hostname_buffer;
}


char *my__p;
//See: http://man7.org/linux/man-pages/man2/sethostname.2.html
int gethostname (char *name, size_t len)
{
	int len_ret;

    //dá pra retornar direto.
    //colocando no buffer do app
    len_ret = (int) gramado_system_call ( 38, 
                        (unsigned long) name,
                        (unsigned long) name,
                        (unsigned long) name );
     

     return len_ret;
}



//See: http://man7.org/linux/man-pages/man2/sethostname.2.html
int sethostname (const char *name, size_t len){

    return (int) gramado_system_call ( 39, 
                    (unsigned long) name,
                    (unsigned long) name,
                    (unsigned long) name );
}



char __Login_buffer[64];

//#todo
char *getlogin (void)
{
	//passamos um buffer para o kernel.
	gramado_system_call ( 803, 
	    (unsigned long) &__Login_buffer[0],
	    (unsigned long) &__Login_buffer[0],
	    (unsigned long) &__Login_buffer[0] );
	
	//strcpy(__Login, "test");
	return __Login_buffer;
}

//#todo
int setlogin(const char *name)
{

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
//usar  setlogin 
 
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

int isatty (int fd){ 

    struct termios t;


    return ( tcgetattr(fd, &t) != -1 ); 
}


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










