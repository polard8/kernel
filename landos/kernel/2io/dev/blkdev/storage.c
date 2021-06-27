

#include <kernel.h>  



/*
 ********************************************************
 * disk_init:
 *
 *     Initialize the disk manager.
 */

// #bugbug
// #fixme
// The boot disk was not include in the diskList[]
// Probably the 'ide module' will discover all the ide disks
// and rebuild the list. This way all the information made here
// was gone. #fixme

int disk_init (void)
{
    struct disk_d *d;

    unsigned char BootDisk=0;

    int i=0;



#ifdef KERNEL_VERBOSE
    printf ("disk_init: Initializing..\n");
#endif


    // Clean the disk list.

    for ( i=0; i<DISK_COUNT_MAX; i++ )
    {
        diskList[i] = 0;
    };

 
    //
    //  Disk structure
    //

	//#importante
	//Essa estrutura � vital, n�o podemos ficar sem ela.
	
    d = (void *) kmalloc( sizeof(struct disk_d) );

    if( (void *) d == NULL ){
        panic ("disk_init: d\n");
    }
 
    if( (void *) storage == NULL ){
        panic ("disk_init: storage");
    }else{
        d->used  = (int) TRUE;
        d->magic = (int) 1234;

        // This is the boot disk.
        // So, it will be the number '0'.
        d->id = 0;
        current_disk             = d->id;
        diskList[ current_disk ] = (unsigned long) d;   //#test

        d->diskType = DISK_TYPE_NULL;

        // Get the number of the boot disk.
        // This info was provide by BIOS at boot time.
        // That is why we call this 'boot_disk_number'.
        // See: core/info.c

        // #bugbug #todo
        // Nao chamar um metodo fora desse modulo 
        // para realizar esse trabalho.

        d->boot_disk_number = (char) info_get_boot_info(3);

        BootDisk = (char) d->boot_disk_number;

        switch (BootDisk){
            case 0x80:  d->name = "sda";  break;
            case 0x81:  d->name = "sdb";  break;
            case 0x82:  d->name = "sdc";  break;
            case 0x83:  d->name = "sdd";  break;
            default:
                debug_print("disk_init: [FAIL] default boot disk number\n");
                d->name = "sd?";
                break;
        };

        d->next = NULL;

        // #bugbug
        // Is this structure initialized ?

        if ( (void*) storage != NULL ){
            storage->system_disk = (struct disk_d *) d;
        }

        // global.
        ____boot____disk =  (struct disk_d *) d;
    };

   //more?

//done:

    printf("Done\n");

    return 0;
}

