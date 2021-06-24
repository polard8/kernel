



#include <kernel.h>    

/*
 **********************************************************
 * task_switch:
 *
 * Switch the thread.
 * Save and restore context.
 * Select the next thread and dispatch.
 * return to _irq0.
 * Called by KiTaskSwitch.
 */
 
void task_switch (void)
{
	// #todo
}



/*
 ****************************************************
 * psTaskSwitch:
 * 
 *     Interface para chamar a rotina de Task Switch.
 *     Essa rotina somente é chamada por hw.inc.
 *     KiTaskSwitch em ts.c gerencia a rotina de 
 * troca de thread, realizando operações de salvamento e 
 * restauração de contexto utilizado variáveis globais e 
 * extrutura de dados, seleciona a próxima thread através 
 * do scheduler, despacha a thread selecionada através do 
 * dispatcher e retorna para a função _irq0 em hw.inc, 
 * que configurará os registradores e executará a 
 * thread através do método iret.
 *
 * #importante:
 * Na verdade, é uma interface pra uma rotina que 
 * faz tudo isso.
 * 
 */
 
/*
	// @todo: Fazer alguma rotina antes aqui ?!
	
	// Obs: A qui poderemos criar rotinas que não lidem com a troca de 
	// threads propriamente, mas com atualizações de variáveis e gerenciamento 
	// de contagem.
	// >> Na entrada da rotina podemos atualizar a contagem da tarefa que acabou de rodar.
	// >> A rotina task_switch fica responsável apenas troca de contexto, não fazendo 
	// atualização de variáveis de contagem.
	// >> ?? Na saída ??
	
	// ?? quem atualizou as variáveis de critério de escolha ??? o dispacher ??
*/



// Called by:
// _irq0 in hw.asm

void psTaskSwitch (void){

    // Check current process limits.
    if ( current_process < 0 || current_process >= PROCESS_COUNT_MAX )
    {
        printf ("psTaskSwitch: current_thread %d", current_process );
        die();
    }

    // Check current thread limits.
    if ( current_thread < 0 || current_thread >= THREAD_COUNT_MAX )
    {
        printf ("psTaskSwitch: current_thread %d", current_thread ); 
        die();
    }

#ifdef SERIAL_DEBUG_VERBOSE
    debug_print (".");
    // debug_print ("ts ");
#endif

    //
    // real task switch
    //

    task_switch();

    // obs: 
    // Nessa hora já temos um thread atual e um processo atual 
    // selecionados. Podemos checar as variáveis para conferir se 
    // não está fora dos limites. Se estiverem fora dos limites, 
    // podemos usar algum método para selecionarmos outro processo 
    // ou outra thread com limites válidos.
 
    // #importante:   
    // Retornando para _irq0 em x86/hw.inc.
}

