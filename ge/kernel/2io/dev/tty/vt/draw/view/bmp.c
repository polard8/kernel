/*
 * File: ui/windows/view/bmp.c
 *
 * Description:
 *     BMP file support.
 *     We can use this to display a boot splash image.
 *
 * Obs: 
 *     As rotinas de bmp precisam melhorar.
 *     Conferir os parametros do bmp em seu header.
 * todo: 
 * Criar uma rotina para filtrar o bmp por tamanho e tipo.
 * 
 * bugbug: 
 * bmp envolve o carregamento de arquivo.
 * Temos a opção de utilizarmos arquivos que foram carregados
 * na inicialização, como parte dos elementos da interface gráfica.
 *
 * History: 
 *     2015 - Created by Fred Nora. 
 *            24 bpp support.
 *     2018 - Display 4bpp, 8bpp, and 32bpp BMPs.
 */


#include <kernel.h>


// Screen width and height. 
// Herdadas do bootloader.

extern unsigned long SavedX;
extern unsigned long SavedY;


// 4bpp support.
static int nibble_count_16colors = 0;



// #todo 
// kgws não pode acessar o lfb, devemos chamar o diálogo em x/video.c


/*
 **********************************
 * bmpDirectDisplayBMP:
 *
 *     Decodifica uma imagem BM que já está carregada na memória. 
 *    ( Pinta diretamente no LFB )
 * 
 * IN:
 *     address = endereço base
 *     x       = posicionamento 
 *     y       = posicionamento
 *
 * 
 *  #todo: 
 *  Criar defines para esses deslocamentos.
 */


