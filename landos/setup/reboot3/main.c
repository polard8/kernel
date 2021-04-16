// main.c 
// reboot2.
// We click on a button to reboot the system.



#include "reboot3.h"


#define GRID_HORIZONTAL    1000
#define GRID_VERTICAL      2000


int running = 1;


	//
	// ## Janelas de teste ##
	//
	
	// #todo
	// A intenção é colocarmos isso dentro do procedimento de janelas
	// para acessarmos quando necessário.
	// Para isso, é necessário enviarmos uma mensagem WM_CREATE no momento
	// em que a janela principal foi criada. (Ou logo após.#test)
	
    struct window_d *main_window;

    struct window_d *gWindow;          //grid 
    struct window_d *mWindow;          //menu
    struct window_d *reboot_button;    //reboot button;

    struct window_d *__icon1;
    struct window_d *__icon2;
    struct window_d *__icon3;
    struct window_d *__icon4;

    // criados peplo procediento de janela.
    struct window_d *test_button;
    struct window_d *check_box_window;


//static char *dest_argv[] = { "-sujo0","-sujo1","-sujo2",NULL };
//static unsigned char *dest_envp[] = { "-sujo", NULL };
//static unsigned char dest_msg[512];

 

int 
reboot3Procedure ( 
    struct window_d *window, 
    int msg, 
    unsigned long long1, 
    unsigned long long2 );
 

/*
 * *********************************
 * reboot3Procedure:
 *     Dialog.
 */

