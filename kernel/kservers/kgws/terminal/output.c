
//output.c

// output size for terminal kserver

#include <kernel.h>


void terminalPutChar ( int c ){
	
	int cWidth = get_char_width ();
	int cHeight = get_char_height ();
	
	if ( cWidth == 0 || cHeight == 0 )
	{
		//#debug
		printf ("servicesPutChar:");
		die ();
	}
	
    // Desenhar o char no backbuffer
	// Copiar o retêngulo na memória de vídeo.
	
	// flag on.
	stdio_terminalmode_flag = 1;  
	
	putchar ( (int) c );
	refresh_rectangle ( g_cursor_x * cWidth, g_cursor_y * cHeight, 
		cWidth, cHeight );
	
	// flag off.
	stdio_terminalmode_flag = 0;  
}


