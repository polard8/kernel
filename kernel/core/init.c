/*
 * File: init.c 
 *
 * Descrição:
 *     Arquivo principal do módulo INIT kernel.
 *     Faz inicializações.
 *     Esse módulo está em kernel base.
 *
 * In this file:
 *    +init
 *    +init_test_disk
 *    +init_video
 *    +init_globals
 *
 * Histórico:
 *     Versão 1.0, 2015 - Esse arquivo foi criado por Fred Nora.
 *     Versão 1.0, 2016 - Aprimoramento geral das rotinas básicas.
 *     //...
 */ 

 
#include <kernel.h>


//Onde ficam os códigos e arquivos de configuração usados na inicialização.
//A ideia é que se a inicialização precisar de algum arquivo, deve procurá-lo
//nos diretórios previamente combinados.
//melhor que sejam poucos e que sempre sejam os mesmos.

#define INIT_ROOT_PATH  "root:"
#define INIT_BIN_PATH   "root:/volume2/bin"
//...


//externs
//@todo:
//isso deverá ser definido em /gramado.
//extern char *GramadoSystemRoot;
//extern char *GramadoMajorVersion;
//extern char *GramadoMinorVersion;
//extern char *GramadoVersionString;
//...


//Variáveis internas.
//int initStatus;
//...


/*
void init_set_current_runlevel ( int number )
void init_set_current_runlevel ( int number )
{
	//#todo: limits.
    current_runlevel = number;
}
*/

/*
int init_get_current_runlevel (void)
int init_get_current_runlevel (void)
{
    return (int) current_runlevel;
}
*/



/*
 * save_kernel_args:
 *     Salvando em estrutura os argumentos recebidos.
 */

void save_kernel_args (void){
	
    //KernelArgs.arg1 = ;
    //KernelArgs.arg2 = ;
	//KernelArgs.arg3 = ;
	//KernelArgs.arg4 = ;
}


/*
 ***********************************
 * init_architecture_dependent:
 *     Rotina de inicialização dependente da arquitetura atual da máquina.
 *     A fase 1 identificou o tipo de processador. Aqui chamaremos a rotina 
 * de inicialização de acordo com o tipo identificado.
 *     A fase 1 inicializou a estrutura processor. Aqui checamos se ela é 
 * válida.
 *  GDT, IDT, ... TR ...
 *
 * Obs: Essa é a fase 2 de inicialização.
 *
 * Obs: Dependente significa dependente da marca do procesador.
 */

int init_architecture_dependent (void){
	
	int Status = 0;
	unsigned char Type;
	
	
	debug_print ("init_architecture_dependent\n");
	
	//
	// Fase. (Verificar se essa rotina foi chamada 
	// na fase certa de inicialização.)
    //
	
	if ( KeInitPhase != 1 )
	{
		panic ("init_architecture_dependent: KeInitPhase\n");	
	}


	// #### IMPORTANTE ####
	//
	// VAMOS ANTECIPAR ESSA INICIALIZAÇÃO NA TENTATIVA DE
	// ANTECIPARMOS O USO DE MENSAGENS.
    // >>> mas essa rotina precisa do kmalloc ,,,
	//então tem que ser depois da inicialização do stdio.
	
	
	// Os parâmetros de tela dependem das propriedades de hardware
	// como monitor e placa de vídeo.
	
	//screenInit();

    //printf("init_architecture_dependent: #Debug");
    //refresh_screen();
    //while(1){};		
	
	
	//
	// * A estrutura para informações sobre o processador. 
	//
	
	// Check structure.
	if ( (void *) processor == NULL )
	{
	    panic ("sm-init-init_architecture_dependent: processor\n");
    }

	// Sonda pra ver qual é a marca do processador.
	// @todo: É a segunda vez que fazemos a sondagem ?!
	
	Type = (int) hal_probe_processor_type();
	
	//Type.
	processor->Type = (int) Type;
	
	
	//
	//Inicializa de acordo com o tipo de processador..
	//
	
	switch (Type)
	{
	    //Intel. (pega os parâmetros do processador intel e coloca na estrutura).
	    case Processor_INTEL: 
		    init_intel(); 
			break;

        //AMD. (pega os parâmetros do processador amd e coloca na estrutura).
	    case Processor_AMD: 
		    init_amd(); 
			break;

        //Continua ...
			
		//@todo: Aqui é um erro fatal.	
		default:
		    panic ("sm-init-init_architecture_dependent default Type\n");
            break;		
	};
	
	
	//
	// @todo: GDT, IDT (usar extern).
	//	
	
	
	// o contexto é depedente.
	//Inicializando o Process manager.
	init_process_manager ();




    //
    // Continua ...
    //
	
    // Done.
    
	return (int) Status;
}



