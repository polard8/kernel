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
extern unsigned long kernel_begin;
extern unsigned long kernel_end;
extern unsigned long code_begin;
extern unsigned long code_end;
extern unsigned long data_begin;
extern unsigned long data_end;
extern unsigned long bss_begin;
extern unsigned long bss_end;



/*
 * KeInformation: 
 *    @todo:
 *    Mostra em informações sobre o kernel.
 *    Chama módulo externo (Server em user mode) para
 *    mostrar informações sobre o kernel ou sobre o sistema.
 *
 *    Obs: As informções podem ser salvas em um arquivo
 *         de saída padrão.
 */
void KeInformation(){	
	return;    //Ainda não implementada.
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
void KiInformation()
{
	struct window_d *hWnd;
	struct window_d *hWindow;
	
	
	//unsigned long HeapTotal = ((kernel_heap_end - kernel_heap_start)/1024);
	//unsigned long StackTotal = ((kernel_stack_start - kernel_stack_end)/1024);	
	
	//Parent window.
	if( (void*) gui->main == NULL){
	    return;
	};
	
	unsigned long left   = gui->main->left;
	unsigned long top    = gui->main->top;
	unsigned long width  = gui->main->width;
	unsigned long height = gui->main->height;		
	
    //no caso de falha a mensagem aparecerá aqui.
	//o cursor será configurado mais a frente.
	g_cursor_x = (left/8);
	g_cursor_y = (top/8); 	
	
	if(VideoBlock.useGui == 1)
	{
		//Parent window.
	    if( (void*) gui->main == NULL){
	        return;
	    };
			
	    //Create.
	    hWindow = (void*) CreateWindow( 3, 0, VIEW_MAXIMIZED, "//KERNEL Information", 
	                                    left, top, width, height, 
			     				        gui->main, 0, KERNEL_WINDOW_DEFAULT_CLIENTCOLOR, KERNEL_WINDOW_DEFAULT_BGCOLOR ); 

	    if( (void*) hWindow == NULL){
	        printf("KiInformation:\n");
		    return;
        }else{
		    RegisterWindow(hWindow);
			set_active_window(hWindow);
			SetFocus(hWindow);
	    };										
		
		
		// Auterando as margens.
		// Essas margens são usadas pela função printf.
		// Obs: As medidas são feitas em números de caracteres.
		// Obs: @todo: Devemos usar aqui o retângulo da área de cliente,
		// e não as margens da janela.
		// A estrutura de janela deve nos oferecer os valores para a métrica do 
		// retângulo da área de cliente.
		// Obs: @todo:Acho que essa não é a forma correta de configurar isso. Uma 
		//rotina deveria perceber as dimensões da janela de do caractere e determinar
		//as margens.
		
		g_cursor_left   = (hWindow->left/8);
		g_cursor_top    = (hWindow->top/8) + 4;   //Queremos o início da área de clente.
		g_cursor_right  = g_cursor_left + (width/8);
		g_cursor_bottom = g_cursor_top  + (height/8);
		
		//cursor (0, mas com margem nova).
		g_cursor_x = g_cursor_left; 
		g_cursor_y = g_cursor_top; 
		
        
	    //
	    // Messages.
	    //
	
	    printf("\n[System Info:]\n");
	    //OS info.
	    printf("%s ",OS_NAME);
	    printf("Version: %d.%d.%d\n\n",
		    SYSTEM_VERSIONMAJOR,
			SYSTEM_VERSIONMINOR,
			SYSTEM_VERSIONREVISION );
	
	    //
		// Screen resolution. (first of all)
		//
	    
		printf("\n[Screen Resolution:]\n");
		printf("Width={%d} Height={%d}\n",
		    g_device_screen_width, g_device_screen_height );
		
		//
	    // Kernel info.
	    //
	
	    //Version and time running.	
	    printf("\n[Kernel Info:]\n");
	    printf("Kernel version: %s\n",KERNEL_VERSION );
	    printf("Ticks running: %d\n",kernel_tick_total );

												   
        //ShowUserInfo(int user_id);	


	    //
        // Show status.
        //
	
	    //Status do mecanismo de task switch.
	    switch(task_switch_status)
	    {
	        case LOCKED:
		    printf("Task switch is LOCKED.\n");
			break; 
	        case UNLOCKED:
		    printf("Task switch is UNLOCKED.\n");
		    break; 	
	    };

	    //Status do Scheduler.
	    switch(g_scheduler_status)
	    {
	        case LOCKED:
		    printf("Scheduler is LOCKED.\n");
		    break; 
	        case UNLOCKED:
		    printf("Scheduler is UNLOCKED.\n");
		    break; 
	    };

		
	    //
	    // Mostra o número de vezes que um critério de seleção de thread 
	    // foi usado pelo scheduler.
	    //
	
	    printf("\n[Dispatch criteria:]\n");
	    printf("cIdle={%d} cInit={%d} cNext={%d} cCur={%d} cAny={%d} cIdeal={%d} cDisp={%d}\n",
		    DispatchCountBlock->SelectIdleCount,
			DispatchCountBlock->SelectInitializedCount,
			DispatchCountBlock->SelectNextCount,
			DispatchCountBlock->SelectCurrentCount,
			DispatchCountBlock->SelectAnyCount,
			DispatchCountBlock->SelectIdealCount,
			DispatchCountBlock->SelectDispatcherQueueCount );
			

			
		printf("\n## thread info ## \n");	
		printf("\n{ %d } threads running\n",ProcessorBlock.running_threads);	
        show_thread_information();		
		
        //
	    // Mostra Heap e Stack do kernel..
	    //
	
	
        //printf("\n[Kernel Heap and Stack info:]\n");
	    //printf("HEAP: Start={%x} | End={%x} | Total={%d KB} \n",kernel_heap_start ,kernel_heap_end ,HeapTotal);	
        //printf("AvailableHeap={%d KB}\n",g_available_heap/1024);
	    
		//@todo:
		//mostrar o tamanho da pilha..
		//#bugbug: A informações sobre a stack estão incorretas, pois essas variáveis mostram 
		// o endereço da stack na hora da inicialização. Quando o processador retorna de ring3 para ring0
		//ele usa o endereço de pilha indicado na TSS.
		//Pois bem, é mais digno mostrar aqui o endereço da pilha, indicado no TSS.
		//printf("STACK: Start={%x} | End={%x} | Total={%d KB} \n",kernel_stack_start ,kernel_stack_end ,StackTotal);
        //printf("STACK: StartPhysicalAddress={%x} \n",kernel_stack_start_pa);
	
	    //
	    // Video info
	    //
	
	    //printf("\n[Video Info:]\n");
	
	    //Video mode.
	    //printf("The video option is %x \n",g_video_mode);
	    //printf("FrontbufferPA={%x} FrontbufferVA={%x} BackbufferVA={%x} \n",g_frontbuffer_pa ,g_frontbuffer_va ,g_backbuffer_va);
	
	    //
	    // user info
	    //
	
	    printf("\n[User Info:]\n");
	
	    //Group and user.
	    printf("Group={%d} User={%d} \n", 
		    current_group, current_user);
	
	    //user session, window station, desktop.
	    printf("UserSession={%d} DesktopPool={%d} Desktop={%d} \n",
		    current_usersession, current_windowstation, current_desktop );
															
	    ShowUserInfo(0);  //#bugbug
	
	
	    //
	    // Process and thread info
	    //
	
	    printf("\n[Process Info:]\n");	
        //process, thread.
	    printf("CurrentProcess={%d} CurrentThread={%d} \n\n", 
		    current_process, current_thread );
	
					
	
	    //
	    // Memory info.
	    // Obs: memoryShowMemoryInfo mostrará informações 
		// que hoje estão aqui nessa rotina.
	    //  
	    memoryShowMemoryInfo();
	
	    //Específico para intel.
	    //Talves isso não deva ficar aqui.
	    //show_cpu_intel_parameters();
	
	
	    //
		// Disks and directories
		//
		
		//printf("\n[Disks and directories:]\n");
		
		//disk
		//printf("%s (system disk)\n",SYSTEM_DISK);
		//printf("%s (system volume)\n",SYSTEM_VOLUME);
		
		//directories
		//printf("%s\n",SYSTEM_GBUILD);
		//printf("%s\n",SYSTEM_GDOCS);
		//printf("%s\n",SYSTEM_GRAMADO);
		//printf("%s\n",SYSTEM_GSDK);
		//printf("%s\n",SYSTEM_GSRC);
	    
		//
		// Test.
		//
		
		
		//Tentando mostrar informações sobre a imagem do kernel.
		//o início da área de código e o início da área de dados.
		
		/* #bugbug: os valores apresentados não foram os esperados.
		printf("KernelBegin={%x} Kernelend={%x}\n" ,kernel_begin ,kernel_end );
		printf("CodeBegin={%x} CodeEnd={%x} \n",code_begin ,code_end);
		printf("DataBegin={%x} DataEnd={%x} \n",data_begin ,data_end);
		printf("BSSBegin={%x} BSSEnd={%x} \n",bss_begin ,bss_end);
		*/
		
		
		//More?!
	
        SetFocus(hWindow);
	
		
		//voltando a margem normal a margem
		g_cursor_left = left;       //0;
		g_cursor_top =  top;        //0;
		g_cursor_right  = (width/8);   
		g_cursor_bottom = (height/8);  
		
		//cursor (0, mas com margem nova)
		g_cursor_x = g_cursor_left; 
		g_cursor_y = g_cursor_top;
        //set_up_cursor(g_cursor_left,g_cursor_top); 		

		StatusBar(hWindow,"Esc=EXIT","Enter=?");		
		//Nothing.
	};	   	
	
	
//Done
done:
    //talvez possamos da refresh apenas da janela onde as strings aparecem...
	if( VideoBlock.useGui == 1 ){
		refresh_screen();
	}
	
	//SetFocus(hWindow);	
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

