

#include <kernel.h>

unsigned long __GetProcessStats ( int pid, int index ){

    struct process_d *p;


    if (pid<0){
        panic ("__GetProcessStats: pid \n");
    }

    // Process

    p = (void *) processList[pid];

    if ( (void *) p == NULL ){
        printf ("__GetProcessStats: struct \n");
        return 0; 

    } else {
        //checar validade.
		//...
    };


    switch (index){

        case 1:  return (unsigned long) p->pid;  break; 
        case 2:  return (unsigned long) p->ppid;  break; 
        case 3:  return (unsigned long) p->uid;  break; 
        case 4:  return (unsigned long) p->gid;  break; 
        case 5:  return (unsigned long) p->state;  break; 
        case 6:  return (unsigned long) p->plane;  break; 
        case 7:  return (unsigned long) p->input_type;  break; 
        case 8:  return (unsigned long) p->personality;  break; 
        case 9:  return (unsigned long) p->appMode;  break; 

        case 10:  
            return (unsigned long) p->private_memory_size;
            break;  

        case 11:
            return (unsigned long) p->shared_memory_size;
            break;          

        case 12:
            return (unsigned long) p->workingset_size;
            break;          

        case 13:
            return (unsigned long) p->workingset_peak_size;
            break;          

        case 14:
            return (unsigned long) p->pagefaultCount;
            break;          

        //case 15:  return (unsigned long) p->DirectoryPA;  break;
        //case 16:  return (unsigned long) p->DirectoryVA;  break;
        
        case 17:  return (unsigned long) p->Image;  break;
        case 18:  return (unsigned long) p->ImagePA;  break;
        case 19:  return (unsigned long) p->childImage;  break;
        case 20:  return (unsigned long) p->childImage_PA;  break;
        case 21:  return (unsigned long) p->Heap;  break;
        case 22:  return (unsigned long) p->HeapEnd;  break;
        case 23:  return (unsigned long) p->HeapSize;  break;
        case 24:  return (unsigned long) p->HeapPointer;  break;
        case 25:  return (unsigned long) p->HeapLastValid;  break;
        case 26:  return (unsigned long) p->HeapLastSize;  break;
        case 27:  return (unsigned long) p->Stack;  break;
        case 28:  return (unsigned long) p->StackEnd;  break;
        case 29:  return (unsigned long) p->StackSize;  break;
        case 30:  return (unsigned long) p->StackOffset;  break;
        case 31:  return (unsigned long) p->iopl;  break;
        case 32:  return (unsigned long) p->base_priority;  break;
        case 33:  return (unsigned long) p->priority;  break;
        case 34:  return (unsigned long) p->step;  break;
        case 35:  return (unsigned long) p->quantum;  break;
        case 36:  return (unsigned long) p->timeout;  break;
        case 37:  return (unsigned long) p->ticks_remaining;  break;
        
        case 38:  
            return (unsigned long) p->profiler_percentage_running;
            break;

        case 39:
            return (unsigned long) p->profiler_ticks_running;
            break;

        case 40:
            return (unsigned long) p->profiler_last_ticks;
            break;

        case 41:  return (unsigned long) p->thread_count;  break;
        case 42:  return (unsigned long) p->bound_type;  break;
        case 43:  return (unsigned long) p->preempted;  break;
        case 44:  return (unsigned long) p->saved;  break;
        case 45:  return (unsigned long) p->PreviousMode;  break;
        case 46:  return (unsigned long) p->wait4pid;  break;
        case 47:  return (unsigned long) p->exit_code;  break;
        case 48:  return (unsigned long) p->signal;  break;
        case 49:  return (unsigned long) p->umask;  break;
        case 50:  return (unsigned long) p->dialog_address; break;
        case 51:  return (unsigned long) p->ImageSize;  break;
           
        // #todo:
        // Precisamos da quantidade de p�ginas usadas.
    
        // ...
    };

    return 0;
}

