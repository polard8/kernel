/*
 * File: volume.c 
 *
 * Descrição:
 *     Gerenciador de volumes.
 *     Arquivo principal do Volume Manager.
 *     MB - Módulos incluídos no Kernel Base.
 *
 *     Obs: O Gerenciador de Volumes um módulo muito importante do Kernel.
 *
 * Versão 1.0, 2015, 2016.
 */


#include <kernel.h>


/*
 * volume_init:
 *     Inicializa o volume manager.
 */
int volume_init()
{
    printf("volume_init: Initializing..\n");	

	// Structure.
    volumeinfo = (void*) malloc( sizeof(struct volumeinfo_d) );
	if( (void*) volumeinfo == NULL ){
	    printf("volume_init:");
		refresh_screen();
		while(1){}
	}else{
		
	    //
	    // Bom, como aqui já temos uma estrutura válida,
	    // então podemos completá-la com parâmetros padrões.
	    //
	
	    volumeinfo->volumeId = 0;
	    volumeinfo->volumeUsed = 0;
	    volumeinfo->volumeMagic = 0;
	    //volumeinfo->volumeName = NULL;    //Pointer.		
		//...
	};
	
	//
	// @todo: More ??!
	//

done:	
    return (int) 0;
};


/*
int init_volume_manager();
int init_volume_manager()
{
	volume_init();
    return (int) 0;
};
*/


/*
int volumeInit(){
	;
};
*/


//
//fim.
//


