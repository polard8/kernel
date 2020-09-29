/*
 * File: char.c 
 * 
 *     gws - Char support.
 * 
 * History:
 *     2019 - Created by Fred Nora.
 *     2020 -
 */


#include <gws.h>


// #todo
// Draw char.
// Service 1004.
int serviceDrawChar(void)
{

    //O buffer é uma global nesse documento.
    unsigned long *message_address = (unsigned long *) &__buffer[0];


    struct gws_window_d *window;
    int window_id = -1;
    unsigned long x=0;
    unsigned long y=0;
    unsigned long color=0;
    
    int __char=0;

    // #todo
    char *text_buffer; 


    // #debug
    gwssrv_debug_print ("serviceDrawChar: \n");


    // Get
    
    
    window_id = message_address[4];
    x         = message_address[5];
    y         = message_address[6]; 
    color     = message_address[7];
    unsigned long C = (unsigned long) message_address[8];
    //text_buffer =    //#todo
   
    //lets create a fake string.
    unsigned char _string[4];
   
   _string[0] = (unsigned char) C;
   _string[1] = (unsigned char) 0;
   
    
    //
    // Window ID
    //
   
    // Limits
    if ( window_id < 0 || window_id >= WINDOW_COUNT_MAX ){
        gwssrv_debug_print ("gwssrv: serviceDrawChar window_id\n");
        return -1;
    }

    //gwssrv_debug_print ("serviceDrawChar: get window pointer\n");
    
    //#todo
    // Get the window structure given the id.
    window = (struct gws_window_d *) windowList[window_id];

    // #bugbug
    // O ponteiro eh nao nulo, mas esta numa regiao invalida.
    // why??
    
    //gwssrv_debug_print ("serviceDrawChar: [debug] cheching pointer validation\n");
    //printf ("[debug] window id      = %d \n",window_id);
    //printf ("[debug] window pointer = %x *hang\n",window);
    //while(1){}
    
    
    
    
    if ( (void *) window == NULL ){
        gwssrv_debug_print ("gwssrv: serviceDrawChar window\n");
        return -1;
    }

    //gwssrv_debug_print ("serviceDrawChar: pointer not null\n");
    
    if ( window->used != 1 || window->magic != 1234 ){
        gwssrv_debug_print ("gwssrv: serviceDrawChar validation\n");
        return -1;
    }
    
    //
    // Draw
    //
    
    gwssrv_debug_print ("serviceDrawChar: Draw !!!\n");
    
    // Ok it is working
    dtextDrawText ( (struct gws_window_d *) window,
        x, y, color, (unsigned char *) &_string[0] );
    
    //#test
    //It is working
    // Usando a janela screen por enquanto.
    //dtextDrawText ( (struct gws_window_d *) gui->screen,
        //x, y, color, (unsigned char *) &_string[0] );

    //It is working
    //charBackbufferDrawcharTransparent ( x, y, color, C );
    
    //
    // Refresh
    //  
        
    //gws_show_backbuffer ();       // for debug   
    //gws_show_window_rect(window);   // something faster for now.
    //something faster.

    // x,y,w,h
    gws_refresh_rectangle ( (window->left +x), (window->top +y), 8, 8 );

    gwssrv_debug_print ("gwssrv: serviceDrawChar done\n");

    return 0;
}






int gwssrv_init_char(void)
{

    //char
    gcharWidth  = 8;   //gde_get_system_metrics (7);
    gcharHeight = 8;   //gde_get_system_metrics (8);

    //...
    
    return 0;
}


// Constrói um caractere transparente 8x8 no buffer.
void 
charBackbufferCharBlt ( 
    unsigned long x, 
    unsigned long y, 
    unsigned long color, 
    unsigned long c )
{
    charBackbufferDrawcharTransparent ( x, y, color, c );
}



void charSetCharWidth ( int width )
{
    gcharWidth = (int) width;
}


void charSetCharHeight ( int height )
{
    gcharHeight = (int) height;
}


int charGetCharWidth (void)
{
    return (int) gcharWidth;
}


int charGetCharHeight (void)
{
    return (int) gcharHeight;
}


/*
 ******************************************************
 * gws_drawchar_transparent:
 *     Desenha um caractere sem alterar o pano de fundo.
 *     >> no backbuffer.
 */

// #bugbug
// Nessa função estamos usando globais.
// Talvez devamos pegá-las antes e não 
// referenciá-las diretamente.