// Systemcall 882.
// Pega o nome do processo.
int getprocessname ( int pid, char *buffer ){

    struct process_d *p;

    char *name_buffer = (char *) buffer;

    //#todo
    //checar validade dos argumentos.

    if (pid<0){
        debug_print ("getprocessname: [FAIL] pid\n");
        return -1;
    }

    //#todo
    //buffer validation
 
    p = (struct process_d *) processList[pid]; 

    if ( (void *) p == NULL ){
        debug_print ("getprocessname: [FAIL] p\n");
        return -1;
    }else{
        if ( p->used != TRUE || p->magic != 1234 ){
            debug_print ("getprocessname: [FAIL] VALIDATION\n");
            return -1;
        }
        
        // 64 bytes
        strcpy ( name_buffer, (const char *) p->__processname );  
        
        //#bugbug: Provavelmente isso ainda nem foi calculado.
        return (int) p->processName_len;
    };

    return -1;
}

/*
 * processObject:
 *     Cria uma estrutura do tipo processo, mas não inicializada.
 *     #todo: Criar a mesma rotina para threads e janelas.
 */

struct process_d *processObject (void){

    struct process_d *tmp;

    tmp = (void *) kmalloc ( sizeof(struct process_d) );

    if ( (void *) tmp == NULL ){
        panic ("ps-processObject: tmp");
    }

    return (struct process_d *) tmp;
}

/*
 * getNewPID:
 *     Pegar um slot vazio na lista de processos.
 *     +Isso pode ser usado para clonar um processo.
 */

// Começaremos a busca onde começa o range de IDs 
// de processos de usuário.
// Se encontramos um slot vazio, retornaremos o índice.
 
pid_t getNewPID (void){

    struct process_d *p;

    int i = USER_BASE_PID;

    while ( i < PROCESS_COUNT_MAX ){

        p = (struct process_d *) processList[i];

        if ( (void *) p == NULL ){ return (pid_t) i; }
        
        i++;
    };

    debug_print ("getNewPID: fail\n");

    return (pid_t) (-1);
}

/*
 * processTesting:
 *     Testando se o processo � v�lido. Se for v�lido retorna 1234.
 *     @todo: repensar os valores de retorno. 
 * system call (servi�o 88.)
 */

int processTesting (int pid){

    struct process_d *P;

    // Process.
    P = (void *) processList[pid];

    if ( (void *) P == NULL ){
        return 0;

    }else{
        if ( P->used == 1 && P->magic == 1234 ){ return (int) 1234; }
    };

    return 0;
}

/*
 * processSendSignal:
 *     Envia um sinal para um processo.
 *     Se o sinal e o processo forem v�lidos, um sinal � colocado
 * no PCB do processo.
 *     @todo: Rotinas envolvendo sinais devem ir para outro arquivo.
 */

int processSendSignal (struct process_d *p, unsigned long signal){
	
	//SIGNAL_COUNT_MAX
	
	//Limit
    //if(signal >= 32){
	//	return 1;
	//}
	
	if (signal == 0)
	{
		return 1;
	}
	
	//struct fail
	//if( (void*) p == NULL ){
	//	return 1;
	//}		
	
//ok:	
	//Ok
	if ( (void*) p != NULL )
	{	
		p->signal = (unsigned long) signal;
		return 0; //(int) signalSend(p,signal);
	}
	
	//...
	
//fail:
	
	return 1;
}

/*
 ***********************************************************
 * init_processes:
 *    Inicaliza o process manager.
 *   #todo: rever esse nome, pois na verdade estamos inicializando variaveis 
 * usadas no gerenciamento de processo.
 */

// Called by init_microkernel in mk.c

void init_processes (void){

    register int i=0;

    debug_print("init_processes:\n");


	//
	// Iniciando vari�veis globais.
	//

	kernel_request = 0;    // O que fazer com a tarefa atual.
	
	
	// ?? Contagem de tempo de execu��o da tarefa atual.
	//n�o precisa, isso � atualizado pelo request()
	//kernel_tick = 0;                                 

    kernel_switch = 0;     // ?? Ativa o kernel switch do scheduler.

    current_process = 0;


    // Clear process list.
    i=0;
    while (i < PROCESS_COUNT_MAX){
        processList[i] = (unsigned long) 0;
        i++;
    };

    // More ?
}

