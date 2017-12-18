/*
 * Gramado Kernel - The main file for the kernel.
 * (c) Copyright 2015-2016 Fred Nora.
 *
 * File: k\main.c 
 * 
 * Description:
 *     project browser: 'SHELL.BIN IS MY MASTER.'
 *     This is the Kernel Base. It's the mains file for a 32bit Kernel. 
 *     The type is 'hybrid'.
 *     The entry point is in 'head.s'.
 *
 * This is classes for a logic hardware layout.
 *
 * **** Classes: ****
 * ==================
 * 1) kernel.ram               (K5)
 * 2) kernel.io.cpu            (K4)
 * 2) kernel.io.dma            (K3)
 * 3) kernel.devices.unbloqued (K2)
 * 3) kernel.devices.blocked   (K1)
 * 4) kernel.things            (K0)
 *
 * The first three system utilities are: 
 * IDLE.BIN, SHELL.BIN and TASKMAN.BIN.
 *
 * The Kernel area is the first 4MB of real memory.
 * The image was loaded in the address 0x00100000 and the entry point is in 
 * the address 0x00101000. The logic address for the Kernel image is 
 * 0xC0001000 and the entry point is 0xC0001000.
 * 
 * @todo: Create a log file.
 *
 *  In this file:
 *  ============
 *      + kMain - The entry point for a C part of the Kernel.
 *      + Nothing!
 *
 * Revision History:
 *     Version: 1.0, 2015 - Created by Fred Nora.
 *     Version: 1.0, 2016 - Revision.
 *     //... 
 */ 
#include <kernel.h>


// 
// Variables from Boot Loader.
//

extern unsigned long SavedBootBlock;    //Boot Loader Block.
extern unsigned long SavedLFB;          //LFB address.  
extern unsigned long SavedX;            //Screen width. 
extern unsigned long SavedY;            //Screen height.
extern unsigned long SavedBPP;          //Bits per pixel.
//...

//
// Args.
//

extern unsigned long kArg1;
extern unsigned long kArg2;
extern unsigned long kArg3;
extern unsigned long kArg4;
//...
 

extern unsigned long SavedBootMode;




/*
 * kMain: 
 *     The entry point for a C part of the Kernel.
 *
 * Function history: 
 *     2015 - Created.
 *     Nov 2016 - Revision.
 *     ... 
 */
