/*
 * Arquivo: queue.c
 *
 *     Faz parte do Process Manager, parte fundamental do Kernel Base.
 *
 * Descrição:
 *     Rotinas de queue para o kernel.
 *     Obs: As rotinas de queue aqui usam uma abordagem não convencional
 * e pouco eficiente. 
 *
 * Versão 1.0, 2015.
 */
 

#include <kernel.h>


/*
 * init_queue:
 *     Inicializa a estrutura de fila.
 */
int init_queue(struct queue_d *q)
{	
 
	unsigned int i;
	
    q->standbyHead = 0; 
    q->standbyTail = 0;
    q->standbyMax  = DISPATCHER_PRIORITY_MAX;

    q->runningHead = 0; 
    q->runningTail = 0;
    q->runningMax  = DISPATCHER_PRIORITY_MAX;	
		
	//ready.
	q->readyHead = 0; 
    q->readyTail = 0;
    q->readyMax  = DISPATCHER_PRIORITY_MAX;	
	
	//waiting.
    q->waitingHead  = 0;
    q->waitingTail  = 0;
    q->waitingMax   = DISPATCHER_PRIORITY_MAX;
		
    q->blockedHead  = 0;
    q->blockedTail  = 0;
    q->blockedMax   = DISPATCHER_PRIORITY_MAX;
	
	
    q->zombieHead  = 0;
    q->zombieTail  = 0;
    q->zombieMax   = DISPATCHER_PRIORITY_MAX;

    q->deadHead  = 0;
    q->deadTail  = 0;
    q->deadMax   = DISPATCHER_PRIORITY_MAX;

    q->initializedHead  = 0;
    q->initializedTail  = 0;
    q->initializedMax   = DISPATCHER_PRIORITY_MAX;
	
	
  //Cooperação, sistema.
    q->syscoopHead = 0; 
    q->syscoopTail = 0;
    q->syscoopMax = DISPATCHER_PRIORITY_MAX;


	//Concorrência, sistema.
    q->sysconcHead = 0; 
    q->sysconcTail = 0;
    q->sysconcMax = DISPATCHER_PRIORITY_MAX;


	//Concorrência, usuário.
    q->userconcHead = 0; 
    q->userconcTail = 0;
    q->userconcMax = DISPATCHER_PRIORITY_MAX;
	
	//Cooperação, usuário.
    q->usercoopHead = 0; 
    q->usercoopTail = 0;
    q->usercoopMax = DISPATCHER_PRIORITY_MAX;
	
	//realtime.
	q->realtimeHead = 0; 
    q->realtimeTail = 0;
    q->realtimeMax  = DISPATCHER_PRIORITY_MAX;

	
	//default.
    q->defaultHead  = 0;
    q->defaultTail  = 0;
    q->defaultMax   = DISPATCHER_PRIORITY_MAX;


	i=0;
	while(i <= q->standbyMax){
	    q->standbyList[i] = (unsigned long) 0; 
		++i;
	};	
	
	i=0;
	while(i <= q->runningMax){
	    q->runningList[i] = (unsigned long) 0; 
		++i;
	};	

	
    //Ready list.
	i=0;
	while(i <= q->readyMax){
	    q->readyList[i] = (unsigned long) 0; 
		++i;
	};
	
	//Wainting list.
	i=0;
    while(i <= q->waitingMax){
		q->waitingList[i] = (unsigned long) 0;	
		++i;
	};	
	
	i=0;
    while(i <= q->blockedMax){
		q->blockedList[i] = (unsigned long) 0;	
		++i;
	};		
	
	i=0;
    while(i <= q->zombieMax){
		q->zombieList[i] = (unsigned long) 0;	
		++i;
	};		
	
	i=0;
    while(i <= q->deadMax){
		q->deadList[i] = (unsigned long) 0;	
		++i;
	};	
	
	i=0;
    while(i <= q->initializedMax){
		q->initializedList[i] = (unsigned long) 0;	
		++i;
	};		
	
    //syscoop.
	i=0;
	while(i <= q->syscoopMax){
	    q->syscoopList[i] = (unsigned long) 0; 
		++i;
	};

	//usercoop.
	i=0;
	while(i <= q->usercoopMax){
	    q->usercoopList[i] = (unsigned long) 0; 
		++i;
	};

	//sysconc.
	i=0;
	while(i <= q->sysconcMax){
	    q->sysconcList[i] = (unsigned long) 0; 
		++i;
	};
     
	//userconc. 
	i=0;
	while(i <= q->userconcMax){
	    q->userconcList[i] = (unsigned long) 0; 
		++i;
	};

	
    //Realtime list.
	i=0;
	while(i <= q->realtimeMax){
	    q->realtimeList[i] = (unsigned long) 0; 
		++i;
	};
	
	//Default list.
	i=0;
    while(i <= q->defaultMax){
		q->defaultList[i] = (unsigned long) 0;	
		++i;
	};
	
//
// Done.
//	
done:
	return (int) 0;
};



