/*
 * File: gramado\gui\char.c
 *
 * Descrição:
 *     Constrói caractere em modo gráfico.
 *     Desenha o caractere pixel por pixel.
 *     Faz parte do módulo Window Manager do tipo MB.
 * Obs: A fonte usada é a fonte 8x8 que está na ROM BIOS. em 0x000FFA6E.
 *
 * Versão 1.0, 2015.
 */

 
#include <kernel.h>


//
// @todo: Criar uma estrutura para o char. entre os elementos
// pode ter os buffer para o char. backbuffer, frontbuffer, dedicatedbuffer.
//
//


//
// charDirectCharBuilt: 
//     Desenha um caractere diretamente no frontbuffer.
//     Obs: Requer sincronização vertical.
//     Obs: A sincronização é feita antes de desenha o caractere e não
// a cada pixel enviado.
//
//void charDirectCharBuilt( void* FrontBuffer, unsigned long x, unsigned long y, unsigned long color, unsigned long c);
//void charDirectCharBuilt( void* FrontBuffer, unsigned long x, unsigned long y, unsigned long color, unsigned long c)
//{
//    return; //Ainda não implementada.	
//}


/*
 * my_buffer_char_blt:
 *     Constrói um caractere 8x8 no buffer.
 */
//void charBuiltCharBackBuffer( unsigned long x, unsigned long y, unsigned long color, unsigned long c)
void my_buffer_char_blt( unsigned long x, 
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
	 
    if( gfontAddress == 0 || 
	      gcharWidth <= 0 || 
		 gcharHeight <= 0 )
	{
	    gfontAddress = (unsigned long) BIOSFONT8X8;    //ROM bios.
		gcharWidth = DEFAULT_CHAR_WIDTH;               //8.
		gcharHeight = DEFAULT_CHAR_HEIGHT;             //8.
	};
	
	/*
	//@todo: Criar essas variáveis e definições.
	switch(gFontSize)
	{
		case FONT8X8:
	    gfontAddress = (unsigned long) BIOSFONT8X8;    //getFontAddress(...)
		gcharWidth = 8;
		gcharHeight = 8;
		break;
		
		case FONT8X16:
	    gfontAddress = (unsigned long) BIOSFONT8X16;    //getFontAddress(...)
		gcharWidth = 8;
		gcharHeight = 16;
		break;
		 
		//...
	}
	*/
	
	

 	//
	// O caractere sendo trabalhado.
	// Offset da tabela de chars de altura 8 na ROM.	
    //
	
	work_char = (void *) gfontAddress + (c * gcharHeight);

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
int charInit()
{
	
    if( gfontAddress == 0 || 
	      gcharWidth == 0 || 
		 gcharHeight == 0 )
	{
		//@todo: Criar definições globais para esses valores, ou estruturas.
	    gfontAddress = (unsigned long) BIOSFONT8X8;    //ROM bios.
		gcharWidth = 8;
		gcharHeight = 8;
	};
	
	//@todo: Criar essas variáveis e definições.
	switch(gFontSize)
	{
		case FONT8X8:
	    gfontAddress = (unsigned long) BIOSFONT8X8;    //getFontAddress(...)
		gcharWidth = 8;
		gcharHeight = 8;
		break;
		
		case FONT8X16:
	    gfontAddress = (unsigned long) BIOSFONT8X16;    //getFontAddress(...)
		gcharWidth = 8;
		gcharHeight = 16;
		break;
		 
		//...
	}

}
*/


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

//
//fim
//

