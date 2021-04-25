/*
 * File shellui.c 
 * 
 * 2017 - Fred Nora.
 */


#include "gdeshell.h"


extern int ShellFlag;


#define SHELLFLAG_NULL 0
#define SHELLFLAG_COMMANDLINE 1
#define SHELLFLAG_SCRIPT 2
#define SHELLFLAG_HELP 3
#define SHELLFLAG_VERSION 4
#define SHELLFLAG_USAGE 5
#define SHELLFLAG_TOPBAR 6
//...


// Credits: L.
void shellui_fntos (char *name)
{
    int  i, ns = 0;
    char ext[4];
    //const char ext[4];

    //transforma em maiúscula
    while ( *name && *name != '.' )
    {
        if ( *name >= 'a' && *name <= 'z' )
            *name -= 0x20;

        name++;
        ns++;

        // ##bugbug: 
        // E se não encontrarmos o ponto??
    };

    // aqui name[0] é o ponto.
	// então constroi a extensão.
    for ( i=0; i < 3 && name[i+1]; i++ )
    {
        if ( name[i+1] >= 'a' && name[i+1] <= 'z' )
            name[i+1] -= 0x20;

        ext[i] = name[i+1];
    };

    while (ns < 8)
    {
        *name++ = ' ';
        ns++;
    };

    for ( i=0; i < 3; i++ ){
        *name++ = ext[i];
    };

    *name = '\0';
}


/*
 ***********************************************
 * shellTopbarProcedure:
 *     Procedimento de janela.
 *     LOCAL
 */

unsigned long 
shellTopbarProcedure ( 
    struct window_d *window, 
    int msg, 
    unsigned long long1, 
    unsigned long long2 )
{
    printf ("shellTopbarProcedure: Deprecated\n");
    return 0;
}


// Deprecated
void shellCreateEditBox (void)
{
    printf ("shellCreateEditBox: Deprecated\n");
    return 0;
}


/*
 ******************** 
 * shellCreateMainWindow:
 *
 *     Obs: Essa é uma janela filha.
 *     @todo: ?? e o procedimento de janela ?? e as mensagens ??
 *     Obs: É uma janela simples e limpa, feita para dispositivos IOT 
 * com resolução 800x600.
 *
 */
 
// #todo
// Vamos criar a main window do tamanho da tela. get system metrics. 

// #bugbug
// Por causa do gerenciamento da sessão crítica essa função 
// deverá retornar NULL se falhar.

struct window_d *shellCreateMainWindow ( int status ){

    struct window_d *w;

     //#bugbug
     //shellShell já inicializou isso com a métrica do sistema.

    //
    // Limits.
    //

    if ( wpWindowLeft > 50 )
        wpWindowLeft = 50;

    if ( wpWindowTop > 50 )
        wpWindowTop = 50;

    if ( wsWindowWidth > 2048 )
        wsWindowWidth = 2048;

    if ( wsWindowHeight > 2048 )
        wsWindowHeight = 2048;

    // no zeros.

    if ( wsWindowWidth == 0 ) { wsWindowWidth  = 100; }
    if ( wsWindowHeight == 0 ){ wsWindowHeight = 100; }


    /*
     // #debug
     printf("l={%d} t={%d} w={%d} h={%d}\n", 
         wpWindowLeft, wpWindowTop, wsWindowWidth, wsWindowHeight ); 
     while (1){ asm ("pause"); }
    */


    //
    // Draw
    //
    
    // #todo
    // We have the argument 'status'.
    // Is it used here?

    // backup
    //w = (void *) gde_create_window ( 
    //                 1, 1, 1, "gdeshell",
    //                 wpWindowLeft, wpWindowTop, 
    //                 wsWindowWidth, wsWindowHeight,    
    //                 0, 0, xCOLOR_GRAY1, xCOLOR_GRAY1 );

    w = (void *) gde_create_window ( 
                     WT_OVERLAPPED, 1, 1, "gdeshell",
                     wpWindowLeft, wpWindowTop, 
                     wsWindowWidth, wsWindowHeight,    
                     0, 0, xCOLOR_GRAY1, xCOLOR_GRAY1 );


    // #bugbug
    // Por causa do gerenciamento da sessão crítica essa função 
    // deverá retornar NULL se falhar.

    return (struct window_d *) w;
}

// IN: The console window
int commodore_ui(struct window_d *window)
{

    return -1;
    
    /*
    struct window_d  *w;  


    printf("commodore_ui: Starting ...\n");

    w = (struct window_d *) window;

    if ( (void*) w == NULL ){
        printf("commodore_ui: w\n");
        return -1;
    }
    
    //++
    gde_enter_critical_section ();

    // Set terminal window.
    // This way the kernel will use this window to print the chars
    // in terminal mode.
    
    gramado_system_call ( 
        SYSTEMCALL_SETTERMINALWINDOW, 
        (unsigned long) w, 
        (unsigned long) w, 
        (unsigned long) w );
        
    gde_replace_window(w,40,40);
    gde_resize_window(w,320,280);

    //terminal_rect.left   = wpWindowLeft;
    //terminal_rect.top    = wpWindowTop;
    //terminal_rect.width  = wsWindowWidth;
    //terminal_rect.height = wsWindowHeight;
    
    gde_redraw_window(w,TRUE);
    
    
    shellSetCursor(0,0);
    
    
    // gde_show_window(w);

    gde_exit_critical_section ();
    //--
    
    */
    
    return -1;
}



