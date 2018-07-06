/*
 * File: gws\gws\pixel.c
 *
 * Descrição:
 *     Rotinas de pintura de pixel.
 *     Faz parte do módulo Window Manager do tipo MB.
 *
 * *IMPORTANTE
 * Obs: Se uma estrutura de janela for passada como argumento
 *      na hora de colocar um pixel então usaremos o buffer dedicado
 * indicado nessa estutura. Caso contrário, se não for passado
 * um ponteiro pra estrutura de janela, ou se estrutura não tem um 
 * ponteiro para buffer dedicado, então usaremos um buffer padrão,
 * que sempre será o buffer dedicado da janela principal, gui->main.
 * que podemos chamar de 'desktop', mas não é a estrutura de desktop
 * como a conhecemos. 
 *
 * Uma solução elegante seria ter ponteiros para buffers na 
 * estrutura da gui->, assim podemos alocar memória para um buffer
 * genérico, e seu ponteiro ser passado para a janela que se interessar 
 * por ela. As estruturas de user session, windos station, e desktop
 * tambem podem ter ponteiros para buffers genéricos. Podemos também
 * ter uma variável global para isso e também estrututra de buffer.
 *
 *
 * A solução mais simples é passar para a rotina de pintura o buffer desejado,
 * não a estrutura de buffer e sim apenas o ponteiro para o buffer. se bem que 
 * se fosse passado um ponteiro para um estrutura de buffer seria bem mais seguro.
 *
 * Versão 1.0, 2015.
 */

 
#include <kernel.h>


//
// Variáveis importadas. 
//


//Herdadas do Boot Loader.
// De onde vem isso ?? head.s
// @todo: Devemos chamar o módulo hal para obtermos esses valores.
//depois salvamos em variáveis internas usadas pela gui.
extern unsigned long SavedBootBlock;
extern unsigned long SavedLFB;
extern unsigned long SavedX;
extern unsigned long SavedY;
extern unsigned long SavedBPP; 

//Outras.
// De onde vem isso ??
// @todo: Devemos chamar o módulo hal.
extern void gui_buffer_putpixel();


//
// @todo:
// Criar a rotina guiRefreshScreen(); ??
//
//

/*
//Pinta um pixel diretamente na memória de vídeo.
//Obs: A sincronização vertical deve ser feita na hora de pintar
//um caractere, e não a cada pixel pintado.
//Porém se um aplicativo em user mode desejar pintar apenas um pixel,
//é necessário fazer a sincrnização vertical.
void pixelDirectPutPixel( void* FrontBuffer, unsigned long x, unsigned long y, unsigned long color );
void pixelDirectPutPixel( void* FrontBuffer, unsigned long x, unsigned long y, unsigned long color )
{
    return; //ainda não implementada.							  
}
*/


										 
//Pinta um pixel em um buffer de janela.
void 
pixelPutPixelWindowBuffer( void *buffer, 
                           unsigned long x, 
						   unsigned long y, 
						   unsigned long color )
{
	return; //@todo: Ainda não implementada.					  
};

										 
/*
 * *IMPORTANTE
 * Obs: Se uma estrutura de janela for passada como argumento
 *      na hora de colocar um pixel então usaremos o buffer dedicado
 * indicado nessa estutura. Caso contrário, se não for passado
 * um ponteiro pra estrutura de janela, ou se estrutura não tem um 
 * ponteiro para buffer dedicado, então usaremos um buffer padrão,
 * que sempre será o buffer dedicado da janela principal, gui->main.
 * que podemos chamar de 'desktop', mas não é a estrutura de desktop
 * como a conhecemos.
*/										 
void 
pixelPutPixelDedicatedWindowBuffer( struct window_d *window, 
                                    unsigned long x, 
									unsigned long y, 
									unsigned long color )
{
	//O buffer será selecionado por essa rotina ficará aqui
	void *buff;
	
	//Se temos uma estrutura de janela, essa estrutura pode
	//conter um ponteiro para um buffer dedicado de janela.
	if( (void *) window == NULL )
	{
		buff = NULL;
		goto useDefaultBuffer;
	}else{
		
		//Se o ponteiro para buffer dedicado indicado na estrutura
		//for inválido.
		if( (void*) window->DedicatedBuffer == NULL ){
			goto useDefaultBuffer;
		}
		
		//Ok.
		//O ponteiro para o buffer dedicado parece válido.
		//@todo: A rotina de criação de estrutura de janela
		//tem que alocar dinâmicamente memória para o buffer corretamente.
		//e não pode admitir falha nesse requesito.
		
		
		buff = (void*) window->DedicatedBuffer;
		goto useDedicatedBuffer;
		//
		//
	}
	//Nothing.
	
// Somos obrigados a usar o buffer dedicado da janela principal.	
//@por enquanto isso não será considerado uma falha.
useDefaultBuffer:
	//@todo: pegar o buffer default.
	buff = (void*) gui->defaultWindowDedicatedBuffer1;
	if( (void*) buff == NULL ){
		//@todo: Alocamos memória par a o buffer
		
		//buff = (void*) malloc(SIZE??);
		
		printf("pixelPutPixelDedicatedWindowBuffer:");
		refresh_screen();
		while(1){}
	}
	//...pinta asm_putpixel()
//Aqui conseguimos encontrar o buffer dedicado da janela em questão.	
//O buffer selecionad foi o buffer dedicado da janela. temos que checar.
useDedicatedBuffer:	
	if( (void*) buff == NULL ){
		//@todo: Alocamos memória par a o buffer
		
		//buff = (void*) malloc(SIZE??);
		
		printf("pixelPutPixelDedicatedWindowBuffer:");
		refresh_screen();
		while(1){}
	}
	//pinta. asm_putpixel()
    return;	
}


