/*
 * File: gws/gws/line.c
 *
 * Descrição:
 *     Rotinas de pintura de linha.
 *     Faz parte do módulo Window Manager do tipo MB.
 *
 * History:
 *     2015 - Created by Fred Nora.
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


/*
 * lineDrawHorizontalLineWindowBuffer:
 *     Pinta uma linha horizontal no buffer da janela.
 *     Serve para pintar janelas que irão direto do seu buffer para o LFB da 
 * memória de vídeo, sem passar pelo back buffer. (OVERLAPPED)
 *
 */
/* 
void lineDrawHorizontalLineWindowBuffer(struct window_d *window,
                                        unsigned long x1,
										unsigned long y,
										unsigned long x2,
										unsigned long color );
										
void lineDrawHorizontalLineWindowBuffer(struct window_d *window,
                                        unsigned long x1,
										unsigned long y,
										unsigned long x2,
										unsigned long color )
{
    return;	
}
*/



/* my_buffer_horizontal_line:
 *     Draw a horizontal line on backbuffer. */

void 
my_buffer_horizontal_line( unsigned long x1,
                           unsigned long y, 
						   unsigned long x2,  
						   unsigned long color )
{
	while (x1 < x2){
		
		backbuffer_putpixel ( color, x1, y, 0 );
        x1++;  
    }
};

					  
void 
refresh_horizontal_line ( unsigned long x1,
                          unsigned long y, 
	  				      unsigned long x2 )
{
	
	int bytes_count;
	
	switch (SavedBPP)
	{
		case 32:
		    bytes_count = 4;
		    break;
		
		case 24:
		    bytes_count = 3;
			break;
			
		//#todo 
		//#bugbug	
		
		default:
			break;
	}
	
	//800;
	int width = (int) SavedX;  	
	
	void *s = (void *) (BACKBUFFER_ADDRESS)  + (y * bytes_count * width) + (x1 * bytes_count);
    void *d = (void *) (FRONTBUFFER_ADDRESS) + (y * bytes_count * width) + (x2 * bytes_count);
	
	// ??
	// Não pode ser isso. 
	// Tem que ser uma string de tamanho definido.
	// strcpy(d,s);	
	
	unsigned long size = (unsigned long) ( (x2-x1)*3 ); 
	
	memcpy ( (void *) d, (const void *) s, size );
};


//
// End.
//

