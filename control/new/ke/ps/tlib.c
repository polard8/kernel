
// tlib.c
// Thread library.

#include <kernel.h>


/*
 * sys_get_message:
 *     Get a message from the current thread and 
 * put it into the given buffer.
 *     The message has 6 standard elements.
 */
// Called by sci.c
// Service 111.
// It is called by the applications.
// It is also used for ipc.

void *sys_get_message(unsigned long ubuf)
{
    struct thread_d  *t;
    unsigned long *message_address = (unsigned long *) ubuf;
    //int head_pos=0;

    //debug_print ("sys_get_message:\n");

// buffer
// #todo: Check some other invalid address.
    if ( ubuf == 0 ){ 
        panic ("sys_get_message: buffer\n");
        //return NULL;
    }

// Thread

    if(current_thread<0 ||
       current_thread>=THREAD_COUNT_MAX)
    {
        return NULL;
    }

    t = (void *) threadList[current_thread];

    if ( (void *) t == NULL ){
        panic ("sys_get_message: t\n");
    }

    if ( t->used != TRUE || t->magic != 1234 ){
        panic ("sys_get_message: t validation\n");
    }

// ===========================================================
// usando a fila de mensagens com estrutura.

    struct msg_d  *next_msg;

// Get the next head pointer.
    next_msg = (struct msg_d *) t->MsgQueue[ t->MsgQueueHead ];

    if ( (void*) next_msg == NULL ){
        goto fail0;
    }

    if (next_msg->used != TRUE || next_msg->magic != 1234 )
    {
        goto fail0;
    }

// invalid
    if( next_msg->msg == 0 ){
        goto fail0;
    }

// Get standard entries.
    message_address[0] = (unsigned long) next_msg->window;
    message_address[1] = (unsigned long) (next_msg->msg & 0xFFFFFFFF);
    message_address[2] = (unsigned long) next_msg->long1;
    message_address[3] = (unsigned long) next_msg->long2;

// Get extra entries.
    message_address[4] = (unsigned long) next_msg->long3;
    message_address[5] = (unsigned long) next_msg->long4;

// #test
    message_address[8] = (unsigned long) next_msg->sender_tid;
    message_address[9] = (unsigned long) next_msg->receiver_tid;


// Buffer size:
// 32 slots.

// jiffies when posted.
    //message_address[10] = (unsigned long) next_msg->long3; 

// jiffies when gotten by the app.
    message_address[11] = (unsigned long) jiffies;


// clear the entry.
// Consumimos a mensagem. Ela não existe mais.
// Mas preservamos a estrutura.
    next_msg->window = NULL;
    next_msg->msg = 0;
    next_msg->long1 = 0;
    next_msg->long2 = 0;
    next_msg->long3 = 0;
    next_msg->long4 = 0;

// ==================================

done:
// Yes, We have a message.
// round
    t->MsgQueueHead++;
    if ( t->MsgQueueHead >= 31 ){  t->MsgQueueHead = 0;  }
    return (void *) 1;

fail0:
// No message.
// round
    t->MsgQueueHead++;
    if ( t->MsgQueueHead >= 31 ){  t->MsgQueueHead = 0;  }
    return NULL;
}

// 120
// Get a message given the index.
// With restart support.
// IN: buffer, index, flag: TRUE=restart the queue at the end.