/*
 ******************************************************************
 * init_architecture_independent:
 *
 *    Rotina de inicialização da parte do sistema que é independente da 
 * arquitetura presente. Independente da tipo de processador. 
 *    Obs: Essa é a fase 1 de inicialização.
 */

int init_architecture_independent (void){
	
    int Status;

    debug_print ("init_architecture_independent\n");

    if (KeInitPhase != 0){
        panic ("init_architecture_independent: KeInitPhase\n");
    }

	
	//
	//  ## HAL ##
	//
    
	// #bugbug
	// Se é HAL é dependente da arquitetura.
	// Isso deveria ficar na outra rotina.
	// Não mudaremos por enquanto.
	
#ifdef EXECVE_VERBOSE	
    printf ("init_architecture_independent: Initializing HAL..\n");
#endif

    Status = init_hal ();

    if (Status != 0){
        panic ("init-init_architecture_independent: init_hal\n");
    }

	
    //
	//  ## MICREOKERNEL ##
	//
	
	
	// Microkernel:
#ifdef EXECVE_VERBOSE
	// Obs: O Microkernel lida com informações dependentes da arquitetura,
	// porém inicializa a gerencia de processos e threads e de comunicação
	//entre processos.
	//#bugbug @todo: Se é microkernel é processo é registrador ... acho que leva em consideração a arquitetura.
	printf ("init_architecture_independent: Initializing Microkernel..\n");
#endif	
	
	Status = init_microkernel ();

    if (Status != 0){
	    panic ("init-init_architecture_independent: init_microkernel\n");
    }
	
	
	//
	// ## EXECUTIVE ##
	//
	
	
    // Executive:
#ifdef EXECVE_VERBOSE
	// Obs: O executive não é tão dependente da arquitetura, ele é
	//uma camada mais alta, porém será inicializado aqui para
	//efeito de ordem, já que estamos inicializando os tres módulos
	//básicos do kernel base nesse momento.
	printf ("init_architecture_independent: Initializing Executive..\n");
#endif	
	
	Status = init_executive ();

    if (Status != 0){
	    panic ("init-init_architecture_independent: init_executive\n"); 
    }

	//
	// ## GWS ?? ##
	//
	
	// Gramado:
#ifdef EXECVE_VERBOSE
    printf ("init_architecture_independent: Initializing Gramado..\n");
#endif

   
    // #bugbug
    // Deprecated?

    Status = init_gramado();
    if (Status != 0)
    {
        panic ("init-init_architecture_independent: init_gramado\n"); 
    }


    // Initializing window manager.


    // Text mode not supported.
    if (g_useGUI != 1)
    {
        panic ("init_architecture_independent: PANIC: No GUI!\n");
    }

// Window manager.
#ifdef EXECVE_VERBOSE
    printf ("init-init_architecture_independent: init_window_manager\n");
#endif

    init_window_manager();


    // More? ...


//done:

#ifdef EXECVE_VERBOSE
    printf ("init_architecture_independent: Done\n");
    refresh_screen();
    //while(1){}
#endif

    return 0;
}


/*
 **************************************************
 * init_globals:
 *     Init globals. 
 *     Inicia variáveis globais do Kernel Base.
 *     Obs: Inicializar por categorias.
 */

