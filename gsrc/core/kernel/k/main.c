/*
 * Gramado Operating System - The main file for the kernel.
 * (c) Copyright 2015~2018 - Fred Nora.
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
 *     2015      - Created by Fred Nora.
 *     2016~2018 - Revision.
 *     //... 
 */ 
#include <kernel.h>

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


extern unsigned long SavedBootMode;

extern void turn_task_switch_on();


char copyright[] =
"Copyright (c) 2005-2018\n\tFred Nora.  All rights reserved.\n\n";

/* BSD quote: Components of the first process. */


/*
 *************************************************
 * kMain: 
 *     The entry point for a C part of the Kernel.
 *
 * Function history:
 *     2015 - Created by Fred Nora.
 *     2016~2018 - Revision.
 *     ...
 */
int kMain(int argc, char* argv[])
{
    int Status = 0;

    KernelStatus = KERNEL_NULL;

    //Initializing the global spinlock.
    __ipc_kernel_spinlock = 1;

    // #test.
    // initializing zorder list.
    int zIndex;
    for( zIndex = 0; zIndex < ZORDER_COUNT_MAX; zIndex++ ){
        zorderList[zIndex] = (unsigned long) 0;
    }

    //initializing zorder counter.
    zorderCounter = 0;

    // set system window procedure.
    SetProcedure( (unsigned long) &system_procedure);


    //
    // Video.
    // First of all.
    // ps: Boot loader is mapping the LFB.
    //

//setupVideo:

    // @todo: 
    // Device screen sizes.

    //Set graphics mode or text mode using a flag.
    if(SavedBootMode == 1){
        g_useGUI = GUI_ON;
        VideoBlock.useGui = GUI_ON;
        //...
    }else{
        g_useGUI = GUI_OFF;
        VideoBlock.useGui = GUI_OFF;
        //...
    };
	
	
	//verbose mode do kernel.
	//permite que a tela do kernel funcione igual a um 
	//terminal, imprimindo os printfs um abaixo do outro.
	//sempre reiniciando x.	
	stdio_verbosemode_flag = 1;

    videoVideo();
    videoInit();
	
	



    //
    // Init screen
    //

    //If we are using graphics mode.
    if(VideoBlock.useGui == GUI_ON){
#ifdef KERNEL_VERBOSE
        printf("kMain: Using GUI!\n");
#endif
    };

    //If we are using text mode.
    if(VideoBlock.useGui != GUI_ON){
        set_up_text_color(0x0F, 0x00);

        //g_current_vm = 0x800000;
        //Set cga video memory: 0x800000vir = 0xb8000fis.
        videoSetupCGAStartAddress(SCREEN_CGA_START); 

    //Debug.
#ifdef KERNEL_VERBOSE
        kclear(0);
        kprint("kMain: Debug" ,9 ,9 );
        printf("kMain: Text Mode!\n");
#endif
    };

#ifdef KERNEL_VERBOSE
    printf("kMain: Starting kernel...\n");
    refresh_screen(); 
#endif

//initializeSystem:

    systemSystem();	
    Status = (int) systemInit();
    if(Status != 0){
        printf("main-kMain: systemInit\n");
        KernelStatus = KERNEL_ABORTED;
        goto fail;
    };

    //
    //=================================================
    // processes and threads initialization.
    // Creating processes and threads.
    // The processes are: Kernel, Idle, Shell, Taskman.
    // ps: The images are loaded in the memory.
    //

//createProcesses:

    // Creating Kernel process. PID=0.
	// #importante: Obs: Nesse caso o kernel base também tem um processo,
	// mas ele não é escalonado como os outros processos. O kernel base 
	// possui uma estrutura de processo somente para efeito de organização 
	// e compartilhamento de recursos.
    // Cuidado para não corromper as informações que o processo precisa.
    // #bugbug: A estrutura do processo kernel não é inicializada corretamente
    // pois alguns valores são determinados e não pertencem ao processo kernel.
    // Obs: Por enquanto está bom, pois estamos criando aumaticamente o processo 
	// do mesmo jeito que criamos os outros processos.
	//
    KernelProcess = (void*) create_process( NULL, // Window station.
	                                        NULL, // Desktop.
											NULL, // Window.
											(unsigned long) 0xC0001000,  // Entry point. 
                                            PRIORITY_HIGH,               // Priority.
											(int) 0,                     // ppid.
											"KERNEL-PROCESS",            // Name.
											RING0,                       // iopl. 
											(unsigned long ) KERNEL_PAGEDIRECTORY ); // Page directory.	
    if( (void*) KernelProcess == NULL )
	{
        printf("main-kMain: KernelProcess\n");
        die();
    }else{

        //configurando o processador.
        //#bugbug; Não sabemos se essa estrutura está inicializada.
        processor->CurrentProcess = (void*) KernelProcess;
        processor->NextProcess    = (void*) KernelProcess;
        //...
    };


    //Creating Idle process.
    InitProcess = (void*) create_process( NULL, 
	                                      NULL, 
										  NULL, 
										  (unsigned long) 0x00401000, 
                                          PRIORITY_HIGH, 
										  (int) KernelProcess->pid, 
										  "IDLEPROCESS", 
										  RING3, 
										  (unsigned long ) KERNEL_PAGEDIRECTORY );	
    if((void*) InitProcess == NULL)
	{
        printf("main-kMain: InitProcess\n");
        die();
    }else{
        //processor->IdleProcess = (void*) IdleProcess;	
    };

    //Creating Shell process.
    ShellProcess = (void*) create_process( NULL, 
	                                       NULL, 
										   NULL, 
										   (unsigned long) 0x00401000, 
                                           PRIORITY_HIGH, 
										   (int) KernelProcess->pid, 
										   "SHELLPROCESS", 
										   RING3, 
										   (unsigned long ) KERNEL_PAGEDIRECTORY );	
    if((void*) ShellProcess == NULL){
        printf("main-kMain: ShellProcess\n");
        die();
    }else{
        //...
    };


    //Creating Taskman process. 
    TaskManProcess = (void*) create_process( NULL, 
	                                         NULL, 
											 NULL, 
											 (unsigned long) 0x00401000, 
                                             PRIORITY_LOW, 
											 KernelProcess->pid, 
											 "TASKMANPROCESS", 
											 RING3, 
											 (unsigned long ) KERNEL_PAGEDIRECTORY);	
    if((void*) TaskManProcess == NULL){
        printf("main-kMain: TaskManProcess\n");
        die();
    }else{
        //...
    };


    //
    // *** NÃO HÁ PROBLEMA EM CRIAR MANUALMENTE AS 
	//     PRIMEIRAS THREADS DO SISTEMA ***
    //


    //
    // Creating threads. 
    // The threads are: Idle, Shell, Taskman.
    // The Idle thread belong to Idle process.
    // The Shell thread belongs to Shell process.
    // The Taskman thread belongs to Taskman process.
    //

//createThreads:

    //====================================================
    //Create Idle Thread. tid=0. ppid=0.
    IdleThread = (void*) KiCreateIdle();
    if( (void*) IdleThread == NULL )
	{
        printf("main-kMain: IdleThread\n");
        die();
    }else{

        IdleThread->ownerPID = (int) InitProcess->pid;

        //Thread.
        processor->CurrentThread = (void*) IdleThread;
        processor->NextThread    = (void*) IdleThread;
        processor->IdleThread    = (void*) IdleThread;
        //...
    };


    //=============================================
    // Create shell Thread. tid=1. 
    ShellThread = (void*) KiCreateShell();
    if( (void*) ShellThread == NULL )
	{
        printf("main-kMain: ShellThread\n");
        die();
    }else{

        ShellThread->ownerPID = (int) ShellProcess->pid;
        //...
    };

    //===================================
    //Create taskman Thread. tid=2.
    TaskManThread = (void*) KiCreateTaskManager();
    if( (void*) TaskManThread == NULL )
	{
        printf("main-kMain: TaskManThread\n");
        die();
    }else{

        TaskManThread->ownerPID = (int) TaskManProcess->pid;
        //...
    };

    //...


//Kernel base Debugger.
doDebug:
    Status = (int) debug();
    if(Status != 0){    
        MessageBox(gui->screen,1,"main-kMain","debug");
        KernelStatus = KERNEL_ABORTED;
        goto fail;
    }else{
        KernelStatus = KERNEL_INITIALIZED;
    };


    //
    // TESTS:
    // We can make some testes here.
    //


    //Inicializando as variáveis do cursor piscante do terminal.
    //isso é um teste.
    timer_cursor_used = 0;   //desabilitado.
    timer_cursor_status = 0;


//doTests:
   //...

 
	
    // Initializing ps/2 controller.
	//unblocked/ldisc.c
    ps2();
	
	
	//
	// IN:
	//    FORCEPIO = Força o driver a funcionar no modo pio.
	//    0 = Dá ao driver a chance de funcionar em modo DMA.
	//    Como o DMA anda não funciona, podemos ir usando ele 
	// no modo PIO.
	//
	ata_initialize(FORCEPIO);




    //
    // Loading file tests.
    //


   // void *b;


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

done:

    // Return to assembly file, (head.s).
    if(KernelStatus == KERNEL_INITIALIZED){

#ifdef KERNEL_VERBOSE
    refresh_screen();
#endif

        //This function do not return.
        startStartIdle() ;
    };

fail:
    MessageBox(gui->screen,1,"main-kMain","EXIT_FAILURE");
    refresh_screen();
    return (int) EXIT_FAILURE;
};


