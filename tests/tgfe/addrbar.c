// Suporte a top bar.

#include <types.h>

#include "heap.h"
#include "api.h"

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "status.h"
#include "addrbar.h"

/*
 * topbarInitializeTopBar:
 *
 */
void topbarInitializeTopBar()
{
	int i;
	
	unsigned long OldX, OldY;

	//salva cursor antigo.
	OldX = apiGetCursorX();
    OldY = apiGetCursorY();
	
	//posiciona.#teste
	apiSetCursor( 0, 0 );
	
	for( i=0; i < ((800/8)-1); i++)
	{
		printf(" ");
	};
	
	apiSetCursor( 8, 0 );	
	printf("|TEDITOR");

	apiSetCursor( 44, 0 );	
	printf("|Application for testing system resources");
	
//done:
    apiSetCursor(OldX,OldY);
   // return;	
};



