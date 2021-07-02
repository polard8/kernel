
// system.c

#include <kernel.h>    


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

/*
 * systemShutdownViaAPM:
 *     Desliga a máquina via APM.
 *     (Deve chamar uma rotina herdada do BM).
 */

void systemShutdownViaAPM (void){

    // Obs: @todo:
	//     Existe uma rotina no BM que desliga a máquina via APM usando 
	// recursos do BIOS. A rotina começa em 32bit, assim podemos tentar herdar 
	// o ponteiro para a função.
	
    //Chamar a função de 32 bit herdado do BM.
    //todo: usar iret.
	
	// Check limits.
	// O ponteiro herdado tem que ser um valor dentro do endereço onde 
	// roda o BM, que começa em 0x8000.
	// if(shutdown_address > 0x8000 && shutdown_address < 0x20000 ){
		
	//Pilha para iret.
    //asm("pushl %0" :: "r" ((unsigned long) 8)     : "%esp");    //cs.
    //asm("pushl %0" :: "r" ((unsigned long) shutdown_address)    : "%esp");  //eip.
	//asm("iret \n");    //Fly!	
		
	//};


    panic ("systemShutdownViaAPM:\n");
}

/*
 ****************************************
 * systemShutdown:
 *     Interface para shutdown.
 */ 

// #todo

void systemShutdown (void)
{
    printf ("systemShutdown: It's safe to turnoff your computer");

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

void systemSetupVersion (void){

    Version = (void *) kmalloc( sizeof(struct version_d) );

    // #todo:
    // Isso deve ser considerado um erro fatal,
    // pois existem aplicações que dependem da versão do sistema 
    // para funcionarem corretamente.. 

    if ( (void *) Version == NULL ){
        panic("systemSetupVersion: Version");
    } else {
        Version->Major = VERSION_MAJOR;
        Version->Minor = VERSION_MINOR;
        Version->Build = VERSION_BUILD;
    };


    // VersionInfo.
    VersionInfo = (void *) kmalloc ( sizeof(struct version_info_d) );

        //#todo:
        //Isso deve ser considerado um erro fatal,
        //pois existem aplicações que dependem da versão do sistema 
        //para funcionarem corretamente.. 

    if ( (void *) VersionInfo == NULL ){
        panic ("systemSetupVersion: VersionInfo\n");
    }else{

        // #todo
        if ( (void *) Version != NULL  )
        {

            //VersionInfo->version = (void *) Version;
            //...VersionInfo->string = (char*) ...;
            //... 			
        };
		//...
    };

    //
    // System
    //

    if ( (void *) System == NULL ){
        panic ("systemSetupVersion: System");
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





















