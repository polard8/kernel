
// disk_w.c


#include <kernel.h>


static int 
__do_save_sequence ( 
    unsigned long buffer_va, 
    unsigned long lba, 
    size_t number_of_clusters );

    
// ----------------------------

static int 
__do_save_sequence ( 
    unsigned long buffer_va, 
    unsigned long lba, 
    size_t number_of_clusters )
{
    int i=0;

// Arguments
    unsigned long buffer_base = (unsigned long) buffer_va;
    unsigned long buffer_off=0;
    unsigned long lba_base = (unsigned long) lba;
    unsigned long lba_off=0;
    size_t Total = (size_t) (number_of_clusters & 0xFFFFFFFF);
    //size_t Max=0; 

// #todo:
// #bugbug:
// How much is the max number of cluster we can save 
// into this disk.

// Esperando antes do próximo.
        
    for ( i=0; i<Total; i++ )
    {
        // Waiting before the next.
        // #bugbug: 
        // Maybe this is make this process very slow in the vms.
        
        // #todo:
        // Maybe, do not use this on vms.
        // See: atairq.c
        // if (is_qemu != TRUE)
        disk_ata_wait_irq();

        ataWriteSector ( 
            (unsigned long) ( buffer_base + buffer_off ), 
            (unsigned long) ( lba_base    + lba_off ), 
            0, 
            0 );

        // Update offsets.
        // Sector size is 512 and the cluster has only one sector for now.
        // #todo
        // We need different sizes of sectors and 
        // different n umber of spc.
        buffer_off += 0x200;  
        lba_off    += 1;
    };
    
// ok. No errors.
    return 0;
}


/*
 * write_lba:
 *     Grava um setor no disco dado o endereço do buffer e o lba. 
 */
// #bugbug
// Essa rotina e' independente do sistema de arquivos.
// #todo: use 'int' return.

void write_lba ( unsigned long address, unsigned long lba )
{

// #todo: 
// Check lba limits.

    if (address == 0){
        debug_print ("write_lba: [FAIL] Limits\n");
        goto fail;
    }

    // See: volume.h
    switch (g_currentvolume_fatbits){

    case 32:
        printf ("write_lba: [ERROR] FAT32 not supported\n");
        goto fail;
        break;

    //See: atahdd.c
    case 16:
        ataWriteSector ( address, lba, 0, 0 ); 
        return;
        break;

    case 12:
        printf ("write_lba: [ERROR] FAT12 not supported\n");
        goto fail;
        break;

    default:
        printf ("write_lba: [ERROR] g_currentvolume_fatbits NOT SUPPORTED\n");
        goto fail;
        break;
    };

// Nothing.

fail:
    refresh_screen();
    return;
}


/*
 * fatWriteCluster:
 *     Salva um cluster no disco.
 *
 * Argumentos:
 *   setor   ~ Primeiro setor do cluster.
 *   address ~ Endereço do primeiro setor do cluster.
 *   spc     ~ Número de setores por cluster.
 */

// #todo
// Return 'int'.
// #bugbug: it is not only for fat... it is hw worker.

void 
fatWriteCluster ( 
    unsigned long sector, 
    unsigned long address, 
    unsigned long spc )
{
    unsigned long i=0;

    // #todo
    // We need some limits here for now.

    if (spc == 0){
        debug_print("fatWriteCluster: spc\n");
        return;
    }

    for ( i=0; i < spc; i++ )
    {
        write_lba ( address, (sector + i) );
        address = (address +512); 
    };

    //...

    //return 0;  //#todo
}


// Save fat into the disk.
// Low level. It doesn't check the status of the fat cache.
int 
fs_save_fat ( 
    unsigned long fat_address, 
    unsigned long fat_lba, 
    size_t fat_size )
{

// #bugbug: 
// Debug provisório.
    debug_print ("fs_save_fat:\n");
    printf      ("Saving fat\n");
    refresh_screen();

// Filters

    if (fat_address == 0){
        panic("fs_save_fat: fat_address\n");
    }
    if (fat_lba == 0){
        panic("fs_save_fat: fat_lba\n");
    }
    // VOLUME1_FAT_SIZE
    // Only one size for now
    if (fat_size != VOLUME1_FAT_SIZE){
        panic("fs_save_fat: fat_size\n");
    }

// Do save!
    __do_save_sequence(
        (unsigned long) fat_address,
        (unsigned long) fat_lba,
        (size_t) fat_size );

// #bugbug: 
// Debug provisório.
    debug_print ("fs_save_fat: Done\n");
    printf      ("fs_save_fat: Done\n"); 
    refresh_screen ();

    return 0;
}


/*
 * fs_save_rootdir:
 *     Salva o diretório raiz no disco.
 *     @todo: Identificar parâmetros do sistema de arquivos atual. 
 */

int 
fs_save_rootdir ( 
    unsigned long root_address, 
    unsigned long root_lba, 
    size_t root_size )
{


// #bugbug: 
// Debug
    debug_print ("fs_save_rootdir:\n");
    printf      ("Saving rootdir\n");
    refresh_screen();

// Filters

    if (root_address == 0){
        panic("fs_save_rootdir: root_address\n");
    }
    if (root_lba == 0){
        panic("fs_save_rootdir: root_lba\n");
    }
    // 32 setores
    // 512 entradas de 32 bytes cada.
    // Only one size for now
    if (root_size != 32){
        panic("fs_save_rootdir: root_size\n");
    }

// Do save!
    __do_save_sequence(
        (unsigned long) root_address,
        (unsigned long) root_lba,
        (size_t) root_size );

// #bugbug: 
// Debug provisório.
    debug_print ("fs_save_rootdir: Done\n");
    printf      ("fs_save_rootdir: Done\n"); 
    refresh_screen ();

    return 0;
}


//
// End
//


