/*
 * File: rect.c
 *
 *     Draw rectangles.
 *  
 * History:
 *    2015 - Created by Fred Nora.
 */


#include <kernel.h>



//Herdadas do Boot Loader.
// De onde vem isso ?? head.s
// @todo: Devemos chamar o módulo hal para obtermos esses valores.
//depois salvamos em variáveis internas usadas pela gui.

extern unsigned long SavedBootBlock;
extern unsigned long SavedLFB;
extern unsigned long SavedX;
extern unsigned long SavedY;
extern unsigned long SavedBPP; 


// ??
// Copiando ...
// Destination is an Null pointer? 
// Source is an Null pointer? 
// Zero-sized copy? 
// Destination is Source?

void *rectStrCopyMemory32 ( unsigned long *dest, 
                            unsigned long *src, 
                            int count ) 
{
	int i;
	
	if ( (dest == NULL)  || 
	     (src == NULL)   || 
		 (count == 0)    || 
		 (src == dest) ) 
	{
        // Yes		
		return dest;
	}
	
	// GCC should optimize this for us :)
	
	for ( i=0; i < count; i++ ) 
	{
		dest[i] = src[i];
	}
	
	return dest;
}


//
//===============================================================
// refresh rect - Fred. P.
//
// @todo:
// Nessa macro podemos usar variáveis globais e inicializar
// essas variável. E considerarmos valores como g_bpp, g_screen_width. 
//


//#define RGB_PIXEL_OFFSET(x,y) \
//( (3*800*(y)) + (3*(x)) )

//
// #define RGB_PIXEL_OFFSET(x,y) \
// ( (3*screenGetWidth()*(y)) + (3*(x)) )
//
// #define RGB_PIXEL_OFFSET(x,y) \
// ( ( screenGetBPP() * screenGetWidth()*(y)) + ( screenGetBPP() *(x)) )

// #define RGB_PIXEL_OFFSET(x,y) \
// ( ( g_bpp * g_screen_width *(y)) + ( g_bpp *(x)) )

//================================================


//Usada no refresh rectangle.
//#todo: precisamos de uma variável para a lergura 
//da tela e para bytes per pixel.
//#todo: isso deve virar uma função.
//#define BUFFER_PIXEL_OFFSET(x,y) \
//( (3*800*(y)) + (3*(x)) )

/*
 
 ### Usar isso ###
 
unsigned long function_BUFFER_PIXEL_OFFSET ( unsigned long x, unsigned long y );
unsigned long function_BUFFER_PIXEL_OFFSET ( unsigned long x, unsigned long y )
{
    //( (3*800*(y)) + (3*(x)) )
	
    return (unsigned long) ( ( bytes_per_pixel * pixels_per_line *(y)) + ( bytes_per_pixel *(x)) );    	
};
*/

//
// @todo: Criar uma estrutura para o elemento gráfico. entre os elementos da estrutura
// pode ter os buffer para o char. backbuffer, frontbuffer, dedicatedbuffer.
//
//


/*
 * rectDrawRectangleWindowBuffer:
 *     Pinta um retângulo no buffer da janela.
 *     Serve para pintar janelas que irão direto do seu buffer para o LFB da 
 * memória de vídeo, sem passar pelo back buffer. (OVERLAPPED)
 *
 */
/*
void rectDrawRectangleWindowBuffer(struct window_d *window, 
                                   unsigned long x, 
                                   unsigned long y, 
						           unsigned long width, 
						           unsigned long height, 
						           unsigned long color ); 
void rectDrawRectangleWindowBuffer(struct window_d *window, 
                                   unsigned long x, 
                                   unsigned long y, 
						           unsigned long width, 
						           unsigned long height, 
						           unsigned long color )
{
    return;	
}
*/


