/*
 * File: main.c
 *
 * Arquivo principal do aplicativo teditor.bin 
 * O aplicativo é usado para testes do sistema operacional Gramado 0.4
 *
    ## todo: 
	pegar algumas funções do shell e usar aqui.
	agora eles usam o mesmo esquema de strutura de linhas para o texto.
 
 * 2018 - Created by Fred Nora.
 */


#include "gramcode.h"



#define WINDOW_LEFT     40 
#define WINDOW_TOP      40
#define WINDOW_WIDTH   480  
#define WINDOW_HEIGHT  480



    // main window.
    struct window_d *hWindow;

    // save button.
    struct window_d *save_button;




//static int running = 1;
int running = 1;

//static char *dest_argv[] = { "-sujo0","-sujo1","-sujo2",NULL };
//static unsigned char *dest_envp[] = { "-sujo", NULL };
//static unsigned char dest_msg[512];

void editorClearScreen(); 
int editor_save_file ();

void teditorTeditor ();

void shellInitSystemMetrics();
void shellInitWindowLimits();
void shellInitWindowSizes();
void shellInitWindowPosition();


void teditorInsertNextChar (char c);
void teditorRefreshCurrentChar (); 

void gramcodeLinesInsertChar ( int line_number, int at, int c );


void *teditorProcedure ( struct window_d *window, 
                         int msg, 
                         unsigned long long1, 
                         unsigned long long2 );


int
__SendMessageToProcess ( int pid, 
                          struct window_d *window, 
                          int message,
                          unsigned long long1,
                          unsigned long long2 );





/*
 * Limpar a tela 
 * #todo: poderemos limpara a tela do mesmo modo que o shell faz.    
 */

void editorClearScreen (){
	
	int lin, col;    

	// @todo:
	//system( "cls" ); // calls the cls command.
	
    gde_set_cursor (0,0);

	// Tamanho da tela. 80x25

	// Linhas.
    for ( lin=0; lin < ((600/8)-1); lin++ )
    {
        col = 0;

        gde_set_cursor (col,lin);

        // Colunas.
        for ( col=0; col < ((800/8)-1); col++ )
        {
            printf ("%c",' ');
        };
    };


    gde_set_cursor (0,2);
}



/*
 *====================================
 * editor_save_file:
 * Testando a rotina de salvar um arquivo.
 * Estamos usando a API.
 */

int editor_save_file (){
	

	// #importante:
	// Não podemos chamar a API sem que todos os argumentos estejam corretos.
	
	// #obs:
	// Vamos impor o limite de 4 setores por enquanto. 
	// 512*4 = 2048  (4 setores) 2KB
	// Se a quantidade de bytes for '0'. ???
	
	
	//preparando o arquivo para salvar.
	//precisamos colocar no buffer
	
	//isso é um teste.
	
	
	//strcat( RAW_TEXT, "initializing file ...");
	
	/*
	int l; //linha
	int c; //coluna
	int p = 0; //posição dentro do buffer.
	
	for ( l=0; l<16; l++ )
	{
		for ( c=0; c<80; c++ )
		{
			//pega um char.
			RAW_TEXT[p] = (char) LINES[l].CHARS[c];
			p++;
		}
	};
	*/




    int Ret;

    unsigned long number_of_sectors = 0;
    size_t len = 0;

    char file_1_name[] = "FILE1234TXT";	
    //char file_1[] = "Arquivo \n escrito \n em \n user mode no editor de textos teditor.bin :) \n";

 
	//Initializing ...
    printf ("editor_save_file: Saving ...\n");


	// Lenght in bytes.
	
	//len = (size_t) strlen (file_1);
    len = (size_t) strlen ( RAW_TEXT );


    if (len <= 0){
        printf ("editor_save_file:  Fail. Empty file.\n");
        return (int) 1;
    }


    if (len > 2048){
        printf ("editor_save_file:  Limit Fail. The  file is too long.\n");
        return (int) 1;
    }


    //
    // Number os sectors.
    //


    number_of_sectors = (unsigned long) ( len / 512 );


    if ( len > 0 && len < 512 )
    {
        number_of_sectors = 1; 
    }


    if ( number_of_sectors == 0 ){
        printf ("editor_save_file:  Limit Fail. (0) sectors to save.\n");
        return (int) 1;
    }


    // limite de teste.
    // Se tivermos que salvar mais que 4 setores.

    if ( number_of_sectors > 4 )
    {
        printf ("editor_save_file:  Limit Fail. (%d) sectors to save.\n",
            number_of_sectors );
        return (int) 1;
    }



	//
	// Save
	//


    // name, number of sectors, size in bytes, address, flag.

    Ret = (int) gde_save_file ( file_1_name, 
                    number_of_sectors, len,            
                    &RAW_TEXT[0], 
                    0x20 );    

    printf ("done\n");

    return (int) Ret;
}


