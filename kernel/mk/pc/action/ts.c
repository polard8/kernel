/*
 * File: mk\pc\ts.c
 *
 *     Task Switching.
 *
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
 * History:
 *     2015 - Created by Fred Nora.
 *     2016 - Revision.
 *     //...
 */


#include <kernel.h>
 
 
//
// Variáveis internas.
//
  
int lock_taskswitch;  
//int __taskswitch_lock;
//...


  
//  
// Funções internas.  
//

void taskswitchRR();
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
 
void KiTaskSwitch (){
	
	//Limits.
	
	if ( current_thread < 0 || current_thread >= THREAD_COUNT_MAX )
	{	
	    printf("KiTaskSwitch error: current_thread TID={%d}", 
		    current_thread );										   
        die();
	}
	
	if ( current_process < 0 || current_process >= PROCESS_COUNT_MAX )
	{
		
	    printf("KiTaskSwitch error: current_thread TID={%d}",
		    current_process );										   
        die();
	}
	
	debug_print("ts ");
	

	// ## Task switch ##
	
	task_switch ();
	
    // obs: 
	// Nessa hora ja temos um thread atual e um processo atual selecionados.
    // podemos checar as variáveis para conferir se não está fora dos limites.
    // Se estiverem fora dos limites, podemos usar algum etodo para selecioanrmos 
    // outro processo ou outra thread com limites válidos.
	
	//Retornando para _irq0 em head\x86\hw.inc.
};


/*
 * task_switch:
 *
 *     Gerencia a rotina de troca de thread, realizando operações de 
 * salvamento e restauração de contexto, seleciona a próxima thread 
 * através do scheduler, despacha a thread selecionada através do 
 * dispatcher e retorna para a função _irq0 em hw.inc, que 
 * configurará os registradores e executará a thread através do 
 * método iret.
 *
 * Obs:
 *     Apenas a interface KiTaskSwitch chama essa rotina.
 */
 
