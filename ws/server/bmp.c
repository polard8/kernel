/*
 * File: view/bmp.c
 *
 * Description:
 *     BMP support.
 *
 * Obs: 
 *     As rotinas de bmp precisam melhorar.
 *     Conferir os parametros do bmp em seu header.
 *     todo: Criar uma rotina para filtrar o bmp por tamanho e tipo.
 *            bugbug: bmp envolve o carregamento de arquivo.
 *            Temos a op��o de utilizarmos arquivos que foram carregados
 * na inicializa��o, como parte dos elementos da interface gr�fica.
 * Obs: Esse tipo de servi�os pode ser oferecido por servidor.
 * 
 * History: 
 *     2019 - Created by Fred Nora. 
 *            Ported from older versions in the system.
 */


#include <gws.h>


// 4bpp support.
static int nibble_count_16colors = 0;


/*
 ********************************************************
 * bmpDirectDisplayBMP:
 *
 *     Mostra na tela uma imagem bmp que j� est� 
 * carregada na mem�ria. (diretamente no LFB)
 * 
 * IN:
 *     address = endere�o base
 *     x       = posicionamento 
 *     y       = posicionamento
 *
 *    #todo: 
 *    Criar defines para esses deslocamentos.
 */ 


// #todo
// Vamos suspender essa rotina, porque
// falta  a fun��o que escreve diretamente no lfb
// estando aqui em ring3.


