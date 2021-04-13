/*
 * File: gws.c
 * 
 *     Part of the Gramado Window Server.
 *
 * History:
 *     2019 - Created by Fred Nora.
 */



// Window server routines.
#include <gws.h>



int dirty=0;
int background=0;



/*
// #test
// from: x-window-system
int
gws_WriteToClient ( 
    struct gws_client_d *who, 
    int count, 
    char *buf );
int
gws_WriteToClient ( 
    struct gws_client_d *who, 
    int count, 
    char *buf )
{
    return -1;
}
*/


/*
 *******************************************
 * xxxThread:
 *     Um thread dentro para testes.
 */

void xxxThread (void){

    printf("\n");
    printf("$\n");
    //printf("$$\n");
    //printf("$$$\n");
    printf("#### This is a thread ####\n");
    //printf("$$$\n");
    //printf("$$\n");
    printf("$\n");
    printf("\n");

    gws_show_backbuffer ();


    while (1)
    {
        printf("$"); fflush(stdout);
		asm ( "pause" );
		asm ( "pause" );
		asm ( "pause" );
		asm ( "pause" );
    };
}



/*
 *************************************************************
 * shellTestThreads:
 *     Cria um thread e executa.
 *     #bugbug ...j� funcionou uma vez, mas agora est� com problemas.
 *     @todo: na hora de criar a thread precisamos passar o PID desse processo.
 */

void ____test_threads (void){

    void *T;	
	
	// Obs: 
	// As threads criadas aqui s�o atribu�das ao processo PID=0.
	// @todo: 
	// No kernel, quando criar uma thread ela deve ser atribu�da
    // ao processo que chamou a rotina de cria��o.	
	
	printf ("____test_threads: Creating threads..\n");
	//apiCreateThread((unsigned long)&shellThread, 0x004FFFF0,"TestShellThread1");
	//apiCreateThread((unsigned long)&shellThread, 0x004FFFF0,"TestShellThread2");
	//apiCreateThread((unsigned long)&shellThread, 0x004FFFF0,"TestShellThread3");
	//apiCreateThread((unsigned long)&shellThread, 0x004FFFF0,"TestShellThread4");
	//...
	
	//
	// # Criar e executar #
	//
	
	// Tentando executar um thread.
	// *******************************
    // OBS: 
	// ISSO J� FUNCIONOU. 
	// ESTAMOS SUSPENDENDO PORQUE PRECISAMOS AUMENTAR O 
	// TAMANHO DO HEAP USADO PELO PROCESSO PARA 
	// ALOCA��O DIN�MICA, ELE N�O T� DANDO CONTA 
    // DE TODA A DEMANDA POR MEM�RIA.		  
	
	//>>Dessa vez pegaremos o retorno, 
	// que deve ser o ponteiro para a estrutura da thread.
	// Obs: N�o podemos usar a estrutura porque ela est� 
	// em ring0.
	//>>Chamaremos a system_call que executa essa thread 
	// que temos o ponteiro da estrutura.
    
	void *ThreadTest1;	
	
	//#bugbug: 
	// N�o temos mais espa�o no heap do preocesso 
	// para alocar mem�ria pois gastamos o heap com 
	// a imagem bmp. (isso aconteceu kkk).

	unsigned long *threadstack1;
	

    //++
    gwssrv_enter_critical_section();
	
	// #importante:
	// Como a torina de thread � bem pequena e o 
	// alocador tem pouqu�ssimo heap, vamos alocar o m�nimo.
	// Isso � apenas um teste, vamos var se a thread funciona 
	// com um a pilha bem pequena. 2KB.
	
	threadstack1 = (unsigned long *) malloc (2*1024);
	
	//Ajuste para o in�cio da pilha.
	//threadstack1 = ( threadstack1 + (2*1024) - 4 ); 
	
	//
	// # Criando a thread #
	//
	
//creating:

    printf ("____test_threads: Tentando executar uma thread..\n");	

    //ThreadTest1  = (void *) gde_create_thread ( (unsigned long) &xxxThread, 
    //                            (unsigned long) (&threadstack1[0] + (2*1024) - 4), 
    //                            "ThreadTest1" );

    ThreadTest1  = (void *) gwssrv_create_thread ( 
                                (unsigned long) &xxxThread, 
                                (unsigned long) (&threadstack1[0] + (2*1024) - 4), 
                                "ThreadTest1" );

    if ( (void *) ThreadTest1 == NULL )
    {
        printf ("____test_threads: apiCreateThread fail \n");
        printf ("____test_threads: ThreadTest1");
        exit(1);
    }

	// # executando #
	
	// #importante:
	// L� no kernel, isso deve selecionar a thread para 
	// execuss�o colocando ela no estado standby.
	// Logo em seguida a rotinad e taskswitch efetua o spawn.

    gwssrv_start_thread (ThreadTest1);
    gwssrv_exit_critical_section ();
    //--


	printf ("____test_threads: Tentando executar um thread [ok]..\n");
	
	//permitir que o shell continue.
}


    
/*
 **************************
 * gwssrv_create_thread:
 *     Create a thread.
 *     #todo: 
 *     Precisamos uma função que envie mais argumentos.
 *     Essa será uma rotina de baixo nível para pthreads.
 */

