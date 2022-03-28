

#include <kernel.h>



void set_char_width ( int width )
{
    gcharWidth = (int) width;
}


void set_char_height (int height)
{
    gcharHeight = (int) height;
}


int get_char_width (void)
{
    return (int) gcharWidth;
}


int get_char_height (void)
{
    return (int) gcharHeight;
}


/*
 *****************************************************
 * d_draw_char:
 *     Constroi um caractere 8x8 no buffer.
 *     Desenha um caractere e pinta o pano de fundo.
 *     >> no backbuffer.
 */ 

void 
d_draw_char ( 
    unsigned long x, 
    unsigned long y, 
    unsigned long c,
    unsigned int fgcolor,
    unsigned int bgcolor )
{

    // loop
    register int y2=0;
    register int x2=0;

    // #todo: 
    // Rever isso.

    // The window.
    //struct window_d *hWindow;

    // The char.
    char *work_char; 

    // The mask.
    unsigned char bit_mask = 0x80;


    // #debug
    //debug_print ("d_draw_char:\n");

	//
	// Window Terminal.
	//


	/*
	if( VideoBlock.useGui == 1 )
	{
        //se existe um terminal.
		if( (void *) terminal != NULL )
        {
		    if( (void*) terminal->window != NULL )
			{
			    hWindow = (void*) terminal->window;
			
			    x = hWindow->left + x;
			    y = hWindow->top + y;
			};
		};
    };
	*/



	/*
	 * Get the font pointer.
	 *
	 * @todo:
	 *     usar variavel g8x8fontAddress.
	 *     + Criar e usar uma estrutura para fonte.
	 *     + Usar o ponteiro para a fonte atual que foi carregada.
	 *     + Criar um switch para o tamanho da fonte.
	 *     isso deveria estar na inicializa��o do m�dulo char.
	 *     ...
	 */


	// Default:
	//     Testando o uso de uma fonte default no caso de erro.
	//     Testando a troca da fonte padr�o.
	//     O sistema n�o vai parar no caso de erro. Nesse caso ele escolhera
	// um valor default.
	// Definido em: include/kernel/gramado/kservers/kgws/kgws/ws.h


    // Trying to use the ROM BIOS font 
    // if we do not have loadable one.

    if ( gws_currentfont_address == 0 ){
        gws_currentfont_address = (unsigned long) BIOSFONT8X8;
    }


    // 8x8
    if ( gcharWidth <= 0 || gcharHeight <= 0 )
    {
        gcharWidth  = DEFAULT_CHAR_WIDTH;
        gcharHeight = DEFAULT_CHAR_HEIGHT;
    }


    // Checking the font size.

    switch (gfontSize){

        case FONT8X8:
            //gws_currentfont_address = (unsigned long) BIOSFONT8X8;    //getFontAddress(...)
            //gcharWidth = 8;
            //gcharHeight = 8;
            set_char_width (8);
            set_char_height (8);
            break;


        case FONT8X16:
            //gws_currentfont_address = (unsigned long) BIOSFONT8X16;    //getFontAddress(...)
            //gcharWidth = 8;
            //gcharHeight = 16;
            set_char_width (8);
            set_char_height (16);
            break;


		// #todo: 
		// Criar op��es
		// ...


		// #importante:
		// #BUGBUG
		// Se n�o temos um tamanho selecionado ent�o teremos 
		// que usar o tamanho padr�o.

        // ROM bios.
        default:
            gws_currentfont_address = (unsigned long) BIOSFONT8X8; 
            set_char_width (8);
            set_char_height (8);
            gfontSize = FONT8X8;  //#todo: fu��o para configurar isso.
            break;
    };



	// tentando pintar um espa�o em branco.
	// Nas rotinas da biblioteca gr�fica, quando encontram
	// um espa�o(32), nem manda para c�, apenas incrementam o cursor.

	// #imporatante:
	// O caractere sendo trabalhado.
	// Offset da tabela de chars de altura 8 na ROM.

    work_char = (void *) gws_currentfont_address + (c * gcharHeight);


	// Draw.

    for ( y2=0; y2 < gcharHeight; y2++ )
    {
        bit_mask = 0x80;

        for ( x2=0; x2 < gcharWidth; x2++ )
        {
            backbuffer_putpixel ( 
                *work_char & bit_mask ? fgcolor: bgcolor,  // color
                (x + x2),                                  // x 
                y,                                         // y
                0 );                                       // rop_flags

            bit_mask = (bit_mask >> 1); 
        };

        // Next line of the char.
        y++; 
        work_char++; 
    };
}


