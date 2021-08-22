/*
 * File: gdef.h
 * 
 * Global definitions for the boot loader.
 * Put this in the top of the includes.
 *
 * History:
 *     2016 - Created by Fred Nora.
 */



//
// ==  The boot block structure.
//

// #todo
// It needs to be the same shape of the bootblock structure
// found in the boot manager (BM.BIN), in bootloader.inc.

struct boot_block_d
{
    unsigned long lfb;
    unsigned long x;
    unsigned long y;
    unsigned long bpp;
    unsigned long last_valid_address;
    unsigned long metafile_address;
    unsigned long disk_number;
    unsigned long heads; 
    unsigned long spt; 
    unsigned long cylinders; 
    unsigned long boot_mode; 
    unsigned long gramado_mode;
    //...
};

struct boot_block_d BootBlock;


//
// =====================================================
//


// main flags.
int gdefLegacyBIOSBoot;
int gdefEFIBoot;
int gdefSafeBoot;
int gdefShowLogo;
int gdefShowProgressBar;
//...



// + Objects.
// + Global structs.
// ...



// Essa flag será lida pela rotina de falta de página.
// para ignorar e não parar o sistema.
int ____testing_memory_size_flag;
unsigned long __last_valid_address; //salvando o úlltimo endereço válido


//
// End.
//

