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
 * save_kernel_args:
 *     Salvando em estrutura os argumentos recebidos.
 */
void save_kernel_args (){
	
    //KernelArgs.arg1 = ;
    //KernelArgs.arg2 = ;
	//KernelArgs.arg3 = ;
	//KernelArgs.arg4 = ;
	
    //return;
};


/*
 * boot:
 *     @todo: Propósito ??
 *            Boot de alguma partição.(volume) 
 *            Boot do volume sinalizado.
 *            Identificar volumes.
 */
void boot (){
    
	panic("sm-init-boot:");	
};	


/*
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

int init_architecture_dependent (){
	
	int Status = 0;
	unsigned char Type;
	
	
	debug_print("init_architecture_dependent\n");
	
	//
	// Fase. (Verificar se essa rotina foi chamada na fase certa de inicialização.)
    //
	
	if ( KeInitPhase != 1 ){
		panic("sm-init-init_architecture_dependent: KeInitPhase\n");	
	}

	// #### IMPORTANTE ####
	//
	// VAMOS ANTECIPAR ESSA INICIALIZAÇÃO NA TENTATIVA DE
	// ANTECIPARMOS O USO DE MENSAGENS.
    // >>> mas essa rotina precisa do malloc ,,,
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
	if ( (void *) processor == NULL ){
	    panic("sm-init-init_architecture_dependent: processor\n");
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
	
	
	//Inicializando o Process manager.
	init_process_manager();
	
 //
 // Continua ...
 //
	
//
// Done.
//

//done:

    return (int) Status;
};



/*
 ******************************************************************
 * init_architecture_independent:
 *
 *    Rotina de inicialização da parte do sistema que é independente da 
 * arquitetura presente. Independente da tipo de processador. 
 *    Obs: Essa é a fase 1 de inicialização.
 */

