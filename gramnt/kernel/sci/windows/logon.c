/*
 * File: logon.c
 *
 * Descrição:
 *     Kernel Mode Logon Support Routines.
 *     @todo: Esse módulo deve prepara o ambiente para rodar o processo logon.bin.
 *     Esse logon pode ser usado par um eventual boot loader ou system installer.
 *
 *     Arquivo principal do módulo logon do executive.
 *     *IMPORTANTE: Esse é o ambiente de logon.
 *                  É onde o programa de logon vai rodar.
 *                  Cria um desktop para o Logon.
 *
 *     MB - Módulos incluídos no Kernel Base.
 *     No momento aparece a janela do Shell, que é um processo em user mode.
 *     Esse shell que aparece no momento do logon servirá para
 *     configurações. 
 *     No ambiente de logon o comando será passado para o procedimento do
 *     Shell.
 *
 *     Mesma coisa se o ambiente for a gui.(user environment).O comando
 *     deve ser passado para o Shell, para configurações.
 *
 *     O Logon está na WindowStation0 e no Desktop0. 
 *     O desktop do logon tem a main window e a navigation bar, mas pode 
 * ser predefido, assim como na criação da gui.
 *
 * Observação:
 *     É nesse momento, antes de ativar o sistema multitarefas que pode-se
 * instalar as atualizações ou configurações pendentes.
 *     A pendência de configurações ou atualizações serão gravadas em arquivos
 * de configuraçãoou em metafiles, que serão lidos nesse momento.
 * 
 *
 * Obs: A tela de logon poderia, como opção, apresentar as configurações
 *      gravadas em um metafile do sistema. Pois as configurações são
 *      realizadas nesse momento. 
 *      Poderia mostrar configurações salvas em variáveis globais.
 *
 *      *IMPORTANTE: O logon deve ser um programa em user mode que chama rotinas aqui contidas.
 *
 * Quando logon virar um proceso em user mode:
 * +Registra o processo de logon
 * +Cria window stations e desktops. 
 *
 * History:
 *     2015 - Created by Fred Nora.
 *     2016 - Revision.
 */
 
 
#include <kernel.h>



//Variáveis internas.
//int logonStatus;
//...


// Internas.
void logon_create_screen (void);
void logon_create_background (void);
void logon_create_logo (void);
void logon_create_taskbar (void);
void logon_create_mainwindow (void);
void logon_create_controlmenu (void);
void logon_create_infobox (void);
void logon_create_messagebox (void);
void logon_create_debug (void);
void logon_create_navigationbar (void);
void logon_create_grid (void);
void logon_create_developer_screen (void);
int ExitLogon (void);






/* 
 ***************************************************
 * init_logon_manager:
 * 
 *     Cria a interface gráfica do Logon.
 *     É o ambiente onde o processo de logon deve rodar. 
 *
 *     Fundo -> Screen, Background.
 *     Logo  -> Sobreposto. 
 *     Navigation bar.
 *     Usuário.
 */

