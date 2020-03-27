/*
 * File: storage/storage.c 
 *
 *     Storage manager.
 *     Manages disks and volumes. 
 *
 * 2015 - Created by Fred Nora.
 * 2018 - Revision.
 *
 */


// See:
// See sci/fs/fs.c for mounted volumes structure.

#include <kernel.h>


//
//    ### disk support ###
//


//Mostra informa��es sobre o disco atual.

void diskShowCurrentDiskInfo (void)
{
    printf ("The current disk is %d\n", current_disk );
    diskShowDiskInfo (current_disk);
}


//Mostra informa��es sobre um disco dado seu descritor.
int diskShowDiskInfo ( int descriptor ){

    struct disk_d *d;

    //#debug
    //printf ("diskShowDiskInfo:\n\n");
    printf ("\n\n");

    if ( descriptor < 0 || descriptor > DISK_COUNT_MAX ){
        printf ("descriptor fail\n");
        goto fail;
    }


    d = (struct disk_d *) diskList[descriptor];

    if ( (void *) d == NULL ){
        printf ("struct fail\n");
        goto fail;

    } else {


        if ( d->used != 1 || d->magic != 1234 ){
			printf("flags fail\n");
			goto fail;
        }

        printf ("disk %d - %s \n", d->id, d->name );

        //printf ("id={%d} used={%d} magic={%d} \n", 
            //d->id, d->used, d->magic );

        printf ("boot_disk={%d}\n",d->boot_disk_number);
        printf ("diskType={%d}\n", d->diskType );
        //printf ("name={%s}\n", d->name );
		//...
		goto done;
    };

	goto done;

	
fail:
    printf("fail\n");
    return (int) 1;

done:

    printf ("done\n");
    return 0;
}


//show info for all disks in the list.
void disk_show_info (void)
{
    int i;
    struct disk_d *disk;
    
    for(i=0; i<DISK_COUNT_MAX; i++)
    {
        disk = (struct disk_d *) diskList[i];
        
        if ( (void *) disk != NULL ){
            diskShowDiskInfo(i);
        }
    };
}


/*
 * disk_get_disk_handle:
 *     Obtem o ponteiro da estrutura dado o descritor.
 */
 
void *disk_get_disk_handle ( int number ){

	if ( number < 0 || number >= DISK_COUNT_MAX ){
		return NULL;
	}


    return (void *) diskList[number];
}


/* #deletar */

void *disk_get_current_disk_info (void)
{
	return NULL;
}


/*
 ********************************************************
 * disk_init:
 *     Inicializa o Disk Manager.
 *     Que � um m�dulo do tipo MB.
 *
 */
 
//int diskInit() 

int disk_init (void){

    int i=0;
    
    unsigned char __boot_disk;


#ifdef KERNEL_VERBOSE
    printf ("disk_init: Initializing..\n");
#endif


    // Clean.
    for ( i=0; i<DISK_COUNT_MAX; i++ ){
        diskList[i] = 0;
    };

 
    //
    //  Disk
    //

    struct disk_d *d;

	//#importante
	//Essa estrutura � vital, n�o podemos ficar sem ela.
	
    d = (void *) kmalloc( sizeof(struct disk_d) );
    

    if( (void *) d == NULL )
        panic ("disk_init: d");
 
 
    if( (void *) storage == NULL ){
        panic ("disk_init: storage");

	}else{
		
		
		d->diskType = DISK_TYPE_NULL;
		
	    d->id = 0;
	    d->boot_disk_number = (char) info_get_boot_info (3);
	    
		d->used = (int) 1;
	    d->magic = (int) 1234;
	    
	    __boot_disk = (char) d->boot_disk_number;
        switch (__boot_disk)
        {
            case 0x80:
                d->name = "sda";
                break;

            case 0x81:
                d->name = "sdb";
                break;

            case 0x82:
                d->name = "sdc";
                break;

            case 0x83:
                d->name = "sdd";
                break;
           
            default:
                d->name = "sd?";
                break;
        };

		
		d->next = NULL;
		
		//global
	    current_disk = 0;
	
        storage->system_disk = (struct disk_d *) d;

        ____boot____disk =  (struct disk_d *) d;
    };



   //more?
 

//done:

    printf("Done\n");

    return 0;
}



