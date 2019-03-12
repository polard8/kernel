

// gerenciamento do desktop,
// manipulação dos ícones no desktop.


#include "shell.h" 


//desktop folders.

#ifndef PDESKTOPFOLDER
#define PDESKTOPFOLDER "root:/volume0"
#endif
char *primary_desktop_folder = PDESKTOPFOLDER;

#ifndef SDESKTOPFOLDER
#define SDESKTOPFOLDER "root:/volume1/users/fred/desktop"
#endif
char *secondary_desktop_folder = SDESKTOPFOLDER;



int desktop_running = 0;


 





int desktopInitialize (){
	
	printf("Initializing desktop ...\n");
	printf("%s\n",primary_desktop_folder);
    printf("%s\n",secondary_desktop_folder);	
	
	return 0;
};



/*
 * desktop_loop:
 *     Loop de mensagens no modo desktop.
 */
int desktop_loop(){

    return 0;
}


// Procedimento de janela do modo desktop.
unsigned long 
desktopProcedure ( struct window_d *window, 
                 int msg, 
 			     unsigned long long1, 
				 unsigned long long2 )
{
	printf ("Desktop procedure \n");
    return 0;
}