// Create window test.
void testCreateWindow (void)
{
    struct window_d *hWindow;

    //++
    gde_begin_paint();
    
    hWindow = (void *) gde_create_window ( 
                         WT_OVERLAPPED, 1, 1, "XXX-test", 
                         10, 10, 200, 200,
                         0, 0, COLOR_RED, COLOR_YELLOW ); 

    if ( (void *) hWindow == NULL )
    {
        gde_end_paint();
        return;
    }

    // ok. Registrar e mostrar.
    gde_register_window(hWindow);
    gde_show_window(hWindow);

    gde_end_paint();
    //--
}


/*
 *************************************
 * shellDisplayBMP:
 *     Carrega um arquivo .bmp na memória e decodifica, mostrando na tela.
 */

int shellDisplayBMP (char *file_name){
	
	// #bugbug @todo: Aumenta o tamanho do heap do processo.
	// Esse heap é gerenciando nas bibliotecas ou na API.
	//Obs: 32Kb é alem do limite.
	
	// testando malloc.
	void *b = (void *) malloc (1024*30); 	
    
	if ( (void *) b == NULL )
	{
		printf("shellTestDisplayBMP: allocation fail\n");
		//while(1){}
		return -1;
	}
	
	//Carregando o arquivo.
loadFile:

    shellui_fntos ( (char *) file_name );

    //@todo: Usar alguma rotina da API específica para carregar arquivo.
	// na verdade tem que fazer essas rotinas na API.
	
	system_call ( SYSTEMCALL_READ_FILE, (unsigned long) file_name, 
		(unsigned long) b, (unsigned long) b);	
	 
	//Usando a API para exibir o bmp carregado. 
	gde_display_bmp ( (char *) b, 10, 00 ); 
 
    //
	//Mostrando informações sobre o arquivo.
	//
	
	//base do bmp carregado na memória
	//unsigned char *bmp = (unsigned char *) b;
	
	
	//@todo: encontrando o magic
	
	//if( bmp[0] != 0x42 )
	//{
	//	printf("~Sig fail\n");
	//    printf("magic0 %c\n", bmp[0]);	
	//    printf("magic1 %c\n", bmp[1]);			
	//	printf("buffer %x\n",bmp); //Ok
    //    printf("buffer %x\n",b);   //Ok
		//printf("width %d \n", bmp[0x12]);
		//printf("height %d \n", bmp[0x16]);
	//}
	
	//
	//Mostrando características do bmp.
	
	//printf("magic0 %c\n", bmp[0]);	
	//printf("magic1 %c\n", bmp[1]);
	//printf("data area begin %c %c %c \n",bmp[base] ,bmp[base+1] ,bmp[base+2]);	
	//printf("buffer %x \n",bmp);
	//printf("data area address %x \n",&bmp[base]);
	
	return 0;
}


/*
 *************************************
 * shellDisplayBMP:
 *     Carrega um arquivo .bmp na memória e decodifica, mostrando na tela.
 *  tamanho dado em kb
 */

int shellDisplayBMPEx (char *file_name, int size )
{

    // não pode ser igual a zero, 
    // nem menor que zero, nem maior que 3mb.

    if ( size <= 0 || size > (1024*3) )
    {
        return 1;
    }

	// testando malloc.
	void *b = (void *) malloc (1024*size); 	
    
	if ( (void *) b == NULL )
	{
		printf("shellTestDisplayBMP: allocation fail\n");
		//while(1){}
		return -1;
	}
	
	//Carregando o arquivo.
loadFile:

    shellui_fntos ( (char *) file_name );

    //@todo: Usar alguma rotina da API específica para carregar arquivo.
	// na verdade tem que fazer essas rotinas na API.
	
	system_call ( SYSTEMCALL_READ_FILE, (unsigned long) file_name, 
		(unsigned long) b, (unsigned long) b);	
	 
	//Usando a API para exibir o bmp carregado. 
	gde_display_bmp ( (char *) b, 0, 0 ); 
	 
    //
	//Mostrando informações sobre o arquivo.
	//
	
	//base do bmp carregado na memória
	//unsigned char *bmp = (unsigned char *) b;
	
	
	//@todo: encontrando o magic
	
	//if( bmp[0] != 0x42 )
	//{
	//	printf("~Sig fail\n");
	//    printf("magic0 %c\n", bmp[0]);	
	//    printf("magic1 %c\n", bmp[1]);			
	//	printf("buffer %x\n",bmp); //Ok
    //    printf("buffer %x\n",b);   //Ok
		//printf("width %d \n", bmp[0x12]);
		//printf("height %d \n", bmp[0x16]);
	//}
	
	//
	//Mostrando características do bmp.
	
	//printf("magic0 %c\n", bmp[0]);	
	//printf("magic1 %c\n", bmp[1]);
	//printf("data area begin %c %c %c \n",bmp[base] ,bmp[base+1] ,bmp[base+2]);	
	//printf("buffer %x \n",bmp);
	//printf("data area address %x \n",&bmp[base]);
	
	return 0;
}



