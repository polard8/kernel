/*
 * File: rect.c
 *
 * Descrição:
 *     Rotina de pintura de retangulos.
 *     Faz parte do módulo Window Manager do tipo MB.
 *
 * History:
 *    2015 - Created by Fred Nora.
 */


#include <kernel.h>


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
#define BUFFER_PIXEL_OFFSET(x,y) \
( (3*800*(y)) + (3*(x)) )

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
 * drawDataRectangle:
 *     Cria um retângulo no Backbuffer. Em qualquer posição do Backbuffer
 * dado o limite do tamanho da tela.
 *     @todo: Criar rotina para pintar um retângulo em um buffer dedicado.
 *            Toda janela tem um buffer dedicado. O BackBuffer é o buffer
 * dedicado da janela principal. 'gui->main'
 */
void 
drawDataRectangle( unsigned long x, 
                   unsigned long y, 
				   unsigned long width, 
				   unsigned long height, 
				   unsigned long color )
{
	struct rect_d *rect;
	
	//A estrutura base é usada para efetuar essa rotina aqui,
	//e depois permanece suja.
    
    rect->bg_color = color;
   
    //Dimensões.
	rect->x = 0;        
    rect->y = 0;         
    rect->width = width;   
    rect->height = height;    
   
    //Margens.
    rect->left = x;    
    rect->top = y;
    rect->right = rect->left + rect->width;
    rect->bottom = rect->top + rect->height; 

    //Limits.
	//@todo: Repensar os limites para uma janela.
	// Uma janela poderá ser maior que as dimensões de um dispositivo.
	// mas não poderá ser maior que as dimensões do backbuffer.
	// Ou seja: O dedicated buffer de uma janela deve ser menor que
	// o backbuffer.
	
	//#todo: Usar variável para largura.
	
    if ( rect->right > 800 )
	{
        rect->right = 800;
	}	

	/* @todo:
    if( rect->bottom > 600 ){
        rect->bottom = 600;
	};
    */	
  	
    //Pinta as linhas no Backbuffer.  
	while ( height-- )
	{
	    my_buffer_horizontal_line ( rect->left, y, rect->right, 
		    rect->bg_color );
		
		y++;
    };    
};
  
  
  
/*
 * getClientAreaRect:
 *     Obtém o ponteiro da estrutura do retângulo  
 *     da área de cliente da janela ativa.
 *     @todo: oferecer esse serviço para a api.
 */  
void *getClientAreaRect (){
	
    return (void *) rectClientArea;	
};


/*
 * setClientAreaRect:
 *     Inicializa a estrutura do retângulo da área de cliente 
 * da janela ativa.
 */
void setClientAreaRect( unsigned long x, 
                        unsigned long y, 
						unsigned long cx, 
						unsigned long cy )
{
    struct rect_d *r;

	r->x = x;
	r->y = y;
	r->cx = cx;
	r->cy = cy;
	
	//Se a estrutura ainda não foi inicializada.
    if ( (void *) rectClientArea == NULL )
	{
	    return;
	}
	 
    rectClientArea = (void *) r;
};


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
void 
refresh_rectangle ( unsigned long x, 
                    unsigned long y, 
				    unsigned long width, 
				    unsigned long height )
{    
	void *p = (void *) FRONTBUFFER_ADDRESS;		
	void *q = (void *) BACKBUFFER_ADDRESS;

	//register unsigned int i;
	unsigned int i;
	
	unsigned int line_size, lines;
	unsigned int offset;
	unsigned long Width = (unsigned long) screenGetWidth();
	unsigned long Height = (unsigned long) screenGetHeight();	

	line_size = (unsigned int) width; 
	lines = (unsigned int) height;
	offset = (unsigned int) BUFFER_PIXEL_OFFSET( x, y );
	
	p = (void *) (p + offset);    
	q = (void *) (q + offset);    
	 
    vsync ();	
	
	for ( i=0; i < lines; i++ )
	{
		memcpy( p, q, (line_size * 3) );
		q += (Width * 3);
		p += (Width * 3);
	};	
};


// A ideia aqui é efetuar o refresh de um retângulo que esteja em um dado buffer.
void 
refresh_rectangle2 ( unsigned long x, 
                     unsigned long y, 
				     unsigned long width, 
				     unsigned long height,
                     unsigned long buffer1,
                     unsigned long buffer2 )
{    
	void *p = (void *) buffer1;		
	void *q = (void *) buffer2;

	//register unsigned int i;
	unsigned int i;
	
	unsigned int line_size, lines;
	unsigned int offset;
	unsigned long Width = (unsigned long) screenGetWidth();
	unsigned long Height = (unsigned long) screenGetHeight();	

	line_size = (unsigned int) width; 
	lines = (unsigned int) height;
	offset = (unsigned int) BUFFER_PIXEL_OFFSET( x, y );
	
	p = (void *) (p + offset);    
	q = (void *) (q + offset);    
	 
    vsync ();	
	
	for ( i=0; i < lines; i++ )
	{
		memcpy( p, q, (line_size * 3) );
		q += (Width * 3);
		p += (Width * 3);
	};	
};