/* 
void rectDrawRectangle( struct window_d *window, struct rect_d *rect);
void rectDrawRectangle( struct window_d *window, struct rect_d *rect)
{
	struct window_d *hwndDesktop;
	
    hwndDesktop = guiGetMainWindow();
	
	// Criaremos o retângulo na janela principal caso o ponteiro 
	//passado seja inválido.
	
    if( (void*) window == NULL ){
        window = hwndDesktop;
    };

    unsigned long x; 
    unsigned long y; 
	unsigned long width; 
	unsigned long height; 
	unsigned long color;

    x      = window->left + rect->x;	
	y      = window->top + rect->y;
	width  = rect->width;
	height = rect->height;
	color = rect->bg_color;
	
    drawDataRectangle( x, y, width, height, color );
	
}						
*/

 
/* 
 *************************************
 * drawDataRectangle:
 *     Draw a rectangle on backbuffer. 
 */

void 
drawDataRectangle ( unsigned long x, 
                    unsigned long y, 
                    unsigned long width, 
                    unsigned long height, 
                    unsigned long color )
{
	struct rect_d rect;
	
    rect.bg_color = color;

    //Dimensions.
	rect.x = 0;        
    rect.y = 0;         
    rect.width = width;   
    rect.height = height;    

    //Margins.
    rect.left = x;    
    rect.top = y;
    rect.right = rect.left + rect.width;
    rect.bottom = rect.top + rect.height; 

	// Limits.
	
	// #todo: 
	// Repensar os limites para uma janela.
	// Uma janela poderá ser maior que as dimensões de um dispositivo.
	// mas não poderá ser maior que as dimensões do backbuffer.
	// Ou seja: O dedicated buffer de uma janela deve ser menor que
	// o backbuffer.
	
    if ( rect.right > SavedX )
	{
        rect.right = SavedX;
	}	

    if ( rect.bottom > SavedY )
	{
        rect.bottom = SavedY;
	}
    	
  	
    // Draw lines on backbuffer.
	
	while (height--)
	{	
	    my_buffer_horizontal_line ( rect.left, y, rect.right, rect.bg_color );
		
		y++;
    };    
}


/*
 * getClientAreaRect:
 *     Obtém o ponteiro da estrutura do retângulo  
 *     da área de cliente da janela ativa.
 *     @todo: oferecer esse serviço para a api.
 */  

void *getClientAreaRect (void){
	
	
	// #bugbug
	// Essa variável global está estranha.
	// ?? Isso é o que ? um ponteiro de estruttura ?
	
    return (void *) rectClientArea;	
}


/*
 * setClientAreaRect:
 *     Inicializa a estrutura do retângulo da área de cliente 
 * da janela ativa.
 */

void 
setClientAreaRect ( unsigned long x, 
                    unsigned long y, 
                    unsigned long cx, 
                    unsigned long cy )
{
    struct rect_d *r;

    if ( (void *) rectClientArea == NULL )
	{
	    return;

	}else{

        r->x = x;
        r->y = y;
        r->cx = cx;
        r->cy = cy;

        rectClientArea = (void *) r;
	};
}




/*
 * #todo 
 * kgws não pode acessar o lfb, devemos chamar o diálogo em x/video.c
 * 
 */
 
/*
 ***********************************************************
 * refresh_rectangle:
 *     Copiar um retângulo do backbuffer para o frontbuffer. 
 * 
 *     @todo: Rotina parecida com essa pode ser criada e usada para manipular 
 * regiões da tela, como área de cliente efetuar scroll de buffer em páginas 
 * de navegador ou menus .. mas para isso, a cópia seria dentro do próprio 
 * backbuffer ou de um terceiro buffer para o backbuffer. 
 *
 * Histórico:
 *     2017 - Criado por Frederico Lamberti Pissarra.
 *     2018 - Fred Nora.
 */	


//#importante
//É bem mais rápido com múltiplos de 4.
 