/*
 **************************************
 *  teditorProcedure:
 *      Procedimento de janela.
 */
 
void *teditorProcedure ( struct window_d *window, 
                         int msg, 
                         unsigned long long1, 
                         unsigned long long2 )
{
    unsigned long input_ret;
    unsigned long compare_return;
    int q;

    int key_state = -1;


    switch (msg)
    {

        case MSG_CREATE:
            saveCreateButton ();
            break;


		//Faz algumas inicializações de posicionamento e dimensões.
        //case MSG_INITDIALOG:
        //    break;

		//Torna a janela visível.
        //case MSG_SHOWWINDOW:
		//    break; 
		 
		case MSG_KEYDOWN:
            switch (long1)
            {
				// Null key.
				case 0:
				break;
				
				case VK_RETURN:
				    
					//#test
					printf("\r");
					printf("\n"); //FLUSH
					
                    break; 

				//#test
                case VK_TAB:
					printf ("\t");
				    break;

				//#todo	
				case VK_BACK:
				    
					//#test
					//o cursor do ldisc no kernel precisa ser atualizado tambem.
					//textCurrentCol--;
					//gde_set_cursor (textCurrentCol,textCurrentRow);
					//teditorInsertNextChar ( (char) ' ' ); 	
					
					//MessageBox ( 3, "String1","String2" );
					
                    break;					
				
				// #importante:
				// Teclas de digitação.
				
				default:
				    // Improvisando um salvamento de arquivo.
				    if ( long1 == 's' )
					{
					    //#todo
						//pegar o status de control.
						//#todo: isso precisa ir para a API.(138)
						key_state = (int) gramado_system_call ( 138, 
						                      (unsigned long) VK_CONTROL, 
						                      (unsigned long) VK_CONTROL, 
						                      (unsigned long) VK_CONTROL );
					    // pressionada
						if ( key_state == 1 )
					    {
						    editor_save_file ();
							key_state = -1;
							break;
						}
					}
					//Colocando no buffer e exibindo na tela.
				    teditorInsertNextChar ( (char) long1 );  
				    break;
			};
			break;
			
		case MSG_SYSKEYDOWN:
		    switch (long1)
			{
				//#bugbug
				//vamos testar usando as teclas de função.
				//mas no futuro usaremos as setas.
				//o problema é que o procedimento do sistema também usa isso

				//#teste: Isso é um improviso.
				//Criando o botão para salvar o arquivo.
				case VK_F1:
				   saveCreateButton ();
				   break;
				
				
				case VK_F2:
				   break;

			
				case VK_F3:
				   break;

				case VK_F4:
				   break;

			};
			break;



		// MSG_MOUSEKEYDOWN
		case 30:
			//qual botão?
			switch (long1)
			{
				case 1:
					if ( window == save_button )
					{
                        gramado_system_call ( 9900,   
                            (unsigned long) window, 
                            (unsigned long) window, 
                            (unsigned long) window );
					}
					break;
					
				case 2:
					break;
					
				case 3:
					break;
			}
			break;

        // mouse key up
		case 31:
			//qual botão?
			switch (long1)
			{
				case 1:
					if ( window == save_button )
					{
                        gramado_system_call ( 9901,   
                            (unsigned long) window, 
                            (unsigned long) window, 
                            (unsigned long) window );
						 editor_save_file ();
					}
					break;
					
				case 2:
					break;
					
				case 3:
					break;
			}
			break;



		default:
		    break;
	};

	
    // done

    // Esse tratamento pode ir para essa chamada na api.
    if ( (void *) window == NULL )
    {
		return NULL;
    }


	// #test
	// Cuidado com isso. 
	// Podemos chamar duas rotinas quando pressionarmos alguma tecla. 
	// Por exemplo F1 chamaria uma rotina aqui e outra no kernel.

    return (void *) gde_system_procedure ( window, msg, long1, long2 );
}


