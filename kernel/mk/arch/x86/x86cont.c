/*
 * File: x86cont.c
 *
 * Descrição:
 *     Operações com contexto de processador.
 *     Salva e restaura o contexto, para uso em task switch.
 *     Faz parte do Process Manager, parte fundamental do Kernel Base.
 *
 * @todo: 
 *     Criar funções que trabalhem o contexto e registradores.
 *     ??
 *
 * Obs: @todo: Esse módulo deverá ser apenas uma interface para chamar
 * rotinas de mudança de contexto que deverão ficar em um módulo externo
 * ao kernel base, porem ainda em ring0. Essas rotinas poderão fazer parte
 * do módulo HAL, que será dependente da arquitetura.
 * Ou seja, pode existir um modulo hal em ring 0 para cada arquitetura, 
 * porem o kernel base será o mesmo para todas as arquiteturas.
 * O módulo hal, dependente da arquitetura, será selecionado na hora da
 * instalação.
 *
 * History:
 *     2015 - Created by Fred Nora.
 *     //...
 */


#include <kernel.h>


extern void set_page_dir();


static inline void ckSetCr3 ( unsigned long value ){

    __asm__ ( "mov %0, %%cr3" : : "r" (value) );
}


/*
static inline uint32_t ckGetCr3()
{
    uint32_t ret;
    __asm__ ( "mov %%cr3, %0 " : "=r"(ret) );
    return ret;
}
*/


//
// Variáveis internas. 
//

//int contextStatus;
//int contextError;
//int contextCpuType;
//...


// Context:
//     Variáveis para salvar o contexto.
//     Essas variáveis devem permanecer encapsuladas
//     nesse arquivo dó módulo. Somente esse
//     arquivo terá acesso à essas variáveis.
//     
//     *IMPORTANTE:
//         Obviamente a rotina _irq0, que é o handler
//         do timer está acessando essas variáveis
//         fazendo uso d 'extern'. 

unsigned long contextSS;        //User mode.
unsigned long contextESP;       //User mode.
unsigned long contextEFLAGS;
unsigned long contextCS;
unsigned long contextEIP;
unsigned long contextDS;
unsigned long contextES;
unsigned long contextFS;
unsigned long contextGS;
unsigned long contextEAX;
unsigned long contextEBX;
unsigned long contextECX;
unsigned long contextEDX;
unsigned long contextESI;
unsigned long contextEDI;
unsigned long contextEBP;
//
// @todo: Outros registradores.
// debug
// mmx
// ponto flutuante
// Continua ...
// 




/*
 **************************************
 * save_current_context:    
 *    Salvando o contexto da thread interrompida pelo timer IRQ0.
 *    O contexto da tarefa interrompida foi salvo em variáveis pela 
 * isr do timer. Aqui esse contexto é colocado na estrutura que 
 * organiza as threads.
 *
 * @todo: 
 *     Estão faltando variáveis nesse contexto, como registradores de 
 * debug e float point por exemplo.
 *     Mudar nome para contextSaveCurrent();.
 */
 
