/*
 * File: gramado\gui\char.c
 *
 * Descrição:
 *     Constrói caractere em modo gráfico.
 *     Desenha o caractere pixel por pixel.
 *     Faz parte do módulo Window Manager do tipo MB.
 * Obs: A fonte usada é a fonte 8x8 que está na ROM BIOS. em 0x000FFA6E.
 *
 * History:
 *     2015 - Created by Fred Nora.
 *     2018 - Revision.
 *
 */

 
#include <kernel.h>


//
// @todo: Criar uma estrutura para o char. entre os elementos
// pode ter os buffer para o char. backbuffer, frontbuffer, dedicatedbuffer.
//
//



/*
 ********************************************************
 * my_buffer_char_blt:
 *     Constrói um caractere transparente 8x8 no buffer.
 */
//void charBuiltCharBackBuffer( unsigned long x, unsigned long y, unsigned long color, unsigned long c)
void my_buffer_char_blt( unsigned long x, 
                         unsigned long y, 
						 unsigned long color, 
						 unsigned long c)
{
    drawchar_transparent( x, y, color, c );								
};


void set_char_width( int width ){
	gcharWidth = (int) width;
	return;
}

void set_char_height( int height ){
	gcharHeight = (int) height;
	return;
}

int get_char_width(){
	return (int) gcharWidth;
}


int get_char_height(){
	return (int) gcharHeight;
}


/*
 ******************************************************
 * drawchar_transparent:
 *     Desenha um caractere sem alterar o pano de fundo.
 */						   
void drawchar_transparent( unsigned long x, 
                           unsigned long y, 
						   unsigned long color, 
						   unsigned long c)
{	
	int x2;
    int y2;
    unsigned char bit_mask = 0x80;	
    char *work_char;  
    struct window_d *hWindow;			
	  
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
	 *     +Criar variáveis internas para tamanho de fonte.
	 *     +Pegar as informações em uma estrutura.
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
	 *     isso deveria estar na inicialização do módulo char.
	 *     ...
	 */
	 
    if( gws_currentfont_address == 0 || 
	      gcharWidth <= 0 || 
		 gcharHeight <= 0 )
	{
	    gws_currentfont_address = (unsigned long) BIOSFONT8X8;    //ROM bios.
		gcharWidth = DEFAULT_CHAR_WIDTH;               //8.
		gcharHeight = DEFAULT_CHAR_HEIGHT;             //8.
		
		//debug
		printf("drawchar_transparent: address fail\n");
		die();
	};
	

	//@todo: Criar essas variáveis e definições.
	switch(gfontSize)
	{
		case FONT8X8:
	        //gws_currentfont_address = (unsigned long) BIOSFONT8X8;    //getFontAddress(...)
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
		// Se não temos um tamanho selecionado então teremos 
		// que usar o tamanho padrão.
		//
		default:
		   // printf("gui-char-drawchar_transparent: Font size fail.");
		//	printf("gui-char-drawchar_transparent: Using default ...");
	        
			// Fonte padrão.
		//	gws_currentfont_address = (unsigned long) BIOSFONT8X8;    //ROM bios.
		  //  gcharWidth = DEFAULT_CHAR_WIDTH;               //8.
		   // gcharHeight = DEFAULT_CHAR_HEIGHT;             //8.	
            
            //gfontStatus = 0;  //fail 			
		    
			break;
	};
	

 	//
	// O caractere sendo trabalhado.
	// Offset da tabela de chars de altura 8 na ROM.	
    //
	
	work_char = (void *) gws_currentfont_address + (c * gcharHeight);

	//
	// Draw.
	//
	
    for( y2 = 0; y2 < gcharHeight; y2++ )
    {
        bit_mask = 0x80;

        for( x2 = 0; x2 < gcharWidth; x2++ )
        {
			//
			// @todo: o nome dessa rotina de putpixel será mudado.
			//
			
            if( (*work_char & bit_mask) )
                my_buffer_put_pixel(color, x + x2, y, 0);  //Put pixel.
                bit_mask = (bit_mask >> 1);                //Rotate bitmask.
        };
		
		y++;            //Próxima linha da 8 linhas do caractere.
		work_char++;   
	};
	
	//
	// Algo mais ?
	//
	
	

done:
    return;  	         	   
};

				
/*
 *****************************************************
 * draw_char:
 *     Constrói um caractere 8x8 no buffer.
 *     Desenha um caractere e pinta o pano de fundo.
 */
