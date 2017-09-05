/*
 * File: taskswitch.c
 *
 * Descrição:
 *     Faz parte do Process Manager, parte fundamental do Kernel Base.
 *     Rotinas de Task Switch. Salva o contexto da tarefa, chama o scheduler 
 * pra trocar a tarefa e depois chama o dispatcher pra rodar a próxima.
 *     O Task Switch é feito de mais de uma maneira, de acordo com o modo 
 * selecionado. (rr, prioridade ...)
 *     The most common reasons for a context switch are:
 *     The time slice has elapsed.
 *     A thread with a higher priority has become ready to run.
 *     A running thread needs to wait.
 *
 * Histórico:
 *     Versão 1.0, 2015 - Esse arquivo foi criado por Fred Nora.
 *     Versão 1.0, 2016 - Aprimoramento geral das rotinas básicas.
 *     //...
 */


#include <kernel.h>
 
 
//
// Variáveis internas.
//
  
int lock_taskswitch;  
//int taskswitchLock;  //@todo Criar
//...


  
//  
// Funções internas.  
//

void taskswitchRR();
//void task_switch_rr();  //@Mudar para taskswitchRR().
//...



//
// ...
//

/*
void taskswitchFlushTLB();
void taskswitchFlushTLB(){
	//@todo: Implementar.
	return;
}
*/

/*
 * KiTaskSwitch:
 *     Interface para chamar a rotina de Task Switch.
 *     KiTaskSwitch em taskswitch.c gerencia a rotina de troca de thread, 
 * realizando operações de salvamento e restauração de contexto utilizado 
 * variáveis globais e extrutura de dados, seleciona a próxima thread através 
 * do scheduler, despacha a thread selecionada através do dispatcher e 
 * retorna para a função _irq0 em hardware.inc, que configurará os 
 * registradores e executará a thread através do método iret.
 * Na verdade, esta servido de interface pra uma rotina que faz tudo isso.
 * 
 */
void KiTaskSwitch()
{
	//
	// @todo: Fazer alguma rotina antes aqui ?!
    //
	
done:
	task_switch();
    return;
};



/*
 * task_switch:
 *     Gerencia a rotina de troca de thread, realizando operações
 * de salvamento e restauração de contexto, seleciona a próxima thread
 * através do scheduler, despacha a thread selecionada através do dispatcher
 * e retorna para a função _irq0 em hardware.inc, que configurará os registradores
 * e executará a thread através do método iret.
 *
 *
 * Obs:
 *     Apenas a ISR0, _irq0, pode chamar essa rotina.
 * 
 */
