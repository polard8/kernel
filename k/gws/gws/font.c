/*
 * File:  font.c Gerenciador de fontes.
 *
 *          
 */


#include <kernel.h>


int dummyzzzfontstuff;


void 
gwsSetCurrentFontAddress( unsigned long address )
{
	gws_currentfont_address = (unsigned long) address;
};

unsigned long
gwsGetCurrentFontAddress()
{
	return (unsigned long) gws_currentfont_address;
};

//
// End.
//

