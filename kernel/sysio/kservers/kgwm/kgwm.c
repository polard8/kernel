/*
 * File: kgwm.c
 * 
 *     kgwm - kernel gramado window manager.
 * 
 * History:
 *     2017 -  Created by fred Nora.
 */
 
// Window manager into the kernel base.
 
// #obs:
// Aplicativo poderão se conectar com o servidor de recusros
// gráficos, principalmente a GUI, que será chamada de 
// Gramado Window Manager.
// Outros window managers poderão ser criados, e eles precisarão 
// ser registrados e abrirem o servidor para usarem seus recursos.
// do mesmo modo o shell atual poderá se registrar,
// o processo de logon poderá se registrar em um servidor de logon.


#include <kernel.h>



// unsigned char  gws_bame[] = "GWS - Gramado Window Server";
// unsigned char  GramadoName[] = "GRAMADO LAYER";

//Status do gwm.
//Qual é o id do processo que é o atual window manager.
//o oficial é o Gramado Window Manager, hoje 
//chamado de shell.bin
//int gws_status;
//int gws_wm_PID;
//int gws_wm_status;


int kgwm_status;
int kgwm_wm_PID;
int kgwm_wm_status;



//
// # internal
//

void gui_create_screen (void);
void gui_create_background (void);
void gui_create_logo (void);
void gui_create_taskbar (void);
void gui_create_mainwindow (void);
void gui_create_controlmenu (void);
void gui_create_infobox (void);
void gui_create_messagebox (void);
void gui_create_debug (void);
void gui_create_navigationbar (void);
void gui_create_grid (void);



//
// cursor
//


/*
void gwsEnableTextCursor ()
{
    g_show_text_cursor = 1;
}

void gwsDisableTextCursor ()
{
    g_show_text_cursor = 0;
}
*/ 

 
//abrir o servidor de janelas. 
int gwsOpen (void){
	
	//Aberto.
	kgwm_status = 1;
	//..

    return 0;
}


//fechar o servidor de janelas
int gwsClose (void){
	
	kgwm_status = 0;

    return 0;
}


// Registrar um window manager.
int kgwmRegisterWindowManager ( int pid ){

    int Status = 0;


    if ( kgwm_status != 1 )
    {
		Status = 1;
		goto fail;
    }else{
		
	    kgwm_wm_PID = (int) pid;
	    kgwm_wm_status = 1;
		goto done;
    };


fail:
    printf("kgwmRegisterWindowManager: fail\n");

done:
    return 0;
}
 

/* 
 *****************************************************
 * create_gui:
 *     Cria as janelas principais: Screen, Background,Logo ...
 *     Cria Window Station, Desktop, Windows, Menu ...
 *     @todo: guiCreate();
 *
 * Obs: esse é o user environment. 
 *(deixe o desenvolvedor saber em qual desktop ele está.)
 */
 