/*
 * queue_insert_data:
 *     Coloca um dado no fim da fila. (FIFO)
 */
int queue_insert_data(struct queue_d *q, unsigned long data, int type)
{
    if((void*) q == NULL){
        printf("queue_insert_data:"); 
		refresh_screen();
        while(1){}		
    };	
	
	switch(type)
	{	
        case QUEUE_STANDBY:
		    goto standbyInsertData;
            break;		

        case QUEUE_RUNNING:
		    goto runningInsertData;
            break;		
			
	    //tipo ready
	    case QUEUE_READY:
		    goto readyInsertData;
		    break;
		
		//tipo waiting
		case QUEUE_WAITING:
		    goto waitingInsertData;
		    break;		        
		
        case QUEUE_BLOCKED:
		    goto blockedInsertData;
            break;			
		
        case QUEUE_ZOMBIE:
		    goto zombieInsertData;
            break;	
			
        case QUEUE_DEAD:
		    goto deadInsertData;
            break;
			
        case QUEUE_INITIALIZED:
		    goto initializedInsertData;
            break;				
		
		case QUEUE_SYSCOOP:
		    goto syscoopInsertData;
            break;
			
        case QUEUE_USERCOOP: 
		    goto usercoopInsertData;
            break;
			
        case QUEUE_SYSCONC:
		    goto sysconcInsertData;
            break;
			
        case QUEUE_USERCONC:
		    goto userconcInsertData;
            break;		
		
		//tipo realtime
		case QUEUE_REALTIME:
		    goto realtimeInsertData;
		    break;
		
		//qualquer tipo.
		default:
		    goto defaultInsertData;
		    break;
	};
	
//STANDBY	
standbyInsertData:
    q->standbyList[q->standbyTail++] = (unsigned long) data;
	if(q->standbyTail >= q->standbyMax){
	    q->standbyTail = q->standbyHead;
	}
    goto done;

//running	
runningInsertData:
    q->runningList[q->runningTail++] = (unsigned long) data;
	if(q->runningTail >= q->runningMax){
	    q->runningTail = q->runningHead;
	}
    goto done;
		
	
//Ready Threads. fila do dispatcher	
readyInsertData:
    q->readyList[q->readyTail++] = (unsigned long) data;
	if(q->readyTail >= q->readyMax){
	    q->readyTail = q->readyHead;
	}
    goto done;	
	
//Waiting Threads.	
waitingInsertData:
    q->waitingList[q->waitingTail++] = (unsigned long) data;
	if(q->waitingTail >= q->waitingMax){
	    q->waitingTail = q->waitingHead;
	}
    goto done;	

//blocked	
blockedInsertData:
    q->blockedList[q->blockedTail++] = (unsigned long) data;
	if(q->blockedTail >= q->blockedMax){
	    q->blockedTail = q->blockedHead;
	}
    goto done;
	
	
//zombie	
zombieInsertData:
    q->zombieList[q->zombieTail++] = (unsigned long) data;
	if(q->zombieTail >= q->zombieMax){
	    q->zombieTail = q->zombieHead;
	}
    goto done;
	
//dead	
deadInsertData:
    q->deadList[q->deadTail++] = (unsigned long) data;
	if(q->deadTail >= q->deadMax){
	    q->deadTail = q->deadHead;
	}
    goto done;

//initialized
initializedInsertData:
    q->initializedList[q->initializedTail++] = (unsigned long) data;
	if(q->initializedTail >= q->initializedMax){
	    q->initializedTail = q->initializedHead;
	}
    goto done;

syscoopInsertData: 
    q->syscoopList[q->syscoopTail++] = (unsigned long) data;
	if(q->syscoopTail >= q->syscoopMax){
	    q->syscoopTail = q->syscoopHead;
	}
    goto done;

usercoopInsertData:
    q->usercoopList[q->usercoopTail++] = (unsigned long) data;
	if(q->usercoopTail >= q->usercoopMax){
	    q->usercoopTail = q->usercoopHead;
	}
    goto done;

sysconcInsertData:
    q->sysconcList[q->sysconcTail++] = (unsigned long) data;
	if(q->sysconcTail >= q->sysconcMax){
	    q->sysconcTail = q->sysconcHead;
	}
    goto done;
	
userconcInsertData:
    q->userconcList[q->userconcTail++] = (unsigned long) data;
	if(q->userconcTail >= q->userconcMax){
	    q->userconcTail = q->userconcHead;
	}
    goto done;
	
//Real Time Threads.	
realtimeInsertData:
    q->realtimeList[q->realtimeTail++] = (unsigned long) data;
	if(q->realtimeTail >= q->realtimeMax){
	    q->realtimeTail = q->realtimeHead;
	}
    goto done;

//Default queue.
defaultInsertData:
    q->defaultList[q->defaultTail++] = (unsigned long) data;
	if(q->defaultTail >= q->defaultMax){
	    q->defaultTail = q->defaultHead;
	}
    goto done;
//Done.
done:
	return (int) 0;
};