void *gwssrv_create_thread ( 
    unsigned long init_eip, 
    unsigned long init_stack, 
    char *name )
{
    //#define	SYSTEMCALL_CREATETHREAD     72
    gwssrv_debug_print ("gwssrv_create_thread:\n");
    return (void *) gramado_system_call ( 72, //SYSTEMCALL_CREATETHREAD, 
                        init_eip, 
                        init_stack, 
                        (unsigned long) name );
}


/*
 ****************************************************************
 * gwssrv_start_thread:
 *     Coloca no estado standby para executar pela primeira vez
 */

void gwssrv_start_thread (void *thread)
{

    //#define	SYSTEMCALL_STARTTHREAD  94 
    gramado_system_call ( 94, //SYSTEMCALL_STARTTHREAD, 
        (unsigned long) thread, 
        (unsigned long) thread, 
        (unsigned long) thread );
}


int service_drain_input (void)
{
    gwssrv_debug_print ("gwssrv: service_drain_input [TODO]\n");
    //handle_ipc_message();
    return -1;
}


// #todo
// Sleep if there is no message in the queue.
void gwssrv_wait_message(void)
{
    // #todo
    // block()
    
    // #using this one for now.
    gwssrv_yield();
}


// refresh the whole screen.
// #todo: move to view/
void gws_show_backbuffer(void)
{

    // #debug
    // [Deprecated] Using the kernel service.
    // gwssrv_show_backbuffer();

    // #todo:
    // Create this flag. 
    // if (!paint_ready) return;


    if( (void *) gui->screen_window == NULL )
    {
        debug_print("gws_show_backbuffer: [PANIC] screen window fail\n");
        return;
    }
    
    //See: window.c
    gws_show_window_rect (gui->screen_window);
}


unsigned long gws_get_device_width(void)
{
    return (unsigned long) __device_width;
}


unsigned long gws_get_device_height(void)
{
    return (unsigned long) __device_height;
}


int gwssrv_init_globals(void)
{
    //Loop to clear something
    register int i=0;

    // get gramado mode.
    // jail, p1, home, p2, castle ...
 
    current_mode = gwssrv_get_system_metrics(130);


    // #todo
    // Check valiation and panic if fail.
    
    if (current_mode<0){
        printf("gwssrv_init_globals: [PANIC] current_mode\n");
        exit(1);
    }

    //
    // framebuffer and backbuffer.
    //

    // buffers
    // We need to find a better way to get these addresses,
    // maybe a library. (direct framebuffer library thing)
    // I guess it uses a shared memory allocator.That is why we can
    // use these addresses.
    // #test:
    // We have the rtl included in this project,
    // let's give rtl a chance for now.
    
    // #todo #todo
    // Is this call using the sc82 syscall ? or the sc80 ?
    // We need full access to the kernel structure.

    //____FRONTBUFFER_VA = (unsigned long) gwssrv_get_system_metrics(11);
    //____BACKBUFFER_VA  = (unsigned long) gwssrv_get_system_metrics(12); // #todo: check

    ____FRONTBUFFER_VA = (unsigned long) rtl_get_system_metrics(11);
    ____BACKBUFFER_VA  = (unsigned long) rtl_get_system_metrics(12);


    // Screen
    __device_width  = (unsigned long) gwssrv_get_system_metrics(1);
    __device_height = (unsigned long) gwssrv_get_system_metrics(2);
    __device_bpp    = (unsigned long) gwssrv_get_system_metrics(9);
    
    // Saving
    SavedX   = (unsigned long) __device_width;
    SavedY   = (unsigned long) __device_height;
    SavedBPP = (unsigned long) __device_bpp;
    SavedLFB = (unsigned long) ____FRONTBUFFER_VA;
        
    if ( SavedX == 0 || 
         SavedY == 0 || 
         SavedBPP == 0 || 
         SavedLFB == 0 )
    {
        printf ("gwssrv_init_globals: [FAIL] Screen properties\n");
        exit (1);
    }

    // jail, p1, home, p2, castle ...
    if (current_mode < 0)
    {
        printf ("gwssrv_init_globals: [FAIL] current_mode\n");
        exit (1);
    }


    //
    // == buffers ======================================
    //
    
    // #todo
    // O tamanho dos backbuffers depende da resoluçao da tela.
    // Pois temos 4MB alocados. 
    // Talvez menos, por causa de alguma memoria compartilhada irregular.

    // #bugbug: Null pointers,    
    for (i=0; i<MAX_SCREENS; ++i){ screens[i] = 0; }

    screens[SCREEN_FRONTBUFFER] = (unsigned long) ____FRONTBUFFER_VA;
    screens[SCREEN_BACKBUFFER]  = (unsigned long) ____BACKBUFFER_VA;

    if ( screens[SCREEN_FRONTBUFFER] == 0 || 
         screens[SCREEN_BACKBUFFER] == 0 )
    {
        printf ("gwssrv_init_globals: [FAIL] screens\n");
        exit(1);
    }


    // refresh the device screen ??

    refresh_device_screen_flag = FALSE;


    //background_color = xCOLOR_GRAY3;
   
   
    // Color scheme: Humility
    gwssrv_initialize_color_schemes(ColorSchemeHumility);
    gwssrv_select_color_scheme(ColorSchemeHumility);

    //...

    return 0;
}


