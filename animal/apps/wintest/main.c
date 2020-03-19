// main.c 
// reboot2.
// We click on a button to reboot the system.



#include "wintest.h"



//#define TEDITOR_VERBOSE 1

#define GRID_HORIZONTAL 1000
#define GRID_VERTICAL 2000

//static int running = 1;
int running = 1;


	//
	// ## Janelas de teste ##
	//

	//struct window_d *mainWindow;
    struct window_d *gWindow;          //grid 
    struct window_d *mWindow;          //menu
    struct window_d *reboot_button;    //reboot button;
    struct window_d *button1;          //button1;
    struct window_d *button2;          //button2;
 
//static char *dest_argv[] = { "-sujo0","-sujo1","-sujo2",NULL };
//static unsigned char *dest_envp[] = { "-sujo", NULL };
//static unsigned char dest_msg[512];

 

int 
reboot2Procedure ( struct window_d *window, 
                   int msg, 
                   unsigned long long1, 
                   unsigned long long2 );
 


/*
 * *********************************
 * reboot2Procedure:
 *     Procedimento de janela.
 */
 
int 
reboot2Procedure ( struct window_d *window, 
                   int msg, 
                   unsigned long long1, 
                   unsigned long long2 )
{
	switch (msg)
	{
		case MSG_CREATE:
		    //printf ("MSG_PAINT:\n");
		    
	    //++
        enterCriticalSection (); 
        button2 = (void *) APICreateWindow ( WT_BUTTON, 1, 1, " REBOOT ",  
                                (50), (50), 
                                (100), (100),   
                                NULL, 0, xCOLOR_GRAY3, xCOLOR_GRAY3 );

        if ( (void *) button2 == NULL )
        {
            printf ("Couldn't create button\n");
            return 1;
        }else{

           APIRegisterWindow (button2);
           apiShowWindow (button2);
           refresh_screen ();
        };
        exitCriticalSection (); 
	    //--		    
		    
		    break;

		case MSG_SYSKEYDOWN:
		    switch (long1)
			{  
				case VK_F1:
						
					break;
					
				case VK_F2:
					break;
					
				case VK_F3:
					break;
					
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
				    //#test
				    //printf ("x=%d y=%d \n",apiGetCursorX (), apiGetCursorY ());
				    //refresh_screen();
				    if ( window == button2 )
				    {
						apiReboot();
					}
					
				    if ( window == button1 )
				    {
						//ok
						//apiSendMessageToProcess ( getpid(), NULL, MSG_CREATE, 0, 0 );
						
						//#TODO: TESTAR
						//apiSendMessageToProcess ( getpid(), NULL, MSG_PAINT, 0, 0 );


						//ok
						//gde_set_focus (button1);
						//apiShowWindow (button1);
						//refresh_screen();
						
						//ok. a margem falhou.
						//apiSetCursor (50,50);
						
						//apiReboot();
						
						//ok
						//APIresize_window (button1, 10, 10);
						//APIredraw_window (button1, 1);
						//apiShowWindow (button1);
						//refresh_screen();


						//APIreplace_window (button1, apiGetCursorX (), apiGetCursorY ());
						//APIredraw_window (button1, 1);
						//apiShowWindow (button1);
						//refresh_screen();

						
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
					
					//para uma janela default.
                    gde_set_focus (window);

					break;
			};
			break;
		
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

    unsigned long left = 600;
    unsigned long top = 100;
    unsigned long width = 280;
    unsigned long height = 320;


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

	//++
    apiBeginPaint (); 
    hWindow = (void *) APICreateWindow ( WT_OVERLAPPED, 1, 1, 
                           "Wintest",
                           left, top, width, height,    
                           0, 0, 0xF5DEB3, 0x2d89ef );  

    if ( (void *) hWindow == NULL )
    {
        printf ("Wintest: hWindow fail");
        apiEndPaint ();
        goto fail;
    }else{

        APIRegisterWindow (hWindow);
        APISetActiveWindow (hWindow);
        APISetFocus (hWindow);
        apiShowWindow (hWindow);
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
    button1 = (void *) APICreateWindow ( WT_BUTTON, 1, 1, " Click ",  
                                (width/3), ((height/4)*2), 
                                (width/3), (height/8),   
                                hWindow, 0, xCOLOR_GRAY3, xCOLOR_GRAY3 );

    if ( (void *) button1 == NULL )
    {
        printf ("Couldn't create button\n");
        return 1;
    }else{

        APIRegisterWindow (button1);
        apiShowWindow (button1);
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
		enterCriticalSection(); 
		system_call ( 111,
		    (unsigned long) &message_buffer[0],
			(unsigned long) &message_buffer[0],
			(unsigned long) &message_buffer[0] );
		exitCriticalSection(); 

		if ( message_buffer[1] != 0 )
		{
	        reboot2Procedure ( (struct window_d *) message_buffer[0], 
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

