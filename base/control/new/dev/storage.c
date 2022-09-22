
// storage.c

#include <kernel.h>  

const char* sda_string = "sda";
const char* sdb_string = "sdb";
const char* sdc_string = "sdc";
const char* sdd_string = "sdd";
const char* sdfail_string = "sd?";

//
// private functions: prototypes ============
//

static int __create_boot_partition(void);
static int __create_system_partition(void);
static int __create_vfs_partition(void);


// =================================================

// local
// Create boot partition.
// Volume 1
static int __create_boot_partition(void)
{
    char name_buffer[32];


    // The main structure.
    if ( (void *) storage == NULL ){
        panic ("__create_boot_partition: storage");
    }

// --------

//
// Volume 1 - Boot partition.
//

// Volume.

    volume_bootpartition = (void *) kmalloc( sizeof(struct volume_d) );

    if ( (void *) volume_bootpartition == NULL ){
        panic ("__create_boot_partition: volume_bootpartition");
    }

// #todo:
    //volume_bootpartition->objectType = ?;
    //volume_bootpartition->objectClass = ?;

// Sera usado pelo VFS.
    volume_bootpartition->volumeType = VOLUME_TYPE_DISK_PARTITION;

    volume_bootpartition->id = BOOTPARTITION_VOLUME_ID;

//
// Disk
//

// The disk that the volume belongs to.
    volume_bootpartition->disk = NULL;

    if( (void*) ____boot____disk != NULL ){
        volume_bootpartition->disk = (void*) ____boot____disk;
    }
    
// The filesystem used by this volue.
    volume_bootpartition->fs = NULL;


// #todo
// Volume limits.

    volume_bootpartition->__first_lba=0;
    volume_bootpartition->__first_lba=0;


    volume_bootpartition->VBR_lba  = VOLUME1_VBR_LBA;
    volume_bootpartition->FAT1_lba = VOLUME1_FAT_LBA;
    volume_bootpartition->FAT2_lba = 0;  //#bugbug
    volume_bootpartition->ROOT_lba = VOLUME1_ROOTDIR_LBA;
    volume_bootpartition->DATA_lba = VOLUME1_DATAAREA_LBA;

// Name

    //volume_bootpartition->name = "VOLUME 1 - BOOT";  
    sprintf ( (char *) name_buffer, "VOLUME-%d",volume_bootpartition->id);
    volume_bootpartition->name = (char *) strdup ( (const char *) name_buffer);  

    //#todo
    volume_bootpartition->cmd = "#TODO";

//
// Current volume
//

    current_volume = volume_bootpartition->id;

// Finalizing

    volume_bootpartition->used = (int) TRUE;
    volume_bootpartition->magic = (int) 1234;

    volumeList[BOOTPARTITION_VOLUME_ID] = (unsigned long) volume_bootpartition; 

    storage->boot_volume = (struct volume_d *) volume_bootpartition; 

// done:
    return 0;
}


// local
// Create system partition.
// Volume 2
static int __create_system_partition(void)
{
    char name_buffer[32];


    // The main structure.
    if ( (void *) storage == NULL ){
        panic ("__create_system_partition: storage");
    }


//
// Volume 2 - System partition.
//

// #bugbug: Isso esta errado.
// A partiçao do sistema precisa começar 
// logo apos a partiçao de boot, e a partiçao
// de boot tem 32MB.

    // Volume.
    volume_systempartition = (void *) kmalloc( sizeof(struct volume_d) );

    if ( (void *) volume_systempartition == NULL ){
        panic ("__create_system_partition: volume_systempartition");
    }

//#todo:
    //volume_systempartition->objectType = ?;
    //volume_systempartition->objectClass = ?;

// Sera usado pelo VFS.
    volume_systempartition->volumeType = VOLUME_TYPE_DISK_PARTITION;

    volume_systempartition->id = SYSTEMPARTITION_VOLUME_ID;

//
// Disk
//

// The disk that the volume belongs to.
    volume_systempartition->disk = NULL;

// The filesystem used by this volue.
    volume_systempartition->fs = NULL;


// #todo
// Volume limits.

    volume_systempartition->__first_lba=0;
    volume_systempartition->__first_lba=0;

    volume_systempartition->VBR_lba  = VOLUME2_VBR_LBA;
    volume_systempartition->FAT1_lba = VOLUME2_FAT_LBA;
    volume_systempartition->FAT2_lba = 0;  //#bugbug
    volume_systempartition->ROOT_lba = VOLUME2_ROOTDIR_LBA;
    volume_systempartition->DATA_lba = VOLUME2_DATAAREA_LBA;

// Name

    //volume_systempartition->name = "VOLUME 2";  
    sprintf ( (char *) name_buffer, "VOLUME-%d",volume_systempartition->id);
    volume_systempartition->name = (char *) strdup ( (const char *) name_buffer);  

    //#todo 
    volume_systempartition->cmd = "#TODO";


// Finalizing

    volume_systempartition->used = (int) TRUE;
    volume_systempartition->magic = (int) 1234;

    volumeList[SYSTEMPARTITION_VOLUME_ID] = (unsigned long) volume_systempartition;

    storage->system_volume = (struct volume_d *) volume_systempartition; 

// done:
    return 0;
}






