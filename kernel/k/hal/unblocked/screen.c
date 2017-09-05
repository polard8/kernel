/*
 * File: screen.c
 *
 * Descrição: 
 *     Parametros de tela e monitor de video.. 
 *     (hardware stuffs..).
 *
 * Versão 1.0, 2015.
 */
 
 
#include <kernel.h>


//
// Variáveis importadas.
//

extern unsigned long SavedBootMode;
extern unsigned long SavedX;            //Screen width. 
extern unsigned long SavedY;            //Screen height.


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
 *    @todo: esssas variáveis naão devem ser globais, devem ser encapsuladas
 * no módulo. screen.c
 */
unsigned long g_screen_width; 
unsigned long g_screen_height;


//Get width.
unsigned long screenGetWidth()
{
	return (unsigned long) g_screen_width;
};
 
//Get height. 
unsigned long screenGetHeight()
{
	return (unsigned long) g_screen_height;	
};


/*
 * refresh_screen:
 *     Coloca o conteúdo do BackBuffer no LFB da memória de vídeo.
 */
void refresh_screen()
{
    screenRefresh();
	return;
};


/*
 * screenRefresh:
 *     Coloca o conteúdo do BackBuffer no LFB da memória de vídeo.
 */
void screenRefresh()
{
	//
	// @todo: Essa rotina pode ser escrita em assembly,
	//        aqui mesmo. 
	//
	
	//Se o modo de vídeo permite.
    if(g_useGUI == 1 || SavedBootMode == 1){
        asm_refresh_screen();
    };	
	return;	
};


/*
 * screenSetSize:
 *     Configura as dimensões da tela.
 *     Tamanho do monitor.
 */
void screenSetSize(unsigned long width, unsigned long height)
{
    g_screen_width  = (unsigned long) width; 
    g_screen_height = (unsigned long) height;
    return;
};


/*
 * screenInit:
 *     Inicializando o gerenciamento de tela.
 */ 
int screenInit()
{
	
	//
	// Configura globais com base nos valores passados pelo Boot Loader.
	//
	
	//printf("Set up\n");
	screenSetSize( (unsigned long) SavedX, (unsigned long) SavedY);
	
	
	//
	// Setup Screen structure.
	//
	
    Screen = (void*) malloc( sizeof(struct screen_d) );
    if((void*) Screen == NULL)
	{	
	    printf("init_screen:");
		refresh_screen();
		while(1){}
	}
	else
	{
		
	    Screen->left = SCREEN_DEFAULT_LEFT;
	    Screen->top  = SCREEN_DEFAULT_TOP;
	    
		
		//printf("gets\n");
		Screen->width  = (unsigned long) screenGetWidth();
	    Screen->height = (unsigned long) screenGetHeight();

		//printf("Structs\n");
        ScreenInfo    = (void*) Screen;
        CurrentScreen = (void*) Screen;
        //...		
    };
	
	//More?!
	
done:
    printf("done\n");
	return (int) 0;
};


/*
 *Constructor.
int screenScreen()
{};
*/


//
// Fim.
//

