/*
 * File: request.c
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


//
// Internas,
//

void do_request_12 ( int tid );

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
 
// Kernel request support.
// This routine was called by the task switch as a extra service.
// See: ts.c

int KiRequest (void)
{
    //debug_print("KiRequest: [OK] Kernel request support.");
 
    if ( kernel_request < 0 || kernel_request > KERNEL_REQUEST_MAX )
    {
        debug_print("KiRequest: [PANIC] kernel_request\n");
        printf ("KiRequest: %d", kernel_request );
        die();
    }

    return (int) request();
}



/*
 *******************************************************
 * request:
 *    Trata os requests do Kernel.
 *    Isso eh chamado durante a a fase kernel 
 *    de uma interrupçao de timer.
 *    
 *    São serviços que terão seu atendimento atrazado até pouco antes de 
 * retornar da interrupção do timer.
 *    Sendo assim, um programa em user mode pode solicitar um request através
 * de uma system call, sendo a system call transformada em request, adiando
 * o atendimento.
 *   O atendimento do request pendende será feito com o auxílio da estrutura
 * de request.
 *   Um request será atendido somente quando o timeout zerar. (defered)
 */
 
int request (void){

    // Targets

    struct process_d  *Process;
    struct thread_d   *Thread;

    int PID=-1;
    int TID=-1;

    unsigned long r=0;    //Número do request.
    unsigned long t=0;    //Tipo de thread. (sistema, periódica...).


	// targets.

    PID = (int) REQUEST.target_pid;
    TID = (int) REQUEST.target_tid;



	//
	// ## timeout ##
	//

    if ( REQUEST.timeout > 0 )
    {
        REQUEST.timeout--;
        return 1;
        //return -1; // use this one if it is possible.
    }


	//
	// Filtro.
	//

    if ( PID < 0 || PID > PROCESS_COUNT_MAX ){
        Process = NULL;
    }else{
        Process = (void *) processList[PID];
    };


    if ( TID < 0 || TID > THREAD_COUNT_MAX ){
        Thread = NULL;
    }else{
        Thread = (void *) threadList[TID];
    };


	//
	// Number
	//

    r = kernel_request;

    if (r >= KERNEL_REQUEST_MAX){
        // msg ...
        return -1;
    }


    switch (r) 
    {
        //0 - request sem motivo, (a variável foi negligenciada).
        // Ou ainda estamos checando se tem um resquest,
        // se não tem apenas retornamos.
        case KR_NONE:
            //debug_print ("request: KR_NONE\n");
            //nothing for now.       
            break;


        //1 - Tratar o tempo das threads de acordo com o tipo.  
        //#importante: De acordo com o tipo de thread.
        case KR_TIME:
            debug_print ("request: KR_TIME\n");
            panic       ("request: KR_TIME\n");
            break;


        //2 - faz a current_thread dormir. 
        case KR_SLEEP:
            debug_print ("request: block a thread\n");
            do_thread_blocked ( (int) REQUEST.target_tid );
            break;


        //3 - acorda a current_thread.
        case KR_WAKEUP:
            debug_print ("request: wake up a thread\n");
            wakeup_thread ( (int) REQUEST.target_tid );
            break;


        //4
        case KR_ZOMBIE:
            debug_print ("request: do thread zombie\n");
            do_thread_zombie ( (int) REQUEST.target_tid );
            break;

        //5 - start new task.
        //Uma nova thread passa a ser a current, para rodar pela primeira vez.
        //Não mexer. Pois temos usado isso assim.	
        case KR_NEW:
            debug_print ("request: Start a new thread\n");
            //Start a new thread. 
            if (start_new_task_status == 1){
                current_thread = start_new_task_id;
            }
            break;


        //6 - torna atual a próxima thread anunciada pela atual.
        case KR_NEXT:
            debug_print ("request: KR_NEXT\n");
            panic       ("request: KR_NEXT\n");
            break;


        //7 - tick do timer.
        case KR_TIMER_TICK:
            debug_print ("request: KR_TIMER_TICK\n");
            panic       ("request: KR_TIMER_TICK\n");
            break;

        //8 - limite de funcionamento do kernel.
        case KR_TIMER_LIMIT:
            debug_print ("request: KR_TIMER_LIMIT\n");
            panic       ("request: KR_TIMER_LIMIT\n");
            break;


        // 9 - Checa se ha threads para serem inicializadas e 
        // inicializa pelo método spawn.
        // obs: 
        // Se spawn retornar, continua a rotina de request. 
        // Sem problemas.
        case KR_CHECK_INITIALIZED:
            debug_print ("request: Check for standby\n");
            check_for_standby ();
            break;


        //#todo
        //Chama o procedimento do sistema.
        // ?? args ??	
        // o serviço 124 aciona esse request.
        case KR_DEFERED_SYSTEMPROCEDURE:
            debug_print ("request: defered system procedure [TODO]\n");
            //system_procedure ( REQUEST.window, REQUEST.msg, REQUEST.long1, REQUEST.long2 );
            break;


        //exit process
        case 11:
            debug_print ("request: Exit process\n");
            exit_process ( (int) REQUEST.target_pid, (int) REQUEST.long1 );
            break;


        // exit thread.
        // Sairemos da thread, mas se for a thread de controle, 
        // também sairemos do processo.
        case 12:
            debug_print ("request: [12] Exit thread\n");
            //printf      ("request: [12] [DEBUG] Exiting thread %d\n", 
            //    REQUEST.target_tid);
            do_request_12( (int) REQUEST.target_tid );
            break;


        //make target porcess current
        //cuidado.
        case 13:
            debug_print ("request: Get current process\n");
            current_process = REQUEST.target_pid;
            break;


        //make target thread current
        //cuidado.
        case 14:
            debug_print ("request: Get current thread\n");
            current_thread = REQUEST.target_tid;
            break;


        case 15:
            debug_print ("request: Wait for a reason \n");
            wait_for_a_reason ( REQUEST.target_tid, (int) REQUEST.long1  );
            break;

		// todo: 
		// Tratar mais tipos.	
		//...


        default:
            debug_print ("request: Default \n");  
            printf      ("request: Default request {%d} \n", r );
            break;
    };


//Done:
//   Essas finalizações aplicam para todos os requests.

    clear_request();
    kernel_request = (unsigned long) 0;  


    // Ok.
    return 0;
}