int init_storage_support(void)
{
    storage = (void *) kmalloc ( sizeof(struct storage_d) );
    if ( (void *) storage == NULL )
    {
       printf ("init_storage_support: storage\n");
       return FALSE;
    }
    return TRUE;
}


// local
// Create vfs partition
// Volume 0.
static int __create_vfs_partition(void)
{
    char name_buffer[32];


// The main structure.

    if ( (void *) storage == NULL ){
        panic ("__create_vfs_partition: storage");
    }


//
// Volume 0 - vfs
//

// Volume.

    volume_vfs = (void *) kmalloc ( sizeof(struct volume_d) );

    if ( (void *) volume_vfs == NULL ){
        panic ("__create_vfs_partition: volume_vfs");

    }

    // #todo:
    //volume_vfs->objectType = ?;
    //volume_vfs->objectClass = ?;

    volume_vfs->id = VFS_VOLUME_ID;

// Sera usado pelo VFS.
    volume_vfs->volumeType = VOLUME_TYPE_BUFFER;

//
// Disk
//

// The disk that the volume belongs to.
    volume_vfs->disk = NULL;

// The filesystem used by this volue.
    volume_vfs->fs = NULL;


// #todo
// Volume limits.

    volume_vfs->__first_lba=0;
    volume_vfs->__first_lba=0;

// These fields are not used in a vfs.
    volume_vfs->VBR_lba=0;
    volume_vfs->FAT1_lba=0;
    volume_vfs->FAT2_lba=0;
    volume_vfs->ROOT_lba=0;
    volume_vfs->DATA_lba=0;

// Name

    //volume_vfs->name = "VOLUME 0"; 
    sprintf ( (char *) name_buffer, "VOLUME-%d",volume_vfs->id);
    volume_vfs->name = (char *) strdup ( (const char *) name_buffer);  

// #todo
// cmd

    volume_vfs->cmd = "#TODO";

// Finalizing

    volume_vfs->used = (int) TRUE;
    volume_vfs->magic = (int) 1234;

    volumeList[VFS_VOLUME_ID] = (unsigned long) volume_vfs;

    storage->vfs_volume = (struct volume_d *) volume_vfs; 

// done:
    return 0;
}