int init_architecture_independent (){
	
    int Status;
	
	debug_print ("init_architecture_independent\n");
		
    if (KeInitPhase != 0){
		panic("sm-init-init_architecture_independent: KeInitPhase\n");
	}; 

	
	//
	//  ## HAL ##
	//
    
	// #bugbug
	// Se é HAL é dependente da arquitetura.
	// Isso deveria ficar na outra rotina.
	// Não mudaremos por enquanto.
	
	
	Status = init_hal ();	
	
	if (Status != 0)
	{
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
	printf("Initializing Microkernel..\n");
#endif	
	
	Status = init_microkernel ();
	
	if (Status != 0)
	{
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
	printf("Initializing Executive..\n");
#endif	
	
	Status = init_executive ();
	
	if (Status != 0)
	{
	    panic ("init-init_architecture_independent: init_executive\n"); 
	}
	
	//
	// ## GWS ?? ##
	//
	
	// Gramado:
#ifdef EXECVE_VERBOSE
    printf("Initializing Gramado..\n");
#endif
	
	Status = init_gramado ();
	
	if (Status != 0)
	{
	    panic ("init-init_architecture_independent: init_gramado\n"); 
	}
	

	// User Info:
	// =========
	//
	// @todo: Usuário e sessão devem ser independentes do modo de vídeo. 
	//        Text ou Graphics.
	// @todo: Essas informações são independentes da arquitetura,
	//      Essa rotina pode ir pra outro lugar.
	
UserInfo:
#ifdef EXECVE_VERBOSE	  
    printf ("init-init_architecture_independent: init_user_info\n");
#endif
	
	//initialize user info structure.
    init_user_info ();       	
    
	// User Session, Window Station and Desktop.
	// @todo: Essas informações são independentes da arquitetura,
	//      Essa rotina pode ir pra outro lugar.
	
UserSession:
#ifdef EXECVE_VERBOSE	
    printf ("init-init_architecture_independent: init_user_session\n");   
#endif
	
	//initialize user session.
	init_user_session();   	 
	
	
	// (ROOM)
	
WindowStation:
#ifdef EXECVE_VERBOSE
    printf ("init-init_architecture_independent: init_window_station\n");   
#endif  
	
	init_room_manager();

	// DESKTOP
	
Desktop:
#ifdef EXECVE_VERBOSE
    printf ("init-init_architecture_independent: init_desktop\n");   
#endif    
	
	init_desktop(); 
 
	
	//
	//  ## WINDOWS ##
	//
	
	// Window manager. 
	// (Inicializa janelas e cria o logon).
	// @todo: 
	// Essas informações são independentes da arquitetura,
	// Essa rotina pode ir pra outro lugar.
	
WindowManager:	

	//Caso não se use gui.
	
	if (g_useGUI != 1)
	{
	    SetProcedure ( (unsigned long) &system_procedure);		
		
		// #BUGBUG
		// Aqui cacelamos a inicialização do window manager
		// caso não estejamos no modo gráfico.
		// Como não temos suporte para modo texto, deveríamos abortar.
		
	}else{
        
		// Window manager.
#ifdef EXECVE_VERBOSE	    
		printf ("init-init_architecture_independent: init_window_manager\n");
#endif
		
		init_window_manager ();	
		
		
	};
	
	
	
	// tty support.
	ttyInit();

	
	
	//
	// terminal support.
	//
	
	//init_system_terminal();


    // Continua ...	 
	
	
	
done:
	
#ifdef EXECVE_VERBOSE
    //debug
    printf("Done\n");	
	//refresh_screen();
    //while(1){}
#endif	
	
    return (int) 0;
}


/*
 **************************************************
 * Init globals: 
 *     Inicia variáveis globais do Kernel Base.
 *     Obs: Inicializar por categorias.
 */
void init_globals (){

#ifdef EXECVE_VERBOSE	
    //printf("sm-init-init_globals:\n");
	debug_print("init_globals:\n");
#endif
	
	
	//Outros.
	errno = 0;
	
	//alocando memória para as estruturas do fluxo padrão.
	stdin = (void *) malloc( sizeof(FILE) );
	stdout = (void *) malloc( sizeof(FILE) );
	stderr = (void *) malloc( sizeof(FILE) );
	
	//kstdin  = (void*) malloc( sizeof(FILE) );
	//kstdout = (void*) malloc( sizeof(FILE) );
	//kstderr = (void*) malloc( sizeof(FILE) );
	
    //inicializa as estruturas do fluxo padrão.	
	stdioInitialize();
	
	
	//#importante
	//>>> é a partir daqui que temos mensagens!!!
	
    screenInit();
	
	//
	// ## FIRST MESSAGE !! ##
	//
	
	debug_print("init_globals: WE HAVE MESSAGES NOW !!!\n");
	printf("init_globals: first message!\n");
	
	
    //===================	
	//vamos atrazar configuração de janela em favor de configuração de mensagem

	//Atalho para a próxima mensagem de teclado..(test) debug
	gNextKeyboardMessage = (int) 0;
	
	//Essa flag bloqueia e impede que uma janela obtenha o foco.
	gFocusBlocked = (int) 0;
	
	//
	// As globais relativas à usuário são independentes do ambiente gráfico.
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
	
	// System.
	// @todo:
	
	
	//Globais no ambiente GUI.
	if ( g_useGUI == 1 )
	{
		//NÃO PRECISAMOS MAIS DISSO, DELETAR;
		//Próximo procedimento de janela.
	    g_next_proc = (unsigned long) &system_procedure; 
		
		//Windows globals.
		current_usersession = (int) 0;    //>Current User Session.
		current_room = (int) 0;  //>>Current Window Station.
	    current_desktop = (int) 0;        //>>>Current Desktop.
		current_window = (int) 0;         //>>>>Current Window.
	    windows_count = (int) 0;          //Window count.
	    window_with_focus = (int) 0;      //Window with focus.
		current_menu = (int) 0;           //Current Menu.
        //Continua...	

		// windows, menus ...
		init_windows();
        init_menus();	
	
        //Continua...		
	};
		
	
	//Messages.
	g_nova_mensagem = 0;
	g_new_message = 0;
	
    //FS type.	
	g_file_system_type = FS_TYPE_FAT16;	//tipo 1, fat16.
	fatbits = (int) 16;
	
	//===================	
	
	// #importante:
	// provavelmente isso altere o comportamento do cursor,
	// levando o cursor par ao início da tela. Então precisamos
	// repintar o background para recomeçarmos.
	
	//printf("#breakpoint glob");
    //refresh_screen(); 
    //while(1){}	
	
	
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

};


/*
 ******************************************
 * init:
 * Base initializations. (Four phases).
 */ 
int init (){
	
    int Status = 0;
	
	debug_print("init:\n");
	
	
	
	
	
	//#debug : ISSO FUNCIONOU ... 
	
	//printf ("++++++++++++++++++++++++ init:  ++++++++++++++++++++++++++++++\n");
    //refresh_screen(); 
    //while(1){}	
	
	
	
	
	
	//Check kernel phase.
	if ( KeInitPhase != 0 )
	{
		debug_print("init: KeInitPhase fail\n");
		panic ("sm-init-init: KeInitPhase\n");
        //die();		
	}
	
	
	//
	// ### IMPORTANTE ###
	//
	
	
    //Globals.
	init_globals();
	
//#ifdef EXECVE_VERBOSE	
	printf("sm-init-init: init_globals ok\n");     
//#endif  
	
	
	//#bugbug:
	//Depois de iniciar as globais, provavelmente o cursor mude 
	//para o início da tela.
	//então após iniciarmos as globais temos que repintar o background e 
	// fazer um refresh da tela se a flag de verbose estiver ligada.
	
    //Object manager.	
#ifdef EXECVE_VERBOSE	
	printf("sm-init-init: init_object_manager\n");
#endif	
	init_object_manager();
	
	//i/o Manager.
#ifdef EXECVE_VERBOSE	
	printf("sm-init-init: ioInit\n");	
#endif	
	ioInit();
	
	
	//#debug :  
	//breakpoint ante de começar as questoes de disco.
    // ok isso funcionou
    
	//printf ("++++++++++++++++++++++++ init:  ++++++++++++++++++++++++++++++\n");
    //refresh_screen(); 
    //while(1){}		
	
	
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
		
	storage = (void *) malloc ( sizeof(struct storage_d) );
	if ( (void *) storage == NULL ){
	    panic ("sm-init-init: storage");
	}	
	
		
#ifdef EXECVE_VERBOSE	
	printf("sm-init-init: disk_init\n");
#endif    
	disk_init();
	
#ifdef EXECVE_VERBOSE	
	printf("sm-init-init: volume_init\n");
#endif    
	volume_init();
	
	
	
#ifdef EXECVE_VERBOSE	
	printf("fsInit: VFS..\n");
#endif
	
	vfsInit();
	
	
//deletar	
#ifdef EXECVE_VERBOSE	
	//printf("sm-init-init: fsInit\n");
#endif    
	fsInit();
	
		
    //System folders.
    //#bugbug; Onde estamos criando isso.
	
#ifdef EXECVE_VERBOSE	
	printf("sm-init-init: create_system_folders\n");
#endif	
	create_system_folders(); 
    
    
    
    
    
    
    
    

#ifdef EXECVE_VERBOSE	
	printf("sm-init-init: initialize_system_message_queue\n");
#endif	
	initialize_system_message_queue(); 
	
	
    
    
	//#debug :  
	//breakpoint ante de começar as questoes de network
    //ok isso funcionou.
    
	//printf ("++++++++++++++++++++++++ init:  ++++++++++++++++++++++++++++++\n");
    //refresh_screen(); 
    //while(1){}		
    
    
    

	//
	// Network
	//
	
	networkInit ();
	
	
	
    //
	// Initialize Platform structure.
	//
	
#ifdef EXECVE_VERBOSE
	printf("sm-init-init: Platform\n");	
#endif

	Platform = (void *) malloc( sizeof(struct platform_d) );
	
	if( (void *) Platform ==  NULL )
	{
		// # This is the Root struct #
		panic("sm-init-init: Platform\n");	
	
	}else{
		
		//Hardware
	    Hardware = (void *) malloc( sizeof(struct hardware_d) );
	    if( (void *) Hardware ==  NULL ){
		    printf("sm-init-init: Hardware\n");	
	        die();
		}else{
		    Platform->Hardware = (void *) Hardware;
            //printf(".");			
		};
		
		//Firmware
	    Firmware = (void *) malloc( sizeof(struct firmware_d) );
	    if( (void *) Firmware ==  NULL ){
		    printf("sm-init-init: Firmware\n");	
	        die();
		}else{
		    Platform->Firmware = (void *) Firmware;
            //printf(".");  			
		};

		
		//System (software)
	    
		//
		// *IMPORTATE: Aqui estamos inicializando a estrutura do systema.
		//
		
		System = (void *) malloc( sizeof(struct system_d) );
	    if( (void *) System ==  NULL ){
		    printf("sm-init-init: System\n");	
	        die();
		}else{
			
			System->used = 1;    //Sinaliza que a estrutura esta em uso.
			System->magic = 1234; //sinaliza que a estrutura não esta corrompida.
			
		    Platform->System = (void *) System;
            //printf(".");			
		};
		
		//printf(" Done!\n");	
		//...
	};
	
	//fail
	//printf("#breakpoint before independent");
	//refresh_screen();
	//while(1){}		

	
	//Fase 1: Inicia a parte independente da arquitetura.
	Status = (int) init_architecture_independent();
	if(Status != 0){
	   //Nothing for now.
	};
	KeInitPhase = 1;
	
	//fail
	//printf("#breakpoint before dependent");
	//refresh_screen();
	//while(1){}	
    
    
 	//#debug :  
	//breakpoint depois de arch independent. gigabyte/intel
	//rodou atá aqui ... porém nao sabemos se todos
	//os dispositivos pci forar listados e se a gerencia de janelas
	//inicializou corretamente.
	
	//printf ("++++++++++++++++++++++++ init:  ++++++++++++++++++++++++++++++\n");
    //refresh_screen(); 
    //while(1){}		

   

	
    
	//Fase 2: Inicia a parte de arquitetura especifica da máquina atual.
	//        Ou seja, considera a marca do processador.
    Status = (int) init_architecture_dependent();	 
    if(Status != 0){
	    //Nothing for now.
	};
	
	
 	//#debug :  
	//breakpoint depois de arch dependent
	//ok..rodou ate' aqui ... mas nao sabemos se fez um bom trabalho.
	
	//printf ("++++++++++++++++++++++++ init:  ++++++++++++++++++++++++++++++\n");
    //refresh_screen(); 
    //while(1){}		

	
	
	
	
	// #importante
	// So podemos carregar o diretorio raiz depois que inicializamos o 
    // controlador de IDE e as estruturas de sistema de arquivos.
	
	fs_load_rootdir ();
	
	
	KeInitPhase = 2;

	
	
	
	
 	//#debug :  
	//breakpoint antes do logon
	//rodou ate' aqui.
	
	//printf ("++++++++++++++++++++++++ init:  ++++++++++++++++++++++++++++++\n");
    //refresh_screen(); 
    //while(1){}		

	
	
	
    //
	//  ==============  #### LOGON #### ===============
	//
	
	
	
	
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
		printf("sm-init-init: Logon\n");
#endif	    
		
		create_logon ();
		
		//Libera. (Aceita argumentos).
		init_logon (0,0);    

        //Obs: *IMPORTANTE Usa-se o procedimento de janela do Logon.		
	};	
	KeInitPhase = 3; 
			
	
	
	
 	//#debug :  
    // isso funcionou. gigabyte/intel
	
	//printf ("++++++++++++++++++++++++++++++++++++++++++++++++ init: ++++++\n");
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
	printf(">>>debug hang: after init");
	refresh_screen(); 
	while (1){
		asm ("hlt");
	}
#endif	
	
	
	
    return (int) 0;  
};


 

//
// End.
//