/*
 
int 
bmpDirectDisplayBMP ( 
    char *address, 
    unsigned long x, 
    unsigned long y );

int 
bmpDirectDisplayBMP ( 
    char *address,
    unsigned long x,
    unsigned long y )
{
	int i, j, base, offset;
	
	unsigned long left, top, bottom;

	unsigned long Width, Height;
	unsigned long xLimit, yLimit;
	
	unsigned short sig;
	
	unsigned long color, color2;
	unsigned long pal_address;	
	
	struct bmp_header_d *bh;
	struct bmp_infoheader_d *bi;
	
	// Endere�o base do BMP que foi carregado na mem�ria
	unsigned char *bmp = (unsigned char *) address;
	
	// Vari�vel para salvar rgba.
	unsigned char *c = (unsigned char *) &color;
    unsigned char *c2 = (unsigned char *) &color2;	
	
	unsigned long *palette = (unsigned long *) (address + 0x36);		
	unsigned char *palette_index = (unsigned char *) &pal_address;	
	
	// Limits
	// @todo: get system metrics.
	xLimit = 800;
	yLimit = 600;
	
	
	//
	// Sincroniza��o do retra�o vertical.
	//
	
	// #suspenso
	// vsync ();
	
	
	// Limits.
	if ( x > xLimit || y > yLimit )
	{
		printf("bmpDirectDisplayBMP: Limits \n");
        goto fail;		
        //return (int) 1; 
	};
	

	// @todo:
	// Testar validade do endere�o.
	if ( address == 0 ){
		//goto fail;
	};
	
	
	//
	// struct for Info header
	//
	
	//## BUGBUG 
	// Um malloc aqui pode esgotar o heap 
	//na hora de movimentar o mouse.
	//precisamos usar um buffer interno para
	//essa estrutura.
	
	char buffer[512];
	char buffer2[512];
	
	//bh = (struct bmp_header_d *) malloc( sizeof(struct bmp_header_d) );	
    bh = (struct bmp_header_d *) &buffer[0];
	
	if ( (void *) bh == NULL )
	{
		//goto fail;
	}	
	
	// Signature.
	sig = *( unsigned short* ) &bmp[0];
	bh->bmpType = sig;
	
	// Size. ( 2 bytes )
	unsigned short Size = *( unsigned short* ) &bmp[2];
	bh->bmpSize = Size;
	
	
	//
	// struct for Info header
	//
	
	//Windows bmp.
	//bi = (struct bmp_infoheader_d *) malloc( sizeof(struct bmp_infoheader_d) );
    bi = (struct bmp_infoheader_d *)  &buffer2[0];
	
	if ( (void *) bi == NULL )
	{
		//goto fail;
	}	
	
	//The size of this header.
	bi->bmpSize = *(unsigned long *) &bmp[14];
	
	// Width and height.
    Width = *( unsigned long * ) &bmp[18];
    Height = *( unsigned long * ) &bmp[22];	
	
	//@todo: checar validade da altura e da largura encontrada.
	
	// Salvar.
	bi->bmpWidth = (unsigned long) Width;
	bi->bmpHeight = (unsigned long) Height;
	
	
	// Number of bits per pixel.
	// 1, 4, 8, 16, 24 and 32.
	bi->bmpBitCount = *( unsigned short * ) &bmp[28];
	
	// 24
	//if( bi->bmpBitCount != 24 ){
	//	//fail
	//}
	
	
	// 0 = Nenhuma compress�o.
	if ( bi->bmpCompression != 0 ){
		//fail
	}
	
	
	//
	// # Draw #
	//
	
//DrawBMP:	

	left = x;    
	top = y; 
	bottom = ( top + bi->bmpHeight );

	// In�cio da �rea de dados do BMP.
	
	//#importante:
	//A base � diferente para os tipos ?? 

	switch ( bi->bmpBitCount )
    {
		//Obs: Cada cor � representada com 4 bytes. RGBA.
		
		//case 1:
		//    base = (0x36 + 0x40);
		//    break;
		    
		//case 2:
		//    base = (0x36 + 0x40);
		//    break;
		
        // 4 bytes pra cada cor, 16 cores, 64 bytes.		
		case 4:
		    base = (0x36 + 0x40);
		    break; 
		
        //4 bytes pra cada cor, 256 cores, 1024bytes.		
		case 8: 
		    base = (0x36 + 0x400); 
			break; 
			
		default:
		    base = 0x36;
			break;
	};	
	
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
			// Pr�ximo pixel para 8bpp
	        if ( bi->bmpBitCount == 8 )
	        {   
				offset = base;
				color = (unsigned long) palette[  bmp[offset] ];
				
				base = base + 1;     
	        };			
			
			
			// Pr�ximo pixel para 16bpp
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
		        
				base = base + 2;    
	        };			
			

			// Pr�ximo pixel para 24bpp.
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
			
			
			// Pr�ximo pixel para 32bpp.
	        if ( bi->bmpBitCount == 32 )
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
			
			//Nesse momento j� temos a cor selecionada 
			//no formato 0xaarrggbb ... 
			//Agora se a flag de mascara estiver selecionada,
			//ent�o devemos ignora o pixel e n�o pint�-lo.	
			
			switch (bmp_change_color_flag)
			{
				//1000
				//flag para ignorarmos a cor selecionada.
				//N�o pinte nada.
				//Devemos pintar caso a cor atual seja  
				//diferente da cor selecionada.
				case BMP_CHANGE_COLOR_TRANSPARENT:
				    if ( color != bmp_selected_color )
					{
		                lfb_putpixel ( (unsigned long) color, 
			                (unsigned long) left, 
						    (unsigned long) bottom, 
						    0 );							
					};
				    break;
					
				//2000	
				//Substitua pela cor indicada.
				//Se a cor atual � igual a cor selecionada,
				//devemos substituir a cor atual pela substituta.
				//Mas se a cor atual for diferente da cor selecionada,
				//pintamos normalmente a cor atual.
				case BMP_CHANGE_COLOR_SUBSTITUTE:
				    if ( color == bmp_selected_color )
					{	 
						lfb_putpixel ( (unsigned long) bmp_substitute_color, 
			                (unsigned long) left, 
						    (unsigned long) bottom, 
						     0 );
							 
                    } else {
		                							
						lfb_putpixel ( (unsigned long) color, 
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
				
			        lfb_putpixel ( (unsigned long) color, 
			            (unsigned long) left, 
						(unsigned long) bottom, 
						0 );		
						
					break;
			};

			// Pr�ximo pixel.
			left++; 
		};
		
		
		// Vamos para a linha anterior.
		bottom = bottom-1;
		
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
}
*/



/*
 ********************************************************
 * bmpDisplayBMP:
 *
 *     Mostra na tela uma imagem BMP que j� est� 
 * carregada na mem�ria. (pinta no backbuffer)
 * 
 * IN:
 *     address = endere�o base onde o bmp j� est� carregado.
 *     x       = posicionamento 
 *     y       = posicionamento
 *
 *     @todo: Criar defines para esses deslocamentos.
 */

