/*
 * Arquivo: gui.c
 *
 * Descrição:
 * Arquivo principal do Módulo GUI.
 * Responsável for oferecer rotinas gráficas em kernel mode.
 * Esse módulo está incluído no kernel base, a vantagem é ganho de velocidade.
 *
 * OBS: 
 *     A GUI deve ser mínima. 
 *     Com pouquíssimos recursos visuais oferecidos em kernel mode.
 *     O mais importante é que o kernel configure, 
 * user section, window station, desktops.
 *      
 *     Ao iniciar o ambiente do usuário (gui) (área de trabalho) deve-se 
 * apenas criar as janelas que servirão de backgrounds para aplicativos 
 * como (task bar) (menu bar) (menus) etc ... 
 * Apenas inicialize essas janelas.
 *
 * Obs: @todo: Ao fim da rotina de inicialização, podemos criar
 * os buffers adicionais. Os buffers dedicados devem ser criados
 * pela rotina Create window.
 *
 * @todo: Identifies Session components
 *         A inicialização da gui precisa identificar componentes de sessão.
 * Versão 1.0, 2015, 2016.
 */
 

#include <kernel.h>


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
 * Obs: esse é o user environment. (deixe o desenvolvedor saber em qual desktop ele está.)
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
    if((void*) gui == NULL)
	{	
	    printf("create_gui:");
		refresh_screen();
		while(1){};
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
		
		printf("create_gui: User Session..\n");
		init_user_session();
				
		printf("create_gui: Window Station..\n");
		init_window_station();
	    
		printf("create_gui: Desk..\n");
	    init_desktop();	
	    
		printf("create_gui: Wind..\n");
	    init_windows();	
	    
		printf("create_gui: Menu..\n");
	    init_menus();
		
		//
		// System MenuBar: (Barra no topo da tela). 
		//
		
		printf("create_gui: System Menu bar..\n");
		systemCreateSystemMenuBar();
		
		//
		// Continua ...
        //
		
    };
	
	
	//
	// Configura quais janelas devem ser pintadas.
	//
	
    if(g_guiMinimal == 1){		
        SetGuiParameters(0,1,1,0,0,1,0,0,0,0,0,0); 	
	}else{
		
        SetGuiParameters( 0,    //Refresh.         
                          1,    //*Screen.          
                          1,    //*Background.       
                          0,    //Logo.            
                          0,    //Taskbar. #test.        
                          1,    //*Main.(Desktop window, Área de trabalho)             
                          0,    //Menu.           
                          0,    //Info Box.         
                          0,    //Message Box.       
                          0,    //Debug.           
                          1,    //Navigation Bar.    
                          0 );  //Grid. #test.	
						   
	};
  	
	//
	// *** Filtro importante.
	//
	
	if( (void*) gui == NULL )
	{
		printf("create_gui ERROR: gui struct!");
		refresh_screen();
		while(1){};
	};
	
	//
	// Pinta as janelas da GUI que foram selecionadas. 
	// 1) Screen, Background, Logo.
	// 2) Main window, Navigation window
	// 3) Taskbar, Menu ...
	//
		
	//Screen, Background, Main and Logo.
    
	if(gui->screenStatus == 1){ 
	    gui_create_screen(); 
	};
	
	if(gui->backgroundStatus == 1){	
	    gui_create_background(); 
	};
	
    if(gui->mainStatus == 1){ 
	    gui_create_mainwindow(); 
	};
	
	if(gui->logoStatus == 1){ 
	    gui_create_logo(); 
	};	

	//Taskbar, Message box, Control menu and Navigation bar.
	
	if(gui->taskbarStatus == 1){	
	    gui_create_taskbar(); 
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
	
	//
	// Strings.
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
			draw_text(gui->main, 8*14, 8*4, COLOR_WHITE, "Welcome to User Environmet, press F1=HELP.");
			//draw_text(gui->main, 8*10, 8*11, COLOR_WHITE, "F1=HELP");
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
	    gui->logoStatus = logo;
	    gui->mainStatus = main; 	
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
	
	hWindow = (void*) CreateWindow(1,0,VIEW_MINIMIZED,"Screen",
	                               Left, Top, Width, Height,
						           0,0,0,COLOR_BLACK);     
	if( (void*) hWindow == NULL)
	{
	    printf("gui_create_screen:");
		refresh_screen();
	    while(1){};
	}else{

		RegisterWindow(hWindow);
		set_active_window(hWindow); 
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
 * @todo: Cria buffer dedicado.
 */
void gui_create_background()
{ 
    struct window_d *hWindow; 
	
	if( (void*) gui == NULL ){
        return;
    };		
	
	hWindow = (void*) CreateWindow( 1,0,0,"Background", 
		                            0,0,800,600, 
							        gui->screen,0,0,COLOR_BACKGROUND);  
	if( (void*) hWindow == NULL )
	{
	    printf("gui_create_background:");
		refresh_screen();
	    while(1){};
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
 * gui_create_logo:
 *     Cria a janela para o logo da área de trabalho. O logo da área de 
 * trabalho é a imagem da área de trabalho.
 *
 * @todo: Cria buffer dedicado.
 */
void gui_create_logo()
{ 
    struct window_d *hWindow; 
	
	if( (void*) gui == NULL ){
        return;
    };		
	
	//O logo pertence ao desktop.
	hWindow = (void*) CreateWindow( 2, 0, 0, "Logo", 
	                                800/3, 600/3, 800/3, 600/3, 
							        gui->screen, 0, 0, COLOR_WINDOW);
	if( (void*) hWindow == NULL)
	{
	    printf("gui_create_logo:");
	    refresh_screen();
		while(1){};
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
    return; 
};


/*
 * gui_create_taskbar:
 *      Cria a taskbar da área de trabalho.
 *
 *      @todo: na verdade a taskbar na area de
 * trabalho deve ser a taskbar do aplicativo em user mode
 * responsável pelo gerenciamento de programas. Programm Manager.
 * o que inclui o menu iniciar. 
 * Quando a taskbar estiver na vertical, não poderá sobrepor
 * a GMB (Global Manu Bar). sendo ela seu limite superior.
 * 
 * @todo: Cria buffer dedicado.
 */
void gui_create_taskbar()
{ 
	struct window_d *hWindow;  

    //
	// @todo: Criar o ambiente para a barra de tarefas (task bar).
	//
	
	if( (void*) gui == NULL ){
        return;
    };		
	
draw_bar:	
	//A navigation bar perence a janela principal.
	hWindow = (void*) CreateWindow( 1, 0, 0, "TaskBar", 
	                                0, 800-32, 800, 32, 
							        gui->screen, 0, 0, COLOR_BLUE);	
	if( (void*) hWindow == NULL)
	{
	    printf("gui_create_taskbar:");
		refresh_screen();
	    while(1){};
	}else{
	    		
	    RegisterWindow(hWindow);
		set_active_window(hWindow); 
	    windowLock(hWindow); 
	    
		if( (void*) gui != NULL ){
            gui->taskbarStatus = (int) 1;
			gui->taskbar = (void*) hWindow;
	    };
		
		//Desktop.
		//a janela pertence ao desktop 0
	    //hWindow->desktop = (void*) desktop0;
		
	};
	
	//
	// Buttons.
	//
	
draw_buttons:

	//Window Menu ( system menu ) fecha janelas e programas.
    draw_button( (void*) gui->taskbarStatus, "Menu", 1, 0*(800/8), 8, 100, 24, COLOR_WINDOW);	
				 		 
	//File Menu (gerencia a criação de arquivos.)
    draw_button( (void*) gui->taskbarStatus, "File", 1, 1*(800/8), 8, 100, 24, COLOR_WINDOW);	
	
	//
    // Continua ...
    //	
    
done:	
	SetFocus(hWindow);
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
 * @todo: Cria buffer dedicado.
 */
void gui_create_mainwindow()
{
    struct window_d *hWindow; 
	
	if( (void*) gui == NULL ){
        return;
    };	
	
	//A janela principal perence ao desktop
	hWindow = (void*) CreateWindow( 1, 0, VIEW_MINIMIZED, "Area de Trabalho", 
	                                0, 0, 800, 600-32, 
							        gui->screen, 0, 0, COLOR_WINDOW ); 
	if( (void*) hWindow == NULL){
	    printf("gui_create_mainwindow:");
	    refresh_screen();
		while(1){};
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
 * gui_create_controlmenu:
 *     Esse é o controlmenu da area de trabalho.
 * mesmo que nao esteja rodando o programa gerenciador de
 * deprogramas esse control menu existirá.
 *
 */
void gui_create_controlmenu()
{ 
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
		refresh_screen();
		while(1){}	
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
	struct window_d *hWindow;  

	if( (void*) gui == NULL ){
        return;
    };	    
	
	hWindow = (void*) CreateWindow( 1, 0, 0, "NavigationBar", 
	                                0, 600-(8*5), 800, (8*5), 
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
		
		if( (void*) gui == NULL){
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
	             1*(800/16), 8, 24, 24, COLOR_BLACK);				   
	//Home.
    draw_button( gui->navigationbar, "O", 1, 
	             2*(800/16), 8, 24, 24, COLOR_BLACK);	
	//TaskList, (lista os processos).
    draw_button( gui->navigationbar,  "=", 1, 
	             3*(800/16), 8, 24, 24, COLOR_BLACK);	
	
    // Text. 
    //draw_text( gui->navigationbar, 1*(480/8), 8, COLOR_WINDOWTEXT, ".Desktop"); 	
	
	
/*
    * Text.   
    if( (void*) gui->navigationbar != NULL )
	{
        //draw_text( gui->navigationbar, 1*(800/8), 8, COLOR_WINDOWTEXT, "/WindowStation0/Desktop0 GUI");
        //draw_text( gui->navigationbar, 5*(800/8), 8, COLOR_WINDOWTEXT, "F1=HELP");
	};
*/	


    // Continua ...
    
done:	
    SetFocus(hWindow);     
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



/*
 * init_gui:
 *     Inicializa a GUI.
 *     É preciso criar a GUI antes de inicializar.
 *     @todo: Mudar para guiInit(). 
 */
int init_gui()
{
	// Habilita taskswitch e scheduler.
	set_task_status(UNLOCKED);
    scheduler_unlock();	 	
		
	//SetProcedure( (unsigned long) &system_procedure);	
	
	//
	// A partir de agora o scheduler pode procurar por threads 
	// no estado 'Initialized' e executar.
	//	 
		
done:
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

//
// End.
//