/*
 *****************************************
 * teditorTeditor:
 *     Contrutor e inicialização.
 */
 
void teditorTeditor (){

    int i=0;
    int j=0;


	//
	// ## Inicializando as estruturas de linha ##
	//
	
	//inicializamos com espaços.
	for ( i=0; i<32; i++ )
	{
		for ( j=0; j<80; j++ )
		{
		    LINES[i].CHARS[j] = (char) ' ';
		    LINES[i].ATTRIBUTES[j] = (char) 7;
	    }
		
		LINES[i].left = 0;
		LINES[i].right = 0;
		LINES[i].pos = 0;
	};	
	


	//inicializa as metricas do sistema.
	//inicializa os limites da janela.
	//inicia o tamanho da janela.
	//inicializar a posição da janela.
	
    // #todo
    // Mudar o nome dessas funções.
    
    shellInitSystemMetrics ();
    shellInitWindowLimits ();
    shellInitWindowSizes ();
    shellInitWindowPosition ();
}


void shellInitSystemMetrics (){
	
	//pegaremos todas as metricas de uma vez só,
	//se uma falhar, então pegaremos tudo novamente.
	
	// Tamanho da tela.	
	smScreenWidth =  gde_get_system_metrics(1);
    smScreenHeight = gde_get_system_metrics(2); 
	
	smCursorWidth =  gde_get_system_metrics(3);
	smCursorHeight = gde_get_system_metrics(4);
	
	smMousePointerWidth =  gde_get_system_metrics(5);
	smMousePointerHeight = gde_get_system_metrics(6);
	
	smCharWidth =  gde_get_system_metrics(7);
	smCharHeight = gde_get_system_metrics(8);	
	//...
}


void shellInitWindowLimits (){
	
    //
    // ## Window limits ##
    //

    //full screen support
    wlFullScreenLeft = 0;
    wlFullScreenTop = 0;
    wlFullScreenWidth = smScreenWidth;
    wlFullScreenHeight = smScreenHeight;



    //limite de tamanho da janela.
    wlMinWindowWidth = smCharWidth * 10;
    wlMinWindowHeight = smCharWidth * 10;
    //wlMinWindowWidth = smCharWidth * 80;
    //wlMinWindowHeight = smCharWidth * 25;
    wlMaxWindowWidth = wlFullScreenWidth;
    wlMaxWindowHeight = wlFullScreenHeight;


    //quantidade de linhas e colunas na área de cliente.
    wlMinColumns = 80;
    wlMinRows = 1;
    wlMaxColumns = (wlFullScreenWidth / 8);
    wlMaxRows = (wlFullScreenHeight / 8);
	
	//dado em quantidade de linhas.
    textMinWheelDelta = 1;  //mínimo que se pode rolar o texto
    textMaxWheelDelta = 4;  //máximo que se pode rolar o texto	
	textWheelDelta = textMinWheelDelta;
	//...
}



void shellInitWindowSizes (){
	
    //
    //  ## Window size ##
    //

    //wsWindowWidth = wlMinWindowWidth;
    //wsWindowHeight = wlMinWindowHeight;
	
	//Tamanho da janela do shell com base nos limites 
    //que ja foram configurados.	
	
	wsWindowWidth =  WINDOW_WIDTH;
	wsWindowHeight = WINDOW_HEIGHT;
	
	
	if ( wsWindowWidth < wlMinWindowWidth )
	{
		wsWindowWidth = wlMinWindowWidth;
	}
	
	if ( wsWindowHeight < wlMinWindowHeight )
	{
	    wsWindowHeight = wlMinWindowHeight;
	}
}


void shellInitWindowPosition (){
	
	//window position
	wpWindowLeft = WINDOW_LEFT;
	wpWindowTop = WINDOW_TOP;
	
	//wpWindowLeft = (unsigned long) ( (smScreenWidth - wsWindowWidth)/2 );
	//wpWindowTop = (unsigned long) ( (smScreenHeight - wsWindowHeight)/2 );  	
}