void create_gui (void){
	
	//
	// Select terminal
	//
	
    terminalInit ();
	
	// Set minimal gui set up!.
	//g_guiMinimal = 1;
	
	// Initializing 'gui' structure.
	// Obs: Essa estrutura foi antes usada pelo Logon.
	//      Agora a GUI reinicializa.
	//      Todos os parametros da estrutura precisam ser inicializados.
	// @todo: Estamos reinicializando tudo, recriando estruturas 
	//        que devem ser deletadas na finalização do logon. @todo.

    gui = (void *) kmalloc ( sizeof(struct gui_d) );

    if ( (void *) gui == NULL )
    {
        panic ("create_gui:");

    } else {

		// Set user session, room (Window Station), desktop. 
		// window and menu.
		
        current_usersession = 0;        
        current_room = 0;             
        current_desktop = 0;        

        current_window = 0;         
        current_menu = 0;           


		// #todo: 
		// ?? O logon deveria ter selecionado o perfil do usuário
		// e essa rotina não deveria ser chamada. ??

        init_user_info ();

		// Em ordem:
		// user section, window station and desktop.
		// windows and menus.


        init_user_session ();
#ifdef KERNEL_VERBOSE
        printf ("wm: user session ok\n");
#endif


        init_room_manager ();
#ifdef KERNEL_VERBOSE
        printf ("wm: room ok\n");
#endif


        init_desktop ();
#ifdef KERNEL_VERBOSE 
        printf ("wm: desktop ok\n");
#endif


        init_windows ();
#ifdef KERNEL_VERBOSE 
        printf ("wm: Init windows ok\n");
#endif


        init_menus ();
#ifdef KERNEL_VERBOSE
        printf ("wm: Init menu ok\n");
#endif


		// #bugbug
		// System MenuBar: 
		// (Barra no topo da tela). 

        systemCreateSystemMenuBar ();
#ifdef KERNEL_VERBOSE
        printf ("wm: System menubar ok\n");
#endif


		//
		// Continua ...
		//

    };


	// #importante:
	// Configura quais janelas devem ser pintadas.

    if (g_guiMinimal == 1)
    {
        SetGuiParameters( 0,    // Refresh.  
                          1,    // *Screen.  
                          1,    // *Background. 
                          0,    // Logo.  
                          1,    // *Taskbar. #test. 
                          1,    // *Main.(Desktop window, Área de trabalho) com base na taskbar.  
                          0,    // Menu. 
                          0,    // Info Box. 
                          0,    // Message Box. 
                          0,    // Debug. 
                          0,    // Navigation Bar. 
                          0 );  // Grid. #test.

    }else{

        SetGuiParameters( 0,    // Refresh. 
                          1,    // *Screen.  
                          1,    // *Background. 
                          0,    // Logo.  
                          1,    // *Taskbar. #test.  
                          1,    // *Main.(Desktop window, Área de trabalho) com base na taskbar.  
                          0,    // Menu.  
                          0,    // Info Box. 
                          0,    // Message Box.  
                          0,    // Debug.  
                          0,    // Navigation Bar. 
                          0 );  // Grid. #test.
    };


	// #importante.
	// Checando se 'gui' 'e uma estrutura va'lida.
	// precisaremos dela nas rotinas abaixo.

    if ( (void *) gui == NULL ){
        panic ("create_gui: gui struct");
    }



	// #grupo1:
	//     Base windows:
	//     screen,background,taskbar
	// #grupo2:
	//     main (com base na screen e na taskbar.)
	// #grupo3:
	//     outros.


//creatingWindows:

	//Grupo1:
	//Base windows:
	//screen,background,taskbar

    if (gui->screenStatus == 1)
    { 
        gui_create_screen (); 
    }

    if (gui->backgroundStatus == 1)
    {
        gui_create_background (); 
    }

    if (gui->taskbarStatus == 1)
    {
        gui_create_taskbar (); 
    }


	//grupo2
	//main (com base na screen e na taskbar.)

    if (gui->mainStatus == 1)
    { 
        gui_create_mainwindow (); 
    }

	//grupo3
	//outros.

    if (gui->logoStatus == 1)
    { 
        gui_create_logo (); 
    }

    if (gui->messageboxStatus == 1)
    { 
        gui_create_messagebox (); 
    }

    if (gui->menuStatus == 1)
    { 
        gui_create_controlmenu (); 
    }

    if (gui->navigationbarStatus == 1)
    { 
        gui_create_navigationbar (); 
    }

	// Grid: Dentro do grid haverá sempre 3 partes: 
	//       Header | Content | Footer.
	//       Obs: @todo: O grid deve levar em consideração a
	// área que lhe pertence, ou seja a área de trabalho.  

    if (gui->gridStatus == 1)
    { 
        gui_create_grid (); 
    }


//drawingStrings:

	// Strings.
	// String no background.
	// Obs: Informações de ambiemte para o desenvolvedor.
	//@todo: Informar o desktop atual.

    if ( (void *) CurrentUser != NULL )
    {
        if (g_guiMinimal != 1)
        {
            draw_text ( gui->main, 0, 0, COLOR_WHITE, "User Environment");
            draw_text ( gui->main, 0, 8, COLOR_WHITE, "================");
            draw_text ( gui->main, 8*14, 8*4, 
                COLOR_WHITE, "Welcome to User Environmet, press F1=HELP");
            draw_text ( gui->main, 8*14, 8*5, COLOR_WHITE, 
                "This is the user environment");
            //...

			//Outros:
			//StatusBar( gui->main, "Dektop", "GUI");
			//Message box
			//...
        };

		//Outras opções ?
		//Nothing.
    };


	// Testando client area.
	//draw_text(gui->ClientArea, 8, 8, COLOR_WHITE, ".Desktop");
	//draw_text(gui->screen, 8, 8, COLOR_WHITE, ".Desktop");
	//draw_text(gui->screen, 1*(480/8), 1*(640/8), COLOR_WHITE, ".Desktop"); 
	//StatusBar( gui->screen, "StatusBar: ", "Barra de status na area de trabalho.");


	//
	// #todo: 
	// More ?!!
	//


//done:

	//Refresh.
	//(O 1 avisa que é necessário dar refresh pois foram efetuadas 
	//rotinas de pintura).

    if ( gui->refresh == 1 )
    {
        refresh_screen ();
		
		//Status.
        gui->refresh = 0;  
    }
}



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
	
	// Checa validade da estrutura.

    if ( (void *) gui == NULL )
    {
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
    // #todo: 
    // More ?!!
    //
}


