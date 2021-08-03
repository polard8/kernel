
// system.c

#include <kernel.h>    



/*
 ***************************************
 * systemGetSystemMetrics:
 *     Retorna informações sobre o sistema.
 * 
 *     #todo: 
 *     Criam um enum para essa função, aqui mesmo nesse arquivo.
 */

unsigned long systemGetSystemMetrics ( int index )
{


    // #bugbug
    // We have a HUGE problem here.
    // We can't properly get the data inside the structures. 
    // The value is not the same when we enter inside the kernel via
    // keyboard interrupt or via system interrupt.
    // #todo: Maybe we need to use global variables for now
    // and review all the moment when the ring3 app tryes to
    // get data from a ring0 struct.

    // # The solution.
    // We are trying to have more system calls. sc80 sc81 sc82.
    // These system calls uses different set of selectors.

	//print ("#debug: systemGetSystemMetrics: i={%d} \n",index)

    if ( index <= 0 ){
        return (unsigned long) 0;
    }

    switch ( index ){

        //screen width.
        case 1:
            return (unsigned long) screenGetWidth();
            break;

        //screen height.	
        case 2:
            return (unsigned long) screenGetHeight();
            break;


        //cursor width in pixels.
        case 3:
            return (unsigned long) CONSOLE_TTYS[fg_console].cursor_width_in_pixels;
            break;

        //cursor height in pixels.
        case 4:
            return (unsigned long) CONSOLE_TTYS[fg_console].cursor_height_in_pixels;
            break;


        // mouse pointer width.
        case 5:
            return (unsigned long) g_mousepointer_width;
            break;
         
        // mouse pointer height. 
        case 6:
            return (unsigned long) g_mousepointer_height;
            break;

		//char width.
        case 7:
		    return (unsigned long) get_char_width();
            break;

		//char height.
        case 8:
		    return (unsigned long) get_char_height();
            break;
            
            
        case 9:
            return (unsigned long) SavedBPP;
            break;    
            
      
        //
        // screen buffers
        //

        // lfb pa
        case 10:
		    return (unsigned long) g_frontbuffer_pa;
            break;        

            
        // lfb va
        case 11:
		    return (unsigned long) g_frontbuffer_va;
            break;        

        // main backbuffer va
        case 12:
		    return (unsigned long) g_backbuffer_va;
            break;                   
     
                      
        //20   
        // mouse x    
        case SM_GETMOUSEX:
            //#bugbug: Pegando informações com o driver de mouse.
            //return (unsigned long) ps2_mouse_get_info (3); 
            panic ("systemGetSystemMetrics: SM_GETMOUSEX #todo \n");
            break;

        //21
        //mouse y
        case SM_GETMOUSEY:
           //#bugbug: Pegando informações com o driver de mouse.
            //return (unsigned long) ps2_mouse_get_info (4); 
            panic ("systemGetSystemMetrics: SM_GETMOUSEY #todo\n");
            break;

        //
        // Ram support
        //
      
        // base memory
        case 30:
            return (unsigned long) memorysizeBaseMemory;
            break;
            
        // extended - base
        case 31:
            return (unsigned long) memorysizeOtherMemory;
            break;
            
            
        // extended memory
        case 32:
            return (unsigned long) memorysizeExtendedMemory;
            break;
            
        // total = base + other + extended 
        case 33:
            return (unsigned long) memorysizeTotal;
            break;                    

        // used
        case 34:
            return (unsigned long) memorysizeUsed;
            break;  
        
        // free   
        case 35:
            return (unsigned long) memorysizeFree;
            break;  
            
         //
         // Kernel Heap support.
         //   

        case 40:
            return (unsigned long) kernel_heap_start;
            break;  
            
        case 41:
            return (unsigned long) kernel_heap_end;
            break;  
            
        case 42:
            return (unsigned long) g_available_heap;
            break; 
            
         //
         // Kernel Stack support.
         //   
            
        case 50:
            return (unsigned long) kernel_stack_start;
            break; 

        case 51:
            return (unsigned long) kernel_stack_end;
            break; 
            
        case 52:
            return (unsigned long) kernel_stack_start_pa;
            break; 


            
        //
        // used memory support
        //

        case 60:
            return (unsigned long) mm_used_ring0_area;
            break;   

        case 61:
            return (unsigned long) mm_used_ring3_area;
            break;   


        case 62:
            return (unsigned long) mm_used_backbuffer;
            break;   



        case 63:
            return (unsigned long) mm_used_pagedpool;
            break;   



        case 64:
            return (unsigned long) mm_used_heappool;
            break;   


        case 65:
            return (unsigned long) mm_used_extraheap1;
            break;   
            
        case 66:
            return (unsigned long) mm_used_extraheap2 ;
            break;   
            
        case 67:
            return (unsigned long) mm_used_extraheap3;
            break; 
            

        //
        // Dispatch critéria.
        //
        
        case 70:
            return (unsigned long) DispatchCountBlock->SelectIdleCount;
            break;               

        case 71:
            return (unsigned long) DispatchCountBlock->SelectInitializedCount;
            break;   
            
        case 72:
            return (unsigned long) DispatchCountBlock->SelectNextCount;
            break;                         

        case 73:
            return (unsigned long) DispatchCountBlock->SelectCurrentCount;
            break;   
            
        case 74:
            return (unsigned long) DispatchCountBlock->SelectAnyCount;
            break;   
            
        case 75:
            return (unsigned long) DispatchCountBlock->SelectIdealCount;
            break;   
            
        case 76:
            return (unsigned long) DispatchCountBlock->SelectDispatcherQueueCount;
            break;               
   


        // system type. by memory size;
        case 90:
            return (unsigned long) g_mm_system_type;
            break;  
            
        //
        // Profiler ... (reservar vários números.)
        //
        
                      
        case 100:
            return (unsigned long) g_profiler_ints_irq0;
            break;              

        case 101:
            return (unsigned long) g_profiler_ints_irq1;
            break;              
            
        case 102:
            return (unsigned long) g_profiler_ints_irq2;
            break; 

        case 103:
            return (unsigned long) g_profiler_ints_irq3;
            break;

        case 104:
            return (unsigned long) g_profiler_ints_irq4;
            break;              

        case 105:
            return (unsigned long) g_profiler_ints_irq5;
            break;              
            
        case 106:
            return (unsigned long) g_profiler_ints_irq6;
            break;              
            
            
        case 107:
            return (unsigned long) g_profiler_ints_irq7;
            break;              

        case 108:
            return (unsigned long) g_profiler_ints_irq8;
            break;              

        case 109:
            return (unsigned long) g_profiler_ints_irq9;
            break;              
            
        case 110:
            return (unsigned long) g_profiler_ints_irq10;
            break;              
            
            
        case 111:
            return (unsigned long) g_profiler_ints_irq11;
            break; 

        case 112:
            return (unsigned long) g_profiler_ints_irq12;
            break; 

        case 113:
            return (unsigned long) g_profiler_ints_irq13;
            break; 
            
        case 114:
            return (unsigned long) g_profiler_ints_irq14;
            break; 
            
            
        case 115:
            return (unsigned long) g_profiler_ints_irq15;
            break; 
            
          
        // Interrupção de serviços do sistema.
        case 117:
            return (unsigned long) g_profiler_ints_gde_services;
            break; 

       // PIT
       // See: hal/pit.h
       
       // jiffies.
       // total ticks
       case 118:  return (unsigned long) jiffies;  break;

       // seconds
       // por quantos segundos o sistema esta rodando
       // jiffies/sys_time_hz
       case 119:  return (unsigned long) seconds;      break;
       
       // Por quantos ms o sistema esta rodando.
       case 120:  return (unsigned long) sys_time_ms;  break;

       // pit frequency
       case 121:  return (unsigned long) sys_time_hz;  break;

        // ...

       // gramado mode, gamemode.
       // jail, p1, home ...
       case 130:  return (unsigned long) current_mode;  break;

       // When a thread is running to call this service,
       // so, this thread is the current thread.
       // But, current for what processor?
       case 140:  return (unsigned long) current_process;  break;
       case 141:  return (unsigned long) current_thread;   break;

       //case 150:  break;
       //case 151:  break;

        // 200 ~ 2xx window server info.
        // See: ws.h

        // #bugbug
        // Quando estamos dentro do kernel por entrarmos via interrupçao de teclado,
        // esses valores estao certos,
        // mas quando estamos dentro do kernel, por entrarmos via interrupçao de sistema,
        // esses valores estao errados.
        // #porque
        // ?? seria algum problema de selecao de diretorio de paginas,
        // ou de configuraçao de registrador de segmento.
        // podemos checar se a configuraçao dos segmentos de dados esta
        // certa na hora da entrada da interrupçao de sistema.
        // o problema eh que mudarmos o registrador de segmento, entao
        // o kernel nao podera mais pegar as informaçoes que estao em ring3. certo??
        // See:
        // sw.asm
        
        case 200:
           //printf ("#type: %d\n",WindowServer_type);
           //refresh_screen();
           return (unsigned long) WindowServer_type;
           break;

        case 201:
           //printf ("#pid: %d\n",WindowServer_pid);
           //refresh_screen();
           return (unsigned long) WindowServer_pid; 
           break;

        case 202:
           //printf ("#virtual_console: %d\n",WindowServer_virtual_console);
           //refresh_screen();
           return (unsigned long) WindowServer_virtual_console; 
           break;

        case 203:
           //printf ("#initialized: %d\n",WindowServer_initialized);
           //refresh_screen();
           return (unsigned long) WindowServer_initialized; 
           break;
        
        // is quemu
        case 300:
            return (unsigned long) g_is_qemu;
            break;
           

        // ...
                
        default:
            goto done;
            break;
    };

done:
    return (unsigned long) 0;
}