/*
 * shellTestDisplayBMP:
 *     Carrega um arquivo .bmp na memória e decodifica, mostrando na tela.
 *     Devemos usar a função oferecida pela api.
 */

void shellTestDisplayBMP (void)
{
	// #bugbug @todo: Aumenta o tamanho do heap do processo.
	// Esse heap é gerenciando nas bibliotecas ou na API.
	// Obs: 32Kb é alem do limite.

    void *b = (void *) malloc (1024*30);
    
    if ( (void *) b == NULL )
    {
        printf("shellTestDisplayBMP: b\n");
        return;
    }


//Carregando o arquivo.
loadFile:
    //@todo: Usar alguma rotina da API específica para carregar arquivo.
	// na verdade tem que fazer essas rotinas na API.

    system_call ( 
        SYSTEMCALL_READ_FILE, 
        (unsigned long) bmp1_file_name, 
        (unsigned long) b, 
        (unsigned long) b);

    // Display.
    gde_display_bmp ( (char *) b, 10, 450 );


    //
    // Mostrando informações sobre o arquivo.
    //

	//base do bmp carregado na memória
	//unsigned char *bmp = (unsigned char *) b;
	
	
	//@todo: encontrando o magic
	
	//if( bmp[0] != 0x42 )
	//{
	//	printf("~Sig fail\n");
	//    printf("magic0 %c\n", bmp[0]);	
	//    printf("magic1 %c\n", bmp[1]);			
	//	printf("buffer %x\n",bmp); //Ok
    //    printf("buffer %x\n",b);   //Ok
		//printf("width %d \n", bmp[0x12]);
		//printf("height %d \n", bmp[0x16]);
	//}
	
	//
	//Mostrando características do bmp.
	
	//printf("magic0 %c\n", bmp[0]);	
	//printf("magic1 %c\n", bmp[1]);
	//printf("data area begin %c %c %c \n",bmp[base] ,bmp[base+1] ,bmp[base+2]);	
	//printf("buffer %x \n",bmp);
	//printf("data area address %x \n",&bmp[base]);		
}


/*
 * bmpDisplayBMP:
 *     Mostra na tela uma imagem .bmp carregada na memória.
 *     #todo: No kernel ou na api tem rotina mais aprimorada que essa.
 */

// #bugbug
// Some param are not used.

void 
bmpDisplayBMP ( 
    void *address, 
    unsigned long x, 
    unsigned long y, 
    int width, 
    int height )
{
    if ( (void*) address == NULL )
    {
        return;
    }

    gde_display_bmp ( (char *) address, x, y ); 
}


// buttons
int shellTestButtons (void)
{
    unsigned long ScreenWidth  = gde_get_system_metrics(1);
    unsigned long ScreenHeight = gde_get_system_metrics(2);

	unsigned long app1Left = ((ScreenWidth/8) * 2);
	unsigned long app2Left = ((ScreenWidth/8) * 3);
	unsigned long app3Left = ((ScreenWidth/8) * 4);
	unsigned long app4Left = ((ScreenWidth/8) * 5);

	unsigned long app1Top = (ScreenHeight - ((ScreenHeight/16)*2) ); 
	unsigned long app2Top = app1Top; 
	unsigned long app3Top = app1Top; 
	unsigned long app4Top = app1Top;

    // botão de reboot
    // em shell.h está o ponteiro.
    app1_button = (void *) gde_create_window ( 
                               WT_BUTTON, 1, 1, "(CIMA)",
                               app1Left, app1Top, 80, 24, 
                               0, 0, COLOR_GREEN, COLOR_GREEN );
    gde_register_window (app1_button);

    // botão de close
    // em shell.h está o ponteiro.
    app2_button = (void *) gde_create_window ( 
                               WT_BUTTON, 1, 1, "(BAIXO)", 
                               app2Left, app2Top, 80, 24,
                               0, 0, COLOR_GREEN, COLOR_GREEN );
    gde_register_window (app2_button);


    // botão de close
    // em shell.h está o ponteiro.
    app3_button = (void *) gde_create_window ( 
                               WT_BUTTON, 1, 1, " APP3 ", 
                               app3Left, app3Top, 80, 24, 
                               0, 0, COLOR_GREEN, COLOR_GREEN );
    gde_register_window (app3_button);


    // botão de close
    // em shell.h está o ponteiro.
    app4_button = (void *) gde_create_window ( 
                               WT_BUTTON, 1, 1, " APP4 ", 
                               app4Left, app4Top, 80, 24,
                               0, 0, COLOR_GREEN, COLOR_GREEN );
    gde_register_window (app4_button);

    return 0;
}