void *sys_get_message2(unsigned long ubuf, int index, int restart)
{
    struct thread_d  *t;
    unsigned long *message_address = (unsigned long *) ubuf;
    //int head_pos=0;

    //debug_print ("sys_get_message:\n");

// buffer
// #todo: Check some other invalid address.
    if ( ubuf == 0 ){ 
        panic ("sys_get_message2: buffer\n");
        //return NULL;
    }

// Thread

    if(current_thread<0 ||
       current_thread>=THREAD_COUNT_MAX)
    {
        return NULL;
    }

// Thread pointer.
    t = (void *) threadList[current_thread];
    if ( (void *) t == NULL ){
        panic ("sys_get_message2: t\n");
    }
    if ( t->used != TRUE || t->magic != 1234 ){
        panic ("sys_get_message2: t validation\n");
    }

// Get the index.

    if( index<0 || index >= 32){
        goto fail0;
    }

    t->MsgQueueHead = (int) (index & 0xFFFFFFFF);

// ===========================================================
// usando a fila de mensagens com estrutura.

    struct msg_d  *next_msg;

// Get the next head pointer.
    next_msg = (struct msg_d *) t->MsgQueue[ t->MsgQueueHead ];
    if ( (void*) next_msg == NULL ){
        goto fail0;
    }
    if (next_msg->used != TRUE || next_msg->magic != 1234)
    {
        goto fail0;
    }

// Invalid message code.
    if ( next_msg->msg == 0 ){
        goto fail0;
    }

// Get standard entries.
    message_address[0] = (unsigned long) next_msg->window;
    message_address[1] = (unsigned long) (next_msg->msg & 0xFFFFFFFF);
    message_address[2] = (unsigned long) next_msg->long1;
    message_address[3] = (unsigned long) next_msg->long2;

// Get extra entries.
    message_address[4] = (unsigned long) next_msg->long3;
    message_address[5] = (unsigned long) next_msg->long4;

// #test
    message_address[8] = (unsigned long) next_msg->sender_tid;
    message_address[9] = (unsigned long) next_msg->receiver_tid;

// Buffer size:
// 32 slots.

// jiffies when posted.
    //message_address[10] = (unsigned long) next_msg->long3; 

// jiffies when gotten by the app.
    message_address[11] = (unsigned long) jiffies;

// Clear the entry.
// Consumimos a mensagem. Ela não existe mais.
// Mas preservamos a estrutura.
    next_msg->window = NULL;
    next_msg->msg = 0;
    next_msg->long1 = 0;
    next_msg->long2 = 0;
    next_msg->long3 = 0;
    next_msg->long4 = 0;

// ==================================

// It is a valid thread pointer.
done:
    if (restart==TRUE){
        t->MsgQueueHead=0;
        t->MsgQueueTail=0;
        return (void*) 1;
    }

// Yes, We have a message.
// round
    t->MsgQueueHead++;
    if ( t->MsgQueueHead >= 32 ){ t->MsgQueueHead = 0; }
    return (void *) 1;

// Is it a valid thread pointer?
fail0:
// No message.
// round

    if (restart==TRUE)
    {
        if ( (void*) t != NULL ){
            t->MsgQueueHead=0;
            t->MsgQueueTail=0;
        }
        return NULL;
    }

    if( (void*) t != NULL){
        t->MsgQueueHead++;
        if ( t->MsgQueueHead >= 32 ){
            t->MsgQueueHead = 0;
        }
    }

    return NULL;
}


// post_message_to_tid:
// #bugbug
// long1 and long2 will mask to single byte.
// IN: tid, window, message code, ascii code, raw byte.
// Post message.

