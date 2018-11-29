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


/*
 * disk_get_current_disk_info:
 *     Obtem o ponteiro da estrutura de informações do disco atual.
 *
 */
void *disk_get_current_disk_info (){
	
	return (void *) CurrentDiskInfo; 
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

	int i;

	
#ifdef KERNEL_VERBOSE	
    printf("disk_init: Initializing..\n");
#endif	

    //@todo: Tem que limpara a lista de discos.	
	for ( i=0; i<DISK_COUNT_MAX; i++ ){
		
		diskList[i] = 0;
	};
	
	
	// Inicializando uma estrutura global de informações sobre o 
	// disco do sistema.
	// ?? Em que arquivo está essa estrutura.

	// disk info
    diskinfo_conductor = (void*) malloc( sizeof(struct diskinfo_d) );
	if( (void*) diskinfo_conductor == NULL )
	{
	    printf("sm-disk-disk_init:");
		die();
	}else{
		
	    diskinfo_conductor->id = 0;
	    
		diskinfo_conductor->used = 1;
	    diskinfo_conductor->magic = 1234;
	    
		diskinfo_conductor->name = "DISK INFO";
		
		//diskinfo_conductor->BytesPerSector = DISK_BYTES_PER_SECTOR;
	    //diskinfo_conductor->SectorsPerCluster = 0;
        //...		
	};
	
	
	// disk.
    disk_conductor = (void *) malloc( sizeof(struct disk_d) );
	if( (void *) disk_conductor == NULL )
	{
	    printf("sm-disk-disk_init:");
		die();
	}else{
		
		//@todo:
		//disk_conductor->objectType = ?;
		//disk_conductor->objectClass = ?;
		
		disk_conductor->diskType = DISK_TYPE_NULL;
		
	    disk_conductor->id = 0;
	    
		disk_conductor->used = (int) 1;
	    disk_conductor->magic = (int) 1234;
	    
		disk_conductor->name = "DISK 0";
		
		disk_conductor->disk_info = (struct diskinfo_d *) diskinfo_conductor;
		
		//atualiza a lista
		diskList[0] = (unsigned long) disk_conductor;
	};	
	
	
	//
	//  selecionando o primeiro disco,
	// que deve ser o volume do vfs
	//
	current_disk = 0;

		
    //
	//@todo: Nothing more ?!!
	//
	
done:
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


/*
int init_disk_manager();
int init_disk_manager()
{
	disk_init();
    return (int) 0;
};


*/



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
	//  selecionando o volume atual.
	//  a partição de boot.
	//  
	
	current_volume = 1;	

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
	    
		volume_bootpartition->name = "VOLUME 1 - BOOT";  
        
		volume_bootpartition->cmd = "root:/volume1";
		
		// Não configuraremos por enquanto.
        volume_bootpartition->volume_info = NULL;

        volumeList[1] = (unsigned long) volume_bootpartition; 		
	};
	
	
	// Volume.
	volume_systempartition = (void *) malloc( sizeof(struct volume_d) );
	
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
	// @todo: More ??!
	//

done:	
    return (int) 0;
};



//pegaremos informações sobre um disco ide checando o mbr.
//o índice determina qual informações pegaremos.
// -1 = sem assinatura.
// -2 = nenhuma partição ativa. (80)
// ...
//
//checar o mbr de uma das quatro portas do controlador ide.
//#obs: o mbr pertence ao disco todo na interface ide, 
//mas pode dizer alguma coisa sobre as partições,
// se olharmos na tabela de partições.

int get_ide_disk_info ( int port, unsigned long buffer, int master )
{
    unsigned char *mbr = (unsigned char *) buffer; 
	
	// read test (buffer, lba, rw flag, port number )
    

	
	
	pio_rw_sector ( (unsigned long) &mbr[0], // buffer
	                 (unsigned long) 0,      // 0 = mbr
					 (int) 0x20,             // 20 = ler
					 (int) port,             // port 0-3
                     (int) master );         // 1 = master  0 = slave
	
	
	// Check signature.
	if ( mbr[0x1FE] != 0x55 || mbr[0x1FF] != 0xAA )
	{
		
	    //printf("get_ide_disk_info: Sig FAIL \n" );
        return -1;	
	};	
	
	
	//name
	int i;
	
	printf("OS name: [ ");
	for ( i=0; i<8; i++ )
	{
	    printf("%c", mbr[ BS_OEMName + i ] );
	};
	printf(" ]\n");	
	
    return 0;	
};


void show_ideports_info()
{
	
 
    printf("\nTesting ports. Looking for signature ...\n");  
  
	
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
	
	
	
		
		refresh_screen();
	
 
	printf("done\n");
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


