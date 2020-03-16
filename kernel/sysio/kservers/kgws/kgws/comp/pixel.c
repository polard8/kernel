/*
 * File: pixel.c
 *
 * Rotinas de mais baixo nível do compositor do servidor kgws.
 * #todo:
 * Lembrando que esse servidor não deve acessar o LFB, para isso
 * usaremos o diálogo com o driver de vídeo através do x-server.
 * See: x/video.c
 * 
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
 * 2015.
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

//extern void gui_buffer_putpixel (void);


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
pixelPutPixelWindowBuffer ( void *buffer, 
                            unsigned long x, 
                            unsigned long y, 
                            unsigned long color )
{
	//return; 
	//@todo: Ainda não implementada.
}



 
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
pixelPutPixelDedicatedWindowBuffer ( struct window_d *window, 
                                     unsigned long x, 
                                     unsigned long y, 
                                     unsigned long color )
{


	//#suspensa.
	
	/*
	//O buffer será selecionado por essa rotina ficará aqui
	void *buff;
	
	//Se temos uma estrutura de janela, essa estrutura pode
	//conter um ponteiro para um buffer dedicado de janela.
	if ( (void *) window == NULL )
	{
		buff = NULL;
		goto useDefaultBuffer;
		
	}else{
		
		//Se o ponteiro para buffer dedicado indicado na estrutura
		//for inválido.
		
		if ( (void *) window->DedicatedBuffer == NULL )
		{
			goto useDefaultBuffer;
		}
		
		//Ok.
		//O ponteiro para o buffer dedicado parece válido.
		//@todo: A rotina de criação de estrutura de janela
		//tem que alocar dinâmicamente memória para o buffer corretamente.
		//e não pode admitir falha nesse requesito.
		
		buff = (void *) window->DedicatedBuffer;
		goto useDedicatedBuffer;
	};
	
	//Nothing.
	
// Somos obrigados a usar o buffer dedicado da janela principal.	
//@por enquanto isso não será considerado uma falha.
useDefaultBuffer:

	//@todo: pegar o buffer default.
	buff = (void *) gui->defaultWindowDedicatedBuffer1;
	
	if ( (void *) buff == NULL )
	{
		//@todo: Alocamos memória par a o buffer
		
		//buff = (void*) malloc(SIZE??);
		
		printf("pixelPutPixelDedicatedWindowBuffer:");
		die();
		//refresh_screen();
		//while(1){}
	};
	
	//...pinta asm_putpixel()
//Aqui conseguimos encontrar o buffer dedicado da janela em questão.	
//O buffer selecionad foi o buffer dedicado da janela. temos que checar.
useDedicatedBuffer:	

	if ( (void *) buff == NULL )
	{
		//@todo: Alocamos memória par a o buffer
		
		//buff = (void*) malloc(SIZE??);
		
		printf("pixelPutPixelDedicatedWindowBuffer:");
		die();
		
		//refresh_screen();
		//while(1){}
	}
	//pinta. asm_putpixel()
	
	*/

    return;
}



/*
 *********************************
 * backbuffer_putpixel:
 *
 *     Ok. 
 *     O servidor kgws pode acessar um backbuffer. Mas não tem acesso
 * ao frontbuffer. Para isso ele precisa usasr o diálogo do driver 
 * de vídeo.
 *      
 * IN: 
 *     color, x, y, 0
 */

void 
backbuffer_putpixel ( unsigned long ax, 
                      unsigned long bx, 
                      unsigned long cx, 
                      unsigned long dx )
{

	// #importante
	// Esse é o original. Isso funciona.
	// Não usar.
	// hal_backbuffer_putpixel ( ax, bx, cx, dx );


	// #test
	// tentando um novo método.
	// usando o endereço virtual do backbuffer.
	// precisamos de uma variável global para isso.

    // # todo
    // Estamos determinando um valor.
    // Precisamos de uma variável de devinição do sistema.
    
    // BACKBUFFER_VA
    // See: /include/kernel/globals/gva.h 
    
    unsigned char *where = (unsigned char *) 0xC0800000;

    unsigned long color = (unsigned long) ax;

    char b, g, r, a;


    // bgra

    b = (color & 0xFF);	
    g = (color & 0xFF00) >> 8;
    r = (color & 0xFF0000) >> 16;
    a = (color >> 24) + 1;


    // Position.

    int x = (int) bx;
    int y = (int) cx;




	// 3 = 24 bpp

    int bytes_count;

    //
    // bpp
    //
    
    // #danger
    // Esse valor foi herdado do bootloader.

    switch (SavedBPP)
    {
		case 32:
		    bytes_count = 4;
		    break;
		
		case 24:
		    bytes_count = 3;
			break;
			
		//#testando
		//case 16:
		//	bytes_count = 2;
		//	break;
		
		//case 8:
		//	bytes_count = 1;
		//	break;
		
		default:
		    panic ("backbuffer_putpixel: SavedBPP");
		    break;
	}
	
	// #importante
	// Pegamos a largura do dispositivo.
	
    int width = (int) SavedX; 

    int offset = (int) ( (bytes_count*width*y) + (bytes_count*x) );

    //
    // BGR and A
    //

    where[offset]    = b;
    where[offset +1] = g;
    where[offset +2] = r;
    if ( SavedBPP == 32 ){ where[offset +3] = a; };

}




