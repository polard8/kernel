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
extern unsigned long SavedBPP;
//...

//
// Funções importadas.
//

extern void asm_refresh_screen (void);


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
unsigned long screenGetWidth (void)
{
	return (unsigned long) screen_width;
}
 

//Get height. 
unsigned long screenGetHeight (void)
{
	return (unsigned long) screen_height;	
}


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
 *********************************************************
 * refresh_screen:
 *     Coloca o conteúdo do BackBuffer no LFB da memória de vídeo.
 *     Ok, isso está no lugar certo. Pois somente
 *  O driver de vídeo pode acessar o LFB
 *  /x/video/screen.c 
 */

// backup.
// This is working very well.
// Copying long by long. 
// Total size is wrong.
// Esse é mais rápido.
void refresh_screen (void){

    int i=0;

    unsigned long *backbuffer  = (unsigned long *) BACKBUFFER_VA;
    unsigned long *frontbuffer = (unsigned long *) FRONTBUFFER_VA;


    vsync();

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



// #todo
// Testing this routine.
// Copying byte by byte.
/*
void refresh_screen(void){

    unsigned char *backbuffer = (unsigned char *) BACKBUFFER_VA;
    unsigned char *frontbuffer = (unsigned char *) FRONTBUFFER_VA;

    unsigned long i=0;
    unsigned long total=0; 

    total = (unsigned long) (SavedY * SavedX * (SavedBPP/8) ); 

    for ( i=0; i< total; i++ )
        frontbuffer[i] = backbuffer[i];
}
*/

// Copia para o lfb o conteúdo de uma backbuffer qualquer.
/*
void refresh_screen2 (unsigned long backbuffer_address)
void refresh_screen2 (unsigned long backbuffer_address){
	
	unsigned long *backbuffer = (unsigned long *) backbuffer_address;
	unsigned long *frontbuffer = (unsigned long *) FRONTBUFFER_VA;
	
	int i=0;
	
	 vsync ();	
	
	//#test velocidade?
	for ( i=0; i< SavedX*SavedY; i++ )
		frontbuffer[i] = backbuffer[i];	
}
*/


/*
 *****************************************
 * screenRefresh:
 *     Coloca o conteúdo do BackBuffer no LFB da memória de vídeo.
 *     Se o modo de vídeo permite.
 */
 
// #bugbug
// Que rotina é essa ?
 
void screenRefresh (void)
{
	//refresh_screen();
	
    //?? SavedBootMode	
    if( g_useGUI == 1 || SavedBootMode == 1 )
	    asm_refresh_screen();
}


/*
 **********************************************
 * screenInit:
 *     Inicializando o gerenciamento de tela.
 */ 

// #bugbug
// Screen is a reagion in the display, or in many displays.
// Display is a monitor, or a set o hid in a given host.

int screenInit (void){


    debug_print ("screenInit:\n");

    // Configura globais com base nos valores passados pelo Boot Loader.

    screenSetSize ( (unsigned long) SavedX, (unsigned long) SavedY );

    // Setup Screen structure.
    // See: screen.h
    
    Screen = (void *) kmalloc ( sizeof(struct screen_d) );
    
    if ( (void *) Screen == NULL ){
        panic ("screenInit:");
        
    }else{

        Screen->used = 1;
        Screen->magic = 1234;
        
        Screen->id = 0;
         
        Screen->left = SCREEN_DEFAULT_LEFT;
        Screen->top  = SCREEN_DEFAULT_TOP; 
        Screen->width  = (unsigned long) screenGetWidth();
        Screen->height = (unsigned long) screenGetHeight();
        
        
        Screen->next = NULL;
        //...
 
        // salvando o ponteiro da estrutura. 
        ScreenInfo    = (void *) Screen;
        CurrentScreen = (void *) Screen;
        //...
    };



	// More?!
	
//done:
	
//#ifdef KERNEL_VERBOSE
//    printf("done\n");
//#endif


    return 0;
}



/*
 *Constructor.
int screenScreen()
{};
*/


//
// End.
//

