/*
 * File: dev/tty/vt/draw/view/bg.c 
 *
 * 
 * Descrição:
 *     Rotinas de configuração do background de um desktop.
 *     O background de um desktop é onde fica a imagem de pano de fundo.
 * Também é conhecido como Backbuffer.
 *
 * Window server.
 *
 * History:
 *     2013 - Created by Fred Nora.
 */


#include <kernel.h>



// Herdadas do Boot Loader.
// De onde vem isso ?? head.s
// #todo: 
// Devemos chamar o módulo hal para obtermos esses valores.
// depois salvamos em variáveis internas usadas pela gui.

extern unsigned long SavedBootBlock;
extern unsigned long SavedLFB;
extern unsigned long SavedX;
extern unsigned long SavedY;
extern unsigned long SavedBPP; 


// Load and show bg bmp.
void bg_load_image (void)
{

    int status = -1;
    
    char __path[] = "/BOOT/ANIMAL.BMP";
        
    // 512*4096 = 2MB
    unsigned long tmp_size = (512*4096);
    void *__buffer = (void *) allocPages ( 512 );

    debug_print("bg_load_image: \n");
    
    
    if ( (void*) __buffer == NULL ){
        debug_print("bg_load_image: __buffer\n");
        return;
    }


    // # not tested.
    // See: fs.c
    // IN: path os two levels, address.
    status = (int) fs_load_path ( 
                       (const char*)   __path, 
                       (unsigned long) __buffer,
                       (unsigned long) tmp_size );
  
    if (status < 0)
    {
        // Load from root dir.
        
        // See: read.c
        status = (int) fsLoadFile ( 
                           VOLUME1_FAT_ADDRESS, 
                           VOLUME1_ROOTDIR_ADDRESS, 
                           FAT16_ROOT_ENTRIES, //#bugbug: Number of entries.
                           "ANIMAL  BMP", 
                           (unsigned long) __buffer,
                           tmp_size );
        
        if (status != 0){
            debug_print ("bg_load_image: fail\n");
            return;
        }
    }

    // A imagem foi carregada no buffer.
    // Vamos exibir na tela em 0,0.

    // #bugbug: 
    // A imagem sai cortada do lado direito.

    bmpDisplayBMP ( (char *) __buffer, 0, 0 );  
}
 
 
/*
 ******************************
 * backgroundDraw:
 *     Draw device screen in graphics mode.
 *     Clear the screen in text mode.
 *     #todo get device info.
 */

// #atenção: rotina sensível.

void backgroundDraw (unsigned long color)
{

    //loop
    register unsigned long i=0;


    if (VideoBlock.useGui != 1){
        debug_print ("backgroundDraw: No GUI\n");
        return;
    }

    for ( i=0; i<SavedY; i++ ){
        my_buffer_horizontal_line ( 0, i, SavedX, color );
    };
    
    // Cursor.
    // Nao funciona
    set_up_cursor(0,0);
}


/* 
 * backgroundSetColor:
 *     Set background color in graphics mode. 
 */

void backgroundSetColor (unsigned long color)
{
    //#cancelada	
}


/*
 * backgroundRedraw:
 *     Redraw bg. 
 */

void backgroundRedraw (unsigned long color)
{
    // #bugbug
    // gui structure validation

    if ( (void *) gui == NULL ){ return; };

    if ( gui->backgroundStatus == 0 ){ return; };

    if ( (void *) gui->background != NULL )
    {
        backgroundDraw(color);
    }
}


// Constructor.
// #bugbug: The validation of this index.

void backgroundBackground (void)
{
    CONSOLE_TTYS[fg_console].cursor_x = 0;
    CONSOLE_TTYS[fg_console].cursor_y = 0; 
}


// Initialize background.
// Not good

int backgroundInit (void){

    //loop
    register int i=0;
    
    unsigned long *lfb = (unsigned long *) BACKBUFFER_VA;


    // #bugbug:
    // We need to get w and h if the function is available.
    //debug_print ("backgroundInit: FIXME: w and h\n");

    //#bugbug
    for ( i=0; i< 800*600; i++ )
    {
        lfb[i] = COLOR_BLACK;
    }

    backgroundBackground ();

	//...

    return 0; 
}

// Called by kernel_main().
int Background_initialize(void)
{

    // Clear the screen.
    // print some basic info.

    // obs:
    // Nesse momento o bl deixou a tela suja.
    // Entao as mensagens nessa fase da inicializaçao
    // sao apresentadas em cima da sujeira deixada pelo boot loader.
    // #test:
    // Se possivel vamos limpara a tela agora. Pois ja inicializamos
    // a runtime.
    // #bugbug: slow.

    //printf ("XXX\n");
    //refresh_screen();
    //while(1){}
    
    backgroundDraw ( (unsigned long) COLOR_BLACK );

    // Cursor.
    // Nao funciona
    // set_up_cursor(0,4);

    // #debug
    // Breakpoint
    // This is used to debug.
    // Show info and hang.


    //
    // The first char!
    //
   
    // This is the first char ever for 
    // the new background.

    printf ("$\n");


    // ========================================
    
    printf ("Background_initialize: [DEBUG] Show bootblock info\n");
    printf ("Boot block pa %x\n",SavedBootBlock); 
    printf ("lfb %x\n",BootBlock.lfb);
    printf ("x   %d\n",BootBlock.x);
    printf ("y   %d\n",BootBlock.y);
    printf ("bpp %d\n",BootBlock.bpp);
    printf (">>>  Gramado mode %d\n", BootBlock.gramado_mode);
    
    //
    // Refresh
    //

    refresh_screen();
    //while(1){}

    return 0;
}


//
// End.
//