int 
bmpDisplayBMP ( 
    char *address, 
    unsigned long x, 
    unsigned long y )
{
    // Endereço base do BMP que foi carregado na memoria
    unsigned char *bmp = (unsigned char *) address;

    struct gws_bmp_header_d      *bh;
    struct gws_bmp_infoheader_d  *bi;

    int i, j, base, offset;

    unsigned int left, top, bottom;


    // Zoom support.
    // It is working.
    // But we need to work in the 'position' thing
    // and accept some function parameters for that effect.
    int useZoom=FALSE;
    int ZoomFactor=8;
    int iwZoom=0;
    int ihZoom=0;


    unsigned int X=0;
    unsigned int Y=0;
    unsigned int Width=0;
    unsigned int Height=0;
    
    unsigned int xLimit=0;
    unsigned int yLimit=0;

    unsigned short sig=0;

    unsigned int color=0;
    unsigned int color2=0;
    unsigned long pal_address=0;


    // Vari�vel para salvar rgba.
    unsigned char *c  = (unsigned char *) &color;
    unsigned char *c2 = (unsigned char *) &color2;

    unsigned int *palette        = (unsigned int *) (address + 0x36);
    unsigned char *palette_index = (unsigned char *) &pal_address;


    // Limits

    // #todo: 
    // Get system metrics.

    xLimit = 800;
    yLimit = 600;


    gwssrv_debug_print ("bmpDisplayBMP:\n");


    // Limits.
    if ( x > xLimit || y > yLimit ){
        gwssrv_debug_print ("bmpDisplayBMP: Limits \n");
        printf             ("bmpDisplayBMP: Limits \n");
        goto fail;
    }


    // #todo:
    // Testar validade do endereço.
    if ( address == 0 ){
        gwssrv_debug_print ("bmpDisplayBMP: address fail \n");
        printf             ("bmpDisplayBMP: address fail \n");
        goto fail;
    }



	//
	// struct for Info header
	//

    // #todo: 
    // Podemos usar malloc?
    
    // Buffer para as estruturas.
    //char buffer[512];
    //char buffer2[512];


    bh = (struct gws_bmp_header_d *) malloc ( sizeof(struct gws_bmp_header_d) );

    if ( (void *) bh == NULL )
    {
        gwssrv_debug_print ("bmpDisplayBMP: bh fail \n");
        printf             ("bmpDisplayBMP: bh fail \n");
        goto fail;
    }

    //
    // Signature.
    //

    sig = *(unsigned short *) &bmp[0];
    bh->bmpType = sig;
    //printf ("sig={%x}\n",sig);

    if ( bmp[0] != 'B' || bmp[1] != 'M' )
    {
        gwssrv_debug_print ("bmpDisplayBMP: [FAIL] signature \n");
        printf             ("bmpDisplayBMP: [FAIL] signature %c %c\n", 
            bmp[0], bmp[1]);
        goto fail;
    }

    //
    // Size. ( 2 bytes )
    //

    unsigned short Size = *(unsigned short *) &bmp[2];
    bh->bmpSize = Size;
    //printf ("Size={%x}\n",Size);



	//
	// struct for Info header
	//

    //Windows bmp.
    bi = (struct gws_bmp_infoheader_d *) malloc ( sizeof(struct gws_bmp_infoheader_d) );

    if ( (void *) bi == NULL ){
        gwssrv_debug_print ("bmpDisplayBMP: bi fail \n");
        printf             ("bmpDisplayBMP: bi fail \n");
        goto fail;
    }

    // The size of this header.
    bi->bmpSize = *( unsigned long * ) &bmp[14];
    //printf ("HeaderSize={%x}\n",bi->bmpSize);

    // X and Y.
    X = x;
    Y = y;
    
    // Width and height.
    Width  = *( unsigned long * ) &bmp[18];
    Height = *( unsigned long * ) &bmp[22];

    // Salvar.
    bi->bmpWidth  = (unsigned long) Width;
    bi->bmpHeight = (unsigned long) Height;

    //printf ("w=%d h=%d\n",Width,Height);




    // Number of bits per pixel.
    // 1, 4, 8, 16, 24 and 32.
    bi->bmpBitCount = *( unsigned short * ) &bmp[28];

    //printf ("Count={%d}\n", bi->bmpBitCount );
    
    
    
    //#limits
    //if( bi->bmpBitCount != 24 )
    //{
    //    printf("bmpDisplayBMP: Count fail\n");
    //    goto fail;
    // }


    //
    // Compression.
    //

    // 0 = No compression.

    /*
    if ( bi->bmpCompression != 0 ){
        gwssrv_debug_print ("bmpDisplayBMP: bmpCompression fail \n");
        printf             ("bmpDisplayBMP: bmpCompression fail \n");
        goto fail;
    }
    */
    

    //
    // Draw
    //

    gwssrv_debug_print ("bmpDisplayBMP: Draw!\n");
    //printf             ("bmpDisplayBMP: Draw!\n");

    // Top, Left, Bottom.

    left = x; 
    top  = y; 
    bottom = ( top + bi->bmpHeight );


    //
    // Data area.
    //

    // bpp
    // The begin of the data area depends on the bpp value.

// #tutorial:
//1     -  1 bpp (Mono)
//4     -  4 bpp (Indexed)
//8     -  8 bpp (Indexed) bbgggrrr
//16565 - 16 bpp (5:6:5, RGB Hi color)
//16    - 16 bpp (5:5:5:1, RGB Hi color)
//160   - 16 bpp (5:5:5:1, RGBA Hi color)
//24    - 24 bpp (True color)
//32    - 32 bpp (True color, RGB)
//320   - 32 bpp (True color, RGBA)	


    switch ( bi->bmpBitCount ){

        // ??
        //case 1:  base = (0x36 + 0x40); break;

        // ??
        //case 2: base = (0x36 + 0x40); break;

        // 4 bytes pra cada cor, 16 cores. Total 64 bytes.
        case 4:  
            base = (0x36 + 0x40); 
            gwssrv_debug_print ("bmpDisplayBMP: bmpBitCount 4\n"); 
            break; 

        // 4 bytes pra cada cor, 256 cores. Total 1024 bytes.
        case 8:  
            base = (0x36 + 0x400); 
            gwssrv_debug_print ("bmpDisplayBMP: bmpBitCount 8\n"); 
            break;

        // #todo: Onde fica a base??
        case 16:
            base = 0x36;
            gwssrv_debug_print ("bmpDisplayBMP: [FIXME] bmpBitCount 16\n"); 
            break;

        // #todo: Onde fica a base??
        case 24:
            base = 0x36;
            gwssrv_debug_print ("bmpDisplayBMP: [FIXME] bmpBitCount 24\n"); 
            break;

        // #todo: Onde fica a base??
        case 32:
            base = 0x36;
            gwssrv_debug_print ("bmpDisplayBMP: [FIXME] bmpBitCount 32\n"); 
            break;

        // #bugbug
        // We need to abort.
        default:  
            base = 0x36;
            gwssrv_debug_print ("bmpDisplayBMP: [FAIL] bmpBitCount fail\n"); 
            break;
    };

    //#debug
    gwssrv_debug_print ("bmpDisplayBMP: for\n");
    //printf             ("bmpDisplayBMP: for\n");

    for ( i=0; i < bi->bmpHeight; i++ )
    {
        for ( j=0; j < bi->bmpWidth; j++ )
        {
            // >> 16 cores
            // Um pixel por nibble.
            if (bi->bmpBitCount == 4 )
            {
                offset = base;
    
                palette_index[0] = bmp[offset];

                // Segundo nibble.
                if ( nibble_count_16colors == 2222 )
                {
                    palette_index[0] = ( palette_index[0] & 0x0F);  
                    color = (unsigned int) palette[  palette_index[0]  ];

                    nibble_count_16colors = 0;
                    base = base + 1;

                // Primeiro nibble.
                }else{

                    palette_index[0] =  ( (  palette_index[0] >> 4 ) & 0x0F);
                    color = (unsigned int) palette[  palette_index[0] ];

                    nibble_count_16colors = 2222;
                    //base = base + 0;
                };
            }

            // >> 256 cores
            // Próximo pixel para 8bpp
            if ( bi->bmpBitCount == 8 )
            {   
                offset = base;
                color = (unsigned int) palette[  bmp[offset] ];

                base = base + 1; 
            }

            // >>
            // Pr�ximo pixel para 16bpp
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

                base = base + 2; 
            }

            // Próximo pixel para 24bpp.
            if ( bi->bmpBitCount == 24 )
            { 
                c[0] = 0; //A

                offset = base;
                c[1] = bmp[offset];

                offset = base+1;
                c[2] = bmp[offset];

                offset = base+2;
                c[3] = bmp[offset];

                base = base + 3; 
            }


            // Próximo pixel para 32bpp.
            if ( bi->bmpBitCount == 32 )
            {
                c[0] = 0;  //A

                offset = base;
                c[1] = bmp[offset];

                offset = base+1;
                c[2] = bmp[offset];

                offset = base+2;
                c[3] = bmp[offset];

                base = base + 4;    
            }

			//
			// # Put pixel #
			//
				
			//Nesse momento j� temos a cor selecionada 
			//no formato 0xaarrggbb ... 
			//Agora se a flag de mascara estiver selecionada,
			//ent�o devemos ignora o pixel e n�o pint�-lo.	

            switch (bmp_change_color_flag)
            {
				//1000
				//flag para ignorarmos a cor selecionada.
				//N�o pinte nada.
				//Devemos pintar caso a cor atual seja  
				//diferente da cor selecionada.
                case BMP_CHANGE_COLOR_TRANSPARENT:
                    if ( color != bmp_selected_color )
                    {

                        if (useZoom==FALSE){
                            pixelBackBufferPutpixel ( //original, funciona.
                                (unsigned int) color, 
                                (unsigned long) left, 
                                (unsigned long) bottom);
                        }

                        // #test
                        // Testing zoom support.
                        
                        // zoom.
                        if (useZoom==TRUE){
                            for (ihZoom=0; ihZoom < (ZoomFactor+1); ihZoom++){
                            for (iwZoom=0; iwZoom < (ZoomFactor+1); iwZoom++){ 

                            pixelBackBufferPutpixel ( 
                                (unsigned int) color, 
                                (unsigned long) left   + (j * ZoomFactor) + iwZoom, 
                                (unsigned long) bottom - (i * ZoomFactor) + ihZoom );
                            
                            };};
                        }


                    }
                    break;

				//2000	
				//Substitua pela cor indicada.
				//Se a cor atual � igual a cor selecionada,
				//devemos substituir a cor atual pela substituta.
				//Mas se a cor atual for diferente da cor selecionada,
				//pintamos normalmente a cor atual.
                case BMP_CHANGE_COLOR_SUBSTITUTE:
                    if ( color == bmp_selected_color )
                    {
                        pixelBackBufferPutpixel ( 
                            (unsigned int) bmp_substitute_color, 
                            (unsigned long) left, 
                            (unsigned long) bottom );

						//my_buffer_put_pixel ( (unsigned long) bmp_substitute_color, 
			            //    (unsigned long) left, 
						//    (unsigned long) bottom, 
						//     0 );
							 
						//backbuffer_putpixel ( (unsigned long) bmp_substitute_color, 
			            //    (unsigned long) left, 
						//    (unsigned long) bottom, 
						//     0 );

                    }else{

                        pixelBackBufferPutpixel ( 
                            (unsigned int) bmp_substitute_color, 
                            (unsigned long) left, 
                            (unsigned long) bottom );

						//my_buffer_put_pixel( (unsigned long) color, 
			            //    (unsigned long) left, 
						//    (unsigned long) bottom, 
						//    0 );
							
						//backbuffer_putpixel ( (unsigned long) color, 
			            //    (unsigned long) left, 
						//    (unsigned long) bottom, 
						//    0 );

                    }; 
                    break;

                // ...

                // 0 and default
                // Pintamos normalmente a cor atual.

                case BMP_CHANGE_COLOR_NULL:
                default:

                    pixelBackBufferPutpixel( 
                        (unsigned int) bmp_substitute_color, 
                        (unsigned long) left, 
                        (unsigned long) bottom );

			        //my_buffer_put_pixel( (unsigned long) color, 
			        //    (unsigned long) left, 
					//	(unsigned long) bottom, 
					//	0 );				
				    
			        //backbuffer_putpixel ( (unsigned long) color, 
			        //    (unsigned long) left, 
					//	(unsigned long) bottom, 
					//	0 );

                    break;
            };

            // next pixel

            left++; 
        };

        // Vamos para a linha anterior.
        // Reiniciamos o x.

        bottom = (bottom-1);
        left = x;
    };


	// ## test palette 
	//int p;
	
	//if(bi->bmpBitCount == 8 )
	//{
	//    printf("\n");
	//    for( p=0; p<16; ++p )
	//    {
	//        printf("%x\n",palette[p]);
	//    }
	//    printf("\n");
	//};


