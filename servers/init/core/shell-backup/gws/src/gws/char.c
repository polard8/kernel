
#include <api.h>
#include <gws.h>




/*
 ********************************************************
 * my_buffer_char_blt:
 *     Constrói um caractere transparente 8x8 no buffer.
 */

//void charBuiltCharBackBuffer( unsigned long x, unsigned long y, unsigned long color, unsigned long c)

void my_buffer_char_blt ( unsigned long x, 
                          unsigned long y, 
						  unsigned long color, 
						  unsigned long c )
{
    gws_drawchar_transparent ( x, y, color, c );								
}


void set_char_width ( int width ){
	
	gcharWidth = (int) width;
}


void set_char_height ( int height ){
	
	gcharHeight = (int) height;
}


int get_char_width (){
	
	return (int) gcharWidth;
};


int get_char_height (){
	
	return (int) gcharHeight;
};


/*
 ******************************************************
 * drawchar_transparent:
 *     Desenha um caractere sem alterar o pano de fundo.
 */		

void 
gws_drawchar_transparent ( unsigned long x, 
                           unsigned long y, 
                           unsigned long color, 
                           unsigned long c )
{	
    int x2;
    int y2;

    unsigned char bit_mask = 0x80;	
    
	char *work_char;  
 
	//struct window_d *hWindow;			

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
	 
    if ( gws_currentfont_address == 0 || 
	     gcharWidth <= 0 || 
		 gcharHeight <= 0 )
	{
	    //gws_currentfont_address = (unsigned long) BIOSFONT8X8;    //ROM bios.
		//gcharWidth = DEFAULT_CHAR_WIDTH;               //8.
		//gcharHeight = DEFAULT_CHAR_HEIGHT;             //8.
		
		// #debug
		// Estamos parando para testes.
		
		printf("gws_drawchar_transparent : Initialization fail\n");
		while(1){}
	};
	

	//@todo: 
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
	

	// O caractere sendo trabalhado.
	// Offset da tabela de chars de altura 8 na ROM.	
	
	 work_char = (void *) gws_currentfont_address + (c * gcharHeight);
	 // work_char = (void *) gws_currentfont_address + (c * 8);

	//
	// Draw.
	//
	
    for ( y2=0; y2 < gcharHeight; y2++ )
    {
        bit_mask = 0x80;

        for ( x2=0; x2 < gcharWidth; x2++ )
        {			
	        //Put pixel. 
            if ( ( *work_char & bit_mask ) )
			{ 
                gws_backbuffer_putpixel ( color, x + x2, y );  				
			}
            
			//Rotate bitmask.
			bit_mask = (bit_mask >> 1);                
        };
		
		y++;            //Próxima linha da 8 linhas do caractere.
		work_char++;   
	};
	
	// Algo mais ?        	   
}


/*
 *****************************************************
 * draw_char:
 *     Constrói um caractere 8x8 no buffer.
 *     Desenha um caractere e pinta o pano de fundo.
 */ 

void 
gws_draw_char ( unsigned long x, 
                unsigned long y,  
                unsigned long c,
                unsigned long fgcolor,
                unsigned long bgcolor )
{	
	int x2;
    int y2;
	
    unsigned char bit_mask = 0x80;	
    
	char *work_char;  
    
	//struct window_d *hWindow;

	  
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
		
		printf("gws_draw_char: initialization fail\n");
		while(1){}
	};
	
    //@todo: 
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
				
			//Put pixel.				
			gws_backbuffer_putpixel ( *work_char & bit_mask ? fgcolor: bgcolor, 
			    x + x2, y );
				
			
            bit_mask = (bit_mask >> 1); 								 
        };
		
		//Próxima linha da (y) linhas do caractere.
		y++;            
		work_char++;   
	};
	
	// Algo mais ?       	   
}