static inline void mainSetCr3( unsigned long value){
    __asm__ ( "mov %0, %%cr3" : : "r"(value) );
}


/*
 * startStartIdle:
 *     Inicia a thead idle.
 *
 *     @todo: 
 *         + Iniciar o processo da idle.
 *         + Detectar se o aplicativo está carregado na memória 
 *           antes de passar o comando pra ele via iret.
 *           Mudar para startIdleThread().
 *
 */
void startStartIdle() 
{
    int i;
 
    if((void*) IdleThread == NULL)
    {
        //printf("KeStartIdle error: Struct!\n");
        MessageBox(gui->screen,1,"main-startStartIdle","IdleThread");
        die();
    }else{

        //Checar se o programa já foi inicializado antes. 
        //Ele não pode estar.
        if(IdleThread->saved != 0){
            printf("main-startStartIdle: saved\n");
            die();
        };

        //Checar se o slot na estrutura de tarefas é válido.
        if(IdleThread->used != 1 || IdleThread->magic != 1234){
            printf("main-startStartIdle: tid={%d} magic \n", IdleThread->tid);
            die();
        };

        set_current(IdleThread->tid);      //Seta a thread atual.
        //...
    };

    // State ~ Checa o estado da tarefa.
    if(IdleThread->state != STANDBY){
        printf("main-startStartIdle: state tid={%d}\n",IdleThread->tid);
        die();
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


    //Set cr2 and flush TLB.
    mainSetCr3( (unsigned long) IdleThread->Directory);
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


    //
    //#importante;
    // Os valores aqui devem vir da estrutura da thread idle e não 
    // serem determinados.
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

    panic("main-startStartIdle: panic *");
};


//
// End.
//