int 
bmpDirectDisplayBMP ( 
    char *address,
    unsigned long x,
    unsigned long y )
{

    int i=0; 
    int j=0; 
    int base=0; 
    int offset=0;

    unsigned long left=0;
    unsigned long top=0; 
    unsigned long bottom=0;

    unsigned long Width=0; 
    unsigned long Height=0;
    unsigned long xLimit=0;
    unsigned long yLimit=0;

    unsigned short Sig=0;
    unsigned short Size=0;

    unsigned long color=0; 
    unsigned long color2=0;

    unsigned long pal_address=0;

    // Structures.

    struct bmp_header_d      *bh;
    struct bmp_infoheader_d  *bi;



    // Endereço base do BMP que foi carregado na memória.
    unsigned char *bmp = (unsigned char *) address;


    // Variável para salvar rgba.
    unsigned char *c  = (unsigned char *) &color;
    unsigned char *c2 = (unsigned char *) &color2;


    unsigned long *palette       = (unsigned long *) (address + 0x36);
    unsigned char *palette_index = (unsigned char *) &pal_address;


    // Device limits.
    
    xLimit = SavedX;
    yLimit = SavedY;


    // Sincronização do retraço vertical.
    // Suspenso.
    // vsync();


    // Limits.

    if ( x > xLimit || y > yLimit ){
        printf ("bmpDirectDisplayBMP: Limits \n");
        goto fail;
    }


    // #todo:
    // Testar validade do endereço.

    if ( address == 0 ){
        printf ("bmpDirectDisplayBMP: address \n");
        goto fail;
    }


    //
    // == struct for Info header ===================================
    //

    // #bugbug
    // Um kmalloc aqui pode esgotar o heap na hora de movimentar o mouse.
    // Pois ainda nao temos um kfree() que funcione.
    // Precisamos usar um buffer interno para essa estrutura.
    char buffer[512];

    //bh = (struct bmp_header_d *) kmalloc( sizeof(struct bmp_header_d) );
    bh = (struct bmp_header_d *) &buffer[0];

    if ( (void *) bh == NULL ){
        debug_print ("bmpDirectDisplayBMP: bh \n");
        goto fail;
    }

    //
    // Get data from the header.
    //


    // Signature.
    Sig = *( unsigned short * ) &bmp[0];
    bh->bmpType = Sig;


    // Size. ( 2 bytes )
    Size = *( unsigned short * ) &bmp[2];
    bh->bmpSize = Size;



    //
    // == struct for Info header ===============================
    //

    // #bugbug
    // Um kmalloc aqui pode esgotar o heap na hora de movimentar o mouse.
    // Pois ainda nao temos um kfree() que funcione.
    // Precisamos usar um buffer interno para essa estrutura.
    char buffer2[512];

    //bi = (struct bmp_infoheader_d *) kmalloc( sizeof(struct bmp_infoheader_d) );
    bi = (struct bmp_infoheader_d *)  &buffer2[0];

    if ( (void *) bi == NULL ){
        debug_print ("bmpDirectDisplayBMP: bi \n");
        goto fail;
    }

    //
    // Get data from the info header.
    //


    // The size of this header.
    bi->bmpSize = *(unsigned long *) &bmp[14];


    // Width and height.
    // #todo: 
    // Checar validade da altura e da largura encontrada.

    Width  = *(unsigned long *) &bmp[18];
    Height = *(unsigned long *) &bmp[22];

    // Salvar.
    bi->bmpWidth  = (unsigned long) Width;
    bi->bmpHeight = (unsigned long) Height;


    // Number of bits per pixel.
    // 1, 4, 8, 16, 24 and 32.
    bi->bmpBitCount = *( unsigned short * ) &bmp[28];


    // Compression support.
    // 0 = Nenhuma compressão.
    // ...
    if ( bi->bmpCompression != 0 ){
        debug_print ("bmpDirectDisplayBMP: [FAIL] Compression NOT supported\n");
        //goto fail;
    }

//
// == Draw ======================================================
//


    left = x;
    top  = y; 
    bottom = ( top + bi->bmpHeight );


    //
    // The data area.
    //


    // #importante:
    // A base é diferente para os tipos ?? 

//#Aprendendo:
//1     -  1 bpp (Mono)
//4     -  4 bpp (Indexed)
//8     -  8 bpp (Indexed) bbgggrrr
//16565 - 16 bpp (5:6:5, RGB Hi color)
//16    - 16 bpp (5:5:5:1, RGB Hi color)
//160   - 16 bpp (5:5:5:1, RGBA Hi color)
//24    - 24 bpp (True color)
//32    - 32 bpp (True color, RGB)
//320   - 32 bpp (True color, RGBA)	


    // Obs: 
    // Cada cor é representada com 4 bytes. RGBA.

    switch ( bi->bmpBitCount ){


        //case 1:  base = (0x36 + 0x40);  break;
        //case 2:  base = (0x36 + 0x40);  break;

        // 4 bytes pra cada cor, 16 cores, 64 bytes.
        case 4:  base = (0x36 + 0x40);  break; 

        //4 bytes pra cada cor, 256 cores, 1024bytes.
        case 8:   base = (0x36 + 0x400);  break; 

        default:
            debug_print ("bmpDirectDisplayBMP: [FAIL] Default bit count\n");
            base = 0x36;
            break;
    };

    // Draw!

    for ( i=0; i < bi->bmpHeight; i++ )
    {
        for ( j=0; j < bi->bmpWidth; j++ )
        {
            // 16 cores
            // Um pixel por nibble.
            if ( bi->bmpBitCount == 4 )
            {
                offset = base;

                palette_index[0] = bmp[offset];

                // Segundo nibble.
				if( nibble_count_16colors == 2222 )
				{
					palette_index[0] = ( palette_index[0] & 0x0F );  
					color = (unsigned long) palette[  palette_index[0]  ];
					
					nibble_count_16colors = 0;
					base = base + 1;
					
				// Primeiro nibble.	
				}else{

			        palette_index[0] = ( (  palette_index[0] >> 4 ) & 0x0F );
					color = (unsigned long) palette[  palette_index[0] ];
				    
					nibble_count_16colors = 2222;
					//base = base;
                };
            };

            // 256 cores
            // Próximo pixel para 8bpp
            if ( bi->bmpBitCount == 8 )
            {
                offset = base;
                color = (unsigned long) palette[  bmp[offset] ];
                base = (base + 1); 
            };


            // Próximo pixel para 16bpp
            if ( bi->bmpBitCount == 16 )
            {
				//a
				c[0] = 0; 
				
				offset = base;

				//b
			    c[1] = bmp[offset];
			    c[1] = (c[1] & 0xF8);      // '1111 1000' 0000 0000  

				//g
			    c2[0] = bmp[offset];
			    c2[0] = c2[0] &  0x07;     // '0000 0111' 0000 0000 
			    c2[1] = bmp[offset+1];
			    c2[1] = c2[1] &  0xE0;     //  0000 0000 '1110 0000' 
				c[2] = ( c2[0] | c2[1] );  

			    //r
			    c[3] = bmp[offset+1];
			    c[3] = c[3] & 0x1F;        // 0000 0000 '0001 1111' 

                base = (base + 2);
            };


            // Próximo pixel para 24bpp.
            if ( bi->bmpBitCount == 24 )
            {  
                c[0] = 0;  // A

				offset = base;
				c[1] = bmp[offset];
			    
			    offset = base+1;
			    c[2] = bmp[offset];

			    offset = base+2;
			    c[3] = bmp[offset];

                base = (base + 3);
            };


            // Próximo pixel para 32bpp.
            if ( bi->bmpBitCount == 32 )
            {
                c[0] = 0;  // A

				offset = base;
			    c[1] = bmp[offset];
			
			    offset = base+1;
			    c[2] = bmp[offset];
			
			    offset = base+2;
			    c[3] = bmp[offset];

                base = (base + 4);
            };

			//
			// # Put pixel #
			//

			//Nesse momento já temos a cor selecionada 
			//no formato 0xaarrggbb ... 
			//Agora se a flag de mascara estiver selecionada,
			//então devemos ignora o pixel e não pintá-lo.	

            switch (bmp_change_color_flag)
            {
				//1000
				//flag para ignorarmos a cor selecionada.
				//Não pinte nada.
				//Devemos pintar caso a cor atual seja  
				//diferente da cor selecionada.
                case BMP_CHANGE_COLOR_TRANSPARENT:
                    if ( color != bmp_selected_color )
                    {
                        lfb_putpixel ( (unsigned long) color, 
                            (unsigned long) left, (unsigned long) bottom, 0 );
                    }
                    break;

				//2000
				//Substitua pela cor indicada.
				//Se a cor atual é igual a cor selecionada,
				//devemos substituir a cor atual pela substituta.
				//Mas se a cor atual for diferente da cor selecionada,
				//pintamos normalmente a cor atual.
				case BMP_CHANGE_COLOR_SUBSTITUTE:
				    if ( color == bmp_selected_color )
					{	 
						lfb_putpixel ( (unsigned long) bmp_substitute_color, 
			                (unsigned long) left, (unsigned long) bottom, 0 );
							 
                    }else{
                        lfb_putpixel ( (unsigned long) color, 
                            (unsigned long) left, (unsigned long) bottom, 0 );
                    }; 
                    break;

				// ...

                // 0 and default
                // Pintamos normalmente a cor atual.
                case BMP_CHANGE_COLOR_NULL:
                default:
                    lfb_putpixel ( (unsigned long) color, 
                        (unsigned long) left, (unsigned long) bottom, 0 );
                     break;
            };

			// Próximo pixel.
            left++; 
        };

        // Vamos para a linha anterior.
        bottom = (bottom-1);

        // Reiniciamos o x.
        left = x;    
    };


	// ## test palette 
	//int p;
	
	//if(bi->bmpBitCount == 8 )
	//{
	//    printf("\n");
	//    for( p=0; p<16; ++p )
	//    {
	//	   printf("%x\n",palette[p]);
	//    }
	//    printf("\n");
	//};



done:
	//Debug
	//printf("w={%d} h={%d}\n", bi->bmpWidth, bi->bmpHeight );
    return 0;

fail:	
    //printf("fail");	
    return (int) 1;
    //return (int) -1;
}


