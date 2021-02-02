/*
 * File: info.c
 *
 *     System info routines.
 *
 * History:
 *     2015 - Created by Fred Nora.
 */


#include <kernel.h>


//Usados para mostrar informa��es sobre a localiza��o 
//das partes da imagem do kernel.
//#todo: deletar;
/*
extern unsigned long kernel_begin;
extern unsigned long kernel_end;
extern unsigned long code_begin;
extern unsigned long code_end;
extern unsigned long data_begin;
extern unsigned long data_end;
extern unsigned long bss_begin;
extern unsigned long bss_end;
*/



/*
 *********************************************************
 * KiInformation: 
 * Mostra uma lista de informa��es sobre o Sistema.
 * Obs: @todo: A lista de informa��es de ser bem completa, 
 * pois servir� de ajuda ao desenvolvedor. Deve conter 
 * de tudo, abordando todas as camadas do sistema. 
 * 
 * Ordem por classe:
 * ================
 * RAM: ram, sm, uigm, uitm.
 * IO: cpu, dma.
 * DEVICES: umblocked, blocked
 * THINGS:
 *
 * Obs: As inform��es podem ser salvas em um arquivo de sa�da padr�o.
 */

//void infoShowKernelInfo() 


void KiInformation (void)
{

    // The current mode.
    // This is not the product name.

    printf ("\n");
    
    switch (current_mode){

        case GRAMADO_JAIL:
            printf ("GRAMADO_JAIL: Good for games.\n");
            break;
            
        case GRAMADO_P1:
            printf ("GRAMADO_P1: Good for applications.\n");
            break;
            
        case GRAMADO_HOME:
            printf ("GRAMADO_HOME: Good for applications.\n");
            break;
            
        case GRAMADO_P2:
            printf ("GRAMADO_P2: Good for applications.\n");
            break;
            
        case GRAMADO_CASTLE:
            printf ("GRAMADO_CASTLE: Good for database.\n");
            break;
        
        //case GRAMADO_CALIFORNIA:
        // ...
        default:
            printf ("INFO: mode={%d} current_mode not defined!\n", current_mode);
            goto fail;
            break;
    };

    // Timing
    printf ("\n");
    printf ("seconds %d | jiffies %d | %d HZ | sys time %d ms  \n", 
        seconds,
        jiffies, 
        sys_time_hz, 
        sys_time_ms );


	//
	// ## User ##
	//
	
	//Group and user.
    printf ("User Info: Group={%d} User={%d}\n", 
        current_group, current_user );

	//user session, room (window station), desktop.
    printf ("UserSession={%d} Room={%d} Desktop={%d}\n",
        current_usersession, current_room, current_desktop );

	// #bugbug: 
	// Rever isso.

    ShowUserInfo(0);  

    //
    // Status 
    //
    
    // Status do mecanismo de task switch.
    switch ( task_switch_status ){
    case LOCKED:    printf("Task switch LOCKED\n");    break; 
    case UNLOCKED:  printf("Task switch UNLOCKED\n");  break; 
    };

    // Status do Scheduler.
    switch ( g_scheduler_status ){
    case LOCKED:    printf("Scheduler LOCKED\n");    break; 
    case UNLOCKED:  printf("Scheduler UNLOCKED\n");  break; 
    };

	//
	// Process and thread
	//

    printf ("\n");
    printf ("[Process Info]\n");

	//Current process and current thread.
    printf ("CurrentProcess={%d} CurrentThread={%d}\n", 
        current_process, current_thread );

    printf ("\n");
    printf ("[Thread Info]\n");

    printf ("Number of threads %d\n\n", 
        UPProcessorBlock.threads_counter );

    // See: thread.c
    show_thread_information ();

    // Dispatch criteria
    // Show how many times a dispatch criteria was used by
    // the dispatcher.

    printf ("\n");
    printf ("[Dispatch criteria]\n");
    printf ("cIdle={%d} cInit={%d} cNext={%d} cCur={%d} "
            "cAny={%d} cIdeal={%d} cDisp={%d}\n\n",
        DispatchCountBlock->SelectIdleCount,
        DispatchCountBlock->SelectInitializedCount,
        DispatchCountBlock->SelectNextCount,
        DispatchCountBlock->SelectCurrentCount,
        DispatchCountBlock->SelectAnyCount,
        DispatchCountBlock->SelectIdealCount,
        DispatchCountBlock->SelectDispatcherQueueCount );



	//
	// ## Heap and Stack ##
	//

    //Obs: Estou revendo isso.
	//printf("\n[Kernel Heap and Stack info:]\n");
	//printf("HEAP: Start={%x} | End={%x} | Total={%d KB} \n",
	//    kernel_heap_start ,kernel_heap_end ,HeapTotal);	
    //printf("AvailableHeap={%d KB}\n",g_available_heap/1024);
	    
	//@todo:
	//mostrar o tamanho da pilha..
	//#bugbug: A informa��es sobre a stack est�o incorretas, 
	//pois essas vari�veis mostram 
	// o endere�o da stack na hora da inicializa��o. 
	//Quando o processador retorna de ring3 para ring0
	//ele usa o endere�o de pilha indicado na TSS.
	//Pois bem, � mais digno mostrar aqui o endere�o da pilha, 
	//indicado no TSS.
	//printf("STACK: Start={%x} | End={%x} | Total={%d KB} \n",
	//    kernel_stack_start ,kernel_stack_end ,StackTotal);
    //printf("STACK: StartPhysicalAddress={%x} \n",kernel_stack_start_pa);
	
	//
	// ## Video ##
	//
	
	//printf("\n[Video Info:]\n");
	
	//Video mode.
	//printf("The video option is %x \n",g_video_mode);
	//printf("FrontbufferPA={%x} FrontbufferVA={%x} BackbufferVA={%x} \n",
	//    g_frontbuffer_pa ,g_frontbuffer_va ,g_backbuffer_va);


    //
    //  ## Memory ##
    //

    memoryShowMemoryInfo();

    // Nothing. 
    goto done;
    
    // ==========================

fail:
    printf ("Fail\n");
done:
    // Resolution
    printf ("\n");
    printf ("Screen Resolution: W=%d H=%d BPP=%d \n",
        g_device_screen_width, 
        g_device_screen_height, 
        g_device_screen_bpp );

    refresh_screen();
    return;
}


// ================================================
// The data comes from boot block and beyond.

// #test
// Lets use the info that omes from the BootBlock structure.
// This structure was initialized for kernel_main() in main.c

unsigned long info_get_boot_info ( int i )
{

    if (i<0){  return 0;  }

    switch (i){

        // #bugbug
        // If we use the BootBlock structure, maybe the info
        // will be accessible only using the sci2. int 0x82.

        case 1:
           return (unsigned long) BootBlock.last_valid_address;
           break;

        case 2:
           return (unsigned long) BootBlock.metafile_address;
           break;

        case 3:
           return (unsigned long) BootBlock.disk_number;
           break;

        case 4:
           return (unsigned long) BootBlock.heads;
           break;

        case 5:
           return (unsigned long) BootBlock.spt;
           break;

        case 6:
           return (unsigned long) BootBlock.cylinders;
           break;

        case 7:
           //return (unsigned long) 
           break;

        case 9:
           //return (unsigned long) 
           break;
    };
    
   //fail 
   return 0;
}


//
// End.
//

