/*
 * File: ps/disp/x86/x86cont.c
 *
 * Context switching:
 * Saving and restoring the x86 cpu context.
 * Part of the dispatcher module.
 *
 * History:
 *     2015 - Created by Fred Nora.
 */


#include <kernel.h>


extern void set_page_dir (void);


static inline void ckSetCr3 ( unsigned long physical_address )
{
    asm ( "mov %0, %%cr3" : : "r" (physical_address) );
}


/*
static inline uint32_t ckGetCr3()
{
    uint32_t ret;
    __asm__ ( "mov %%cr3, %0 " : "=r"(ret) );
    return ret;
}
*/


// Context:
//     Vari�veis para salvar o contexto.
//     Essas vari�veis devem permanecer encapsuladas
//     nesse arquivo d� m�dulo. Somente esse
//     arquivo ter� acesso � essas vari�veis.
//     
//     *IMPORTANTE:
//         Obviamente a rotina _irq0, que � o handler
//         do timer est� acessando essas vari�veis
//         fazendo uso d 'extern'. 


unsigned long contextSS;        // User mode.
unsigned long contextESP;       // User mode.
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
// #todo: 
// Outros registradores.
// debug
// mmx
// ponto flutuante
// Continua ...
// 




/*
 **************************************
 * save_current_context: 
 * 
 *    Salvando o contexto da thread interrompida pelo timer IRQ0.
 *    O contexto da tarefa interrompida foi salvo em vari�veis pela 
 * isr do timer. Aqui esse contexto � colocado na estrutura que 
 * organiza as threads.
 *
 * @todo: 
 *     Est�o faltando vari�veis nesse contexto, como registradores de 
 * debug e float point por exemplo.
 *     Mudar nome para contextSaveCurrent();.
 */


void save_current_context (void){

    struct thread_d  *t;

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

    if ( current_thread < 0 || current_thread >= THREAD_COUNT_MAX )
    {
        printk ("save_current_context: TID=%d\n", current_thread );
        goto fail0;
    }

    t = (void *) threadList[current_thread];

    if ( (void *) t == NULL ){
        printf ("save_current_context: [ERROR] Struct Thread={%d}\n",
            current_thread );
        goto fail1;
    }

    if ( t->used != TRUE || t->magic != 1234 )
    {
        printf ("save_current_context: [ERROR] Validation Thread={%d}\n",
            current_thread );
        goto fail1;
    }

    // Fill the structure.

    // Stack frame
    t->ss     = (unsigned long) contextss[0];      // usermode
    t->esp    = (unsigned long) contextesp[0];     // usermode
    t->eflags = (unsigned long) contexteflags[0];
    t->cs     = (unsigned long) contextcs[0];
    t->eip    = (unsigned long) contexteip[0];

    // Segments
    t->ds = (unsigned long) contextds[0];
    t->es = (unsigned long) contextes[0];
    t->fs = (unsigned long) contextfs[0];
    t->gs = (unsigned long) contextgs[0];

    t->eax = (unsigned long) contexteax[0];
    t->ebx = (unsigned long) contextebx[0];
    t->ecx = (unsigned long) contextecx[0];
    t->edx = (unsigned long) contextedx[0];
    t->esi = (unsigned long) contextesi[0];
    t->edi = (unsigned long) contextedi[0];
    t->ebp = (unsigned long) contextebp[0];

    // ...

//done:
    return;
fail1:
    show_process_information();
fail0:
    die();
}


/*
 ****************************************************
 * restore_current_context: 
 *     Carregando o contexto da pr�xima thread a ser executada.
 *     Pegando os valores na estrutura e colocando nas vari�veis 
 * que ser�o usadas pelo arquivo em assembly para carregar os valores 
 * dentro dos registradores.
 *
 * @todo:   
 *     Mudar nome para contextRestoreCurrent();.
 */