/*
 * init_test_disk:
 *     Testando opera��es com disco.
 *
 *     @todo: Essa rotina pode virar um aplicativo de teste.
 *
 * + Carrega o arquivo KCONFIG.TXT se estiver presente e 
 *   sonda informa��es de configura��o contidas nele, exibindo as
 *   informa��es.
 */

void init_test_disk (void){
	
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
	
	//@todo: Usar constantes ou vari�veis para esses valores.
	
	addr = (void *) kmalloc(512*32); 
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

	
	
	//@todo: Checar esse valor m�ximo.
	
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
}


//
// ================================================================
//

//
//    ### volume support ###
//

//Mostra informa��es sobre o volume atual.

void volumeShowCurrentVolumeInfo (void){

    printf ("The current volume is %d\n",current_volume);
    volumeShowVolumeInfo (current_volume);	
}


/*
 ************************************************
 * volumeShowVolumeInfo:
 *
 */
 
int volumeShowVolumeInfo ( int descriptor ){

    struct volume_d *v;

    //printf ("volumeShowVolumeInfo:\n");
    printf ("\n\n");

    if ( descriptor < 0 || descriptor > VOLUME_COUNT_MAX ){
        printf("descriptor fail\n");
        goto fail;
    }


    v = (struct volume_d *) volumeList[descriptor];

    if( (void *) v == NULL ){
		printf("struct fail\n");
		goto fail;

    }else{
	

        if ( v->used != 1 || v->magic != 1234 ){
            printf("flags fail\n");
            goto fail;
        }

        printf ("volume %d - %s \n", v->id, v->name );

        //printf("used={%d}\n",v->used);
        //printf("magic={%d}\n",v->magic);

        printf("volumeType={%d}\n",v->volumeType);
		
		//#bugbug
		//@todo: Esse nome temos que pegar no diret�rio raiz.
		
        //printf("name={%s}\n",v->name);
		
		//printf("path_string={%s}\n",v->path_string);
		
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

    return 0;
}



void *volume_get_volume_handle( int number )
{
	//check limts
    if ( number < 0 || number >= VOLUME_COUNT_MAX ){
        return NULL;
    }
    

    return (void *) volumeList[number];
}


void *volume_get_current_volume_info (void)
{
    if( current_volume < 0 || current_volume > VOLUME_COUNT_MAX ){
	    return NULL;
	}
	
    return (void *) volumeList[VOLUME_COUNT_MAX];	
}



/*
 ***************************************************
 * volume_init:
 *     Inicializa o volume manager.
 */
 
//int volumeInit()

int volume_init (void){

    int i;
    
    
    char name_buffer[32];


#ifdef KERNEL_VERBOSE
    printf ("volume_init: Initializing..\n");
#endif


    // Clean
    for ( i=0; i<VOLUME_COUNT_MAX; i++ ){
        volumeList[i] = 0;
    };


    if ( (void *) storage == NULL ){
        panic ("volume_init: storage");
    }


    // ??? Esse � o root ???


	// Volume.
    volume_vfs = (void *) kmalloc( sizeof(struct volume_d) );

    if ( (void *) volume_vfs == NULL ){
        panic ("volume_init: volume_vfs");

    }else{
		
		//@todo:
		//volume_vfs->objectType = ?;
        //volume_vfs->objectClass = ?;
		
		
		// Ser� usado pelo VFS.
		volume_vfs->volumeType = VOLUME_TYPE_BUFFER;
		
	    volume_vfs->id = 0;
	    
		volume_vfs->used = (int) 1;
	    volume_vfs->magic = (int) 1234;
	    
        //volume_vfs->name = "VOLUME 0"; 
        sprintf ( (char *) name_buffer, "VOLUME-%d",volume_vfs->id);
        volume_vfs->name = (char *) strdup ( (const char *) name_buffer);  

        //#todo
        volume_vfs->cmd = "#TODO";

        volumeList[0] = (unsigned long) volume_vfs;
        storage->vfs_volume = (struct volume_d *) volume_vfs; 
    };

	
    // Volume.
    volume_bootpartition = (void *) kmalloc( sizeof(struct volume_d) );

    if ( (void *) volume_bootpartition == NULL ){
        panic ("volume_init: volume_bootpartition");

    }else{

		//@todo:
		//volume_bootpartition->objectType = ?;
        //volume_bootpartition->objectClass = ?;
		
		
		// Ser� usado pelo VFS.
		volume_bootpartition->volumeType = VOLUME_TYPE_DISK_PARTITION;

        volume_bootpartition->id = 1;
           
		volume_bootpartition->used = (int) 1;
	    volume_bootpartition->magic = (int) 1234;
	    
		//volume_bootpartition->name = "VOLUME 1 - BOOT";  
        sprintf ( (char *) name_buffer, "VOLUME-%d",volume_bootpartition->id);
        volume_bootpartition->name = (char *) strdup ( (const char *) name_buffer);  
        
        
        //#todo
		volume_bootpartition->cmd = "#TODO";
		
		//Volume atual
        current_volume = 1;

        volumeList[1] = (unsigned long) volume_bootpartition; 
        storage->boot_volume = (struct volume_d *) volume_bootpartition; 
    };

	
	// Volume.
    volume_systempartition = (void *) kmalloc( sizeof(struct volume_d) );

    if ( (void *) volume_systempartition == NULL ){
        panic ("volume_init: volume_systempartition");

	}else{
		
		//@todo:
		//volume_systempartition->objectType = ?;
        //volume_systempartition->objectClass = ?;
		
		
		// Ser� usado pelo VFS.
		volume_systempartition->volumeType = VOLUME_TYPE_DISK_PARTITION;
		
	    volume_systempartition->id = 2;
	    
		volume_systempartition->used = (int) 1;
	    volume_systempartition->magic = (int) 1234;
	    
		//volume_systempartition->name = "VOLUME 2";  
        sprintf ( (char *) name_buffer, "VOLUME-%d",volume_systempartition->id);
        volume_systempartition->name = (char *) strdup ( (const char *) name_buffer);  


        //#todo 
		volume_systempartition->cmd = "#TODO";

        volumeList[2] = (unsigned long) volume_systempartition;
        storage->system_volume = (struct volume_d *) volume_systempartition; 
	};


    return 0;
}


//show info for all volumes in the list.
void volume_show_info (void)
{
    int i;
    struct volume_d *volume;
    
    for(i=0; i<VOLUME_COUNT_MAX; i++)
    {
        volume = (struct volume_d *) volumeList[i];
        
        if ( (void *) volume != NULL )
        {
            volumeShowVolumeInfo(i);
        }
    };
}


/*
 * pegaremos informa��es sobre um disco ide checando o mbr.
 * o �ndice determina qual informa��es pegaremos.
 * -1 = sem assinatura.
 * -2 = nenhuma parti��o ativa. (80)
 * ...
 *
 * checar o mbr de uma das quatro portas do controlador ide.
 * #obs: o mbr pertence ao disco todo na interface ide, 
 * mas pode dizer alguma coisa sobre as parti��es,
 * se olharmos na tabela de parti��es.
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
}


/*
 * show_ideports_info:
 *     #importante: Testando se tem discos nas portas IDE.
 *     Se est� v�lida ent�o carregamos o primeiro setor do disco,
 *     checamos pela assinatura no fim do MBR e imprimimos o nome do disco,
 *     que est� presente no BPB.
 */

void show_ideports_info (void){
	
    printf("\n show_ideports_info: Testing ports, looking for signature\n");  
	
	//primary master 
	printf("\n Testing primary master \n");
    if ( ide_ports[0].used ==  1 )
	{
	    if ( get_ide_disk_info ( (int) 0, (unsigned long) kmalloc(512), 1 ) == -1 )
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
	    if ( get_ide_disk_info ( (int) 0, (unsigned long) kmalloc(512), 0 ) == -1 )
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
	    if ( get_ide_disk_info ( (int) 2, (unsigned long) kmalloc(512), 1 ) == -1 )
        {
	        printf("secondary master signature FAIL\n");	
	    }else{
	        printf("secondary master signature OK\n");
	    };				
			
	} else {
		printf("No disk in secondary master\n");
	};
	
	//#bugbug
	//como aqui o que temos � um disco (CD) a interface � ATAPI 
	//e possivelmente SCSI, Ent�o as regras s�o diferentes,
	//vamos testar isso depois.
	//secondary slave (.ISO) (1024 bytes)
	//Para teste vamos colocar outro disco HD aqui.
	//ok, est� funcionando com os 4 discos hd
    printf("\n Testing secondary slave \n");
	if ( ide_ports[2].used ==  1 )
	{
	    if ( get_ide_disk_info ( (int) 2, (unsigned long) kmalloc(1024), 0 ) == -1 )
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


