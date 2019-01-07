/*
 * File: mk\request.c
 *
 * Descrição:
 *     Arquivo principal da central de requests do kernel.
 *     Rotinas de atendimento dos requests que o kernel recebe dele mesmo. 
 * Requests são solicitações feitas em kernel mode para o kernel atender. Uma 
 * rotina em kernel mode sinaliza um tipo de request através da configuração
 * da variável kernel_request e em algum momento da troca e escalonamento de
 * threads esse request é atendido com a chamada da rotina request().
 *     As requests são para o funcionamento do kernel, e não para atender
 * solicitações de aplicativos em ring 3. Também serve para medir algumas 
 * demandas de recursos.
 *
 * * IMPORTANTE: 'Request' será considerado 'sinônimo' de Signal !
 *                Uma rotina de sinal agendará um request par o 
 *                kernel base atender.
 *                Signal será considerado um serviço e fará parte 
 *                das rotinas do sistema em executive/sys. 
 *
 * Lista de requests:
 * =================
 *
 * KERNEL_REQUEST_NONE: 
 *     Request null, sem motivo definido.
 * KERNEL_REQUEST_TIME: 
 *     Contador de vezes que a thread rodou.
 * KERNEL_REQUEST_SLEEP: 
 *     Faz a thread atual dormir. Entrando no estado waiting.
 * KERNEL_REQUEST_WAKEUP: 
 *     Acorda a thread atual.
 * KERNEL_REQUEST_ZOMBIE: 
 *     Torna zombie a thread atual.
 * KERNEL_REQUEST_NEW: 
 *     Inicia uma nova thread. A thread roda pela primeira vez.
 *     Ela estar no estado INITIALIZED.
 * KERNEL_REQUEST_NEXT: 
 *     ?? Reinicia a execução de uma thread.
 * KERNEL_REQUEST_TIMER_TICK: 
 *      ?? O tick do timer.
 * KERNEL_REQUEST_TIMER_LIMIT: 
 *     ?? Um limite de contagem.
 * //...
 *
 * History:
 *     2015 - Created by Fred Nora.
 *     //...
 */  
 
 
/*
    # planejando próximos eventos ...

	{
	#bugbug: Situação em que temos que acordar uma threa por causa de evento de input.	
	+ Ocorreu um evento de input, devemos acordar a trhead que estava esperando por ele.
	#importante: Me parece que esse caso não deve ser tratado aqui e sim na hora do 
	tratamento da interrupção, pois input não pode esperar. O tempo de resposta é importante.
	Lembrando que esse tratamento de requests é 'adiado' até o fim da rotina de interrupção 
	de timer.
	}
	
	{
	   ...	
	}
	

*/ 
 
 
 
#include <kernel.h>


/*
 *********************************************************
 * KiRequest: 
 *    Trata os requests. 
 *    São serviços que terão seu atendimento atrazado até
 * pouco antes de retornar da interrupção do timer.
 * São serviços para o ambiente ring0.    
 *
 *    (eventos, solicitações , waits ...).
 *    Essa rotina é chamada em todas as 
 * interrupções de timer.
 *
 *    @todo: Aqui deve ficar apenas as intefaces que 
 * chamam as rotinas de tratamento dos requests.
 */
 
void KiRequest (){
	
	//#todo: #bugbug: limite imposto
	int Max = 11;
	
    //
    // @todo:
	//     Check some limits.
    //	
	
	// Limits
    if( kernel_request < 0 || 
	    kernel_request > Max )
	{
        printf("KiRequest: %d", kernel_request );
		die();
	};
	
	//...
    
	request ();
};


/*
 *******************************************************
 * request:
 *     Trata os requests do Kernel.
 *    São serviços que terão seu atendimento atrazado até
 * pouco antes de retornar da interrupção do timer.
 * São serviços para o ambiente ring0.  
 *     2015 (Fred Nora) - Created.
 *     2016 (FN) - Revisão.
 *     ...
 */
 
