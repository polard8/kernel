/*
 * File: kernel/request.c
 *
 *      Kernel requests.
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
 
int KiRequest (){
		
    if ( kernel_request < 0 || kernel_request > KERNEL_REQUEST_MAX )
	{	
        printf ("KiRequest: %d", kernel_request );
		die ();
	}
	
	return (int) request ();
}


/*
 *******************************************************
 * request:
 *    Trata os requests do Kernel.
 *    São serviços que terão seu atendimento atrazado até pouco antes de 
 * retornar da interrupção do timer.
 *    Sendo assim, um programa em user mode pode solicitar um request através
 * de uma system call, sendo a system call transformada em request, adiando
 * o atendimento.
 *   O atendimento do request pendende será feito com o auxílio da estrutura
 * de request.
 *   Um request será atendido somente quando o timeout zerar. (defered)
 */
 
int request (){
	
	//targets	
    struct process_d *Process; 
    struct thread_d *Thread;	
	int PID;
	int TID;
	
	unsigned long r;    //Número do request.
	unsigned long t;    //Tipo de thread. (sistema, periódica...).
	

	//
	// targets.
	//
	
	PID = (int) REQUEST.target_pid;
    TID = (int) REQUEST.target_tid;

	
	//
	// ## timeout ##
	//
	
	if ( REQUEST.timeout > 0 )
	{
	    REQUEST.timeout--;
		return 1;
	}
	
	
	//
	// Filtro.
	//

	if ( PID < 0 || PID > PROCESS_COUNT_MAX )
	{
		Process = NULL;
	}else{
	    Process = (void *) processList[PID];		
	}
		
	if ( TID < 0 || TID > THREAD_COUNT_MAX )
	{
	    Thread = NULL;
	}else{
	
	    Thread = (void *) threadList[TID];	
	}

	
    //
	// # Number #
	//
	
	r = kernel_request;
	
	if (r >= KERNEL_REQUEST_MAX)
		return -1;
	
	switch (r) 
	{
	    //0 - request sem motivo, (a variável foi negligenciada).
        case KR_NONE:
	        //nothing for now.       
	    break;

	    //1 - Tratar o tempo das threads de acordo com o tipo.  
		//#importante: De acordo com o tipo de thread.
	    case KR_TIME:		    
            panic ("request: KR_TIME\n");
			//return -1;
	        break;
		
	    //2 - faz a current_thread dormir. 
   	    case KR_SLEEP:   
		    do_thread_sleeping ( (int) REQUEST.target_tid );
	        break;
         
	    //3 - acorda a current_thread.
	    case KR_WAKEUP:
		    wakeup_thread ( (int) REQUEST.target_tid );
		    break;

        //	
	    case KR_ZOMBIE:
            //panic ("request: KR_ZOMBIE\n");
			do_thread_zombie ( (int) REQUEST.target_tid );
		    break;
			
		//5 - start new task.
		//Uma nova thread passa a ser a current, para rodar pela primeira vez.
		//Não mexer. Pois temos usado isso assim.	
		case KR_NEW:	
		    //Start a new thread. 
	        if(start_new_task_status == 1)
			{		
		        current_thread = start_new_task_id;
	        };
		    break;
			
        //6 - torna atual a próxima thread anunciada pela atual.
		case KR_NEXT:
            panic ("request: KR_NEXT\n");
			//return -1;
			break;	
			
		//7 - tick do timer.
		case KR_TIMER_TICK:
		    panic ("request: KR_TIMER_TICK\n");
		    //return -1;
			break;
        
		//8 - limite de funcionamento do kernel.
        case KR_TIMER_LIMIT:
		    panic ("request: KR_TIMER_LIMIT\n");
		    //return -1;
			break;
			
		// 9 - Checa se ha threads para serem inicializadas e 
		// inicializa pelo método spawn.
		// obs: se spawn retornar, continua a rotina de request. sem problemas.	
		case KR_CHECK_INITIALIZED:
            check_for_standby ();
		    break;
			
		//#todo
		//Chama o procedimento do sistema.
        // ?? args ??	
        // o serviço 124 aciona esse request.		
		case KR_DEFERED_SYSTEMPROCEDURE:
		    //system_procedure ( REQUEST.window, REQUEST.msg, REQUEST.long1, REQUEST.long2 );
			break;
			
	    //exit process
		case 11:
			exit_process ( (int) REQUEST.target_pid, (int) REQUEST.long1 );
			break;
			
		//exit thread.	
		case 12:
			exit_thread ( (int) REQUEST.target_tid );
			break;
			
		//make target porcess current
		//cuidado.	
		case 13:	
			current_process = REQUEST.target_pid;
			break;
			
		//make target thread current
		//cuidado.	
		case 14:	
			current_thread = REQUEST.target_tid;
			break;			
		
		//@todo: Tratar mais tipos.	
		//...
		
		default:
		    printf ("request: Default request {%d} \n", r );
		    break;
    };
	
//Done:
//   Essas finalizações aplicam para todos os requests.

    clear_request ();
	kernel_request = (unsigned long) 0;  
	
	
	// OK.
	return 0;
}


int 
create_request ( unsigned long number, 
                 int status, 
                 int timeout,
				 int target_pid,
				 int target_tid,
                 struct window_d *window, 
                 int msg, 
                 unsigned long long1, 
                 unsigned long long2 )
{
	
	if (number > KERNEL_REQUEST_MAX)
		return 1;
	
	kernel_request = number;
    REQUEST.kernel_request = number;
	
	REQUEST.status = status;
	
	if (timeout < 0 )
	{
		REQUEST.timeout = 0;
	}else{
	    REQUEST.timeout = timeout;
	}
	
	REQUEST.target_pid = target_pid;
	REQUEST.target_tid = target_tid;	
	
	REQUEST.window = (struct window_d *) window;
	REQUEST.msg = msg;
	REQUEST.long1 = long1;
	REQUEST.long2 = long2;
		
	//extra.
	//rever isso depois.
	REQUEST.long3 = 0;
	REQUEST.long4 = 0;
	REQUEST.long5 = 0;
	REQUEST.long6 = 0;
	
	//OK
	return 0;
}

void clear_request()
{
    REQUEST.kernel_request = 0;
	REQUEST.status = 0;
	REQUEST.timeout = 0;
	
	REQUEST.target_pid = 0;
	REQUEST.target_tid = 0;	
		
	REQUEST.window = NULL;
	REQUEST.msg = 0;
	REQUEST.long1 = 0;
	REQUEST.long2 = 0;
		
	REQUEST.long3 = 0;
	REQUEST.long4 = 0;
	REQUEST.long5 = 0;
	REQUEST.long6 = 0;
}




//
// End.
//