void 
refresh_rectangle ( 
    unsigned long x, 
    unsigned long y, 
    unsigned long width, 
    unsigned long height )
{

	void *p = (void *) FRONTBUFFER_ADDRESS;
	const void *q = (const void*) BACKBUFFER_ADDRESS;

	//#TEST
	register unsigned int i;
	//unsigned int i;

	unsigned int line_size, lines;
	unsigned int offset;
	unsigned long Width = (unsigned long) screenGetWidth();
	unsigned long Height = (unsigned long) screenGetHeight();

	int count; 

	// = 3; 24bpp
	int bytes_count;

	line_size = (unsigned int) width; 
	lines = (unsigned int) height;

	
	switch (SavedBPP)
	{
		case 32:
		    bytes_count = 4;
		    break;
		
		case 24:
		    bytes_count = 3;
			break;
			
		//...
	}

	// #atenção.
	
	//offset = (unsigned int) BUFFER_PIXEL_OFFSET( x, y );
	
	offset = (unsigned int) ( (bytes_count*SavedX*(y)) + (bytes_count*(x)) );
	
	p = (void *) (p + offset);    
	q = (const void *) (q + offset);    
	 
	// #bugbug
	// Isso pode nos dar problemas.
	// ?? Isso ainda é necessário nos dias de hoje ??
	
	vsync ();	
		
	//(line_size * bytes_count) é o número de bytes por linha. 

	//#importante
	//É bem mais rápido com múltiplos de 4.	
	
	//se for divisível por 4.
	if ( ((line_size * bytes_count) % 4) == 0 )
	{
        count = ((line_size * bytes_count) / 4);  	

	    for ( i=0; i < lines; i++ )
	    {
		    //copia uma linha ou um pouco mais caso não seja divisível por 
		    memcpy32 ( p, q, count );
		    
			q += (Width * bytes_count);
	 		p += (Width * bytes_count);
	    };
	}

	//se não for divisível por 4.
	if ( ((line_size * bytes_count) % 4) != 0 )
	{
	    for ( i=0; i < lines; i++ )
	    {
		    memcpy ( (void *) p, (const void *) q, (line_size * bytes_count) );
		    
			q += (Width * bytes_count);
		    p += (Width * bytes_count);
	    };	
	}
}


// ??
// A ideia aqui é efetuar o refresh de um retângulo 
// que esteja em um dado buffer.
// ?? Not tested yet

void 
refresh_rectangle2 ( 
    unsigned long x, 
    unsigned long y, 
    unsigned long width, 
    unsigned long height,
    unsigned long buffer1,
    unsigned long buffer2 )
{    
	void *p = (void *) buffer1;   // destino
	const void *q = (const void *) buffer2;  //origem.

	//register unsigned int i;
	unsigned int i;
	
	unsigned int line_size, lines;
	unsigned int offset;
	unsigned long Width = (unsigned long) screenGetWidth();
	unsigned long Height = (unsigned long) screenGetHeight();	

	int count; 

	// = 3; //24bpp
	int bytes_count;
	
	line_size = (unsigned int) width; 
	lines = (unsigned int) height;
	
	switch (SavedBPP)
	{
		case 32:
		    bytes_count = 4;
		    break;
		
		case 24:
		    bytes_count = 3;
			break;
	}
	
	
	//offset = (unsigned int) BUFFER_PIXEL_OFFSET( x, y );
	offset = (unsigned int) ( (bytes_count*SavedX*(y)) + (bytes_count*(x)) );	

	
	p = (void *) (p + offset);    
	q = (const void *) (q + offset);    
	 
    //vsync ();
	
	
	//(line_size * 3) é o número de bytes por linha. 
	
	//se for divisível por 4.
	if( ((line_size * 3) % 4) == 0 )
	{
        count = ((line_size * 3) / 4);  	

	    for ( i=0; i < lines; i++ )
	    {
		    //copia uma linha ou um pouco mais caso não seja divisível por 
		    memcpy32 ( p, q, count );
		    
			q += (Width * 3);
	 	    p += (Width * 3);
	    };
	}

	//se não for divisível por 4.
	if( ((line_size * 3) % 4) != 0 )
	{

        //count = (line_size * 3);  		
	
	    for ( i=0; i < lines; i++ )
	    {
		    memcpy ( (void *) p, (const void *) q, (line_size * 3) );
		    q += (Width * 3);
		    p += (Width * 3);
	    };	
	}  		
	
	/*
	
	for ( i=0; i < lines; i++ )
	{
		memcpy( p, q, (line_size * 3) );
		q += (Width * 3);
		p += (Width * 3);
	};	
	*/
}