int
post_message_to_tid ( 
    int tid, 
    struct window_d *window, 
    int msg, 
    unsigned long long1, 
    unsigned long long2 )
{

// #todo: Change these to target_thread e target_tid.

// Target thread.
    struct thread_d *t;
// Target tid
    tid_t TargetTID = (tid_t) (tid & 0xFFFF);

    unsigned long tmp_msg=0;

    //#debug
    //debug_print("post_message_to_tid:\n");

// Thread

    if ( TargetTID < 0 || 
         TargetTID >= THREAD_COUNT_MAX )
    {
        panic("post_message_to_tid: TargetTID\n");
        //goto fail;
    }
    t = (struct thread_d *) threadList[TargetTID];
    if ( (void *) t == NULL ){
        panic ("post_message_to_tid: t \n");
    }
    if ( t->used != 1 || t->magic != 1234 ){
        panic ("post_message_to_tid: t validation \n");
    }
    if(TargetTID != t->tid){
        panic("post_message_to_tid: TargetTID != t->tid");
    }

// Reset the running count.
// Giving to the thread more time.
    t->runningCount = 0;
    t->runningCount_ms = 0;


// Giving more credits to the receiver.
// The receiver will lose this time in the scheduler.
// The scheduler will balance the credits.
    t->quantum = (t->quantum + QUANTUM_BOOST);

    if ( t->quantum > QUANTUM_MAX ){
        t->quantum = QUANTUM_MAX;
    }


// Wake up the target thread?

    // wakeup_thread(t->tid);

// #todo
// Podemos melhorar a prioridade ou o quantum da thread alvo.

//
// The message
//

    tmp_msg = (unsigned long) (msg & 0xFFFFFFFF);

// ==========================================================
// #test
// Vamos colocar essa mensagem na outra fila de mensagens.
// Essa nova fila sera a única fila no futuro.

    struct msg_d *next_msg;

    // get the pointer for the next entry
    next_msg = (struct msg_d *) t->MsgQueue[ t->MsgQueueTail ];

    if ( (void*) next_msg == NULL )
        panic ("post_message_to_tid: next_msg\n");

    if( next_msg->used != TRUE || next_msg->magic != 1234 )
        panic ("post_message_to_tid: next_msg validation \n");

// #test
// O slot ja tem uma mensagem que nao foi consumida.
    //if( next_msg->msg != 0 ){
    //    panic ("post_message_to_tid: not responding ...\n");
    //}

    next_msg->window = (struct window_d *) window;
    next_msg->msg    = (int) (tmp_msg & 0xFFFFFFFF);
    next_msg->long1  = (unsigned long) long1;
    next_msg->long2  = (unsigned long) long2;

// #test
// ktime.
    next_msg->long3 = (unsigned long) jiffies;

// #test
// Status das teclas de controle.
// #todo:
// Como o driver de teclado esta dentro do kernel,
// então podemos chamar uma função que pegue uma 
// variavel contendo o status de todas as teclas de controle.

    //next_msg->long4 = (unsigned long) wmGetControlKeysState();

// #test
    next_msg->sender_tid = -1;  // from kernel. 
    next_msg->receiver_tid = (tid_t) TargetTID;

done:
    t->MsgQueueTail++;
    if ( t->MsgQueueTail >= 31 )
        t->MsgQueueTail = 0;
    return 0;

fail0:
    t->MsgQueueTail++;
    if ( t->MsgQueueTail >= 31 )
        t->MsgQueueTail = 0;
    return -1;
}

int
post_message_to_ws ( 
    struct window_d *window, 
    int msg, 
    unsigned long long1, 
    unsigned long long2 )
{

    tid_t tid=-1;

    if( WindowServerInfo.initialized != TRUE )
        return -1;

    tid = (tid_t) WindowServerInfo.tid;
         
    if ( tid < 0 || 
         tid >= THREAD_COUNT_MAX )
    {
        return -1;
    }

// #todo
// precisamos de uma flag que indique que isso deve ser feito.
// See: tlib.c

    // IN: tid, window pointer, msgcode, data1, data2.
    post_message_to_tid(
        (int) tid,
        NULL,
        (int) msg,
        long1,
        long2 );

   return 0;
}


// Post message to the foreground thread.
int
post_message_to_foreground_thread ( 
    struct window_d *window, 
    int msg, 
    unsigned long long1, 
    unsigned long long2 )
{

// Paranoia.
    if( foreground_thread < 0 || 
        foreground_thread >= THREAD_COUNT_MAX )
    {
        return -1;
    }

    if(msg<0){
        return -1;
    }

    return (int) post_message_to_tid( 
                     foreground_thread,
                     window, msg, long1, long2 );
}


