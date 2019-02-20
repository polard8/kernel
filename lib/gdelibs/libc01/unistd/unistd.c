/*
 * File: unistd.c
 *
 * Unix standard.
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


//system calls.
#include <stubs/gramado.h> 



#define	UNISTD_SYSTEMCALL_FORK     71  
#define	UNISTD_SYSTEMCALL_EXIT     70
#define	UNISTD_SYSTEMCALL_GETPID   85
#define	UNISTD_SYSTEMCALL_GETPPID  81

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
 ********************************************************
 * execve:
 * Executes a new process.
 * PS: Does not return on success, and the text, data, bss, 
 * and stack of the calling process are overwritten by 
 * that of the program loaded. 
 */
 
int 
execve ( const char *filename, 
         const char *argv[], 
         const char *envp[] )
{
	
	//@todo: Ainda não implementada.
	
	return (int) -1;
}


/*
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
    
	
	//Nothing.
//wait_forever:
	
    while (1){
		
		asm ("pause");
	};	
}


/* Ainda estamos testando isso. A rotina no kernel está 
clonando o a estrutura do processo mas ainda há outras coisas pra 
fazer como memória, diretório e a troca correta de diretório de 
páginas dutante o taskswitch */

 
int fork (){
	
    //return (int) unistd_system_call ( UNISTD_SYSTEMCALL_FORK, (unsigned long) 0, 
	//				(unsigned long) 0, (unsigned long) 0 ); 
	
    return (int) gramado_system_call ( UNISTD_SYSTEMCALL_FORK, (unsigned long) 0, 
					(unsigned long) 0, (unsigned long) 0 ); 
}


// SVr4,  POSIX.1-2001.   
// Not quite	compatible with	the 4.4BSD call, which
// sets all	of the real, saved, and	effective user IDs.	   
int setuid ( uid_t uid )
{	
	//#todo: ainda não temos a suystem call.
	return -1;
}


pid_t getpid(void){
	
	//return (pid_t) unistd_system_call( UNISTD_SYSTEMCALL_GETPID, 0, 0, 0);
	return (pid_t) gramado_system_call( UNISTD_SYSTEMCALL_GETPID, 0, 0, 0);
}


pid_t getppid(void){
	
	//return (pid_t) unistd_system_call( UNISTD_SYSTEMCALL_GETPPID, 0, 0, 0);
	return (pid_t) gramado_system_call( UNISTD_SYSTEMCALL_GETPPID, 0, 0, 0);
}


gid_t getgid(void)
{	
	//#todo: ainda não temos a suystem call.
	return -1;
}


int dup(int oldfd)
{
	return -1; //#todo
}


int dup2(int oldfd, int newfd)
{
	return -1; //#todo
}


int dup3(int oldfd, int newfd, int flags)
{
	return -1; //#todo
}


int fcntl (int fd, int cmd, ... /* arg */ )
{
	return -1; //#todo
}


// nice - change process priority
int nice(int inc)
{
	return -1; //#todo
};


//shutdown	- shut down part of a full-duplex connection
int shutdown ( int	sockfd,	int how )
{
	return -1; //#todo
};

	 
ssize_t send ( int sockfd, const void *buf, size_t len, int flags )
{
	return -1; //#todo
};


int pause(void)
{
	return -1; //#todo
};


int mkdir(const char *pathname, mode_t mode)
{
	return -1; //#todo
};


int rmdir(const char *pathname)
{
	return -1; //#todo
};	


int link(const char *oldpath, const char *newpath)
{
	return -1; //#todo
};	


//socket -	create an endpoint for communication
int socket ( int domain, int type, int protocol )
{
	return -1; //#todo
}


ssize_t recv ( int sockfd,	void *buf, size_t len, int flags )
{
	return -1; //#todo
}


int mlock(const void *addr, size_t len)
{
	return -1; //#todo
}


int munlock(const void *addr, size_t len)
{
	return -1; //#todo
}


int mlockall( int flags)
{
	return -1; //#todo
}


int munlockall(void)
{
	return -1; //#todo
}


long sysconf(int name)
{
	return -1; //#todo
}


int fsync(int fd)
{
	return -1; //#todo
}


int fdatasync(int fd)
{
	return -1; //#todo
}


long fpathconf(int fd, int name)
{
	return -1; //#todo
}


long pathconf(char *path, int name)
{
	return -1; //#todo
}


int ioctl ( int d, int request, ... )
{
	return -1; //#todo
}




	
	
	
	








