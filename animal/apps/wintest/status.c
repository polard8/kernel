// Suporte a status bar.



#include "wintest.h"


/*
 * statusInitializeStatusBar:
 *
 */
 
void statusInitializeStatusBar (){
	
	int i;
	unsigned long OldX, OldY;

	//salva cursor antigo.
	OldX = apiGetCursorX();
    OldY = apiGetCursorY();
	
	//posiciona.#teste
	apiSetCursor( 0, (600/8) -1 );
	
	for( i=0; i < ((800/8)-1); i++)
	{
		printf (" ");
	};
	
	apiSetCursor( 8, (600/8) -1 );	
	printf("|# Status Bar offset 8.");

	apiSetCursor( 44, (600/8) -1 );	
	printf("|# Status Bar  offset 44.");
	
done:
    apiSetCursor (OldX,OldY);
    return;	
}


void update_statuts_bar ( char *string1, char *string2 ){
	
	int i;
	unsigned long OldX, OldY;

	//salva cursor antigo.
	OldX = apiGetCursorX();
    OldY = apiGetCursorY();
	
	//posiciona.#teste
	apiSetCursor( 0, (600/8) -1 );
	
	for( i=0; i < ((800/8)-1); i++)
	{
		printf(" ");
	};
	
	apiSetCursor( 8, (600/8) -1 );	
	printf(string1);

	apiSetCursor( 44, (600/8) -1 );	
	printf(string2);
	
done:
    apiSetCursor (OldX,OldY);	
}


