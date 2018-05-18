/*
 * File: gui\bmp.c
 *
 * Descrição:
 *     Rotinas para bmp.
 *     Faz parte do módulo Window Manager do tipo MB.
 *
 * Obs: 
 *     As rotinas de bmp precisam melhorar.
 *     Conferir os parametros do bmp em seu header.
 *     todo: Criar uma rotina para filtrar o bmp por tamanho e tipo.
 *            bugbug: bmp envolve o carregamento de arquivo.
 *            Temos a opção de utilizarmos arquivos que foram carregados
 * na inicialização, como parte dos elementos da interface gráfica.
 * 
 * History: 
 *     2015 - Created by Fred Nora. 
 */


#include <kernel.h>



/*
 ********************************************************
 * bmpDisplayBMP:
 *
 * Mostra na tela uma imagem bmp carregada na memória.
 * 
 * IN:
 *     address = endereço base
 *     x       = posicionamento 
 *     y       = posicionamento
 *
 *	// @todo: Criar defines para esses deslocamentos.
 */
void bmpDisplayBMP( char *address, 
                    unsigned long x, 
					unsigned long y )
{
	int i, j, base, offset;
	
	unsigned long left, top, bottom;
	
	unsigned long color;
	unsigned long color2;
	
	unsigned long Width;
	unsigned long Height;
	
	unsigned long xLimit, yLimit;
	
	struct bmp_header_d *bh;
	struct bmp_infoheader_d *bi;
	
	
	// Endereço base do BMP que foi carregado na memória
	unsigned char *bmp = (unsigned char *) address;
	
	// Variável para salvar rgba.
	unsigned char *c   = (unsigned char *) &color;	
	unsigned char *xCh   = (unsigned char *) &color2;	
	
	//
	// Limits
	//
	
	xLimit = 800;
	yLimit = 600;
	
	
	//@todo: Refazer isso
	if( x > xLimit )
	{ 
        return; 
	};
	
	if( y > yLimit )
	{ 
        return; 
	};

	
	//
	// @todo:
	// Testar validade do endereço.
	//
	
	
	if( address == 0 )
	{
		//goto fail;
	};
	
	
	//
	// struct for Info header
	//
	
	bh = (struct bmp_header_d *) malloc( sizeof(struct bmp_header_d) );
	
    if( (void*) bh == NULL )
	{
		//goto fail;
	}	
	

	//
	// Signature.
	//
	
    unsigned short sig;
	
	sig = *( unsigned short* ) &bmp[0];
	
	bh->bmpType = sig;
	
	
	//
	// Size. ( 2 bytes )
	//
	
	unsigned short Size = *( unsigned short* ) &bmp[2];
	
	bh->bmpSize = Size;
	
	
	//
	// struct for Info header
	//
	
	//Windows bmp.
	bi = (struct bmp_infoheader_d *) malloc( sizeof(struct bmp_infoheader_d) );
	
    if( (void*) bi == NULL )
	{
		//goto fail;
	}	
	
	//The size of this header.
	bi->bmpSize = *( unsigned long* ) &bmp[14];
	
	// Width and height.
    Width = *( unsigned long* ) &bmp[18];
    Height = *( unsigned long* ) &bmp[22];	
	
	//@todo: checar validade da altura e da largura encontrada.
	
	// Salvar.
	bi->bmpWidth = (unsigned long) Width;
	bi->bmpHeight = (unsigned long) Height;
	
	
	/* Number of bits per pixel */
	//1, 4, 8, 16, 24 and 32.
	bi->bmpBitCount = *( unsigned short* ) &bmp[28];
	
	// Único suportado ainda.
	if(bi->bmpBitCount != 24 )
	{
		//fail
	}
	
	
	//
	// Draw !
	//
	
	
	
	left = x;    //
	top  = y; 
	
	
	//bottom = top + height;
	bottom = (top + bi->bmpHeight );

	// Início da área de dados do BMP.
	base = 0x36; 


//1 - 1 bpp (Mono)
//4 - 4 bpp (Indexed)
//8 - 8 bpp (Indexed)
//16565 - 16 bpp (5:6:5, RGB Hi color)
//16    - 16 bpp (5:5:5:1, RGB Hi color)
//160   - 16 bpp (5:5:5:1, RGBA Hi color)
//24 - 24 bpp (True color)
//32 - 32 bpp (True color, RGB)
//320 - 32 bpp (True color, RGBA)	
	
	for( i=0; i < bi->bmpHeight; i++ )	
	{
		//#bugbug: 
		//Precisa ser o valor encontrado na estrutura +1.
		
		for( j=0; j < bi->bmpWidth; j++ )	
		{	
			// Construindo o char.
			

			// Próximo pixel para 8bpp
	        if(bi->bmpBitCount == 8 )
	        {
			    
				offset = base;
			    
		        //b 1100 0000
				c[1] = bmp[offset];
				c[1] = ( c[1] & 0xE0 );
			    
				//g 0011 1000
			    c[2] = bmp[offset];
				c[2] =  (c[2] & 0x3C) ;
			
			    //r 0000 0111
			    c[3] = bmp[offset];
				c[3] =  (c[3] & 0x07);
			
			    //??
			    c[0] = 0;
				
		        
				base = base + 1;    
	        };			
			
			// Próximo pixel para 16bpp
			//565 ou 4444 ou 5551
			//testando apenas 4444
	        if(bi->bmpBitCount == 16 )
	        {
			
			    //b
				offset = base;
			    c[1] = bmp[offset];
			    c[1] =  (c[1] & 0xF8);  // 1111 1000  
				
				//g
			    //offset = base+1;
			    //c[2] = bmp[offset];
			    c[2] = bmp[offset];
			    c[2] = c[2] &  0x1F;  // 0000 0111 
				
			    //r
			    offset = base+1;
			    c[3] = bmp[offset];
			    c[3] = c[3] & 0xFF;  // 0001 1111 
				
			    //??
			    c[0] = 0;											
		        
				base = base + 2;    
	        };			
			
			// Próximo pixel para 24bpp
	        if(bi->bmpBitCount == 24 )
	        {
			    //
				offset = base;
			    c[1] = bmp[offset];
			    
				//
			    offset = base+1;
			    c[2] = bmp[offset];
			
			    //
			    offset = base+2;
			    c[3] = bmp[offset];
			
			    //??
			    c[0] = 0;								
		        base = base + 3;    
	        };
			
			
			// Próximo pixel para 32bpp
	        if(bi->bmpBitCount == 32 )
	        {
			    offset = base;
			    c[1] = bmp[offset];
			
			    offset = base+1;
			    c[2] = bmp[offset];
			
			    offset = base+2;
			    c[3] = bmp[offset];
			
			    offset = base+3;
			    c[0] = bmp[offset];
				
		        base = base + 4;    
	        };
			
			
		
			my_buffer_put_pixel( (unsigned long) color, 
			                     (unsigned long) left, 
								 (unsigned long) bottom, 
								 0 );
			
			// Próximo pixel.
			left++; 
		};
		
		
		// Vamos para a linha anterior.
		bottom = bottom-1;
		
		// Reiniciamos o x.
		left = x;    
	};	
	
	
	
fail:	
    //printf("fail");	
done:	
	//Debug
	printf("w={%d} h={%d}\n", bi->bmpWidth, bi->bmpHeight );
	return;
};


 



/*
int bmpInit()
{}
*/

//
// End.
//