void a_soft_place_to_fall(void)
{
    while (TRUE)
    { 
        asm ("cli");
        //asm ("mwait");   
        asm ("hlt");
    };
}

// The kernel hangs.
void die (void){

    // Bullet.
    printf ("die: * System Halted\n");

    if ( VideoBlock.useGui == TRUE ){
        refresh_screen ();
    }

    a_soft_place_to_fall();
    die();
}

/*
 * system_get_pid:
 * 
 */

// Usada para obter o pid de alguns drivers e servidores
// do sistema. Aqueles servidores que só podem ter um do tipo 
// rodando ao mesmo tempo.
// É o serviço 9999.
// See: kernel.h, system.h

int system_get_pid (int index){

    if ( index < 0 ){
        return -1;
    }


    switch (index)
    {
        case GETPID_NULL:
            return -1;
            break;

        case GETPID_WS:
            //return (int) g_ws_pid;
            break;

        case GETPID_WM:
           // return (int) g_wm_pid;
            break;

        default:
            return -1;
            break;
    };

    return (int) -1;
}


// ??
// APM is a 16bit real mode thing.
void systemShutdownViaAPM (void)
{
    panic ("systemShutdownViaAPM: [FAIL]\n");
}


/*
 ****************************************
 * systemShutdown:
 *     Interface para shutdown.
 */ 

