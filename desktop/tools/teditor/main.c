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


#include <types.h>

#include "heap.h"
#include "api.h"

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "status.h"
#include "topbar.h"

#include "teditor.h"

//#define TEDITOR_VERBOSE 1

//# usado para teste 
#define WINDOW_WIDTH     640 
#define WINDOW_HEIGHT    480
#define WINDOW_LEFT      4   //10
#define WINDOW_TOP       4   //10



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


unsigned long 
teditorProcedure ( struct window_d *window, 
                   int msg, 
				   unsigned long long1, 
				   unsigned long long2 );


/*
 ************************************************************
 * mainGetMessage:
 *     Função principla chamada pelo crt0.asm.
 *     Testando o recebimento de mensagens enviadas pelo shell.
 */
 
#define LSH_TOK_DELIM " \t\r\n\a" 
#define SPACE " "
#define TOKENLIST_MAX_DEFAULT 80
 
int mainGetMessage (){
	
	char *tokenList[TOKENLIST_MAX_DEFAULT];
	char *token;
	int token_count;
	int index;	
	
	
	// #importante
	// Linha de comandos passada pelo shell.
	char *shared_memory = (char *) (0xC0800000 -0x100);	
	
	
#ifdef TEDITOR_VERBOSE	
	
	printf("\n");
	printf("mainGetMessage:\n");
	printf("Initializing teditor.bin ...\n\n");	
	//printf("\n");
	//printf(".\n");
	printf("..\n");
	printf("# MESSAGE={%s} #\n", shared_memory );
	printf("..\n");
	//printf(".\n");
	//printf("\n");
	
	//#debug
	//while(1){
	//	asm ("pause");
	//}
	
#endif
	

    // Criando o ambiente.
	// Transferindo os ponteiros do vetor para o ambiente.

	tokenList[0] = strtok ( &shared_memory[0], LSH_TOK_DELIM );
	
 	// Salva a primeira palavra digitada.
	token = (char *) tokenList[0];
 
	index = 0;                                  
    while ( token != NULL )
	{
        // Coloca na lista.
        // Salva a primeira palavra digitada.
		tokenList[index] = token;

		//#debug
        //printf("shellCompare: %s \n", tokenList[i] );
		
		token = strtok ( NULL, LSH_TOK_DELIM );
		
		// Incrementa o índice da lista
        index++;
		
		// Salvando a contagem.
		token_count = index;
    }; 

	//Finalizando a lista.
    tokenList[index] = NULL;	
	
	
	// #debug 
	// Mostra argumentos.
#ifdef TEDITOR_VERBOSE	
	// Mostra a quantidade de argumentos. 	
	printf("\n");
	printf("token_count={%d}\n", token_count );
	
	//Mostra os primeiros argumentos.
	for ( index=0; index < token_count; index++ )
	{
		token = (char *) tokenList[index];
	    if ( token == NULL )
		{
			printf("mainGetMessage: for fail!\n")
			goto hang;
		}
	    printf("# argv{%d}={%s} #\n", index, tokenList[index] );		
	};
#endif	
	
	

	
#ifdef TEDITOR_VERBOSE		
    //Inicializando o editor propriamente dito.	
	printf("Calling mainTextEditor ... \n"); 
#endif	
	
	
	int retval;

    retval = (int) mainTextEditor ( token_count, tokenList );
	
	switch (retval)
	{
		case 0:
		    printf("mainGetMessage: mainTextEditor returned 0.\n");
			break;
			
		case 1:
		    printf("mainGetMessage: mainTextEditor returned 1.\n");
		    break;
			
		//...
		
	    default:
		    printf("mainGetMessage: mainTextEditor returned defaul\n");
            break; 		
	};
		
    printf("*HANG\n");
	
    while (1){
        asm("pause");
    };
};


/*
 ********************************************
 * mainTextEditor:
 *     O editor de textos.
 * In this fuction:
 *     Initializes crt.
 *     Initializes stdio.
 *
 */
