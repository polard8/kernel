/*
 * File: gws\gws\line.c
 *
 * Descrição:
 *     Rotinas de pintura de linha.
 *     Faz parte do módulo Window Manager do tipo MB.
 *
 * History:
 *     2015 - Created by Fred Nora.
 */


#include <kernel.h>



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


//@todo: draw h line  x y width

/*
 * my_buffer_horizontal_line:
 *     Pinta uma linha horinzontal no backbuffer.
 */
void 
my_buffer_horizontal_line( unsigned long x1,
                           unsigned long y, 
						   unsigned long x2,  
						   unsigned long color )
{
	while(x1 < x2){
        my_buffer_put_pixel( color, x1, y, 0 );
        x1++;  
    }
	//return;
};

//@todo: ??						  
void 
refresh_horizontal_line( unsigned long x1,
                         unsigned long y, 
	  				     unsigned long x2 )
{
	void *s = (void *) (BACKBUFFER_ADDRESS)  + (y*3*800) + (x1*3);
    void *d = (void *) (FRONTBUFFER_ADDRESS) + (y*3*800) + (x2*3);
	
	// ??
	// Não pode ser isso. Tem que ser uma string de tamanho definido.
	// strcpy(d,s);	
	
	unsigned long size = (unsigned long) ( (x2-x1)*3 ); 
	
	memcpy( (void *) d, (const void *) s, size );
	//return;
};



//OPÇÕES
//bcopy(char *from, char *to, int len)
//strcpy(char *to, const char *from)
//memcpy(void *v_dst, const void *v_src, unsigned long c)
//strcpy(char *to, const char *from)
//fim.
//