/*
 * queue_insert_head:
 *     Coloca um dado no fim da fila. (LIFO)
 */
int queue_insert_head(struct queue_d *q, unsigned long data, int type)
{
    if((void*) q == NULL){
        printf("queue_insert_head:"); 
		refresh_screen();
        while(1){}		
    };	
	
	switch(type)
	{
        case QUEUE_STANDBY:
		    goto standbyInsertData; 
            break;		

        case QUEUE_RUNNING:
		    goto runningInsertData; 
            break;		
			
	    //tipo ready
	    case QUEUE_READY:
		    goto readyInsertData; 
		    break;
		
		//tipo waiting
		case QUEUE_WAITING:
		    goto waitingInsertData; 
		    break;		        
		
        case QUEUE_BLOCKED:
		    goto blockedInsertData; 
            break;			
		
        case QUEUE_ZOMBIE:
		    goto zombieInsertData; 
            break;	
			
        case QUEUE_DEAD:
		    goto deadInsertData;  
            break;
			
        case QUEUE_INITIALIZED:
		    goto initializedInsertData; 
            break;	
			
        case QUEUE_SYSCOOP:
		    goto syscoopInsertData;
            break;	
			
        case QUEUE_USERCOOP: 
		    goto usercoopInsertData;
            break;
			
        case QUEUE_SYSCONC:
		    goto sysconcInsertData;
            break;
			
        case QUEUE_USERCONC:
		    goto userconcInsertData;
            break;		
			
	    //tipo ready
	    case QUEUE_REALTIME:
		    goto realtimeInsertData;
		    break;
		
		//qualquer tipo.
		default:
		    goto defaultInsertData;
		    break;
	};
	
standbyInsertData:
    q->standbyList[q->standbyHead] = (unsigned long) data;
    goto done;

runningInsertData:
    q->runningList[q->runningHead] = (unsigned long) data;
    goto done;
	
readyInsertData:
    q->readyList[q->readyHead] = (unsigned long) data;
    goto done;	
	
waitingInsertData:
    q->waitingList[q->waitingHead] = (unsigned long) data;
    goto done;	
	
blockedInsertData:
    q->blockedList[q->blockedHead] = (unsigned long) data;
    goto done;	
	
zombieInsertData:
    q->zombieList[q->zombieHead] = (unsigned long) data;
    goto done;	
	
deadInsertData:
    q->deadList[q->deadHead] = (unsigned long) data;
    goto done;	

initializedInsertData:
    q->initializedList[q->initializedHead] = (unsigned long) data;
    goto done;	
	
syscoopInsertData: 
    q->syscoopList[q->syscoopHead] = (unsigned long) data;
    goto done;

usercoopInsertData:
    q->usercoopList[q->usercoopHead] = (unsigned long) data;
    goto done;

sysconcInsertData:
    q->sysconcList[q->sysconcHead] = (unsigned long) data;
    goto done;

userconcInsertData:
    q->userconcList[q->userconcHead] = (unsigned long) data;
    goto done;

realtimeInsertData:
    q->realtimeList[q->realtimeHead] = (unsigned long) data;
    goto done;
	
defaultInsertData:
    q->defaultList[q->defaultHead] = (unsigned long) data;
    goto done;
//Done.
done:
	return (int) 0;
};


