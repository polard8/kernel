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
int gwsOpen (void)
{
	//Aberto.
	kgwm_status = 1;
	//..

    return 0;
}


//fechar o servidor de janelas
int gwsClose (void)
{
	kgwm_status = 0;

    return 0;
}


// Registrar um window manager.
int kgwmRegisterWindowManager ( int pid )
{
    int Status = 0;


    if ( kgwm_status != 1 )
    {
        Status = 1;
        goto fail;
    
    }else{
        kgwm_wm_PID = (int) pid;
        kgwm_wm_status = 1;
        return 0;
    };

fail:
    printf("kgwmRegisterWindowManager: fail\n");
    return Status;
}


/*
 * SetGuiParameters:
 *     Configura a inicialização das janelas gerenciadas pelo kernel.
 *     @todo: Limite de janelas (+- 10)
 *
 */
 
void 
SetGuiParameters(
    int refresh,        //Flag. Colocar ou não o backbuffer na tela.
    int screen,         //Tela do computador.
    int background,     //Background da area de trabalho. 
    int logo,           //Logo, Janela para imagem da área de trabalho.
    int taskbar,        //Barra de tarefas.(Ícones para programas).
    int main,           //Janela principal.(Desktop, ou Kernel Setup Utility). 
    int menu,           //Control menu da Área de trabalho.
    int infobox,        //Janelinha no canto, para alerta sobre sobre eventos ocorridos no sistema.
    int messagebox,     //O message box do kernel.(Cada app cria seu messagebox). 
    int debug,          //Janela do debug do kernel.(sonda por problemas).
    int navigationbar,  //Janela de navegação(Semelhante a navigation bar dos dispositivos mobile). 
    int grid )          //Grid da janela principal.
{ 

    //Passados via argumento.
	
	//
	//@todo: gui status. fail or not.
	//
	
	// Checa validade da estrutura.

    if ( (void *) gui == NULL ){
        debug_print ("SetGuiParameters: gui\n");
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
    
    unsigned long Width  = (unsigned long) screenGetWidth ();
    unsigned long Height = (unsigned long) screenGetHeight ();


	// #IMPORTANTE: 
	// Não tem Parent Window!

    if ( (void *) gui == NULL ){
        debug_print ("gui_create_screen: gui\n");
        return;
    }

	//Window:
	//Pintado uma janela simples, toda preta, do tamanho da tela 
	//do sispositivo.

    hWindow = (void *) CreateWindow ( 1, 0, VIEW_MINIMIZED, "Screen",
                           Left, Top, Width, Height,
                           0, 0, 0, COLOR_BLACK );

    if ( (void *) hWindow == NULL ){
         panic ("gui_create_screen: hWindow");

    }else{
        RegisterWindow (hWindow);
        set_active_window (hWindow); 

        // Isso impede que rotinas mudem as caracteríscicas 
        // da janela principal 
        // sem antes destravar ou sem ter autorização para isso.

        windowLock (hWindow); 

		// Estrutura gui.
        if ( (void *) gui != NULL ){
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
    
    unsigned long Width  = (unsigned long) screenGetWidth ();
    unsigned long Height = (unsigned long) screenGetHeight ();


    if ( (void *) gui == NULL ){
        debug_print ("gui_create_background: gui\n");
        return;
    }


	//Window:
	//0x00808000 (verde)
	//Criando um pano de fundo do mesmo tamaho da tela,
	//Penso que é nessa janela que podemos carregar uma imagem de 
	//pano de fundo.

    hWindow = (void *) CreateWindow ( 1, 0, VIEW_MINIMIZED, "Background", 
                           Left, Top, Width, Height,
                           gui->screen, 0, 0, 0x00008080 );


    if ( (void *) hWindow == NULL ){
        panic ("gui_create_background:");

    }else{
        RegisterWindow (hWindow);
        set_active_window (hWindow); 
        windowLock (hWindow);  


        //Estrutura gui.
        if ( (void *) gui != NULL ){
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
    
    unsigned long Width  = (unsigned long) screenGetWidth ();
    unsigned long Height = (unsigned long) screenGetHeight ();


    if ( (void *) gui == NULL ){
        debug_print ("gui_create_taskbar: gui\n");
        return;
    }


    // draw bar

    Height = (Height/8);

    hWindow = (void *) CreateWindow ( 1, 0, VIEW_MINIMIZED, "taskbar", 
                           Left, Top, Width, Height, 
                           gui->screen, 0, 0, COLOR_WHITE );

    if ( (void *) hWindow == NULL){
        panic ("gui_create_taskbar:\n");

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
    
    unsigned long Width  = (unsigned long) screenGetWidth ();
    unsigned long Height = (unsigned long) screenGetHeight ();


	//estrutura gui.
    if ( (void *) gui == NULL ){
        panic ("gui_create_mainwindow: gui\n");
    }


	//janela taskbar.
    if ( (void *) gui->taskbar == NULL ){
        panic ("gui_create_mainwindow: taskbar\n");
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

    hWindow = (void *) CreateWindow ( 1, 0, VIEW_MINIMIZED, "desktop window", 
                           Left, Top, Width, Height,           
                           gui->screen, 0, 0, COLOR_WHITE );   

    if ( (void *) hWindow == NULL){
        panic ("gui_create_mainwindow:\n");

     }else{   

        RegisterWindow (hWindow);
        windowLock (hWindow); 
        set_active_window (hWindow); 

        //a janela pertence ao desktop 0
        //hWindow->desktop = (void*) desktop0;

        if ( (void *) gui == NULL ){
            //message
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
							        gui->screen, 0, 0, COLOR_WHITE ); 
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





void gui_create_logo (void)
{ 
    debug_print ("gui_create_logo: deprecated\n");
}


void gui_create_controlmenu (void)
{ 
    debug_print ("gui_create_controlmenu: deprecated\n");
}



/*
 *gui_create_infobox:
 * janelinha de informações do sistema.
 * avisa o usuario sobre eventos do sistema.
 *como novos dispositivos encontrados.
 * @todo: Cria buffer dedicado.
 */

void gui_create_infobox (void){
 
    if ( (void *) gui == NULL ){
        debug_print ("gui_create_infobox: gui\n");
        return;
    
    }else{
        gui->infobox = NULL;
    };    
}


/*
 * Cria a janela para message box.
 */

void gui_create_messagebox (void){
 
    if ( (void *) gui == NULL ){
        debug_print ("gui_create_messagebox: gui\n");
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
 
    if ( (void *) gui == NULL ){
        debug_print ("gui_create_debug: gui\n");
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


// deletar
void gui_create_navigationbar (void)
{
    debug_print ("gui_create_navigationbar: deprecated\n");
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
 
    if ( (void *) gui == NULL ){
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

    if ( (void *) gui == NULL){
        //message
        return NULL;
    }


    return (void *) gui->DEVELOPERSCREEN;
}



//background

void *guiGetBackgroundWindow (void){

    if ( (void *) gui == NULL){
        //message
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
guiSetUpMainWindow ( 
    unsigned long x, 
    unsigned long y, 
    unsigned long width, 
    unsigned long height )
{

    unsigned long Left = (unsigned long) SCREEN_DEFAULT_LEFT;
    unsigned long Top  = (unsigned long) SCREEN_DEFAULT_TOP;
    
    unsigned long Width  = (unsigned long) screenGetWidth ();
    unsigned long Height = (unsigned long) screenGetHeight ();


	//check limits

    if ( x > Width || y > Height )
    { return; }

    if ( width > Width || height > Height ) 
    { return; }

    if ( (void *) gui == NULL )
    { return; }


    if ( (void *) gui->main == NULL )
    {
        return;

    }else{
        replace_window (gui->main, x, y);
        resize_window ( gui->main, width, height);
    };

	//Nothing.
}


int register_wm_process ( pid_t pid ){

    if (pid<0 || pid >= PROCESS_COUNT_MAX ){
        debug_print("register_wm_process: pid fail\n");
        return -1;
    }

    if ( __gpidWindowManager != 0 ){
        debug_print("register_wm_process:\n");
        return -1;
    }

    __gpidWindowManager = (pid_t) pid;
    
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
kgwm_mouse_dialog ( 
    struct window_d *window,
    int msg,
    unsigned long long1,
    unsigned long long2 )
{

    //#todo: No more mouse support for this window server.
    debug_print("kgwm_mouse_dialog: [DEPRECATED]\n");
    
    // #todo
    // Checar validade da estrutura.
    
    if ( window->isControl == 1 ){
        return (unsigned long) kgwm_window_control_dialog ( window,
                                   msg, long1, long2 ); 
    } 

    return 0;
}



unsigned long
kgwm_window_control_dialog ( 
    struct window_d *window,
    int msg,
    unsigned long long1,
    unsigned long long2 )
{

    //#bugbug
    if ( window->isControl != 1 ){
        panic ("kgwm_window_control_dialog: isControl ?");
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
                        window->control->ke_window = window; //afeta esse botão
                        window->control->ke_msg    = MSG_HIDE;
                        window->control->ke_long1  = 0;
                        window->control->ke_long2  = 0;

                        window->control->ke_newmessageFlag = TRUE;
                    }
                    //if ( window->isRestore == 1 ){} //#todo: Criar esse elemento na struct
                    if ( window->isMaximize == 1 )
                    {
                        window->control->ke_window = window; //afeta esse botão
                        window->control->ke_msg    = MSG_MAXIMIZE;
                        window->control->ke_long1  = 0;
                        window->control->ke_long2  = 0;

                        window->control->ke_newmessageFlag = TRUE;
                    }
                    if ( window->isClose == 1 )
                    {
                        window->control->ke_window = window; //afeta esse botão
                        window->control->ke_msg    = MSG_CLOSE;
                        window->control->ke_long1  = 0;
                        window->control->ke_long2  = 0;

                        window->control->ke_newmessageFlag = TRUE;
                    }

                    return 0;
                }
                break;
            };
            break;
    };

    return 0;
}


int init_gramado (void)
{
    debug_print ("init_gramado: [DELETE THIS]\n");
    return 0;
}


//
// End.
//