/*
 * disk_init:
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

//#ifdef KERNEL_VERBOSE
    //printf ("disk_init: Initializing..\n");
//#endif


//
//  storage structure
//

    if( (void *) storage == NULL ){
        panic ("disk_init: storage\n");
    }


// Clean the disk list.

    for ( i=0; i<DISK_COUNT_MAX; i++ )
    {
        diskList[i] = 0;
    };

//
//  Disk structure
//

// #importante
// Essa estrutura eh vital, 
// nao podemos ficar sem ela.

    d = (void *) kmalloc( sizeof(struct disk_d) );

    if( (void *) d == NULL ){
        panic ("disk_init: d\n");
    }

    d->used = (int) TRUE;
    d->magic = (int) 1234;

// This is the boot disk.
// So, it will be the number '0'.

    d->id = 0;
    current_disk = d->id;
    diskList[ current_disk ] = (unsigned long) d;   //#test

    d->diskType = DISK_TYPE_NULL;

// Get the number of the boot disk.
// This info was provide by BIOS at boot time.
// That is why we call this 'boot_disk_number'.
// See: info.c
// #bugbug #todo
// Nao chamar um metodo fora desse modulo 
// para realizar esse trabalho.

    //#bugbug: This methoc gets info from a non initialized structure.
    // see: BootBlock in info.h
    //d->boot_disk_number = (char) info_get_boot_info(3);
    d->boot_disk_number = -1;  //#fail

    BootDisk = (char) d->boot_disk_number;

// #bugbug: if d->name is a ponter we need to point to
// a const well define string, or create a new one.


    switch (BootDisk){
    case 0x80:  d->name = sda_string;  break;
    case 0x81:  d->name = sdb_string;  break;
    case 0x82:  d->name = sdc_string;  break;
    case 0x83:  d->name = sdd_string;  break;
    default:
        debug_print("disk_init: [FAIL] default boot disk number\n");
        d->name = sdfail_string;
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

    if ( descriptor < 0 || 
         descriptor >= DISK_COUNT_MAX )
    {
        printf ("descriptor fail\n");
        goto fail;
    }


    d = (struct disk_d *) diskList[descriptor];

    if ( (void *) d == NULL ){
        printf ("struct fail\n");
        goto fail;
    }

    if ( d->used != TRUE || d->magic != 1234 )
    {
        printf("flags fail\n");
        goto fail;
    }

    printf ("disk %d - {{{{ %s }}}} \n", d->id, d->name );
    printf ("boot_disk = {%d}\n",d->boot_disk_number);
    printf ("diskType  = {%d}\n", d->diskType );
    //printf ("name={%s}\n", d->name );
    // ...

//done:
    printf ("done\n");
    return 0;

fail:
    printf("fail\n");
    return (int) -1;
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
    int i=0;
    struct disk_d *disk;

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


/*
 * volume_init:
 *     Inicializa o volume manager.
 */

int volume_init (void)
{
    int Status = -1;  //fail
    register int i=0;
    char name_buffer[32];


    // The main structure.
    if ( (void *) storage == NULL ){
        panic ("volume_init: storage");
    }

    // Clear the list
    for ( i=0; i<VOLUME_COUNT_MAX; i++ ){
        volumeList[i] = 0;
    };


// --------


// Volume 0 - vfs
    Status = (int) __create_vfs_partition();
    if(Status<0){
        panic("volume_init: __create_vfs_partition fail\n");
    }

// Volume 1 - Boot partition.
    Status = (int) __create_boot_partition();
    if(Status<0){
        panic("volume_init: __create_boot_partition fail\n");
    }

// Volume 2 - System partition.
    Status = (int) __create_system_partition();
    if(Status<0){
        panic("volume_init: __create_system_partition fail\n");
    }

//done:
    return 0;
}


int volumeShowVolumeInfo ( int descriptor )
{
    struct volume_d *v;

    //printf ("volumeShowVolumeInfo:\n");
    printf ("\n");

    if ( descriptor < 0 || 
         descriptor >= VOLUME_COUNT_MAX )
    {
        printf("descriptor fail\n");
        goto fail;
    }


    v = (struct volume_d *) volumeList[descriptor];

    if( (void *) v == NULL ){
        printf ("struct fail\n");
        goto fail;
    }

    if ( v->used != 1 || v->magic != 1234 )
    {
        printf("flags fail\n");
        goto fail;
    }

    printf ("volume %d - %s \n", v->id, v->name );
    printf ("volumeType = {%d}\n", v->volumeType);

    printf ("VBR_lba  {%d}\n", v->VBR_lba  );
    printf ("FAT2_lba {%d}\n", v->FAT1_lba );
    printf ("FAT2_lba {%d}\n", v->FAT2_lba );
    printf ("ROOT_lba {%d}\n", v->ROOT_lba );
    printf ("DATA_lba {%d}\n", v->DATA_lba );
    // ...

//done
    return 0;

fail:
    printf("Fail\n");
    return (int) -1;
}


void volumeShowCurrentVolumeInfo (void)
{
    if (current_volume<0)
        return;

    printf ("The current volume is %d\n", current_volume );

    diskShowDiskInfo (current_volume);
}


// Show info for all volumes in the list.
void volume_show_info (void)
{
    int i=0;
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

// check limts
    if ( number < 0 || 
         number >= VOLUME_COUNT_MAX )
    {
        return NULL;
    }

    return (void *) volumeList[number];
}


void *volume_get_current_volume_info (void)
{
    if ( current_volume < 0 || 
         current_volume > VOLUME_COUNT_MAX )
    {
         return NULL;
    }

    return (void *) volumeList[VOLUME_COUNT_MAX];
}


