/*
 * File: unb\screen.c
 *
 * Descrição: 
 *     Parametros de tela e monitor de video. 
 *     (hardware stuff). 
 *
 * History:
 *     2015 - Created by Fred Nora.
 */
 
 
#include <kernel.h>


//
// Variáveis importadas.
//

//Passadas pelo Boot Loader.
extern unsigned long SavedBootMode;
extern unsigned long SavedX;            //Screen width. 
extern unsigned long SavedY;            //Screen height.
//...

//
// Funções importadas.
//

extern void asm_refresh_screen();


//
// Variáveis internas.
//

//int screenStatus;
//int screenError;
//int screenWidth;
//int screenHeight;
//...


/*
 * Screen Size:
 *     Tamanho da tela, do monitor de video.
 *      //@todo: se estamos encapsulando no módulo, retirar o G de global.
 *
 *    @todo: Essas variáveis não devem ser globais. Devem ser dados acessíveis 
 * somente por métodos presents no módulo screen.c.
 *
 */
//unsigned long g_screen_width; 
//unsigned long g_screen_height;
unsigned long screen_width; 
unsigned long screen_height;



//Get width.
unsigned long screenGetWidth()
{
	return (unsigned long) screen_width;
};
 
//Get height. 
unsigned long screenGetHeight()
{
	return (unsigned long) screen_height;	
};


/*
 * screenSetSize:
 *     Configura as dimensões da tela.
 *     Tamanho do monitor.
 */
void screenSetSize( unsigned long width, unsigned long height )
{
    screen_width = (unsigned long) width; 
    screen_height = (unsigned long) height;
    //return;
};


/*
 * refresh_screen:
 *     Coloca o conteúdo do BackBuffer no LFB da memória de vídeo.
 */

void refresh_screen (){
	
	unsigned long *backbuffer = (unsigned long *) BACKBUFFER_VA;
	unsigned long *frontbuffer = (unsigned long *) FRONTBUFFER_VA;
	
	int i=0;
	
	 vsync ();	
	
	//#test velocidade?
	for ( i=0; i< SavedX*SavedY; i++ )
		frontbuffer[i] = backbuffer[i];	
	
    //antigo.
	//isso funciona.
	//screenRefresh();

	//teste
	//isso funciona.
    //refresh_rectangle ( 0, 0, SavedX, SavedY );
}


/*
 *****************************************
 * screenRefresh:
 *     Coloca o conteúdo do BackBuffer no LFB da memória de vídeo.
 *     Se o modo de vídeo permite.
 */
void screenRefresh()
{
    //?? SavedBootMode	
    if( g_useGUI == 1 || SavedBootMode == 1 )
	    asm_refresh_screen();
};


/*
 **********************************************
 * screenInit:
 *     Inicializando o gerenciamento de tela.
 */ 

int screenInit (){
	
    //Configura globais com base nos valores passados pelo Boot Loader.
	
	screenSetSize ( (unsigned long) SavedX, (unsigned long) SavedY );
	
	// Setup Screen structure.
	
    Screen = (void *) malloc( sizeof(struct screen_d) );
    
	if ( (void *) Screen == NULL )
	{	
	    panic ("screenInit:");
		
	}else{
		
	    Screen->left = SCREEN_DEFAULT_LEFT;
	    Screen->top = SCREEN_DEFAULT_TOP; 
		
		Screen->width = (unsigned long) screenGetWidth();
	    Screen->height = (unsigned long) screenGetHeight();
		//...
         
		// salvando o ponteiro da estrutura. 
        ScreenInfo = (void *) Screen;
        CurrentScreen = (void *) Screen;
        //...		
    };
	
	// More?!
	
//done:
	
//#ifdef KERNEL_VERBOSE
//    printf("done\n");
//#endif
	
	return (int) 0;
};


/*
 *Constructor.
int screenScreen()
{};
*/


//
// End.
//