int kMain(int argc, char* argv[])
{	
    int Status = 0;

    KernelStatus = KERNEL_NULL;
	
	//Inicializando a flag que será usada para travar o foco
	// de entrada na tela do desenvolvedor. gui->DEVELOPERSCREEN
	//@todo: Não usar isso.
	//_lockfocus = 0; 
	
	//Inicializando o semáforo binário do kernel de uso geral.
	//Aplicações usarão isso para entrarem em suas sessões críticas.
	//@todo: Criar um método para isso.
    __ipc_kernel_spinlock = 1;
	
	
    //@todo: Encontrar o lugar apropriado para a  inicialização de zorder 
	//provavelmente na inicialização da gui.
	// initializing zorder list
	int zIndex;
	for( zIndex = 0; zIndex < ZORDER_COUNT_MAX; zIndex++ ){
		zorderList[zIndex] = (unsigned long) 0;
	}
	
	//initializing zorder counter.
	zorderCounter = 0;
	
	//
	// Window procedure.
	//
	
	SetProcedure( (unsigned long) &system_procedure);
	
	
	//
	// Video.
	//
	
//setupVideo:	
	
	//@todo: Device screen sizes.
	
    //Set graphic mode or text mode using a flag.
	if(SavedBootMode == 1){
        g_useGUI = GUI_ON; 
	    VideoBlock.useGui = GUI_ON;
        //... 		
	}else{
		g_useGUI = GUI_OFF;  
		VideoBlock.useGui = GUI_OFF;
        //...		
	};

	//Construtor. 
	//Configura algumas variáveis internas do gerenciador de vídeo.
	videoVideo();
	
	videoInit();  //Setup video first of all.	   
	

	//
	// Init screen
	//
	
	//If we are using graphic mode.
	if(VideoBlock.useGui == GUI_ON){
#ifdef KERNEL_VERBOSE	
		//kbackground(COLOR_BLUE);
	    printf("kMain: Using GUI!\n");	
        //drawDataRectangle( 20, 20, 20, 20, COLOR_RED);
#endif       	
	};
	
	//If we are using text mode.
	if(VideoBlock.useGui != GUI_ON){	
	    set_up_text_color(0x0F, 0x00);
		
		//g_current_vm = 0x800000;
	    //Set cga video memory: 0x800000vir = 0xb8000fis.
	    videoSetupCGAStartAddress(SCREEN_CGA_START); 
	    
	
	    //Debug.
	    kclear(0);
	    kprintf("kMain: Debug" ,9 ,9 );
	    printf("kMain: Text Mode!\n");	    	
	};
	
	//Debug message.
#ifdef KERNEL_VERBOSE
	printf("kMain: Starting up system..\n");
	refresh_screen(); //@TODO: Talvez isso não precise.
	//while(1){}	
#endif
	
	//
	//============================================================
    // System initialization.. system.c
	// Inicializaremos todas funcionalidades do sistema 
	// Mas processos e threads não serão criados.
    //
    
//initializeSystem:
	
	//Construtor.
    systemSystem();	
	
	//Inicializações.
	Status = (int) systemInit();    //(system.c).	
    if(Status != 0){	
		printf("kMain fail: System Init.\n");
		KernelStatus = KERNEL_ABORTED; 
		goto fail;		
	};
	
	//
	//============================================================
	// processes and threads initialization.
	// Creating processes and threads.
	// The processes are: Kernel, Idle, Shell, Taskman.
	// obs: As imagens ja estão carregadas na memória.
	
//createProcesses:	
	
	// Creating Kenrel process. PID=0.	
	KernelProcess = (void*) KiCreateKernelProcess();	
	if( (void*) KernelProcess == NULL ){
	    printf("kMain error: Create KernelProcess!");
		refresh_screen();
		while(1){}
	}else{
		//ppid.
		KernelProcess->ppid = (int) KernelProcess->pid;
        
		//process.
	    processor->CurrentProcess = (void*) KernelProcess;
        processor->NextProcess    = (void*) KernelProcess;	
		//...
    };

    //Creating Idle process.
	InitProcess = (void*) create_process( NULL, NULL, NULL, (unsigned long) 0x00401000, 
	                                      PRIORITY_HIGH, (int) KernelProcess->pid, "IDLEPROCESS");	
	if((void*) InitProcess == NULL){
		printf("kMain error: Create Idle process.\n");
		die();
		//refresh_screen();
		//while(1){};
	};
    //processor->IdleProcess = (void*) IdleProcess;	
	
	
    //Creating Shell process.
	ShellProcess = (void*) create_process( NULL, NULL, NULL, (unsigned long) 0x00401000, 
	                                       PRIORITY_HIGH, (int) KernelProcess->pid, "SHELLPROCESS");	
	if((void*) ShellProcess == NULL){
		printf("kMain error: Create shell process.\n");
		die();
		//refresh_screen();
		//while(1){};
	};	

	
	//Creating Taskman process. 
	TaskManProcess = (void*) create_process( NULL, NULL, NULL, (unsigned long) 0x00401000, 
	                                         PRIORITY_LOW, KernelProcess->pid, "TASKMANPROCESS");	
	if((void*) TaskManProcess == NULL){
		printf("kMain error: Create taskman process.\n");
		die();
		//refresh_screen();
		//while(1){};
	};		
	
	
	
	//
	// Creating threads. 
	// The threads are: Idle, Shell, Taskman.
	// The Idle thread belong to Idle process.
	// The Shell thread belongs to Shell process.
	// The Taskman thread belongs to Taskman process.
	//

//createThreads:
	
	//Create Idle Thread. tid=0. ppid=0.
	IdleThread = (void*) KiCreateIdle();	
	if( (void*) IdleThread == NULL )
	{
	    printf("kMain error: Create Idle Thread!");
		die();
		//refresh_screen();
		//while(1){}
	}else{
	    
        IdleThread->ownerPID = (int) InitProcess->pid;  //ID do processo ao qual o thread pertence.    
		
		//Thread.
	    processor->CurrentThread = (void*) IdleThread;
        processor->NextThread    = (void*) IdleThread;
        processor->IdleThread    = (void*) IdleThread;		
		//...		
    };
	
	
	
	// Create shell Thread. tid=1. 
	ShellThread = (void*) KiCreateShell();	
	if( (void*) ShellThread == NULL ){
	    printf("kMain error: Create Shell Thread!");
		die();
		//refresh_screen();
		//while(1){}
	}else{
		
	    ShellThread->ownerPID = (int) ShellProcess->pid;  //ID do processo ao qual o thread pertence. 
		//...		
    };
	
	
	//Create taskman Thread. tid=2. 
	TaskManThread = (void*) KiCreateTaskManager();
	if( (void*) TaskManThread == NULL ){
	    printf("kMain error: Create TaskMan Thread!");
		die();
		//refresh_screen();
		//while(1){}
	}else{
		
	    TaskManThread->ownerPID = (int) TaskManProcess->pid; //ID do processo ao qual o thread pertence. 		
		//...		
    };	
	

 
    //
	// Debug.
	//
	
doDebug:
	
	//Kernel base Debugger.
	Status = (int) debug();	
	if(Status != 0){    
		//printf("kMain fail: Debug!\n");
		MessageBox(gui->screen,1,"kMain ERROR","Debug Status Fail!");
		KernelStatus = KERNEL_ABORTED;	
		goto fail;
	}else{
	    KernelStatus = KERNEL_INITIALIZED;
	};	
	
	

	//
	// TESTS:
	// We can make some testes here.
	//
//doTests:	
   //...
    


	//if(VideoBlock.useGui != 1){	
	//    kclear(0);
    //    kprintf("kMain: Done" ,10 ,9 );
    //};
	
	
	
	//
	// *Importante:
	//  Iniciando o suporte ao browser.
	//  O Browser é uma janela criada e gerenciada pelo kernel ...
	//  em suas abas rodarão os aplicativos e páginas da web.
	//
	
	/* suspendido
	printf("main: initializing browser support.\n");
	windowInitializeBrowserSupport();
	printf("main: done.\n");
	*/
	
	
	//
	// Tentando inicializar o controlador de mouse.
	//
	// Já foi criada a irq12
	// ja foi configurado vetor da IDT.
	// já foi criado um handle para a irq12.
	// agora inicializaremos o controlador 8042
	// testando inicializar o mouse no procedimento de janela do sistema em F6.
	
	
	//
	// * Isso funcionou. Inicializando mouse e teclado juntos.
	//   @todo: Deixar isso aqui.
	//
	
    ps2();	
	
	//
	// Done.
	//

  // void *b;
   
done:

   /*	
    //===================================
	// @todo: Carregar a estrelinha e usar como ponteiro de mouse.
	//
	//janela de test
    CreateWindow( 1, 0, 0, "Fred-BMP-Window", 
	              (30-5), (450-5), (128+10), (128+10), 
				  gui->main, 0, COLOR_WINDOW, COLOR_WINDOW); 
	// testing BMP support 32KB
	b = (void*) malloc(512*1024);
	//#bugbug checar a validade do buffer
	
	unsigned long fileret;
		
	//taskswitch_lock();
	//scheduler_lock();
	fileret = fsLoadFile( "FREDNORABMP", (unsigned long) b);
	if(fileret != 0)
	{
		//escrevendo string na janela
	    draw_text( gui->main, 10, 500, COLOR_WINDOWTEXT, "FREDNORA BMP FAIL");  	
	}
	bmpDisplayBMP( b, 30, 450, 128, 128 );
	//scheduler_unlock();
	//taskswitch_unlock();

    //===================================	
	*/
	
	/*
	  * esse teste funcionou.
	//
	// testando a alocação de páginas.
	//
	
	printf("main: testing page allocator\n");
	
	// isso substitui o malloc.
	b = (void*) newPage();
	if( (void *) b == NULL ){
		printf("main: newPage: buffer:");
		refresh_screen();
		while(1){}
	}
	
	unsigned long fileret;
	fileret = fsLoadFile( "INIT    TXT", (unsigned long) b);
	if(fileret != 0)
	{
		//escrevendo string na janela
	    draw_text( gui->main, 10, 500, COLOR_WINDOWTEXT, "INIT.TXT FAIL");  	
	}else{
		
		printf("%s",b);
		refresh_screen();
		while(1){}
	}	
	
	//#debug
	printf("main: debug done");
	refresh_screen();
	while(1){}
	
	*/
	
	//
	// RETURNING !
	//
	
	//
	// Return to assembly file, (head.s).
	//
	
	if(KernelStatus == KERNEL_INITIALIZED)
	{

#ifdef KERNEL_VERBOSE
		//printf("KeMain: EXIT_SUCCESS\n");
		refresh_screen();
#endif	

        //
		// **  START IDLE THREAD  **
		//
		
		startStartIdle() ;
		
	    //return (int) EXIT_SUCCESS;	
	};
	
	// Fail!
fail:
    //if(KernelStatus != KERNEL_INITIALIZED){...};	
	//printf("KeMain: EXIT_FAILURE\n");
	MessageBox(gui->screen,1,"kMain ERROR","Kernel main EXIT_FAILURE!");
	refresh_screen();  
	return (int) EXIT_FAILURE;   
};




