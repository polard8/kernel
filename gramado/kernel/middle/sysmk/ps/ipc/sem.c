/*
 * File: pc/ipc/sem.c  
 *
 * Descrição:
 *   
 *     Gerenciamento de semáforos.
 *     Faz parte do Process Manager, parte fundamental do Kernel Base.
 *     Rotinas de Down e Up.
 *     Os processos entram e saem da sua região crítica utilizando as 
 * rotinas de Down e Up. 
 * 
 * Obs: 
 * Quando um processo em user mode solicitar o uso de um semáforo, ele
 * tem que ter em mão um ponteiro para uma estrutura válida. Então 
 * através de uma system call ele consegue utilizar os métodos 
 * down e up. 
 *
 * History:
 *      2015 - Created by Fred Nora.
 *      2020 - Revision.
 */


#include <kernel.h>


/*
 **************************************************************
 * init_semaphore:
 *     Inicializa uma estrutura de semáforo.
 *     Obs: Quem chama essa função deve alocar memória para a 
 * estrutura e passar por argumento uma estrutura válida.
 */

int init_semaphore ( struct semaphore_d *s, unsigned int count ){

	if ( (void *) s == NULL )
	{
	    return (int) 1;    
	}
	
	// Atribui algum valor ao semáforo. 
	// Deve ser 1, para que o primeiro processo à solicitar o semáforo já 
	// possa usá-lo.
	
	//1.
	s->count = (unsigned int) count;    
    
	return (int) 0;
}


/*
 ************************************************
 * Down:
 * 
 *     Quando um processo vai entrar na sua região crítica ele 
 * executa um Down.
 * Se o semáforo estiver com zero, significa que o recurso já está 
 * bloqueado por outro processo, então o processo que está tentando 
 * utilizar o recurso deve esperar, mudando o estado para waiting.
 * O processo deve esperar.
 * Opções:
 *     + Retornamos um valor que indique que o processo deve esperar
 *       em um loop.
 *     + Bloquamos o processo até que o semáforo esteja liberado.
 */ 

// Enquanto for 0, eu espero. 
// Quando mudar para 1, eu mudo para 0 e avanço.

int Down (struct semaphore_d *s){

    int Flag=0;

    // Fail
    if ( (void *) s ==  NULL){
        debug_print ("Down: s fail\n");
        return (int) 1; 

    }else{
        // How many processes are using?
        Flag = (int) s->count;
    };


    switch (Flag)
    {
		// Já estava liberado, retornamos a indicação de avançar.
		// Obs: O semáfo fica bloquado.
        case 1: 
            s->count = 0; 
            return 0; 
            break;

		// Estava bloqueado, retornamos a indicação de esperar.
		// Obs: Ele permanece bloqueado.
        case 0: 
            return (int) 1; 
            break;

		//Qualquer valor estranho, retornamos a indicação de esperar.
		//#todo: podemos simplesmente diminuir o contador.
        default:
            debug_print ("Down: default\n"); 
            break;
    };

    // ??
    // Nothing
    return (int) 1;
}


/*
 ***************************************************
 * Up:
 *     Quando um processo sai da sua região crítica
 *     ele dá um Up no semáforo, mudando seu valor pra 1.
 *     Isso libera o recurso pra outro processo.
 */ 

int Up (struct semaphore_d *s){

	//
	// *** Mudo para 1.
	//

    int Flag=0;

    // Fail
    if ( (void *) s == NULL){
        debug_print ("Up: s fail\n");
        return (int) 1;

    }else{

        // Counter. 
        Flag = (int) s->count;
    };

    switch (Flag)
    {
        //O semáforo já está liberado.
        case 1: 
            return 0; 
            break;

        //Caso ainda não esteja.
        case 0:
        default:
            s->count = 1;
            return 0;
            break;
    };


//fail:
    return (int) 1;
}


void semaphore_down (struct semaphore_d *s)
{
    Down(s);
}


void semaphore_up (struct semaphore_d *s)
{
    Up(s);
}


void *create_semaphore (void)
{
    debug_print ("create_semaphore: [TODO]\n");
    return NULL;
}


void delete_semaphore(struct semaphore_d *s)
{
    debug_print ("delete_semaphore: [TODO]\n");
    return;
}


void open_semaphore(struct semaphore_d *s)
{
    debug_print ("open_semaphore: [TODO]\n");
    return; 
}

 
void close_semaphore(struct semaphore_d *s)
{
    debug_print ("close_semaphore: [TODO]\n");
    return; 
}


//
// End.
//
