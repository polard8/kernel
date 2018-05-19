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


#define Swap2Bytes(val) \
 ( (((val) >> 8) & 0x00FF) | (((val) << 8) & 0xFF00) )

 

// Swap 4 byte, 32 bit values:
#define Swap4Bytes(val) \
 ( (((val) >> 24) & 0x000000FF) | (((val) >>  8) & 0x0000FF00) | \
   (((val) <<  8) & 0x00FF0000) | (((val) << 24) & 0xFF000000) )


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
static int nibble_count_16colors = 0;
 
int bmpDisplayBMP( char *address, 
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
	// Endereço do início da paleta de 16 cores.
	// Endereço do início da paleta de 256 cores.
	unsigned char *bmp        = (unsigned char *)  address;
	//unsigned long *palette16  = (unsigned long *) (address + 0x36);
	//unsigned long *palette256 = (unsigned long *) (address + 0x36);
	unsigned long *palette    = (unsigned long *) (address + 0x36);		
	
	
	
	// Variável para salvar rgba.
	unsigned char *c   = (unsigned char *) &color;	
	unsigned char *xCh   = (unsigned char *) &color2;	
	
	
	
	//
	// Limits
	//
	
	xLimit = 800;
	yLimit = 600;
	
	
	//@todo: Refazer isso
	if( x > xLimit || y > yLimit ){ 
        return (int) 1; 
	}
	

	
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
	
	
	// 0 = Nenhuma compressão.
	if(bi->bmpCompression != 0 )
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
	
	//#importante:
	//a base é diferente para os tipos.
	 

	switch(bi->bmpBitCount)
    {
		//case 1:
		//    base = (0x36 + 0x40);
		//    break;
		    
		//case 2:
		//    base = (0x36 + 0x40);
		//    break;
			
		case 4:
		    //4bytes pra cada cor, 16 cores, 64bytes.
		    base = (0x36 + 0x40);
		    break; 
			
		case 8:
		    //4bytes pra cada cor, 256 cores, 1024bytes.
		    base = (0x36 + 0x400);
		    break; 
			
		default:
		    base = 0x36;
			break;
	}	
	

//1 - 1 bpp (Mono)
//4 - 4 bpp (Indexed)
//8 - 8 bpp (Indexed) bbgggrrr
//16565 - 16 bpp (5:6:5, RGB Hi color)
//16    - 16 bpp (5:5:5:1, RGB Hi color)
//160   - 16 bpp (5:5:5:1, RGBA Hi color)
//24 - 24 bpp (True color)
//32 - 32 bpp (True color, RGB)
//320 - 32 bpp (True color, RGBA)	


    //
	// ## ABGR8888 ##
	// Little-endian
	// pegando os caracteres
	//
	// 0 = A (MSByte)(left byte) 
	// 1 = B 
	// 2 = G 
	// 3 = R
	//
	// Output long = 0xRRGGBBAA
    //	
	// Exemplo: gramado GUI
    //#define COLOR_RED   0xFF000000 
    //#define COLOR_GREEN 0x00FF0000
    //#define COLOR_BLUE  0x0000FF00

    char palette_index[2];	
	
	for( i=0; i < bi->bmpHeight; i++ )	
	{
		//#bugbug: 
		//Precisa ser o valor encontrado na estrutura +1.
		
		for( j=0; j < bi->bmpWidth; j++ )	
		{	
	        // 16 cores
			// Construindo o char.
			// um nibble por índice. @todo
	        if(bi->bmpBitCount == 4 )
	        {				
				offset = base;
							    
				palette_index[0] = bmp[offset];
												
                //segundo nibble.
				if( nibble_count_16colors == 2222 )
				{
					palette_index[0] = ( palette_index[0] & 0x0F); 
				    color = (unsigned long) cga_16colors_palette[  palette_index[0]  ];
					//color = (unsigned long) palette[  palette_index[0]  ];
					nibble_count_16colors = 0;
					base = base + 1;
					
				//primeiro nibble.	
				}else{

			        palette_index[0] =  ( (  palette_index[0] >> 4 ) & 0x0F);
					color = (unsigned long) cga_16colors_palette[  palette_index[0] ];
					//color = (unsigned long) palette[  palette_index[0] ];
				    nibble_count_16colors = 2222;
					base = base;
				}
	        };	

			// 256 cores
			// Próximo pixel para 8bpp
	        if(bi->bmpBitCount == 8 )
	        {   
				offset = base;
							    
				palette_index[0] = (char) bmp[offset];
				
				color = (unsigned long) vga_256colors_palette[ palette_index[0] ];
				
				base = base + 1;     
	        };			
			
			// Próximo pixel para 16bpp
			//565 ou 4444 ou 5551
			//testando apenas 4444
	        if(bi->bmpBitCount == 16 )
	        {
				offset = base;
				
				
				//A
			    c[0] = 0;	

			    //b				
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
		        
				base = base + 2;    
	        };			
			
			// Próximo pixel para 24bpp
	        if(bi->bmpBitCount == 24 )
	        {
			    //
				offset = base;
			    
				
				//A
			    c[0] = 0;					
				
				c[1] = bmp[offset];
			    
				//
			    offset = base+1;
			    c[2] = bmp[offset];
			
			    //
			    offset = base+2;
			    c[3] = bmp[offset];
										
		        base = base + 3;    
	        };
			
			
			// Próximo pixel para 32bpp
	        if(bi->bmpBitCount == 32 )
	        {
			    
			    
				//A
				//offset = base+3;
			    c[0] = 0;				
				
				offset = base;
			    c[1] = bmp[offset];
			
			    offset = base+1;
			    c[2] = bmp[offset];
			
			    offset = base+2;
			    c[3] = bmp[offset];
				
		        base = base + 4;    
	        };
			
			
		    //Swap4Bytes(color);
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
	
	// ## test palette 
	//int p;
	
	//printf("\n");
	//for( p=0; p<16; ++p )
	//{
	//	printf("%x\n",palette[p]);
	//}
	//printf("\n");
	
fail:	
    //printf("fail");	
done:	
	//Debug
	//printf("w={%d} h={%d}\n", bi->bmpWidth, bi->bmpHeight );
	return (int) 0;
};


 



/*
int bmpInit()
{}
*/

//
// End.
//