/*
 *******************************************************
 * create_request:
 *     Cria o request, que será atendido depois.
 *     Isso eh chamado no serviço 70, por exemplo.
 *     #bugbug: Pode haver sobreposicao de requests?
 */

int 
create_request ( 
    unsigned long number, 
    int status, 
    int timeout,
    int target_pid,
    int target_tid,
    struct window_d *window, 
    int msg, 
    unsigned long long1, 
    unsigned long long2 )
{


    debug_print ("create_request:\n");

    if (number > KERNEL_REQUEST_MAX){
        debug_print ("create_request: number not valid\n");
        return 1;
        //return -1;  //#todo: Use this one if it is possible.
    }


    kernel_request = number;

    REQUEST.kernel_request = number;
    REQUEST.status         = status;


    if (timeout < 0 ){
        REQUEST.timeout = 0;
    }else{
        REQUEST.timeout = timeout;
    };


    REQUEST.target_pid = target_pid;
    REQUEST.target_tid = target_tid;

    // #obs
    // Atenção com isso.

    REQUEST.window = (struct window_d *) window;
    REQUEST.msg    = (int) msg;
    REQUEST.long1  = (unsigned long) long1;
    REQUEST.long2  = (unsigned long) long2;

	//extra.
	//rever isso depois.
    REQUEST.long3 = 0;
    REQUEST.long4 = 0;
    REQUEST.long5 = 0;
    REQUEST.long6 = 0;


    //Ok.
    return 0;
}



void clear_request (void)
{

    REQUEST.kernel_request = 0;
    REQUEST.status     = 0;
    REQUEST.timeout    = 0;
    REQUEST.target_pid = 0;
    REQUEST.target_tid = 0;

    REQUEST.window = NULL;
    REQUEST.msg    = 0;
    REQUEST.long1  = 0;
    REQUEST.long2  = 0;
    REQUEST.long3  = 0;
    REQUEST.long4  = 0;
    REQUEST.long5  = 0;
    REQUEST.long6  = 0;

    // The number of the current request.
    kernel_request = 0;
}