void task_switch (){
	
	//#importante
	//Vamos lidar com a thread atual, que é a thread
	//que foi interrompida pelo timer.
	
	int New;
	int Max;    
	
	//@todo: Melhorar o nome dessas variáveis.
	struct process_d *P;         // Processo atual. 
    struct thread_d *Current;    // Thread atual. 	
	//...
	
	// Obs: Devemos atualizar a variável global que indica quel é a thread atual 
	//      e a variável global que indica qual é o processo atual.
	//      >> Essas variáveis sofre alterações durante essa rotina. Pois 
	// quando essa rotina começa, as veriáveis representam o contexto antigo, e 
	// quando essa rotina termina as variáveis devem representar o próximo contexto.
	//      >> Portanto a única atualização que interessa é no termino dessa rotina.
	//         ?? Essa atualização pode ser feita na interface KiTaskSwitch ??
	
	Max = DISPATCHER_PRIORITY_MAX;
	
	
	//
	// ## Thread atual.
	//

	
	// Valida 'Struct' da thread atual.	
	
    Current = (void *) threadList[current_thread]; 
	
	if ( (void *) Current == NULL )
	{
	    printf("ts-task_switch: Struct={%x}", (void *) Current );										   
        die();
	}

	
	//
	// ## Thread atual.
	//

	
	// Processo atual.
	// No caso da estrutura do processo so qual o thread 
	// pertence ser inválida.
	// Obs: Não queremos que a thread pertença a um processo inválido.
    
	P = (void *) Current->process;
	
	if ( (void *) P == NULL ){
		
	    printf("task_switch error: P Struct={%x}", (void *) P );										   
        die();		
	}
	
	//Ok o processo ao qual o thread pertence é um processo válido.
	if ( (void *) P != NULL )
	{
		/* #testar #bugbug ... antes de liberarmos esse filtro precisamos 
		                       atualizar corretamente o current process
							   no fim da rotina de task switch. Talvez até mesmo em spawn 
							   e init idle thread.
                               							   
		//Conferindo se o valor salvo na estrutura do processo é o mesmo 
		//que foi salvo na variável global que indica qual é o processo atual.
		if( P->pid != current_process ){
	        printf("task_switch error: P->pid != current_process ");										   
            die();					
		}
		*/
		
		//Obs: Se o if mais acima for verdadeiro essa 
		//atualização não é nessessária. 
		
		if ( P->used == 1 && P->magic == 1234 )
		{	
		    current_process = (int) P->pid;
		}
		
		//Obs: Podemos fazer outros testes referentes ao 
		//processo que o thread pertence.
		//...
		
	};
	//...	
	
	
	//
	// ## Contagem ##
	//
	
	
	//            step: Quantas vezes ela já rodou no total.
	//    runningCount: Quanto tempo ela está rodando antes de parar.

	Current->step++; 
	
	//quanto tempo em ms ele rodou no total.
	Current->total_time_ms = (unsigned long) Current->total_time_ms + (1000/sys_time_hz);	
	
	//incrementa a quantidade de ms que ela está rodando antes de parar.
	//isso precisa ser zerado quando ela reiniciar no próximo round.
	Current->runningCount_ms = (unsigned long) Current->runningCount_ms + (1000/sys_time_hz);	

	Current->runningCount++;
	
	// @todo: Agora a estrutura de processo tem uma 
	// variável double Cycles.
	// A contagem de ticks será registrada na estrutura 
	// do processo também.      

    //Outras configurações iniciais.
	
	
	//
	// ## locked ##
	//	
	
	
	//  LOCKED:
	//  O mecanismo de task switch está desligado, mas a tarefa é válida para 
	//  user mode. 
	//  Retorna sem salvar o contexto.
	//  @todo: 
	//      Checar a tarefa atual. Seu iopl. (Deve ser ring0).
	//      importante: Não colocamos isso na interface KiTaskSwitch porque 
	//                   é bom fazermos todas as checagens antes de acionarmos 
	//                   essa condicional. 
	
	if ( task_switch_status == LOCKED )
	{    		
	    // @todo: 
	    // Incrementar o tempo que todas as outras estão sem rodar.
	    // Usando a thread list.
	    // @todo: Checar contexto. iopl. stacks.    
		
		// Atualiza a contagem de tipo de seleção.
		IncrementDispatcherCount(SELECT_CURRENT_COUNT);
		
		// Obs: taskswitch locked, Retorna sem salvar.
		return;  
	};
	
	
	
	//
	// ## unlocked ##
	//		
	
	
	// UNLOCKED:
	// O mecanismo de taskswitch esta destravado, podemos usa-lo.
	// > Salvamos o contexto.
	// > Retornameo se não venceu a cota.
	// > Se venceu a cota é preempção por vencimento de cota.
	// > Checamos se existe uma thread no estado standby, querendo rodar pela primeira vez.
	//   Se ouver essa rotina é desviada para um spawn e não prossegue.
	// > Checamos se existem 'requests': Pedidos pendentes.
	
	if ( task_switch_status == UNLOCKED )
	{   
		//
	    // ## SAVE CONTEXT ##
	    //
		
	    save_current_context ();
	    Current->saved = 1;	
				
        // Checa o 'quantum'. 
		//(Limite que uma thread pode usar o processador).
        // Continua rodando até vencer a cota.		
		// @todo: Talvez possa restaurar antes de retornar.
		// Retorna sem restaurar, se ainda não venceu a cota.
		
		if ( Current->runningCount < Current->quantum )
		{
			// Atualiza a contagem de tipo de seleção.
			IncrementDispatcherCount (SELECT_CURRENT_COUNT);
			return; 
		
		}else{
			
		    //
			// ## PREEMPT ##
			//
			
				//debug_print(" preempt ");
			
		    // Aqui a thread atual pode estar no estado running ou initialized.
		    // +Se estiver running, torna ready. (preempt).
		    // +Se estiver initialized, vai checar e executar mais a frente.
		    // #bugbug ?? E se tiver em outro estado ?? O que fazemos ??
		
		    // * MOVEMENT 3 (Running --> Ready).
		    if ( Current->state == RUNNING )
		    {
                // MOVEMENT 3 (running >> ready)  				
			    Current->state = READY;    //Preempt.
		    
			    // Início da fila onde a prioridade é menor.
			    if ( Current->preempted == PREEMPTABLE )
				{
					debug_print(" preempt_q1 ");
					// @todo: Nesse momento prioridade pode ser baixada para 
					// o nível de equilíbrio.
			        queue_insert_head ( queue, (unsigned long) Current, 
					    QUEUE_READY );	
			    };
			
			    // Fim da fila onde a prioridade é maior.
			    if ( Current->preempted == UNPREEMPTABLE )
				{
					debug_print(" preempt_q2 ");
					//Obs: Não abaixa a prioridade.
			        queue_insert_data( queue, (unsigned long) Current, 
						QUEUE_READY );	
			    };
			    //Nothing.
		    };
		    
			debug_print(" ok ");
			//
			// ## EXTRA ##
			//
			
			
			// #IMPORTANTE
			// O RECORRENTE É ESCOLHERMOS UMA THREAD DA FILA DO DISPATCHER 
			// NESSE MOMENTO. MAS DE TEMPOS EM TEMPOS VAMOS FAZER ALGUMA 
			// ATIVIDADE EXTRA QUE EXIGEM BASTANTE TEMPO DE PROCESSAMENTO.
			// Obs: A flag 'extra' é acionada pelo dd\timer.c de tempos 
			// em tempos.
			
			// @todo:
			// A tarefa mais próxima de sua Dead Line é a tarefa de maior 
			// prioridade.
			// check_for_ ... (mais próxima da deadline)	

			// *IMPORTANTE:
			// schedi.c
			// Checando se tem threads em standby que estão esperando pra 
			// rodar pela primeira vez.
		    // Obs: Essa chamada não retorna se encontrar uma thread assim. 

            // Request:
            // Esse é o momento ideal para atender os requests. 
			// Pois a thread que estava utilizando o processador, 
			// utilizou toda a sua cota. 			 
			// Então agora atendemos o request, (Internal Signal), 
			// somente depois de a thread ter utilizado o processador 
			// durante todo o tempo que lhe foi concedido. :)			
			
			if (extra == 1)
			{
				KiRequest ();
				
				extra = 0;
			}	
			
			// sempre
			// Isso precisa ser sempre ou então o processo init não 
			// vai rodar, pois é essa rotina que muda todos os processos 
			// para running.
			// #obs: poderíamos especialmente mudar manualmente 
			// os primeiros processos para running, deixando assim essa 
			// rotina para rodar de tempos em tempos.
			
			//#bugbug
			//checar demosra, pois tem que olhar todas.
			//precismos de uma flag de alerta.??
			
			//debug_print(" check_for_standby \n");
			
			// fica em schedi.c
            check_for_standby (); 
			
		    // #importante
            // Não havendo thread para ser inicializada, nem request, 
			// então roda uma thread da fila do dispatcher.
			
			//debug_print(" goto try_next ");
			
		    goto try_next;
			
			//Nothing.
		};
	    //Nothing.
	};
	
    
	// * Se estamos aqui é porque houve uma falha anormal. Então tentaremos 
	//   selecionar a próxima thread. 
	
	
//crazyFail:
	
	goto dispatch_current;      	
	
	
	//
	//    ####  NEXT ####
	//
	
	
	// Seleciona a Current, usando a fila do dispacher.
	
try_next: 
	
    debug_print(" N ");
	
	
	//se temos apenas uma thread, ela não terá next.
	//não ha porque checar o próximo.
	if (ProcessorBlock.threads_counter == 1)
	{
		//#nao tem problema
		//o execve do gramado core vai atualizar IdleThread,
		//reutilizando a estrutura.
		
		debug_print(" JUSTONE ");
		Conductor = IdleThread;
		
		goto go_ahead;
	}


	// Obs: 
	// No pior dos casos o condutor irá parar no fim da lista.
	
	//
	// ## IMPORTANTE ##
	//
	
	// ?fim
	// Checa se é o último da lista encadeada.
	// Se for o último da lista encadeada, vamos reconstruir a lista.
	// Um lista representa um round.
	
	// #obs:
	// Podemos tentar outra abordagem e não reescalonarmos toda vez que 
	// um round chegar ao fim. Pois o sistema perderia muito tempo reescalonando 
	// em sistemas com poucas threads rodando.
	// Então dependendo no número de threads podemos reescalonar ao fim de todos 
	// os rounds ou apenas reiniciar o mesmo round por um número determinado de vezes.
	
	//#bugbug:
	//se tivermos apenas uma thread, esse negócio será acionado sempre.
	
	if ( (void *) Conductor->Next == NULL )
	{
		
		debug_print(" LAST ");	
		
		// #Agendar.
		// Fim da lista.  
		// Recriar a lista. 
				
	    //#test 
		//De tempos em tempos escalonamos. 
		//if ( sys_time_ticks_total % 100 == 0 )
	    //{
			// Com a lista atualizada, vá em frente.			
		//    KiScheduler ();	
		//    goto go_ahead;  
	    //}

		// Com a lista atualizada, vá em frente.			
		KiScheduler ();	
		goto go_ahead;  		
	};
	
	
	// ? mais threads na lista ...
	// Se ainda não for o último da lista encadeada.
	// Se tem mais threads na lista, fica fácil selecionar a próxima.
	
	if ( (void *) Conductor->Next != NULL )
	{
	    // O condutor avança e pega o próximo da lista.
		
		Conductor = (void *) Conductor->Next;
		
		goto go_ahead;
		
	}else{ 
	    //@todo: Se o próximo for NULL.
		//goto go_ahead;
	};
	
	
	// *Importante:
	// E se não for o último da lista e próximo for NULL?
	// É o que trataremos logo abaixo.
	
	//Nothing.
	
go_ahead:

    //##############################################//
    //                                              //
    //    #### Uma thread foi selecionada ####      //
    //                                              //
    //##############################################//

	
	// Pronto, temos uma nova thread atual. 
	// Ela é representada pelo 'Conductor'.
	
	Current = (void *) Conductor;
	
	
    // Checa a validade da estrutura.	
    // Se for inválida, tentamos a próxima novamente pegando a 
	// próxima da lista;
	
	
	//
	// ## BUGBUG ##: 
	//
	// Se Current for NULL, certamente não teremos uma next, e teremos uma PF
	// ao tentarmos acessar a estrutura. Para tratar isso podemos tentar 
	// reescalonar antes de tentarmos novamente, daí estrutura vai ser válida.
	// #importante: Tentar a próxima pode significar um loop infinito.
	// Reescalonamos para diminuir a chance de entrarmos em um loop infinito.
	//
	
	if( (void *) Current == NULL )
	{ 
	    // #bugbug 
		// Isso pode gerar um loop infinito.
		// Reescalonamos para diminuir a chance de entrarmos em um 
		// loop infinito.
		
		debug_print(" Struct ");
		
		KiScheduler ();
		
		goto try_next;
		
	} else {
		
		if ( Current->used != 1 || Current->magic != 1234 )
		{

			debug_print(" val ");
			
	        // #bugbug 
		    // Isso pode gerar um loop infinito.
		    // Reescalonamos para diminuir a chance de entrarmos em um 
		    // loop infinito.
		
		    KiScheduler ();
		
		    goto try_next;	
		};		
		
		//Se não está pronta a thread, tentamos novamente.
		
	    if ( Current->state != READY )
		{
			
			debug_print(" state ");
			
	        // #bugbug 
		    // Isso pode gerar um loop infinito.
		    // Reescalonamos para diminuir a chance de entrarmos em um 
		    // loop infinito.
		
		    KiScheduler ();
		
		    goto try_next;	
		};
		
		
		//
		//    ####  Dispatcher ####
		//
		
		// #finalmente
		// Selecionamos uma thread atravéz do dispatcher. 
		// Incrementando a contagem do tipo de seleção.
		// Obs: Current é a thread selecionada.
		// Salvamos o TID da thread selecionada.
		// Despacha a thread selecionada.
		// Essa rotina está logo abaixo.
		
		IncrementDispatcherCount (SELECT_DISPATCHER_COUNT);
		
		current_thread = (int) Current->tid;
		
		goto dispatch_current;    			
	};	
	
	
	//
	// # fail #
	//
	
	//
	// Nothing.
	// @todo: #bugbug. Se estamos aqui é porque houve 
	// uma falha anormal. Vamos optar pela atual e não 
	// tentaremos mais nada.
    //
 	
//superCrazyFail:
	goto dispatch_current; 
	//#Obs: Não tentaremos novamente.
	//goto try_next; 
	
	//Nothing.
	
	
	//
	//    ####  Dispatch current ####
	//	
	
// Nesse momento a current_thread foi selecionada e não tem volta.

dispatch_current:
	
	
	debug_print(" DISPATCH_CURRENT \n");
    
    //
    //    ####  Validation ####
    //	
	
	// Checa a validade da thread selecionada.
	// @todo: Resiliência. Tomar uma decisão e não desistir.
	// A idle é sempre uma última opção.
	
    Current = (void *) threadList[current_thread];
	
	if ( (void *) Current == NULL )
	{
		
		panic ("pc-action-ts-task_switch.dispatch_current: Struct ERROR");
	
	} else {
		
		// @todo: Resiliência. Tomar uma decisão e não desistir.
		// A idle é sempre uma última opção.		
	    
		// Checando a validação.
		// Checando se está pronta.
		
		if ( Current->used != 1 || 
		     Current->magic != 1234 || 
			 Current->state != READY )
	    {
	        panic ("pc-action-ts-task_switch.dispatch_current: validation ERROR");
	    };
		
		// #todo:
        // Obs: 
		// Podemos filtrar outros parâmetros sistemicamente importante.		
		// ...
		
		
	    // Estrutura Current válida.
	    // Vamos configurá-la.
	
	    // Reinicia a contagem de tempo rodando. Isso é, 
	    // quantas vezes a thread usou a CPU até esgotar o quantum, sua cota.
	    
		Current->runningCount = 0;	
		
		// #todo:
		// ??Podemos configurar mais elementos da estrutura??
	
	};
	
	//
	// #### Chama o dispatcher #### 
	//
	
	// #importante:
	// Isso coloca a thread selecionada no estado RUNNING 
	// e restaura o contexto.
	
	//
	// * MOVEMENT 4 (Ready --> Running).
	//
	
	dispatcher (DISPATCHER_CURRENT);    	
	
	// #importante: 
	// Retornamos do dispatcher.
	// O dispatcher restaurou o contexto para a próxima thread, 
	// passando os valores da estrutura para variáveis que serão 
	// usadas para carregar os registradores na hora do iretd.
	// Agora vamos retornar para a rotina da _irq0 feita em assembly, 
	// que está em head\x86\hw.inc, mas antes, voltamos para a 
	// interface KiTaskSwitch() que chamou essa rotina.
	
	//
    //  #### DONE ####
	//
	
done:
    
	// #importante 
	// Nesse momento não mais o que fazer.
	// Apenas checaremos a validade de algumas coisas, mas não faremos 
	// mais nenhuma configuração.
	// No caso de erro de validade, apenas abortamos.

    // #importante
	// Estamos prestes a retornarmos para a interface que retorna 
	// para o assembly.
	
	//	
	//    ## Overflow ## 
	//
	
	// Checar se não é maior que o número máximo de índices 
	// que a lista suporta.
	
	if ( Current->ownerPID < 0 || Current->ownerPID >= THREAD_COUNT_MAX )
	{
		printf ("action-ts-task_switch: ownerPID ERROR \n", Current->ownerPID );
		die();
	};
	
	
	//
	//    ## PROCESS ## 
	//
	
	
    P = (void *) processList[Current->ownerPID];
	
	// Estrutura inválida
	
	if ( (void *) P == NULL )
	{
		printf("action-ts-task_switch: Process %s struct fail \n", P->name_address );
		die();
	};
	
	// Estrutura válida.
	
	if ( (void *) P != NULL )
	{
		// Corrompida.
		if ( P->used != 1 || P->magic != 1234 )
		{
		    printf("action-ts-task_switch: Process %s corrompido \n", 
			    P->name_address );
		    die();			
		};
			
		// Não corrompida.	
		if ( P->used == 1 && P->magic == 1234 )
		{
		    current_process = (int) P->pid;
			
			
            // # PAGE DIRECTORY #
			
			if ( (unsigned long) P->DirectoryPA == 0 )
			{	
		        printf ("action-ts-task_switch: Process %s directory fail\n", 
				    P->name_address );
		        die();
			};
			
			// #BUGBUG
			// Esse salvamento parece desnecessário.
			
			current_process_pagedirectory_address = (unsigned long) P->DirectoryPA;
		    
			goto doneRET;
		};
		
		
		//
		//  ## Fail ##
		//
		
		panic ("action-ts-task_switch: *** Struct  *** \n");
	};
	
	//
	//  ## Fail  ##
	//
	
	panic ("action-ts-task_switch: bug sinistro kkk \n");
	
	
	//
	//   #### Return ####
	//
	
	
doneRET:
	
    // #importante 
    // Esse é o retorno planejado.
    // Se estamos aqui é porque todas as etapas foram cumprindas com sucesso. 	
	// Nesse momento retornaremos para a interface que chamou essa função.
	// Depois a interface retorna para o assembly que está atendendo a irq0.
	// Obs: Nesse momento o cr3 já está configurado.
	// :)
	
	return; 		
};


