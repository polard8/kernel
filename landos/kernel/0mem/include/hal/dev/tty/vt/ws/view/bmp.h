/*
 * File: bmp.h
 *
 *    Header para rotinas de BMP.
 *
 * History:
 *    2015 - Created by Fred Nora.
 *           24bpp support. 
 *    2018 - 4bpp, 8bpp, 32bpp support.
 */
 
 
/* "MB" */ 
#define BMP_TYPE 0x4D42        
 
#define  BMP_CHANGE_COLOR_NULL  0
#define  BMP_CHANGE_COLOR_TRANSPARENT  1000
#define  BMP_CHANGE_COLOR_SUBSTITUTE   2000
//...
  
 
//flag que avisa que dve haver alguma mudança nas cores. 
int bmp_change_color_flag; 
 
//salva-se aqui uma cor para substituir outra. 
unsigned long bmp_substitute_color; 
 
//cor selecionada para ser substituída ou ignorada. 
unsigned long bmp_selected_color;  
 
/* ## Cancelada ! ## */
static unsigned long cga_16colors_palette[1] = { 0x000000, };

/* ## Cancelada ! ## */
static unsigned long vga_256colors_palette[1] = { 0x00000000, };



      

/*
 ******************************************************
 * bmpDirectDisplayBMP:
 *
 * Mostra na tela uma imagem bmp carregada na memória. (no LFB)
 * 
 * IN:
 *     address = endereço base
 *     x       = posicionamento 
 *     y       = posicionamento
 *
 */
int bmpDirectDisplayBMP( char *address, 
                   unsigned long x, 
				   unsigned long y );


/*
 ******************************************************
 * bmpDisplayBMP:
 *
 * Mostra na tela uma imagem bmp carregada na memória. no backbuffer()
 * 
 * IN:
 *     address = endereço base
 *     x       = posicionamento 
 *     y       = posicionamento
 *
 */
int bmpDisplayBMP( char *address, 
                   unsigned long x, 
				   unsigned long y );
				   
int bmpDisplayMousePointerBMP( char *address, 
                               unsigned long x, 
				               unsigned long y );
							   
							   
//mostra no lfb
//levando em consideração tratamento de transparência.
int bmpDisplayCursorBMP( char *address, 
                         unsigned long x, 
				         unsigned long y );
					
						   
//
// End.
//


