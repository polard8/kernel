//unistd.c

/* UNIX style */
/*posix*/


#include <sys/types.h>        //


#define	UNISTD_SYSTEMCALL_FORK  71  
#define	UNISTD_SYSTEMCALL_EXIT  70

//protótipo de função interna.
void *unistd_system_call ( unsigned long ax, 
                          unsigned long bx, 
				          unsigned long cx, 
				          unsigned long dx );



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
};




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
};

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

 
    stdlib_system_call ( UNISTD_SYSTEMCALL_EXIT, (unsigned long) status, 
	    (unsigned long) status, (unsigned long) status );
    
	
	//Nothing.
//wait_forever:
	
    while (1){
		
		asm ("pause");
	};	
};

/* Ainda estamos testando isso. A rotina no kernel está 
clonando o a estrutura do processo mas ainda há outras coisas pra 
fazer como memória, diretório e a troca correta de diretório de 
páginas dutante o taskswitch */

 
int fork (){
	
    return (int) unistd_system_call ( UNISTD_SYSTEMCALL_FORK, (unsigned long) 0, 
					(unsigned long) 0, (unsigned long) 0 ); 
};

//Get process ID.
/*
int getpid(){
	return (int) system_call( SYSTEMCALL_GETPID, 0, 0, 0);
}
*/

/*
int getppid(){
	return (int) system_call( SYSTEMCALL_GETPPID, 0, 0, 0);
}
*/