done:

    gws_refresh_rectangle (X,Y,Width,Height);

    // #debug
    gwssrv_debug_print ("bmpDisplayBMP: done \n");
    //printf            ("bmpDisplayBMP: done \n");
    //printf("w={%d} h={%d}\n", bi->bmpWidth, bi->bmpHeight );
    return 0;

fail:
    gwssrv_debug_print ("bmpDisplayBMP: Fail \n");
    printf             ("bmpDisplayBMP: Fail \n");
    return (int) 1;
    //return (int) -1;
}


// mostra no lfb
// levando em consideraçao tratamento de transparencia.

// #todo: precisamos de put pixel direto no lfb.
/*
int 
bmpDisplayMousePointerBMP ( 
    char *address, 
    unsigned long x, 
    unsigned long y );

int 
bmpDisplayMousePointerBMP ( 
    char *address, 
    unsigned long x, 
    unsigned long y )
{

	//flag para ignorarmos a cor selecionada.
	bmp_change_color_flag = BMP_CHANGE_COLOR_TRANSPARENT;
	
	
	//#importante:
	//Selecionamos a cor que ser� ignorada.
    //background do bitmap � branco.
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
*/


//mostra no lfb
//levando em considera��o tratamento de transpar�ncia.
//mostra no lfb
//levando em considera��o tratamento de transpar�ncia.

