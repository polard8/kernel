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
 * 2015 - Created by Fred Nora.
 * 2018 - Revision.
 *
 */


#include <kernel.h>


//
//    ### disk support ###
//


//Mostra informações sobre o disco atual.
void diskShowCurrentDiskInfo (){
	
	printf ("The current disk is %d\n", current_disk );
	diskShowDiskInfo(current_disk);
};


//Mostra informações sobre um disco dado seu descritor.
int diskShowDiskInfo ( int descriptor ){
	
	struct disk_d *d;
	
	//#debug
	printf("diskShowDiskInfo:\n\n");
	
	
    if ( descriptor < 0 || descriptor > DISK_COUNT_MAX )
	{
		printf("descriptor fail\n");
		goto fail;
	}		
	
	d = (struct disk_d *) diskList[descriptor];
	
	if ( (void *) d == NULL )
	{
		printf("struct fail\n");
		goto fail;
		
	} else {
		
		if ( d->used != 1 || d->magic != 1234 ){
			
			printf("flags fail\n");
			goto fail;
		}		
		
		printf ("id={%d} used={%d} magic={%d} \n", d->id, d->used, d->magic );
		
		printf ("diskType={%d}\n", d->diskType );
		printf("name={%s}\n", d->name );		
		//...
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



/*
 * disk_get_disk_handle:
 *     Obtem o ponteiro da estrutura dado o descritor.
 */
void *disk_get_disk_handle ( int number ){
	
	if ( number < 0 || number >= DISK_COUNT_MAX ){
		return NULL;
	}
	
	return (void *) diskList[number];
};


/* #deletar */
void *disk_get_current_disk_info (){
	return NULL;
};



/*
 ********************************************************
 * disk_init:
 *     Inicializa o Disk Manager.
 *     Que é um módulo do tipo MB.
 *
 */
 
//int diskInit() 

int disk_init (){

	int i=0;

	
#ifdef KERNEL_VERBOSE	
    printf("disk_init: Initializing..\n");
#endif	

    //Limpar lista.	
	
	for ( i=0; i<DISK_COUNT_MAX; i++ ){
		
		diskList[i] = 0;
	};
	
 
	//
	//  ## disk ##
    //
	
	//#importante
	//Essa estrutura é vital, não podemos ficar sem ela.
	
	storage->d = (void *) malloc( sizeof(struct disk_d) );
	
	if( (void *) storage->d == NULL )
	{
		panic ("sm-disk-disk_init:");
		
	}else{
		
		//@todo:
		//disk_conductor->objectType = ?;
		//disk_conductor->objectClass = ?;
		
		storage->d->diskType = DISK_TYPE_NULL;
		
	    storage->d->id = 0;
	    
		storage->d->used = (int) 1;
	    storage->d->magic = (int) 1234;
	    
		storage->d->name = "DISK 0";
		
		storage->d->next = NULL;
		
		//global
	    current_disk = 0;
	
		//atualiza a lista
		diskList[current_disk] = (unsigned long) storage->d;
	};	
	
    //
	//@todo: Nothing more ?!!
	//
	
//done:

    printf("Done\n");
	
    return (int) 0;
};



/*
 * init_test_disk:
 *     Testando operações com disco.
 *
 *     @todo: Essa rotina pode virar um aplicativo de teste.
 *
 * + Carrega o arquivo KCONFIG.TXT se estiver presente e 
 *   sonda informações de configuração contidas nele, exibindo as
 *   informações.
 * 
 */
void init_test_disk (){
	
	/*@todo: Teste desse tipo pode ser feito em user mode.*/
	
 	/*
    int Index = 0;
	//int fileSize = 0;
	void *addr;
	
	//Deve existir uma estrutura de propriedades do arquivo,
	//como tamanho ...

	
	//@todo: testando lock
	//taskswitch_lock();
	
	printf("init_test_disk: Testing..\n");
	
	//
	// Alocando no heap do kernel. (Root dir de 32 setores).
	//
	
	//@todo: Usar constantes ou variáveis para esses valores.
	
	addr = (void *) malloc(512*32); 
	if( (void *) addr ==  NULL)
	{
	    printf("init_test_disk: error\n");
		
		free(addr);     //@todo *** Cuidado (testando free()).
		
		refresh_screen();
		//while(1){}
		return;
	}
	else
	{		
	    printf("init_test_disk: Loading file..\n");
		fsLoadFile("KCONFIG TXT", (unsigned long) addr);
		printf(addr);	   		
	};
	
	
	//
	// buffer. @todo: Usar ioBuffers.
	//
	
	
	unsigned char *buffer = (unsigned char *) addr;			

	
	
	//@todo: Checar esse valor máximo.
	
	Index = 0;
	while(Index < 128)
	{
	    if( buffer[Index] == 'U')
        {
			if( buffer[Index +1] == 'S' &&
                buffer[Index +2] == 'E' &&
                buffer[Index +3] == 'R' &&
                buffer[Index +4] == '='	)
			{
			    printf("UserName={%s}\n", &buffer[Index+5]);	
			};
			
		};			
		
		Index++;
	};
	
	
//checkingMBR:	
	fsCheckMbr();    //Check MBR.
	
	
	
	//read_lba( FAT16_ROOTDIR_ADDRESS + b, FAT16_ROOTDIR_LBA + i);  

	//@todo: Testando unlock
	//taskswitch_unlock();

done:
	printf("Done.\n");
	*/
    return;
};

//
// ================================================================
//

//
//    ### volume support ###
//

//Mostra informações sobre o volume atual.
void volumeShowCurrentVolumeInfo (){
	
	printf("The current volume is %d\n",current_volume);
    volumeShowVolumeInfo (current_volume);	
};


/*
 ************************************************
 * volumeShowVolumeInfo:
 *
 */
int volumeShowVolumeInfo ( int descriptor ){
	
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
		
		printf("path_string={%s}\n",v->path_string);
		
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

int volume_init (){
	
	int i;
	
#ifdef KERNEL_VERBOSE
    printf("volume_init: Initializing..\n");
#endif


	//limpar
	for ( i=0; i<VOLUME_COUNT_MAX; i++ ){
		volumeList[i] = 0;
	};

	
	// root: - Volume 0 (vfs)
    // root:/volume0 - Links para o raiz.   
	// root:/volume1 - volume da partição de boot.
	// root:/volume2 - volume da partição de sistema.
	
	
	
	// Volume.
	volume_vfs = (void*) malloc( sizeof(struct volume_d) );
	
	if ( (void *) volume_vfs == NULL )
	{
	    panic ("sm-disk-volume_init: volume_vfs");

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

        volumeList[0] = (unsigned long) volume_vfs; 		
	};
	
	
	// Volume.
	volume_bootpartition = (void*) malloc( sizeof(struct volume_d) );
	
	if ( (void *) volume_bootpartition == NULL )
	{
	    panic ("sm-disk-volume_init: volume_bootpartition");

	}else{
		
		//@todo:
		//volume_bootpartition->objectType = ?;
        //volume_bootpartition->objectClass = ?;
		
		
		// Será usado pelo VFS.
		volume_bootpartition->volumeType = VOLUME_TYPE_DISK_PARTITION;
		
	    volume_bootpartition->id = 1;
	    
		volume_bootpartition->used = (int) 1;
	    volume_bootpartition->magic = (int) 1234;
	    
		volume_bootpartition->name = "VOLUME 1 - BOOT";  
        
		volume_bootpartition->cmd = "root:/volume1";
		
		//Volume atual
        current_volume = 1;	

        volumeList[current_volume] = (unsigned long) volume_bootpartition; 	

        //#importante 
        //atualizamos a estrutura storage com o volume atual.
		storage->v = volume_bootpartition;   		
	};
	
	
	// Volume.
	volume_systempartition = (void *) malloc( sizeof(struct volume_d) );
	
	if ( (void *) volume_systempartition == NULL )
	{
	    panic ("sm-disk-volume_init: volume_systempartition");

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

        volumeList[2] = (unsigned long) volume_systempartition; 		
	};
	
    return (int) 0;
};




/*
 * pegaremos informações sobre um disco ide checando o mbr.
 * o índice determina qual informações pegaremos.
 * -1 = sem assinatura.
 * -2 = nenhuma partição ativa. (80)
 * ...
 *
 * checar o mbr de uma das quatro portas do controlador ide.
 * #obs: o mbr pertence ao disco todo na interface ide, 
 * mas pode dizer alguma coisa sobre as partições,
 * se olharmos na tabela de partições.
 */

int get_ide_disk_info ( int port, unsigned long buffer, int master ){
	
	int i = 0;
    unsigned char *mbr = (unsigned char *) buffer; 
	
	// (buffer, lba, rw flag, port number )
    
	pio_rw_sector ( (unsigned long) &mbr[0], // buffer
	                (unsigned long) 0,       // 0 = mbr
					(int) 0x20,              // 20 = ler
					(int) port,              // port 0-3
                    (int) master );          // 1 = master  0 = slave
	
	
	// Check signature.
	if ( mbr[0x1FE] != 0x55 || mbr[0x1FF] != 0xAA )
	{	
	    //printf("get_ide_disk_info: Sig FAIL \n" );
        return -1;	
	}	
	
	
	//print OS name.
	//#define BS_OEMName 2
		
	printf("OS name: [ ");
	
	for ( i=0; i<8; i++ ){
	    printf("%c", mbr[ BS_OEMName + i ] );
	};
	
	printf(" ]\n");	
	
    return 0;	
};


/*
 * show_ideports_info:
 *     #importante: Testando se tem discos nas portas IDE.
 *     Se está válida então carregamos o primeiro setor do disco,
 *     checamos pela assinatura no fim do MBR e imprimimos o nome do disco,
 *     que está presente no BPB.
 */
void show_ideports_info (){
	
    printf("\n show_ideports_info: Testing ports, looking for signature\n");  
	
	//primary master 
	printf("\n Testing primary master \n");
    if ( ide_ports[0].used ==  1 )
	{
	    if ( get_ide_disk_info ( (int) 0, (unsigned long) malloc(512), 1 ) == -1 )
        {
	        printf("primary master signature FAIL\n");	
	    }else{
	        printf("primary master signature OK\n");
	    };				
			
	} else {
		printf("No disk in primary master\n");
	};
	
	
	//primary slave 
    printf("\n Testing primary slave \n");
	if ( ide_ports[0].used ==  1 )
	{
	    if ( get_ide_disk_info ( (int) 0, (unsigned long) malloc(512), 0 ) == -1 )
        {
	        printf("primary slave signature FAIL\n");	
	    }else{
	        printf("primary slave signature OK\n");
	    };				
			
	} else {
		printf("No disk in primary slave\n");
	};
	
	
	//secondary master 
	printf("\n Testing secondary master \n");
    if ( ide_ports[2].used ==  1 )
	{
	    if ( get_ide_disk_info ( (int) 2, (unsigned long) malloc(512), 1 ) == -1 )
        {
	        printf("secondary master signature FAIL\n");	
	    }else{
	        printf("secondary master signature OK\n");
	    };				
			
	} else {
		printf("No disk in secondary master\n");
	};
	
	//#bugbug
	//como aqui o que temos é um disco (CD) a interface é ATAPI 
	//e possivelmente SCSI, Então as regras são diferentes,
	//vamos testar isso depois.
	//secondary slave (.ISO) (1024 bytes)
	//Para teste vamos colocar outro disco HD aqui.
	//ok, está funcionando com os 4 discos hd
    printf("\n Testing secondary slave \n");
	if ( ide_ports[2].used ==  1 )
	{
	    if ( get_ide_disk_info ( (int) 2, (unsigned long) malloc(1024), 0 ) == -1 )
        {
	        printf("secondary slave signature FAIL\n");	
	    }else{
	        printf("secondary slave signature OK\n");
	    };				
			
	} else {
		printf("No disk in secondary slave\n");
	};
	 
	printf("done\n");
	refresh_screen();	
}



//
// End.
//