/*
 ***********************************
 * bmpDisplayBMP:
 *
 *     Decodifica uma imagem BMP que já está carregada na memória. 
 *     (Pinta no backbuffer)
 * 
 * IN:
 *     address = endereço base
 *     x       = posicionamento 
 *     y       = posicionamento
 *
 * 
 *  #todo: 
 *  Criar defines para esses deslocamentos.
 */

int 
bmpDisplayBMP ( 
    char *address, 
    unsigned long x, 
    unsigned long y )
{

    int i=0; 
    int j=0; 
    int base=0; 
    int offset=0;


    unsigned long left=0;
    unsigned long top=0; 
    unsigned long bottom=0;

    unsigned long Width=0; 
    unsigned long Height=0;
    unsigned long xLimit=0;
    unsigned long yLimit=0;


    unsigned short Sig=0;
    unsigned short Size=0;

    unsigned long color=0;
    unsigned long color2=0;


    unsigned long pal_address=0;

    // Structures.

    struct bmp_header_d      *bh;
    struct bmp_infoheader_d  *bi;


	// Endereço base do BMP que foi carregado na memória
	unsigned char *bmp = (unsigned char *) address;
	
	// Variável para salvar rgba.
    unsigned char *c  = (unsigned char *) &color;
    unsigned char *c2 = (unsigned char *) &color2;

	unsigned long *palette       = (unsigned long *) (address + 0x36);		
	unsigned char *palette_index = (unsigned char *) &pal_address;	
	
	
	//
	// Limits
	//
	
	// #todo: 
	// Get system metrics.
	
	//xLimit = 800;
	//yLimit = 600;

	xLimit = SavedX;
	yLimit = SavedY;

    if ( x > xLimit || y > yLimit ){
        printf ("bmpDisplayBMP: Limits \n");
        goto fail;
    }


	// #todo:
	// Testar validade do endereço.
	

    if ( address == 0 ){
        printf ("bmpDisplayBMP: address \n");
        goto fail;
    }


	//
	// struct for Info header
	//
	
	// #BUGBUG 
	// Um kmalloc aqui pode esgotar o heap na hora de movimentar o mouse.
	// Precisamos usar um buffer interno para essa estrutura.

	char buffer[512];

	//bh = (struct bmp_header_d *) kmalloc( sizeof(struct bmp_header_d) );	
    bh = (struct bmp_header_d *) &buffer[0];

    if ( (void *) bh == NULL ){
        debug_print ("bmpDisplayBMP: bh \n");
        goto fail;
    }


    // Signature. ( 2 bytes )
    Sig = *(unsigned short *) &bmp[0];
    bh->bmpType = Sig;


    // Size. ( 2 bytes )
    // #bugbug: Isso deve ser 4 bytes
    Size = *( unsigned short * ) &bmp[2];
    //unsigned long Size = *( unsigned long * ) &bmp[2];
    bh->bmpSize = Size;

	
	//Offset from beginning of file to the beginning of the bitmap data
	//unsigned long DataOffset = *( unsigned long * ) &bmp[10];
	//bh->bmpOffBits = DataOffset;	
	
	
	
	//
	// struct for Info header
	//

	// #BUGBUG 
	// Um kmalloc aqui pode esgotar o heap na hora de movimentar o mouse.
	// Precisamos usar um buffer interno para essa estrutura.

	char buffer2[512];
	
	//Windows bmp.
	//bi = (struct bmp_infoheader_d *) kmalloc( sizeof(struct bmp_infoheader_d) );
    bi = (struct bmp_infoheader_d *)  &buffer2[0];

    if ( (void *) bi == NULL ){
        debug_print ("bmpDisplayBMP: bi \n");
        goto fail;
    }


	//The size of this header.
	
	bi->bmpSize = *( unsigned long* ) &bmp[14];



    // Width and height.
    // #todo: 
    // Checar a validade da altura e da largura encontrada.

    Width  = *( unsigned long * ) &bmp[18];
    Height = *( unsigned long * ) &bmp[22];

    // Salvando altura e largura.
	bi->bmpWidth  = (unsigned long) Width;
	bi->bmpHeight = (unsigned long) Height;


	// Number of bits per pixel.
	// 1, 4, 8, 16, 24 and 32.
	bi->bmpBitCount = *( unsigned short * ) &bmp[28];
	
	// 24
	// if ( bi->bmpBitCount != 24 ){
	//	//fail
	//}
	
	

    // Compression support.
    // 0 = Nenhuma compressão.
    // ...
    if ( bi->bmpCompression != 0 ){
        debug_print ("bmpDisplayBMP: [FAIL] Compression NOT supported\n");
        //goto fail;
    }


    // offset 2E - the number of colors in the color palette, 
    // or 0 to default to 2^n
	//bi->bmpClrUsed = *( unsigned long * ) &bmp[46];    
    
    
    // offset 32 - the number of important colors used, 
    // or 0 when every color is important; generally ignored	
	//bi->bmpClrImportant = *( unsigned long * ) &bmp[50];	
	
	
	// More ?
	
//
// == Draw ======================================================
//


	left = x;    
	top  = y; 
	bottom = ( top + bi->bmpHeight );


    //
    // == Data Area ============================================
    //

//#Aprendendo:
//1     -  1 bpp (Mono)
//4     -  4 bpp (Indexed)
//8     -  8 bpp (Indexed) bbgggrrr
//16565 - 16 bpp (5:6:5, RGB Hi color)
//16    - 16 bpp (5:5:5:1, RGB Hi color)
//160   - 16 bpp (5:5:5:1, RGBA Hi color)
//24    - 24 bpp (True color)
//32    - 32 bpp (True color, RGB)
//320   - 32 bpp (True color, RGBA)	

    // Início da área de dados do BMP.
    // #importante: A base é diferente para os tipos ?? 
    // Obs: Cada cor é representada com 4 bytes. RGBA.

    switch ( bi->bmpBitCount ){
		
        // 1 bit
		//case 1:
		//    base = (0x36 + 0x40);
		//    break;

		
		// 2 bit    
		//case 2:
		//    base = (0x36 + 0x40);
		//    break;

		
		// 4 bit
        // 4 bytes pra cada cor, 16 cores, 64 bytes.		
		case 4:
		    base = (0x36 + 0x40);
		    break; 

		
		// 8 bit
        // 4 bytes pra cada cor, 256 cores, 1024 bytes.		
		case 8: 
		    base = (0x36 + 0x400); 
			break; 


		// ?
		// 24bpp, 32bpp.
		default:
		    base = 0x36;
			break;
    };


    // Draw!

    for ( i=0; i < bi->bmpHeight; i++ )
    {
        for ( j=0; j < bi->bmpWidth; j++ )
        {
	        // 16 cores
            // Um pixel por nibble.
	        if (bi->bmpBitCount == 4 )
	        {
				offset = base;
							    
				palette_index[0] = bmp[offset];
												
                // Segundo nibble.
				if( nibble_count_16colors == 2222 )
				{
					palette_index[0] = ( palette_index[0] & 0x0F);  
					color = (unsigned long) palette[  palette_index[0]  ];
					
					nibble_count_16colors = 0;
					base = base + 1;
					
				// Primeiro nibble.	
				}else{

			        palette_index[0] =  ( (  palette_index[0] >> 4 ) & 0x0F);
					color = (unsigned long) palette[  palette_index[0] ];
				    
					nibble_count_16colors = 2222;
					//base = base;
				};
	        };	

			// 256 cores
			// Próximo pixel para 8bpp
	        if( bi->bmpBitCount == 8 )
	        {   
				offset = base;
				color = (unsigned long) palette[  bmp[offset] ];
				
				base = base + 1;     
	        };			
			
			
			// Próximo pixel para 16bpp
	        if( bi->bmpBitCount == 16 )
	        {
				//a
				c[0] = 0;  	
				
				offset = base;	
			    
				//b				
			    c[1] = bmp[offset];
			    c[1] = (c[1] & 0xF8);      // '1111 1000' 0000 0000  
				
				//g
			    c2[0] = bmp[offset];
			    c2[0] = c2[0] &  0x07;     // '0000 0111' 0000 0000 
			    c2[1] = bmp[offset+1];
			    c2[1] = c2[1] &  0xE0;     //  0000 0000 '1110 0000' 
				c[2] = ( c2[0] | c2[1] );  
					
			    //r
			    c[3] = bmp[offset+1];
			    c[3] = c[3] & 0x1F;        // 0000 0000 '0001 1111' 										
		        
				base = base + 2;    
	        };			
			

			// Próximo pixel para 24bpp.
	        if( bi->bmpBitCount == 24 )
	        {  
			    c[0] = 0; //A					
				
				offset = base;
				c[1] = bmp[offset];
			    
			    offset = base+1;
			    c[2] = bmp[offset];
			
			    offset = base+2;
			    c[3] = bmp[offset];
										
		        base = base + 3;    
	        };
			
			
			// Próximo pixel para 32bpp.
	        if( bi->bmpBitCount == 32 )
	        {	
			    c[0] = 0;  //A				
				
				offset = base;
			    c[1] = bmp[offset];
			
			    offset = base+1;
			    c[2] = bmp[offset];
			
			    offset = base+2;
			    c[3] = bmp[offset];
				
		        base = base + 4;    
	        };
			
			//
			// # Put pixel #
			//
			
			//Nesse momento já temos a cor selecionada 
			//no formato 0xaarrggbb ... 
			//Agora se a flag de mascara estiver selecionada,
			//então devemos ignora o pixel e não pintá-lo.	
			
			switch(bmp_change_color_flag)
			{
				//1000
				//flag para ignorarmos a cor selecionada.
				//Não pinte nada.
				//Devemos pintar caso a cor atual seja  
				//diferente da cor selecionada.
				case BMP_CHANGE_COLOR_TRANSPARENT:
				    if ( color != bmp_selected_color )
					{
		                //my_buffer_put_pixel ( (unsigned long) color, 
			            //    (unsigned long) left, 
						//    (unsigned long) bottom, 
						//    0 );	

		                backbuffer_putpixel ( (unsigned long) color, 
			                (unsigned long) left, 
						    (unsigned long) bottom, 
						    0 );							
					};
				    break;
					
				//2000	
				//Substitua pela cor indicada.
				//Se a cor atual é igual a cor selecionada,
				//devemos substituir a cor atual pela substituta.
				//Mas se a cor atual for diferente da cor selecionada,
				//pintamos normalmente a cor atual.
				case BMP_CHANGE_COLOR_SUBSTITUTE:
				    if( color == bmp_selected_color )
					{
			            
						//my_buffer_put_pixel ( (unsigned long) bmp_substitute_color, 
			            //    (unsigned long) left, 
						//    (unsigned long) bottom, 
						//     0 );
							 
						backbuffer_putpixel ( (unsigned long) bmp_substitute_color, 
			                (unsigned long) left, 
						    (unsigned long) bottom, 
						     0 );

							 
                    } else {
		                
						//my_buffer_put_pixel( (unsigned long) color, 
			            //    (unsigned long) left, 
						//    (unsigned long) bottom, 
						//    0 );
							
						backbuffer_putpixel ( (unsigned long) color, 
			                (unsigned long) left, 
						    (unsigned long) bottom, 
						    0 );

							
					};							 
				    break;
					
				//...	
					
				// 0 and default
				// Pintamos normalmente a cor atual.
                case BMP_CHANGE_COLOR_NULL:				
				default:
				
			        //my_buffer_put_pixel( (unsigned long) color, 
			        //    (unsigned long) left, 
					//	(unsigned long) bottom, 
					//	0 );				
				    
			        backbuffer_putpixel ( (unsigned long) color, 
			            (unsigned long) left, 
						(unsigned long) bottom, 
						0 );		
						
					break;
			};

			// Próximo pixel.
			left++; 
        };

		// Vamos para a linha anterior.
        bottom = (bottom-1);

		// Reiniciamos o x.
		left = x;    
    };


	// ## test palette 
	//int p;
	
	//if(bi->bmpBitCount == 8 )
	//{
	//    printf("\n");
	//    for( p=0; p<16; ++p )
	//    {
	//	   printf("%x\n",palette[p]);
	//    }
	//    printf("\n");
	//};
	
	
done:	
	//Debug
	//printf("w={%d} h={%d}\n", bi->bmpWidth, bi->bmpHeight );
	return 0;
	
fail:	
    //printf("fail");	
    return (int) 1;
    //return (int) -1;
}