// #todo: precisamos de putpixl direto no lfb.

/*
int 
bmpDisplayCursorBMP ( 
    char *address, 
    unsigned long x, 
    unsigned long y );

int 
bmpDisplayCursorBMP ( 
    char *address, 
    unsigned long x, 
    unsigned long y )
{

	//flag para ignorarmos a cor selecionada.
	bmp_change_color_flag = BMP_CHANGE_COLOR_TRANSPARENT;

	//#importante:
	//Selecionamos a cor que ser� ignorada.
    //background do bitmap � branco.
	bmp_selected_color = COLOR_WHITE;

	// Display !!
	// Direct on LFB.
    // Clear flags.
	
	bmpDirectDisplayBMP ( address, x, y );
	
	bmp_change_color_flag = 0;
	bmp_selected_color = 0;


    return 0;
}
*/


/*
 * gwssrv_get_system_icon:
 *     Get an address to a shared memory buffer
 * where there is an icon previously loaded by the kernel.
 * 
 */

// Called by gwssrv_display_system_icon.

void *gwssrv_get_system_icon (int n)
{
    if (n<0){
        return NULL;
    }

    return (void *) gramado_system_call(9100,n,n,n);
}


/*
 * gwssrv_display_system_icon:
 * 
 * 
 */
 
// Called by createwDrawFrame on createw.c

