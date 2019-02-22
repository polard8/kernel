/*
 * File: syscall.c
 *
 * Estabelece contato como servidor de serviços do kernel via interrupção.
 *
 * @todo: 
 *     Não faz sentido chamar os serviços do kernel, de dentro dele,
 *     via interrupção. Essa função pode apenas chamar os serviços diretamente,
 *     via função.
 *
 */


#include <kernel.h>

/*
 * systemcall:
 *    Isso chama a interrupção do sistema de dentro do kernel base.
 *    #todo: mudar o retorno para unsigned long.
 *    ??onde está o header??
 */

// #bugbug
// Estamos em ring 0.
// Quando chamamos interrupções estando em ring 0?

int 
systemcall ( unsigned long number, 
                 unsigned long ax, 
                 unsigned long bx, 
                 unsigned long cx, 
                 unsigned long dx )
{
    int ret_val;

    asm volatile ( "int %1\n" 
                  : "=a" (ret_val) 
                  : "i" (0x80), "a"(ax), "b"(bx), "c"(cx), "d"(dx) );

	return (int) ret_val;
}


/*
 ***********************************************************
 * jmp_address:
 *     Transfere o comando para alguma rotina. Sem volta.
 *
 *     @todo: Check if we got a prototype.
 *     #todo: mudar o retorno para void.
 */

int 
jmp_address ( unsigned long arg1, 
              unsigned long arg2, 
              unsigned long arg3, 
              unsigned long arg4 )  
{ 
    asm (" pushl %0" :: "r" (arg4) : "%esp");    //Window.
    asm (" pushl %0" :: "r" (arg3) : "%esp");    //Msg.
    asm (" pushl %0" :: "r" (arg2) : "%esp");    //Long1.       
    asm (" pushl %0" :: "r" (arg1) : "%esp");    //Long2.
	 
	asm (" jmpl *_next_address ");           
	 	
    //    
	// No return !
	//
	
	return (int) -1;
}


//
// End.
//
