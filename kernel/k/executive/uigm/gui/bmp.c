/*
 * File: bmp.c
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
 * 
 * Histórico: 
 *     Versão 1.0, 2015 - Created. 
 */


#include <kernel.h>


//
// Funções importadas.
//

extern void my_buffer_load_bitmap_16x16();


/* bugbug alloc
void bmpTest();
void bmpTest()
{
	printf("*teste ...\n");
	refresh_screen();
	//unsigned long buf[1024*2]; //3kb
	void *buf;
	
	buf = (void*) malloc( 3*1024);
	if(buf == NULL)
	{
	    printf("alloc.");
		refresh_screen();
		while(1){}
	}
	printf("Loading ...%x \n",(unsigned long)buf);
	refresh_screen();
	carregar_arquivo("FREDFILEBMP",(unsigned long) buf);
	load_bitmap_16x16( (unsigned long) buf, 100,100,0);
	printf("*done.");
	refresh_screen();
	while(1){}
};
*/


/*
 * carrega_bitmap_16x16:
 *    Põe bitmap de tamanho 16x16 no buffer.
 *
 * a - endreço da imagem 
 * b - x
 * c - y 
 * d - null
 *
 * @todo: Deletar, tem outra igual logo abaixo.
 * Obs:   Buffer, não precisa esperar o retraço vertical.
 */
void carrega_bitmap_16x16( unsigned long ax, 
                           unsigned long bx, 
                           unsigned long cx, 
                           unsigned long dx )
{
    load_bitmap_16x16( ax, bx, cx, dx );
    return;				  
};


/*
 * load_bitmap_16x16:
 *     Põe bitmap no backbuffer.
 *
 * Argumentos:
 *     eax = endereço da imagem na memória. 
 *     ebx = x no backbuffer.
 *     ecx = y no backbuffer.
 *     edx = null.
 *
 * Obs: Coloca no backbuffer, por isso não precisa de sincronizar o retraço 
 * vertical.
 *      Talvez um bitmap deva ser colocado em seu próprio buffer dedicado.
 * Ou pintado no buffer dedicado de alguma janela.
 *
 * @todo: Mudar o nome da função para bmpLoad16x16(...).
 */
void load_bitmap_16x16( unsigned long ax, 
                        unsigned long bx,
						unsigned long cx, 
						unsigned long dx )
{
    //todo: Checar parâmetros no header do bmp.
	
	//Passa os argumentos via registradores.
    asm volatile(" \n " :: "a"(ax), "b"(bx), "c"(cx), "d"(dx) );
	
    my_buffer_load_bitmap_16x16();
    return;				  
};


/*
int bmpInit()
{}
*/

//
// End.
//

