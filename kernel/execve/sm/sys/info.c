/*
 * File: info.c
 *
 * Descrição:
 *     Rotinas de informações sobre o sistema.
 *
 * History:
 *     2015 - Created by Fred Nora.
 *     2016 - Revision.
 */
 

#include <kernel.h>


//Usados para mostrar informações sobre a localização 
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
 * KeInformation: 
 *    @todo:
 *    Mostra em informações sobre o kernel.
 *    Chama módulo externo (Server em user mode) para
 *    mostrar informações sobre o kernel ou sobre o sistema.
 *
 *    Obs: 
 *    As informções podem ser salvas em um arquivo de saída padrão.
 */

void KeInformation (){
	
	//return;    //Ainda não implementada.
};


/*
 *********************************************************
 * KiInformation: 
 * Mostra uma lista de informações sobre o Sistema.
 * Obs: @todo: A lista de informações de ser bem completa, 
 * pois servirá de ajuda ao desenvolvedor. Deve conter 
 * de tudo, abordando todas as camadas do sistema. 
 * 
 * Ordem por classe:
 * ================
 * RAM: ram, sm, uigm, uitm.
 * IO: cpu, dma.
 * DEVICES: umblocked, blocked
 * THINGS:
 *
 * Obs: As informções podem ser salvas em um arquivo de saída padrão.
 */

//void infoShowKernelInfo() 

void KiInformation (){
	
	printf("\n");	
	
#ifdef IMPORTED_VARIABLES	
	//=======================================
	// #Warning                            //
	// Variables imported from Makefile    //
	//=======================================
	
	printf ("Gramado %d.%d.%d%s (%s)\n",
        GRAMADO_VERSION, 
        GRAMADO_PATCHLEVEL,
        GRAMADO_SUBLEVEL, 
        GRAMADO_EXTRAVERSION,
        GRAMAD0_NAME );	
#endif
	
	//screen 
	
	printf("Screen Resolution: W={%d} H={%d} \n",
	    g_device_screen_width, g_device_screen_height );
	
	//timing
	
	printf("%d Hz | sys time %d ms | ticks %d \n", 
	    sys_time_hz, sys_time_ms, sys_time_ticks_total );	
	
	//
	// ## User ##
	//
	
	//Group and user.
	printf("User Info: Group={%d} User={%d}\n", current_group, current_user );
	
	//user session, room (window station), desktop.
	printf("UserSession={%d} Room={%d} Desktop={%d}\n",
		current_usersession, current_room, current_desktop );
	
	//#bugbug Rever isso.
	ShowUserInfo(0);  
	

    // ## Status ##

	// Status do mecanismo de task switch.
	switch( task_switch_status )
	{
	    case LOCKED:
		    printf("Task switch is LOCKED\n");
			break; 
	    
		case UNLOCKED:
		    printf("Task switch is UNLOCKED\n");
		    break; 	
	};

	// Status do Scheduler.
	switch( g_scheduler_status )
	{
	    case LOCKED:
		    printf("Scheduler is LOCKED\n");
		    break; 
	    
		case UNLOCKED:
		    printf("Scheduler is UNLOCKED\n");
		    break; 
	};

	//
	// ## Process and thread ##
	//
	
	printf("[Process Info:]\n");	
    
	//Current process and current thread.
	printf("CurrentProcess={%d} CurrentThread={%d}\n", 
	    current_process, current_thread );

	printf("# thread info #\n");	
	printf("{ %d } threads_counter\n\n", ProcessorBlock.threads_counter );	
    
	show_thread_information ();		

		
	// Critério de dispatch.
	// Mostra o número de vezes que um critério de seleção 
	// de thread foi usado pelo dispatcher.
	
	printf("\n");
    printf("[Dispatch criteria:]\n");
	printf("cIdle={%d} cInit={%d} cNext={%d} cCur={%d} "
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
	//#bugbug: A informações sobre a stack estão incorretas, 
	//pois essas variáveis mostram 
	// o endereço da stack na hora da inicialização. 
	//Quando o processador retorna de ring3 para ring0
	//ele usa o endereço de pilha indicado na TSS.
	//Pois bem, é mais digno mostrar aqui o endereço da pilha, 
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
	
	//Nothing.   	
    goto done;	
	
fail:
    printf("fail\n");	
done:
    //SetFocus(hWindow);
	
	// Talvez possamos da refresh apenas da janela 
	// onde as strings aparecem.	
    refresh_screen();
	return;	
};


/*
 Salva as informações em um arquivo de texto.
void infoSaveInfo();
void infoSaveInfo()
{
	return;
}
*/

/*
 * @todo:
 *
void infoShowKernelInfo();
void infoShowKernelInfo()
{
	return;
};
*/


//
// Fim.
//