int 
reboot3Procedure ( 
    struct window_d *window, 
    int msg, 
    unsigned long long1, 
    unsigned long long2 )
{

    unsigned long left = 300;
    unsigned long top  = 100;
    unsigned long width  = 480;
    unsigned long height = 480;



    // Virtual Console and tty.
    int __current_virtual_console = -1;
    int ____tty_id = -1;
    int ____this_tty_id = -1;
    char __wbuf2[128]; //line ?  write
    char __rbuf2[128]; //line ? read 
    int __w_size2 = 0;


    switch (msg)
    {

        case MSG_SYSKEYDOWN:
            switch (long1)
            {

				case VK_F1:
						printf ("disabling ps2 mouse\n");
	                    system_call ( 9800,   //serviço. seleciona o diálogo 
	                        (unsigned long) 4001, // (desabilita) mensagem par ao diálogo
		                    (unsigned long) 0, 
		                    (unsigned long) 0 );
					break;


                case VK_F2:
 						debug_print ("reboot2: Enabling ps2 mouse\n");
	                    system_call ( 9800,   //serviço. seleciona o diálogo 
	                        (unsigned long) 4000, // (habilita) mensagem par ao diálogo
		                    (unsigned long) 0, 
		                    (unsigned long) 0 );
					break;


                // Update button and return.
                case VK_F3:
                    debug_print ("reboot2: [F3] Rebooting ...");
                    // button down
                    gramado_system_call ( 9900,   
                        (unsigned long) reboot_button, 
                        (unsigned long) reboot_button, 
                        (unsigned long) reboot_button );

                    // button up
                    gramado_system_call ( 9901,   
                        (unsigned long) reboot_button, 
                        (unsigned long) reboot_button, 
                        (unsigned long) reboot_button );

                    gde_reboot();
                    debug_print ("reboot2: Unexpected return");
                    goto done;
                    break;
            };
            goto done;
            break;


        case MSG_SYSKEYUP:
            goto done;
            break;


        //vamos criar um botão.
        case MSG_CREATE:
            return 0;
           // VAMOS TESTAR A CONCEXÃO COM O PROCESSO PAI.
           // que será o noraterm.

           // link by pid
           // #todo: Create the function link_by_pid()
           //gramado_system_call ( 267,
           //    getpid(),    //master
           //    getppid(),   //slave pai(terminal)
           //    0 );
        
           //____this_tty_id = gramado_system_call ( 266, getpid(), 0, 0 );        

           //write ( ____this_tty_id, __wbuf2, __w_size2 = sprintf (__wbuf2,"writting from reboot2 ...\n") );    

           /*
            //++
            gde_enter_critical_section (); 
            test_button = (void *) gde_create_window ( WT_BUTTON, 1, 1, 
                                       "MSG_CREATE",  
                                       10, 60, 
                                       (width/3), (height/8),   
                                        main_window, 0, 
                                        xCOLOR_GRAY3, xCOLOR_GRAY3 );

            if ( (void *) test_button == NULL )
            {
                printf ("Couldn't create test_button\n");
                gde_exit_critical_section ();
                return 1;
            }else{

                gde_register_window (test_button);
                gde_show_window  (test_button);
                //gde_show_backbuffer ();
            };
            gde_exit_critical_section (); 
	        //--
	        
            //++
            gde_enter_critical_section (); 
            check_box_window = (void *) gde_create_window ( WT_CHECKBOX, 1, 1, 
                                           "MSG_CREATE",  
                                           40, 150, 
                                           20, 20,   
                                           main_window, 0, COLOR_WHITE, COLOR_WHITE );

            if ( (void *) check_box_window == NULL )
            {
                printf ("Couldn't create test_button\n");
                gde_exit_critical_section ();
                return 1;
            }else{

                gde_register_window (check_box_window);
                gde_show_window  (check_box_window);
                //gde_show_backbuffer ();
            };
            gde_exit_critical_section (); 
	        //--
	        */
	        goto done;
            break;


        // #bugbug
        // Essa mensagem foi enviada quando chamamos um redraw
        // da janela. Então esse redraw chamaria MSG_PAINT recursivamente.
        // à não ser que faça isso somente para janelas de aplicaitivo. Overlapped.
        case MSG_PAINT:
            if ( window == main_window )
            {
                gde_redraw_window (window,1);
                gde_redraw_window (reboot_button, 1);
                gde_redraw_window (test_button, 1);
                gde_redraw_window (__icon1, 1);
                gde_redraw_window (check_box_window, 1);
            }
            goto done;
            break;




		// MSG_MOUSEKEYDOWN
		case 30:
		    switch (long1)
			{
				//botão 1.
				case 1:
				    if ( window == reboot_button )
				    {
                        // button_down
                        // Quando um botão é clicado ou pressionado,
                        // ele será repintado com a aparência de botão apertado.
                        gramado_system_call ( 9900,   
                            (unsigned long) window, 
                            (unsigned long) window, 
                            (unsigned long) window );

                        //OK. Isso funcionou.
						//printf ("disabling ps2 mouse\n");
	                    //system_call ( 9800,   //serviço. seleciona o diálogo 
	                        //(unsigned long) 4001, // (desabilita) mensagem par ao diálogo
		                    //(unsigned long) 0, 
		                    //(unsigned long) 0 );
		                    
						break;
					}

				    if ( window == gWindow )
					{
						printf("grid window\n");
						break;
					}
				    if ( window == mWindow )
					{
						printf("menu window\n");
						break;
					}
				    if ( window == test_button )
					{
						printf ("Test button pressed\n");
	                    //system_call ( 9800,   //serviço. seleciona o diálogo 
	                        //(unsigned long) 4001, // (desabilita) mensagem par ao diálogo
		                    //(unsigned long) 0, 
		                    //(unsigned long) 0 );
		               break;
					}
					if (window == main_window)
					{
						//gde_set_focus(window);
						//raise window.
	                     //system_call ( 9700, 
	                         //(unsigned long) window, 
		                     //(unsigned long) window, 
		                     //(unsigned long) window );
						 
						//MessageBox(3,"x","main");
						//printf("Main\n");
						break;
					}

					break;
			};
			goto done;
			break;


        // MSG_MOUSEKEYUP
		case 31:
		    switch(long1)
		    {

                case 1:
                    if (window == main_window)
                    {
                        // Apenas seta o foco.
                        gde_set_focus (window);
                        
                        //bugbug
                        // Repinta e manda uma mensagem MSG_PAINT
                        // par ao aplicativo.
                        // gde_redraw_window (window,1);
                        
                        // update window
                        // atualiza a área de cliente.
                        // manda uma mensagem MSG_PAINT
                        //gramado_system_call (279, (unsigned long) window, 0, 0 );
                        gde_update_window ( (struct window_d *) window );
                        break;
                    }
 
 
				    if ( window == reboot_button )
				    {
                        gramado_system_call ( 9901,   
                            (unsigned long) window, 
                            (unsigned long) window, 
                            (unsigned long) window );
						gde_reboot ();
						
						//gde_replace_window (main_window, 70, 70);
						//gde_resize_window (main_window, 200,200);
						//gde_set_focus (main_window);
						//gde_redraw_window (main_window,1);
					}
				    break;
			};
			goto done;
			break;



        // #bugbug
        // A função set focus ainda não envia essa
        // mensagem porque estava falahndo na máquina real.
        case MSG_SETFOCUS:
            //gde_redraw_window (main_window, 1);
            //gde_redraw_window (reboot_button, 1);
            break;


        case MSG_KILLFOCUS:
            gde_message_box (3, "reboot2","MSG_KILLFOCUS");
            break;


		case MSG_MOUSEMOVE:
		    if (window == main_window)
		    {
				//printf ("m");
			}
		    break;


		case MSG_MOUSEOVER:
		    if (window == main_window)
		    {
				//printf ("o");
			}
		    break;
		    
		case MSG_MOUSEEXITED:
		    if (window == main_window)
		    {
				//printf ("e");
			}
		    break;
		    
		//carrega    
		case MSG_MOUSE_DRAG:
		    if (window == main_window)
		    { 
				//printf ("D");
				//APIreplace_window (window, apiGetSystemMetrics ( 20 ), apiGetSystemMetrics ( 21 ) );
                //APIredraw_window (window, 1);
                //apiShowWindow (window);
             }
             break;
             
        case MSG_MOUSE_DROP:
			 if (window == main_window)
			 {
				//printf ("Drop");
				//APIreplace_window (window, apiGetSystemMetrics ( 20 ), apiGetSystemMetrics ( 21 ) );
				//raise window.
	           // system_call ( 9700, 
	                //(unsigned long) window, 
		           // (unsigned long) window, 
		            //(unsigned long) window );                
                //APIredraw_window (window, 1);
                //apiShowWindow (window);        
             }
             break;
             
         case MSG_MOUSE_DOUBLECLICKED:
             if ( window == main_window )
             {
				 gde_maximize_window (window);
				 gde_redraw_window (window, 1);
             }
             break;

 
        default:
            debug_print("reboot2: default message");
            break;
	};


done:
    return (int) gde_system_procedure ( window, msg, long1, long2 );
}