/*
 ***************************************************
 * teditorInsertNextChar:
 *     Coloca um char na próxima posição do buffer.
 *     Memória de vídeo virtual, semelhante a vga.
 */

void teditorInsertNextChar (char c){
	

    // Isso funcionou.
    char buff[2];
    buff[0] = (char) c;
    buff[1] = (char) '\0';


    strcat ( RAW_TEXT, (const char *) &buff[0] );

	// Cursor da linha
    LINES[textCurrentRow].CHARS[textCurrentCol] = (char) c;


    //
    // Refresh
    //
    
    teditorRefreshCurrentChar ();


	// Update
    textCurrentCol++;


    if (textCurrentCol >= 80 )
    {
		textCurrentCol = 0;
		
		textCurrentRow++;
		
		if ( textCurrentRow >= 25 )
		{
			//teditorScroll ();
			printf(" *SCROLL");
			while(1){ asm("pause"); }
		}
    };


    LINES[textCurrentRow].pos = textCurrentCol;
    LINES[textCurrentRow].right = textCurrentCol;
}



void 
gramcodeLinesInsertChar ( int line_number, 
                          int at, 
                          int c )
{
    LINES[line_number].CHARS[at] = (char) c;
}


// refresh do char que está na posição usada pelo input.

void teditorRefreshCurrentChar ()
{
    printf ("%c", LINES[textCurrentRow].CHARS[textCurrentCol] );
    fflush(stdout);
}


/*
 **********************************************
 * shellCreateTaskBar:
 *
 */

int saveCreateButton (){

	// Tamanho da tela.
    unsigned long ScreenWidth = gde_get_system_metrics (1);
    unsigned long ScreenHeight = gde_get_system_metrics (2); 


    //printf ("Creating save button ... %d %d\n", ScreenWidth, ScreenHeight);


    //++
    gde_enter_critical_section (); 
    save_button = (void *) gde_create_window ( WT_BUTTON, 1, 1, 
                                " Save ",     
                                4, 4, 80, 24,    
                                hWindow, 0, 
                                xCOLOR_GRAY3, xCOLOR_GRAY3 );

    if ( (void *) save_button == NULL )
    {
        gde_exit_critical_section ();
        printf ("Couldn't create save button\n");
        return 1;
    }
    gde_register_window (save_button);
    gde_show_window (save_button);
    gde_exit_critical_section ();
    //--


	//refresh_screen();
	return 0;
}

//
// ===============================================================
//
int
__SendMessageToProcess ( int pid, 
                         struct window_d *window, 
                         int message,
                         unsigned long long1,
                         unsigned long long2 )
{
	unsigned long message_buffer[5];

	
    if (pid<0)
        return -1;

	message_buffer[0] = (unsigned long) window;
	message_buffer[1] = (unsigned long) message;
	message_buffer[2] = (unsigned long) long1;
	message_buffer[3] = (unsigned long) long2;
	//...


    return (int) gramado_system_call ( 112 , 
                     (unsigned long) &message_buffer[0], 
                     (unsigned long) pid, 
                     (unsigned long) pid );
}
//
// ===============================================================
//



/*
 ****************************
 * main: 
 */
 