void init_globals (void){


    int i=0;


#ifdef EXECVE_VERBOSE
    printf("sm-init-init_globals:\n");
   debug_print("init_globals:\n");
#endif

    //Outros.
    errno = 0;

    // Inicializa as estruturas do fluxo padrão.
    // Isso vai usar a file table.
    stdioInitialize();


	//#importante
	//>>> é a partir daqui que temos mensagens!!!
	
    screenInit ();
	
	//
	// ## FIRST MESSAGE !! ##
	//
	
    debug_print("init_globals: WE HAVE MESSAGES NOW!\n");
    printf("init_globals: First message!\n");


	//
	// Runlevel
	//
	
	// 5 	Start the system normally with appropriate 
	// display manager (with GUI) 	
	// Same as runlevel 3 + display manager.
	// Full multi-user graphical mode. 
	current_runlevel = 5;
	
    //===================	
	//vamos atrazar configuração de janela em favor de configuração de mensagem

	//Atalho para a próxima mensagem de teclado..(test) debug
	gNextKeyboardMessage = (int) 0;
	
	//Essa flag bloqueia e impede que uma janela obtenha o foco.
	gFocusBlocked = (int) 0;
	
	
	//
	// ==== Profiler ====
	//
	
	// See: include/kernel/profiler/pints.h
	
	// Interrupção para serviços do sistema.
	g_profiler_ints_gde_services = 0;

    // Legacy hardware interrupts (irqs) (legacy pic)
    g_profiler_ints_irq0 = 0;  
    g_profiler_ints_irq1 = 0;  
    g_profiler_ints_irq2 = 0;  
    g_profiler_ints_irq3 = 0;  
    g_profiler_ints_irq4 = 0;  
    g_profiler_ints_irq5 = 0;  
    g_profiler_ints_irq6 = 0;  
    g_profiler_ints_irq7 = 0;  
    g_profiler_ints_irq8 = 0;   
    g_profiler_ints_irq9 = 0;   
    g_profiler_ints_irq10 = 0;  
    g_profiler_ints_irq11 = 0;  
    g_profiler_ints_irq12 = 0;  
    g_profiler_ints_irq13 = 0;  
    g_profiler_ints_irq14 = 0;  
    g_profiler_ints_irq15 = 0;  
    // ...


	//
	// As globais relativas à usuário são independentes do 
	// ambiente gráfico.
	//
	
	//Group, User.
	current_group = 0;
	current_user  = 0;
	
	//User Session, Window Station, Dasktop.
	current_usersession = 0;
	current_room = 0;
	current_desktop = 0;
	
	//Process, Thread.
	current_process = (int) 0;
	current_thread  = (int) 0;

	// Kernel.
    kernel_request = 0;


    // Globais no ambiente GUI.
    if ( g_useGUI == 1 ){

        // security layers.
        current_usersession = (int) 0;    // Current User Session.
        current_room = (int) 0;           // Current Room. (Window Station.)
        current_desktop = (int) 0;        // Current Desktop.
        
        // Window support.
        current_window = (int) 0;         // Current Window.
        windows_count = (int) 0;          // Window count.
        window_with_focus = (int) 0;      // Window with focus.
        current_menu = (int) 0;           // Current Menu.
        // Continua ...

        // windows, menus ...
        init_windows();
        init_menus();

        //Continua...
    }


    // Messages.
    g_new_message = 0;



    // FS type.
    // type 1, fat16.
    g_currentvolume_filesystem_type = FS_TYPE_FAT16;    
    g_currentvolume_fatbits = (int) 16;



	//===================
	
	// #importante:
	// provavelmente isso altere o comportamento do cursor,
	// levando o cursor par ao início da tela. Então precisamos
	// repintar o background para recomeçarmos.
	
	//printf("#breakpoint glob");
    //refresh_screen(); 
    //while(1){}	
	
	//#bugbug isso esta dando problemas.
#ifdef EXECVE_VERBOSE
	backgroundDraw ( (unsigned long) COLOR_BLUE ); 
#endif

	
	//printf("#breakpoint glob");
    //refresh_screen(); 
    //while(1){}
	
	//
	// Keyboard support.
	//
	
	//ldisc_init_modifier_keys();
	//ldisc_init_lock_keys();	
	
	//Continua ...

}