/*
 *****************************************
 * gui_create_screen:
 *     Cria a tela. (Screen)
 *     Atribuindo as dimensões.
 *     ...
 * #todo: 
 * Cria buffer dedicado.
 */

void gui_create_screen (void){

    struct window_d *hWindow; 

    unsigned long Left = (unsigned long) SCREEN_DEFAULT_LEFT;
    unsigned long Top  = (unsigned long) SCREEN_DEFAULT_TOP;
    unsigned long Width = (unsigned long) screenGetWidth ();
    unsigned long Height = (unsigned long) screenGetHeight ();


	// #IMPORTANTE: 
	// Não tem Parent Window!

    if ( (void *) gui == NULL )
    {
        return;
    }

	//Window:
	//Pintado uma janela simples, toda preta, do tamanho da tela 
	//do sispositivo.

    hWindow = (void *) CreateWindow ( 1, 0, VIEW_MINIMIZED, "Screen",
                           Left, Top, Width, Height,
                           0, 0, 0, COLOR_BLACK );

    if ( (void *) hWindow == NULL )
    {
         panic ("gui_create_screen:");
    }else{

        RegisterWindow (hWindow);
        set_active_window (hWindow); 

		// Isso impede que rotinas mudem as caracteríscicas da janela principal 
		// sem antes destravar ou sem ter autorização para isso.

        windowLock (hWindow); 

		// Estrutura gui.
        if ( (void *) gui != NULL )
        {
            gui->screen = (void *) hWindow;
        }

        //Desktop.
        //a janela pertence ao desktop 0
        //hWindow->desktop = (void*) desktop0;

		//Nothing.
    };

	// @todo: 
	// More ??!!

    // #bugbug: 
	// #importante:
	// Não usar set focus nessa que é a primeira janela.
}


/*
 * gui_create_background:
 *     Cria o background. Pinta ele de uma cor.
 *     O background é filha da janela screen.
 *
 * Criando um pano de fundo do mesmo tamaho da tela,
 * Penso que é nessa janela que podemos carregar uma imagem de 
 * pano de fundo.
 *
 * #todo: 
 * Cria buffer dedicado.
 */

void gui_create_background (void){
 
    struct window_d *hWindow; 

    unsigned long Left = (unsigned long) SCREEN_DEFAULT_LEFT;
    unsigned long Top  = (unsigned long) SCREEN_DEFAULT_TOP;
    unsigned long Width = (unsigned long) screenGetWidth ();
    unsigned long Height = (unsigned long) screenGetHeight ();


    if ( (void *) gui == NULL )
    {
        return;
    }


	//Window:
	//0x00808000 (verde)
	//Criando um pano de fundo do mesmo tamaho da tela,
	//Penso que é nessa janela que podemos carregar uma imagem de 
	//pano de fundo.

    hWindow = (void *) CreateWindow ( 1, 0, VIEW_MINIMIZED, "Background", 
                           Left, Top, Width, Height,
                           gui->screen, 0, 0, COLOR_BACKGROUND );

    if ( (void *) hWindow == NULL )
    {
        printf ("gui_create_background:");
        die ();

    }else{

        RegisterWindow (hWindow);
        set_active_window (hWindow); 
        windowLock (hWindow);  


        //Estrutura gui.
        if ( (void *) gui != NULL )
        {
            gui->background = (void *) hWindow;
        }

		//Desktop.
        //a janela pertence ao desktop 0
        //hWindow->desktop = (void*) desktop0;

		//Nothing.
    };


done:
    SetFocus (hWindow);
    return; 
}