/*
 ********************************************
 * main:
 */

int main ( int argc, char *argv[] ){


    struct window_d *hWindow;

    FILE *fp;

    int ch=0;
    int char_count = 0;


    unsigned long left   = 100;
    unsigned long top    = 100;
    unsigned long width  = 400;
    unsigned long height = 400;

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
    gde_begin_paint ();
    hWindow = (void *) gde_create_window ( 
                           WT_OVERLAPPED, 1, 1, 
                           "Reboot2",
                           left, top, width, height, 
                           0, 0, COLOR_WINDOW, COLOR_WINDOW );  

    if ( (void *) hWindow == NULL ){
        printf ("reboot2: hWindow fail");
        gde_end_paint ();
        goto fail;
    }else{
		//Registrar e mostrar.
        gde_register_window (hWindow);
        gde_show_window (hWindow);
        main_window = ( struct window_d *) hWindow;
    };
    gde_end_paint ();
    //--



    //#todo: Usar outro método para enviar a mensagem.
    //reboot3Procedure ( (struct window_d *) hWindow, 
     //   (int) MSG_CREATE, 
     //   (unsigned long) 0, 
     //   (unsigned long) 0 );


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



    //
    // #test
    //
    
    // Testando a criação de uma janela do tipo ícone.
    // #obs: Esse apps não precisa desse tipo de janela. Foi somente
    // usado para teste.

    // #todo
    // We need a way to select the icon's bmp label.

	//++
    gde_enter_critical_section (); 
    __icon1 = (void *) gde_create_window ( 
                           WT_ICON, 1, 1, " Icon1 ",  
                           (10), (10), (64), (64),   
                           hWindow, 0, xCOLOR_GRAY3, xCOLOR_GRAY3 );
    if ( (void *) __icon1 == NULL ){
        printf ("Couldn't create icon\n");
        gde_exit_critical_section ();
        return 1;
    }else{
        gde_register_window (__icon1);
        gde_show_window (__icon1);
        //gde_show_backbuffer ();  //deletar
    };
    gde_exit_critical_section (); 
	//--

	//++
    gde_enter_critical_section (); 
    reboot_button = (void *) gde_create_window ( 
                                 WT_BUTTON, 1, 1, 
                                 " Reboot [F1] ",  
                                 (80), (10), (200), (64),   
                                 hWindow, 0, 
                                 xCOLOR_GRAY3, xCOLOR_GRAY3 );

    if ( (void *) reboot_button == NULL ){
        printf ("Couldn't create button\n");
        gde_exit_critical_section ();
        return 1;
    }else{
        gde_register_window (reboot_button);
        gde_show_window (reboot_button);
        //gde_show_backbuffer (); //deletar
    };
    gde_exit_critical_section (); 
	//--




	//++
    gde_enter_critical_section (); 
    __icon2 = (void *) gde_create_window ( 
                           WT_ICON, 1, 1, " Icon2 ",  
                           (10), (100), (64), (64),   
                           hWindow, 0, xCOLOR_GRAY3, xCOLOR_GRAY3 );
    if ( (void *) __icon2 == NULL ){
        printf ("Couldn't create icon\n");
        gde_exit_critical_section ();
        return 1;
    }else{
        gde_register_window (__icon2);
        gde_show_window (__icon2);
        //gde_show_backbuffer ();  //deletar
    };
    gde_exit_critical_section (); 
	//--

	//++
    gde_enter_critical_section (); 
    reboot_button = (void *) gde_create_window ( 
                                 WT_BUTTON, 1, 1, 
                                 " Reboot [F2] ",  
                                 (80), (100), (200), (64),   
                                 hWindow, 0, 
                                 xCOLOR_GRAY3, xCOLOR_GRAY3 );

    if ( (void *) reboot_button == NULL ){
        printf ("Couldn't create button\n");
        gde_exit_critical_section ();
        return 1;
    }else{
        gde_register_window (reboot_button);
        gde_show_window (reboot_button);
        //gde_show_backbuffer (); //deletar
    };
    gde_exit_critical_section (); 
	//--





	//++
    gde_enter_critical_section (); 
    __icon3 = (void *) gde_create_window ( 
                           WT_ICON, 1, 1, " Icon3 ",  
                           (10), (200), (64), (64),   
                           hWindow, 0, xCOLOR_GRAY3, xCOLOR_GRAY3 );
    if ( (void *) __icon3 == NULL ){
        printf ("Couldn't create icon\n");
        gde_exit_critical_section ();
        return 1;
    }else{
        gde_register_window (__icon3);
        gde_show_window (__icon3);
        //gde_show_backbuffer ();  //deletar
    };
    gde_exit_critical_section (); 
	//--

	//++
    gde_enter_critical_section (); 
    reboot_button = (void *) gde_create_window ( 
                                 WT_BUTTON, 1, 1, 
                                 " Reboot [F3] ",  
                                 (80), (200), (200), (64),   
                                 hWindow, 0, 
                                 xCOLOR_GRAY3, xCOLOR_GRAY3 );

    if ( (void *) reboot_button == NULL ){
        printf ("Couldn't create button\n");
        gde_exit_critical_section ();
        return 1;
    }else{
        gde_register_window (reboot_button);
        gde_show_window (reboot_button);
        //gde_show_backbuffer (); //deletar
    };
    gde_exit_critical_section (); 
	//--




	//++
    gde_enter_critical_section (); 
    __icon4 = (void *) gde_create_window ( 
                           WT_ICON, 1, 1, " Icon4 ",  
                           (10), (300), (64), (64),   
                           hWindow, 0, xCOLOR_GRAY3, xCOLOR_GRAY3 );
    if ( (void *) __icon4 == NULL ){
        printf ("Couldn't create icon\n");
        gde_exit_critical_section ();
        return 1;
    }else{
        gde_register_window (__icon4);
        gde_show_window (__icon4);
        //gde_show_backbuffer ();  //deletar
    };
    gde_exit_critical_section (); 
	//--

	//++
    gde_enter_critical_section (); 
    reboot_button = (void *) gde_create_window ( 
                                 WT_BUTTON, 1, 1, 
                                 " Reboot [F4] ",  
                                 (80), (300), (200), (64),   
                                 hWindow, 0, 
                                 xCOLOR_GRAY3, xCOLOR_GRAY3 );

    if ( (void *) reboot_button == NULL ){
        printf ("Couldn't create button\n");
        gde_exit_critical_section ();
        return 1;
    }else{
        gde_register_window (reboot_button);
        gde_show_window (reboot_button);
        //gde_show_backbuffer (); //deletar
    };
    gde_exit_critical_section (); 
	//--




    //
    // show
    //

    gde_set_focus(main_window);
     
    // #debug
    // gde_show_backbuffer ();
    //while (1){}


	//
	// == Loop =================================
	//

    unsigned long message_buffer[5];

Mainloop:


    while (running)
    {

        gde_enter_critical_section ();
        system_call ( 
            111,
            (unsigned long) &message_buffer[0],
            (unsigned long) &message_buffer[0],
            (unsigned long) &message_buffer[0] );
        gde_exit_critical_section ();


        //if ( message_buffer[1] != 0 )
            //gdeyield();


        if ( message_buffer[1] != 0 )
        {
            reboot3Procedure ( 
                (struct window_d *) message_buffer[0], 
                (int)               message_buffer[1], 
                (unsigned long)     message_buffer[2], 
                (unsigned long)     message_buffer[3] );

            message_buffer[0] = 0;
            message_buffer[1] = 0;
            message_buffer[2] = 0;
            message_buffer[3] = 0;
        }
    };


fail:
    printf ("fail.\n");

done:
    //running = 0;
    return 0;
}