/*
 * queue_get_data:
 *     Pega um dado de uma fila.
 *     Pega da ready. (FIFO)
 *     ?? Pega e remove o primeiro elemento da lista. 
 */
void *queue_get_data(struct queue_d *q, int type)
{
    struct queue_d *New;
	
    if((void*) q == NULL){
        printf("queue_get_data:"); 
		refresh_screen();
        while(1){}		
    };		
	
	switch(type)
	{
        case QUEUE_STANDBY:
		    goto standbyGetData;
            break;		

        case QUEUE_RUNNING:
		    goto runningGetData; 
            break;		
			
	    //tipo ready
	    case QUEUE_READY:
		    goto readyGetData; 
		    break;
		
		//tipo waiting
		case QUEUE_WAITING:
		    goto waitingGetData; 
		    break;		        
		
        case QUEUE_BLOCKED:
		    goto blockedGetData;  
            break;			
		
        case QUEUE_ZOMBIE:
		    goto zombieGetData; 
            break;	
			
        case QUEUE_DEAD:
		    goto deadGetData;  
            break;
			
        case QUEUE_INITIALIZED:
		    goto initializedGetData;  
            break;	
	
        case QUEUE_SYSCOOP:
		    goto syscoopGetData;
            break;
			
        case QUEUE_USERCOOP: 
		    goto usercoopGetData;
            break;
			
        case QUEUE_SYSCONC:
		    goto sysconcGetData;
            break;
			
        case QUEUE_USERCONC:
		    goto userconcGetData;
            break;		
			
	    //tipo realtime
	    case QUEUE_REALTIME:
		    goto realtimeGetData;
		    break;
		
		//qualquer tipo.
		default:
		    goto defaultGetData;
		    break;
	};	
	
standbyGetData:
    New = (void*) q->standbyList[q->standbyHead];	
    goto done;
runningGetData:
    New = (void*) q->runningList[q->runningHead];	
    goto done;
readyGetData:
    New = (void*) q->readyList[q->readyHead];	
    goto done;
waitingGetData:
    New = (void*) q->waitingList[q->waitingHead];
    goto done;	
blockedGetData:
    New = (void*) q->blockedList[q->blockedHead];
    goto done;	
zombieGetData:
    New = (void*) q->zombieList[q->zombieHead];
    goto done;	
deadGetData:
    New = (void*) q->deadList[q->deadHead];
    goto done;	
initializedGetData:
    New = (void*) q->initializedList[q->initializedHead];
    goto done;	
syscoopGetData: 
    New = (void*) q->syscoopList[q->syscoopHead];	
    goto done;
usercoopGetData:
    New = (void*) q->usercoopList[q->usercoopHead];	
    goto done;
sysconcGetData:
    New = (void*) q->sysconcList[q->sysconcHead];	
    goto done;
userconcGetData:
    New = (void*) q->userconcList[q->userconcHead];	
    goto done;
realtimeGetData:
    New = (void*) q->realtimeList[q->realtimeHead];	
    goto done;
defaultGetData:
    New = (void*) q->defaultList[q->defaultHead];
    goto done;
// Done.
done:
    //feed_ready_queue(q,1);    //feed head.
    return (void*) New;    	
};


