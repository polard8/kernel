


#include <kernel.h>


extern unsigned long SavedX;
extern unsigned long SavedY;
extern unsigned long SavedBPP;


unsigned long screen_width; 
unsigned long screen_height;


// Get width.
unsigned long screenGetWidth (void)
{
    return (unsigned long) screen_width;
}

// Get height. 
unsigned long screenGetHeight (void)
{
    return (unsigned long) screen_height;
}

// screenSetSize:
//     Configura as dimensões da tela.
//     Tamanho do monitor.

void screenSetSize( unsigned long width, unsigned long height )
{
    screen_width  = (unsigned long) width; 
    screen_height = (unsigned long) height;
}


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

void refresh_screen (void)
{
    int i=0;

    // #bugbug
    // #danger
    // Dependendo do tamanho da tela, 
    // essa rotina pode acabar copiando conteúdo 
    // para alguma parte não mapeada no lfb.
    // Precisamos de limites. Obedecendo a quantidade mapeada.

    //unsigned long *backbuffer  = (unsigned long *) BACKBUFFER_VA;
    //unsigned long *frontbuffer = (unsigned long *) FRONTBUFFER_VA;

    // #bugbug
    // Como temos apenas 2MB de lfb mapeados, 
    // então vamos copiar menos dados pra evitar ultrapassar o limite
    // e causar PF.
    unsigned char *backbuffer  = (unsigned char *) BACKBUFFER_VA;
    unsigned char *frontbuffer = (unsigned char *) FRONTBUFFER_VA;


    debug_print_string("refresh_screen:\n");

    vsync();

    if ( SavedX == 0 || SavedY == 0 || SavedBPP == 0 )
    {
        debug_print_string("refresh_screen: [FAIL] validation\n");
        return;
    }


    if ( refresh_screen_flag != TRUE )
    {
        debug_print_string("refresh_screen: [FAIL-FIXME] refresh_screen_flag\n");
        return;
    }


    //int Total = (int)(SavedX*SavedBPP*SavedY);
    
    int Total = (screen_size_in_kb * 1024);

    // #todo
    // Isso significa que só poderemos 
    // usar o modo 320x200 por enquanto.
    
    // clipping:
    // Podemos recortar, e mesmo que a resoluçao seja alta,
    // somente escreveremos nos primeiros 2mb ...
    // Isso seria divertido, a velocidade seria alta,
    // mas teriamos uma tela recortada. kkk
    // Essa tecnica pode ser uma opçao configuravel

    if ( Total >= (2*1024*1024) )
    {
        debug_print_string("refresh_screen: [FAIL-FIXME] Total\n");
        return;
    }

    for ( i=0; i< Total; i++ )
    {
        frontbuffer[i] = backbuffer[i];
    };
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
        panic ("screenInit:\n");
    }else{
        Screen->used  = TRUE;
        Screen->magic = 1234;
        Screen->id = 0;
        Screen->left = SCREEN_DEFAULT_LEFT;
        Screen->top  = SCREEN_DEFAULT_TOP; 
        Screen->width  = (unsigned long) screenGetWidth();
        Screen->height = (unsigned long) screenGetHeight();
        Screen->next   = NULL;
        // ...
 
        // salvando o ponteiro da estrutura. 
        ScreenInfo    = (void *) Screen;
        CurrentScreen = (void *) Screen;
        //...
    };

    // ?

    return 0;
}