// Post message to the ws control thread.
int
post_message_to_ws_thread ( 
    struct window_d *window, 
    int msg, 
    unsigned long long1, 
    unsigned long long2 )
{
    if( WindowServerInfo.initialized == TRUE ){
        return -1;
    }
    if(msg<0){
        return -1;
    }
    return (int) post_message_to_tid( 
                     WindowServerInfo.tid,
                     window, msg, long1, long2 );
}


// service 112
// Post message to tid.
// Asynchronous.
unsigned long
sys_post_message_to_tid( 
    int tid, 
    unsigned long message_buffer )
{

    if( tid < 0 || tid >= THREAD_COUNT_MAX )
        return 0;

    if( message_buffer == 0 )
        return 0;

    unsigned long *buf = (unsigned long *) message_buffer;

// Post message.
// Asynchronous.

    post_message_to_tid(
        tid,       //tid
        buf[0],    //window
        buf[1],    //msg code
        buf[2],    //long1
        buf[3] );  //long2

    return 0;
}


// show_slot:
// Show info about a thread.

void show_slot(int tid)
{
    struct thread_d  *t;

    if ( tid < 0 || tid >= THREAD_COUNT_MAX )
    {
        printf ("show_slot: tid\n");
        goto fail;
    }

    t = (void *) threadList[tid];

    if ( (void *) t == NULL ){
        printf ("show_slot: t\n");
        goto fail;
    }

// Show one slot

    printf ("\n");
    printf ("TID   PID   Per   pdPA  Prio  State Quan *Jiffies initial_rip rflags   tName \n");
    printf ("====  ====  ====  ====  ====  ===== ==== ====    ==========  ======  =====   \n");
    printf ("%d    %d    %d    %x   %d    %d    %d    %d      %x          %x      %s      \n", 
        t->tid, 
        t->owner_pid,
        t->personality,
        t->pml4_PA,
        t->priority, 
        t->state,
        t->quantum,    // Quantum
        t->step,       // >>> Jiffies
        t->initial_rip,
        t->rflags,
        t->name_address );

    //#test
    printf(":: stime{%d} utime{%d}\n",t->stime,t->utime);

    goto done;

fail:
    printf ("Fail\n");
done:
    return; 
}


// show_slots:
// Show info about all threads.
// Loop
// Mostra as tarefas válidas, mesmo que estejam com problemas.

void show_slots(void)
{
    struct process_d  *p;
    struct thread_d   *t;
    int i=0;

    printf("\n");
    //printf("Thread info: jiffies{%d} sec{%d} min{%d}\n", 
        //jiffies, seconds, (seconds/60));

    printf("Thread info: jiffies{%d} \n", jiffies );
    printf("Focus tid {%d}\n",foreground_thread);

    for ( i=0; i<THREAD_COUNT_MAX; i++ )
    {
        t = (void *) threadList[i];

        if ( (void *) t != NULL && 
             t->used  == 1 && 
             t->magic == 1234 )
        {
            show_slot(t->tid);
        }
    };

    refresh_screen();
}


/*
 * show_reg:
 *     Show the content of the registers.
 *    rflags
 *    cs:rip
 *    ss:rsp
 *    ds,es,fs,gs
 *    a,b,c,d
 */

void show_reg(int tid)
{
    struct thread_d  *t;

    if ( tid < 0 || tid >= THREAD_COUNT_MAX )
    {
        printf("show_reg: fail\n");
        return;
    }

    t = (void *) threadList[tid];

    if ( (void *) t == NULL ){
        printf ("show_reg: fail\n");
        return;
    } 

// Show registers

    printf("\n");
    printf("rflags=[%x] \n", 
        t->rflags);
    printf("cs:rip=[%x:%x] ss:rsp=[%x:%x] \n", 
        t->cs, t->rip, t->ss, t->rsp );
    printf("ds=[%x] es=[%x] fs=[%x] gs=[%x] \n",
        t->ds, t->es, t->fs, t->gs );
    printf("a=[%x] b=[%x] c=[%x] d=[%x] \n",
        t->rax, t->rbx, t->rcx, t->rdx );

    // r8~r12
    // ...
}