/*
 * CloseAllProcesses:
 *     Bloqueia todos os processos da lista de processos.
 *     Menos o processo '0'.
 *     processCloseAllProcesses();    
 */

void CloseAllProcesses (void)
{
    //loop
    int i=0;
    
    struct process_d *P;

	// #importante:
	// Menos o 0, pois � o kernel. 

    //Pega, bloqueia e tira da lista.
    for ( i=1; i < PROCESS_COUNT_MAX; i++ )
    {
        P = (void *) processList[i];
        P->state = PROCESS_BLOCKED;
        
        // Not kernel.
        if (i != 100){
            processList[i] = (unsigned long) 0;
        }
    };

    //Check process 0.
    P = (void *) processList[0];

    if ( (void *) P == NULL ){
        panic ("CloseAllProcesses: P\n");
    }

    // #bugbug
    // The kernel is process 100.

    P = (void *) processList[100];

    if ( (void *) P == NULL ){
        panic ("CloseAllProcesses: kernel\n");
    }
}

// usado pelo comando "current-process" no shell
void show_currentprocess_info (void){

    struct process_d *Current;


    if ( current_process < 0 || current_process >= PROCESS_COUNT_MAX )
    {
        //printf("show_process_information: current_process fail\n");
        return;
    }


	//Struct.
    Current = (void *) processList[current_process];

    if ( (void *) Current == NULL )
    {
        printf ("show_currentprocess_info: struct \n");
        return; 

    } else {

		//Index.
        printf ("PID={%d} PPID={%d} UID={%d} GID={%d} \n",
            Current->pid, Current->ppid, Current->uid, Current->gid );
		//Name
        //printf ("Name={%s} \n", Current->name_address );
        printf ("Name={%s} \n", Current->name );
        
		//Image Address.
        printf ("ImageAddress={%x} \n", Current->Image );

		//Directory Address. *IMPORTANTE.
        //printf (">>DirectoryPA={%x} \n", Current->DirectoryPA );
        //printf (">>DirectoryVA={%x} \n", Current->DirectoryVA );

		//Heap and stack.
        printf("Heap={%x}  HeapSize={%d KB}  \n", Current->Heap, 
            Current->HeapSize );

        printf("Stack={%x} StackSize={%d KB} \n", Current->Stack, 
            Current->StackSize );

		//...
    };

    refresh_screen();
}

/*
 * show_process_information:
 *     Mostra informa��es sobre os processos. 
 *     #todo: na verdade um aplicativo em user mode deve fazer esse trabalho
 * solicitando informa��es sobre cada processo atrav�s de chamadas.
 */

// Mostrar informa��es sobre os processos da lista.
// obs: as imagens s�o carregadas em endere�os virtuais diferentes
// e o endere�o mostrado � em rela��o ao diret�rio de p�ginas do kernel
// pois o kernel � que controla o posicionamento das imagens.

void show_process_information (void)
{
    // loop
    int i=0;
    struct process_d *p;

    printf ("show_process_information: \n");


    for ( i=0; i<PROCESS_COUNT_MAX; i++ )
    {

        p = (void *) processList[i];

        if ( (void *) p != NULL && 
                      p->used  == TRUE && 
                      p->magic == 1234 )
        { 

            //printf("\n");
            printf("\n=====================================\n");
            printf(">>[%s]\n", p->__processname);
            printf("PID=%d PPID=%d \n", p->pid,  p->ppid );
            
            printf("image-base =%x image-size =%d \n", 
                p->Image, p->ImageSize );
            printf("heap-base  =%x heap-size  =%d \n", 
                p->Heap,  p->HeapSize );
            printf("stack-base =%x stack-size =%d \n", 
                p->Stack, p->StackSize );

            //printf("dir-pa=%x dir-va=%x \n", 
            //    p->DirectoryPA, p->DirectoryVA );

            printf("iopl=%d prio=%d state=%d \n", 
                p->iopl, p->priority, p->state );

            printf("syscalls = { %d }\n", p->syscalls_counter );
        }
    // Nothing.
    };

    refresh_screen();
}


































