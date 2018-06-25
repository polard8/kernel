/*
 * File: gramado\logon\logon.c
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
 *    Versão 1.0, 2015, 2016.
 */
 
 
#include <kernel.h>



//Variáveis internas.
//int logonStatus;
//...


// Internas.
void logon_create_screen();
void logon_create_background();
void logon_create_logo();
void logon_create_taskbar();
void logon_create_mainwindow();
void logon_create_controlmenu();
void logon_create_infobox();
void logon_create_messagebox();
void logon_create_debug();
void logon_create_navigationbar();
void logon_create_grid();
void logon_create_developer_screen();

int ExitLogon();


/* 
 ***************************************************
 * create_logon:
 *     Cria a interface gráfica do Logon.
 *     É o ambiente onde o processo de logon deve rodar. 
 *
 *     Fundo -> Screen, Background.
 *     Logo  -> Sobreposto. 
 *     Navigation bar.
 *     Usuário.
 *
 *    @todo Cria window stations, desktops ...
 *    @todo: logonCreate();
 *
 */
void create_logon()
{
	struct window_d *hWindow; 	 
	
	//g_guiMinimal = 1;
	
	
	//Disable interrupts, lock task switch and scheduler.
	asm("cli");
	set_task_status(LOCKED); 	
	scheduler_lock();

	//
	// GUI Structure. 
	// 	
	
	gui = (void*) malloc( sizeof(struct gui_d) );
    if( (void*) gui == NULL)
	{
	    printf("create_logon:");
		die();
	}else{
	    
        //Set session ,window station, desktop, window and menu.
	    current_usersession = 0;       // User Session.
	    current_windowstation = 0; // Window Station.
	    current_desktop = 0;       // Desktop.
	    current_window = 0;        // Window.
	    current_menu = 0;          // Menu.
		
		// Initialize Session, WindowStation, Desktop, Windows and Menus.
		  
		//user section.
#ifdef KERNEL_VERBOSE		
		printf("create_logon: User Session..\n");
#endif		
		init_user_session();
		
		//initialize window station default.	
#ifdef KERNEL_VERBOSE			    
		printf("create_logon: Station..\n");   
#endif	    
		init_window_station();  	
	
	    //initialize desktop default.
#ifdef KERNEL_VERBOSE			    
		printf("create_logon: Desktop..\n");   
#endif	    
		init_desktop(); 	    
	
	    //Inicia estrutura.	
#ifdef KERNEL_VERBOSE			    
		printf("create_logon: Windows..\n");   
#endif	    
		init_windows(); 

		//menus.
#ifdef KERNEL_VERBOSE				
		printf("create_logon: Menu..\n");
#endif	    
		init_menus();        
	    
		//init_menus( ... 	
	    //...
	};
	
	// Configura elementos da tela de login.
    if( g_guiMinimal == 1 )
	{
        SetLogonParameters(0,1,1,0,0,1,0,0,0,0,0,0); 	
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
					   
draw_logon_stuffs:	
	   
	//Debug.
	//printf("create_logon: Draw..\n");   

	//Screen, Background and Logo. 
	if(gui->screenStatus == 1){ 
	    logon_create_screen(); 
	};
	
	if(gui->backgroundStatus == 1){	
	    logon_create_background(); 
	};	
	
	if(gui->logoStatus == 1){ 
	    logon_create_logo(); 
	};	

	//Taskbar, Control menu and Messagebox.
    if(gui->taskbarStatus == 1){	
	    logon_create_taskbar(); 
	};
    if(gui->menuStatus == 1){ 
	    logon_create_controlmenu(); 
	};
    if(gui->messageboxStatus == 1){ 
	    logon_create_messagebox(); 
	};
	
	//Main window, Navigation bar and grid.    
	if(gui->mainStatus == 1){ 
	    logon_create_mainwindow(); 
	};
    if(gui->navigationbarStatus == 1){ 
	    logon_create_navigationbar(); 
	};
    if(gui->gridStatus == 1){ 
	    logon_create_grid(); 
	};
	
		
	//
	// ## Strings ##
	//
	
	if( (void*) CurrentUser != NULL )
	{

		// Obs: 
		// As mensagens aqui são para auxiliar 
		// o desenvolvedor no processo de inicialização.
		//@todo: Informar o desktop atual.
			
        if(g_guiMinimal != 1)
		{
            //draw_text(gui->screen, 8, 1*8, 
			//    COLOR_WHITE, (unsigned char *) CurrentUser->name_address);
   			
			draw_text( gui->main, 400 +8, 8*1, 
			    COLOR_WHITE, "Gramado 0.1" );
				
			draw_text( gui->main, 400 +8, 8*2, 
			    COLOR_WHITE, "(c) Copyright 2005-2018, Fred Nora" );
			
			draw_text( gui->main, 400 +8, 8*3, 
			    COLOR_WHITE, "(under construction) ");
				
			draw_text( gui->main, 400 +8, 8*4, 
			    COLOR_WHITE, "(This is the enviroment to run logon.bin)" );
				
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
	
	//Debug:
	//printf("#debug logon.c");				   
	//die();
		
	//
	// # Done # 
	//
	
done:

	// # Refresh #
 	
	if( gui->refresh == 1 )
	{
		refresh_screen();
		gui->refresh = 0;
	};
	
    gui->initialised = 1;
    return;
};


/*
 *****************************************************
 * ExitLogon:
 *     Fecha o ambeinte de logon.
 *     @todo: logonExit();
 *     Isso pode ser chamado nas rotinas de 
 * reboot e shutdown.
 */
int ExitLogon()
{					
    if( (void*) gui != NULL )
	{
        //CloseWindow();
		//...
		
		if( (void*) gui->screen != NULL ){
		    SetFocus(gui->screen);
	    };
	};
	
	//...
	
done:	
	logonStatus = 0;
	return (int) 0;
};


/*
 ******************************************
 * SetGuiParameters:
 *     Configura a inicialização das janelas 
 * gerenciadas pelo kernel.
 *     @todo: Limite de janelas (+- 10)
 *
 */
void SetLogonParameters( int refresh,  // Flag. Colocar ou não o backbuffer na tela.
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
int grid             // Grid da janela principal.
//limites ...
)
{
    if( (void*) gui == NULL )
	{
		//@todo:
		//precisamos de uma mensagem de alerta.
		printf("SetLogonParameters: fail\n");
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
	    //...		
		
	};	
    return;
};


/*
 **************************************
 * logon_create_screen:
 *     Cria a tela. 
 *     Atribuindo as dimensões.
 *     ...
 */
void logon_create_screen()
{
	struct window_d *hWindow; 
	
	unsigned long Left = 0;
	unsigned long Top = 0;
	unsigned long Width = (unsigned long) screenGetWidth();
	unsigned long Height = (unsigned long) screenGetHeight();
	
	// Screen
	// Obs: Não tem 'parent window' !!!
	hWindow = (void*) CreateWindow( 1, 0, VIEW_MINIMIZED, "Screen", 
	                                Left, Top, Width, Height, 
							        NULL, 0, 0, COLOR_BLACK );  
	if( (void*) hWindow == NULL ){
	    printf("logon_create_screen:");
		die();
	}else{
	    
		RegisterWindow(hWindow);
	    windowLock(hWindow); 
		set_active_window(hWindow); 
		
		//a janela pertence ao desktop 0
	    //hWindow->desktop = (void*) desktop0;

	    if( (void*) gui == NULL){
		    return;
		}else{
	        gui->screen = (void*) hWindow;
		};
	};
	
done:
    //#bugbug: 
	//Não usar set focus nessa que é a primeira janela.	
	//windowLock(hWindow);
    return; 
};


/*
 ***********************************************
 * logon_create_background:
 *     Cria o background. Pinta ele de uma cor.
 *
 */
void logon_create_background()
{ 
    struct window_d *hWindow;

	unsigned long Left = (unsigned long) SCREEN_DEFAULT_LEFT;
	unsigned long Top  = (unsigned long) SCREEN_DEFAULT_TOP;
	unsigned long Width = (unsigned long) screenGetWidth();
	unsigned long Height = (unsigned long) screenGetHeight();	

	//Debug:
	//printf("logon_create_background createwindow\n");				   
	//refresh_screen();

	//O background pertence ao desktop0.
	hWindow = (void*) CreateWindow( 1, 0, 0, "Background", 
	                                Left, Top, Width, Height, 
							        gui->screen, 0, 0, COLOR_BACKGROUND );
													
	if( (void*) hWindow == NULL){
	    printf("logon_create_background:");
		die();
	}else{
	    
		RegisterWindow(hWindow);
	    windowLock(hWindow); 
		set_active_window(hWindow); 
	    //a janela pertence ao desktop 0
	    //hWindow->desktop = (void*) desktop0;

		if( (void*) gui == NULL){
		    return;
		}else{
	        gui->background = (void*) hWindow;
		};	

	};
	
done:
    SetFocus(hWindow);
    //windowLock(hWindow);	
    return; 
};


/*
 *************************************************
 * logon_create_mainwindow:
 *      A área de trabalho.
 *      *Importante: É a área disponível na tela para o aplicativo. 
 */
void logon_create_mainwindow()
{  
    struct window_d *hWindow; 
	 
	//Dimensões:
	unsigned long Left = (unsigned long) SCREEN_DEFAULT_LEFT;
	unsigned long Top  = (unsigned long) SCREEN_DEFAULT_TOP;
	unsigned long Width = (unsigned long) screenGetWidth();
	unsigned long Height = (unsigned long) screenGetHeight();

 
	if( (void*) gui == NULL ){
        return;
    }; 
	
	//
	// A janela principal pertence ao desktop.
	//
	
	//
	// Estamos criando uma área de trabalho que
	// é o tamanho total da tela menos a área destinada
	// à barra de tarefas.
	// A barra de tarefas ainda não foi criada, mas
	// um tamanho inicial para ela ja foi reservado.
	//
	
	hWindow = (void*) CreateWindow( 1, 0, VIEW_MINIMIZED, "logon desktop window", 
	                                Left, Top, Width, Height,           
							        gui->screen, 0, 0, COLOR_WINDOW  );      
	if( (void*) hWindow == NULL){
	    printf("logon-logon-logon_create_mainwindow:\n");
	    die();
	}else{   
	    		
	    RegisterWindow(hWindow);
	    windowLock(hWindow); 
		set_active_window(hWindow); 
		
	    //a janela pertence ao desktop 0
	    //hWindow->desktop = (void*) desktop0;
		
		if( (void*) gui == NULL){
		    return;
		}else{
	        gui->main = (void*) hWindow;
		};	
	};
	
	
	//
	//  Desktop Window:
	//      Criar a janela gui->desktop.
	//      Na verdade a janela do desktop
	//      é a janela da área de trabalho.
	//
	
    /*	
	gui->desktop = (void*) CreateWindow( 1, 0, VIEW_MINIMIZED, "Desktop Window", 
	                                0, 16, 800, 600-16-16, 
							        gui->screen, 0, 0, COLOR_WINDOW ); 
	*/
	
	gui->desktop = (void*) gui->main;
	
	if( (void*) gui->desktop == NULL){
		
		gui->desktop = (void*) gui->screen;
		
		if( (void*) gui->desktop == NULL){ 
		    goto done;
		};
	};
	
	//Não registrar pois main menu ja está registrada.
	//RegisterWindow(gui->desktop);
	
done:
    SetFocus(hWindow);
    return;	
};


/*
 * logon_create_logo:
 *     Cria a janela para o logo da area de trabalho.
 *     o logo da area de trabalho é a magem da area de trabalho.
 *
 *     Obs: Sem logo por enquanto.
 */
void logon_create_logo(){ 
    return; //Cancelada! 
};


/*
 * logon_create_taskbar:
 *     Obs: Não há tarefas durante o ambiente de logon.
 *          Não precisa de barra de tarefas.
 */
void logon_create_taskbar(){ 
    return; //Cancelada!.
};


/*
 * logon_create_controlmenu:
 *     Inicializar a estrutura do System menu, 
 *     para ser usado durante o ambiente de logon.
 *     
 *
 */
void logon_create_controlmenu(){ 
    return; 
};


/*
 * logon_create_infobox:
 *     Janelinha de informações do sistema.
 *     Avisa o usuário sobre eventos do sistema na ora do logon,
 * como novos dispositivos encontrados.
 *     Inicalizar uma estrutura light de infobox.
 */
void logon_create_infobox(){
   //@todo: trocar isso por message window, aquela janela amarela de mensagens.
    return; //Nothing for now.
};


/*
 * logon_create_messagebox:
 *     @todo: Inicializa o message box a ser usado no ambiente de logon.
 *            Light message box. 
 */
void logon_create_messagebox(){ 
    return; 
};


/*
 * logon_create_debug:
 *     Pequeno debug de estruturas e parâmetros e logon.
 * 
 */
void logon_create_debug(){ 
    return; //Nothing for now.
};


/*
 * logon_create_navigationbar:
 *     A barra de navegação na tela de logon.
 *
 *     Nessa barra pode ter botões como desligar ou reboot.
 *     Barra de navegação, semelhante as barras encontradas nos 
 * dispositivos móveis.
 *     Usada para navegação simples. 
 *     Fica em baixo.
 *     A barra de navegação da tela de logon pode ser um pouco mais larga.
 *
 */
void logon_create_navigationbar()
{
	
/*
 * #suspensa
 
    struct window_d *hWindow; 

	unsigned long Left = (unsigned long) SCREEN_DEFAULT_LEFT;
	unsigned long Top  = (unsigned long) SCREEN_DEFAULT_TOP;
	unsigned long Width = (unsigned long) screenGetWidth();
	unsigned long Height = (unsigned long) screenGetHeight();

	if( (void*) gui == NULL ){
        return;
    };		
	
	//A navigation bar pertence a janela principal.
	hWindow = (void*) CreateWindow( 1, 0, 0, "NavigationBar", 
	                                 Left, Height-(8*5), Width, (8*5), 
									gui->screen, 0, 0, COLOR_BLACK); 
	if( (void*) hWindow == NULL)
	{
	    printf("logon_create_navigationbar:");
		die();
		//refresh_screen();
	    //while(1){};
	}else{
	    		
        //navigation bar como foreground window inicialmente.		
		//set_current_foreground(desktop0, gui->navigationbar);
		
		RegisterWindow(hWindow);
	    windowLock(hWindow); 
		set_active_window(hWindow); 
		
	    //a janela pertence ao desktop 0
	    //hWindow->desktop = (void*) desktop0;
		gui->navigationbar = (void*) hWindow;
	};

	// Buttons.
draw_buttons:	
    draw_button( gui->navigationbar, "MENU", 1, 2, 2, 48, 20, COLOR_BLACK);	
	
   
//	//Start
//    draw_button( gui->navigationbar, "F1=START", 1,  
//	             6*(480/8), 8, 100, 24, 
//				 COLOR_WINDOW);	
//    
//				 
//    //Reboot
//    draw_button( gui->navigationbar, "F2=REBOOT", 1,  
//	             8*(480/8), 8, 100, 24, 
//				 COLOR_WINDOW);	
			
	
    //
    // Text.
    //
	
draw_texts:    
	draw_text( gui->navigationbar, 1*(600/8), 8, COLOR_WHITE, ".Logon "); 
	//draw_text( gui->navigationbar, 2*(480/8), 8, COLOR_WHITE, CurrentUser->name_address ); 
	
done:
    SetFocus(hWindow);	

*/	
	return; 
};


/*
 * logon_create_grid:
 *     O Kernel não cria grid em logon.
 */
void logon_create_grid(){ 
	return; //Cancelada!
};


/*
 * logon_create_developer_screen:
 *     Cria a tela do desenvolvedor, a única tela em primeiro plano e com foco de
 * entrada durante a fase de desenvolvimento da interface gráfica.
 *     É conveniente que essa tela seja de uma cor diferente, para os aplicativos 
 * testarem cores diferentes de fonte.
 *     Atribuindo as dimensões.
 *     ...
 */
void logon_create_developer_screen()
{
	
/*
 * #suspensa
 
    struct window_d *hWindow; 
	
	//
	// @todo: Os parâmetros passados com as dimensões foram
	//        passados pelo boot loader e estão disponíveis.
	//
	
	//Métrica. 
	//Precisa ter boa altura.
	//Não pode atrapalhar as outras que serão basicamente pequenas e centralizadas.
	//Então ela deve ser estreita e do lado esquerdo... 
	//Deve ter uma cor distinta... naõ pode preto, azul, nem verde, nem rosa...
	//Será laranjada.
	unsigned long Left = (unsigned long) SCREEN_DEFAULT_LEFT;
	unsigned long Top  = (unsigned long) SCREEN_DEFAULT_TOP;
	unsigned long Width = (unsigned long) screenGetWidth();
	unsigned long Height = (unsigned long) screenGetHeight();
	
    
    Width = (Width/2);	
	
	//
	//
	//
	//
	
	// Screen - Não tem parent window.
	hWindow = (void*) CreateWindow( 3, 0, VIEW_NORMAL, "{} DEVELOPER SCREEN", 
	                                Left, Top, Width, Height, 
							        NULL, 0, COLOR_ORANGE, COLOR_BLUE );  
	if( (void*) hWindow == NULL ){
	    printf("logon_create_developer_screen:");
		die();
		//refresh_screen();
	    //while(1){};
	}else{
	    
		RegisterWindow(hWindow);
	    windowLock(hWindow);     //?? 
		set_active_window(hWindow); 
		
		//a janela pertence ao desktop 0
	    //hWindow->desktop = (void*) desktop0;

		//
		// Mais métricas.
		//
		hWindow->left    = Left;
	    hWindow->top     = Top;
		hWindow->width   = Width; 
		hWindow->height  = Height;
		hWindow->right   = (Left+Width);
		hWindow->bottom  = (Top+Height);
		//...
		
		//Cursor
		hWindow->cursor_x = Left;
		hWindow->cursor_y = Top;
		
		
		//salva na estrutura gui->
		if( (void*) gui == NULL){
		    return;
		}else{
	        gui->DEVELOPERSCREEN = (void*) hWindow;
		};
	};
	
done:
    //
	// *IMPORTANTE:
	//
	//  TRAVAREMOS A JANELA EM PRIMEIRO PLANO E COM O FOCO DE ENTRADA.
    //  NENHUMA OUTRA JANELA PODERÁ GANHAR O FOCO.
    //  
    // Até que a interface gráfica fique mais robusta, apenas a janela 
    // dodesenvolvedor ficará com o foco de entrada.  	
	//
	
	//ganho o foco.
	SetFocus(hWindow);
	
	//trava o foco nela.
	//não criaremos uma rotina para manipular essa variável...
	//e ela será usada apenas uma vez. 
	// essa variável será uma flag na rotina SetFocus(.).
	//e ficará definida no começo do arquivo window.h.
	//_lockfocus = 1;
	

	//ERRO NA CRIAÇÃO DA ESTRUTURA.
	if( (void*) gui->DEVELOPERSCREEN == NULL ){
		printf("logon_create_developer_screen: gui->DEVELOPERSCREEN");
		die();
		//refresh_screen();
		//while(1){};
	};
	
*/
    return; 
};


/*
 *********************************************
 * LogonProcedure:
 *     O procedimento de janela do Logon.
 *
 */																
unsigned long LogonProcedure( struct window_d *window, 
                              int msg, 
							  unsigned long long1, 
							  unsigned long long2 ) 
{
    
	//Obs: Deve ser simples para o módulo logon do kernel base.
	
	switch(msg)
	{			
		case MSG_SYSKEYDOWN:                 
            switch(long1)	       
            {   
				//Start	
				case VK_F1:
					ExitLogon();               
					startUserEnvironment(0,0);    
                    break;
					
				//Reboot	
                case VK_F2:
					ExitLogon();
				    KiReboot();				
                    break;				
														
				default:
                    //Nothing.
				    break;
		    };              
        break;
		
		default:
		    //Nothing.
		    break;
	};
	
// Done.
done:
	//Refresh screen. 
	if(VideoBlock.useGui == 1){
	    refresh_screen();
	};
	return (unsigned long) 0;
};

						
/*
 **********************************************
 * init_logon:
 *     Inicializa o Logon.
 *     Obs: Aceita argumentos.
 * Argumentos:
 * -l ou /l; ...
 *
 */
int init_logon(int argc, char *argv[]) 
{    	
	int LogonFlag = 0;
	char *s;    //String
	
	//
	// Se não há argumentos.
	//
	
	if(argc < 1){
		goto done;
    };
	
	//
	// Dependendo do argumento encontrado muda-se a flag.
	//
	
    while(--argc) 
    {
        s = *++argv;
        if (*s == '-' || *s == '/') 
		{
            while(*++s) 
			{
                switch(*s) 
				{
                    case 'l':
                        LogonFlag = 0;
                        break;

                    case 's':
                        LogonFlag = 0;
                        break;

                    case 'r':
					    LogonFlag = 0;
                        break;

                    case 'f':
					    LogonFlag = 0;
                        break;

                    default:    
					    //usage();
						break;
                };
            };
        }
        else 
		{
            //usage();
        }
    };
	
	//
	// Aqui deve-se habilitar as opções de acordo
	// com a flag.
	//
	
	//
	// Keyboard support.
	//
	
	ldisc_init_modifier_keys();
	ldisc_init_lock_keys();
	
	//...
	
done:
	//printf("init_logon: Initializing..\n");
    SetProcedure( (unsigned long) &LogonProcedure);	
    logonStatus = 1;	
	//g_logged = (int) 0;
	return (int) 0;
};


/*
int logonInit()
{}
*/

//
//fim.
//