// #todo

void systemShutdown (void)
{
    printf ("systemShutdown: It's safe to turnoff your computer\n");

    refresh_screen ();
    die ();
}

/*
 * systemShowDevicesInfo:
 * 
 *     Mostrar informações sobre o sistema, seguindo a ordem de
 *     velocidade dos dispositivos e barramentos.
 *     Ex: CPU, Memória, PCIE (video), South Bridge, Super Io ...
 *     A Apresentação da sondágem pode ser feita em outra ordem,
 *     melhor que seja a ordem alfabética.
 *     See: devmgr.c
 */

void systemShowDevicesInfo (void)
{
    devmgr_show_device_list();
}



/*
 ***************************************
 * systemSetupVersion:
 *     Setup version info.     
 */

// See:
// config/version.h
// config/u.h
// system.h

void systemSetupVersion (void)
{

//
// Global structure
//

    Version = (void *) kmalloc( sizeof(struct version_d) );

    // #todo:
    // Isso deve ser considerado um erro fatal,
    // pois existem aplicações que dependem da versão do sistema 
    // para funcionarem corretamente.. 

    if ( (void *) Version == NULL ){
        panic("systemSetupVersion: Version");
    }


    Version->Major = VERSION_MAJOR;
    Version->Minor = VERSION_MINOR;
    Version->Build = VERSION_BUILD;

//
// Global structure
//

    VersionInfo = (void *) kmalloc ( sizeof(struct version_info_d) );

    // #todo:
    // Isso deve ser considerado um erro fatal,
    // pois existem aplicações que dependem da versão do sistema 
    // para funcionarem corretamente.. 

    if ( (void *) VersionInfo == NULL ){
        panic ("systemSetupVersion: VersionInfo\n");
    }


//
// Global structure
//

    if ( (void *) System == NULL ){
        panic ("systemSetupVersion: System\n");
    }

//
// Colocando na estrutura System se ela for válida.
//

    if ( (void *) System != NULL )
    {

        if ( System->used == 1 && System->magic == 1234 )
        {
            System->version      = (void *) Version;
            System->version_info = (void *) VersionInfo;
        }
        //Nothing
    }

	// More ?!
}

