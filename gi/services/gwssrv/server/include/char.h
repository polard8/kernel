
#ifndef __CHAR_H
#define __CHAR_H


// Draw char support
int gcharWidth;
int gcharHeight;



void charSetCharWidth ( int width );
void charSetCharHeight ( int height );
int charGetCharWidth ();
int charGetCharHeight ();



void 
charBackbufferCharBlt ( 
    unsigned long x, 
    unsigned long y, 
    unsigned long color, 
    unsigned long c );


/*
 ******************************************************
 * drawchar_transparent:
 *     Desenha um caractere sem alterar o pano de fundo.
 */

void 
charBackbufferDrawcharTransparent ( 
    unsigned long x, 
    unsigned long y, 
    unsigned long color, 
    unsigned long c );


/*
 *****************************************************
 * draw_char:
 *     Constrói um caractere 8x8 (configurável) no buffer.
 *     Desenha um caractere e pinta o pano de fundo.
 */ 

void 
charBackbufferDrawchar ( 
    unsigned long x, 
    unsigned long y,  
    unsigned long c,
    unsigned long fgcolor,
    unsigned long bgcolor );
    

int gwssrv_init_char(void);

#endif


//
// End.
//







  