void task_switch()
{
	int New;
	int Max;   
    struct thread_d *Current;  //Thread atual. 	
    struct process_d *P;       //Processo atual. 	
	//...
	
	Max = DISPATCHER_PRIORITY_MAX;
	
	//
	// Valida 'Struct' e 'ID' da thread atual.	
	//

	//Limits.
	if(current_thread < 0 || current_thread >= THREAD_COUNT_MAX ) 
	{
	        printf("task_switch error: Id, current_thread={%d}",current_thread);										   
		    refresh_screen();
		    while(1){}
	}
	else
	{
	    Current = (void *) threadList[current_thread]; 
	    if( (void*) Current == NULL ){
	        printf("task_switch error: Struct={%x}",(void*) Current);										   
		    refresh_screen();
		    while(1){}
	    };
		//Nothing.
	};
	
	//Contagem.
	//step: Quantas vezes ela já rodou no total.
	//runningCount: Quanto tempo ela está rodando antes de parar.
	Current->step++;          
	Current->runningCount++;

    //Outras configurações iniciais.
	
	//Processo atual.
    P = (void*) Current->process;
	if( (void*) P != NULL )
	{
		if(P->used == 1 && P->magic == 1234){
		    current_process = (int) P->pid;
		};
	};
	//...	
	
	/*
	 * LOCKED:
	 *     O mecanismo de task switch está desligado, 
	 *     mas a tarefa é válida para user mode. 
	 *     Retorna sem salvar o contexto.
	 *
	 * @todo: 
	 *     Checar a tarefa atual. seu iopl.(deve ser ring0)
	 *
	 */
	if(task_switch_status == LOCKED)
	{    		
		//
		// @todo: Incrementar o tempo que todas as outras estão sem rodar.
		// usando a thread list.
		//
		
		//@todo: Checar contexto. iopl. stacks.
		
		//
		//taskswitch locked,
		//Retorna sem salvar.
		//
		
		IncrementDispatcherCount(SELECT_CURRENT_COUNT);
		return;  
	};
	
	//UNLOCKED.
	if(task_switch_status == UNLOCKED)
	{   

		//
	    // * SAVE CONTEXT.
	    //
		
	    save_current_context();
	    Current->saved = 1;	
				
        // Checa o 'quantum'. (Limite que uma thread pode usar o processador).
		if( Current->runningCount < Current->quantum )    
		{  
            //Continua rodando atá vencer a cota.
			
			//@todo: talvez possa restaurar antes de retornar.
			// retorna sem restaurar,se ainda não venceu a cota.
			IncrementDispatcherCount(SELECT_CURRENT_COUNT);
			return; 
		}
		else    //Vencido o quantum.
		{
			
		    //
		    //    Aqui a thread atual pode estar no estado running ou initialized.
		    //    +Se estiver running, torna ready. (preempt).
		    //    +Se estiver initialized, vai checar e executar mais a frente.
		    //
		
		    // * MOVEMENT 3 (Running --> Ready).
		    if(Current->state == RUNNING)
		    {   
		        //Preempt.
			    Current->state = READY;
		    
			    //Início da fila onde a prioridade é menor.
			    if(Current->preempted = PREEMPTABLE){
					//@todo: Nesse momento prioridade pode ser baixada para o nível de equilíbrio.
			        queue_insert_head(queue, (unsigned long) Current, QUEUE_READY);	
			    };
			
			    //fim da fila onde a prioridade é maior.
			    if(Current->preempted = UNPREEMPTABLE){
					//Obs: Não abaixa a prioridade.
			        queue_insert_data(queue, (unsigned long) Current, QUEUE_READY);	
			    };
			    //Nothing.
		    };
		    
			//
			//@todo:
			//A tarefa mais proxima de sua dead line e 
			//a tarefa de maior prioridade.
			//check_for_ ... (mais proxima da deadline)
			//
			
			//
			// *IMPORTANTE:
			// Checa se tem threads em standby 
			// esperando pra rodar pela primeira vez.
			// Não retorna se encontrar. 
			// @todo: na verdade essa função deveria se chamar check for standby
			//
			check_for_initialized(); 
            
            //
            // Request:
            // Esse é o momento ideal para atender os requests. Pois a thread
            // que estava utilizando o processador, utilizou toda a sua cota. 			 
			// Então agora atendemos o request, (Signal), somente depois de a 
			// thread ter utilizado o processador durante todo o tempo que lhe 
			// foi concedido. :)
            //			
			
			KiRequest();
			//request();
			
            //
            // Não havendo thread para ser inicializada, nem request, roda uma 
			// thread da fila do dispatcher.
            //
			
		    goto try_next;
		};
	    //Nothing.
	};
	
    //
	// * Se estamos aqui é porque houve uma falha anormal. Então
	//   tentaremos selecionar a próxima thread. 
	//
	
	goto dispatch_current;      	
	
	
	//
	// try_next:
	//     Seleciona a Current usando a fila do dispacher.
	//
	
try_next: 

	//
	// No pior dos casos o condutor irá parar no fim da lista.
	//
	
	//Checa se é o último da lista.
	if( (void*) Conductor->Next == NULL )
	{
		//Fim da lista. 
		//Recriar a lista. (#Agendar).
		//@todo: Use thid interface KiScheduler();
		//KiScheduler();
		scheduler();     
		goto go_ahead;  //Com a lista atualizada, vá em frente.
	};
	
	//Se ainda não for o último da lista.
	if( (void*) Conductor->Next != NULL )
	{
	    //O condutor avança e pega o próximo da lista.
		Conductor = (void*) Conductor->Next;
		goto go_ahead;
	}else{ 
	    //@todo: Se o próximo for NULL.
		//goto go_ahead;
	};
	//@todo: E se não for o último da lista e próximo for NULL?
	//Nothing.
go_ahead:
    
	//
	// Pronto, temos uma nova thread atual.	
    //
	
	Current = (void *) Conductor;
	
    //Checa a validade da estrutura.	
	if( (void *) Current == NULL )
	{ 
        //
        // Se for inválida, tentamos novamente.
		// @todo: #bugbug Isso pode gerar um loop infinito.
		//
		goto try_next;  
	}
	else
	{
		//
		// Obs: O 'else' é para o caso da estrutura ter um ponteiro válido.
		// Agora checamos os outros parâmetros da estrutura.
		//
		
		//Se for inválido. (Estrutura corrompida).
		if( Current->used != 1 || Current->magic != 1234){
			//Tentamos novamente.
			//@todo: #bugbug Isso pode gerar um loop infinito.
			goto try_next;	
		};		
		//Se não está pronta a thread.
	    if( Current->state != READY){
			//Tentamos novamente.
			//@todo: #bugbug Isso pode gerar um loop infinito.			
	        goto try_next; 
		};
		
		//
		// Selecionamos uma thread atravéz do dispatcher. Incrementando a 
		// contagem do tipo de seleção.
		//
		IncrementDispatcherCount(SELECT_DISPATCHER_COUNT);
		
		//Obs: Current é a thread selecionada.
		//Salvamos o TID da thread selecionada.
		current_thread = (int) Current->tid;
		goto dispatch_current;  //Dispacha a thread selecionada.  			
	};	
	
	//
	// Nothing.
	// @todo: #bugbug. Se estamos aqui é porque houve uma falha anormal. Vamos
    // optar pela atual e não tentaremos mais nada.
    //
 	
	goto dispatch_current; 
	//goto try_next; //#Obs: Não tentaremos novamente.
	
	//Nothing.
	
//	
// Done.
// Nesse momente a current_thread foi selecionada e não tem volta.
//
dispatch_current:
    
	//
	// Última filtragem, só por paranóia.
	// 
	// if(current_thread < 0 || current_thread >= THREAD_COUNT_MAX ){
	//     goto try_next;
	// };
    //
	
	//Checa a validade da thread selecionada.
    Current = (void *) threadList[current_thread];
	if( (void *) Current == NULL )
	{
		//@todo: Resiliência. Tomar uma decisão e não desistir.
	    //A idle é sempre uma última opção.
		panic("task_switch.dispatch_current error: Struct");
	    while(1){};
	}
	else
	{
	    if( Current->used != 1 || 
		    Current->magic != 1234 || 
			Current->state != READY )
	    {
			//@todo: Resiliência. Tomar uma decisão e não desistir.
			//A idle é sempre uma última opção.
	        panic("task_switch.dispatch_current error: Param.");
	        while(1){}
	    };
        //Obs: Podemos filtrar outros parâmetros sistemicamente importante.		
		//Nothing.
	};
	
    //
	// runningCount:
	// Reinicia a contagem de tempo rodando. Isso é, quantas vezes a thread usou 
	// a CPU até esgotar o quantum, sua cota.
    //
	
	Current->runningCount = 0;
	
	//
	// Chama o dispatcher.
	// Coloca a thread selecionada no estado RUNNING e
    // restaura o contexto.
	//
	
	//
	// * MOVEMENT 4 (Ready --> Running).
	//
	
	dispatcher(DISPATCHER_CURRENT);    	
	
	//
	// Retornamos do dispatcher.
	// O dispatcher restaurou o contexto para a próxima thread. Passando
	// os valores da estrutura para variáveis que serão usadas para carregar 
	// os registradores na hora do iretd.
	// Agora vamos retornar para a rotina da ISR0 em assembly, 
	// que está em hardware.inc.
	//
	
	//Nothing.
	
//Done.
done:
    
	//
	// @todo: Salvar em uma variável global o cr3 do processo da thread selecionada
    // para que a rotina em assembly, (hardware.s), configura o cr3.	
	//
	
	
	
    P = (void*) processList[Current->ppid];
	
	//estrutura inválida
	if( (void*) P == NULL ){
		//fail;
		printf("taskswitch: Process %s struct fail \n", P->name_address);
		refresh_screen();
		while(1){}
	}
	
	//estrutura válida.
	if( (void*) P != NULL )
	{
		//corrompida
		if(P->used != 1 || P->magic != 1234){
				//fail
		       printf("taskswitch: Process %s corrompido \n", P->name_address);
		       refresh_screen();
		       while(1){}			
		}
			
		//não corrompida.	
		if(P->used == 1 && P->magic == 1234)
		{
		    current_process = (int) P->pid;
			
			//Debug:
			//@todo: Isso é provisório.
			//So deixaremos passar o diretório do processo kernel.
			//if( (unsigned long) P->Directory != KERNEL_PAGEDIRECTORY){
			
			//Obs: #bugbug: Aviso.
			//Permite vários endereços, menos 0.
			//Um endereço inválido pode ser colocado em cr3, travando o sistema.
			
			if( (unsigned long) P->Directory == 0 ){	
				//fail
		       printf("taskswitch: Process %s directory fail \n", P->name_address);
		       refresh_screen();
		       while(1){}
			}
			current_process_pagedirectory_address = (unsigned long) P->Directory;
			//current_process_pagedirectory_address = (unsigned long) P->page_directory->Address;
		};
	};
	
	
	
	//Debug:
	//Provisório
	//current_process_pagedirectory_address = (unsigned long) KernelProcess->Directory;
	//current_process_pagedirectory_address = (unsigned long) KERNEL_PAGEDIRECTORY;
	
    // 
	// Done.
	// Ao retornar, a rotina ISR0 em assembly, atualiza o registrador CR3 com o 
	// ponteiro para o diretório de páginas do processo ao qual a thread pertence, 
	// alimenta os registradores e efetua iretd. #fim :)
	//
	return; 		
};



