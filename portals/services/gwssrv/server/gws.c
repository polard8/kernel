/*
 * File: gws.c
 * 
 *     Part of the Gramado Window Server.
 *
 * History:
 *     2019 - Created by Fred Nora.
 *     2020    
 */




//
#include <stddef.h>

//Using some system resources.
//#include <api.h>

// window server routines.
#include <gws.h>


/*
 *******************************************
 * xxxThread:
 *     Um thread dentro para testes.
 */
void xxxThread (void){
	printf("\n");
	printf("$\n");
	printf("$$\n");
	//printf("$$$\n");
    printf("#### This is a thread ####\n");
	//printf("$$$\n");
	printf("$$\n");
	printf("$\n");
    printf("\n");
	
    gws_show_backbuffer ();

    //while(1){}
    while(1)
    {
        printf("$"); fflush(stdout);
		asm ( "pause" );
		asm ( "pause" );
		asm ( "pause" );
		asm ( "pause" );
    }
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

void *
gwssrv_create_thread ( 
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


void gws_show_backbuffer(void)
{

    // #debug
    // [Deprecated] Using the kernel service.
    // gwssrv_show_backbuffer();

    // #todo:
    // Create this flag. 
    // if (!paint_ready) return;


    if( (void *) gui->screen == NULL ){
        debug_print("gws_show_backbuffer: [PANIC] screen window fail\n");
        return;
    }
    gws_show_window_rect(gui->screen);
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
    // buffers
    ____FRONTBUFFER_VA = (unsigned long) gwssrv_get_system_metrics(11);
    ____BACKBUFFER_VA  = (unsigned long) gwssrv_get_system_metrics(12);


    // Screen
    SavedX = gwssrv_get_system_metrics(1);
    SavedY = gwssrv_get_system_metrics(2);
    __device_width  = SavedX;
    __device_height = SavedY;


    // bpp
    SavedBPP = (unsigned long) gwssrv_get_system_metrics(9);


    //background_color = xCOLOR_GRAY3;
   
   
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
//int gwsInit (void){

int gwsInit(void)
{

    //paint_ready = FALSE;


    // Initializing globals.
    gwssrv_init_globals();

    
    // #todo
    // Configurar as estruturas em ordem:
    // Current display, current screen, current root window.


    CurrentDisplay = (void *) malloc (sizeof(struct gws_display_d));
    if( (void*) CurrentDisplay == NULL){
        debug_print("gwsInit: CurrentDisplay\n");
        return -1;
        //while(1);
    }else{
        CurrentDisplay->id = 0; //
        CurrentDisplay->used = 1; //
        CurrentDisplay->magic = 1234; //
        
        CurrentDisplay->fd = 0;
        
        //...
    };
    
    
    CurrentScreen  = (void *) malloc (sizeof(struct gws_screen_d));
    if( (void*) CurrentScreen == NULL){
        debug_print("gwsInit: CurrentScreen\n");
        //while(1);
    }else{
        CurrentScreen->id = 0; 
        CurrentScreen->used = 1; 
        CurrentScreen->magic = 1234; 

        // Serão configurados depois.
        // Por enquanto estamos apenas limpando.
        CurrentScreen->width = 0;
        CurrentScreen->height = 0;
        CurrentScreen->font_size = 0;
        CurrentScreen->char_width  = 0;
        CurrentScreen->char_height = 0;
        CurrentScreen->backbuffer  = NULL;
        CurrentScreen->frontbuffer = NULL;
        //...

    };


    // font support.
    gwssrv_init_font();

    // char support
    gwssrv_init_char();
    

    //windows
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


    if ( (void *) gui != NULL )
    {
        // (root window)
        gui->screen = (struct gws_window_d *) createwCreateWindow ( WT_SIMPLE, 
                                              1, 1, "screen-window",  
                                              0, 0, 
                                              __device_width, __device_height,   
                                              NULL, 0, xCOLOR_GRAY3, xCOLOR_GRAY3 );

        if ( (void*) gui->screen == NULL)
        {
            debug_print("gwsInit: [FAIL] screen window\n");
            printf     ("gwsInit: [FAIL] screen window\n");
            exit(1);
            //return -1;    
        }

        gui->screen->used = 1;
        gui->screen->magic = 1234;
        
        //#test
        gwsDefineInitialRootWindow (gui->screen);
    
        // main window.
        // desktop area without the bars.
        // For maximized apps.
        gui->main = gui->screen;
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




// Função padrão para todos os servidores ???
// #todo: temos que criar isso.
int serverInit (void)
{
    printf ("serverInit: Initializing gws server ...\n");

    return (int) gwsInit();
}