/*
 ************************************
 * gwsInit:
 *     Initialize the server. 
 *
 */

int gwsInit(void)
{

    //paint_ready = FALSE;


    // Initializing globals.
    gwssrv_init_globals();

    
    // #todo
    // Configurar as estruturas em ordem:
    // Current display, current screen, current root window.


    //
    // == Display ===============================================
    //

    CurrentDisplay = (void *) malloc (sizeof(struct gws_display_d));
    
    if ( (void*) CurrentDisplay == NULL ){

        // #todo: fail and exit.
        debug_print("gwsInit: [FAIL] CurrentDisplay\n");
        return -1;
        //while(1);
 
    }else{
 
        CurrentDisplay->id = 0; //
        
        CurrentDisplay->used  = TRUE; 
        CurrentDisplay->magic = 1234; 

        // ??
        CurrentDisplay->fd = 0;
        
        //...
    };

    //
    // == Screen ===============================================
    //
    
    DeviceScreen  = (void *) malloc (sizeof(struct gws_screen_d));

    if ( (void*) DeviceScreen == NULL ){

        // #todo: fail and exit.
        debug_print("gwsInit: [FAIL] DeviceScreen\n");
        return -1;
        //while(1);

    }else{

        DeviceScreen->id = 0; 

        DeviceScreen->used  = TRUE;
        DeviceScreen->magic = 1234;
        
        //#todo:
        DeviceScreen->flags = 0;

        // #test
        // Configuramos algumas variaveis globais quando
        // chamamos a rotina de inicializaçao de globais.
        // See: gwssrv_init_globals().
        
        DeviceScreen->width  = SavedX;
        DeviceScreen->height = SavedY;
        DeviceScreen->bpp    = SavedBPP;  // bits per pixel
        
        // #todo
        // Maybe we can check the validation of w h bpp.
        
        DeviceScreen->pitch = ( SavedX * (SavedBPP/8) );

        DeviceScreen->font_size   = 0;    //todo
        DeviceScreen->char_width  = 0;    //todo
        DeviceScreen->char_height = 0;    //todo
        
        // # ??
        // We simply used gwssrv_get_system_metrics() to get these addresses.
        // See: gwssrv_init_globals()
        // We need to find a better way to get these addresses,
        // maybe a library. (direct framebuffer library thing)
        
        DeviceScreen->backbuffer  = (void *) ____BACKBUFFER_VA;
        DeviceScreen->frontbuffer = (void *) ____FRONTBUFFER_VA;
        
        // #todo
        // Maybe we can check the validation of the buffers.
        
        
        //DeviceScreen->hotspot_x = ( DeviceScreen->width  / 2 );
        //DeviceScreen->hotspot_y = ( DeviceScreen->height / 2 );
        DeviceScreen->hotspot_x = ( DeviceScreen->width  >> 1 );
        DeviceScreen->hotspot_y = ( DeviceScreen->height >> 1 );

        
        // Limites para a tela em cruz. '+'
        DeviceScreen->min_x = 0;
        DeviceScreen->min_y = 0;
        //DeviceScreen->max_x = ( DeviceScreen->width  / 2 );
        //DeviceScreen->max_y = ( DeviceScreen->height / 2 );
        DeviceScreen->max_x = ( DeviceScreen->width  >> 1 );
        DeviceScreen->max_y = ( DeviceScreen->height >> 1 );

        //...

        // The device screen will be the valid screen for now.
        // Save the device screen in the diplay structure.

        if ( (void *) CurrentDisplay != NULL )
        {
            CurrentDisplay->device_screen = DeviceScreen;
            CurrentDisplay->valid_screen  = DeviceScreen;
        }
    };

    // font support.
    gwssrv_init_font();

    // char support
    gwssrv_init_char();

    // windows
    // Inicializamos algumas variáves ...
    // as primeira janelas são criadas logo abaixo.
    gwssrv_init_windows();    

    //
    // gui structure.
    //
    
    // First level structure for the GUI.

    gui = (void *) malloc( sizeof( struct gui_d) );

    if ( (void *) gui == NULL )
    {
        debug_print("gwsInit: gui\n");
        printf     ("gwsInit: gui\n");
        exit(1);
        //return -1;
    }


    //
    // Root window.
    //
    
    // See:
    // createw.c

    struct gws_window_d *tmpRootWindow;
    
    tmpRootWindow = (struct gws_window_d *) createwCreateRootWindow();

    if ( (void*) tmpRootWindow == NULL)
    {
        debug_print("gwsInit: [FAIL] Couldn't create root window\n");
        printf     ("gwsInit: [FAIL] Couldn't create root window\n");
        exit(1);
    }


    // #bugbug
    // Its is not a screen. It is only a window.
    // It is the main window of the gui structure.
    // The 'screen' window is the device screen and the
    // main window is the desktop window.

    if ( (void *) gui != NULL )
    {
        // screen
        // Isso foi criado logo acima.

        gui->_screen = DeviceScreen;

        // display
        // Isso foi criado logo acima.

        gui->_display = CurrentDisplay;

        // Screen window and main window.
        gui->screen_window = tmpRootWindow;
        gui->main_window   = tmpRootWindow;
    } 



    //
    // Refresh
    //
    
    // #todo
    // Configurar a estrutura de cliente.
    // Inicializar a lista de clientes.
    
    // #kgws.
    // Isso usa o kernel.
    // #todo: Acho que nessa hora ja temos uma rotina própria válida.

    //paint_ready = TRUE;
    
    gwssrv_show_backbuffer();
    
    return 0;
}


