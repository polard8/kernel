/*
 * File: windows/char.c
 *
 *     Constroi caractere em modo gr�fico.
 *     Desenha o caractere pixel por pixel.
 *     Faz parte do m�dulo Window Manager do tipo MB.
 * 
 * Obs: 
 * A fonte usada � a fonte 8x8 que est� na ROM BIOS. em 0x000FFA6E.
 *
 * History:
 *     2015 - Created by Fred Nora.
 *     2018 - Revision.
 */


#include <kernel.h>


// @todo: Criar uma estrutura para o char. entre os elementos
// pode ter os buffer para o char. backbuffer, frontbuffer, dedicatedbuffer.



/*
 ********************************************************
 * my_buffer_char_blt:
 *     Constr�i um caractere transparente 8x8 no buffer.
 */
 
void 
my_buffer_char_blt ( 
    unsigned long x, 
    unsigned long y, 
    unsigned long color, 
    unsigned long c )
{
    d_drawchar_transparent ( x, y, color, c );
}


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
 ******************************************************
 * d_drawchar_transparent:
 *     Desenha um caractere sem alterar o pano de fundo.
 *     >> no backbuffer.
 */

void 
d_drawchar_transparent ( 
    unsigned long x, 
    unsigned long y, 
    unsigned long color, 
    unsigned long c )
{

    // #todo: 
    // Rever isso.

    struct window_d *hWindow;

    int x2=0;
    int y2=0;

    unsigned char bit_mask = 0x80;

    char *work_char;  

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
            if ( ( *work_char & bit_mask ) )
            { 
                backbuffer_putpixel ( color, x + x2, y, 0 ); 
            }

            // Rotate bitmask.
            bit_mask = (bit_mask >> 1); 
        };

        // Next line in the char.
        y++; 
        work_char++; 
    };

	// Algo mais ?
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
    unsigned long fgcolor,
    unsigned long bgcolor )
{

    // #todo: 
    // Rever isso.

    // The window.
    struct window_d *hWindow;

    // The char.
    char *work_char; 

    // The mask.
    unsigned char bit_mask = 0x80;

    // The position.
    int x2=0;
    int y2=0;


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

            // Put pixel.
            backbuffer_putpixel ( *work_char & bit_mask ? fgcolor: bgcolor, 
                x + x2, y, 0 );

            bit_mask = (bit_mask >> 1); 
        };

        // Next line of the char.
        y++; 
        work_char++; 
    };

	// Algo mais ? 
}


/*
int charInit()
{
	
    if( gws_currentfont_address == 0 || 
	      gcharWidth == 0 || 
		 gcharHeight == 0 )
	{
		//@todo: Criar defini��es globais para esses valores, ou estruturas.
	    gws_currentfont_address = (unsigned long) BIOSFONT8X8;    //ROM bios.
		gcharWidth = 8;
		gcharHeight = 8;
	};
	
	//@todo: Criar essas vari�veis e defini��es.
	switch(gfontSize)
	{
		case FONT8X8:
	        gws_currentfont_address = (unsigned long) BIOSFONT8X8;    //getFontAddress(...)
		    gcharWidth = 8;
		    gcharHeight = 8;
		    break;
		
		//case FONT8X16:
	    //    gws_currentfont_address = (unsigned long) BIOSFONT8X16;    //getFontAddress(...)
		//    gcharWidth = 8;
		//    gcharHeight = 16;
		//    break;
		 
		//...
		
		//
		// #importante:
		// #BUGBUG
		// Se n�o temos um tamanho selecionado ent�o teremos 
		// que usar o tamanho padr�o.
		//
		default:
		    printf("gui-char-drawchar_transparent: Font size fail.");
			printf("gui-char-drawchar_transparent: Using default ...");
	        
			// Fonte padr�o.
			gws_currentfont_address = (unsigned long) BIOSFONT8X8;    //ROM bios.
		    gcharWidth = DEFAULT_CHAR_WIDTH;               //8.
		    gcharHeight = DEFAULT_CHAR_HEIGHT;             //8.	
            
            //gfontStatus = 0;  //fail 
		    
			break;
	};

}
*/


//
// End.
//

