/*
 * File: main.c
 *
 * Arquivo principal do aplicativo gramtext.
 * O aplicativo é usado para testes do sistema operacional Gramado 0.4
 *
    ## todo: 
	pegar algumas funções do shell e usar aqui.
	agora eles usam o mesmo esquema de strutura de linhas para o texto.
 
 * 2018 - Created by Fred Nora.
 */
 
 
#include "gramtext.h"




//#define TEDITOR_VERBOSE 1

//# usado para teste 
#define WINDOW_WIDTH     430//400 //640 
#define WINDOW_HEIGHT    400 //480
#define WINDOW_LEFT      4   //10
#define WINDOW_TOP       4   //10



//static int _running = 1;
int _running = 1;

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


unsigned long 
gramtextProcedure ( struct window_d *window, 
                   int msg, 
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
	
	apiSetCursor ( 0, 0 );
	
	// Tamanho da tela. 80x25

	//linhas.
	for ( lin=0; lin < ((600/8)-1); lin++ )
	{
		col = 0;
		
		apiSetCursor(col,lin);
		
		//colunas.
		for ( col=0; col < ((800/8)-1); col++ ){
			
			printf("%c",' ');
	    }
	};
	
	apiSetCursor(0,2);
};



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
	
	//char file_1[] = "Arquivo \n escrito \n em \n user mode no editor de textos teditor.bin :) \n";
	char file_1_name[] = "FILE1234TXT";
	
	unsigned long number_of_sectors = 0;
    size_t len = 0;
	
    
	//Initializing ...
	
	printf("editor_save_file: Salvando um arquivo ...\n");
	
	
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
	
	if ( len > 0 && len < 512 ){
		
	    number_of_sectors = 1; 
    }		
	
	if ( number_of_sectors == 0 ){
		
	    printf ("editor_save_file:  Limit Fail. (0) sectors to save.\n");
        return (int) 1;				
	}
	
	
	//limite de teste.
	//Se tivermos que salvar mais que 4 setores.
	if ( number_of_sectors > 4 )
	{
	    printf ("editor_save_file:  Limit Fail. (%d) sectors to save.\n",
		    number_of_sectors );
        return (int) 1;				
	}
	
	
	//
	// ## save ##
	//
	
	//name, number of sectors, size in bytes, address, flag.
	
    //Ret = (int) apiSaveFile ( file_1_name, number_of_sectors, len,            
    //                file_1, 0x20 );       		

    Ret = (int) apiSaveFile ( file_1_name, number_of_sectors, len,            
                    &RAW_TEXT[0], 0x20 );       		
					
	//if (Ret == 0)
	
	printf ("done\n");	
	
	return (int) Ret;
}


/*
 * gramtextProcedure:
 *     Procedimento de janela do editor.
 */

unsigned long 
gramtextProcedure ( struct window_d *window, 
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
				
				//#todo: Insert new line;	
				case VK_RETURN:
					printf ("\r\n");
                    break; 

                case VK_TAB:					
					printf ("\t");
				    break;

				//#todo	
				case VK_BACK:
				    
					//#test
					//o cursor do ldisc no kernel precisa ser atualizado tambem.
					//textCurrentCol--;
					//apiSetCursor (textCurrentCol,textCurrentRow);
					//teditorInsertNextChar ( (char) ' ' ); 	
					
					MessageBox ( 3, "String1","String2" );
					
                    break;					
				
				
				//teclas de digitação.
				default:
					
					// Control + s ?
				    if ( long1 == 's' )
					{
					    //#todo
						//pegar o status de control.
						//#todo: isso precisa ir para a API.(138)
						key_state = (int) system_call ( 138, (unsigned long) VK_CONTROL , 
						                    (unsigned long) VK_CONTROL , (unsigned long) VK_CONTROL  );	
                        						
					    // pressionada
						if ( key_state == 1 )
					    {
						    editor_save_file ();	
							key_state = -1;
							break;
						}
					}
					
					// #importante:
					// Insert char.
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
		        
				//esquerda
				case VK_F1:
				   //textCurrentCol -= 1;
				   break;
				
				//direita
				case VK_F2:
				   //textCurrentCol += 1;
				   break;

				//baixo  
				case VK_F3:
				   //textCurrentRow += 1;
				   break;

				//cima   
				case VK_F4:
				   //textCurrentRow -= 1;
				   break;

			};
			break;
			
		default:
		    break;
				
	};
	
	return 0;
}


/*
 *********************************
 * teditorTeditor:
 *     Contrutor e inicialização.
 */

void teditorTeditor (){
	
	int i=0;
	int j=0;
	
	// Inicializando as estruturas de linha.
	// Inicializamos com espaços.
	
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
	
	
	// Inicializa as métricas do sistema.	
    // Inicializa os limites da janela.
	// Inicia o tamanho da janela.
	// Inicializar a posição da janela.
	
    shellInitSystemMetrics ();
    shellInitWindowLimits ();
    shellInitWindowSizes ();
    shellInitWindowPosition ();
}