int mainTextEditor ( int argc, char *argv[] ){
	
	int ch;
	FILE *fp;
    int char_count = 0;	
	
	struct window_d *hWindow;
	
	
	//#todo: analizar a contagem de argumentos.
	
	
#ifdef TEDITOR_VERBOSE			
	printf("\n");
	printf("Initializing Text Editor:\n");
	printf("mainTextEditor: # argv0={%s} # \n", argv[0] );	
	printf("mainTextEditor: # argv1={%s} # \n", argv[1] );
#endif	

    //#debug
    //while(1){
	//	asm ("pause");
	//}
	
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
	
	
    //stdlib
	//inicializando o suporte a alocação dinâmica de memória.
	libcInitRT();

	//stdio
	//inicializando o suporte ao fluxo padrão.
    stdioInitialize();	
	
	
	//#importante
	//inicializa as variáveis antes de pintar.
    teditorTeditor ();	
	

	//
	// ## Window ##
	//
    
	//frame
	//Criando uma janela para meu editor de textos.
	
	apiBeginPaint(); 

	hWindow = (void *) APICreateWindow ( WT_OVERLAPPED, 1, 1, argv[1],
	                    wpWindowLeft, wpWindowTop, wsWindowWidth, wsWindowHeight,    
                        0, 0, 0x303030, 0x303030 );	   
	

	if ( (void *) hWindow == NULL )
	{	
		printf("TEDITOR.BIN: hWindow fail");
		apiEndPaint();
		goto fail;
	}
    apiEndPaint();
	
    APIRegisterWindow(hWindow);
	
	
	//set active efetua um redraw ...
	//isso parece ser redundante na inicialização do 
	//programa. Talvez o certo seria desenhar a janela 
	//ja setando ativando.	
    APISetActiveWindow(hWindow);	
    
	//set focus efetua um redraw ...
	//isso parece ser redundante na inicialização do 
	//programa. Talvez o certo seria desenhar a janela 
	//ja setando o foco.
	APISetFocus(hWindow);	
	
	refresh_screen ();	


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
	
//file:

#ifdef TEDITOR_VERBOSE		
	//printf("\n");
	printf("\n");
    printf("Loading file ...\n");
#endif	
	
	// Page fault:    
	// Pegando o argumento 1, porque o argumento 0 é o nome do editor.
	
    // ## No file ## 
	//Se nenhum nome de arquivo foi especificado, então começamos a digitar.
	
	if ( (char *) argv[1] == NULL )
	{	
	    goto startTyping;	
	};
	
	
#ifdef TEDITOR_VERBOSE		
	//printf("\n");
	printf("\n");
    printf("Loading file fopen ...\n");
#endif		
	
	// ## Carregando arquivo. ##
	//
	
	fp = fopen ( (char *) argv[1], "rb" );	
	
	if ( fp == NULL )
    {
        printf("fopen fail start typing ...\n");
        goto startTyping;
		
    }else{
		
		//Mostrando o arquivo.
		
#ifdef TEDITOR_VERBOSE			
        printf(".\n");		
        printf("..\n");		
        //printf("...\n");
#endif 
	
       // printf("Show file\n");
		printf ( "%s", fp->_base );	
       // printf("Show file done\n");
		
#ifdef TEDITOR_VERBOSE	        
		//printf("...\n");
        printf("..\n");		
        printf(".\n");		
#endif

startTyping:

#ifdef TEDITOR_VERBOSE	
		printf("\n");
		printf("Typing a text ...\n");
#endif


//#importante:
//Esse loop deve ser um loop de mensagens 
//e não de chars. Quem tem loop de chars 
//é message box.
//Pois o aplicativo deve receber mensagens 
//sobre eventos de input de teclado e mouse,
//assim como os controles.



	//
	// Habilitando o cursor de textos.
	//
	
	system_call ( 244, (unsigned long) 0, (unsigned long) 0, (unsigned long) 0 );	

	
		//saiu.
        printf(".\n");		
        printf(".\n");		
        printf(".\n");

	};
	
	unsigned long message_buffer[5];	
	
Mainloop:		    
	//
    // #importante:
    // Nessa hora podemos usar esse loop para pegarmos mensagens 
    // e enviarmos para o procedimento de janela do editor de texto.
    // Para assim tratarmos mensagens de mouse, para clicarmos e 
    // botões para salvarmos o arquivo. 
    // Devemos copiar a forma que foi feita o shell.
    //   

    
	
	while (running)
	{
		enterCriticalSection(); 
		system_call ( 111,
		    (unsigned long)&message_buffer[0],
			(unsigned long)&message_buffer[0],
			(unsigned long)&message_buffer[0] );
		exitCriticalSection(); 
			
		if (	message_buffer[1] != 0 )
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
    printf("fail.\n");
done:
    running = 0;
    printf("Exiting editor ...\n");
    printf("done.\n");
	while (1)
	{
		asm("pause");
		exit(0);
	};
    // Never reach this.	
	return (int) 0;
};


/*
 *  
 *     Limpar a tela 
 */

void editorClearScreen (){
	
	int lin, col;    

	// @todo:
	//system( "cls" ); // calls the cls command.
	
	//cursor.
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




//testando a rotina de salvar um arquivo.
//estamos usando a API.
int editor_save_file (){
	
	//
	// #importante:
	// Não podemos chamar a API sem que todos os argumentos estejam corretos.
	//
	
	// #obs:
	// Vamos impor o limite de 4 setores por enquanto. 
	// 512*4 = 2048  (4 setores) 2KB
	// Se a quantidade de bytes for '0'. ???
	
	int Ret;
	
	char file_1[] = "Arquivo \n escrito \n em \n user mode no editor de textos teditor.bin :) \n";
	char file_1_name[] = "FILE2UM TXT";
	
	printf("editor_save_file: Salvando um arquivo ...\n");
	
	unsigned long number_of_sectors = 0;
    size_t len = 0;
	
	
	//
	// Lenght in bytes.
	//
	
	len = (size_t) strlen (file_1);

	if (len <= 0)
	{
	    printf ("editor_save_file:  Fail. Empty file.\n");
        return (int) 1;		
	}
	
	if (len > 2048)
	{
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
	
	if ( number_of_sectors == 0 )
	{
	    printf ("editor_save_file:  Limit Fail. (0) sectors so save.\n");
        return (int) 1;				
	}
	
	//limite de teste.
	//Se tivermos que salvar mais que 4 setores.
	if ( number_of_sectors > 4 )
	{
	    printf ("editor_save_file:  Limit Fail. (%d) sectors so save.\n",
		    number_of_sectors );
        return (int) 1;				
	}
	
	
    Ret = (int) apiSaveFile ( file_1_name,  //name 
                              number_of_sectors,            //number of sectors.
                              len,            //size in bytes			
                              file_1,       //address
                              0x20 );       //flag		
				
	//if (Ret == 0)
	
	printf("t5: done.\n");	
	
	return (int) Ret;
};


unsigned long 
teditorProcedure( struct window_d *window, 
                int msg, 
				unsigned long long1, 
				unsigned long long2 )
{
	unsigned long input_ret;
    unsigned long compare_return;	
    int q;	
	
	
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
				
				case VK_RETURN:
				    
					//#test
					printf("\r");
					printf("\n");
					
                    break; 

				//#test	
                case VK_TAB:					
					printf("\t");
				    break;

				//#todo	
				case VK_BACK:
				    
					//#test
					//o cursor do ldisc no kernel precisa ser atualizado tambem.
					//textCurrentCol--;
					//apiSetCursor (textCurrentCol,textCurrentRow);
					//teditorInsertNextChar ( (char) ' ' ); 					
					
                    break;					
				
				
				//teclas de digitação.
				default:
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
};



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
	
    shellInitSystemMetrics();
    shellInitWindowLimits();
    shellInitWindowSizes();
    shellInitWindowPosition();
	
};



void shellInitSystemMetrics()
{
	//pegaremos todas as metricas de uma vez só,
	//se uma falhar, então pegaremos tudo novamente.
	
	// Tamanho da tela.	
	smScreenWidth = apiGetSystemMetrics(1);
    smScreenHeight = apiGetSystemMetrics(2); 
	smCursorWidth = apiGetSystemMetrics(3);
	smCursorHeight = apiGetSystemMetrics(4);
	smMousePointerWidth = apiGetSystemMetrics(5);
	smMousePointerHeight = apiGetSystemMetrics(6);
	smCharWidth = apiGetSystemMetrics(7);
	smCharHeight = apiGetSystemMetrics(8);	
	//...
} 


void shellInitWindowLimits(){
	
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
}




void shellInitWindowSizes()
{
	
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


};


void shellInitWindowPosition()
{
	
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
	
	
	//cursor da linha
	
	LINES[textCurrentRow].CHARS[textCurrentCol] = (char) c;
	
	//refresh
	teditorRefreshCurrentChar();
	
	//update
	textCurrentCol++;
	
	if (textCurrentCol >= 80 )
	{
		textCurrentCol = 0;
		
		textCurrentRow++;
		
		if ( textCurrentRow >= 25 )
		{
			//shellScroll ();
			printf(" *SCROLL");
			while(1){}
		}
	}
	
	LINES[textCurrentRow].pos = textCurrentCol;
	LINES[textCurrentRow].right = textCurrentCol;
};


//refresh do char que está na posição usada pelo input.

void teditorRefreshCurrentChar (){
	
	printf ("%c", LINES[textCurrentRow].CHARS[textCurrentCol] );
};