/*
 * topbarInitializeTopBar:
 *
 */
 
// #obs:
// Ainda refletindo de esse apps deve ou não criar uma topbar.
// A Topbar pode ficar no window manager.
 
void topbarInitializeTopBar (void){

    int i=0;
    unsigned long OldX, OldY;

    //salva cursor antigo.
    OldX = gde_get_cursor_x ();
    OldY = gde_get_cursor_y ();
	
	//posiciona.#teste
	gde_set_cursor( 0, 0 );
	
	for( i=0; i < ((800/8)-1); i++)
	{
		printf(" ");
	};


	gde_set_cursor( 8, 0 );	
	printf("|TEDITOR");

	gde_set_cursor( 44, 0 );	
	printf("|Application for testing system resources");
	
    gde_set_cursor (OldX,OldY);
}




/*
 * statusInitializeStatusBar:
 *
 */
 
void statusInitializeStatusBar (void){

	int i=0;
	unsigned long OldX, OldY;

	//salva cursor antigo.
	OldX = gde_get_cursor_x ();
    OldY = gde_get_cursor_y ();
	
	//posiciona.#teste
	gde_set_cursor ( 0, (600/8) -1 );
	
	for( i=0; i < ((800/8)-1); i++)
	{
		printf (" ");
	};
	
	gde_set_cursor( 8, (600/8) -1 );	
	printf("|# Status Bar offset 8.");

	gde_set_cursor( 44, (600/8) -1 );	
	printf("|# Status Bar  offset 44.");
	
//done:
    gde_set_cursor (OldX,OldY);
    //return;	
}


void update_statuts_bar ( char *string1, char *string2 ){
	
	int i=0;
	unsigned long OldX, OldY;

	//salva cursor antigo.
	OldX = gde_get_cursor_x ();
    OldY = gde_get_cursor_y ();
	
	//posiciona.#teste
	gde_set_cursor( 0, (600/8) -1 );
	
	for( i=0; i < ((800/8)-1); i++)
	{
		printf(" ");
	};
	
	gde_set_cursor( 8, (600/8) -1 );	
	printf(string1);

	gde_set_cursor( 44, (600/8) -1 );	
	printf(string2);
	
//done:

    gde_set_cursor (OldX,OldY);	
}