/*
 *********************************************************
 * gui_create_taskbar:
 *      Cria a taskbar da área de trabalho. gui->taskbar.
 *      Cria somente a janela que será uada pelo file manager.
 * e que servirá de referência para a janela gui->main
 */

void gui_create_taskbar (void){

    struct window_d *hWindow; 

    unsigned long Left = (unsigned long) SCREEN_DEFAULT_LEFT;
    unsigned long Top  = (unsigned long) SCREEN_DEFAULT_TOP;
    unsigned long Width = (unsigned long) screenGetWidth ();
    unsigned long Height = (unsigned long) screenGetHeight ();


    if ( (void *) gui == NULL )
    {
        return;
    }


    // draw bar

    Height = (Height/8);

    hWindow = (void *) CreateWindow ( 1, 0, VIEW_MINIMIZED, "taskbar", 
                           Left, Top, Width, Height, 
                           gui->screen, 0, 0, COLOR_WINDOW );

    if ( (void *) hWindow == NULL)
    {
        printf ("gui_create_taskbar:\n");
        die ();

    }else{

        RegisterWindow (hWindow);
        windowLock (hWindow); 

        if ( (void *) gui != NULL )
        {
            gui->taskbarStatus = (int) 1;
            gui->taskbar = (void *) hWindow;
        }

		//...
    };

	//...

    //return; 
}


/*
 ***********************************************
 * gui_create_mainwindow:
 *      A área de trabalho.
 *
 *      *Importante: É a área disponível na tela para o aplicativo. 
 *      Onde ficam os ícones.
 *      
 *     A área de trabalho é toda a tela menos a GMB(Global Menu Bar) e 
 * menos a TaskBar. 
 * #todo: 
 * Criar o buffer dedicado para a janela principal.
 *
 * #Obs: 
 * Essa janela é especial e usará o Backbuffer como buffer dedicado.
 */

void gui_create_mainwindow (void){

    struct window_d *hWindow; 

    unsigned long Left = (unsigned long) SCREEN_DEFAULT_LEFT;
    unsigned long Top  = (unsigned long) SCREEN_DEFAULT_TOP;
    unsigned long Width = (unsigned long) screenGetWidth ();
    unsigned long Height = (unsigned long) screenGetHeight ();


	//estrutura gui.
    if ( (void *) gui == NULL )
    {
        printf ("gui_create_mainwindow: gui\n");
        die ();
    }


	//janela taskbar.
    if ( (void *) gui->taskbar == NULL )
    {
        printf ("gui_create_mainwindow: taskbar\n");
        die ();
    }


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

    hWindow = (void *) CreateWindow ( 1, 0, VIEW_MINIMIZED, "gramado desktop window", 
                           Left, Top, Width, Height,           
                           gui->screen, 0, 0, COLOR_WINDOW );   

    if ( (void *) hWindow == NULL)
    {
        printf ("gui_create_mainwindow:\n");
        die ();

     }else{   

        RegisterWindow (hWindow);
        windowLock (hWindow); 
        set_active_window (hWindow); 

        //a janela pertence ao desktop 0
        //hWindow->desktop = (void*) desktop0;

        if ( (void *) gui == NULL )
        {
            return;
        }else{
            gui->main = (void *) hWindow;
        };
    };



	//  Desktop Window:
	//      Criar a janela gui->desktop.
	//      Na verdade a janela do desktop
	//      é a janela da área de trabalho.
	// @todo:
	// #bugbug: Confunde-se com a estrutura de desktop_d.


    /*
	gui->desktop = (void*) CreateWindow( 1, 0, VIEW_MINIMIZED, "Desktop Window", 
	                                0, 16, 800, 600-16-16, 
							        gui->screen, 0, 0, COLOR_WINDOW ); 
	*/


	gui->desktop = (void *) gui->main;

    if ( (void *) gui->desktop == NULL)
    {
        gui->desktop = (void *) gui->screen;

        if ( (void *) gui->desktop == NULL)
        { 
            SetFocus (hWindow);
            return; 
        }
    }


	//Não registrar pois main menu ja está registrada.
	//RegisterWindow(gui->desktop);

    SetFocus (hWindow);
}




/*
 * gui_create_logo:
 *     Cria a janela para o logo da área de trabalho. 
 * O logo da área de trabalho é a imagem da área de trabalho.
 *
 * #todo: 
 * Cria buffer dedicado.
 */

// # suspensa

void gui_create_logo (void){ 


/*
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

	SetFocus(hWindow);
 */

}