/*
 * taskswitchRR:
 *     Task switch usando Round Robin.
 */
void taskswitchRR()
{
	int i;
	int Max = (int) ProcessorBlock.running_tasks;
	struct thread_d *Current; //Thread atual.
	
	//Filtro.
	//if(current_thread ...){}
	
	Current = (void *) threadList[current_thread]; 
	if((void *) Current == NULL){
	    panic("taskswitchRR error: Struct");
		while(1){}
	};
	
	//
	//todo: Checar se a estrutura é válida. 
	//
	
	/*
	 *    Incrementa.
	 *     Continua na mesma tarefa enquanto a contagem de quantum for
	 *     menor que o quantum limite da tarefa atual.
	 *     Assim temos uma contagem de vezes que uma tarefa deve ficar
     *     no processador sem sair.	 
	 */	


	//se o runningCount ainda é menor que a cota, dispacha.
	if(Current->runningCount < 9)    //Current->Quota.
	{ 
		goto dispatch_current;
	}
	else
	{	
		Current->state = READY;
		
		//
		// @todo: Nesse momento, colocar no fim da fila ready. tail
		//
		//queue_insert_data( queue, (unsigned long) Current, QUEUE_READY);
		
		//se ouver outra válida nos slots despacha.
		i = (int) current_thread;
				
		do
		{
		    i++;
			
			//Contando++
			if( i < Max)
			{
		        Current = (void *) threadList[i];
		        if( (void *) Current != NULL )
			    {
			        if( Current->used == 1 && Current->magic == 1234 && Current->state == READY)
				    {
				        Current->runningCount = 0;
				        current_thread = (int) i;
				        goto dispatch_current;
				    };
			    };
			};
			
			// Overflow
			if(i >= Max)
			{ 
			    i = 0; 
				Current = (void *) threadList[i];
			    if( (void *) Current != NULL )
				{
				    if( Current->used == 1 && Current->magic == 1234 && Current->state == READY)
					{
					    Current->runningCount = 0;
					    current_thread = (int) i;
						goto dispatch_current;
					};
				};
			};

		}while( i < Max);
			
        panic("taskswitchRR error: *HANG");
        while(1){}   			
		//Use idle. Não havendo outra alem da idle usa ela.
		//current_thread = (int) 0;
		//goto dispatch_current;
	}; 
	
//	
// Done.
//
dispatch_current:	
	dispatcher(DISPATCHER_CURRENT);	
	return;	
};




/*
 * set_task_status:
 *    Configura o status do mecanismo de task switch.
 *    Se o mecanismo de taskswitch estiver desligado não ocorrerá a mudança.
 *
 * @todo: Mudar o nome dessa função para taskswitchSetStatus(.);
 *
 */ 
void set_task_status(unsigned long status)
{  
	//@todo: criar estrutura.
	task_switch_status = (unsigned long) status;
	return;
};


/*
 * get_task_status:
 *     Obtem o status do mecanismo de taskswitch.
 *
 * @todo: Mudar o nome dessa função para taskswitchGetStatus();.
 */
unsigned long get_task_status()
{
    return (unsigned long) task_switch_status;
};


/*
 * taskswitch_lock:
 *     Trava o mecanismo de taskswitch.
 *     @todo: Mudar para taskswitchLock().
 */ 
void taskswitch_lock()
{
    task_switch_status = (unsigned long) LOCKED;
	return;
};


/*
 * taskswitch_unlock:
 *     Destrava o mecanismo de taskswitch.
 *     @todo: Mudar para taskswitchUnlock().
 */ 
void taskswitch_unlock()
{
    task_switch_status = (unsigned long) UNLOCKED;
	return;
};


//
// Fim.
//