void request (){
	
    struct process_d *Process; 
    struct thread_d *Thread;	

	int Current;
	unsigned long r;    //Número do request.
	unsigned long t;    //Tipo de thread. (sistema, periódica...).
	int Max = 11;	
	
   
	// Current thread.
	Current = (int) current_thread;
	
	//
	// @todo: Filtro.
	//
	
	//if(Current ...){}
	
	Thread = (void *) threadList[Current];
	
	if ( (void *) Thread == NULL )
	{
		//kernel_request = 0;
		//...
		return;    //fail.
	
	} else {
		
	    r = (unsigned long) kernel_request;
	    
		t = (unsigned long) Thread->type; 
		
		Process = (void *) Thread->process;
	    
		//...
	};
	
	//Number limits.
	
	//#bugbug
	//obs: Estamos checando se uma variável unsigned long é menor que zero.
	//     Isso  não é necessário.	
	
	if( r < 0 || r > Max )
	{
        printf("request: Limits! %d\n",r);
		die();
    };
	
    //
	// # Number #
	//
	
	switch(r) 
	{
	    //0 - request sem motivo, (a variável foi negligenciada).
        case KR_NONE:
	        //nothing for now.       
	    break;

	    //1 - Tratar o tempo das threads de acordo com o tipo.  
		//#importante: De acordo com o tipo de thread.
	    case KR_TIME:		    
			switch (t)
            {
                case TYPE_IDLE:   
                case TYPE_SYSTEM:
                    //Nothing.				
                    break;

				//periodic
	            //Ticks Remaining: Quando o tempo de execução de uma 
	            //thread se esgota. (Não faz parte do task switch,     
				//apenas trata o tempo que a tarefa tem para ficar     
				//executando). O tempo restante vai diminuindo.     					
                case TYPE_PERIODIC:   
				    Thread->ticks_remaining--;
					if( Thread->ticks_remaining == 0 )
					{
		                panic("request: Time out TIP={%d}", Thread->tid );					
	                };
                    break;
					
				//round robin.	
                case TYPE_RR:   
				    //Nothing.
					break;
					
				//@todo: Implementar os outros tipos.	
					
				default:
				    //Tipo inválido.
                    break;						
            } 			   
	        break;
		
	    //2 - faz a current_thread dormir. 
   	    case KR_SLEEP:   
		    do_thread_sleeping (Current);
	        break;
         
	    //3 - acorda a current_thread.
	    case KR_WAKEUP:
		    //
		    break;

	    //4 - torna a current_thread zombie.
	    case KR_ZOMBIE:
	        do_thread_zombie (Current);
		    break;
			
		//5 - start new task.
		//Uma nova thread passa a ser a current, para rodar pela primeira vez.
		case KR_NEW:	
		    //Start a new thread. 
	        if(start_new_task_status == 1)
			{		
		        current_thread = start_new_task_id;
	        };
		    break;
			
        //6 - torna atual a próxima thread anunciada pela atual.
		case KR_NEXT:
            current_thread = (int) Thread->Next->tid; 
			break;	
			
		//7 - tick do timer.
		case KR_TIMER_TICK:
		    panic("KR_TIMER_TICK\n");
			//die();
		    break;
        
		//8 - limite de funcionamento do kernel.
        case KR_TIMER_LIMIT:
		    panic("KR_TIMER_LIMIT\n");
			//die();
		    break;
			
		//9 - Checa se ha threads para serem inicializadas e 
		// inicializa pelo método spawn.	
		case KR_CHECK_INITIALIZED:
            check_for_standby();		
		    break;
			
		//#todo
		//Chama o procedimento do sistema.
        // ?? args ??	
        // o serviço 124 aciona esse request.		
		case KR_DEFERED_SYSTEMPROCEDURE:
		    system_procedure ( 0, 0, 0, 0 );
			break;
			
		
		//@todo: Tratar mais tipos.	
		//...
		
		default:
		    //printf("Default Request={%d}\n",r);
		    break;
    };

    //
    // More ?!
    //	
	
/*
 * Done:
 *   Essas finalizações aplicam para todos os requests.
 */	
done:
    //thread->step++;                      //Aumenta o step para todos os tipos.
    kernel_request = (unsigned long) 0;    //Zera o request.
	return; 
};

//
// End.
//