/*
 *******************************************************
 * systemReboot:
 *     Interface de inicialização da parte de sistema para o 
 * processo de reboot.
 *     realiza rotinas de desligamento de sistema antes de chamar 
 * o reiniciamento de hardware.
 *     *IMPORTANTE: Um processo em user mode deve realizar as rotinas 
 * de desligamento.
 *     passar para o kernel somente depois de fechar todos os processos.
 *     Quando essa rotina checar os processos verá que não há mais nada 
 * pra fechar.
 *     se ainda tiver algum processo pra fechar, então essa rotina 
 * fecha, senão termina a rotina. 
 */

void systemReboot (void){

	//int i;
	//unsigned long left;
	//unsigned long top;
	//unsigned long width;
	//unsigned long height;
	
	//struct process_d *P;
	//struct thread_d *T;
		
	//struct window_d *hWnd;
	//struct window_d *hWindow;

    //x86 ?
    debug_print ("systemReboot: [?] ...\n");

    asm ("cli");

// No graphics

    if ( VideoBlock.useGui != TRUE )
    {
        hal_reboot ();
    }


	//#importante:
	//suspendendo a rotina de reboot,
	//até que todas funcionalidades gráficas estejam em ordem.
	//Na verdade deveria existir um aplicativo chamado reboot 
	//que inicialise essa rotina deixando par ao kernel apenas 
	//a parte de baixo nível.

    hal_reboot();


/*
		
	//Parent window.
	if ( (void *) gui->main == NULL )
	{
	    hal_reboot ();
		
	}else{
	    
		left = gui->main->left;
	    top = gui->main->top;
	    
		width = gui->main->width;
	    height = gui->main->height;	
		
	    set_up_cursor( (left/8) , (top/8) );
		//...
	};
	
	// @todo: Usar esquema de cores padrão.
	
	if ( VideoBlock.useGui == 1 )
	{
		//Parent window.
	    if ( (void *) gui->main == NULL ){
	        hal_reboot();
	    }
			
	    //Create.
	    hWindow = (void *) CreateWindow( 3, 0, VIEW_MAXIMIZED, "systemReboot:", 
	                        left, top, width, height, 
			     			gui->main, 0, KERNEL_WINDOW_DEFAULT_CLIENTCOLOR, KERNEL_WINDOW_DEFAULT_BGCOLOR ); 

	    if ( (void *) hWindow == NULL ){
	        hal_reboot();
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
		
		g_cursor_left = (hWindow->left/8);
		g_cursor_top = (hWindow->top/8) + 4;   //Queremos o início da área de clente.
		
		g_cursor_right = g_cursor_left + (width/8);
		g_cursor_bottom = g_cursor_top  + (height/8);
		
		//cursor (0, mas com margem nova).
		g_cursor_x = g_cursor_left; 
		g_cursor_y = g_cursor_top; 
        
	    //
	    //@todo: Criar a interface. realizando configurações de sistema
	    // antes de chamar o hal.
	    // É apropriado deixar aqui as rotinas de desligamento do sistema
	    // ficando para hal a parte de hardware.
	    // +salvar arquivos de configuração.
	    // +salvar discos virtuais.
	    // ...
	    //
    
     	//...
	
        //
        // Coloca uma tela preta pra começar.
        //
	
        //Cls and Message.
	    //backgroundDraw(COLOR_BACKGROUND);
	    //StatusBar( gui->screen, "StatusBar: ", "Rebooting...");	
        //refresh_screen();

	
	    //@todo:
	    //block current task.
	    //close tasks
	    //...

        //
        //@todo: 
	    // +criar uma variavel global que especifique o tipo de reboot.
        // +criar um switch para efetuar os tipos de reboot.
	    // +criar rota de fuga para reboot abortado.
	    // +Identificar o uso da gui antes de apagar a tela.
	    //  modo grafico ou modo texto.
	    //

	
	    //
	    // Video.
	    //
	
        set_up_cursor(0,4);	            //O cursor deveria ficar na área do cliente.	
        set_up_text_color(0x0f, 0x09);  //isso é para modo texto. eu acho??
	    
		//init message.
		sleep(8000);
        printf("\n REBOOT:\n");	
	    printf("The computer will restart in seconds\n");
	
	    //
	    // Scheduler stuffs.
	    //
	
	    sleep(8000);
	    printf("Locking Scheduler and taskswitch\n");
	    scheduler_lock();
	    taskswitch_lock();
	
	
	    //
	    // File System stuffs. @todo
	    //
	
	    //
	    // Fechando processos que não foram fechados pelo shutdown em user mode.
	    // Obs: Todos os processos nesse momento ja deveriam estar terminados
	    // através de rotinas em user mode. Então checamos se falta algum e 
	    // caso haja, terminamos o processo.
	    // Obs: A rotina de fechar processo deve fechar as threads na ordem da lista encadeada.
	    //

	    sleep(8000);
	    printf("Terminating processes..\n");
		
		
		//
		// +Enviamos sinal para todas as threads bloquearem.
		// +desalocamos todos os recursos usados por elas.
		// +mandamos sinal para todas as thears fecharem.
		//
		
//blockingAllThreads:		
		//antes de terminarmos todos processos vamos boquear todas as threads.
	    //Começa do 1 para não fechar o kernel.
	    i = 1;
	
	    while(i < THREAD_COUNT_MAX)
	    {
            //Pega da lista.
		    T = (void *) threadList[i];
		    if(T != NULL)
			{
#ifdef KERNEL_VERBOSE				
		        //bloqueia a thread. 
		        printf("blocking thread TID={%d} ...\n",i);
		        //refresh_screen();
#endif
                if( T->used == 1 ){
                    T->state = BLOCKED; //?? ZOMBIE ??   
		            //block_thread(i, 0);
				}
		    };
		    i++;
	    };

//exitingAllProcesses:	
	    //Começa do 1 para não fechar o kernel.
	    i = 1;
	
	    while(i < PROCESS_COUNT_MAX)
	    {
            //Pega da lista.
		    P = (void *) processList[i];
		    if(P != NULL)
			{
#ifdef KERNEL_VERBOSE				
		        //Termina o processo. (>> TERMINATED)
		        printf("Killing Process PID %d\n", i);
		        //refresh_screen();
#endif
                if( P->used == 1 ){
		            exit_process(i, 0);
				}
		    };
		    i++;
	    };

	    // Final message.
	    sleep(8000);
	    printf("Rebooting..\n");
			
        SetFocus(hWindow);
	
		
		//voltando a margem normal a margem
		//?? isso não é necessário??
		g_cursor_left = (left/8);    //0;
		g_cursor_top = (top/8);        //0;
		
		g_cursor_right = (width/8);   
		g_cursor_bottom = (height/8);  
		
		//cursor (0, mas com margem nova)
		g_cursor_x = g_cursor_left; 
		g_cursor_y = g_cursor_top;
        //set_up_cursor(g_cursor_left,g_cursor_top); 		

        //#bugbug: Aqui não devemos criar uma status bar 
        //apenas atualizar as strings 		
		//StatusBar(hWindow,"Esc=EXIT","Enter=?");		
		//Nothing.
	};
 */

    // Nothing

done:

    refresh_screen();

	//?
    sleep (8*8000);

    printf ("systemReboot: Rebooting ...");
    refresh_screen ();

    //sys_reboot();
    hal_reboot();
    die();
}

