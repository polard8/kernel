/*
 * Gramado GUI - The main file for the GUI layer.
 * (c) Copyright 2015~2018 - Fred Nora.
 */
 
 
// ## GWS - Gramado Window Server ##

// Aplicativo poderão se conectar com o servidor de recusros
// gráficos, principalmente a GUI, que será chamada de 
// Gramado Window Manager.
// Outros window managers poderão ser criados, e eles precisarão 
// ser registrados e abrirem o servidor para usarem seus recursos.
// do mesmo modo o shell atual poderá se registrar,
// o processo de logon poderá se registrar em um servidor de logon.
//

#include <kernel.h>



// unsigned char  gws_bame[] = "GWS - Gramado Window Server";
// unsigned char  GramadoName[] = "GRAMADO LAYER";

//Status do gws.
int gws_status;

//Qual é o id do processo que é o atual window manager.
//o oficial é o Gramado Window Manager, hoje 
//chamado de shell.bin
int gws_wm_PID;
int gws_wm_status;
 
 
//abrir o servidor de janelas. 
int gwsOpen()
{
	//Aberto.
	gws_status = 1;
	//..
	
	return (int) 0;
};


//fechar o servidor de janelas
int gwsClose()
{
	gws_status = 0;
	
	return (int) 0;
};


// Registrar um window manager.
int gwsRegisterWindowManager( int pid )
{
	int Status = 0;
	
	if( gws_status != 1 )
	{
		Status = 1;
		goto fail;
	}else{
		
	    gws_wm_PID = (int) pid;	
	    gws_wm_status = 1;
		goto done;
	};
	
fail:
    printf("gwsRegisterWindowManager: fail\n");	
done:
    return (int) 0;		
};
 


//internas
void gui_create_screen();
void gui_create_background();
void gui_create_logo();
void gui_create_taskbar();
void gui_create_mainwindow();
void gui_create_controlmenu();
void gui_create_infobox();
void gui_create_messagebox();
void gui_create_debug();
void gui_create_navigationbar();
void gui_create_grid();

	
	
/* 
 * create_gui:
 *     Cria as janelas principais: Screen, Background,Logo ...
 *     Cria Window Station, Desktop, Windows, Menu ...
 *     @todo: guiCreate();
 *
 * Obs: esse é o user environment. 
 *(deixe o desenvolvedor saber em qual desktop ele está.)
 */
