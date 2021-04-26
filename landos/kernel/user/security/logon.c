/*
 * File: user/logon.c
 *
 * 
 * Descri��o:
 *     Kernel Mode Logon Support Routines.
 *     @todo: Esse m�dulo deve prepara o ambiente para rodar o processo logon.bin.
 *     Esse logon pode ser usado par um eventual boot loader ou system installer.
 *
 *     Arquivo principal do m�dulo logon do executive.
 *     *IMPORTANTE: Esse � o ambiente de logon.
 *                  � onde o programa de logon vai rodar.
 *                  Cria um desktop para o Logon.
 *
 *     MB - M�dulos inclu�dos no Kernel Base.
 *     No momento aparece a janela do Shell, que � um processo em user mode.
 *     Esse shell que aparece no momento do logon servir� para
 *     configura��es. 
 *     No ambiente de logon o comando ser� passado para o procedimento do
 *     Shell.
 *
 *     Mesma coisa se o ambiente for a gui.(user environment).O comando
 *     deve ser passado para o Shell, para configura��es.
 *
 *     O Logon est� na WindowStation0 e no Desktop0. 
 *     O desktop do logon tem a main window e a navigation bar, mas pode 
 * ser predefido, assim como na cria��o da gui.
 *
 * Observa��o:
 *     � nesse momento, antes de ativar o sistema multitarefas que pode-se
 * instalar as atualiza��es ou configura��es pendentes.
 *     A pend�ncia de configura��es ou atualiza��es ser�o gravadas em arquivos
 * de configura��oou em metafiles, que ser�o lidos nesse momento.
 * 
 *
 * Obs: 
 * A tela de logon poderia, como op��o, apresentar as configura��es
 * gravadas em um metafile do sistema. Pois as configura��es s�o
 * realizadas nesse momento. 
 * Poderia mostrar configura��es salvas em vari�veis globais.
 *
 * IMPORTANTE: 
 * O logon deve ser um programa em user mode que chama rotinas aqui contidas.
 *
 * Quando logon virar um proceso em user mode:
 * +Registra o processo de logon
 * +Cria window stations e desktops. 
 *
 * History:
 *     2015 - Created by Fred Nora.
 */


#include <kernel.h>


//
// == prototypes (internal) =====================================
//

void logon_create_screen_window (void);
int ExitLogon (void);



/* 
 ***************************************************
 * init_logon_manager:
 * 
 *     Cria a interface gr�fica do Logon.
 *     � o ambiente onde o processo de logon deve rodar. 
 *
 *     Fundo -> Screen, Background.
 *     Logo  -> Sobreposto. 
 *     Navigation bar.
 *     Usu�rio.
 */

// It was called by KGWS_initialize() in kgws.c

int init_logon_manager (void){

    struct window_d  *hWindow; 
    int z=0;


	// #suspenso.
	// Suspendemos o uso de variaveis importadas do Makefile,
	// essa era o buffer delas.
	// char str_tmp[120];

    debug_print ("init_logon_manager:\n");


    // #test
    // Nesse momento a tela ainda esta azul,
    // quando o bg foi pintado pelo init_globals.
    // Hora de mudar isso ... par aa fase pos-azul,
    // onde retomam as mensagens de texto.
    // obs: Essa tela nao dura muito tempo,
    // pois logo vem a inicializa�ao das janelas.

    // #???
    // Ja fizemos isso na inicializaçao do kernel
    // Se fizermos novamente, ainda teremos strings
    // sujando a tela.

    //backgroundDraw ( (unsigned long) COLOR_BLACK ); 

	//
	// Aten��o
	//
	
	// #
	// Estamos come�ando um ambiente novo.
	// Vamos limpar a tela para as mensagens desse ambiente.
	// N�o ser� mais azul, igual quanto est�vamos iniciando o hardware
	// e nem preto como no bootloader.
	// Ser� uma cor mais clara.
	
	// Limpa a tela e reinicia o curso em (0,0);

    //backgroundDraw ( (unsigned long) COLOR_GRAY ); 

    kprintf ("\n");
    kprintf ("init_logon_manager: Initializing user environment!\n");
    kprintf ("\n");



    // debug
    //printf("L\n");
    //refresh_screen();
    //while(1){}


    // #todo:
    // Podemos mudar o nome dessa fun�ao para logonSetupVersion()

    kprintf ("init_logon_manager: Initialize version support \n");
    systemSetupVersion();

    //
    // gui structure. 
    //

    // #bugbug ?
    // Não sei se essa estrutura é inicializada em outr lugar também.

    // See: window.h

    gui = (void *) kmalloc ( sizeof(struct gui_d) );

    if ( (void *) gui == NULL){
        panic ("init_logon_manager: gui struct\n");
    }else{

        //
        // TTY
        //

	
	    // tty support.
	    // As mensagens do kernel precisam usar esses parametros.
	    // o kernel usa a tty0.


        // Limpa a lista
        printf ("init_logon_manager: Initializing tty module\n");
        tty_init_module();

        // Limpa a lista de terminais virtuais tamb�m.
        printf ("init_logon_manager: Initializing vt module\n");
        vt_init_module();


        // See: userenv.c
        User_initialize();


        // See: ws.h
        // hostname:Displaynumber.Screennumber
        // gramado:0.0

        // display and screen
        current_display = 0;
        current_screen  = 0;

        // window and menu.
        current_window  = 0;
        current_menu    = 0;    


        // Initializing zorder list.

        for ( z=0; z < KGWS_ZORDER_MAX; z++ )
        {
            Windows[z] = (unsigned long) 0;
        };
        zorderCounter = 0;



        // #test
        // Mostrando as mensagens antes de pintarmos a primeira janela.
        
        //#debug
        //breakpoint

        refresh_screen();
        //while(1){}



        // Inicia estrutura.
        // window.c

#ifdef KERNEL_VERBOSE
		printf ("init_logon_manager: initializing windows\n");   
#endif
        init_windows();


		//menus.
#ifdef KERNEL_VERBOSE
		printf("create_logon: initializing menus\n");
#endif
        init_menus();

	    // ...
    };

    // debug
    //printf("L\n");
    //refresh_screen();
    //while(1){}



    if ( (void *) CurrentUser == NULL ){
        panic ("init_logon_manager: CurrentUser\n");
    }



    //
    // The splash string !
    //

    kprintf ("init_logon_manager: Done\n"); 
    kprintf (":: Welcome to Gramado Operating System! ::\n"); 

    //printf("*breakpoint\n");
    //refresh_screen();
    //while(1){}

    // debug
    //printf("L: Gramado\n");
    //refresh_screen();
    //while(1){}



     //printf("*breakpoint\n");
     //refresh_screen();
     //while(1){}

    // This will create the screen window.
    // The screen window will be the main window too.

    logon_create_screen_window(); 

    if ( (void *) gui->screen == NULL ){
        panic("init_logon_manager: No sreen window\n");
    }

    if ( (void *) gui->main == NULL ){
        panic("init_logon_manager: No main window\n");
    }

    // Write something into the main window.


    // ##
    // Estamos suspendendo isso somente para termos
    // um fluxo contimuo de strings na inicializaçao
    // e nao uma parada para splash screen.
    
    /*
    if ( (void *) gui->main != NULL )
    {
        draw_text ( 
            gui->main, 8, 8, 
            COLOR_WHITE, "Gramado Operating System" );
    }
    */

    // ...

    // debug
    //printf("L: Gramado\n");
    //refresh_screen();
    //while(1){}


    //nao funciona
    //set_up_cursor(0,0);

    // done
    logonStatus      = TRUE;
    gui->initialised = TRUE;

    return 0;
}