// used?
void *systemNull (void)
{
    return NULL;
}


/*
 *******************************
 * init_executive:
 *
 *     Initialize the kernel executive.
 *     Archtecture (independent) inicialization. 
 */

// called by init()

int init_executive (void){

    int Status = 0;


    Initialization.executive = FALSE;

    debug_print ("init_executive:\n");

#ifdef KERNEL_VERBOSE
    printf ("EXECUTIVE:\n");
#endif


//
// PCI
//

    // PCI - Pega informações da PCI.
    // As informaçoes serao salvas em uma lista e usadas depois.
    // por isso temos que sondar agora.
    
    init_pci();


//
// CMOS
//
    // CLOCK - Pega informações de Hora e Data.
    init_clock();

	//...


	// #importante: 
	// Só depois de inicializarmos o ata 'e que podemos carregar 
	// alguma coisa.

    debug_print ("init_executive: ataDialog\n");
    ataDialog ( 1, FORCEPIO, FORCEPIO );

	// ??
	// configura a tabela do kernel de funções exportadas
	// e tabela de ponteiros para tabelas dos outros programas em 
	// kernel mode.
    // Status = (int) executive_config_exported_functions();

	//Continua ...
    
	// #todo: 
	// Checar a validade de 'Initialization' ??

	//#debug
	//printf("Done!\n");

    Initialization.executive = TRUE;

    return (int) Status;
}





