// set_thread_priority:
// Muda a prioridade e o quantum de acordo com a prioridade.
// #bugbug
// Isso nao eh bom, a funcao deve fazer exatamente
// o que o nome diz, #todo: devemos criar
// outra rotina para mudar o quantum.

void 
set_thread_priority ( 
    struct thread_d *t, 
    unsigned long priority )
{

    //unsigned long NewPriority = priority;
    unsigned long OldPriority  = 0;

    unsigned long BasePriority = 0;


// Limits

    if ( priority < PRIORITY_MIN )
    {
        priority=PRIORITY_MIN;
        return;
    }
    if ( priority > PRIORITY_MAX )
    {
        priority=PRIORITY_MAX;
        return;
    }

// Thread validation
    if ( (void *) t == NULL )              { return; }
    if ( t->used != 1 || t->magic != 1234 ){ return; }

// Save old values.
    OldPriority  = t->priority;
    BasePriority = t->base_priority;

// Se aprioridade solicitada for igual da prioridade atual.
    if ( priority == OldPriority ){ return; }

// Se a prioridade solicitada for menor que a prioridade basica.
// #todo: Ent~ao poderiamos usar a prioridade basica.
    if ( priority < BasePriority ){ return; }

// Se a prioridade basica pertencer a classe de tempo real
// nao podemos mudar a prioridade.
    if ( BasePriority > PRIORITY_NORMAL ){ return; }

// limits again
    if ( priority > PRIORITY_MAX )
    {
        t->priority = PRIORITY_MAX;
    }

// Set new priority!
// Set new quantum.
// Se aprioridade solicitada for diferente da prioridade atual.
// Tambem nao pode ser menor que a base.
    if ( priority != OldPriority ){
        t->priority = priority;
    }

//
// Quantum
//

// Não mudaremos os creditos, somente a prioridade no escalonamento.
// Não se preocupe.
// O scheduler equilibra ao fim do round

// Quantum fora dos limites.

    if ( t->quantum < QUANTUM_MIN )
    {
        t->quantum = QUANTUM_MIN;
    }

    if ( t->quantum > QUANTUM_MAX )
    {
        t->quantum = QUANTUM_MAX;
    }
}


// #suspenso
// muda a prioridade para alem dos limites ... teste.
void threadi_power(
    struct thread_d *t, 
    unsigned long priority )
{
    if ( (void *) t == NULL ){ return; }
   
    if ( t->used != 1 || t->magic != 1234 )
    {
        return;
    }

// Priority

    t->priority = PRIORITY_MAX;
    
    // Aceita se tiver nos limites.
    if( t->priority > PRIORITY_MIN &&
        t->priority < PRIORITY_MAX )
    {
         t->priority = priority;
    }

// Credits

    t->quantum = QUANTUM_MAX;
}


/*
 * release:
 * #importante
 * Isso deve liberar uma thread que estava esperando 
 * ou bloqueada por algum motivo.
 * Obs: Aqui não devemos julgar se ela pode ou não ser
 * liberada, apenas alteramos se estado.
 */
// #importante:
// Não estamos selecionando ela para execução,
// apenas estamos dizendo que ela está pronta para executar.

void release(int tid)
{
    struct thread_d *Thread;


    if ( tid < 0 || tid >= THREAD_COUNT_MAX )
    {
        //  
        return; 
    }

    Thread = (void *) threadList[tid];

    if ( (void *) Thread == NULL ){
        return; 
    }

    if ( Thread->magic != THREAD_MAGIC )
    {
        return; 
    }

    Thread->state = READY;
}