void draw_char( unsigned long x, 
                unsigned long y,  
				unsigned long c,
				unsigned long fgcolor,
				unsigned long bgcolor)
{	
	int x2;
    int y2;
    unsigned char bit_mask = 0x80;	
    char *work_char;  
    struct window_d *hWindow;			
	  
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
	 *     +Criar variáveis internas para tamanho de fonte.
	 *     +Pegar as informações em uma estrutura.
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
	 *     isso deveria estar na inicialização do módulo char.
	 *     ...
	 */
	 
    if( gws_currentfont_address == 0 || 
	      gcharWidth <= 0 || 
		 gcharHeight <= 0 )
	{
	    gws_currentfont_address = (unsigned long) BIOSFONT8X8;    //ROM bios.
		gcharWidth = DEFAULT_CHAR_WIDTH;               //8.
		gcharHeight = DEFAULT_CHAR_HEIGHT;             //8.
		//debug
		printf("draw_char: address fail\n");
		die();
	};
	
    //@todo: Criar essas variáveis e definições.
	switch(gfontSize)
	{
		case FONT8X8:
	        //gws_currentfont_address = (unsigned long) BIOSFONT8X8;    //getFontAddress(...)
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
		// Se não temos um tamanho selecionado então teremos 
		// que usar o tamanho padrão.
		//
		//default:
		//    printf("gui-char-drawchar_transparent: Font size fail.");
		//	printf("gui-char-drawchar_transparent: Using default ...");
	        
			// Fonte padrão.
		//	gws_currentfont_address = (unsigned long) BIOSFONT8X8;    //ROM bios.
		//    gcharWidth = DEFAULT_CHAR_WIDTH;               //8.
		//    gcharHeight = DEFAULT_CHAR_HEIGHT;             //8.	
            
            //gfontStatus = 0;  //fail 			
		    
		//	break;
	};
	
	
	//tentando pintar um espaço em branco.
    //Nas rotinas da biblioteca gráfica, quando encontram
	//um espaço(32), nem manda para cá, apenas incrementam o cursor.
	
	

 	//
	// O caractere sendo trabalhado.
	// Offset da tabela de chars de altura 8 na ROM.	
    //
	
	work_char = (void *) gws_currentfont_address + (c * gcharHeight);

	//
	// Draw.
	//
	
    for( y2 = 0; y2 < gcharHeight; y2++ )
    {
        bit_mask = 0x80;

        for( x2 = 0; x2 < gcharWidth; x2++ )
        {
			//
			// @todo: o nome dessa rotina de putpixel será mudado.
			//
			
			//putpixel( glyph[cy] & mask[cx] ? fgcolor: bgcolor, x+cx, y+cy-12 );
			
			//Put pixel.
			my_buffer_put_pixel( *work_char & bit_mask ? fgcolor: bgcolor, 
			                     x + x2, 
								 y, 
								 0 );
            bit_mask = (bit_mask >> 1); 								 
			
            //if( (*work_char & bit_mask) )
            //    my_buffer_put_pixel(color, x + x2, y, 0);  //Put pixel.
            //    bit_mask = (bit_mask >> 1);                //Rotate bitmask.
        };
		
		y++;            //Próxima linha da 8 linhas do caractere.
		work_char++;   
	};
	
	//
	// Algo mais ?
	//
	
	

done:
    return;  	         	   
};



/*
int charInit()
{
	
    if( gws_currentfont_address == 0 || 
	      gcharWidth == 0 || 
		 gcharHeight == 0 )
	{
		//@todo: Criar definições globais para esses valores, ou estruturas.
	    gws_currentfont_address = (unsigned long) BIOSFONT8X8;    //ROM bios.
		gcharWidth = 8;
		gcharHeight = 8;
	};
	
	//@todo: Criar essas variáveis e definições.
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
		// Se não temos um tamanho selecionado então teremos 
		// que usar o tamanho padrão.
		//
		default:
		    printf("gui-char-drawchar_transparent: Font size fail.");
			printf("gui-char-drawchar_transparent: Using default ...");
	        
			// Fonte padrão.
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