/*
 * show_queue_information:
 *      Mostra informações sobre a queue.
 */
void show_queue_information(struct queue_d *q)
{	
	int i=0;
	
	if((void*) q == NULL){
	    printf("show_queue_information error: Struct.\n");
		return;
	};

    printf("Ready queue Information:\n");	
	printf("Head={%d} Tail={%d}\n", q->readyHead, q->readyTail);
	
    while(i < q->readyMax)
    {	
	    q = (void *) q->readyList[i];
        if( (void *) q != NULL ){
            printf("Index={%d} Struct={%x}\n", i, (void*) q );
		}; 
		++i;
	};

	//@todo: Informações de outras filas.
	
done:	
	return;
};


/*
 * ScanReadyQueue:
 *     Procura na fila de threads ready por threads com timeout vencido.
 *     e põe na frente da fila.
 */
void ScanReadyQueue(struct queue_d *q)
{
	struct thread_d *t;
	int i=0;
	
	if((void*)q == NULL){
	    printf("ScanReadyQueue error: Struct.\n");
	    return;
	};
		
	//printf("head={%d} tail={%d}\n", q->readyHead, q->readyTail);

    while( i < q->readyMax)
    {	
	    t = (void *) q->readyList[i];
        if( (void *) t != NULL && t->used == 1 && t->magic == 1234 )
		{
		    if( t->waitingCount >= t->waiting_limit )
            {
			    t->waitingCount = 0;
				t->priority = PRIORITY_BOOST;
				queue_insert_head(queue, (unsigned long) t, 1);
				return;
            };			
		}; 
		++i;
	};
    return;
};


void feed_ready_queue(struct queue_d *q, int type)
{
	struct thread_d *t;
	unsigned long p;
	int i;
	
	//Struct.
	if((void*)q == NULL){
	    printf("feed_ready_queue:");
		refresh_screen();
		while(1){}
	};
	
    switch(type)
    {
	    //Alimenta apenas a 'head' com a thread de maior prioridade.
        case 1:
		    goto feed_head; 
            break;
		
		//Usa os slots com todas as tarefas pra alimentar a fila de ready.
        case 2:
		    goto feed_with_threadList; 
            break;
			
        //alimenta a fila do dispatcher(ready) com elementos de outra lista.
        case 3: 
            break;

		//alimenta a fila do dispatcher(ready) com elementos de outra lista.	
        case 4: 
            break;
		
		default:
		    goto feed_head;
		    break;
	};	

//
// feed_head:	 
//     Alimenta apenas a 'head' com a thread de maior prioridade.
//
feed_head:
    
	i = 1;
    
    do
	{	
	    t = (void *) q->readyList[i];
    
	    if( (void *) t != NULL && t->used == 1 && t->magic == 1234)
	    {
		    if( t->priority == PRIORITY_HIGH || t->priority == PRIORITY_REALTIME )
            {
			    if(t->priority > p)
				{
				    q->readyList[i] = (unsigned long) 0;
				    p = t->priority;
				    queue_insert_head(queue, (unsigned long) t, QUEUE_READY);
				};
				goto done;
            };			
		}; 
		++i;
	}while( i < q->readyMax );
    
	goto done;	
	
	
//usa os slots com todas as tarefas pra alimentar a fila de ready.	
feed_with_threadList:	
	
	i = 1;
    
    do
	{	
	    t = (void *) threadList[i];
        if( (void *) t != NULL && t->used == 1 && t->magic == 1234 )
		{
		    if( t->priority == PRIORITY_HIGH || t->priority == PRIORITY_REALTIME )
            {
			    if( t->priority >= p)
				{
				    q->readyList[i] = (unsigned long) 0;
				    p = t->priority;
				    queue_insert_data(queue, (unsigned long) t, QUEUE_READY);
				};
				goto done;	
            };			
		}; 
		++i;
	}while( i < THREAD_COUNT_MAX );
    	
    goto done;	
	
done:
    return;	
};


//
//fim.
//

