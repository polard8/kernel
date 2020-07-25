/*
 * File: pheap.c
 *
 * Descrição:
 *     PHM - Process Heap Manager.
 *     Faz parte do Process Manager, parte fundamental do Kernel Base.
 *
 *     Cada desktop tem seu próprio heap de memória. 
 *     Um processo usa o heap de memória usado pelo seu desktop.
 *
 * History:
 *     2016 - Created by Fred Nora.
 */
 
 
#include <kernel.h>


//
// Variáveis internas.
//

//int phmStatus;
//int phmError;
//...


/*
    @todo:
        +Set process heap start.
	    +Set process heap end.
		+Get process heap start.
	    +Get process heap end.
		//...		
		
*/


//unsigned long GetProcessHeapEnd(struct process_d *process){};


/*
 * GetProcessHeapStart:
 *     Obtem o início do heap de um processo.
 *     Return 0 if error.
 */
 
/* 
unsigned long GetThreadHeapStart(struct process_d *process)
{
    if((void*) process == NULL){
        return (unsigned long) 0;        
	};  
	return (unsigned long) process->Heap;
};

*/


/*
 *Constructor.
int phmPhm(){
	;
};
*/


/*
int phmInit(){
	;
};
*/


//
// End.
//

