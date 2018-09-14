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
 * init_arquitecture_dependent:
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
int init_arquitecture_dependent (){
	
	int Status = 0;
	unsigned char Type;
	
	//
	// Fase. (Verificar se essa rotina foi chamada na fase certa de inicialização.)
    //
	
	if ( KeInitPhase != 1 ){
		panic("sm-init-init_arquitecture_dependent: KeInitPhase\n");	
	}


	// Os parâmetros de tela dependem das propriedades de hardware
	// como monitor e placa de vídeo.
	
	screenInit();

    //printf("init_arquitecture_dependent: #Debug");
    //refresh_screen();
    //while(1){};		
	
	
	//
	// * A estrutura para informações sobre o processador. 
	//
	
	// Check structure.
	if ( (void *) processor == NULL ){
	    panic("sm-init-init_arquitecture_dependent: processor\n");
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
		    panic ("sm-init-init_arquitecture_dependent: default Type\n");
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
 * init_arquitecture_independent:
 *    Rotina de inicialização da parte do sistema que é independente da 
 * arquitetura presente. Independente da tipo de processador. 
 * Obs: Essa é a fase 1 de inicialização.
 */
int init_arquitecture_independent (){
	
    int Status;
		
    if (KeInitPhase != 0){
		panic("sm-init-init_arquitecture_independent: KeInitPhase\n");
	}; 

	
	// Hal:
#ifdef KERNEL_VERBOSE	
	// Obs: Nesse momento deve haver alguma sondagem de dispositivos,
	//      salvando os parâmetros encontrados.
	//#bugbug @todo: Se é hal ... acho que leva em consideração a arquitetura.
	printf("Initializing Hal..\n");
#endif	
	Status = init_hal();	
	if(Status != 0){
	    panic("sm-init-init_arquitecture_independent: init_hal\n");
	};

	// Microkernel:
#ifdef KERNEL_VERBOSE
	// Obs: O Microkernel lida com informações dependentes da arquitetura,
	// porém inicializa a gerencia de processos e threads e de comunicação
	//entre processos.
	//#bugbug @todo: Se é microkernel é processo é registrador ... acho que leva em consideração a arquitetura.
	printf("Initializing Microkernel..\n");
#endif	
	Status = init_microkernel();
	if(Status != 0){
	    panic("sm-init-init_arquitecture_independent: init_microkernel\n");
	};
	
    // Executive:
#ifdef KERNEL_VERBOSE
	// Obs: O executive não é tão dependente da arquitetura, ele é
	//uma camada mais alta, porém será inicializado aqui para
	//efeito de ordem, já que estamos inicializando os tres módulos
	//básicos do kernel base nesse momento.
	printf("Initializing Executive..\n");
#endif	
	Status = init_executive();
	if(Status != 0){
	    panic("sm-init-init_arquitecture_independent: init_executive\n"); 
	};
	
	// Gramado:
#ifdef KERNEL_VERBOSE
    printf("Initializing Gramado..\n");
#endif
	Status = init_gramado();
	if(Status != 0){
	    panic("sm-init-init_arquitecture_independent: init_gramado\n"); 
	};
	
	//
	// User Info:
	// =========
	//
	// @todo: Usuário e sessão devem ser independentes do modo de vídeo. 
	//        Text ou Graphics.
	//

	//
	// @todo: Essas informações são independentes da arquitetura,
	//      Essa rotina pode ir pra outro lugar.
	//
UserInfo:
#ifdef KERNEL_VERBOSE	  
    printf("sm-init-init_arquitecture_independent: init_user_info\n");
#endif
    init_user_info();       //initialize user info structure.	
    
	
	//
	// User Session, Window Station and Desktop.
	// @todo: Essas informações são independentes da arquitetura,
	//      Essa rotina pode ir pra outro lugar.
	//
	
UserSession:
#ifdef KERNEL_VERBOSE	
    printf("sm-init-init_arquitecture_independent: init_user_session\n");   
#endif    
	init_user_session();    //initialize user session.	 
	
WindowStation:
#ifdef KERNEL_VERBOSE
    printf("sm-init-init_arquitecture_independent: init_window_station\n");   
#endif    
	init_window_station();

Desktop:
#ifdef KERNEL_VERBOSE 
    printf("sm-init-init_arquitecture_independent: init_desktop\n");   
#endif    
	init_desktop(); 
 
	
	// Window manager. - (Inicializa janelas e cria o logon).
	// @todo: Essas informações são independentes da arquitetura,
	//      Essa rotina pode ir pra outro lugar.
	
WindowManager:	

	//Caso não se use gui.
	if(g_useGUI != 1){
	    SetProcedure( (unsigned long) &system_procedure);		
	}else{
        
		// Window manager.
#ifdef KERNEL_VERBOSE	    
		printf("sm-init-init_arquitecture_independent: init_window_manager\n");
#endif	    
		init_window_manager();				
	};
	
	// tty support.
	ttyInit();

	//
	// terminal support.
	//
	
	//init_system_terminal();


    // Continua ...	 
	
done:
#ifdef KERNEL_VERBOSE
    //debug
    printf("Done\n");	
	//refresh_screen();
    //while(1){}
#endif	
    return (int) 0;
};


/*
 **************************************************
 * Init globals: 
 *     Inicia variáveis globais do Kernel Base.
 *     Obs: Inicializar por categorias.
 */
void init_globals (){

#ifdef KERNEL_VERBOSE	
    printf("sm-init-init_globals:\n");	
#endif

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
	current_windowstation = 0;
	current_desktop = 0;
	
	//Process, Thread.
	current_process = (int) 0;
	current_thread  = (int) 0;	   
	
	// Kernel.
	kernel_request = 0;
	
	// System.
	// @todo:
	
	
	//Globais no ambiente GUI.
	if ( g_useGUI == 1 ){
		
		//Próximo procedimento de janela.
	    g_next_proc = (unsigned long) &system_procedure; 
		
		//Windows globals.
		current_usersession = (int) 0;    //>Current User Session.
		current_windowstation = (int) 0;  //>>Current Window Station.
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
	
	
	//
	// Keyboard support.
	//
	
	//ldisc_init_modifier_keys();
	//ldisc_init_lock_keys();	
	
	//Continua ...

// Done.
//done:	
    //return;
};


/*
 ******************************************
 * init:
 * Base initializations. (Four phases).
 */ 
int init (){
	
    int Status = 0;
	
	//Check kernel phase.
	if ( KeInitPhase != 0 ){
		printf("sm-init-init: KeInitPhase\n");
        die();		
	}
 
    //Globals.
#ifdef KERNEL_VERBOSE	
	printf("sm-init-init: init_globals\n");     
#endif    
	init_globals();
	
    //Object manager.	
#ifdef KERNEL_VERBOSE	
	printf("sm-init-init: init_object_manager\n");
#endif	
	init_object_manager();
	
	//i/o Manager.
#ifdef KERNEL_VERBOSE	
	printf("sm-init-init: ioInit\n");	
#endif	
	ioInit();
	
	//Disk manager, volume manager and fs manager.
	
#ifdef KERNEL_VERBOSE	
	printf("sm-init-init: disk_init\n");
#endif    
	disk_init();
	
#ifdef KERNEL_VERBOSE	
	printf("sm-init-init: volume_init\n");
#endif    
	volume_init();
	
	
	
#ifdef KERNEL_VERBOSE	
	printf("fsInit: VFS..\n");
#endif
	
	vfsInit();
	
	
	
#ifdef KERNEL_VERBOSE	
	printf("sm-init-init: fsInit\n");
#endif    
	fsInit();
	
		
    //System folders.
    // ??@todo: /ux4 .../ux1	
#ifdef KERNEL_VERBOSE	
	printf("sm-init-init: create_system_folders\n");
#endif	
	create_system_folders(); 
    

#ifdef KERNEL_VERBOSE	
	printf("sm-init-init: initialize_system_message_queue\n");
#endif	
	initialize_system_message_queue(); 
	
    //
	// Initialize Platform structure.
	//
	
#ifdef KERNEL_VERBOSE
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

	
	//Fase 1: Inicia a parte independente da arquitetura.
	Status = (int) init_arquitecture_independent();
	if(Status != 0){
	   //Nothing for now.
	};
	KeInitPhase = 1;
    
	//Fase 2: Inicia a parte de arquitetura especifica da máquina atual.
	//        Ou seja, considera a marca do processador.
    Status = (int) init_arquitecture_dependent();	 
    if(Status != 0){
	    //Nothing for now.
	};
	KeInitPhase = 2;

	
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

	if ( g_useGUI == 1 ){
		
#ifdef KERNEL_VERBOSE		
		printf("sm-init-init: Logon\n");
#endif	    
		create_logon();
		init_logon(0,0);    //Libera. (Aceita argumentos).

        //Obs: *IMPORTANTE Usa-se o procedimento de janela do Logon.		
	};	
	KeInitPhase = 3; 
			
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
    return (int) 0;  
};


/*
int initInit()
{
	
}
*/

//
// End.
//