/*
 ******************************************************
 * my_buffer_put_pixel:
 *     Coloca um pixel o buffer backbuffer. 
 *     Obs: O backbuffer deverá ser o buffer dedicado da janela principal gui->main.     
 *
 * a = cor
 * b = x
 * c = y
 * d = null
 *
 * O lugar dessa rotina é no hal.
 *
 * @todo: Aqui podemos fazer algum tipo de filtro, considerar
 * a métrica do buffer e chamar a rotina de /hal apropriada.
 * Usando o módulo /hal como interface entre
 * a /gui e o hardware.
 */
//void pixelPutPixelBackBuffer( unsigned long ax, unsigned long bx, unsigned long cx, unsigned long dx )
void 
my_buffer_put_pixel( unsigned long ax, 
                     unsigned long bx, 
				     unsigned long cx, 
					 unsigned long dx )
{
    hal_backbuffer_putpixel( ax, bx, cx, dx );
	//return;
};


//pega um pixel no backbuffer
unsigned long get_pixel( unsigned long x,  unsigned long y )
{
	//SALVA A COR
	unsigned long COLOR;
	
	unsigned char *rgba = (unsigned char *) &COLOR;
	
    unsigned char *backbuffer = (unsigned char *) BACKBUFFER_ADDRESS;	
	unsigned long pos = (unsigned long) (y*3*800)+(x*3);
	
	COLOR  = *( unsigned long* )&backbuffer[pos];
	
	//talvez isso seja invertido
	//rgba[3] = backbuffer[pos];
	//rgba[2] = backbuffer[pos+3];
	//rgba[1] = backbuffer[pos+3+3];
	//rgba[0] = backbuffer[pos+3+3+3];

    return (unsigned long) COLOR;	
}


//copia um pixel do backbuffer para o frontbuffer
void refresh_pixel( unsigned long x,  unsigned long y )
{	
	//SALVA A COR
	unsigned long COLOR;
	
	unsigned char *rgba = (unsigned char *) &COLOR;
	
    unsigned char *frontbuffer = (unsigned char *) FRONTBUFFER_ADDRESS;	
	//unsigned long pos = (unsigned long) ( 3 * x * y );

	unsigned long pos = (unsigned long) (y*3*800)+(x*3);
	
	//pego o pixel no backbuffer
	COLOR = get_pixel( x, y );
	
	*( unsigned long* ) &frontbuffer[pos] = COLOR;
	//*( unsigned long* )&frontbuffer[pos] = get_pixel( x, y );

	
	//talvez isso seja invertido
	//frontbuffer[pos]   = rgba[0];
	//frontbuffer[pos+1] = rgba[1];
	//frontbuffer[pos+2] = rgba[2];
	//frontbuffer[pos+3] = rgba[3];
};


//
// End.
//