/*
 ****
 * lfb_putpixel:
 *
 *    # todo:
 *    Tá errado isso.   
 *    Devemos dialogar com o driver de vídeo e pedir pra ele 
 * acesasr o lfb. 
 * 
 * See: x/video.c __video_lfb_putpixel
 * 
 * IN: 
 *     color, x, y, 0
 */ 


void 
lfb_putpixel ( unsigned long ax, 
               unsigned long bx, 
		       unsigned long cx, 
		       unsigned long dx )
{
	unsigned char *where = (unsigned char *) 0xC0400000;
	
	unsigned long color = (unsigned long) ax;
	
	char b, g, r, a;
	
	b = (color & 0xFF);	
	g = (color & 0xFF00) >> 8;
	r = (color & 0xFF0000) >> 16;
	a = (color >> 24) + 1;
	
	int x = (int) bx;
	int y = (int) cx;

	// = 3; 
	//24bpp
	int bytes_count;
	
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
	
	//#importante
	//Pegamos a largura salva.
	int width = (int) SavedX; 
	
	int offset = (int) ( (bytes_count*width*y) + (bytes_count*x) );
	
	where[offset] = b;
	where[offset +1] = g;
	where[offset +2] = r;

	//teste
	if ( SavedBPP == 32 )
	{
	    where[offset +3] = a;	
	}
}


/*
 * 
 * get_pixel:
 *     Pegando byte do backbuffer.
 * 
 */
 
//#importante:
//pega um pixel no BACKBUFFER
//tem que usar variável pra bytes per pixel e screen width. 
//A ideia é poder pegar os píxel de um retãngulo e salvá los
//para depois devolver ao backbuffer.

unsigned long get_pixel ( unsigned long x,  unsigned long y ){
	
	//SALVA A COR
	unsigned long COLOR;
	
	unsigned char *rgba = (unsigned char *) &COLOR;
	
	unsigned char *backbuffer = (unsigned char *) BACKBUFFER_ADDRESS;

	// = 3; 24bpp
	int bytes_count;

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

	// #importante
	// Usando largura salva.
	
	int width = (int) SavedX; 
		
	unsigned long pos = (unsigned long) (y* bytes_count * width)+(x * bytes_count);	
	
	COLOR = *( unsigned long * ) &backbuffer[pos];
	
    return (unsigned long) COLOR;	
}


//copia um pixel do backbuffer para o frontbuffer
//tem que usar variável pra bytes per pixel e screen width.
//#todo: TESTAR ESSA FUNÇÃO

void refresh_pixel ( unsigned long x,  unsigned long y ){
	
	//SALVA A COR
	unsigned long COLOR;
	
	unsigned char *rgba = (unsigned char *) &COLOR;
	
    unsigned char *frontbuffer = (unsigned char *) FRONTBUFFER_ADDRESS;	
	
	// = 3; 24bpp
	int bytes_count;
	
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

	//#importante
	//Usando largura salva.
	
	int width = (int) SavedX; 	

	unsigned long pos = (unsigned long) (y* bytes_count * width)+(x * bytes_count);
	
	//pego o pixel no backbuffer
	COLOR = get_pixel ( x, y );
		
	//#todo:
	// Checar o limite de pos.
	//unsigned long address = &frontbuffer[pos];
	
	// #bugbug:
	// Isso é potencialmente perigoso para compilar.	
	
	*( unsigned long * ) &frontbuffer[pos] = COLOR;
}


//
// End.
//

