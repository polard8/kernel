/*
 * Gramado Operating System - The main file for the kernel.
 * (c) Copyright 2015~2018 - Fred Nora.
 *
 * File: kernel/entry/x86/x86main.c 
 * 
 * Description:
 *     This is the Kernel Base. 
 *     It's the mains file for a 32 bit x86 Kernel. 
 *     The type is 'hybrid'.
 *     The entry point is in 'head.s'.
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
 *      + mainSetCr3
 *      + startStartIdle
 *      + x86main - The entry point for a C part of the Kernel.
 *
 * Revision History:
 *     2015      - Created by Fred Nora.
 *     2016~2018 - Revision.
 *     //... 
 */ 


#include <kernel.h>


// # external dependencies #

// Variables from Boot Loader.
extern unsigned long SavedBootBlock;    //Boot Loader Block.
extern unsigned long SavedLFB;          //LFB address.  
extern unsigned long SavedX;            //Screen width. 
extern unsigned long SavedY;            //Screen height.
extern unsigned long SavedBPP;          //Bits per pixel.
//...

// Args.
extern unsigned long kArg1;
extern unsigned long kArg2;
extern unsigned long kArg3;
extern unsigned long kArg4;
//...

// Boot mode.
extern unsigned long SavedBootMode;


// Task switching support.
extern void turn_task_switch_on();


char copyright[] =
"Copyright (c) 2005-2018\n\tFred Nora.  All rights reserved.\n\n";


static inline void mainSetCr3 ( unsigned long value ){
	
    __asm__ ( "mov %0, %%cr3" : : "r" (value) );
};


/*
 *********************************************************
 * x86mainStartFirstThread:
 *      #interna
 *      
 *      Seleciona a primeira thread para rodar e salta para user mode.
 */

void x86mainStartFirstThread ( int n ){
	
	int i;
	struct thread_d *Thread;
	 
	if (n < 0)
	{
	    printf ("x86mainStartFirstThread: thread number fail");
        die ();
	}
	
	switch (n){
			
		case 1:
		    Thread = IdleThread; 
		    break;
			
		case 2:
		    Thread = ShellThread;
			break;
		
		case 3:
		    Thread = TaskManThread;
		    break;
			
		default:
	        panic ("x86mainStartFirstThread.default: thread number fail");		
		    break;
	};
	
	
    if ( (void *) Thread == NULL )
    {
        panic ("x86mainStartFirstThread: Thread\n");
		
    } else {

        if ( Thread->saved != 0 )
		{
            printf("x86mainStartFirstThread: saved\n");
            die();
        };

        if ( Thread->used != 1 || Thread->magic != 1234)
		{
            printf("x86mainStartFirstThread: tid={%d} magic \n", Thread->tid);
            die();
        };

        set_current ( Thread->tid );       
        //...
    };

    // State  
    if ( Thread->state != STANDBY )
	{
        printf ("x86mainStartFirstThread: state tid={%d}\n", Thread->tid);
        die();
    }

    // * MOVEMENT 2 ( Standby --> Running)
    if ( Thread->state == STANDBY )
	{
        Thread->state = RUNNING;
        queue_insert_data ( queue, (unsigned long) Thread, QUEUE_RUNNING);
    }


	//Current process.
	current_process = Thread->process->pid;
	
    //
	// Done!
    //
	
    // #debug
    printf ("x86mainStartFirstThread: Starting idle TID=%d (debug) \n", Thread->tid );
    refresh_screen (); 


    for ( i=0; i <= PRIORITY_MAX; i++ ){
		
        dispatcherReadyList[i] = (unsigned long) Thread;
    }


    IncrementDispatcherCount (SELECT_IDLE_COUNT);


    //Set cr3 and flush TLB.
    mainSetCr3 ( (unsigned long) Thread->DirectoryPA );
    asm ("movl %cr3, %eax");
    asm ("movl %eax, %cr3");


    /* turn_task_switch_on:
     * + Creates a vector for timer irq, IRQ0.
     * + Enable taskswitch. */
	 
    turn_task_switch_on();

	//#bugbug:
	//Não podemos inicialziar o timer novamente,
	//temos que aceitar a configuração que o kernel fez.
	//mas essa rotina será a mesma usada como serviço 
	//oferecido pelo kernel, para atualização do HZ.
	//então vamos testá-la.
	
    //timerInit8253 ( HZ );
	timerInit8253 ( 800 );
	
	//parece que isso é realmente preciso, libera o teclado.
	//outb(0x20,0x20); 
   
	// # go!
	// Nos configuramos a idle thread em user mode e agora vamos saltar 
	// para ela via iret.
	
	// #todo:
	// #importante:
	// Podemos usr os endereços que estão salvos na estrutura.
	
	//#bugbug:
	//temos a questão da tss:
	//será que a tss está configurada apenas para a thread idle do INIT ??
	//temos que conferir isso.
	
	//init
    if (n == 1 )
    {		
	
        asm volatile (" cli \n"
                  " mov $0x23, %ax  \n"
                  " mov %ax, %ds  \n"
                  " mov %ax, %es  \n"
                  " mov %ax, %fs  \n"
                  " mov %ax, %gs  \n"
                  " pushl $0x23  \n"              // ss.
                  " movl $0x0044FFF0, %eax  \n"
                  " pushl %eax  \n"               // esp.
                  " pushl $0x3200  \n"            // eflags.
                  " pushl $0x1B  \n"              // cs.
                  " pushl $0x00401000  \n"        // eip.
                  " iret \n" );
	};
	
	//shell
    if (n == 2 )
    {		
	
        asm volatile (" cli \n"
                  " mov $0x23, %ax  \n"
                  " mov %ax, %ds  \n"
                  " mov %ax, %es  \n"
                  " mov %ax, %fs  \n"
                  " mov %ax, %gs  \n"
                  " pushl $0x23  \n"              // ss.
                  " movl $0x0049FFF0, %eax  \n"
                  " pushl %eax  \n"               // esp.
                  " pushl $0x3200  \n"            // eflags.
                  " pushl $0x1B  \n"              // cs.
                  " pushl $0x00451000  \n"        // eip.
                  " iret \n" );
	};
	
    //taskman
    if (n == 3 )
    {		
	
        asm volatile (" cli \n"
                  " mov $0x23, %ax  \n"
                  " mov %ax, %ds  \n"
                  " mov %ax, %es  \n"
                  " mov %ax, %fs  \n"
                  " mov %ax, %gs  \n"
                  " pushl $0x23  \n"              // ss.
                  " movl $0x004FFFF0, %eax  \n"
                  " pushl %eax  \n"               // esp.
                  " pushl $0x3200  \n"            // eflags.
                  " pushl $0x1B  \n"              // cs.
                  " pushl $0x004A1000  \n"        // eip.
                  " iret \n" );
	};
	
	// Paranoia
    panic ("x86mainStartFirstThread: FAIL");
}