/*
 ******************************************************
 * d_drawchar_transparent:
 *     Desenha um caractere sem alterar o pano de fundo.
 *     >> no backbuffer.
 */

void 
d_drawchar_transparent ( 
    unsigned long x, 
    unsigned long y, 
    unsigned int color, 
    unsigned long c )
{

    // loop
    register int y2=0;
    register int x2=0;

    // #todo: 
    // Rever isso.

    //struct window_d *hWindow;
    
    unsigned char bit_mask = 0x80;

    char *work_char;  



    // #debug
    // debug_print ("d_drawchar_transparent:\n");


	//
	// Window Terminal.
	//


	/*
	if( VideoBlock.useGui == 1 )
	{
        //se existe um terminal.
		if( (void *) terminal != NULL )
        {
		    if( (void*) terminal->window != NULL )
			{
			    hWindow = (void*) terminal->window;
			
			    x = hWindow->left + x;
			    y = hWindow->top + y;
			};
		};
    };
	*/



	/*
	 * @todo: 
	 *     +Criar vari�veis internas para tamanho de fonte.
	 *     +Pegar as informa��es em uma estrutura.
	 *     ...
	 */



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
	 *     isso deveria estar na inicializa��o do m�dulo char.
	 *     ...
	 */

	// Default:
	//     Testando o uso de uma fonte default no caso de erro.
	//     Testando a troca da fonte padr�o.
	//     O sistema n�o vai parar no caso de erro. Nesse caso ele escolhera
	// um valor default.
	// Definido em: include/kernel/gramado/kservers/kgws/kgws/ws.h


    // Trying to use the ROM BIOS font 
    // if we do not have loadable one.

    if ( gws_currentfont_address == 0 ){
        gws_currentfont_address = (unsigned long) BIOSFONT8X8;
    }

    // Selecting the default char properties.
    // #bugbug: Is it 'int' type?
    // 8x8
    if ( gcharWidth <= 0 || gcharHeight <= 0 )
    {
        gcharWidth  = DEFAULT_CHAR_WIDTH;
        gcharHeight = DEFAULT_CHAR_HEIGHT;
    }


    // Checking the font size.
    
    // #bugbug
    // Não precisamos configurar a fonte
    // toda vez que formos desenhar um char.

    switch (gfontSize){

        case FONT8X8:
            //gws_currentfont_address = (unsigned long) BIOSFONT8X8;    //getFontAddress(...)
            //gcharWidth = 8;
            //gcharHeight = 8;
            set_char_width (8);
            set_char_height (8);
            break;

        case FONT8X16:
            //gws_currentfont_address = (unsigned long) BIOSFONT8X16;    //getFontAddress(...)
            //gcharWidth = 8;
            //gcharHeight = 16;
            set_char_width (8);
            set_char_height (16);
            break;

		//#todo: 
		//Criar op��es
		//...

		// #importante:
		// #BUGBUG
		// Se n�o temos um tamanho selecionado ent�o teremos 
		// que usar o tamanho padr�o.

        ////ROM bios.
        default:
            gws_currentfont_address = (unsigned long) BIOSFONT8X8;    
            set_char_width (8);
            set_char_height (8);
            gfontSize = FONT8X8;  //#todo: fu��o para configurar isso.
            break;
    };


	// #importante:
	// O caractere sendo trabalhado.
	// Offset da tabela de chars de altura 8 na ROM.

    if ( gws_currentfont_address == 0 ){
        debug_print ("d_drawchar_transparent: [FAIL]gws_currentfont_address\n");
        return;
    }

    work_char = (void *) gws_currentfont_address + (c * gcharHeight);


//
// Draw
//

// See:
// drivers/video/fbdev/pixel.c

    for ( y2=0; y2 < gcharHeight; y2++ )
    {
        bit_mask = 0x80;

        for ( x2=0; x2 < gcharWidth; x2++ )
        {
            if ( ( *work_char & bit_mask ) )
            {
                backbuffer_putpixel ( 
                    color,     // color 
                    (x + x2),  // x
                    y,         // y
                    0 );       // rop_flags
            }
            // Next bit.
            bit_mask = (bit_mask >> 1); 
        };

        // Next line in the char.
        y++; 
        work_char++; 
    };

	// Algo mais ?
}