void create_gui()
{	
	struct window_d *hWindow; 	 

	//
	// Set minimal gui set up!.
	//
	
	//g_guiMinimal = 1;
	
	
    //	
	// Initializing 'gui' structure.
	// Obs: Essa estrutura foi antes usada pelo Logon.
	//      Agora a GUI reinicializa.
	//      Todos os parametros da estrutura precisam ser inicializados.
	// @todo: Estamos reinicializando tudo, recriando estruturas 
	//        que devem ser deletadas na finalização do logon. @todo.
    // 		
	
	gui = (void*) malloc( sizeof(struct gui_d) );
    if((void*) gui == NULL){	
	    printf("create_gui:");
		die();
		//refresh_screen();
		//while(1){};
	}else{
		
        //
		// Set user session, window station, desktop, window and menu.
	    //
		
		current_usersession = 0;        //User Session.
	    current_windowstation = 0;  //Window Station.
	    current_desktop = 0;        //Desktop.
	    current_window = 0;         //Window.
	    current_menu = 0;           //Menu.
		
		
		//
		// @todo: O logon devveria ter selecionado o perfil do usuário
		//        e essa rotina não deveria ser chamada.
		//
		
		init_user_info();
		
		//
		// Em ordem:
		// user section, window station and desktop.
		// windows and menus.
		//
		
#ifdef KERNEL_VERBOSE		
		printf("create_gui: User Session..\n");
#endif
		init_user_session();
		
#ifdef KERNEL_VERBOSE				
		printf("create_gui: Window Station..\n");
#endif
		init_window_station();
	 
#ifdef KERNEL_VERBOSE			 
		printf("create_gui: Desk..\n");
#endif
	    init_desktop();	
	 
#ifdef KERNEL_VERBOSE			 
		printf("create_gui: Wind..\n");
#endif	    
		init_windows();	
	 
#ifdef KERNEL_VERBOSE			 
		printf("create_gui: Menu..\n");
#endif	    
		init_menus();
		
		//
		// System MenuBar: (Barra no topo da tela). 
		//
	
#ifdef KERNEL_VERBOSE			
		printf("create_gui: System Menu bar..\n");
#endif		
		systemCreateSystemMenuBar();
		
		//
		// Continua ...
        //
		
    };
	
	
	//
	// Configura quais janelas devem ser pintadas.
	//
	
    if(g_guiMinimal == 1)
	{		

        SetGuiParameters( 0,    //Refresh.         
                          1,    //*Screen.          
                          1,    //*Background.       
                          0,    //Logo.            
                          1,    //*Taskbar. #test.        
                          1,    //*Main.(Desktop window, Área de trabalho) com base na taskbar.             
                          0,    //Menu.           
                          0,    //Info Box.         
                          0,    //Message Box.       
                          0,    //Debug.           
                          0,    //Navigation Bar.    
                          0 );  //Grid. #test.	
						  
	}else{
		
        SetGuiParameters( 0,    //Refresh.         
                          1,    //*Screen.          
                          1,    //*Background.       
                          0,    //Logo.            
                          1,    //*Taskbar. #test.        
                          1,    //*Main.(Desktop window, Área de trabalho) com base na taskbar.             
                          0,    //Menu.           
                          0,    //Info Box.         
                          0,    //Message Box.       
                          0,    //Debug.           
                          0,    //Navigation Bar.    
                          0 );  //Grid. #test.	
						   
	};
  	
	//
	// *** Filtro importante.
	//
	
	if( (void*) gui == NULL ){
		printf("create_gui: gui struct");
		die();
	};
	
	
	//Grupo1:
	//Base windows:
	//screen,background,taskbar
	
	//grupo2
	//main (com base na screen e na taskbar.)
	
	//grupo3
	//outros.

	
//creatingWindows:
	
    	
	//Grupo1:
	//Base windows:
	//screen,background,taskbar
	
	if(gui->screenStatus == 1){ 
	    gui_create_screen(); 
	};
	
	if(gui->backgroundStatus == 1){	
	    gui_create_background(); 
	};

	if(gui->taskbarStatus == 1){	
	    gui_create_taskbar(); 
	};

	//grupo2
	//main (com base na screen e na taskbar.)
	
	
    if(gui->mainStatus == 1){ 
	    gui_create_mainwindow(); 
	};

	//grupo3
	//outros.

	
	if(gui->logoStatus == 1){ 
	    gui_create_logo(); 
	};	
	
	
    if(gui->messageboxStatus == 1){ 
	    gui_create_messagebox(); 
	};
	
    if(gui->menuStatus == 1){ 
	    gui_create_controlmenu(); 
	};	

    if(gui->navigationbarStatus == 1){ 
	    gui_create_navigationbar(); 
	};
	
	//
	// Grid: Dentro do grid haverá sempre 3 partes: 
	//       Header | Content | Footer.
	//       Obs: @todo: O grid deve levar em consideração a
	// área que lhe pertence, ou seja a área de trabalho.  
	//
	
    if(gui->gridStatus == 1){ 
	    gui_create_grid(); 
	};
	
	
//drawingStrings:
	
	//
	// Strings.
	// String no background.
	//
	
	if( (void*) CurrentUser != NULL )
	{
        if(g_guiMinimal != 1)
	    {		
	        //
            // Obs: Informações de ambiemte para o desenvolvedor.
            //
			
			//@todo: Informar o desktop atual.
			
		    draw_text(gui->main, 0, 0, COLOR_WHITE, "User Environment:");
		    draw_text(gui->main, 0, 8, COLOR_WHITE, "================");
			draw_text(gui->main, 8*14, 8*4, 
			          COLOR_WHITE, "Welcome to User Environmet, press F1=HELP.");
			draw_text(gui->main, 8*14, 8*5, COLOR_WHITE, "This is the user environment");
			//draw_text(gui->main, 8*10, 8*12, COLOR_WHITE, "F1=HELP");
			//...
			
			//Outros:
			//StatusBar( gui->main, "Dektop", "GUI");
			//Message box
			//...
	    };
		
		//Outras opções ?
		
		//Nothing.
	};	
	
	//
	// Testando client area.
	//
	//draw_text(gui->ClientArea, 8, 8, COLOR_WHITE, ".Desktop");
	//draw_text(gui->screen, 8, 8, COLOR_WHITE, ".Desktop");
	//draw_text(gui->screen, 1*(480/8), 1*(640/8), COLOR_WHITE, ".Desktop"); 
    //StatusBar( gui->screen, "StatusBar: ", "Barra de status na area de trabalho.");
	//

	
	//
	// @todo: More ?!!
	//
	
done:
	//Refresh.
    //(O 1 avisa que é necessário dar refresh pois foram efetuadas rotinas de pintura).	
	if(gui->refresh == 1){
		refresh_screen();
		gui->refresh = 0;  //Status.
	};
    return;
};