/*
 *************************************************
 * x86main: 
 *     The entry point for a C part of the Kernel.
 *
 * Function history:
 *     2015 - Created by Fred Nora.
 *     2016~2018 - Revision.
 *     ...
 */
 
int x86main ( int argc, char *argv[] ){
	
    int Status = 0;
    int zIndex;
	
	//
	// serial debug
	//
	
	init_serial(COM1_PORT);

	debug_print("x86main:\n");
	
    KernelStatus = KERNEL_NULL;

    //Initializing the global spinlock.
    __spinlock_ipc = 1;

    // #test.
    // initializing zorder list.
	// isso não deve ficar aqui.
    
    for ( zIndex = 0; zIndex < ZORDER_COUNT_MAX; zIndex++ ){
        zorderList[zIndex] = (unsigned long) 0;
    }

    //initializing zorder counter.
    zorderCounter = 0;

    // #deletar
	// set system window procedure.
    SetProcedure ( (unsigned long) &system_procedure);

    //
    // ## Video support ##
    //
	
	
	// First of all.
    // ps: Boot loader is mapping the LFB.

//setupVideo:

    // @todo: 
    // Device screen sizes.

    //Set graphics mode or text mode using a flag.
    if ( SavedBootMode == 1 )
	{	
        g_useGUI = GUI_ON;
        VideoBlock.useGui = GUI_ON;
        //...
    }else{
        g_useGUI = GUI_OFF;
        VideoBlock.useGui = GUI_OFF;
        //...
    };
	
	
	//verbose mode do kernel.
    //initializes a new line when '\n' is found.
	stdio_verbosemode_flag = 1;
	
	

	//video.c 
	
    videoVideo ();
    videoInit ();
	
    // Init screen

#ifdef ENTRY_VERBOSE	
    //If we are using graphics mode.
    if (VideoBlock.useGui == GUI_ON)
	{
		debug_print("x86main: Using GUI\n");
        //printf("x86main: Using GUI\n");
    }
#endif

    //If we are using text mode.
    if (VideoBlock.useGui != GUI_ON)
	{
		debug_print("x86main: text mode\n");
		
        set_up_text_color(0x0F, 0x00);

        //g_current_vm = 0x800000;
        //Set cga video memory: 0x800000vir = 0xb8000fis.
        videoSetupCGAStartAddress(SCREEN_CGA_START); 

    //Debug.
#ifdef ENTRY_VERBOSE
        kclear(0);
        kprint("x86main: Debug" ,9 ,9 );
        printf("x86main: Text Mode\n");
#endif

        //
		// ## bug bug ##
		//
		
		// Text mode not supported.

		printf ("x86main: Text mode is the current mode. Its not supported.");
		//die ();
		while (1){
			asm ("hlt");
		}
    };

#ifdef ENTRY_VERBOSE
    debug_print("x86main: starting kernel ..\n");
	//printf("x86main: Starting kernel..\n");
    //refresh_screen(); 
#endif


     //
	 // #test
	 // Tentaremos inicializar a runtime aqui.
	 // para obtermos suporte ao texto o mais cedo possível.
	 
	 
        //
        // RUNTIME !
        //	

        //#bugbug:
        //Somente depois da inicialização da runtime é que temos suporte a mensagens,
        //mas queremos mensagens antes, antão vamos tentar antecipar a inicialização da runtime.		

#ifdef EXECVE_VERBOSE		
	    //printf("sm-sys-system-systemStartUp: Initializing Runtime..\n");
	  debug_print("x86main: Initializing runtime\n");
#endif	

        //sm/rt/runtime.c
		
	    Status = (int) KiInitRuntime ();
	    if ( Status != 0 )
		{
			debug_print("x86main: Runtime fail\n");
	        //panic("x86main error: Runtime\n");
	    }
	
	
	
	//#bugbug
	//depois que a runtime está inicializada, então ja temos mensagem,
	//pois temos os endereços virtuais dos buffers.
	//Mas nossa inicialização está apresentando algum problema no Y,
	//que se corrige apenas no momento do logon.
	
    //printf("x86main: RUNTIME OK..\n");
    //refresh_screen(); 
    //while(1){}
//initializeSystem:

    //
	// ## system ##
	//
	
	//#importante
	//#obs: É durante essa rotina que começamos a ter mensagens.	

    systemSystem ();	
    Status = (int) systemInit ();
	
    if ( Status != 0 )
	{
		debug_print("x86main: systemInit fail\n");
        printf("x86main: systemInit fail\n");
        KernelStatus = KERNEL_ABORTED;
        goto fail;
    }
	
	//Ok
	//printf("#breakpoint after systemInit");
    //refresh_screen(); 
    //while(1){}	
	
	debug_print("x86main: processes and threads\n");
	
	//  ## Processes ##

    //=================================================
    // processes and threads initialization.
    // Creating processes and threads.
    // The processes are: Kernel, Idle, Shell, Taskman.
    // ps: The images are loaded in the memory.

//createProcesses:	

    // Creating Kernel process. PID=0.
    KernelProcess = (void *) create_process( NULL, // Window station.
	                                         NULL, // Desktop.
											 NULL, // Window.
											 (unsigned long) 0xC0000000,  // base address. 
                                             PRIORITY_HIGH,               // Priority.
											 (int) 0,                     // ppid.
											 "KERNEL-PROCESS",            // Name.
											 RING0,                       // iopl. 
											 (unsigned long ) gKernelPageDirectoryAddress ); // Page directory.	
    if( (void *) KernelProcess == NULL )
	{
        panic ("x86main: KernelProcess\n");

    }else{
 
        processor->CurrentProcess = (void *) KernelProcess;
        processor->NextProcess = (void *) KernelProcess;
		
		fs_initialize_process_pwd ( KernelProcess->pid, "no-directory" ); 
		
        //...
    };
	
	
	//Cria um diretório que é clone do diretório do kernel base 
	//e retorna o endereço físico desse novo diretório.
	//gInitPageDirectoryAddress = (unsigned long) CreatePageDirectory();
		
    //Creating init process.
	//UPROCESS_IMAGE_BASE;
    InitProcess = (void *) create_process ( NULL, NULL, NULL, 
										  (unsigned long) 0x00400000, 
                                          PRIORITY_HIGH, 
										  (int) KernelProcess->pid, 
										  "INITPROCESS", 
										  RING3, 
										  (unsigned long ) CreatePageDirectory () ); 	
    if ( (void *) InitProcess == NULL )
	{
        panic ("x86main: InitProcess\n");

    }else{
		
		fs_initialize_process_pwd ( InitProcess->pid, "no-directory" );
		
        //processor->IdleProcess = (void*) IdleProcess;	
    };
	
    //====================================================
    //Create Idle Thread. tid=0. ppid=0.
    IdleThread = (void *) KiCreateIdle ();
    if ( (void *) IdleThread == NULL )
	{
        panic ("x86main: IdleThread\n");

    }else{

        //IdleThread->ownerPID = (int) InitProcess->pid;

        //#importante
		//Thread.
        processor->CurrentThread = (void *) IdleThread;
        processor->NextThread    = (void *) IdleThread;
        processor->IdleThread    = (void *) IdleThread;
        //...
    };	
	
	InitProcess->Heap = (unsigned long) g_gramadocore_init_heap_va;
	InitProcess->control = IdleThread;
		
	//registra um dos servidores do gramado core.
	//server_index, process, thread
	ipccore_register ( (int) 0, (struct process_d *) InitProcess, (struct thread_d *) IdleThread );


	// #importante
	// Daqui pra baixo temos a opção de criarmos ou não os processos
	// e as threads. A configuração está em config.h

#ifdef ENTRY_CREATE_SHELL

    //Creating Shell process.
    ShellProcess = (void *) create_process ( NULL, NULL, NULL, 
										   (unsigned long) 0x00450000, 
                                           PRIORITY_HIGH, 
										   (int) KernelProcess->pid, 
										   "SHELLPROCESS", 
										   RING3, 
										   (unsigned long )  CreatePageDirectory () );
    if((void *) ShellProcess == NULL){
        panic ("x86main: ShellProcess\n");

    }else{
		
		fs_initialize_process_pwd ( ShellProcess->pid, current_workingdiretory_string );
		
        //...
    };
		
    //=============================================
    // Create shell Thread. tid=1. 
    ShellThread = (void *) KiCreateShell();
    if( (void *) ShellThread == NULL )
	{
        panic ("x86main: ShellThread\n");

    }else{

        //ShellThread->ownerPID = (int) ShellProcess->pid;
        //...
    };	
	
	ShellProcess->Heap = (unsigned long) g_gramadocore_shell_heap_va;
	ShellProcess->control = ShellThread; 
		
	//registra um dos servidores do gramado core.
	//server_index, process, thread
	ipccore_register ( (int) 1, (struct process_d *) ShellProcess, (struct thread_d *) ShellThread );
	
#endif	



#ifdef ENTRY_CREATE_TASKMAN
	
    //Creating Taskman process. 
    TaskManProcess = (void *) create_process( NULL, 
	                                         NULL, 
											 NULL, 
											 (unsigned long) 0x004A0000, 
                                             PRIORITY_LOW, 
											 KernelProcess->pid, 
											 "TASKMANPROCESS", 
											 RING3, 
											 (unsigned long )  CreatePageDirectory () ); 	
    if ( (void *) TaskManProcess == NULL ){
		
        panic ("x86main: TaskManProcess\n");
		
    }else{
		
		fs_initialize_process_pwd ( TaskManProcess->pid, "no-directory" );
		
        //...
    };
	
    //===================================
    //Create taskman Thread. tid=2.   
	
	TaskManThread = (void *) KiCreateTaskManager();
    	
	if( (void *) TaskManThread == NULL )
	{
        panic ("x86main: TaskManThread\n");

    }else{

        //TaskManThread->ownerPID = (int) TaskManProcess->pid;
        //...
    };
	
	TaskManProcess->Heap = (unsigned long) g_gramadocore_taskman_heap_va;
	TaskManProcess->control = TaskManThread;
		
	//registra um dos servidores do gramado core.
	//server_index, process, thread
	ipccore_register ( (int) 2, (struct process_d *) TaskManProcess, (struct thread_d *) TaskManThread );
	
#endif	



#ifdef ENTRY_CREATE_KERNELTHREAD_RING0
	
    //===================================
    // Cria uma thread em ring 0.
	// Ok. isso funcionou bem.
    
	// >>>>> Como essa thread pertence ao processo kernel, então mudaremos ela 
	// um pouco pra cima, onde criamos o processo kernel.
	// obs: Mesmo não sendo ela o primeiro TID.
	
	RING0IDLEThread = (void *) KiCreateRing0Idle ();
	
    if( (void *) RING0IDLEThread == NULL )
	{
        panic ("x86main: RING0IDLEThread\n");

    }else{

        //RING0IDLEThread->ownerPID =  (int) KernelProcess->pid; 
        //...
    };
	
#endif		


//testando carregar uma segunda thread no mesmo endereço virtual.
//dessa forma mais de uma thread rodará no mesmo endeereço virtual,
//mas em processos diferentes.
#ifdef ENTRY_CREATE_THREAD_400000
  //#bugbug:
  //Me parece que esse rotina afeta o funcionamento 
  //do mecanismo improvisado de execve dentro do gramado core 
  //usando o processo init.
  //Suspenderemos isso e tentaremos outra abordagem. :(
/*
    //#ok funcionou. :)
	//Que vários processo tenham threads em 0x400000
	//Ok a thread foi criada,
	//para ela rodar nessa fase de inicialização 
	//precisamos deixa-la no mesmo estado que as outras.
	//Nesse teste estamos usando um mesmo programa já 
	//carregado por outro processo.
	
    struct thread_d *xxx;
	xxx = (void *) create_thread( 
			                NULL,                        // w. station 
							NULL,                        // desktop
							NULL,                        // w.
							IdleThread->eip,             // init eip
							IdleThread->esp,             // init stack
							TaskManProcess->pid,         // pid (determinado)(provisório).
							(char *) "XXX-thread" );     // name	
							
							
    queue_insert_data ( queue, (unsigned long) xxx, QUEUE_INITIALIZED);
    SelectForExecution (xxx);    // * MOVEMENT 1 (Initialized --> Standby).
*/	
#endif	

    //
	//===============================================
	//
	
	//
	//==============================================
	// ## importante ## 
	// Temos aqui alguma configuração.
	//
	
	next_thread = 0;
	
	// #importante: 
	// Essa não pode fechar nunca.
	// idle thread ... 
	//idle = 3;
	idle = 0;
    
	
	//...


//Kernel base Debugger.
//doDebug:

#ifdef  ENTRY_DEBUG_CHECK_VALIDATIONS

    Status = (int) debug ();
    
	if ( Status != 0 )
	{    
        printf("x86main: debug\n");
		KernelStatus = KERNEL_ABORTED;
        goto fail;
    }else{
        KernelStatus = KERNEL_INITIALIZED;
    };
	
#endif		

   
//    ====================== ## TESTS ## =============================
// begin - We can make some tests here.

	
    //Inicializando as variáveis do cursor piscante do terminal.
    //isso é um teste.
    timer_cursor_used = 0;   //desabilitado.
    timer_cursor_status = 0;


 
	
//doTests:
   //...
	
    // Initializing ps/2 controller.
	//ldisc.c
	debug_print("x86main: ps2\n");    
	ps2();
	
	
 
    //
    // Loading file tests.
    //


   // void *b;


   /*
    //===================================
    // @todo: loads a bmp.
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
	
	/*
	
	// TESTANDO SALVAR UM ARQUIVO ...
    //?? stdin ??
	
	char file_1[] = "Isso é um arquivo de teste ..... \n testando salvar um arquivo!:)";
	
	char file_name[] = "savetest.txt";
	write_fntos( (char *) file_name );
	

    //
    //  ## Save ##
    //
	
	fsSaveFile( file_name,  // Nome. 
	            3,          // Quantidade de setores.
				255,        // Tamanho do arquivo dado em bytes.     
				file_1,     // Buffer onde está o arquivo.
				0x20 );     // Tipo de entrada. 0x20=arquivo.
				
				
	*/
	
    
	//Isso funcionou, não mudar de lugar.
	//Mas isso faz parte da interface gráfica,
	//Só que somente nesse momento temos recursos 
	//suficientes para essa rotina funcionar.
	
	windowLoadGramadoIcons ();
	

	// ## Testando font NelsonCole2 ##
    // #todo: Isso pode ficar no mo'dulo gws?
	gwsInstallFont("NC2     FON");
	//gwsInstallFont("NC2     FON");
	
	
	//
	// ## testando suporte a salvamento de retângulo ##
	//
	
	//#debug
	//printf ("testando salvamento de retangulo\n");
	//refresh_screen();
	
	//isso funcionou ...
	//initialize_saved_rect ();
	
	//testando salvar um retângulo ...
	//save_rect ( 0, 0, 100, 100 );
	
	//copiando aqui no backbuffer
	//show_saved_rect ( 20, 20, 100, 100 );
	
	//
	// ## servidor taskman ##
	//
	
	// ## Criando a janela do servidor taskman ## 
	// usada para comunicação.
	
	gui->taskmanWindow = (void *) CreateWindow ( 1, 0, VIEW_MINIMIZED, 
	                                "taskman-server-window", 
	                                1, 1, 1, 1,           
							        gui->main, 0, 0, COLOR_WINDOW  ); 
								 
	if ( (void *) gui->taskmanWindow == NULL )
	{
		printf("x86main: falaha ao criar a janela do servidor taskman\n");
		die();
	
	} else {
		
		//inicializando a primeira mensagem
		////envia uma mensagem de teste para o servidor taskman
	    gui->taskmanWindow->msg_window = NULL;
		gui->taskmanWindow->msg = 0; //temos uma mensagem.
		gui->taskmanWindow->long1 = 0;
		gui->taskmanWindow->long2 = 0;
        gui->taskmanWindow->newmessageFlag = 0;		
		
	    //gui->taskmanWindow->msg_window = NULL;
		//gui->taskmanWindow->msg = 123; //temos uma mensagem.
		//gui->taskmanWindow->long1 = 0;
		//gui->taskmanWindow->long2 = 0;
        //gui->taskmanWindow->newmessageFlag = 1;		
		
	};
	
	//#debug
	//extern unsigned long code_begin;
	//extern unsigned long code_end;
	//extern unsigned long data_begin;
	//extern unsigned long data_end;
	//extern unsigned long bss_begin;
	//extern unsigned long bss_end;
	
	//printf("\n");
	//printf("\n");
	//printf("#debug\n");
	//printf("======\n");
	
	//printf("\n");
	//printf("code_begin={%x}\n", &code_begin );
	//printf("  code_end={%x}\n", &code_end );

	//printf("\n");
	//printf("data_begin={%x}\n", &data_begin );
	//printf("  data_end={%x}\n", &data_end );

	//printf("\n");
	//printf(" bss_begin={%x}\n", &bss_begin );
	//printf("   bss_end={%x}\n", &bss_end );
	
	//printf("\n");
	//refresh_screen();
	//die();
	
	
	
	// ## testando ctype ##
    //ok ... isso funcionou.
	
   /*	
   int var1 = 'h';
   int var2 = '2';
    
   if( isdigit(var1) ) {
      printf("var1 = |%c| is a digit\n", var1 );
   } else {
      printf("var1 = |%c| is not a digit\n", var1 );
   }
   
   if( isdigit(var2) ) {
      printf("var2 = |%c| is a digit\n", var2 );
   } else {
      printf("var2 = |%c| is not a digit\n", var2 );
   }
	
	//#debug
	refresh_screen();
	while(1){}
	*/
	
	
//    ====================== ## TESTS ## =============================
// #end.	
	
	
#ifdef BREAKPOINT_TARGET_AFTER_ENTRY
    //#debug 
	//a primeira mensagem só aparece após a inicialização da runtime.
	//por isso não deu pra limpar a tela antes.
	printf(">>>debug hang: after entry");
	refresh_screen(); 
	while (1){
		asm ("hlt");
	}
#endif	
	
	
	//
    // done !
    //

done:

    debug_print("x86main: done\n");

    // Return to assembly file, (head.s).
    if ( KernelStatus == KERNEL_INITIALIZED )
	{

#ifdef KERNEL_VERBOSE
    refresh_screen();
#endif


// Isso só executa o INIT se ele foi criado.        
#ifdef ENTRY_INITIALIZE_INIT
		printf("x86main: Initializing INIT ..\n");
		x86mainStartFirstThread (1);
		//startStartIdle() ;
		goto fail;
#endif		
		
// Isso só executa o SHELL se ele foi criado.
#ifdef ENTRY_INITIALIZE_SHELL 
        printf("x86main: Initializing SHELL ..\n");
		x86mainStartFirstThread (2);
	    goto fail;
#endif

// Isso só executa o TASKMAN se ele foi criado.
#ifdef ENTRY_INITIALIZE_TASKMAN
    printf("x86main: Initializing TASKMAN ..\n");
	x86mainStartFirstThread (3);	
	goto fail;
#endif

        printf("x86main: No idle thread selected.\n");
	    goto fail;	
    };

fail:
    printf("x86main: EXIT_FAILURE \n");
	refresh_screen();
    return (int) EXIT_FAILURE;
}


//
// End.
//