/*
 * taskswitchRR:
 *     Task switch usando Round Robin.
 *     Obs: Esse método ainda não foi habilitado.
 */
void taskswitchRR()
{
	int i;
	int Max = (int) ProcessorBlock.threads_counter;
	struct thread_d *Current; //Thread atual.
	
	//Filtro.
	//if(current_thread ...){}
	
	Current = (void *) threadList[current_thread]; 
	if((void *) Current == NULL)
	{
	    panic("taskswitchRR error: Struct");
		//die();
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
	//Obs: Cuidado !! A média é (PRIORITY_NORMAL*2)
	if(Current->runningCount < Current->quantum){ 
		goto dispatch_current;
	}else{
		
        //?? @todo: Talvez aqui seja o movimento 3, running >> ready. Conferir.  		
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
			if(i < Max)
			{
		        Current = (void *) threadList[i];
		        if( (void *) Current != NULL )
			    {
			        if( Current->used == 1 && 
					    Current->magic == 1234 && 
						Current->state == READY)
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
				    if( Current->used == 1 && 
					    Current->magic == 1234 && 
						Current->state == READY )
					{
					    Current->runningCount = 0;
					    current_thread = (int) i;
						goto dispatch_current;
					};
				};
			};

		}while(i < Max);
			
        panic("taskswitchRR error: *HANG");
  			
		//Use idle. Não havendo outra alem da idle usa ela.
		//current_idle_thread.
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
 ***************************************************
 * set_task_status:
 *    Configura o status do mecanismo de task switch.
 *    Se o mecanismo de taskswitch estiver desligado 
 * não ocorrerá a mudança.
 *
 * @todo: Mudar o nome dessa função para taskswitchSetStatus(.);
 *
 */ 
void set_task_status( unsigned long status )
{
    //#bugbug: Mudar para int.	
	task_switch_status = (unsigned long) status;
};


/*
 **************************************************
 * get_task_status:
 *     Obtem o status do mecanismo de taskswitch.
 *
 * @todo: Mudar o nome dessa função para taskswitchGetStatus();.
 */
unsigned long get_task_status()
{
    //#bugbug: Mudar para int.		
    return (unsigned long) task_switch_status;
};


/*
 **********************************************
 * taskswitch_lock:
 *     Trava o mecanismo de taskswitch.
 *     @todo: Mudar para taskswitchLock().
 */ 
void taskswitch_lock (){
	
    task_switch_status = (unsigned long) LOCKED;
};


/*
 *********************************************
 * taskswitch_unlock:
 *     Destrava o mecanismo de taskswitch.
 *     @todo: Mudar para taskswitchUnlock().
 */ 
void taskswitch_unlock (){
	
    task_switch_status = (unsigned long) UNLOCKED;
};


//
// End.
//