/*
 *********************************************
 * do_request_12:
 *     exit thread.
 */

	// exit thread.
	// Sairemos da thread, mas se for a thread de controle, 
	// também sairemos do processo.

void do_request_12 ( int tid ){

    //curent process
    struct process_d  *p;
    struct thread_d   *t;

    //parent process
    struct process_d *parent;
    int __ppid = 0;

    // If we need to exit this process at the end of thois routine.
    // Remember: The thread is turned zombie.
    int kill_process = FALSE;


    if ( tid<0 ){
        debug_print ("do_request_12: not valid tid\n");
        panic       ("do_request_12: not valid tid\n");
    }


    if ( tid != REQUEST.target_tid )
    {
        debug_print ("do_request_12: [PANIC] tid doesn't match\n");
        panic       ("do_request_12: [PANIC] tid doesn't match\n");
        //return;
    }


	//#debug
    //printf ("do_request_12: code=%d \n", REQUEST.long1);


	//exit code.
	switch (REQUEST.long1)
	{
		//sem erros.
		case 0:
			goto do_exit;
			break;
			
		//com erro 1.
		//vamos imprimir a mensagem de erro que estiver no
		//arquivo stderr.
		//#todo talvez precise de fflush se a mensagem estiver
		//no buffer em user mode.
		case 1:
			goto do_printf_error_message;
			break;
			
		//...
		default:
			goto do_exit;
			break;
    };



//#test
do_printf_error_message:

    printf ("do_request_12: do_printf_error_message\n");
    refresh_screen ();

do_exit:


    // #todo
    // #importante
    // Nesse momento temos que que ver qual é o processo pai do processo
    //que saiu, para acordar ele, caso esteja esperando por esse.

   

	//#debug
	//Se não ha erros, não mostramos mensagem.
   // printf ("do_request_12: Exit thread, no error\n");


    //#importante
	// Isso está certo. O que importa é exibir
	// a stream stderr do processo.

    t = (struct thread_d *) threadList[REQUEST.target_tid];
    p = (struct process_d *) processList[t->ownerPID];
    
    
    //
    // Control ?
    //
    
    // If it is the control thread, so we need to kill the process too.
    // Remember: We're gonna put the thread in zombie state before this.
    
    if ( t == p->control )
    {
        debug_print ("do_request_12: [FIXME] This is the control thread!\n");
        kill_process = TRUE;
    }
    

    //parent process
    __ppid = p->ppid;
    parent = (struct process_d *) processList[__ppid];

    // Se o processo pai está esperando pelo processo atual,
    // então acordamos o processo pai.
    
    if (parent->wait4pid == p->pid )
    {
        printf ("do_request_12: Wake up parent ...\n");
        refresh_screen();

        parent->state = PROCESS_RUNNING;
        parent->control->state = RUNNING;
    }


	// #bugbug
	// Ainda não podemos usar esse tipo de coisa,
	// estamos nos preparando par usar,

	//stdout = (FILE *) p->Streams[1]; //stdout
	//stderr = (FILE *) p->Streams[2]; //stderr
	
	// #importante
	// Testando a concatenação.
	
	//fprintf (stderr, "Exiting the thread %d ", REQUEST.target_tid );
	//fprintf (stderr, " *OK ");


    // See: threadi.c
    exit_thread ( (int) REQUEST.target_tid );


	//kprintf ("%s \n", stdout->_base ); 
	//kprintf ("%s \n", stderr->_base );
	
	// Done.


    // If we need to kill the process.
    if (kill_process == TRUE)
    {
        debug_print ("do_request_12: [FIXME] Killing the process\n");
        
        // #todo: Not tested.
        //exit_process(p->pid,0);
    }
     


	// Clear request structure.
    clear_request();

	//#debug
    //kprintf ("do_request_12: done :) \n");
    //refresh_screen ();
}



//
// End.
//