int 
gwssrv_display_system_icon ( 
    int index, 
    unsigned long x, 
    unsigned long y )
{

    int RefreshScreen= FALSE;

    // Shared memory
    // Um endereço compartilhado onde o ícone
    // foi carregado pelo kernel.

    char *sm_buffer;

    // #todo: 
    // limits for x and y.




    //
    // Get buffer address.
    //

    sm_buffer = (char *) gwssrv_get_system_icon(index);
    //sm_buffer = gwssrv_get_system_icon(2);
    // ...

    //
    // check
    //

    // Check pointer validation

    if ( (void *) sm_buffer == NULL )
    {
        printf ("gwssrv_display_system_icon: bmp_buffer fail\n");
        return -1;
    }

    // Check BM header.

    if ( sm_buffer[0] != 'B' || sm_buffer[1] != 'M' )
    {
        // #debug

        gwssrv_debug_print ("gwssrv_display_system_icon: [FAIL] header\n");
        printf             ("gwssrv_display_system_icon: [FAIL] header\n");

        printf ("gwssrv_display_system_icon: %c %c\n", 
            &sm_buffer[0], 
            &sm_buffer[1] );


        // #debug
        // Show the whole screen if fail
        gws_show_backbuffer();
        
        //return -1;
        while(1);
    }

    // Check BM header. Again.

    if ( sm_buffer[0] == 'B' && sm_buffer[1] == 'M' )
    {
        // #flags
        bmp_change_color_flag = BMP_CHANGE_COLOR_TRANSPARENT;
        //bmp_change_color_flag = BMP_CHANGE_COLOR_SUBSTITUTE;
        //bmp_change_color_flag = BMP_CHANGE_COLOR_NULL;
        bmp_selected_color = COLOR_WHITE;

        // Decode on backbuffer ?
 
        // See:
        // ??
        
        bmpDisplayBMP( 
            (char *) sm_buffer, 
            (unsigned long) x, 
            (unsigned long) y ); 

        //gde_display_bmp((char *)sm_buffer, (unsigned long) 80, (unsigned long) 80); 
    }
    
     //#debug
     //printf("gwssrv_display_system_icon: *hang2\n");
     
     // #bugbug #todo
     // We need to use the routine to refresh the rectangle.
     
     if (RefreshScreen == TRUE){
         gws_show_backbuffer();
     }
     
     return 0;
}


//
// End.
//