void restore_current_context (void){

    struct thread_d  *t;

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
    // Continua ...


    if ( current_thread < 0 || current_thread >= THREAD_COUNT_MAX )
    {
        printk ("restore_current_context: TID=%d\n", current_thread );
        goto fail0;
    }

    t = (void *) threadList[current_thread]; 

    if ( (void *) t == NULL ){
        printf("restore_current_context error: t\n");
        goto fail1;
    }

    // Validation
    if ( t->used != TRUE || t->magic != 1234 )
    {
        printf("restore_current_context error: t validation\n");
        goto fail1;
    }

//
// Restore
//

    // Stack frame
    contextss[0]     = (unsigned long) t->ss & 0xffff;  // usermode
    contextesp[0]    = (unsigned long) t->esp;          // usermode 
    contexteflags[0] = (unsigned long) t->eflags;
    contextcs[0]     = (unsigned long) t->cs & 0xffff;  
    contexteip[0]    = (unsigned long) t->eip;

    // Segments
    contextds[0] = (unsigned long) t->ds & 0xffff;
    contextes[0] = (unsigned long) t->es & 0xffff; 
    contextfs[0] = (unsigned long) t->fs & 0xffff; 
    contextgs[0] = (unsigned long) t->gs & 0xffff; 

    contexteax[0] = (unsigned long) t->eax;  
    contextebx[0] = (unsigned long) t->ebx; 
    contextecx[0] = (unsigned long) t->ecx;  
    contextedx[0] = (unsigned long) t->edx; 
    contextesi[0] = (unsigned long) t->esi;  
    contextedi[0] = (unsigned long) t->edi; 
    contextebp[0] = (unsigned long) t->ebp;  
    // Continua...


    // Restore CR3 and flush TLB.

    ckSetCr3 ( (unsigned long) t->DirectoryPA );
    asm ("movl %cr3, %eax");
    asm ("movl %eax, %cr3");

//done:
    return;
fail1:
    show_process_information(); 
fail0:
    die();
    //return;
}


/*
 * check_task_context: 
 */
 
// # cancelada

int contextCheckThreadRing0Context (int tid)
{
    return 0;
}
 

// Checar um contexto valido para threads em ring 3. 
// #bugbug: 
// Nao usaremos mais isso.

int contextCheckThreadRing3Context (int tid){

    struct thread_d *t; 
 
    //...

	// Limits.
	// Erro. Status.

    if ( tid < 0 || tid >= THREAD_COUNT_MAX )
    {
        return FALSE;
    }

    t = (void *) threadList[tid]; 

    if ( (void *) t == NULL )
    {
        return FALSE;
    }

    if ( t->used != TRUE || t->magic != 1234 )
    {
        debug_print("contextCheckThreadRing3Context: validation\n");
        return FALSE;
    }

    // iopl

    if ( t->iopl != 3 )
    {
        debug_print("contextCheckThreadRing3Context: iopl\n");
        return FALSE;
    }

    // Segments

    if ( t->cs != 0x1B || 
         t->ds != 0x23 || 
         t->es != 0x23 ||
         t->fs != 0x23 ||
         t->gs != 0x23 ||
         t->ss != 0x23 ) 
    {
        debug_print("contextCheckThreadRing3Context: segments fail\n" );
        return FALSE; 
    }

    // ...

    // OK: This is a valid thread for ring3.
    return TRUE;
}


/*
 * KiCheckTaskContext:
 *     Chama m�dulo interno pra checar o contexto de uma thread. 
 */
 
int KiCheckTaskContext (int thread_id)
{
	//@todo: filtrar argumento.
    
    return (int) contextCheckThreadRing3Context(thread_id);
}


void KiSaveCurrentContext (void)
{
    save_current_context();
}


void KiRestoreCurrentContext (void)
{
    restore_current_context();
}

 
/*
 * save_context_of_new_task: 
 */

void save_context_of_new_task (int id, unsigned long *task_address)
{
	//return; 
}


//
// End.
//