// Get system metrics.
// Pegaremos todas as metricas de uma vez só,
// se uma falhar, então pegaremos tudo novamente.

void shellInitSystemMetrics (){
	
	// Tamanho da tela.	
	smScreenWidth = apiGetSystemMetrics (1);
    smScreenHeight = apiGetSystemMetrics (2); 
	
	// Cursor.
	smCursorWidth = apiGetSystemMetrics (3);
	smCursorHeight = apiGetSystemMetrics (4);
	
	// Pointer.
	smMousePointerWidth = apiGetSystemMetrics (5);
	smMousePointerHeight = apiGetSystemMetrics (6);
	
	// Char.
	smCharWidth = apiGetSystemMetrics (7);
	smCharHeight = apiGetSystemMetrics (8);	
	
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
    wlMinWindowWidth = smCharWidth * 80;
    wlMinWindowHeight = smCharWidth * 25;
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
};



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
	
	char buff[2];
	
	buff[0] = (char) c;
	buff[1] = (char) '\0';
	
	
	// Coloca no buffer de arquivo cru.
	
	strcat ( RAW_TEXT, (const char *) &buff[0] );
	
	
	// #importante:
	// Coloca na linha e coluna certas.
	
	LINES[textCurrentRow].CHARS[textCurrentCol] = (char) c;
	
	// ??
	// refresh
	teditorRefreshCurrentChar ();
	
	//
	// Update cursor.
	//
	
	textCurrentCol++;
	
	if (textCurrentCol >= 80 )
	{
		textCurrentCol = 0;
		
		textCurrentRow++;
		
		if ( textCurrentRow >= 25 )
		{
			//teditorScroll ();
			printf (" *SCROLL");
			while (1){ asm ("pause"); }
		}
	};
	
    // Posição do último caractere incluído na linha.
	LINES[textCurrentRow].right = textCurrentCol;
	
	// Posição do cursor dentro da linha.
	// É onde o dado deve entrar.
	LINES[textCurrentRow].pos = textCurrentCol;
}


// Insere um char em uma posição de alguma linha, mas não atualiza
// posições de cursor.
void gramcodeLinesInsertChar ( int line_number, int at, int c ){
	
	LINES[line_number].CHARS[at] = (char) c;
}
	

//refresh do char que está na posição usada pelo input.

void teditorRefreshCurrentChar (){
	
	printf ( "%c", LINES[textCurrentRow].CHARS[textCurrentCol] );
}



/*
 *********************************
 * main: 
 */
 
