

void set_char_width ( int width );
void set_char_height ( int height );
int get_char_width ();
int get_char_height ();



void my_buffer_char_blt ( unsigned long x, 
                          unsigned long y, 
						  unsigned long color, 
						  unsigned long c );

/*
 ******************************************************
 * drawchar_transparent:
 *     Desenha um caractere sem alterar o pano de fundo.
 */		

void 
gws_drawchar_transparent ( unsigned long x, 
                           unsigned long y, 
                           unsigned long color, 
                           unsigned long c );


/*
 *****************************************************
 * draw_char:
 *     Constrói um caractere 8x8 no buffer.
 *     Desenha um caractere e pinta o pano de fundo.
 */ 

void 
gws_draw_char ( unsigned long x, 
                unsigned long y,  
                unsigned long c,
                unsigned long fgcolor,
                unsigned long bgcolor );