// Inicializando a estrutura de gerenciamento de retângulo salvo.

int initialize_saved_rect (void){

	printf ("initialize_saved_rect:\n");
	
	// Alocando memória para a estrutura de gerenciamento do retângulo.

    SavedRect = (void *) kmalloc ( sizeof(struct saved_rect_d) );   

    if ( (void *) SavedRect ==  NULL ){
        panic ("initialize_saved_rect: struct");

    } else {
     
        // 800x600x3 (resolução máxima) 351+ páginas.
		//com isso poderemos salvar uma tela nessa resolução.
		SavedRect->buffer_address = (void *) allocPages (360);
	
	    if ( (void *) SavedRect->buffer_address == NULL )
	    {
		    panic ("initialize_saved_rect: buffer fail");
	    }

        SavedRect->x = 0; 
	    SavedRect->y = 0;
		SavedRect->width = 0;
		SavedRect->height = 0;
		
		SavedRect->pixels = 0;
		SavedRect->bytes = 0;
		SavedRect->bpp = 0;
		
		SavedRect->full = 0;   //empty
		
		
		//#todo: limpar o buffer ???
		
	    //...
	};		

	//#debug
	printf ("initialize_saved_rect: done\n");
	//refresh_screen();

	//while (1){ asm ("hlt"); }
	
    return 0;
}


//#testando ...
//salvar um retângulo no buffer será semelhante ao método de 
//salvar um bmp em um arquivo.

int 
save_rect ( unsigned long x, 
            unsigned long y, 
            unsigned long width, 
            unsigned long height )
{
	
	
        //#debug
        //Ok. está pegando os valores certos.
        //printf ("l=%d t=%d w=%d h=%d \n", x, y, width, height );
        //refresh_screen();
        //while(1){}


    if ( (void *) SavedRect ==  NULL )
    {
        printf ("save_rect: SavedRect\n");
        return (int) 1;

    }else{

        if ( (void *) SavedRect->buffer_address == NULL )
        {
            panic ("save_rect: buffer fail");
        }
    };


    // ## transferindo ... ##
    //======================
    //do backbuffer para o buffer de salvamento.


    void *p = (void *) SavedRect->buffer_address;    //(buffer para salvar)
    const void *q = (const void *) BACKBUFFER_ADDRESS;

	//register unsigned int i;
    unsigned int i;

    unsigned int line_size, lines;

	// = 3; //24bpp
    int bytes_count;

    unsigned int offset1;  
    unsigned int offset2;  

    unsigned long Width = (unsigned long) screenGetWidth ();
    unsigned long Height = (unsigned long) screenGetHeight ();

    int count; 


   
        
    /*
    //#isso funcionou usando o buffer de salvamento.
    refresh_rectangle2 ( 0, 0, 400, 400, SavedRect->buffer_address, BACKBUFFER_ADDRESS );
    refresh_rectangle2 ( 0, 0, 800, 600, BACKBUFFER_ADDRESS, SavedRect->buffer_address);
    //move do backbuffer para o lfb
    refresh_rectangle ( 0, 0, 800, 600); 
    while(1){}
    */
    
    
    // #test
    // Salvando 
    
    refresh_rectangle2 ( x, y, width, height, 
        (unsigned long) SavedRect->buffer_address, 
        (unsigned long) BACKBUFFER_ADDRESS );
    return 0;


    //
    //   --------- CUT HERE ------------
    //





    line_size = (unsigned int) width;    //passado por argumento
    lines = (unsigned int) height;       //passado por argumento


	switch (SavedBPP)
	{
		case 32:
		    bytes_count = 4;
		    break;
		
		case 24:
		    bytes_count = 3;
			break;

		default:
		    printf ("save_rect: default\n");
		    return 1;
	};





	//atualizando o offset do backbuffer
    //offset1 = 0;
	//offset1 = (unsigned int) BUFFER_PIXEL_OFFSET( x, y );
    offset1 = (unsigned int) ( (bytes_count*SavedX*(y)) + (bytes_count*(x)) );

	//configurando o offset do buffer de salvamento.
	offset2 = 0;


	p = (void *) (p + offset2);
	q = (const void *) (q + offset1);


    /*
    //#debug
    //O off1 apresentou um valor alto.
    //pois é o valor do offset do backbuffer que será copiado para o
    //buffer de salvamento.
    //printf ("off1=%d off2=%d ",offset1, offset2);
    //refresh_screen();
    //while(1){}
    */

	//não precisa de sincronização pois não estamos enviando para o LFB.
	//vsync ();


	//(line_size * 3) é o número de bytes por linha. 
	//#todo: usar bytes_count


	//se for divisível por 4.
	if ( ((line_size * 3) % 4) == 0 )
	{
        count = ((line_size * 3) / 4); 

	    for ( i=0; i < lines; i++ )
	    {
		    //copia uma linha ou um pouco mais caso não seja divisível por 
		    memcpy32 ( p, q, count );
		    
			q += (Width * 3);
	 	    p += (Width * 3);
	    };
	    
	    return 0;
	}


	//se não for divisível por 4.
	if ( ((line_size * 3) % 4) != 0 )
	{

        //count = (line_size * 3); 
	
	    for ( i=0; i < lines; i++ )
	    {
		    memcpy ( (void *) p, (const void *) q, (line_size * 3) );
		    
		    q += (Width * 3);
		    p += (Width * 3);
	    };
	    
	    return 0;
	} 


	/*
	for ( i=0; i < lines; i++ )
	{
		memcpy( p, q, (line_size * 3) );
		q += (Width * 3);
		p += (Width * 3);
	};	 
    */



    /*
    //#debug
    //printf ("save_rect: done\n");
    printf ("Show buffer: \n");
    unsigned char *__p = (unsigned char *) SavedRect->buffer_address;
    int z;
    for (z=0; z<100; z++)
    {
        printf ("%x ",__p[z]);
    }
    refresh_screen();
    while(1){}
    */


    return 0;
}