//inicializando a estrutura de gerenciamento de retângulo salvo.
int initialize_saved_rect (){
	
	//alocando memória para a estrutura de gerenciamento do retângulo.
    SavedRect = (void *) malloc ( sizeof(struct saved_rect_d) );   

    if ( (void *) SavedRect ==  NULL )
    {
	    return (int) 1;	
		
	} else {
     
        // 800x600x3 (resolução máxima) 351+ páginas.
		//com isso poderemos salvar uma tela nessa resolução.
		SavedRect->buffer_address = (void *) allocPageFrames (360);
	
	    if ( (void *) SavedRect->buffer_address == NULL )
	    {
		    printf ("initialize_saved_rect: buffer fail");
	        die ();	
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
	printf("gws-initialize_saved_rect: **** done");
	//refresh_screen();
	
	//while (1){
	//	asm("hlt");
	//}
	
    return (int) 0;	
};



//#testando ...
//salvar um retângulo no buffer será semelhante ao método de 
//salvar um bmp em um arquivo.
int save_rect ( unsigned long x, 
                unsigned long y, 
				unsigned long width, 
				unsigned long height )
{		
    if ( (void *) SavedRect ==  NULL )
    {
	    return (int) 1;
		
	} else {

	    if ( (void *) SavedRect->buffer_address == NULL )
	    {
		    printf ("save_rect: buffer fail");
	        die ();	
	    }
    };

   // ## transferindo ... ##
   //======================

    //do backbuffer para o buffer de salvamento.
	
	void *p = (void *) SavedRect->buffer_address; //(buffer para salvar)		
	void *q = (void *) BACKBUFFER_ADDRESS;

	//register unsigned int i;
	unsigned int i;
	
	unsigned int line_size, lines;
	
	unsigned int offset1;  
	unsigned int offset2;  
	
	unsigned long Width = (unsigned long) screenGetWidth();
	unsigned long Height = (unsigned long) screenGetHeight();	

	line_size = (unsigned int) width; //passado por argumento
	lines = (unsigned int) height;    //passado por argumento
	
	//atualizando o offset do backbuffer
	offset1 = (unsigned int) BUFFER_PIXEL_OFFSET( x, y );
	
	//configurando o offset do buffer de salvamento.
	offset2 = 0;
	
	p = (void *) (p + offset2);    
	q = (void *) (q + offset1);    
	 
    
	//não precisa de sincronização pois não estamos enviando para o LFB.
	//vsync ();	
	
	for ( i=0; i < lines; i++ )
	{
		memcpy( p, q, (line_size * 3) );
		q += (Width * 3);
		p += (Width * 3);
	};	 

    return (int) 0;		
};


//pintar no backbuffer o retângulo salvo vai ser semelhante ao processo 
//de decodificar um bmp, copiando do arquivo para o backbuffer.
// esses argumentos devem representar o posicionamentod esejado do 
//retângulo no backbuffer.
int show_saved_rect ( unsigned long x, 
                      unsigned long y, 
				      unsigned long width, 
				      unsigned long height )
{		
    if ( (void *) SavedRect ==  NULL )
    {
	    return (int) 1;
		
	} else {

	    if ( (void *) SavedRect->buffer_address == NULL )
	    {
		    printf ("save_rect: buffer fail");
	        die ();	
	    }
    };

   // ## transferindo ... ##
   //======================
	
	void *p = (void *) BACKBUFFER_ADDRESS;   	
	void *q = (void *) SavedRect->buffer_address;         

	//register unsigned int i;
	unsigned int i;
	
	unsigned int line_size, lines;
	
	unsigned int offset1;  //offset dentro do buffer de salvamento.
	unsigned int offset2;  //offset dentro do backbuffer
	
	unsigned long Width = (unsigned long) screenGetWidth();
	unsigned long Height = (unsigned long) screenGetHeight();	

	line_size = (unsigned int) width; //passado por argumento
	lines = (unsigned int) height;    //passado por argumento
		

	offset1 = (unsigned int) BUFFER_PIXEL_OFFSET( x, y );
	offset2 = 0;
	
	p = (void *) (p + offset1);    
	q = (void *) (q + offset2);    
	 
    
	//não precisa de sincronização pois não estamos enviando para o LFB.
	//vsync ();	
	
	for ( i=0; i < lines; i++ )
	{
		memcpy( p, q, (line_size * 3) );
		q += (Width * 3);
		p += (Width * 3);
	};	 

    return (int) 0;	
};


/*
int rectInit()
{}  
*/


//
// End.
//