int main ( int argc, char *argv[] ){


    FILE *fp;

    int ch;
    int ch_test;    
    int char_count = 0;	



	
	//
	// Atenção: saltando ...
	//
	
	// #todo: 
	// Analizar a contagem de argumentos.
		
	goto skip_test;
	


    /*
     
	//
	//========  test =============
	//

	//say hello.
	FILE *opentty_fp;
	FILE *terminal_opentty_fp;
	int x_ch;
	int terminal_PID;
	#define MSG_TERMINALCOMMAND 100 //provisório
	
	//configurando um stream para o tty
	printf ("gramcode: tentando configurar um stream para o tty\n");
	system_call ( 1001, (unsigned long) stdout, 0, 0 );
	
	printf ("gramcode: tentando obter o ponteiro do arquivo\n");
	opentty_fp = (FILE *) system_call ( 1000, getpid(), 0, 0 );
	
	if ( (void *)opentty_fp == NULL )
	{
		printf ("gramcode: arquivo falhou *hang\n");
		while(1){}
	}
	
	printf ("gramcode: escrever no arquivo\n");
	
		fprintf (opentty_fp, "#### HELLO from gramcode.bin ###\n");
		fprintf (opentty_fp, "#### HELLO2 ###");   //sem \n
	
	printf ("gramcode: escrito\n");
	
	printf ("gramcode: pegando o PID do terminal\n");
	
	
		//get terminal pid
		//avisa o terminal que ele pode imprimir as mesangens pendentes que estao na stream
		terminal_PID = (int) system_call ( 1004, 0, 0, 0 );
	
	printf ("gramcode: terminal_PID=%d\n");
	
	if (terminal_PID <= 0 )
	{
			printf ("gramcode: PID fail\n");
		goto hangz;
	}
	
	printf ("gramcode: enviando mensagem para o terminal\n");
	
		__SendMessageToProcess ( terminal_PID, 0, MSG_TERMINALCOMMAND, 2000, 2000 );
	
hangz:	
	printf ("gramcode.bin: done *hang");
	while(1){}

    */



	//
	//  ========= skip test ============
	//
	
	
skip_test:	
	
	
	
	
	
#ifdef TEDITOR_VERBOSE
    gde_set_cursor (0,0);
	printf("\n");
	printf("Initializing Text Editor:\n");
	printf("mainTextEditor: # argv0={%s} # \n", argv[0] );
	printf("mainTextEditor: # argv1={%s} # \n", argv[1] );
#endif

    //prompt_put_string("Testing ...");
    //prompt_flush(0);
    //#debug
    //while(1){ asm ("pause"); }
	
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
	
	
	//#importante
	//inicializa as variáveis antes de pintar.
    teditorTeditor ();
	

	//
	// Window
	//
    
	// frame
	// Criando uma janela para meu editor de textos.

    //++
    gde_begin_paint (); 
    hWindow = (void *) gde_create_window ( WT_OVERLAPPED, 1, 1, 
                          argv[1],
                          wpWindowLeft, wpWindowTop, 
                          wsWindowWidth, wsWindowHeight,    
                          0, 0, 
                          0x303030, 0x303030 );

    if ( (void *) hWindow == NULL )
    {
        gde_end_paint ();
        printf ("gramcode: hWindow fail\n");
        goto fail;

    }else{

        gde_register_window (hWindow);
        gde_set_active_window (hWindow);       
        gde_show_window (hWindow);
    };
    gde_end_paint ();
    //--
    
    //
    // Background
    //
    
    struct window_d *editbox_bg_Window;

	//++
    gde_enter_critical_section ();  
    editbox_bg_Window = (void *) gde_create_window ( WT_SIMPLE, 1, 1, 
                                    "editbox-bg",     
                                    4, 4 +36, 
                                    wsWindowWidth -4 -40, wsWindowHeight -36 -40, 
                                    hWindow, 0, 
                                    0x303030, 0x303030 );
                                    
    if ( (void *) editbox_bg_Window == NULL)
    {
        gde_exit_critical_section (); 
        printf ("editbox_bg_Window fail");
        while(1){}
    }
    gde_register_window (editbox_bg_Window);
    gde_show_window (editbox_bg_Window);
    gde_exit_critical_section ();  
    //--


    //
    // Editbox.
    //
    
    struct window_d *editboxWindow;

	//++
	gde_enter_critical_section ();  
	editboxWindow = (void *) gde_create_window ( WT_EDITBOX, 1, 1, "editbox",     
                                1, 1, 
                                wsWindowWidth -50, wsWindowHeight -80, 
                                editbox_bg_Window, 0, 0x303030, 0x303030 );
	if ( (void *) editboxWindow == NULL)
	{	
		gde_exit_critical_section ();  
		printf ("editboxWindow fail");
		while(1){}
	}
	gde_register_window (editboxWindow);
	gde_set_focus (editboxWindow);
	gde_show_window (editboxWindow);
	gde_exit_critical_section ();  
	//--



    // #test 
    
    //Terminal window.
    // #importante
    // Definindo a janela como sendo uma janela de terminal.
    // Isso faz com que as digitações tenham acesso ao 
    // procedimento de janela de terminal 
    // para essa janela e não apenas ao procedimento de janela do sistema.
    // # provavelmente isso marca os limites para a 
    // impressão de caractere em modo terminal 
        
    system_call ( SYSTEMCALL_SETTERMINALWINDOW, 
         (unsigned long) editboxWindow, 
         (unsigned long) editboxWindow, 
         (unsigned long) editboxWindow );



    //gde_set_cursor (8,8);
    system_call ( 244, 
        (unsigned long) 0, (unsigned long) 0, (unsigned long) 0 ); 
        
    
    //Isso funcionou,
    //printf ("testing printf");
    //prompt_put_string("Testing prompt ...");
    //prompt_flush(0);
    //#debug
    //while(1){ asm ("pause"); }
       
        
        
     //
     // Status bar. 
     //

	//apiBeginPaint();    
	//editorClearScreen(); 
	//topbarInitializeTopBar();
	//statusInitializeStatusBar();
	//update_statuts_bar("# Status bar string 1","# Status bar string 2");
	//apiEndPaint();
	
	
	
	
    //
	//  ## buffer ##
	//
	
	
    //Inicializando buffer.
	//É nesse buffer que ficará o arquivo de texto que será salvo no disco.

    //strcat( RAW_TEXT, "initializing file ...");		
	
	
//file:

    //
    // File name.
    //

    // argv[0] =  Nome do programa.
    // argv[1] =  Nome do arquivo.


    // Se nenhum nome de arquivo foi especificado, então começamos a digitar.
    if ( (char *) argv[1] == NULL ){
        goto startTyping;	
    }



//#ifdef TEDITOR_VERBOSE
    gde_set_cursor (0,0);
    printf("\n");
    printf("Loading file ...\n");
//#endif	

    //
    // Open.
    //


    fp = fopen ( (char *) argv[1], "rb" );	

    if ( fp == NULL ){
        printf ("gramcode: Couldn't open the file. Start typing ...\n");
        goto startTyping;
    }else{


        // Mostrando o arquivo.
        printf ("\n");

        while (1)
        {
            ch_test = (int) fgetc (fp);

            if ( ch_test == EOF ){
                goto out;
            }else{
                printf ("%c", ch_test);	
            };
        };


out:

//#ifdef TEDITOR_VERBOSE
		//printf("...\n");
        //printf("..\n");
        //printf(".\n");
//#endif


//
//    ======== Start typing ========
//


startTyping:

    //É aqui que fica o arquivo que vamos salvar.
    //file_buffer = &RAW_TEXT[0];


#ifdef TEDITOR_VERBOSE	
	printf ("\n");
	printf ("Typing a text ...\n");
#endif


//#importante:
//Esse loop deve ser um loop de mensagens 
//e não de chars. Quem tem loop de chars 
//é message box.
//Pois o aplicativo deve receber mensagens 
//sobre eventos de input de teclado e mouse,
//assim como os controles.



	// Habilitando o cursor.

    gramado_system_call ( 244, 
        (unsigned long) 0, 
        (unsigned long) 0, 
        (unsigned long) 0 );

		//saiu.
        printf("\n");
        //printf(".\n");
        //printf(".\n");
	};



   
    //printf ("testing printf");   //Isso funcionou,
    //prompt_put_string("Testing prompt ...");  //isso não.
    //prompt_flush(0); //isso não.
 

    // #importante:
    // Nessa hora podemos usar esse loop para pegarmos mensagens 
    // e enviarmos para o procedimento de janela do editor de texto.
    // Para assim tratarmos mensagens de mouse, para clicarmos e 
    // botões para salvarmos o arquivo. 
    // Devemos copiar a forma que foi feita o shell.

    unsigned long message_buffer[5];

Mainloop:


    while (running)
    {
        gde_enter_critical_section (); 
        gramado_system_call ( 111,
            (unsigned long) &message_buffer[0],
            (unsigned long) &message_buffer[0],
            (unsigned long) &message_buffer[0] );
        gde_exit_critical_section (); 

        
        if ( message_buffer[1] != 0 )
        {
            teditorProcedure ( (struct window_d *) message_buffer[0], 
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
    printf ("Exiting editor ...\n");
    printf ("done.\n");


    return 0;
}