/*
 ******************************************
 * init:
 *     Base initializations.
 *     (Four phases).
 *     Isso foi chamado por systemStartUp() em execve/sm/system.c
 *   
 *    #todo: 
 *    Descrever aqui as fazer dessa rotina.
 */ 

int init (void){

    int Status = 0;


    debug_print ("==== init:\n");

    // Check kernel phase.

    if ( KeInitPhase != 0 ){
        debug_print ("init: KeInitPhase fail\n");
        panic ("init: KeInitPhase\n");
    }


	//
	// #IMPORTANT
	//

    // Globals.
    debug_print ("init: Globals\n");
    init_globals ();


	// #importante
	// À partir daqui podemos exibir strings na tela.


	
	
	
#ifdef EXECVE_VERBOSE
    printf ("sm-init-init: init_globals ok\n");     
#endif  

	
	//#bugbug:
	//Depois de iniciar as globais, provavelmente o cursor mude 
	//para o início da tela.
	//então após iniciarmos as globais temos que repintar o background e 
	// fazer um refresh da tela se a flag de verbose estiver ligada.
	
    //Object manager.	
#ifdef EXECVE_VERBOSE	
	printf ("sm-init-init: init_object_manager\n");
#endif


    debug_print ("init: Object manager\n");
    init_object_manager ();


    //i/o Manager.
#ifdef EXECVE_VERBOSE	
	printf("sm-init-init: ioInit\n");	
#endif	


    debug_print ("init: io manager\n");
    ioInit ();

    // Inicializa o gerenciamento de dispositivos.
    // Inicializa a lista de dispositivos.
    debug_print ("init: device manager\n");
    
    init_device_manager ();

    //
    // =================== ## STORAGE ## ===========================
    //

    // #ordem:
    // +storage
    // +disk
    // +volume 
    // +file system

	//#importante 
	//A estrutura 'storage' vai ser o nível mais baixo.
	//É nela que as outras partes devem se basear.
    debug_print ("init: storage structure\n");
    
    storage = (void *) kmalloc ( sizeof(struct storage_d) );

    if ( (void *) storage == NULL ){
       panic ("sm-init-init: storage");
    }


#ifdef EXECVE_VERBOSE
    printf ("sm-init-init: disk_init\n");
#endif  

    debug_print ("init: disk\n");
    disk_init ();


#ifdef EXECVE_VERBOSE
    printf("sm-init-init: volume_init\n");
#endif

    debug_print ("init: volume\n");
    volume_init ();


	
#ifdef EXECVE_VERBOSE	
	printf ("fsInit: VFS..\n");
#endif

    debug_print ("init: vfs\n");
    vfsInit ();


//deletar
#ifdef EXECVE_VERBOSE	
    printf ("sm-init-init: fsInit\n");
#endif   

    debug_print ("init: fs\n");
    fsInit ();


    // #todo
    // Mount root fs.
    // See: mountedList[] in sci/fs/fs.c
    // #test: Vamos tentar montar o volume root em mountedList[0].
    debug_print ("init: [FIXME] Initialize mounted list in fs.c\n");

    // Inicializa a lista.
    fs_initialize_mounted_list ();
        

#ifdef EXECVE_VERBOSE
    printf("sm-init-init: initialize_system_message_queue\n");
#endif

    initialize_system_message_queue (); 
    
    
	//
	// Network
	//

    debug_print ("init: network\n");
    networkInit ();

	

    //
    // Initialize Platform structure.
    //

#ifdef EXECVE_VERBOSE
    printf ("system-init: Platform\n");
#endif

    // #important
    // This is the Root struct. :)
    debug_print ("init: Platform struct\n");
    
    Platform = (void *) kmalloc ( sizeof(struct platform_d) );

    if ( (void *) Platform ==  NULL ){
        panic ("init: Platform\n");

    }else{

        // UP or MP.
        Platform->system_type = SYSTEM_TYPE_NULL;

        // Hardware
        Hardware = (void *) kmalloc ( sizeof(struct hardware_d) );

        if ( (void *) Hardware ==  NULL ){
            panic ("init: Hardware\n");

        }else{
            Platform->Hardware = (void *) Hardware;
            //printf(".");			
        };

		//Firmware
        Firmware = (void *) kmalloc ( sizeof(struct firmware_d) );

        if ((void *) Firmware ==  NULL ){
            panic ("sm-init-init: Firmware\n");

        }else{
            Platform->Firmware = (void *) Firmware;
            //printf(".");  			
        };

		
		//System (software)

		//
		// #IMPORTATE: 
		// Aqui estamos inicializando a estrutura do systema.
		//

        System = (void *) kmalloc ( sizeof(struct system_d) );

        if ( (void *) System ==  NULL ){
            panic ("init: System\n");

        }else{

            System->used = 1;    //Sinaliza que a estrutura esta em uso.
            System->magic = 1234; //sinaliza que a estrutura não esta corrompida.
            Platform->System = (void *) System;
            //printf(".");
        };

		//printf(" Done!\n");	
		//...
    };

	
	//Fase 1: Inicia a parte independente da arquitetura.
    Status = (int) init_architecture_independent ();
    if (Status != 0){
        panic ("init: init_architecture_independent fail\n"); 
    }
	KeInitPhase = 1;
    
	//Fase 2: Inicia a parte de arquitetura especifica da máquina atual.
	//        Ou seja, considera a marca do processador.
    Status = (int) init_architecture_dependent ();
    if (Status != 0){
        panic ("init: init_architecture_dependent fail\n"); 
    }



    // #importante
    // Só podemos carregar o diretório raiz depois que 
    // inicializamos o controlador de IDE e as estruturas de 
    // sistema de arquivos.

    debug_print ("init: load root dir.\n");
    fs_load_rootdir ();


    KeInitPhase = 2;


    //#debug
    // printf ("init: *breakpoint\n"); 
    // refresh_screen();
    // while(1){}	

	//
	//  ==============  #### LOGON #### ===============
	//

    debug_print ("init: logon\n");

	
	//printf("#breakpoint before logon");
	//refresh_screen();
	//while(1){}	
	
	//
	// Logon.
	//
	
	//Fase3: Logon. 
//Logon:

    //
    // Logon. 
    // Cria Background, main window, navigation bar.
    // de acordo com predefinição.
    //


    if ( g_useGUI == 1 )
    {

#ifdef EXECVE_VERBOSE
    printf ("sm-init-init: calling create_logon ...\n");
#endif
        create_logon ();

#ifdef EXECVE_VERBOSE
    printf ("sm-init-init: calling init_logon ...\n");
#endif
        //Libera. (Aceita argumentos).
        init_logon (0,0);    

        //Obs: *IMPORTANTE Usa-se o procedimento de janela do Logon.
    };

    KeInitPhase = 3; 



    //#debug
    //printf ("init: *breakpoint :) \n"); 
    //refresh_screen();
    //while(1){}


	// Continua ...
	

// * Fase 3:
// *     classe system.device.unblocked.
// *	   @todo: Inicializar dispositivos LPC/super io.
// *            Keyboard, mouse, TPM, parallel port, serial port, FDC. 
// *
 //* Fase 4:
 //*     classe system.device.unblocked.
 //*     @todo: Dispositivos PCI, ACPI ...
 //*
	
	
// Done.
//done:
    //printf("Done!\n");	
	//refresh_screen();
	//@todo: Deve retornar a variável Status.
	
	
#ifdef BREAKPOINT_TARGET_AFTER_INIT
    //#debug 
	//a primeira mensagem só aparece após a inicialização da runtime.
	//por isso não deu pra limpar a tela antes.
	printf("debug hang: after init");
	refresh_screen(); 
	while (1){ asm ("hlt"); }
#endif


    debug_print ("==== init: done\n");
    printf ("sm-init-init: done\n");

    return 0;  
}


//
// End.
//