int main ( int argc, char *argv[] ){
	
	int ch;
	FILE *fp;
    int char_count = 0;	
	
	struct window_d *hWindow;
	
	
	//#todo: analizar a contagem de argumentos.
	
	
#ifdef TEDITOR_VERBOSE			
	printf ("\n");
	printf ("Initializing gramtext ...\n");
	printf ("# argv0={%s} # \n", argv[0] );	
	printf ("# argv1={%s} # \n", argv[1] );
#endif	

    // #debug
    // while(1){ asm ("pause"); }
	
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
	// ## Window ##
	//
    
	//frame
	//Criando uma janela para meu editor de textos.


    //++
    apiBeginPaint(); 
    hWindow = (void *) APICreateWindow ( WT_OVERLAPPED, 1, 1, argv[1],
                          wpWindowLeft, wpWindowTop, wsWindowWidth, wsWindowHeight,    
                          0, 0, 0x303030, 0x303030 );

    if ( (void *) hWindow == NULL )
    {
        printf ("gramcode: hWindow fail\n");
        goto fail;
    }else{

        APIRegisterWindow (hWindow);
        APISetActiveWindow (hWindow);
        
        // #bugbug
        // ??
        // Isso está repintando a moldura e ficando ruin.
        // Mas precisamos do foco senão trava por causa do teclado.
        // Se setarmos o foco na janela, então a janela mãe
        // será repintada e se tornará a janela ativa.

        //APISetFocus (hWindow);

        apiShowWindow (hWindow);
    };
    apiEndPaint();
    //--


    struct window_d *editbox_bg_Window;

	//++
	enterCriticalSection ();  
	editbox_bg_Window = (void *) APICreateWindow ( WT_SIMPLE, 1, 1, "editbox-bg",     
                                4, 4 +36, 
                                wsWindowWidth -4 -40, wsWindowHeight -36 -40, 
                                hWindow, 0, 0x303030, 0x303030 );
	if ( (void *) editbox_bg_Window == NULL)
	{	
		printf("edit box fail");
		refresh_screen();
		while(1){}
	}
	APIRegisterWindow (editbox_bg_Window);
	
	//APISetFocus (editbox_bg_Window);
	
	apiShowWindow (editbox_bg_Window);
	exitCriticalSection ();  
	//--
	
	
	
	
	

    struct window_d *editboxWindow;

	//++
	enterCriticalSection ();  
	editboxWindow = (void *) APICreateWindow ( WT_EDITBOX, 1, 1, "editbox",     
                                1, 1, 
                                wsWindowWidth -50, wsWindowHeight -80, 
                                editbox_bg_Window, 0, 0x303030, 0x303030 );
	if ( (void *) editboxWindow == NULL)
	{	
		printf("edit box fail");
		refresh_screen();
		while(1){}
	}
	APIRegisterWindow (editboxWindow);
	
	APISetFocus (editboxWindow);
	
	apiShowWindow (editboxWindow);
	exitCriticalSection ();  
	//--





 


	//apiBeginPaint();    
	//editorClearScreen(); 
	//topbarInitializeTopBar();
	//statusInitializeStatusBar();
	//update_statuts_bar("# Status bar string 1","# Status bar string 2");
	//apiEndPaint();
	
	
	//apiBeginPaint();
	//?? edit box ??
	//apiEndPaint();
	
	//
	//  ## Testing file support. ##
	//
	
	
    //
	//  ## buffer ##
	//
	
	
    //Inicializando buffer.
	//É nesse buffer que ficará o arquivo de texto que será salvo no disco.

    //strcat( RAW_TEXT, "initializing file ...");		
	
	
//file:
	
	// Page fault:    
	// Pegando o argumento 1, porque o argumento 0 é o nome do editor.
	
    // ## No file ## 
	//Se nenhum nome de arquivo foi especificado, então começamos a digitar.
	
	if ( (char *) argv[1] == NULL )
	{	
	    goto startTyping;	
	};
	
	
//#ifdef TEDITOR_VERBOSE		
	//printf ("\n");
    printf ("Loading file. fopen ...\n");
//#endif	

	// Carregando arquivo. 
	
	fp = fopen ( (char *) argv[1], "rb" );	
	
	if (fp == NULL)
    {
        printf ("fopen fail, start typing ...\n");
				
        goto startTyping;
		
    }else{
		
		//Mostrando o arquivo.
		
//#ifdef TEDITOR_VERBOSE			
        printf(".\n");		
        printf("..\n");		
        //printf("...\n");
//#endif 
	
       // printf("Show file\n");
		//printf ( "%s", fp->_base );	
       // printf("Show file done\n");
		
		//#test 
		//configurando o endereço do buffer do arquivo carregado.
		//file_buffer = fp->_base;
		
		int ch_test;
		
//#ifdef TEDITOR_VERBOSE
	    //printf ("Testing fgetc ... \n\n");
//#endif 		
		
		while (1)
		{
			// #bugbug: 
			// Page fault quando chamamos fgetc.
			
			//printf("1");
			ch_test = (int) fgetc (fp);
			//ch_test = (int) getc (f1); 
			
			if (ch_test == EOF)
			{
				printf ("\n");
				printf ("EOF reached :)\n");
				
				goto out;
				
			}else{
				
				// #importante
				// Imprimir na tela os caracteres obtidos no arquivo.
				
				//printf("2");
			    printf ("%c", ch_test);	
			};
		};
		
out:
		
//#ifdef TEDITOR_VERBOSE	        
		//printf("...\n");
        printf("..\n");		
        printf(".\n");		
//#endif

		
startTyping:
		
    // É aqui que fica o arquivo que vamos salvar.
		
    //file_buffer = &RAW_TEXT[0];

//#ifdef TEDITOR_VERBOSE	
//		printf ("\n");
//		printf ("Typing a text ...\n");
//#endif

	//
	// Habilitando o cursor de textos.
	//
	
    system_call ( 244, 
        (unsigned long) 0, (unsigned long) 0, (unsigned long) 0 );

		//saiu.
        printf(".\n");
        printf(".\n");
        printf(".\n");

	}; //fim do else.
	

    unsigned long message_buffer[5];


	//
	// main loop
	//

	
// #importante:
// Esse loop deve ser um loop de mensagens e não de chars. Pois o aplicativo 
// deve receber mensagens sobre eventos de input de teclado e mouse,
// assim como os controles.	
// Nessa hora vamos usar esse loop para pegarmos mensagens 
// e enviarmos para o procedimento de janela do editor de texto.
// Para assim tratarmos mensagens de mouse, para clicarmos e 
// botões para salvarmos o arquivo. 
	
	
Mainloop:

    while (_running)
    {
		enterCriticalSection(); 
		system_call ( 111,
		    (unsigned long)&message_buffer[0],
			(unsigned long)&message_buffer[0],
			(unsigned long)&message_buffer[0] );
		exitCriticalSection(); 
			
		if ( message_buffer[1] != 0 )
		{
	        gramtextProcedure ( (struct window_d *) message_buffer[0], 
		        (int) message_buffer[1], 
		        (unsigned long) message_buffer[2], 
		        (unsigned long) message_buffer[3] );

            message_buffer[0] = 0;
            message_buffer[1] = 0;
            message_buffer[3] = 0;
            message_buffer[4] = 0;
        };
    };

	
	//
	// fail.
	//
	
fail:
    printf ("fail\n");

done:

	printf ("Exiting editor ...\n");
    printf ("done\n");

    _running = 0;

    return 0;
}

//
// End.
//