/*
 * SetGuiParameters:
 *     Configura a inicialização das janelas gerenciadas pelo kernel.
 *     @todo: Limite de janelas (+- 10)
 *
 */
void SetGuiParameters(
int refresh,         //Flag. Colocar ou não o backbuffer na tela.
int screen,          //Tela do computador.
int background,      //Background da area de trabalho. 
int logo,            //Logo, Janela para imagem da área de trabalho.
int taskbar,         //Barra de tarefas.(Ícones para programas).
int main,            //Janela principal.(Desktop, ou Kernel Setup Utility). 
int menu,            //Control menu da Área de trabalho.
int infobox,         //Janelinha no canto, para alerta sobre sobre eventos ocorridos no sistema.
int messagebox,      //O message box do kernel.(Cada app cria seu messagebox). 
int debug,           //Janela do debug do kernel.(sonda por problemas).
int navigationbar,   //Janela de navegação(Semelhante a navigation bar dos dispositivos mobile). 
int grid             //Grid da janela principal.
//Limites ...
)
{ 
    //Passados via argumento.
	
	//
	//@todo: gui status. fail or not.
	//
	
	//Checa validade da estrutura.
	if( (void*) gui == NULL ){
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

    //
    // @todo: More ?!!
    //	
	
done:
    return;
};


/*
 * gui_create_screen:
 *     Cria a tela. (Screen)
 *     Atribuindo as dimensões.
 *     ...
 * @todo: Cria buffer dedicado.
 */
void gui_create_screen()
{
    struct window_d *hWindow; 
	
	unsigned long Left = (unsigned long) SCREEN_DEFAULT_LEFT;
	unsigned long Top  = (unsigned long) SCREEN_DEFAULT_TOP;
	unsigned long Width = (unsigned long) screenGetWidth();
	unsigned long Height = (unsigned long) screenGetHeight();

	//
	// * IMPORTANTE: Não tem Parent Window!
	//
	
	if( (void*) gui == NULL ){
        return;
    };		
	
	//Window:
	//Pintado uma janela simples, toda preta, do tamanho da tela 
	//do sispositivo.
	hWindow = (void*) CreateWindow( 1, 0, VIEW_MINIMIZED, "Screen",
	                               Left, Top, Width, Height,
						           0, 0, 0, COLOR_BLACK );     
	if( (void*) hWindow == NULL ){
	    printf("gui_create_screen:");
		die();
	}else{

		RegisterWindow(hWindow);
		set_active_window(hWindow); 
		
		//Isso impede que rotinas mudem as caracteríscicas 
		// da janela principal sem antes destravar ou sem 
		//ter autorização para isso.
		windowLock(hWindow); 
		
		//Estrutura gui.
	    if( (void*) gui != NULL ){
	        gui->screen = (void*) hWindow;
		};
		
	    //Desktop.
		//a janela pertence ao desktop 0
	    //hWindow->desktop = (void*) desktop0;
		
		//Nothing.
	};
	
	// @todo: More ??!!
done:
    //bugbug: Não usar set focus nessa que é a primeira janela.
    return; 
};


/*
 * gui_create_background:
 *     Cria o background. Pinta ele de uma cor.
 *     O background é filha da janela screen.
 *
 * Criando um pano de fundo do mesmo tamaho da tela,
 * Penso que é nessa janela que podemos carregar uma imagem de 
 * pano de fundo.
 *
 * @todo: Cria buffer dedicado.
 */
void gui_create_background()
{ 
    struct window_d *hWindow; 
	
	unsigned long Left = (unsigned long) SCREEN_DEFAULT_LEFT;
	unsigned long Top  = (unsigned long) SCREEN_DEFAULT_TOP;
	unsigned long Width = (unsigned long) screenGetWidth();
	unsigned long Height = (unsigned long) screenGetHeight();	
	
	if( (void*) gui == NULL ){
        return;
    };		
	
	//Window:
	//0x00808000 (verde)
	//Criando um pano de fundo do mesmo tamaho da tela,
	//Penso que é nessa janela que podemos carregar uma imagem de 
	//pano de fundo.
	hWindow = (void*) CreateWindow( 1, 0, VIEW_MINIMIZED, "Background", 
		                            Left, Top, Width, Height,
							        gui->screen, 0, 0, COLOR_BACKGROUND);  
	if( (void*) hWindow == NULL )
	{
	    printf("gui_create_background:");
		die();
	}else{
	    
		RegisterWindow(hWindow);
		set_active_window(hWindow); 
		windowLock(hWindow);  
		
        //Estrutura gui.
		if( (void*) gui != NULL ){
	        gui->background = (void*) hWindow;
		};
		
		//Desktop.
	    //a janela pertence ao desktop 0
	    //hWindow->desktop = (void*) desktop0;
		
		//Nothing.
	};
	
done:
	SetFocus(hWindow);
    return; 
};



/*
 * gui_create_taskbar:
 *      Cria a taskbar da área de trabalho. gui->taskbar.
 *      Cria somente a janela que será uada pelo file manager.
 * e que servirá de referência para a janela gui->main
 *
 */
void gui_create_taskbar()
{ 
	struct window_d *hWindow; 

	unsigned long Left = (unsigned long) SCREEN_DEFAULT_LEFT;
	unsigned long Top  = (unsigned long) SCREEN_DEFAULT_TOP;
	unsigned long Width = (unsigned long) screenGetWidth();
	unsigned long Height = (unsigned long) screenGetHeight();	
	
	if( (void*) gui == NULL ){
        return;
    };
    	
draw_bar:	

    Height = (Height/8);

	hWindow = (void*) CreateWindow( 1, 0, VIEW_MINIMIZED, "taskbar", 
	                                Left, Top, Width, Height, 
							        gui->screen, 0, 0, COLOR_WINDOW );
									
	if( (void*) hWindow == NULL)
	{
	    printf("gramado-gramado-gui_create_taskbar:\n");
		die();
	}
	else
	{
	    RegisterWindow(hWindow);
	    windowLock(hWindow); 
	    
		if( (void*) gui != NULL ){
            gui->taskbarStatus = (int) 1;
			gui->taskbar = (void*) hWindow;
	    };
		
		//...
	};
	
	//...
	
done:	
	return; 
};


/*
 * gui_create_mainwindow:
 *      A área de trabalho.
 *      *Importante: É a área disponível na tela para o aplicativo. 
 *      Onde ficam os ícones.
 *      
 *     A área de trabalho é toda a tela menos a GMB(Global Menu Bar) e menos a TaskBar. 
 * @todo: Criar o buffer dedicado para a janela principal.
 *
 *     Obs: Essa janela é especial e usará o Backbuffer como buffer dedicado.
 */
void gui_create_mainwindow()
{
    struct window_d *hWindow; 
	
	unsigned long Left = (unsigned long) SCREEN_DEFAULT_LEFT;
	unsigned long Top  = (unsigned long) SCREEN_DEFAULT_TOP;
	unsigned long Width = (unsigned long) screenGetWidth();
	unsigned long Height = (unsigned long) screenGetHeight();	
	
	//estrutura gui.
	if( (void*) gui == NULL )
	{
        printf("gui_create_mainwindow: gui\n");
        die();
	};

	//janela taskbar.
	if( (void*) gui->taskbar == NULL )
	{
        printf("gui_create_mainwindow: taskbar\n");
        die();
	};
	
	//
	// Usando a janela taskbar como referência para criar a janela main.
	//
	
	//Top = gui->taskbar->bottom;
	
	
	//Window:
	//Color? (?? Nem precisa pintar, mas precisa criar ??)
	//Área de trabalho.
	//Um retângulo que pode ser menor que o tamanho da tela do 
	//dispositivo.
	//É onde ficam as janelas dos aplicativos.
	//A janela principal perence ao desktop
	hWindow = (void*) CreateWindow( 1, 0, VIEW_MINIMIZED, "gramado desktop window", 
	                                Left, Top, Width, Height,           
							        gui->screen, 0, 0, COLOR_WINDOW );   
	if( (void*) hWindow == NULL){
	    printf("gramado-gui_create_mainwindow:\n");
	    die();
	}else{   
	    		
	    RegisterWindow(hWindow);
	    windowLock(hWindow); 
		set_active_window(hWindow); 
		
	    //a janela pertence ao desktop 0
	    //hWindow->desktop = (void*) desktop0;
		
		if( (void*) gui == NULL ){
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
	// @todo:
	// #bugbug: Confunde-se com a estrutura de desktop_d.
	//
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
 * gui_create_logo:
 *     Cria a janela para o logo da área de trabalho. O logo da área de 
 * trabalho é a imagem da área de trabalho.
 *
 * @todo: Cria buffer dedicado.
 */
void gui_create_logo()
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
	
	//Window:
	//White. Pequena no meio. Pode ser usada na inicialização.
	//O logo pertence ao desktop.
	hWindow = (void*) CreateWindow( 1, 0, VIEW_MINIMIZED, "Logo", 
	                                (Width/3), (Height/3), (Width/3), (Height/3), 
							        gui->screen, 0, 0, COLOR_WINDOW );
	if( (void*) hWindow == NULL )
	{
	    printf("gui_create_logo:");
	    die();
	}else{
	    		
		RegisterWindow(hWindow);
		set_active_window(hWindow); 
	    windowLock(hWindow); 
		
		//Estrutura gui.
		if( (void*) gui != NULL ){
	        gui->logo = (void*) hWindow;
		};
		
		//Desktop.
	    //A janela pertence ao desktop0.
	    //hWindow->desktop = (void*) desktop0;
		
		//Nothing.
	};

done:
	SetFocus(hWindow);	
	
 */
    return; 
};



/*
 * gui_create_controlmenu:
 *     Esse é o controlmenu da area de trabalho.
 * mesmo que nao esteja rodando o programa gerenciador de
 * deprogramas esse control menu existirá.
 *
 */
void gui_create_controlmenu()
{ 

/*
 * #suspensa
 
    struct window_d *cmWindow;
	
	if( (void*) gui == NULL ){
        return;
    };	

	//Usando a janela anteriormente criada.
    if( (void*) gui->screen == NULL ){
        return;
    };	
	
	//
    // Cria a janela e o menu. 
	// (o argumento é a janela mae)
    //	
	
    cmWindow = (void *) create_menu(gui->screen,2,0,0,0);
	if( (void *) cmWindow == NULL ){
	    printf("gui_create_controlmenu:");
		return;
	}else{
	    
		//configura a janela do menu do sistema.
	    set_current_menuwindow(desktop0, cmWindow);
		
		//configura o menu de sistema a ser usado no desktop.
		set_current_sysMenu(desktop0, cmWindow->defaultMenu);
		
		//itens.(test)
	    initmenuArray(cmWindow->defaultMenu,2);	
	    create_menu_item(cmWindow->defaultMenu,"cmitem0",0);
        create_menu_item(cmWindow->defaultMenu,"cmitem1",0);
        //...

        //gui->menu = (void*) cmWindow; //janela do control menu.		
	};			
	
done:
    SetFocus(cmWindow);
    refresh_screen();
	
*/
    return; 
};


/*
 *gui_create_infobox:
 * janelinha de informações do sistema.
 * avisa o usuario sobre eventos do sistema.
 *como novos dispositivos encontrados.
 * @todo: Cria buffer dedicado.
 */
void gui_create_infobox()
{ 
	if( (void*) gui == NULL ){
        return;
    }else{
		
		gui->infobox = NULL;
	};	    
	
done:
    return; 
};


/*
 * Cria a janela para message box.
 */
void gui_create_messagebox()
{ 
	if( (void*) gui == NULL ){
        return;
    }else{
		
		gui->messagebox = NULL;
	};	    
	
done:
    return; 
};


/*
 * cria uma janela para debug do kernel. será um progama em kernel mode.
 * @todo: Cria buffer dedicado.
 */
void gui_create_debug()
{ 
	if( (void*) gui == NULL ){
        return;
    }else{
		
		gui->debug = NULL;
	};	    

	//
    // @todo: Efetuará ou não algum tipo de debug de inicialização ou
    //	      dos elementos básicos do sistema. Essa tela de debug
	//        pode se mostrar uma opção importante para o desenvolvedor.
	//        Mostraria um log de acertos e problemas durante o processo 
    //        de inicialização do sistema operacional.
	//
	
done:
    return; 
};

	
/*
 * gui_create_navigationbar:
 *     Barra de navegação. 
 *     Semelhante às barras encontradas nos dispositivos mobile. Usada para 
 * navegação simples. Fica em baixo e deve ser escura.
 *
 *	   Obs: A navigation bar pertence a janela principal. gui->screen.
 *     Obs: A navigation bar poderá mudar para dentro da janela do shell.
 * que funciona como um navegador.
 *  
 * @todo: Cria buffer dedicado.
 */
void gui_create_navigationbar()
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
	
	hWindow = (void*) CreateWindow( 1, 0, VIEW_MINIMIZED, "NavigationBar", 
	                                Left, Height-(8*5), Width, (8*5), 
							        gui->screen, 0, 0, COLOR_BLACK);  
	if((void*) hWindow == NULL){
	    MessageBox(gui->screen,1,"ERRO","Navigation Bar fail!");
	}else{
	    	    
	    RegisterWindow(hWindow);
	    windowLock(hWindow); 
		set_active_window(hWindow); 

	    
		//hWindow->procedure = NULL;
		
		//@todo:
		//a janela pertence ao desktop 0
	    //hWindow->desktop = (void*) desktop0;
		
		if( (void*) gui == NULL ){
		    return;
		}else{
	        gui->navigationbar = (void*) hWindow;
		};

	};
    //Nothing.

// Buttons.
draw_buttons:
	//Back.
    draw_button( gui->navigationbar, "<",  1, 
	             1*(Width/16), 8, 24, 24, COLOR_BLACK);				   
	//Home.
    draw_button( gui->navigationbar, "O", 1, 
	             2*(Width/16), 8, 24, 24, COLOR_BLACK);	
	//TaskList, (lista os processos).
    draw_button( gui->navigationbar,  "=", 1, 
	             3*(Width/16), 8, 24, 24, COLOR_BLACK);	
	
    // Text. 
    //draw_text( gui->navigationbar, 1*(480/8), 8, COLOR_WINDOWTEXT, ".Desktop"); 	
	
	

//    * Text.   
//    if( (void*) gui->navigationbar != NULL )
//	{
//        //draw_text( gui->navigationbar, 1*(800/8), 8, COLOR_WINDOWTEXT, "/WindowStation0/Desktop0 GUI");
//        //draw_text( gui->navigationbar, 5*(800/8), 8, COLOR_WINDOWTEXT, "F1=HELP");
//	};	


    // Continua ...
    
done:	
    SetFocus(hWindow); 

*/    
	return; 
};


/*
 * gui_create_grid:
 *     Apenas autoriza a utilização de um grid na area de trabalho. 
 *     Havendo essa altorização, o gerenciador de arquivos poderá
 *     desenhá-lo. 
 *     cada item será um arquivo da pasta "area de trabalho".
 * @todo: Cria buffer dedicado.
 */
void gui_create_grid()
{ 
	if( (void*) gui == NULL ){
        return;
    }else{
		
		//initScreenGrid();	
		gui->grid = NULL;
	};	    


done:
    return; 
};


//screen
//métrica do dispositivo.
void *guiGetScreenWindow()
{
	if( (void*) gui == NULL){
		return NULL;
	}
	return (void*) gui->screen;
};


//developer screen
void *guiGetDeveloperScreenWindow()
{
	if( (void*) gui == NULL){
		return NULL;
	}
	return (void*) gui->DEVELOPERSCREEN;
};


//background
void *guiGetBackgroundWindow()
{
	if( (void*) gui == NULL){
		return NULL;
	}
	return (void*) gui->background;
};


//logo
void *guiGetLogoWindow()
{
	if( (void*) gui == NULL){
		return NULL;
	}
	return (void*) gui->logo;
};


//desktop window
void *guiGetDesktopWindow()
{
	if( (void*) gui == NULL){
		return NULL;
	}
	return (void*) gui->desktop;
};


//task bar, top window, mac style
void *guiGetTaskbarWindow()
{
	if( (void*) gui == NULL){
		return NULL;
	}
	return (void*) gui->taskbar;
};



//main window
//GetDesktopWindow
void *guiGetMainWindow()
{
	if( (void*) gui == NULL){
		return NULL;
	}
	return (void*) gui->main;
};

//status bar window (do kernel base)
void *guiGetStatusbarWindow()
{
	if( (void*) gui == NULL){
		return NULL;
	}
	return (void*) gui->statusbar;
};


//grid window (do kernel base)
void *guiGetGridWindow()
{
	if( (void*) gui == NULL){
		return NULL;
	}
	return (void*) gui->grid;
};


//janela do 'control menu' atual.
void *guiGetMenuWindow()
{
	if( (void*) gui == NULL){
		return NULL;
	}
	return (void*) gui->menu;
};


//infobox (o sistema envia mensagens de informação)
void *guiGetInfoboxWindow()
{
	if( (void*) gui == NULL){
		return NULL;
	}
	return (void*) gui->infobox;
};

//tooltip  Janelinha que aparece quando repousa o mouse sobre elemento gráfico.
void *guiGetTooltipWindow()
{
	if( (void*) gui == NULL){
		return NULL;
	}
	return (void*) gui->tooltip;
};


//message box do kernel base. (especial)
void *guiGetMessageboxWindow()
{
	if( (void*) gui == NULL){
		return NULL;
	}
	return (void*) gui->messagebox;
};


//dialogbox do kernel base. (especial)
void *guiGetDialogboxWindow()
{
	if( (void*) gui == NULL){
		return NULL;
	}
	return (void*) gui->dialogbox;
};


//janela de debug usada pelo kernel base.
void *guiGetDebugWindow()
{
	if( (void*) gui == NULL){
		return NULL;
	}
	return (void*) gui->debug;
};


//menubar usada pelo kernel base.
void *guiGetMbhWindowWindow()
{
	if( (void*) gui == NULL){
		return NULL;
	}
	return (void*) gui->mbhWindow;
};


//top bar de verdade, estilo mac ou mobile.
void *guiGetTopbarWindow()
{
	if( (void*) gui == NULL){
		return NULL;
	}
	return (void*) gui->topbar;
};


//navigation bar, estilo mobile.
//gerenciada pelo kernel base.
void *guiGetNavigationbarWindow()
{
	if( (void*) gui == NULL){
		return NULL;
	}
	return (void*) gui->navigationbar;
};


//janela do shell do kernel base.
//naõ é um processo.
void *guiGetShellWindowWindow()
{
	if( (void*) gui == NULL){
		return NULL;
	}
	return (void*) gui->shellWindow;
};


//uma janela filha do shell do kernel base.
void *guiGetShellClientWindowWindow()
{
	if( (void*) gui == NULL ){
		return NULL;
	}
	return (void*) gui->shellClientWindow;
};


// reposiciona e muda o tamanho da gui->main window.
// configura a área de trabalho.
void guiSetUpMainWindow( unsigned long x, 
                         unsigned long y, 
						 unsigned long width, 
						 unsigned long height )
{
	unsigned long Left = (unsigned long) SCREEN_DEFAULT_LEFT;
	unsigned long Top  = (unsigned long) SCREEN_DEFAULT_TOP;
	unsigned long Width = (unsigned long) screenGetWidth();
	unsigned long Height = (unsigned long) screenGetHeight();		
		
	//check limits
	if( x > Width || y > Height ){ 
	    return; 
	}
	
	if( width > Width || height > Height ){ 
	    return; 
	}

	if( (void*) gui == NULL ){
		return;
	}	
	
	if( (void*) gui->main == NULL ){
		return;
	}else{
		
	    replace_window(gui->main, x, y);
	    resize_window( gui->main, width, height);		
	};	
	//Nothing.
};

/*
 * init_gui:
 *     Inicializa a GUI.
 *     É preciso criar a GUI antes de inicializar.
 *     @todo: Mudar para guiInit().
 * Obs: Nada alem de recursos gráficos. 
 */
int init_gui()
{
	// ??
	// Habilita taskswitch e scheduler.
	set_task_status(UNLOCKED);
    scheduler_unlock();	 	
		
	//SetProcedure( (unsigned long) &system_procedure);	
	
	//
	// A partir de agora o scheduler pode procurar por threads 
	// no estado 'Initialized' e executar.
	//	


done:
    //?? erro fatal ??
    if( (void*) gui == NULL )
	{
		printf("init_gui:\n"); 
		//gui->initialised = 0;
		//guiStatus = 0;
		return (int) 1;    //Fail.
	};

    gui->initialised = 1;	
    guiStatus = 1;	
	return (int) 0;
};


/*
int guiInit()
{};
*/


void gramado(){
    return; 	
}

int init_gramado(){
	return 0;
}

//
// End.
//

