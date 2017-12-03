/*
 * Arquivo: bmp.h
 *
 * Descrição:
 *     Header para rotinas de bmp.
 *
 *    Versão 2015.
 */

//mostra na tela uma imagem bmp carregada na memória. 
void bmpDisplayBMP( void *address, unsigned long x, unsigned long y, int width, int height );

void load_bitmap_16x16( unsigned long ax, 
                        unsigned long bx, 
						unsigned long cx, 
						unsigned long dx );
						
void carrega_bitmap_16x16( unsigned long ax, 
                           unsigned long bx, 
						   unsigned long cx, 
						   unsigned long dx );
						   
//
//fim.
//


