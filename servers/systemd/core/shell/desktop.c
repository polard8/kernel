

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


int shellStartDesktopMode (){

	printf ("shellStartDesktopMode: Initializing desktop mode ...\n");
		
	//criamos a barra.
	//lembrando que o ponteiro é global.
	
	shellCreateTaskBar ();
	

    //#todo	
	desktopInitialize ();
	
 	
    //
	// #IMPORTANTE
	// NÃO FAZEMOS LOOP AQUI ....
	// USAREMOS O LOOP DO SHELL.
	// O SHELL CHAMA O PROCEDIMENTO DO DESKTOP CASO A FLAG
	// DEMONSTRE QUE O MODO DESKTOP ESTÁ ATIVADO.
	//

	//Dessa forma, somente inicializaremos e sairemos ...
	
	return 0;
}