/*
 *****************************************************
 * ExitLogon:
 *     Fecha o ambeinte de logon.
 *     @todo: logonExit();
 *     Isso pode ser chamado nas rotinas de 
 * reboot e shutdown.
 */


int ExitLogon (void)
{

    if ( (void *) gui == NULL )
    {
        panic("ExitLogon: gui\n");
    }

    if ( (void *) gui != NULL )
    {

        //CloseWindow();
		//...
		
		if ( (void *) gui->screen != NULL )
		{
			// ?
		    kgwmSetFocus (gui->screen);
	    }
		
		//...
    }
	
	//...
	
	logonStatus = 0;

    return 0;
}


/*
 **************************************
 * logon_create_screen_window:
 * 
 *     ( * ROOT WINDOW )
 * 
 *     Cria a tela. 
 *     Atribuindo as dimens�es.
 *     ...
 */


// #bugbug
// Mudar o nome de 'screen window' para 'root window'
// pis confunde com a entidade 'screen' usada em outros ambiente.

void logon_create_screen_window (void){

    struct window_d *hWindow;

    unsigned long Left   = 0;
    unsigned long Top    = 0;
    unsigned long Width  = (unsigned long) screenGetWidth();
    unsigned long Height = (unsigned long) screenGetHeight();


    if ( Width == 0 || Height == 0 ){
        panic("logon_create_screen_window: w h\n");
    }

	// Screen
	// Obs: N�o tem 'parent window' !!!

	// # minimized
	// n�o pode ser pintada nem repintada.

    hWindow = (void *) CreateWindow ( 
                           WT_SIMPLE, 0, VIEW_FULL, "Screen",
                           Left, Top, Width, Height, 
                           NULL, 0, 0, COLOR_GRAY ); 

    if ( (void *) hWindow == NULL ){
       panic ("logon_create_screen_window: hWindow\n");
    }else{
        if ( hWindow->used != TRUE || hWindow->magic != 1234 ){
            panic ("logon_create_screen_window: hWindow\n");
        }

        RegisterWindow(hWindow);

        if ( (void *) gui == NULL){
            panic ("logon_create_screen_window: gui\n");
        }else{
            gui->screen = (void *) hWindow;
            gui->main   = (void *) hWindow;

            // z order
            // Primeira janela da ordem;
            
            hWindow->z = 0;
            Windows[KGWS_ZORDER_BOTTOM] = (unsigned long) hWindow;

			// #debug
			// refresh_screen();
			// while(1){}

            show_window_rect(hWindow);
        };
    };
}



// Register logon process.
int register_logon_process ( pid_t pid )
{

    if ( pid<0 || pid >= PROCESS_COUNT_MAX )
    {
        debug_print("register_logon_process: [FAIL] pid\n");
        return -1;
    }

    if ( __gpidLogon != 0 ){
        debug_print("register_logon_process:\n");
        return -1;
    }

    // Global variable.

    __gpidLogon = (pid_t) pid;

    return 0;
}


//
// End.
//

