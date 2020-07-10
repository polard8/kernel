// main.c 
// Arquivo principal do aplicativo teditor.bin
// O aplicativo é usado para testes do sistema operacional 
// Gramado 0.3.
//



#include "gfe.h"


//#define TEDITOR_VERBOSE 1

#define GRID_HORIZONTAL 1000
#define GRID_VERTICAL 2000

//static int running = 1;
int running = 1;


    //
	// ## Janelas ##
	//

    struct window_d *main_window;
    
    struct window_d *gWindow;  //grid 
    struct window_d *mWindow;  //menu

//static char *dest_argv[] = { "-sujo0","-sujo1","-sujo2",NULL };
//static unsigned char *dest_envp[] = { "-sujo", NULL };
//static unsigned char dest_msg[512];

 

int 
gfeProcedure ( struct window_d *window, 
               int msg, 
               unsigned long long1, 
               unsigned long long2 );
 


/*
 * *********************************
 * gfeProcedure:
 *     Procedimento de janela.
 */
 
int 
gfeProcedure ( struct window_d *window, 
               int msg, 
               unsigned long long1, 
               unsigned long long2 )
{

    switch (msg)
    {
		case MSG_CREATE:
		    printf ("MSG_CREATE:\n");
		    break;
		    
		case MSG_SYSKEYDOWN:
		    switch (long1)
			{  
				case VK_F1:
				    printf ("F1\n");
					break;
					
				case VK_F2:
				    printf ("F2\n"); 
					break;
					
				//case VK_F3:
 				    //printf ("F3\n");
					//break;
					
				//...
				
                //full screen
                //colocar em full screen somente a área de cliente. 
		        //case VK_F11:
				    
					//break;
					
				//...

			};
			break;		


		// MSG_MOUSEKEYDOWN	
		case 30:
		    switch (long1)
			{
				//botão 1.
				case 1:
				    if ( window == gWindow )
					{
						//printf ("grid window\n");
					}
				    if ( window == mWindow )
					{
						//printf("menu window\n");
					}

					break;
			};
			break;
		
		//up
		case 31:
		    switch (long1)
			{
				//botão 1.
				case 1:
				    if ( window == main_window )
				    {
						gde_set_focus (window);
					}
				    if ( window == gWindow )
					{
						printf ("grid window\n");
					}
				    if ( window == mWindow )
					{
						printf("menu window\n");
					}
					break;
			};
			break;
		
		case MSG_SETFOCUS:
		    if ( window == main_window )
			{
				gde_redraw_window ( main_window, 1);
				gde_redraw_window ( gWindow, 1);
				gde_redraw_window ( mWindow, 1);
		    }
		    break;
		    
		case MSG_KILLFOCUS:
		    break;


		default:
		    break;
    };


    //return 0;
    return (int) gde_system_procedure (window,msg,long1,long2);
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


#ifdef TEDITOR_VERBOSE
	printf("\n");
	printf("Initializing File explorer:\n");
	//printf("mainTextEditor: # argv={%s} # \n", &argv[0] );
#endif


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
	gde_begin_paint (); 
	hWindow = (void *) gde_create_window ( WT_OVERLAPPED, 1, 1, 
	                       "Gramado File Explorer",
	                       10, 10, 640, 480,    
                           0, 0, COLOR_WHITESMOKE, 0x303030 ); 

	if ( (void *) hWindow == NULL )
	{	
		printf ("gfe: hWindow fail");
		gde_end_paint ();
		goto fail;
    }else{

        gde_register_window (hWindow);
        gde_show_window (hWindow);
        main_window = hWindow;
    };
	gde_end_paint ();
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
	void *b = (void *) malloc (1024*30); 
    
	if ( (void *) b == NULL )
	{
		printf ("gfe: allocation fail\n");
		
		goto fail;
	}else{
		
        // @todo: 
	    // Usar alguma rotina da API específica para carregar arquivo.
	    // na verdade tem que fazer essas rotinas na API.
	
        gramado_system_call ( SYSTEMCALL_READ_FILE, 
	        (unsigned long) "FOLDER  BMP", 
		    (unsigned long) b, 
		    (unsigned long) b );
	};
    //--

	

	
	//
    // ## testes ##
    //
 

	
	//
	// Grid.
	//
	
	//++
	gde_begin_paint (); 
	gWindow = (void *) gde_create_window ( WT_SIMPLE, 1, 1, "GRID-WINDOW",
	                       8, 42, 
	                       100, 320,    
                           hWindow, 0, 0x303030, 0x303030 );
	if ( (void *) gWindow == NULL )
	{	
		printf ("gfe: gWindow fail");
		gde_end_paint ();

		goto fail;
	}else{
		
        gde_register_window (gWindow);
		
		// #bugbug
		// problemas na largura dos ítens quando pintamos no modo vertical;
		// ver a rotina no kgws,

        // #bugbug
        // Nessa chamada não temos o posicionamento do grid.

	    //#obs: Acho que isso cria grid.
	    int s = (int) gramado_system_call ( 148, (unsigned long) gWindow, 
	                      4, (unsigned long) GRID_VERTICAL );
	                      //4, (unsigned long) GRID_HORIZONTAL );
	
        if (s != 0)
        {
		    printf ("gfe: 148 fail.\n");
	        gde_end_paint ();
	        
	        goto fail;
	    }
	    
	    gde_show_window (gWindow);
	};
	gde_end_paint ();
	//--
	
	

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
	
	int i;
	
	for ( i=0; i<15; i++ )
	{
		// #isso é um teste.
		// Criando janelas para os ícones, mas deveria 
		// criar grid ou menu.
		// #bugbug: Não temos acesso aos elementos da estrutura 
		// da janela, pois estão em ring0.
	    /*
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
		*/
		
		
	    //Usando a API para exibir o bmp carregado. 
	    //ACHO QUE ISSO SOMENTE PINTA NO BACKBUFFER
	    gde_display_bmp ( (char *) b, 
	        200, 
	        1 + 60 + (i*24) ); 
    };
    
    
    
	 
	//
	// Menu.
	//


    //==================#todo =======================================
    
    //#todo
    //estamos trabalhando na pintura do menu ...
    //está quase funcionando novamente.
    //é questão de posicionamento.


    
	//++
	gde_begin_paint (); 
    mWindow = (void *) gde_create_window ( WT_SIMPLE, 1, 1, "MENU-WINDOW",
                           280, 50, 
                           320, 200,
                           hWindow, 0, COLOR_PINK, COLOR_PINK );
                           
    if ( (void *) mWindow == NULL )
    {	
		printf ("gfe: mWindow fail");
		gde_end_paint ();
		
		goto fail;
    }else{
		
        gde_register_window (mWindow);            
        gde_show_window (mWindow); 
    };
	gde_end_paint ();
    //--

	 
	 // Isso é uma rotina de teste.
	 // #obs: Acho que isso cria menu.
	 // Criaremos o menu de acordo com a janela mãe
	 // mas usaremos apenas o posicionamento da janela mãe. left top
	 // ou o ponteiro do mouse, quando clicarmos com o botão direito.

     gramado_system_call ( 149, 
         (unsigned long) mWindow, 
         (unsigned long) mWindow, 
         (unsigned long) mWindow );  





	//
	// ## Refresh Window ##
	//
	
	// #bugbug
	// Talvez não precisemos disso.
	gde_show_backbuffer ();
	
	
	//
	//  ## Loop ##
	//
	
	
    unsigned long message_buffer[5];

Mainloop:
	
	while (running)
	{
		gde_enter_critical_section(); 
		gramado_system_call ( 111,
		    (unsigned long)&message_buffer[0],
			(unsigned long)&message_buffer[0],
			(unsigned long)&message_buffer[0] );
		gde_exit_critical_section(); 
			
		if ( message_buffer[1] != 0 )
		{
	        gfeProcedure ( (struct window_d *) message_buffer[0], 
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
    
	running = 0;
   
	// printf("#debug *hang\n");
    // printf("done.\n");
	
	//*hang
	//while (1){ asm ("pause"); };
	
	return 0;
}