// invalidate the frame.
void invalidate(void)
{
    dirty = TRUE;
}

// validate the frame.
void validate(void)
{
    dirty = FALSE;
}

//
int isdirty(void)
{
    return (int) dirty;
}

// invalidate all the background.
void invalidate_background(void)
{
    // #bugbug: Use background_dirty ??
    background = TRUE;
}

void validate_background(void)
{
    background = FALSE;
}

int is_background_dirty(void)
{
    return (int) background;
}



void gwssrv_set_keyboard_focus(int window)
{
    if(window<0)
        return;

    set_window_with_focus(window);
}


// Refresh the device screen
// #todo: move to view/
void refresh_screen(void)
{
    refresh_device_screen();
}

// Refresh the device screen
// #todo: move to view/
void refresh_device_screen(void)
{
    gws_show_backbuffer();
}


// Refresh the valid screen
// #todo: move to view/
void refresh_valid_screen(void)
{
    //todo
    //refresh the root window of the valid screen.
    
    if ( (void*) CurrentDisplay == NULL ){
        printf("refresh_valid_screen: [ERROR] CurrentDisplay\n");
        exit (1);
    }
    
    // The valid screen is the device screen.
    if ( CurrentDisplay->valid_screen == CurrentDisplay->device_screen )
    {
        gws_show_backbuffer();
        return;
    }
    
    // Well the valid screen is not the device screen.
    
    // The window server will frequently refresh only the
    // valid screen ... it will be only a part of the
    // device screen in a higher resolution.
    // It depends on the fps rate ...
    // If the fps is very high so we can use the device screen as
    // a fixed valid screen.
    
    // #todo
    // This kind of window is NOT well define yet.
    // We nned to use this pointer.
    // refresh >> CurrentDisplay->valid_screen
    // gws_show_window_rect( CurrentDisplay->valid_screen->root );
    // ...
}



// Função padrão para todos os servidores ???
// #todo: temos que criar isso.

int serverInit (void)
{
    printf ("serverInit: Initializing gws server ...\n");

    return (int) gwsInit();
}