void save_current_context (){
	
    int Status;
	struct thread_d *t;
    
	// Context.
	unsigned long *contextss  = (unsigned long *) &contextSS;	 	
	unsigned long *contextesp = (unsigned long *) &contextESP;	 
	unsigned long *contexteflags = (unsigned long *) &contextEFLAGS;	
	unsigned long *contextcs  = (unsigned long *) &contextCS;	
	unsigned long *contexteip = (unsigned long *) &contextEIP;	
	unsigned long *contextds  = (unsigned long *) &contextDS;	
	unsigned long *contextes  = (unsigned long *) &contextES;	
	unsigned long *contextfs  = (unsigned long *) &contextFS;	
	unsigned long *contextgs  = (unsigned long *) &contextGS;		
	unsigned long *contexteax = (unsigned long *) &contextEAX;	
	unsigned long *contextebx = (unsigned long *) &contextEBX;	
	unsigned long *contextecx = (unsigned long *) &contextECX;	
	unsigned long *contextedx = (unsigned long *) &contextEDX;	
	unsigned long *contextesi = (unsigned long *) &contextESI;	
	unsigned long *contextedi = (unsigned long *) &contextEDI;	
	unsigned long *contextebp = (unsigned long *) &contextEBP;	
	// Continua...

	
	// Structure ~ Colocando o contexto na estrutura.	
	t = (void *) threadList[current_thread];
	
	if ( (void *) t == NULL )
	{
	    printf ("save_current_context error: Struct Thread={%d}\n",
		    current_thread );
			
		show_process_information ();    
		die ();
		
	}else{
		
		
		if ( t->used != 1 || t->magic != 1234 )
		{
	        printf ("save_current_context error: Validation Thread={%d}\n",
		        current_thread );
			
		    show_process_information ();    
		    die ();
		}
		
	    // 
	    // @todo: Checar. 
	    //
	
	    t->ss = contextss[0];      //usermode.
	    t->esp = contextesp[0];    //usermode.
	    t->eflags = (unsigned long) contexteflags[0];
	    t->cs = (unsigned long) contextcs[0];
	    t->eip = (unsigned long) contexteip[0];
	
	    t->ds = contextds[0];
	    t->es = contextes[0];
	    t->fs = contextfs[0];
	    t->gs = contextgs[0];
	
	    t->eax = (unsigned long) contexteax[0];
	    t->ebx = (unsigned long) contextebx[0];
	    t->ecx = (unsigned long) contextecx[0];
 	    t->edx = (unsigned long) contextedx[0];
	    t->esi = (unsigned long) contextesi[0];
	    t->edi = (unsigned long) contextedi[0];
	    t->ebp = (unsigned long) contextebp[0];		
	    //Continua...
	};	
	
	//
	// Flag. ??? Saved.
	//
};



/*
 ****************************************************
 * restore_current_context: 
 *     Carregando o contexto da próxima thread a ser executada.
 *     Pegando os valores na estrutura e colocando nas variáveis 
 * que serão usadas pelo arquivo em assembly para carregar os valores 
 * dentro dos registradores.
 *
 * @todo:   
 *     Mudar nome para contextRestoreCurrent();.
 */

void restore_current_context (){
	
	int Status;
	struct thread_d *t;
	
    // Context.
	unsigned long *contextss  = (unsigned long *) &contextSS;	 	
	unsigned long *contextesp = (unsigned long *) &contextESP;	 
	unsigned long *contexteflags = (unsigned long *) &contextEFLAGS;	
	unsigned long *contextcs  = (unsigned long *) &contextCS;	
	unsigned long *contexteip = (unsigned long *) &contextEIP;	
	unsigned long *contextds  = (unsigned long *) &contextDS;	
	unsigned long *contextes  = (unsigned long *) &contextES;	
	unsigned long *contextfs  = (unsigned long *) &contextFS;	
	unsigned long *contextgs  = (unsigned long *) &contextGS;	
	unsigned long *contexteax = (unsigned long *) &contextEAX;	
	unsigned long *contextebx = (unsigned long *) &contextEBX;	
	unsigned long *contextecx = (unsigned long *) &contextECX;	
	unsigned long *contextedx = (unsigned long *) &contextEDX;	
	unsigned long *contextesi = (unsigned long *) &contextESI;	
	unsigned long *contextedi = (unsigned long *) &contextEDI;	
	unsigned long *contextebp = (unsigned long *) &contextEBP;	
    // Continua...	

	// Structure.
	t = (void *) threadList[current_thread]; 
	
	if ( (void *) t == NULL )
	{
	    printf("restore_current_context error: t\n");
		
		show_process_information ();    
		die ();
	
	} else {
	
	    //
	    // Restore.
	    //
	
	    contextss[0] = t->ss;      //usermode.
	    contextesp[0] = t->esp;    //usermode. 
	    contexteflags[0] = t->eflags;
	    contextcs[0] = t->cs;  
	    contexteip[0] = (unsigned long) t->eip;
	
	    contextds[0] = t->ds;
        contextes[0] = t->es; 
        contextfs[0] = t->fs; 
	    contextgs[0] = t->gs; 
	
	    contexteax[0] = (unsigned long) t->eax;  
	    contextebx[0] = (unsigned long) t->ebx; 
        contextecx[0] = (unsigned long) t->ecx;  
	    contextedx[0] = (unsigned long) t->edx; 
	    contextesi[0] = (unsigned long) t->esi;  
        contextedi[0] = (unsigned long) t->edi; 
	    contextebp[0] = (unsigned long) t->ebp;  
        // Continua...
		
		
		//
		//  ## CR3 ##
		//
		
		// #importante
		// Esse é o grande momento.
		// É nessa hora em que colocamos o endereço FÍSICO do 
		// diretório de páginas usado pela thread no registrador CR3.
		
		ckSetCr3 ( (unsigned long) t->DirectoryPA );

		
		//
		//  ## flush TLB ##
		//
	    
		// #bugbug
		// Esse flush é desnecessário, pois o assembly faz isso 
		// pouco antes do iretd.
	    
		asm ("movl %cr3, %eax");
	    // asm ("nop");
	    // asm ("nop");
	    // asm ("nop");
	    // asm ("nop");
        asm ("movl %eax, %cr3");		
	};

	//
	//flag ??...
	//
};