/*
 * show_saved_rect:
 *      Pintar no backbuffer o retângulo salvo.
 *      Semelhante ao processo de decodificar um bmp, copiando 
 * do arquivo para o backbuffer.
 * Esses argumentos representam o posicionamento desejado do 
 * retângulo no backbuffer. 
 */

int 
show_saved_rect ( unsigned long x, 
                  unsigned long y, 
                  unsigned long width, 
                  unsigned long height )
{


	// Checando a estrutura que tem informações 
	// sobre o retângulo salvo.
	
	if ( (void *) SavedRect ==  NULL )
    {
        printf ("show_saved_rect: SavedRect\n");
	    return (int) 1;
		
	} else {

	    if ( (void *) SavedRect->buffer_address == NULL )
	    {
		    panic ("show_saved_rect: buffer");
	    }
    };
    
    
    
    //#test
    //copiando do buffer de salvamento para o backbuffer.
    refresh_rectangle2 ( x, y, width, height, 
        (unsigned long) BACKBUFFER_ADDRESS, 
        (unsigned long) SavedRect->buffer_address);    
    return 0;
    
    
    //
    //  ----- CUT HERE -------------
    //

	
    //
    // ## Transferindo ... ##
    //
	
	void *p = (void *) BACKBUFFER_ADDRESS;
	const void *q = (const void *) SavedRect->buffer_address;

	//register unsigned int i;
	unsigned int i;
	
	int count; 
	
	// = 3; //24bpp
	int bytes_count;  
	
	unsigned int offset1;  //offset dentro do buffer de salvamento.
	unsigned int offset2;  //offset dentro do backbuffer
	
	unsigned long Width = (unsigned long) screenGetWidth();
	unsigned long Height = (unsigned long) screenGetHeight();

	unsigned int line_size, lines;
	
	line_size = (unsigned int) width; //passado por argumento
	lines = (unsigned int) height;    //passado por argumento
	
	
	switch (SavedBPP)
	{
		case 32:
		    bytes_count = 4;
		    break;
		
		case 24:
		    bytes_count = 3;
			break;
	};



   //p backbuffer
	offset1 = (unsigned int) ( ( bytes_count * SavedX * (y) ) + ( bytes_count * (x) ) );


    //q buffer de salvamento.
    //o conteúdo salvo está no início do buffer de salvamento
	offset2 = 0;


    p = (void *) (p + offset1);          //backbuffer.
    q = (const void *) (q + offset2);    //buffer de salvamento


    /*
    //#debug
    //copiando todo o buffer de salvamento no backbuffer,
    //e mostrando o backbuffer.
    //memcpy32 ( (void *) BACKBUFFER_ADDRESS, (const void *) SavedRect->buffer_address, 
    //    (Width * 3)*400);
    //refresh_screen();
    //while(1){}
    */
 
    // #importante:
	// Não precisa de sincronização pois não estamos enviando para o LFB.
	// vsync ();
	
	//(line_size * 3) é o número de bytes por linha. 
	
	//se for divisível por 4.
	if ( ((line_size * 3) % 4) == 0 )
	{
        count = ((line_size * 3) / 4);

	    for ( i=0; i < lines; i++ )
	    {
		    //copia uma linha ou um pouco mais caso não seja divisível por 
		    memcpy32 ( p, q, count );
		    
			q += (Width * 3);
	 	    p += (Width * 3);
	    };
	}

	//se não for divisível por 4.
	if ( ((line_size * 3) % 4) != 0 )
	{

        //count = (line_size * 3);

	    for ( i=0; i < lines; i++ )
	    {
		    memcpy ( (void *) p, (const void *) q, (line_size * 3) );
		    
		    q += (Width * 3);
		    p += (Width * 3);
	    };
	}


    //#debug
    //printf ("show_saved_rect: done\n");

    return 0;
}