// Show disk information given its descriptor.
int diskShowDiskInfo ( int descriptor )
{
    struct disk_d  *d;

    //#debug
    //printf ("diskShowDiskInfo:\n\n");

    printf ("\n\n");

    if ( descriptor < 0 || descriptor > DISK_COUNT_MAX )
    {
        printf ("descriptor fail\n");
        goto fail;
    }


    d = (struct disk_d *) diskList[descriptor];

    if ( (void *) d == NULL ){
        printf ("struct fail\n");
        goto fail;
    } else {

        if ( d->used != TRUE || d->magic != 1234 )
        {
            printf("flags fail\n");
            goto fail;
        }

        printf ("disk %d - %s \n", d->id, d->name );
        printf ("boot_disk={%d}\n",d->boot_disk_number);
        printf ("diskType={%d}\n", d->diskType );
        //printf ("name={%s}\n", d->name );
        // ...
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

void diskShowCurrentDiskInfo (void)
{
    if (current_disk<0)
        return;

    printf ("The current disk is %d\n", current_disk );

    diskShowDiskInfo (current_disk);
}

// Show info for all disks in the list.
// Called by service 251
void disk_show_info (void)
{
    struct disk_d *disk;
    int i=0;

    // #test
    int CurrentIDEChannel = -1;
    int CurrentIDEdevice  = -1;
    int BootTimeIDEChannel = -1;
    int BootTimeIDEdevice  = -1;

    printf ("~Disk info:\n");

    CurrentIDEChannel  = ata_get_current_ide_channel();
    CurrentIDEdevice   = ata_get_current_ide_device();
    BootTimeIDEChannel = ata_get_boottime_ide_channel();
    BootTimeIDEdevice  = ata_get_boottime_ide_device();


    //printf ("CurrentIDEChannel %d\n", CurrentIDEChannel);
    //printf ("CurrentIDEdevice %d\n", CurrentIDEdevice);
    //printf ("BootTimeIDEChannel %d\n", BootTimeIDEChannel);
    //printf ("BootTimeIDEdevice %d\n", BootTimeIDEdevice);

    // ======================================================
    printf("Current:  ");

    if ( CurrentIDEChannel == ATA_PRIMARY )
        printf("Primary ");
    
    if ( CurrentIDEChannel == ATA_SECONDARY )
        printf("Secondary ");
    

    if ( CurrentIDEdevice == ATA_MASTER )
        printf("Master ");
    
    if ( CurrentIDEdevice == ATA_SLAVE )
        printf("Slave ");

    printf("\n");
    // ======================================================

    // ======================================================
    printf("Boottime:  ");

    if ( BootTimeIDEChannel == ATA_PRIMARY )
        printf("Primary ");
    
    if ( BootTimeIDEChannel == ATA_SECONDARY )
        printf("Secondary ");
    

    if ( BootTimeIDEdevice == ATA_MASTER )
        printf("Master ");
    
    if ( BootTimeIDEdevice == ATA_SLAVE )
        printf("Slave ");

    printf("\n");
    // ======================================================
    
    // All disks in the list.
    
    for (i=0; i<DISK_COUNT_MAX; i++)
    {
        disk = (struct disk_d *) diskList[i];
        
        if ( (void *) disk != NULL )
        {
            diskShowDiskInfo(i);
        }
    };
}

/*
 * disk_get_disk_handle:
 *     Obtem o ponteiro da estrutura dado o descritor.
 */
 
void *disk_get_disk_handle ( int number )
{
    if ( number < 0 || number >= DISK_COUNT_MAX )
    {
        return NULL;
    }

    return (void *) diskList[number];
}


// ================================

/*
 ***************************************************
 * volume_init:
 *     Inicializa o volume manager.
 */

int volume_init (void){

    int i=0;
    char name_buffer[32];


#ifdef KERNEL_VERBOSE
    printf ("volume_init: Initializing..\n");
#endif

    // The main structure.
    if ( (void *) storage == NULL ){
        panic ("volume_init: storage");
    }

    // Clean the list
    for ( i=0; i<VOLUME_COUNT_MAX; i++ ){
        volumeList[i] = 0;
    };


    //
    // == VFS =====================================================
    //


    // Volume.
    volume_vfs = (void *) kmalloc ( sizeof(struct volume_d) );

    if ( (void *) volume_vfs == NULL )
    {
        panic ("volume_init: volume_vfs");

    }else{
        // #todo:
        //volume_vfs->objectType = ?;
        //volume_vfs->objectClass = ?;

        volume_vfs->id = VFS_VOLUME_ID;
        volume_vfs->used = (int) 1;
        volume_vfs->magic = (int) 1234;

        // Sera usado pelo VFS.
        volume_vfs->volumeType = VOLUME_TYPE_BUFFER;
        
        // These fields are not used in a vfs.
        volume_vfs->VBR_lba=0;
        volume_vfs->FAT1_lba=0;
        volume_vfs->FAT2_lba=0;
        volume_vfs->ROOT_lba=0;
        volume_vfs->DATA_lba=0;
        

        //volume_vfs->name = "VOLUME 0"; 
        sprintf ( (char *) name_buffer, "VOLUME-%d",volume_vfs->id);
        volume_vfs->name = (char *) strdup ( (const char *) name_buffer);  

        //#todo
        volume_vfs->cmd = "#TODO";

        volumeList[VFS_VOLUME_ID] = (unsigned long) volume_vfs;
        storage->vfs_volume = (struct volume_d *) volume_vfs; 
    };

    //
    // == boot partition ==============================================
    //


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

        volume_bootpartition->id = BOOTPARTITION_VOLUME_ID;
        volume_bootpartition->used = (int) 1;
        volume_bootpartition->magic = (int) 1234;

        volume_bootpartition->VBR_lba  = VOLUME1_VBR_LBA;
        volume_bootpartition->FAT1_lba = VOLUME1_FAT_LBA;
        volume_bootpartition->FAT2_lba = 0;  //#bugbug
        volume_bootpartition->ROOT_lba = VOLUME1_ROOTDIR_LBA;
        volume_bootpartition->DATA_lba = VOLUME1_DATAAREA_LBA;


        //volume_bootpartition->name = "VOLUME 1 - BOOT";  
        sprintf ( (char *) name_buffer, "VOLUME-%d",volume_bootpartition->id);
        volume_bootpartition->name = (char *) strdup ( (const char *) name_buffer);  
        
        
        //#todo
		volume_bootpartition->cmd = "#TODO";

		//Volume atual
        current_volume = volume_bootpartition->id;

        volumeList[BOOTPARTITION_VOLUME_ID] = (unsigned long) volume_bootpartition; 
        storage->boot_volume = (struct volume_d *) volume_bootpartition; 
    };


    //
    // == system partition ============================================
    //

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
		
	    volume_systempartition->id = SYSTEMPARTITION_VOLUME_ID;
		volume_systempartition->used = (int) 1;
	    volume_systempartition->magic = (int) 1234;

        volume_systempartition->VBR_lba  = VOLUME2_VBR_LBA;
        volume_systempartition->FAT1_lba = VOLUME2_FAT_LBA;
        volume_systempartition->FAT2_lba = 0;  //#bugbug
        volume_systempartition->ROOT_lba = VOLUME2_ROOTDIR_LBA;
        volume_systempartition->DATA_lba = VOLUME2_DATAAREA_LBA;

		//volume_systempartition->name = "VOLUME 2";  
        sprintf ( (char *) name_buffer, "VOLUME-%d",volume_systempartition->id);
        volume_systempartition->name = (char *) strdup ( (const char *) name_buffer);  


        //#todo 
		volume_systempartition->cmd = "#TODO";

        volumeList[SYSTEMPARTITION_VOLUME_ID] = (unsigned long) volume_systempartition;
        storage->system_volume = (struct volume_d *) volume_systempartition; 
	};


    return 0;
}


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
        printf ("struct fail\n");
        goto fail;

    }else{
        if ( v->used != 1 || v->magic != 1234 ){
            printf("flags fail\n");
            goto fail;
        }

        printf ("volume %d - %s \n", v->id, v->name );
        printf ("volumeType={%d}\n", v->volumeType);
        
        printf ("VBR_lba  {%d}\n", v->VBR_lba  );
        printf ("FAT2_lba {%d}\n", v->FAT1_lba );
        printf ("FAT2_lba {%d}\n", v->FAT2_lba );
        printf ("ROOT_lba {%d}\n", v->ROOT_lba );
        printf ("DATA_lba {%d}\n", v->DATA_lba );
        // ...
    };

    return 0;

fail:
    printf("Fail\n");
    return (int) -1;
}

// Show info for all volumes in the list.
void volume_show_info (void)
{
    int i;
    struct volume_d *volume;
    
    for (i=0; i<VOLUME_COUNT_MAX; i++)
    {
        volume = (struct volume_d *) volumeList[i];
        
        if ( (void *) volume != NULL )
        {
            volumeShowVolumeInfo(i);
        }
    };
}

void *volume_get_volume_handle( int number )
{
	//check limts
    if ( number < 0 || number >= VOLUME_COUNT_MAX )
    {
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












