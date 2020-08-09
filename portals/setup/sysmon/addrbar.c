// Suporte a top bar.



 


#include "sysmon.h"


/*
 * topbarInitializeTopBar:
 *
 */
 
// #obs:
// Ainda refletindo de esse apps deve ou não criar uma topbar.
// A Topbar pode ficar no window manager.
 
void topbarInitializeTopBar (){

    int i;
    unsigned long OldX, OldY;

    //salva cursor antigo.
    OldX = gde_get_cursor_x ();
    OldY = gde_get_cursor_y ();

	gde_set_cursor ( 0, 0 );
	
	for( i=0; i < ((800/8)-1); i++)
	{
		printf (" ");
	};
	
	gde_set_cursor ( 8, 0 );	
	printf ("|TEDITOR");

	gde_set_cursor ( 44, 0 );	
	printf ("|Application for testing system resources");


    gde_set_cursor (OldX,OldY);
}



