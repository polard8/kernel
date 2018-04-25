/*
 * File: sm\disk\disk.c 
 * 
 * Descrição:
 *     Gerenciador de discos. 
 *     Arquivo principal do Disk Manager.
 *     MB - Módulos incluídos no Kernel Base.
 *
 *     O Gerenciador de Discos é um módulo muito importante do Kernel.
 *
 *    Versão 1.0, 2015, 2016.
 */

 
//
// Obs: o foco está na lista de discos. diskList
//

#include <kernel.h>



void *disk_get_disk_handle( int number )
{
	//check limts
	if( number < 0 || number >= DISK_COUNT_MAX ){
		return NULL;
	}
	
	return (void *) diskList[number];
};




void *disk_get_current_disk_info()
{
	return (void *) CurrentDiskInfo; 
};


/*
 * disk_init:
 *     Inicializa o Disk Manager.
 *     Que é um módulo do tipo MB.
 *
 */
//int diskInit() 
int disk_init()
{
	
#ifdef KERNEL_VERBOSE	
    printf("disk_init: Initializing..\n");
#endif	
	
	//
	// Inicializando uma estrutura global de informações sobre o 
	// disco do sistema.
	// ?? Em que arquivo está essa estrutura.
	//

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
    disk_conductor = (void*) malloc( sizeof(struct disk_d) );
	if( (void*) disk_conductor == NULL )
	{
	    printf("sm-disk-disk_init:");
		die();
	}else{
		
		//@todo:
		//disk_conductor->objectType = ?;
		//disk_conductor->objectClass = ?;
		
		disk_conductor->diskType = DISK_TYPE_NULL;
		
	    disk_conductor->id = 0;
	    
		disk_conductor->used = 1;
	    disk_conductor->magic = 1234;
	    
		disk_conductor->name = "DISK 0";
		
		disk_conductor->disk_info = (struct diskinfo_d *) diskinfo_conductor;
	};	
		
    //
	//@todo: Nothing more ?!!
	//
	
done:
    printf("Done.\n");
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
void init_test_disk()
{
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
// End.
//

