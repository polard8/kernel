// main.c 
// Garden Paint


#include "sysmon.h"


//#define TEDITOR_VERBOSE 1


#define GRID_HORIZONTAL 1000
#define GRID_VERTICAL 2000


unsigned long __mousex;
unsigned long __mousey;

//static int running = 1;
int running = 1;


	//
	// ## Janelas de teste ##
	//
	
    struct window_d *main_window;
    struct window_d *client_window;

    struct window_d *gWindow;          // grid 
    struct window_d *mWindow;          // menu
    struct window_d *reboot_button;    // reboot button;
    
    
    // launcher buttons
    struct window_d *launcher_button_1;
    struct window_d *launcher_button_2;

    // bar buttons
    struct window_d *bar_button_1; 
    struct window_d *bar_button_2;
    struct window_d *bar_button_3;


//static char *dest_argv[] = { "-sujo0","-sujo1","-sujo2",NULL };
//static unsigned char *dest_envp[] = { "-sujo", NULL };
//static unsigned char dest_msg[512];

 

int 
sysmonProcedure ( struct window_d *window, 
                  int msg, 
                  unsigned long long1, 
                  unsigned long long2 );
 


/*
 * *********************************
 * sysmonProcedure:
 *     Procedimento de janela.
 */

int 
sysmonProcedure ( struct window_d *window, 
                  int msg, 
                  unsigned long long1, 
                  unsigned long long2 )
{

    switch (msg)
    {

		case MSG_SYSKEYDOWN:
		    switch (long1)
			{  
				case VK_F1:
					break;
					
				case VK_F2:
					break;
					
				//case VK_F3:
					//break;

				//...
	
                //full screen
                //colocar em full screen somente a área de cliente. 
		        case VK_F11:    
					break;

				//...

			};
			break;


		// MSG_MOUSEKEYDOWN
        case 30:
            switch (long1)
            {
				//botão 1.
				case 1:
				    if ( window == launcher_button_1 )
				    {
                        gramado_system_call ( 9900,   
                            (unsigned long) window, 
                            (unsigned long) window, 
                            (unsigned long) window );
						 break;
					}

				    if ( window == launcher_button_2 )
				    {
                        gramado_system_call ( 9900,   
                            (unsigned long) window, 
                            (unsigned long) window, 
                            (unsigned long) window );
						 break;
					}
					
					if ( window == bar_button_1 )
					{
                        gramado_system_call ( 9900,   
                            (unsigned long) window, 
                            (unsigned long) window, 
                            (unsigned long) window );
						break;
					}
					
					if ( window == bar_button_2 )
					{
                        gramado_system_call ( 9900,   
                            (unsigned long) window, 
                            (unsigned long) window, 
                            (unsigned long) window );
					    break;
					}

					if ( window == bar_button_3 )
					{
                        gramado_system_call ( 9900,   
                            (unsigned long) window, 
                            (unsigned long) window, 
                            (unsigned long) window );
					    break;
					}

				    if ( window == reboot_button )
				    {
						apiReboot ();
						break;
					}
					
					
				    if ( window == gWindow )
					{
						printf("grid window\n");
					}
				    if ( window == mWindow )
					{
						printf("menu window\n");
					}
					
					//se
					if ( window == main_window )
					{
						//raise window.
	                     system_call ( 9700, 
	                         (unsigned long) main_window, 
		                     (unsigned long) main_window, 
		                     (unsigned long) main_window );
					}

					break;
			};
			break;


        // Mouse button up
        case 31:
            switch (long1)
            {
				case 1:
				    if ( window == launcher_button_1 )
				    {
                        gramado_system_call ( 9901,   
                            (unsigned long) window, 
                            (unsigned long) window, 
                            (unsigned long) window );
						execve ( (const char *) "noraterm.bin", 
                           (const char *) 0, (const char *) 0); 
						 break;
					}
				    if ( window == launcher_button_2 )
				    {
                        gramado_system_call ( 9901,   
                            (unsigned long) window, 
                            (unsigned long) window, 
                            (unsigned long) window );
						 execve ( (const char *) "reboot2.bin",
                            (const char *) 0, (const char *) 0);
						 break;
					}
					if ( window == bar_button_1 )
					{
                        gramado_system_call ( 9901,   
                            (unsigned long) window, 
                            (unsigned long) window, 
                            (unsigned long) window );
                        apiDrawText ( client_window, 4, 40 +32, COLOR_BLACK, "info 1 ...");
                        refresh_screen ();
						break;
					}
					
					if ( window == bar_button_2 )
					{
                        gramado_system_call ( 9901,   
                            (unsigned long) window, 
                            (unsigned long) window, 
                            (unsigned long) window );
                        apiDrawText ( client_window, 4,  40 +32 +32, COLOR_BLACK, "info 2 ...");
                        refresh_screen ();
					    break;
					}

					if ( window == bar_button_3 )
					{
                        gramado_system_call ( 9901,   
                            (unsigned long) window, 
                            (unsigned long) window, 
                            (unsigned long) window );
                        apiDrawText ( client_window, 4,  40 +32 +32 +32, COLOR_BLACK, "info 3 ...");
                        refresh_screen ();
					    break;
					}
				    break;
			};
			break;

       //#todo
       /*
       case MSG_MOUSEMOVE:
           if ( window == bar_button_3 )
           {
			   //pegar posição do ponteiro.
			   __mousex = (unsigned long) apiGetSystemMetrics ( 20 );
			   __mousey = (unsigned long) apiGetSystemMetrics ( 21 );
			   
			   //put pixel on backbuffer.
               gramado_system_call ( 6, COLOR_BLACK, __mousex, __mousey );
           
               //TODO: REFRESH rectangle.
           }
           break;
       */


        default:
            break;
    };


    return 0;
}