/*
 * gui_create_controlmenu:
 *     Esse é o controlmenu da area de trabalho.
 * mesmo que nao esteja rodando o programa gerenciador de
 * deprogramas esse control menu existirá.
 */

// # suspensa

void gui_create_controlmenu (void)
{ 

/*
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

}


/*
 *gui_create_infobox:
 * janelinha de informações do sistema.
 * avisa o usuario sobre eventos do sistema.
 *como novos dispositivos encontrados.
 * @todo: Cria buffer dedicado.
 */

void gui_create_infobox (void){
 
    if ( (void *) gui == NULL )
    {
        return;
    }else{

        gui->infobox = NULL;
    };    
}


/*
 * Cria a janela para message box.
 */

void gui_create_messagebox (void){
 
    if ( (void *) gui == NULL )
    {
        return;
    }else{

        gui->messagebox = NULL;
    };
}


/*
 ******************
 * cria uma janela para debug do kernel. será um progama em kernel mode.
 * @todo: Cria buffer dedicado.
 */

void gui_create_debug (void){
 
    if ( (void *) gui == NULL )
    {
        return;
    }else{

        gui->debug = NULL;
    };

	// #todo: 
	// Efetuará ou não algum tipo de debug de inicialização ou
	// dos elementos básicos do sistema. Essa tela de debug
	// pode se mostrar uma opção importante para o desenvolvedor.
	// Mostraria um log de acertos e problemas durante o processo 
	// de inicialização do sistema operacional.
}


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

// #suspensa
 
void gui_create_navigationbar (void){


/*
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
//  if( (void*) gui->navigationbar != NULL )
//  {
//        //draw_text( gui->navigationbar, 1*(800/8), 8, COLOR_WINDOWTEXT, "/WindowStation0/Desktop0 GUI");
//        //draw_text( gui->navigationbar, 5*(800/8), 8, COLOR_WINDOWTEXT, "F1=HELP");
//  };


    // Continua ...
    
done:
    SetFocus(hWindow); 
*/ 

}


/*
 **************************
 * gui_create_grid:
 *
 *     Apenas autoriza a utilização de um grid na area de trabalho. 
 *     Havendo essa altorização, o gerenciador de arquivos poderá
 *     desenhá-lo. 
 *     cada item será um arquivo da pasta "area de trabalho".
 * 
 * #todo: 
 * Cria buffer dedicado.
 */

void gui_create_grid (void){
 
    if ( (void *) gui == NULL )
    {
        return;
    }else{

		//initScreenGrid();
        gui->grid = NULL;
    };
}


//screen
//métrica do dispositivo.

void *guiGetScreenWindow (void){

    if ( (void *) gui == NULL)
    {
        return NULL;
    }


    return (void *) gui->screen;
}



//developer screen

void *guiGetDeveloperScreenWindow (void){

    if ( (void *) gui == NULL)
    {
        return NULL;
    }


    return (void *) gui->DEVELOPERSCREEN;
}



//background

void *guiGetBackgroundWindow (void){

    if ( (void *) gui == NULL)
    {
        return NULL;
    }


    return (void *) gui->background;
}


//logo

void *guiGetLogoWindow (void){

    if ( (void *) gui == NULL)
    {
        return NULL;
    }


    return (void *) gui->logo;
}


//desktop window
void *guiGetDesktopWindow (void){

    if ( (void *) gui == NULL)
    {
        return NULL;
    }

    return (void *) gui->desktop;
}


//task bar, top window, mac style

void *guiGetTaskbarWindow (void){

    if ( (void *) gui == NULL)
    {
         return NULL;
    }


    return (void *) gui->taskbar;
}


//main window
//GetDesktopWindow

void *guiGetMainWindow (void){

    if ( (void *) gui == NULL)
    {
        return NULL;
    }

    return (void *) gui->main;
}


//status bar window (do kernel base)

void *guiGetStatusbarWindow (void){

    if ( (void *) gui == NULL)
    {
        return NULL;
    }

    return (void *) gui->statusbar;
}


//grid window (do kernel base)

void *guiGetGridWindow (void){

    if ( (void *) gui == NULL)
    {
        return NULL;
    }

    return (void *) gui->grid;
}


//janela do 'control menu' atual.

void *guiGetMenuWindow (void){

    if ( (void *) gui == NULL)
    {
        return NULL;
    }

    return (void *) gui->menu;
}


//infobox (o sistema envia mensagens de informação)

void *guiGetInfoboxWindow (void){

    if ( (void *) gui == NULL)
    {
        return NULL;
    }


    return (void *) gui->infobox;
}


//tooltip  Janelinha que aparece quando repousa o mouse sobre elemento gráfico.

void *guiGetTooltipWindow (void){

    if ( (void *) gui == NULL)
    {
        return NULL;
    }

    return (void *) gui->tooltip;
}


//message box do kernel base. 

void *guiGetMessageboxWindow (void){

    if ( (void *) gui == NULL)
    {
        return NULL;
    }

    return (void *) gui->messagebox;
}


//dialogbox do kernel base. 

void *guiGetDialogboxWindow (void){

    if ( (void *) gui == NULL)
    {
        return NULL;
    }

    return (void *) gui->dialogbox;
}


//janela de debug usada pelo kernel base.

void *guiGetDebugWindow (void){

    if ( (void *) gui == NULL)
    {
        return NULL;
    }

    return (void *) gui->debug;
}


// ?
// menubar usada pelo kernel base.

void *guiGetMbhWindowWindow (void){

    if ( (void *) gui == NULL)
    {
        return NULL;
    }

    return (void *) gui->mbhWindow;
}


//top bar.
void *guiGetTopbarWindow (void){

    if ( (void *) gui == NULL)
    {
        return NULL;
    }

    return (void *) gui->topbar;
}


//navigation bar, estilo mobile.
//gerenciada pelo kernel base.

void *guiGetNavigationbarWindow (void){

    if ( (void *) gui == NULL)
    {
        return NULL;
    }

    return (void *) gui->navigationbar;
}


//janela do shell do kernel base.
//naõ é um processo.

void *guiGetShellWindowWindow (void){

    if ( (void *) gui == NULL)
    {
        return NULL;
    }

    return (void *) gui->shellWindow;
}


//uma janela filha do shell do kernel base.
void *guiGetShellClientWindowWindow (void){

    if ( (void *) gui == NULL )
    {
        return NULL;
    }

    return (void *) gui->shellClientWindow;
}


// reposiciona e muda o tamanho da gui->main window.
// configura a área de trabalho.
void 
guiSetUpMainWindow ( unsigned long x, 
                     unsigned long y, 
                     unsigned long width, 
                     unsigned long height )
{

    unsigned long Left = (unsigned long) SCREEN_DEFAULT_LEFT;
    unsigned long Top  = (unsigned long) SCREEN_DEFAULT_TOP;
    unsigned long Width = (unsigned long) screenGetWidth ();
    unsigned long Height = (unsigned long) screenGetHeight ();


	//check limits

    if ( x > Width || y > Height )
    { 
        return; 
    }
        
    if ( width > Width || height > Height )
    { 
        return; 
    }


    if ( (void *) gui == NULL )
    {
        return;
    }



    if ( (void *) gui->main == NULL )
    {
        return;
    }else{

        replace_window (gui->main, x, y);
        resize_window ( gui->main, width, height);
    };

	//Nothing.
}



/*
 *********************************************
 * init_gui:
 * 
 *     Inicializa a GUI.
 *     É preciso criar a GUI antes de inicializar.
 * 
 *     #todo: 
 *     Mudar para guiInit().
 *
 * Obs: 
 * Nada além de recursos gráficos. 
 */

int init_gui (void){
	
	// ??
	// Habilita taskswitch e scheduler.

    set_task_status (UNLOCKED);
    scheduler_unlock ();
		
	//SetProcedure( (unsigned long) &system_procedure);	


	// A partir de agora o scheduler pode procurar por threads 
	// no estado 'Initialized' e executar.


    if ( (void *) gui == NULL )
    {
		// #obs:
		// Incluímos o die() (23 nov 2019).
		// Vamos parar caso a estrutura 'gui' seja inválida.

        guiStatus = 0;
        printf ("init_gui: gui struct\n"); 
        die ();
        //return (int) 1;    //Fail.
    }


    gui->initialised = 1;
    guiStatus = 1;

    return 0;
}


/*
 *********************************************
 * kgwm_mouse_dialog:
 * 
 *     O system_procedure redireciona para cá as mensagens de mouse.
 *     Lembrando que o aplicativo em ring3 chamou o system_procedure
 *  quando invocou o defered procedure. (defered/default)
 */

unsigned long
kgwm_mouse_dialog ( struct window_d *window,
                    int msg,
                    unsigned long long1,
                    unsigned long long2 )
{

    // #todo
    // Checar validade da estrutura.
    
    if ( window->isControl == 1 )
    {
        return (unsigned long) kgwm_window_control_dialog ( window,
                                   msg,
                                   long1,
                                   long2 ); 
    } 

    switch (msg)
    {
		// #teste
		// testando quando o aplicativo chama o procedimento default,.
		// o teste sera para o click do mouse.
		// no nosso teste esse click é tratado pelo aplicativo,
		// mas a mesnagem chegará aqui para tratarmos os botões gerenciados 
		// pelo servidor kgws.

		// #obs
		// Vamos tratar aqui vários eventos de mouse;

        case 30:
        
			//qual botão do mouse?
			switch (long1)
			{
				//botão 1
				case 1:
					break;

				case 2:
					break;

				case 3:
					break;
			}
			break;

        //#todo
		//case 31:
			//break;


        default:
            break;
    }; //switch


    return 0;
}



unsigned long
kgwm_window_control_dialog ( struct window_d *window,
                             int msg,
                             unsigned long long1,
                             unsigned long long2 )
{

    //#bugbug
    if ( window->isControl != 1 )
    {
		printf ("kgwm_window_control_dialog: isControl ?");
		die ();
		//return 0;
    }

	switch (msg)
	{

        // mouse button down
        case 30:
			//qual botão do mouse?
			switch (long1)
			{
				//botão 1	
				case 1:
				    // Se esse controle é um botão.
				    if ( window->isButton == 1 )
				    {
						button_down ( window );

			            //#debug
			            //printf ("kgwm_window_control_dialog: mouse keydown, window name %s \n",
			             //   window->name ); 
			            //refresh_screen();
			            return 0;
					}
				    break;
				    
			};
				
		// mouse button up
		case 31:
		    switch (long1)
		    {
				case 1:
				    // Se esse controle é um botão.
				    if ( window->isButton == 1 )
				    {
						button_up ( window );

			        //#debug
			        //printf ("kgwm_window_control_dialog: mouse keyup, window name %s \n",
			            //window->name ); 
			        //refresh_screen();
			        
                    if ( window->isMinimize == 1 )
                    {
                      window->control->window = window; //afeta esse botão
                      window->control->msg = MSG_HIDE;
                      window->control->long1 = 0;
                      window->control->long2 = 0;
                      window->control->newmessageFlag = 1;
                    }
                    //if ( window->isRestore == 1 ){} //#todo: Criar esse elemento na struct
                    if ( window->isMaximize == 1 )
                    {
                      window->control->window = window; //afeta esse botão
                      window->control->msg = MSG_MAXIMIZE;
                      window->control->long1 = 0;
                      window->control->long2 = 0;
                      window->control->newmessageFlag = 1;
                    }
                    if ( window->isClose == 1 )
                    {
                      window->control->window = window; //afeta esse botão
                      window->control->msg = MSG_CLOSE;
                      window->control->long1 = 0;
                      window->control->long2 = 0;
                      window->control->newmessageFlag = 1;
                    }
			        if ( window->isScrollBarButton1 == 1 )
                    {
                      window->control->window = window;   //afeta esse botão
                      window->control->msg = MSG_VSCROLL; //8812; //scroll up.
                      window->control->long1 = 1;  //up
                      window->control->long2 = 0;
                      window->control->newmessageFlag = 1;
                    }
                    if ( window->isScrollBarButton2 == 1 )
                    {
			            printf ("Scroll Bar: = \n"); 
			            refresh_screen();
                    }
			        if ( window->isScrollBarButton3 == 1 )
                    {
                      window->control->window = window; //afeta esse botão
                      window->control->msg = MSG_VSCROLL; //8811; //scroll down.
                      window->control->long1 = 0;  //down
                      window->control->long2 = 0;
                      window->control->newmessageFlag = 1;
                    }
			        
			        return 0;
					}
				    break;
			};
		    break;		
				
				
	};


    return 0;
}

/*
int guiInit()
{}
*/

 

int init_gramado (void)
{
    return 0;
}



/*
int gwsInit();
int gwsInit()
{
	printf ("GWS:")
	//#todo:
	
}
*/


//
// End.
//