int init_logon_manager (void){


    struct window_d *hWindow; 
    int z=0;


	// #suspenso.
	// Suspendemos o uso de variaveis importadas do Makefile,
	// essa era o buffer delas.
	// char str_tmp[120];	 

    debug_print ("init_logon_manager\n");

	
	//
	// Atenção
	//
	
	// #
	// Estamos começando um ambiente novo.
	// Vamos limpar a tela para as mensagens desse ambiente.
	// Não será mais azul, igual quanto estávamos iniciando o hardware
	// e nem preto como no bootloader.
	// Será uma cor mais clara.
	
	// Limpa a tela e reinicia o curso em (0,0);
	// Isso funcionou em init.c
    backgroundDraw ( (unsigned long) COLOR_GRAY ); 

    kprintf ("*\n");
    //kprintf ("**\n");
    kprintf ("init_logon_manager: Initializing user environment!\n");
    //kprintf ("**\n");
    kprintf ("*\n");


	//g_guiMinimal = 1;
	
	// Disable interrupts, lock task switch and scheduler.
	
	asm ("cli");
	set_task_status(LOCKED); 
	scheduler_lock();

	//
	// GUI Structure. 
	//

    gui = (void *) kmalloc ( sizeof(struct gui_d) );

    if ( (void *) gui == NULL)
    {
        panic ("init_logon_manager: gui struct");

    }else{

        //
        // TTY
        //

	
	    // tty support.
	    // As mensagens do kernel precisam usar esses par^ametros.
	    // o kernel usa a tty0.
	
	    //#importante
	    //Logo antes user session, room e desktop.
	    //Assim essas informaç~oes ficar~ao na estrutura de tty.
	    //assim saberemos qual usu'ario est'a usando a tty0
	    // deve ser o 'root'.


        // Limpa a lista
        printf ("init_logon_manager: Initializing tty module\n");
        tty_init_module();

        // Limpa a lista de terminais virtuais também.
        printf ("init_logon_manager: Initializing vt module\n");
        vt_init_module();



	// =========
	//
	// @todo: Usuário e sessão devem ser independentes do modo de vídeo. 
	//        Text ou Graphics.
	// @todo: Essas informações são independentes da arquitetura,
	//      Essa rotina pode ir pra outro lugar.
	
//UserInfo:
	
//#ifdef EXECVE_VERBOSE	  
    //printf ("init_user_info\n");
//#endif


        // Initialize user info structure
        printf ("init_logon_manager: init_user_info\n");
        init_user_info ();   

        // See: ws.h
        // hostname:Displaynumber.Screennumber
        // gramado:0.0

        // display and screen
        current_display = 0;
        current_screen = 0;
        
        // User session, room (Window Station), desktop, 
        current_usersession = 0;    
        current_room = 0;           
        current_desktop = 0;        

        // window and menu.
        current_window = 0;        
        current_menu = 0;          

        // Initializing zorder list.

        for ( z=0; z < KGWS_ZORDER_MAX; z++ ){
            Windows[z] = (unsigned long) 0;
        }
        zorderCounter = 0;


		// Initialize user Session, room and Desktop.
  
		//user section.
#ifdef KERNEL_VERBOSE		
		printf ("init_logon_manager: initializing user session\n");
#endif
		init_user_session ();

		//initialize window station default.
#ifdef KERNEL_VERBOSE
		printf ("init_logon_manager: initializing room\n");   
#endif
		init_room_manager ();	

	    //initialize desktop default.
#ifdef KERNEL_VERBOSE
		printf ("init_logon_manager: initializing desktop\n");   
#endif
		init_desktop ();





	    //Inicia estrutura.
		//window.c

#ifdef KERNEL_VERBOSE
		printf ("init_logon_manager: initializing windows\n");   
#endif
		init_windows (); 


		//menus.
#ifdef KERNEL_VERBOSE
		printf("create_logon: initializing menus\n");
#endif
		init_menus();        

	    //...
	};


    //#debug
   // printf ("create_logon: *breakpoint\n"); 
   // refresh_screen();
    //while(1){}


	
	// Configura elementos da tela de login.
    
    if ( g_guiMinimal == 1 )
    {
        SetLogonParameters (0,1,1,0,0,1,0,0,0,0,0,0);

    }else{

        SetLogonParameters(0,  //refresh         
                           1,  //*screen          
                           1,  //*background       
                           0,  //logo            
                           0,  //taskbar (autoriza e prepara para a utilização de uma taskbar.)        
                           1,  //*Main.(Desktop window, Área de trabalho)            
                           0,  //menu           
                           0,  //infobox         
                           0,  //messagebox       
                           0,  //debug           
                           0,  //navigationbar    
                           0); //grid (autoriza e prepara para a utilização de um grid)	
    };

    //
    // ## Draw windows ##
    //

draw_logon_stuff:

    printf ("init_logon_manager: Draw..\n");   

    // Root window !
    // Screen, Background and Logo. 

    if (gui->screenStatus == 1){ 
        logon_create_screen (); 
    }


	/*
	if (gui->backgroundStatus == 1)
	{
	    logon_create_background (); 
	}
	*/

    /*
	if (gui->logoStatus == 1)
	{ 
	    logon_create_logo (); 
	}
	*/

    /*
	//Taskbar, Control menu and Messagebox.
    if (gui->taskbarStatus == 1)
    {
	    logon_create_taskbar (); 
	}
	*/

    /*
    if (gui->menuStatus == 1)
    { 
	    logon_create_controlmenu (); 
	}
	*/
	
	/*
    if (gui->messageboxStatus == 1)
    { 
	    logon_create_messagebox (); 
	}
	*/

    // Main window.
    // Destop. That area for applications.
    if (gui->mainStatus == 1){ 
        logon_create_mainwindow (); 
    }


    /*
    if (gui->navigationbarStatus == 1)
    { 
	    logon_create_navigationbar (); 
	}
	*/
	
	/*
    if (gui->gridStatus == 1)
    { 
	    logon_create_grid (); 
	}
	*/

	//draw_text( gui->main, 400 +8, 8*2, 
	   //COLOR_RED, "Gramado Operating System" );
			    
    //printf ("create_logon: *breakpoint"); 
	//refresh_screen();
	//while(1){}
	
	//
	// ## Strings ##
	//

    if ( (void *) CurrentUser != NULL )
    {

		// Obs: 
		// As mensagens aqui são para auxiliar 
		// o desenvolvedor no processo de inicialização.
		//@todo: Informar o desktop atual.
			
        if (g_guiMinimal != 1)
        {


/*
#ifdef IMPORTED_VARIABLES	
            //=======================================
            // #Warning                            //
            // Variables imported from Makefile    //
            //=======================================
			
			sprintf(str_tmp, "Gramado %d.%d%s (%s)",  
				GRAMADO_VERSION, 
				GRAMADO_PATCHLEVEL,
				GRAMADO_EXTRAVERSION,
				GRAMAD0_NAME );

			draw_text( gui->main, 400 +8, 8*1, 
			    COLOR_WHITE, str_tmp );
#endif
*/

            if ( (void *) gui->main != NULL ){
			draw_text( gui->main, 400 +8, 8*2, 
			    COLOR_WHITE, "Gramado Operating System" );
			
			draw_text( gui->main, 400 +8, 8*3, 
			    COLOR_WHITE, "(under construction) ");
				
			draw_text( gui->main, 400 +8, 8*4, 
			    COLOR_WHITE, "(This is the enviroment to run logon process)" );
		    }
		    
			//...
 	        
			//draw_text(gui->screen, 640/2, 8, COLOR_WHITE, "Press F1 to Log on");
	
			//Opções:
			//StatusBar( gui->screen, "Logon", "Press F1 to start User Environment or F2 to Reboot");
			//Message Box.
			//...
			//
	    };
		//Nothing.
	};
	


	//
	// Done 
	//


done:

    logonStatus = 1;
    
    gui->initialised = 1;

    printf ("init_logon_manager: Done\n"); 
    
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

int ExitLogon (void){


    if ( (void *) gui != NULL )
    {
        //CloseWindow();
		//...
		
		if ( (void *) gui->screen != NULL )
		{
			// ?
		    SetFocus (gui->screen);
	    }
		
		//...
    }
	
	//...
	
	logonStatus = 0;

    return 0;
}


/*
 ******************************************
 * SetGuiParameters:
 *     Configura a inicialização das janelas 
 * gerenciadas pelo kernel.
 *     @todo: Limite de janelas (+- 10)
 */


void 
SetLogonParameters ( 
    int refresh,         // Flag. Colocar ou não o backbuffer na tela.
    int screen,          // Tela do computador.
    int background,      // Background da area de trabalho. 
    int logo,            // Logo, Janela para imagem da area de trabalho.
    int taskbar,         // Barra de tarefas.(icones para programas)
    int main,            // Janela principal.( Desktop, ou Kernel Setup Utility ) 
    int menu,            // Control menu da Área de trabalho.
    int infobox,         // Janelinha no canto, para alerta sobre sobre eventos ocorridos no sistema.
    int messagebox,      // O message box do kernel.(cada app cria seu messagebox.) 
    int debug,           // Janela do debug do kernel.(sonda por problemas)
    int navigationbar,   // Janela de navegação(semelhante a navigation bar dos dispositivos mobile) 
    int grid )           // Grid da janela principal.
{


    if( (void*) gui == NULL ){
        printf ("SetLogonParameters: fail\n");
        //refresh_screen();
        return;

    }else{
		
	    gui->refresh = refresh; 
	    gui->screenStatus = screen;
	    gui->backgroundStatus = background; 
	    gui->mainStatus = main; 
	    gui->logoStatus = logo;
	    gui->taskbarStatus = taskbar;
	    gui->menuStatus = menu;
	    gui->infoboxStatus = infobox;
	    gui->messageboxStatus = messagebox;
	    gui->debugStatus = debug;
	    gui->navigationbarStatus = navigationbar; 
	    gui->gridStatus = grid;  
	    // ...

    };

    //return;
}


/*
 **************************************
 * logon_create_screen:
 * 
 *     ( * ROOT WINDOW )
 * 
 *     Cria a tela. 
 *     Atribuindo as dimensões.
 *     ...
 */

void logon_create_screen (void){

    struct window_d *hWindow; 

    unsigned long Left = 0;
    unsigned long Top = 0;
    unsigned long Width = (unsigned long) screenGetWidth();
    unsigned long Height = (unsigned long) screenGetHeight();


	// Screen
	// Obs: Não tem 'parent window' !!!

	// # minimized
	// não pode ser pintada nem repintada.

    //#bugbug
    //Tá falhando na máquina real mais ou menos nessa hora.
    // vamos testar minimizada como antes, quando funcionava,

    //hWindow = (void *) CreateWindow ( WT_SIMPLE, 0, VIEW_FULL, "Screen", 
    hWindow = (void *) CreateWindow ( 1, 0, VIEW_MINIMIZED, "Screen", 
                           Left, Top, Width, Height, 
                           NULL, 0, 0, COLOR_BLACK );  


    if ( (void *) hWindow == NULL ){
       panic ("logon_create_screen:");

    }else{

        if ( hWindow->used != 1 || hWindow->magic != 1234 ){
            panic ("logon_create_screen: hWindow\n");
        }

        RegisterWindow (hWindow);

        if ( (void *) gui == NULL){
            panic ("logon_create_screen: gui");

        }else{

            gui->screen = (void *) hWindow;

			// z order
			// Primeira janela da ordem;
            hWindow->z = 0;
            Windows[KGWS_ZORDER_BOTTOM] = (unsigned long) hWindow;

			// #debug
			// refresh_screen();
			// while(1){}
		};
    };

//done:
    //return; 
}


/*
 ***********************************************
 * logon_create_background:
 *     Cria o background. Pinta ele de uma cor.
 */

void logon_create_background (void)
{
    // Nothing.
}


/*
 *************************************************
 * logon_create_mainwindow:
 *      A área de trabalho.
 * 
 *  #Importante: 
 *  É a área disponível na tela para o aplicativo. 
 */

void logon_create_mainwindow (void)
{
    // #bugbug
    // Cuidado com isso!
    
    // #todo
    // Checks!
    
    gui->main = (void *) gui->screen;
}



// #todo: Delete this function.
void logon_create_logo (void)
{ 
    // Nothing.
}


// #todo: Delete this function.
void logon_create_taskbar (void)
{ 
    // Nothing.
}


// #todo: Delete this function.
void logon_create_controlmenu (void)
{ 
    // Nothing.
}


// #todo: Delete this function.
void logon_create_infobox (void)
{
    // Nothing.
}


// #todo: Delete this function.
void logon_create_messagebox (void)
{ 
    // Nothing.
}


// #todo: Delete this function.
void logon_create_debug (void)
{ 
    // Nothing.
}


// #todo: Delete this function.
void logon_create_navigationbar (void)
{
    // Nothing.
}


// #todo: Delete this function.
void logon_create_grid (void)
{ 
    // Nothing.
}


// #todo: Delete this function.
void logon_create_developer_screen (void)
{
    // Nothing.
}


//
// ====================================
//


int register_logon_process ( pid_t pid ){

    if (pid<0 || pid >= PROCESS_COUNT_MAX ){
        debug_print("register_logon_process: pid fail\n");
        return -1;
    }

    if ( __gpidLogon != 0 ){
        debug_print("register_logon_process:\n");
        return -1;
    }

    __gpidLogon = (pid_t) pid;
    
    return 0;
}


//
// End.
//