/*
 * check_task_context: */
 
int contextCheckThreadRing0Context (int tid){
	
	//return -1;  //cancelada
	return 0;
};
 

// Checar um contexto válido para threads em ring 3. 

int contextCheckThreadRing3Context (int tid){
	
	//Error. (condição default).	
	int Status = 1;    
	
    struct thread_d *t; 
    //...
	
	// Limits.
	// Erro. Status.
	
	if ( tid < 0 || tid >= THREAD_COUNT_MAX )
	{
	    return (int) 1;    
	}
	
	//Structure.
	
	t = (void *) threadList[tid]; 
    
	if ( (void *) t == NULL )
	{
	    //Erro. Status.
		return (int) 1; 
	
	}else{
		
	    // validation.
	    		
	    if ( t->used != 1 || t->magic != 1234 )
		{
	        printf ("contextCheckThreadRing3Context: validation\n");
		    return (int) 1;
	    };    
	
	    //se é ring 3.
		
	    if ( t->iopl != 3 )
		{
	        printf("contextCheckThreadRing3Context: iopl\n");
		    return (int) 1;
	    };
		
		
	    //Checa se os segmentos tem os valores válidos para ring 3.
	    //0x1B para código e 0x23 para dados.
		
	    if ( t->cs != 0x1B || 
	         t->ds != 0x23 || 
	         t->es != 0x23 ||
	         t->fs != 0x23 ||
	         t->gs != 0x23 ||
	         t->ss != 0x23 ) 
	    {
	        printf ("contextCheckThreadRing3Context: segments fail t={%d}\n", 
				tid );
	        return (int) 1; 
	    };

    	//@todo: Continua checagem ...	
	};


	// Ok o contexto foi aprovado para ring 3. 
	// Retorna 0.

	return (int) 0;
};


/*
 * KiCheckTaskContext:
 *     Chama módulo interno pra checar o contexto de uma thread. */
 
int KiCheckTaskContext (int thread_id){
	
	//@todo: filtrar argumento.
    
	return (int) contextCheckThreadRing3Context(thread_id);
};


void KiSaveCurrentContext (){
	
    save_current_context ();
};


void KiRestoreCurrentContext (){
	
    restore_current_context ();
};

 
/*
 * save_context_of_new_task: */

void save_context_of_new_task (int id, unsigned long *task_address){
	
	//return;    /* CANCELADA !*/
};


//
// End.
//