void 
charBackbufferDrawcharTransparent ( 
    unsigned long x, 
    unsigned long y, 
    unsigned long color, 
    unsigned long c )
{

    char *work_char;
    unsigned char bit_mask = 0x80;

    int x2=0;
    int y2=0;

    //int CharWidth;
    //int CharHeight;


    /*
	 * Get the font pointer.
	 *
	 * @todo:
     *     usar variavel g8x8fontAddress.
	 *     + Criar e usar uma estrutura para fonte.
	 *     + Usar o ponteiro para a fonte atual que foi carregada.
	 *     + Criar um switch para o tamanho da fonte.
	 *     isso deveria estar na inicialização do módulo char.
	 *     ...
	 */

    if ( gws_currentfont_address == 0 || 
         gcharWidth <= 0 || 
         gcharHeight <= 0 )
    {
	    //gws_currentfont_address = (unsigned long) BIOSFONT8X8;    //ROM bios.
		//gcharWidth = DEFAULT_CHAR_WIDTH;               //8.
		//gcharHeight = DEFAULT_CHAR_HEIGHT;             //8.
		
		// #debug
		// Estamos parando para testes.
		
        printf ("gws_drawchar_transparent : Initialization fail\n");
        while(1){}
    }

    // #todo: 
    // Criar essas variáveis e definições.

    switch (gfontSize){

		//case FONT8X8:
	        //gws_currentfont_address = (unsigned long) BIOSFONT8X8;    //getFontAddress(...)
		    //gcharWidth = 8;
		    //gcharHeight = 8;
		    //set_char_width(8);
			//set_char_height(8);
			//break;
		
		//case FONT8X16:
	        //gws_currentfont_address = (unsigned long) BIOSFONT8X16;    //getFontAddress(...)
		    //gcharWidth = 8;
		    //gcharHeight = 16;
		    //set_char_width(8);
			//set_char_height(16);			
		    //break;
		 
		//#todo: 
		//Criar opções
		//...
		
		// #importante:
		// #BUGBUG
		// Se não temos um tamanho selecionado então teremos 
		// que usar o tamanho padrão.
		
        default:
		    //gws_currentfont_address = (unsigned long) BIOSFONT8X8;    //ROM bios.
		    
			//set_char_width(8);
			//set_char_height(8);	
            //gfontSize = FONT8X8;  //#todo: fução para configurar isso.

            break;
    };


    // O caractere sendo trabalhado.

    work_char = (void *) gws_currentfont_address + (c * gcharHeight);


    //
    // Draw.
    //

    for ( y2=0; y2 < gcharHeight; y2++ )
    {
        bit_mask = 0x80;

        for ( x2=0; x2 < gcharWidth; x2++ )
        {

           // Put pixel. 
            if ( ( *work_char & bit_mask ) ){ 
                pixelBackBufferPutpixel ( color, x + x2, y );  
            }

            // Rotate bitmask.
            bit_mask = (bit_mask >> 1);  
        };

        // Próxima linha da 8 linhas do caractere.
        y++; 
        work_char++; 
    };
}


/*
 *****************************************************
 * charBackbufferDrawchar:
 *     Constrói um caractere no buffer.
 *     Desenha um caractere e pinta o pano de fundo.
 */ 

void 
charBackbufferDrawchar ( 
    unsigned long x, 
    unsigned long y,  
    unsigned long c,
    unsigned long fgcolor,
    unsigned long bgcolor )
{

    char *work_char; 
    unsigned char bit_mask = 0x80;

    int x2=0;
    int y2=0;


    /*
     * Get the font pointer.
     *
     * @todo:
     *     usar variavel g8x8fontAddress.	 
     *     + Criar e usar uma estrutura para fonte.
     *     + Usar o ponteiro para a fonte atual que foi carregada.
     *     + Criar um switch para o tamanho da fonte.
     *     isso deveria estar na inicialização do módulo char.
     *     ...
     */
 
    if ( gws_currentfont_address == 0 ||  
         gcharWidth <= 0 || 
         gcharHeight <= 0 )
    {
        //gws_currentfont_address = (unsigned long) BIOSFONT8X8;    //ROM bios.
        //gcharWidth = DEFAULT_CHAR_WIDTH;               //8.
        //gcharHeight = DEFAULT_CHAR_HEIGHT;             //8.

		//#debug
		//Estamos parando só para testes.
		
        printf ("gws_draw_char: initialization fail\n");
        while(1){}
    }

    //todo: 
    //Criar essas variáveis e definições.

    switch (gfontSize){
		
		//case FONT8X8:
	        //gws_currentfont_address = (unsigned long) BIOSFONT8X8;    //getFontAddress(...)
		    //gcharWidth = 8;
		    //gcharHeight = 8;
		    //set_char_width(8);
			//set_char_height(8);
			//break;
		
		//case FONT8X16:
	        //gws_currentfont_address = (unsigned long) BIOSFONT8X16;    //getFontAddress(...)
		    //gcharWidth = 8;
		    //gcharHeight = 16;
		    //set_char_width(8);
			//set_char_height(16);
		    //break;
		 
		//#todo: 
		//Criar opções
		//...
		
		// #importante:
		// #BUGBUG
		// Se não temos um tamanho selecionado então teremos 
		// que usar o tamanho padrão.

        default:
		    //gws_currentfont_address = (unsigned long) BIOSFONT8X8;    //ROM bios.
		    //set_char_width(8);
			//set_char_height(8);	
            //gfontSize = FONT8X8;  //#todo: fução para configurar isso.			
            break;
    };

	//tentando pintar um espaço em branco.
    //Nas rotinas da biblioteca gráfica, quando encontram
	//um espaço(32), nem manda para cá, apenas incrementam o cursor.

	// O caractere sendo trabalhado.
	// Offset da tabela de chars de altura 8 na ROM.

    work_char = (void *) gws_currentfont_address + (c * gcharHeight);

    //
    // Draw.
    //

    for ( y2=0; y2 < gcharHeight; y2++ )
    {
        bit_mask = 0x80;

        for ( x2=0; x2 < gcharWidth; x2++ )
        {

			// Put pixel.
			// A cor varia de acordo com a mascara de bit.
            pixelBackBufferPutpixel ( *work_char & bit_mask ? fgcolor: bgcolor, 
                x + x2, y );

            bit_mask = (bit_mask >> 1); 
        };

        // Próxima linha da (y) linhas do caractere.
        y++; 
        work_char++; 
    };
}


//
// End.
//