/*
 ********************************************
 * main:
 */

int main ( int argc, char *argv[] ){

    struct window_d *hWindow;

    FILE *fp;

    int ch;
    int char_count = 0;

    //#bugbug
    //Ele falha se a largura for pouco.

    //unsigned long left = 600;
    //unsigned long top = 100;
    //unsigned long width = 320;
    //unsigned long height = 480;
    
    unsigned long left;
    unsigned long top;
    unsigned long width;
    unsigned long height;
    

    unsigned long deviceWidth = apiGetSystemMetrics (1); 
    unsigned long deviceHeight = apiGetSystemMetrics (2);

    //left = deviceWidth/2;
    left = 10;
    //top = deviceHeight/3;
    top = 10;

    /*
    if (deviceWidth > 600)
    {
        width = 300;
    }else{
        width = deviceWidth;
    }
    */
    
    width = 480;
    height = 480;
    
    //width = deviceWidth/3;
    //height = deviceHeight/3;


//#ifdef TEDITOR_VERBOSE
	//printf("\n");
	//printf("Initializing File explorer:\n");
	//printf("mainTextEditor: # argv={%s} # \n", &argv[0] );
//#endif

	//
	// ## vamos repetir o que dá certo ...
	//

	//vamos passar mais coisas via registrador.

	//ok
	//foi passado ao crt0 via registrador
	//printf("argc={%d}\n", argc ); 
	
	//foi passado ao crt0 via memória compartilhada.
	//printf("argvAddress={%x}\n", &argv[0] ); //endereço.
	
	
	//unsigned char* buf = (unsigned char*) (0x401000 - 0x100) ;
	//printf("argvString={%s}\n" ,  &argv[0] );
	//printf("argvString={%s}\n" , &buf[0] );
	
	//printf("argv={%s}\n", &argv[2] );

	//
	// ## app window ##
	//

	//green crocodile = 0x44541C 
	//orange royal = 0xF9812A
	//window = 0xF5DEB3
	//client window = 0x2d89ef 
	//...

    //++
    apiBeginPaint (); 
    hWindow = (void *) APICreateWindow (  WT_OVERLAPPED, 1, 1, 
                           "System Monitor",
                           left, top, width, height,    
                           0, 0, 0xF5DEB3, 0x2d89ef );  

    if ( (void *) hWindow == NULL )
    {
		printf ("sysmon: hWindow fail\n");
		apiEndPaint ();

		goto fail;
    }else{

		//Registrar e mostrar.
        APIRegisterWindow (hWindow);
	    apiShowWindow (hWindow);
        
        
        //#test
        //global, pra acessar via procedimento de janela.
        main_window = ( struct window_d *) hWindow;
    };
    apiEndPaint ();
    //--


	//printf("Nothing for now! \n");
    //goto done;

	//apiBeginPaint();    
	//topbarInitializeTopBar();
	//statusInitializeStatusBar();
	//update_statuts_bar("# Status bar string 1","# Status bar string 2");
	//apiEndPaint();
	
	//
	//  ## Testing file support. ##
	//
	
	//++
	/*
	void *b = (void *) malloc (1024*30); 	 
    
	if ( (void *) b == NULL )
	{
		printf ("gfe: allocation fail\n");
		
		goto fail;
	}else{
		
        // @todo: 
	    // Usar alguma rotina da API específica para carregar arquivo.
	    // na verdade tem que fazer essas rotinas na API.
	
	    system_call ( SYSTEMCALL_READ_FILE, (unsigned long) "BMP1    BMP", 
		    (unsigned long) b, (unsigned long) b );
		    
		apiDisplayBMP ( (char *) b, 200, 200 ); 
		
		//não sei se é necessário.
		refresh_screen ();
	};
	 */
    //--

	

	
	//
    // ## testes ##
    //
 

	
	//
	// Grid.
	//
	
	/*
	//++
	apiBeginPaint (); 
	gWindow = (void *) APICreateWindow ( WT_SIMPLE, 1, 1, "GRID-WINDOW",
	                       (1024-150), 10, 100, 320,    
                           hWindow, 0, 0x303030, 0x303030 );	  
	if ( (void *) gWindow == NULL )
	{	
		printf ("gfe: gWindow fail");
		apiEndPaint ();

		goto fail;
	}else{
		
        APIRegisterWindow (gWindow);		
		
		// #bugbug
		// problemas na largura dos ítens quando pintamos no modo vertical;
		// ver a rotina no kgws,
		
	    //#obs: Acho que isso cria grid.
	    int s = (int) system_call ( 148, (unsigned long) gWindow, 
	                      4, (unsigned long) GRID_VERTICAL );
	                      //4, (unsigned long) GRID_HORIZONTAL );		
	
        if (s == 1)	
        {
		    printf ("gfe: 148 fail.\n");
	        apiEndPaint ();
	        
	        goto fail;
	    }
	    
	    apiShowWindow (gWindow);
	};
	apiEndPaint ();
	//--
	*/
	
	
	//
	// Menu.
	//
	
	/*
	//++
	apiBeginPaint (); 
	mWindow = (void *) APICreateWindow ( WT_SIMPLE, 1, 1, "MENU-WINDOW",
	                       (1024-350), 400, 320, 200,
	                       hWindow, 0, COLOR_PINK, COLOR_PINK );	    
                           //hWindow, 0, 0x303030, 0x303030 );	  

	if ( (void *) mWindow == NULL )
	{	
		printf ("gfe: mWindow fail");
		apiEndPaint ();
		
		goto fail;
	}else{
		
        APIRegisterWindow (mWindow);		

	    // #obs: Acho que isso cria menu.
	    // Criaremos o menu de acordo com a janela mãe
	    // mas usaremos apenas o posicionamento da janela mãe. left top
	    // ou o ponteiro do mouse, quando clicarmos com o botão direito.
	    
        system_call ( 149, (unsigned long) mWindow, 
            (unsigned long) mWindow, (unsigned long) mWindow );
            
    	apiShowWindow (mWindow);            
	};
	apiEndPaint ();
    //--	
	*/
	
	
	//
	// ## Mostrando bmps dentro da área de cliente ##
	//
	
	// #todo:
	// Ainda em planejamento.
	 	
	//struct window *tmpWindow;
	//struct window *icon1;
	//struct window *icon2;
	//struct window *icon3;
	//struct window *icon4;
	//...
	
	/*
	int i;
	for ( i=0; i<15; i++ )
	{
		// #isso é um teste.
		// Criando janelas para os ícones, mas deveria 
		// criar grid ou menu.
		// #bugbug: Não temos acesso aos elementos da estrutura 
		// da janela, pois estão em ring0.
	    
        apiBeginPaint(); 
	    tmpWindow = (void*) APICreateWindow( WT_SIMPLE, 1, 1,"ICON-WINDOW",
	                    20, 1+20+(i*24), 
						800-40, 24,    
                        0, 0, COLOR_BLUE, COLOR_BLUE );

	    if((void*) tmpWindow == NULL)
	    {	
		    printf("WINDOW-FAIL");
		    apiEndPaint();
		    goto fail;
	    }
        apiEndPaint();		
		
		
		
	    //Usando a API para exibir o bmp carregado. 
	    //ACHO QUE ISSO SOMENTE PINTA NO BACKBUFFER
	    apiDisplayBMP ( (char *) b, 40, 1 + 60 + (i*24) ); 
    };
    */
    
    
    
	 //
	 // Novo menu.
	 //
	 
	 // #obs: Acho que isso cria menu.
	 // Criaremos o menu de acordo com a janela mãe
	 // mas usaremos apenas o posicionamento da janela mãe. left top
	 // ou o ponteiro do mouse, quando clicarmos com o botão direito.
	    
     //system_call ( 149, (unsigned long) hWindow, 
     //    (unsigned long) hWindow, (unsigned long) hWindow );    
	
			
	//
	// ## Refresh Window ##
	//
	
	// #bugbug
	// Talvez não precisemos disso.
	//refresh_screen ();



	//++
    enterCriticalSection (); 
	launcher_button_1 = (void *) APICreateWindow ( WT_BUTTON, 1, 1, "1",  
                                     10, 36 +10, 
                                     40, 40,    
                                     hWindow, 0, xCOLOR_GRAY3, xCOLOR_GRAY3 );

    if ( (void *) launcher_button_1 == NULL )
    {
		printf ("Couldn't create button\n");
		return 1;
    }else{
        APIRegisterWindow (launcher_button_1);
        apiShowWindow (launcher_button_1);
        refresh_screen ();
    };
    exitCriticalSection (); 
	//--



	//++
    enterCriticalSection (); 
	launcher_button_2 = (void *) APICreateWindow ( WT_BUTTON, 1, 1, "2", 
                                     10 +40 +10, 36 +10,
                                     40, 40,   
                                     hWindow, 0, xCOLOR_GRAY3, xCOLOR_GRAY3 );
	
	if ( (void *) launcher_button_2 == NULL )
	{
		printf ("Couldn't create button\n");
		return 1;
	}else{

        APIRegisterWindow (launcher_button_2);
        apiShowWindow (launcher_button_2);
        refresh_screen ();
	};
    exitCriticalSection (); 
	//--




    //
    // ========= Client background =====================
    //

    struct window_d *client_bg_Window;
    
	//++
	enterCriticalSection ();  
	client_bg_Window = (void *) APICreateWindow ( WT_SIMPLE, 1, 1, "client-bg",     
                                4, 80 +10, 
                                width -4 -42, height -36 -40 -20 -20, 
                                hWindow, 0, 0xF5DEB3, 0xF5DEB3 );
	if ( (void *) client_bg_Window == NULL)
	{	
		printf("edit box fail");
		refresh_screen();
		while(1){}
	}
	client_window = ( struct window_d *) client_bg_Window;
	APIRegisterWindow (client_bg_Window);
	apiShowWindow (client_bg_Window);
	exitCriticalSection ();  
	//--


    struct window_d *client_bar_Window;

	//++
	enterCriticalSection ();  
	client_bar_Window = (void *) APICreateWindow ( WT_SIMPLE, 1, 1, "client-bar",     
                                2, 2, 
                                width -4 -40, 40, 
                                client_bg_Window, 0, 0x404040, 0x404040 );
	if ( (void *) client_bar_Window == NULL)
	{	
		printf(".. fail");
		refresh_screen();
		while(1){}
	}
	APIRegisterWindow (client_bar_Window);
	apiShowWindow (client_bar_Window);
	exitCriticalSection ();  
	//--


    //
    // ============ Bar buttons =========
    //
    
	//++
    enterCriticalSection (); 
	bar_button_1 = (void *) APICreateWindow ( WT_BUTTON, 1, 1, "PID",  
                                     1, 1, 
                                     50, 32,    
                                     client_bar_Window, 0, 
                                     xCOLOR_GRAY3, xCOLOR_GRAY3 );

    if ( (void *) bar_button_1 == NULL )
    {
		printf ("Couldn't create PID button\n");
		return 1;
    }else{
        APIRegisterWindow (bar_button_1);
        apiShowWindow (bar_button_1);
        refresh_screen ();
    };
    exitCriticalSection (); 
	//--


    
	//++
    enterCriticalSection (); 
	bar_button_2 = (void *) APICreateWindow ( WT_BUTTON, 1, 1, "State", 
                                     50 +1, 1,
                                     100, 32,   
                                     client_bar_Window, 0, 
                                     xCOLOR_GRAY3, xCOLOR_GRAY3 );
	
	if ( (void *) bar_button_2 == NULL )
	{
		printf ("Couldn't create State button\n");
		return 1;
	}else{

        APIRegisterWindow (bar_button_2);
        apiShowWindow (bar_button_2);
        refresh_screen ();
	};
    exitCriticalSection (); 
	//--


	//++
    enterCriticalSection (); 
	bar_button_3 = (void *) APICreateWindow ( WT_BUTTON, 1, 1, "Priority", 
                                     50 +1 +100 +1, 1,
                                     200, 32,   
                                     client_bar_Window, 0, 
                                     xCOLOR_GRAY3, xCOLOR_GRAY3 );
	
	if ( (void *) bar_button_3 == NULL )
	{
		printf ("Couldn't create Priority button\n");
		return 1;
	}else{

        APIRegisterWindow (bar_button_3);
        apiShowWindow (bar_button_3);
        refresh_screen ();
	};
    exitCriticalSection (); 
	//--



	//
	//  ## Loop ##
	//


    unsigned long message_buffer[5];

Mainloop:

    while (running)
    {
        enterCriticalSection (); 
        system_call ( 111,
		    (unsigned long) &message_buffer[0],
			(unsigned long) &message_buffer[0],
			(unsigned long) &message_buffer[0] );
		exitCriticalSection (); 


        if ( message_buffer[1] != 0 )
        {
            sysmonProcedure ( (struct window_d *) message_buffer[0], 
               (int) message_buffer[1], 
               (unsigned long) message_buffer[2], 
               (unsigned long) message_buffer[3] );

            message_buffer[0] = 0;
            message_buffer[1] = 0;
            message_buffer[3] = 0;
            message_buffer[4] = 0;
        };
    };



fail:
    printf ("fail.\n");


done:
    
	//running = 0;

    return 0;
}




