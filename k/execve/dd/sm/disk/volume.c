/*
 * File: sm\disk\volume.c 
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




//Mostra informações sobre o volume atual.
void volumeShowCurrentVolumeInfo()
{
	printf("The current volume is %d\n",current_volume);
    volumeShowVolumeInfo(current_volume);	
};

/*
 ************************************************
 * volumeShowVolumeInfo:
 *
 */
int 
volumeShowVolumeInfo( int descriptor )
{
	struct volume_d *v;
	
	printf("volumeShowVolumeInfo:\n");
	
    if( descriptor < 0 || descriptor > VOLUME_COUNT_MAX )
	{
		printf("descriptor fail\n");
		goto fail;
	}	
	
	
	v = (struct volume_d *) volumeList[descriptor];
	
	if( (void *) v == NULL )
	{
		printf("struct fail\n");
		goto fail;
		
	}else{
		
		
		if( v->used != 1 || v->magic != 1234 )
		{
			printf("flags fail\n");
			goto fail;
		}
		
		printf("id={%d}\n",v->id);
		
		printf("used={%d}\n",v->used);
		printf("magic={%d}\n",v->magic);
		
		printf("volumeType={%d}\n",v->volumeType);
		
		//#bugbug
		//@todo: Esse nome temos que pegar no diretório raiz.
		printf("name={%s}\n",v->name);
		//printf("");
		//printf("");
		//printf("");
		//printf("");
		//printf("");
		//printf("");
		//printf("");
		goto done;
	};
	
	goto done;
	
	
fail:
    printf("fail\n");
    return (int) 1;

done:
    printf("done\n");
	return (int) 0;
};	



void *volume_get_volume_handle( int number )
{
	//check limts
	if( number < 0 || number >= VOLUME_COUNT_MAX ){
		return NULL;
	}
	return (void *) volumeList[number];
};


void *volume_get_current_volume_info()
{
    if( current_volume < 0 || current_volume > VOLUME_COUNT_MAX ){
	    return NULL;
	}
	
    return (void*) volumeList[VOLUME_COUNT_MAX];	
};




/*
 ***************************************************
 * volume_init:
 *     Inicializa o volume manager.
 */
//int volumeInit()
int volume_init()
{
	
#ifdef KERNEL_VERBOSE
    printf("volume_init: Initializing..\n");
#endif

    //@todo: tem que limpara a lista de volumes.
	int i;
	for( i=0; i<VOLUME_COUNT_MAX; i++)
	{
		volumeList[i] = 0;
	};


    //
	// Inicializando a estrutura do volume 0,
	// que será o VFS.
	// Esse volume será do tipo buffer, então não será 
	// carregado de nenhum disco.
	//

	//
	// Os outros volumes serão montados no volume de vfs.
	//
	
	//
	// O volume de vfs se chamará 'root'
	//
	
	//
	// root: - Volume 0 (vfs)
    // root:/volume0 - Links para o raiz.   
	// root:/volume1 - volume da partição de boot.
	// root:/volume2 - volume da partição de sistema.
	//
	
	// Volume.
	volume_vfs = (void*) malloc( sizeof(struct volume_d) );
	
	if( (void*) volume_vfs == NULL )
	{
	    printf("sm-disk-volume_init:");
		die();
	}else{
		
		//@todo:
		//volume_vfs->objectType = ?;
        //volume_vfs->objectClass = ?;
		
		
		// Será usado pelo VFS.
		volume_vfs->volumeType = VOLUME_TYPE_BUFFER;
		
	    volume_vfs->id = 0;
	    
		volume_vfs->used = (int) 1;
	    volume_vfs->magic = (int) 1234;
	    
		volume_vfs->name = "VOLUME 0";  
        
		volume_vfs->cmd = "root:";
		
		// Não configuraremos por enquanto.
        volume_vfs->volume_info = NULL;

        volumeList[0] = (unsigned long) volume_vfs; 		
	};
	
	
	// Volume.
	volume_bootpartition = (void*) malloc( sizeof(struct volume_d) );
	
	if( (void*) volume_bootpartition == NULL )
	{
	    printf("sm-disk-volume_init:");
		die();
	}else{
		
		//@todo:
		//volume_bootpartition->objectType = ?;
        //volume_bootpartition->objectClass = ?;
		
		
		// Será usado pelo VFS.
		volume_bootpartition->volumeType = VOLUME_TYPE_DISK_PARTITION;
		
	    volume_bootpartition->id = 1;
	    
		volume_bootpartition->used = (int) 1;
	    volume_bootpartition->magic = (int) 1234;
	    
		volume_bootpartition->name = "VOLUME 1";  
        
		volume_bootpartition->cmd = "root:/volume1";
		
		// Não configuraremos por enquanto.
        volume_bootpartition->volume_info = NULL;

        volumeList[1] = (unsigned long) volume_bootpartition; 		
	};
	
	
	// Volume.
	volume_systempartition = (void*) malloc( sizeof(struct volume_d) );
	
	if( (void*) volume_systempartition == NULL )
	{
	    printf("sm-disk-volume_init:");
		die();
	}else{
		
		//@todo:
		//volume_systempartition->objectType = ?;
        //volume_systempartition->objectClass = ?;
		
		
		// Será usado pelo VFS.
		volume_systempartition->volumeType = VOLUME_TYPE_DISK_PARTITION;
		
	    volume_systempartition->id = 2;
	    
		volume_systempartition->used = (int) 1;
	    volume_systempartition->magic = (int) 1234;
	    
		volume_systempartition->name = "VOLUME 2";  
        
		volume_systempartition->cmd = "root:/volume2";
		
		// Não configuraremos por enquanto.
        volume_systempartition->volume_info = NULL;

        volumeList[2] = (unsigned long) volume_systempartition; 		
	};
	
	
	//
	//  selecionando o volume atual.
	//  a partição de boot.
	//  
	//
	current_volume = 1;
	
	
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


//
//fim.
//