void 
SetThread_PML4PA ( 
    struct thread_d *thread, 
    unsigned long pa )
{
    if ( (void *) thread == NULL )
    {
        //
        return;
    }

// #todo:
// Aqui podemos checar a validade da estrutura,
// antes de operarmos nela.

    thread->pml4_PA = (unsigned long) pa;
}


void check_for_dead_thread_collector(void)
{
    // #importante
    // Essa flag é acionada quando uma thread 
    // entra em estado zombie.

    switch (dead_thread_collector_flag)
    {
        // waik up
        // Liberamos a thread.
        // O próprio dead thread collector vai sinalizar que 
        // quer dormir, dai o case default faz isso.

        case 1:
            // #suspenso
            // release ( RING0IDLEThread->tid );
            break;

        // sleep
        default:
            // #suspenso
            //block_for_a_reason ( 
            //    RING0IDLEThread->tid, 
            //    WAIT_REASON_BLOCKED );
            
            dead_thread_collector_flag = FALSE;
            break;
    };
}



// dead_thread_collector:
// Procura por uma thread no estado zombie mata ela.
// #todo: Alertar o processo que a thread morreu.
// #todo: O scheduler colocou algumas threads em zombie state
// e agora, temos a condição de matar as threads zombie,
// mas não pode ser a thread idle nem a thread atual.

void dead_thread_collector(void)
{
    register int i=0;  //loop

    struct thread_d  *Target;
    struct thread_d  *Idle; 

//
// Check idle
//

    Idle = (struct thread_d *) UPProcessorBlock.IdleThread;
    if ( (void *) Idle == NULL ){
        panic("dead_thread_collector: Idle\n");
    }
    if (Idle->magic != 1234){
        panic("dead_thread_collector: Idle validation\n");
    }


// loop
// Scan
// Kill zombie
//

    for ( i=0; i < THREAD_COUNT_MAX; i++ )
    {
        Target = (void *) threadList[i];

        if ( (void *) Target != NULL )
        {
            if ( Target->state == ZOMBIE  && 
                 Target->used  == TRUE    && 
                 Target->magic == 1234 )
            {
                // Não podemos matar a Idle thread.
                if ( Target == Idle ){
                    panic ("dead_thread_collector: We can't kill the Idle thread!\n");
                }

                // Não podemos matar thread atual,
                // pois precisamos retornar a execução dela.
                if ( Target->tid == current_thread ){
                    panic ("dead_thread_collector: We can't kill the current_thread!\n");
                }

                // Kill
                // #todo: Podemos apenas colocar a estrutura no stock
                // ao invez de destruir ela.

                Target->used = 0;
                Target->magic = 0;
                Target->state = DEAD; // Por enquanto apenas fecha.

                Target = NULL;
                threadList[i] = (unsigned long) 0;

                // diminui o contador                
                UPProcessorBlock.threads_counter--;
                if ( UPProcessorBlock.threads_counter < 1 ){
                    panic("dead_thread_collector: threads_counter\n");
                }

                // #importante:
                // Nessa hora precisamos notificar o 
                // a thread que estava esperando essa thread terminar.
                // Se essa for a thread primária então o processo 
                // irá terminar também, então o processo que esperava 
                // também deverá ser notificado.
            };
            //Nothing.
        };
        //Nothing.
    };

//@todo:
// MOVEMENT 10 (zombie --> Dead)
// MOVEMENT 11 (zombie --> Initialized) .. reinicializar.

}


/*
 * kill_thread:
 *     Destrói uma thread.
 *     Destroi a estrutura e libera o espaço na lista.
 */

void kill_thread (int tid)
{
    int Lzzz = tid;
    debug_print ("kill_thread: Not implemented\n");
    panic       ("kill_thread: Not implemented\n");
}

void kill_all_threads(void)
{
    register int i=0;
    
    // Start at '1'.
    // Cant kill Idle thread.
    for ( i=1; i < THREAD_COUNT_MAX; ++i )
    { 
        kill_thread(i);
    };
}