extern void turn_task_switch_on();


static inline void mainSetCr3( unsigned long value)
{
    __asm__ ( "mov %0, %%cr3" : : "r"(value) );
}

/*
 * startStartIdle:
 *     Inicia a thead idle.
 *
 *     @todo: 
 *         + Iniciar o processo da idle.
 *         + Detectar se o aplicativo está carregado na memória 
 *	         antes de passar o comando pra ele via iret.
 *          Mudar para startIdleThread().
 *
 */
void startStartIdle() 
{
	int i;
	//struct thread_d *Thread;
	
	//Thread = (void *) threadList[0];
 
	
	if((void*) IdleThread == NULL)
	{
		//printf("KeStartIdle error: Struct!\n");
	    MessageBox(gui->screen,1,"ERRO","KeStartIdle: struct");
        KeAbort();
	}else{
	    
		//Checar se o programa já foi inicializado antes. 
		//Ele não pode estar.
	    if(IdleThread->saved != 0){
	        printf("KeStartIdle error: Context!\n");
            KeAbort(); 			
	    };
	    
		//Checar se o slot na estrutura de tarefas é válido.
	    if(IdleThread->used != 1 || IdleThread->magic != 1234){
	        printf("KeStartIdle: IdleThread %d corrompida.\n", IdleThread->tid);
            KeAbort(); 		
	    };
		
        set_current(IdleThread->tid);      //Seta a thread atual.	
		//...
	};
	
	// State ~ Checa o estado da tarefa.	 
    if(IdleThread->state != STANDBY){
        printf("KeStartIdle error: State. Id={%d}\n",IdleThread->tid);
	    refresh_screen();
	    while(1){};
    };
	
    // * MOVEMENT 2 ( Standby --> Running)	
    if(IdleThread->state == STANDBY){
		IdleThread->state = RUNNING;    
		queue_insert_data(queue, (unsigned long) IdleThread, QUEUE_RUNNING);
	};		
//Done!
done:	
	//Debug:
	//Alertando.
    //printf("* Starting idle TID=%d \n", Thread->tid); 
	//refresh_screen(); //@todo: isso é necessãrio ??


	for( i=0; i<=DISPATCHER_PRIORITY_MAX; i++){
	    dispatcherReadyList[i] = (unsigned long) IdleThread;
	};
	
    IncrementDispatcherCount(SELECT_IDLE_COUNT);
	
	
	
		 
	mainSetCr3( (unsigned long) IdleThread->Directory);

	//flush TLB
	asm("movl %cr3, %eax");
    asm("movl %eax, %cr3");			
	
	
	/*
	 * turn_task_switch_on:
	 * + Cria um vetor para o timer, IRQ0.
	 * + Habilita o funcionamento do mecanismo de taskswitch.
	 */	 
	turn_task_switch_on(); 
	
	
	//
	// @todo: Testando timer novamente.
	//        *IMPORTANTE Me parece que tem que configurar o PIT por último.
	//
	
	timerInit8253(); 
	    		
    asm volatile(" cli \n"   
                 " mov $0x23, %ax  \n" 
                 " mov %ax, %ds  \n"
                 " mov %ax, %es  \n"
                 " mov %ax, %fs  \n"
                 " mov %ax, %gs  \n"
                 " pushl $0x23            \n"    //ss.
                 " movl $0x0044FFF0, %eax \n"
                 " pushl %eax             \n"    //esp.
                 " pushl $0x3200          \n"    //eflags.
                 " pushl $0x1B            \n"    //cs.
                 " pushl $0x00401000      \n"    //eip. 
                 " iret \n" );
				//Nothing.
// Fail ~ retorno inesperado.
fail:
    panic("KeStartIdle error: Return!"); 	
	while(1){};  //no return.	   
};




 
//
// End.
//