/*
 ************************* 
 * scroll_screen_rect:
 * 
 *     Scroll a rectangle. ?
 */

// Helper function to scroll routine.
// Called by console_scroll() in tty/console.c

void scroll_screen_rect (void){

    register unsigned int i=0;

    unsigned int line_size=0;  // w 
    unsigned int lines=0;      // h

    unsigned int offset=0;

    // Device info.
    unsigned long deviceWidth  = (unsigned long) screenGetWidth();
    unsigned long deviceHeight = (unsigned long) screenGetHeight();


    //int cWidth = get_char_width ();
    int cHeight = get_char_height ();

	// = 3; 
	//24bpp
    int bytes_count = 0;
    
    int count = 0; 



    // #debug
    //if(cHeight == 8)
        //debug_print(">>8\n");

    // #debug
    //if(cHeight == 16)
        //debug_print(">>16\n");


    line_size = (unsigned int) deviceWidth; 
    lines     = (unsigned int) deviceHeight;

    switch (SavedBPP)
    {
        case 32:  bytes_count = 4;  break;
        case 24:  bytes_count = 3;  break;
        //...

        default:
            panic("scroll_screen_rect: SavedBPP");
            break;
    };


    // Destination and Source.
    // Destination is the first line.
    // Source is the second line. It has the height of a char.

    void *Dest = (void *) BACKBUFFER_ADDRESS;
    const void *Src  = (const void *) BACKBUFFER_ADDRESS + ( bytes_count * SavedX * cHeight ) ;


    //
    // Copy.
    //

	//#importante
	//É bem mais rápido com múltiplos de 4.	
	
	//se for divisível por 4.
    if ( ((line_size * bytes_count) % 4) == 0 )
    {
        count = ((line_size * bytes_count) / 4); 

        // Copia uma linha, quatro bytes de cada vez.  
        for ( i=0; i < lines; i++ )
        {
            memcpy32 (Dest,Src,count);

            Src  += (deviceWidth * bytes_count);
            Dest += (deviceWidth * bytes_count);
        };
        return;
    }


	//se não for divisível por 4.
    if ( ((line_size * bytes_count) % 4) != 0 )
    {
        // Copia a linha, um bytes por vez.
        for ( i=0; i < lines; i++ )
        {
            memcpy ( 
                (void *) Dest, 
                (const void *) Src, 
                (line_size * bytes_count) );

            Src  += (deviceWidth * bytes_count);
            Dest += (deviceWidth * bytes_count);
        };
    }
}






//
// End.
//