/*
 * bmpDisplayMousePointerBMP:
 * 
 * 
 */

//mostra no lfb
//levando em consideração tratamento de transparência.

int 
bmpDisplayMousePointerBMP ( 
    char *address, 
    unsigned long x, 
    unsigned long y )
{


	//flag para ignorarmos a cor selecionada.
	bmp_change_color_flag = BMP_CHANGE_COLOR_TRANSPARENT;
	
	
	//#importante:
	//Selecionamos a cor que será ignorada.
    //background do bitmap é branco.
	bmp_selected_color = COLOR_WHITE;
    
	//
	// Display !!
	//
    
	//no LFB
	bmpDirectDisplayBMP ( address, x, y );
	
	
	//clear flags.
	bmp_change_color_flag = 0;
	bmp_selected_color = 0;
	
    return 0;
}


//mostra no lfb
//levando em consideração tratamento de transparência.

int 
bmpDisplayCursorBMP ( 
    char *address, 
    unsigned long x, 
    unsigned long y )
{

    //flag para ignorarmos a cor selecionada.
    bmp_change_color_flag = BMP_CHANGE_COLOR_TRANSPARENT;

    //#importante:
    //Selecionamos a cor que será ignorada.
    //background do bitmap é branco.
    bmp_selected_color = COLOR_WHITE;

    // Display !!
    // Direct on LFB.
    // Clear flags.

    bmpDirectDisplayBMP ( address, x, y );

    bmp_change_color_flag = 0;
    bmp_selected_color = 0;

    return 0;
}


//
// End.
//

