/*
 * Gramado Kernel - The main file for the kernel.
 * (c) Copyright 2015-2016 Fred Nora.
 *
 * File: k\main.c 
 * 
 * Description:
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
	_lockfocus = 0;

	//
	// Window procedure.
	//
	
	SetProcedure( (unsigned long) &system_procedure);
	
	
	//
	// Video.
	//
	
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

	videoInit();  //Setup video first of all.	   
	

	//
	// Init screen
	//
	
	//If we are using graphic mode.
	if(VideoBlock.useGui == GUI_ON){
		//kbackground(COLOR_BLUE);
	    printf("kMain: Using GUI!\n");	
        //drawDataRectangle( 20, 20, 20, 20, COLOR_RED);       	
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
	printf("kMain: Starting up system..\n");
	refresh_screen();
	//while(1){}	

	//Debug
	//while(1){}
	
	//
    // System initialization..
    //
    
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
	// Creating processes and threads.
	// The processes are: Kernel, Idle, Shell, Taskman.
	//
	
	// Creating Kenrel process. PID=0.	
	// @todo: Change the name to KiCreateKernelProcess.
	KernelProcess = (void*) KeCreateKernelProcess();	
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
	IdleProcess = (void*) create_process( NULL, NULL, NULL, (unsigned long) 0x00401000, 
	                                      PRIORITY_HIGH, (int) KernelProcess->pid, "IDLEPROCESS");	
	if((void*) IdleProcess == NULL){
		printf("kMain error: Create Idle process.\n");
		refresh_screen();
		while(1){};
	};
    //processor->IdleProcess = (void*) IdleProcess;	
	
    //Creating Shell process.
	ShellProcess = (void*) create_process( NULL, NULL, NULL, (unsigned long) 0x00401000, 
	                                       PRIORITY_HIGH, (int) KernelProcess->pid, "SHELLPROCESS");	
	if((void*) ShellProcess == NULL){
		printf("kMain error: Create shell process.\n");
		refresh_screen();
		while(1){};
	};	

	//Creating Taskman process.
	TaskManProcess = (void*) create_process( NULL, NULL, NULL, (unsigned long) 0x00401000, 
	                                         PRIORITY_LOW, 0, "TASKMANPROCESS");	
	if((void*) TaskManProcess == NULL){
		printf("kMain error: Create taskman process.\n");
		refresh_screen();
		while(1){};
	};		
	
	//
	// Creating threads. 
	// The threads are: Idle, Shell, Taskman.
	// The Idle thread belong to Idle process.
	// The Shell thread belongs to Shell process.
	// The Taskman thread belongs to Taskman process.
	//
	
	//Create Idle Thread. tid=0. ppid=0.
	IdleThread = (void*) KeCreateIdle();	
	if( (void*) IdleThread == NULL )
	{
	    printf("kMain error: Create Idle Thread!");
		refresh_screen();
		while(1){}
	}else{
	    
        IdleThread->ppid = (int) IdleProcess->pid;  //PPID.    
		
		//Thread.
	    processor->CurrentThread = (void*) IdleThread;
        processor->NextThread    = (void*) IdleThread;
        processor->IdleThread    = (void*) IdleThread;		
		//...		
    };
	
	// Create shell Thread. tid=1. 
	ShellThread = (void*) KeCreateShell();	
	if( (void*) ShellThread == NULL ){
	    printf("kMain error: Create Shell Thread!");
		refresh_screen();
		while(1){}
	}else{
		
	    ShellThread->ppid = (int) ShellProcess->pid;  //PPID.
		//...		
    };
	
	//Create taskman Thread. tid=2. 
	TaskManThread = (void*) KeCreateTaskManager();
	if( (void*) TaskManThread == NULL ){
	    printf("kMain error: Create TaskMan Thread!");
		refresh_screen();
		while(1){}
	}else{
		
	    TaskManThread->ppid = (int) TaskManProcess->pid; //PPID.		
		//...		
    };	
	
 
    //
	// Debug.
	//
	
done:
	
	//Debug.
	//if(VideoBlock.useGui != 1){	
	//    kclear(0);
    //    kprintf("kMain: Done" ,10 ,9 );
    //};
	
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

    //...	
	
	//
	// RETURNING !
	//
	
	//
	// Return to assembly file, (head.s).
	//
	
	if(KernelStatus == KERNEL_INITIALIZED){
        //@todo: if verbose??
		//printf("KeMain: EXIT_SUCCESS\n");
		refresh_screen();
		return (int) EXIT_SUCCESS;	
	};
	// Fail!
fail:
    //if(KernelStatus != KERNEL_INITIALIZED){...};	
	//printf("KeMain: EXIT_FAILURE\n");
	MessageBox(gui->screen,1,"kMain ERROR","Kernel main EXIT_FAILURE!");
	refresh_screen();  
	return (int) EXIT_FAILURE;   
};
 
//
// End.
//

