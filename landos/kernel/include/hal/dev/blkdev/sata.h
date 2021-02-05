/*
 * Arquivo: sata.h
 *
 * Descrição:
 *     Header para rotinas de hardware para drivers de SATA. hdd.
 *
 * The actual SATA specification is split into three distinct protocol 'layers'.
 * Physical Layer - Information relating to the physical connectors, etc. Not especially relevant here.
 * Link Layer
 * Transport Layer
 *
 * Computers that are currently shipped often are AHCI only, and backwards compatibility mode, if present, has to be manually enabled from the BIOS
 *   a change that often comes with the cost of making the installed OSes unbootable.
 *
 * Detection and Initialization:
 * Send a standard IDENTIFY command to the drive (0xEC).
 * The drive should respond with an error in the ERR bit of the Status Register, and a pair of "signature bytes".
 * On the Primary ATA bus, you get the signature bytes by reading IO ports 
 * 0x1F4 and 0x1F5, and you should see values of 0x3C and 0xC3.
 *
 * Opções:
 * Virtual box: // 8086, 2829  //Intel(R) ICH8M SATA AHCI Controller.
 *
 * 2015 - Created by Fred Nora.
 */



#ifndef ____SATA_H
#define ____SATA_H


#define  SATA_SIG_ATA    0x00000101  // SATA drive
#define  SATA_SIG_ATAPI  0xEB140101  // SATAPI drive
#define  SATA_SIG_SEMB   0xC33C0101  // Enclosure management bridge
#define  SATA_SIG_PM     0x96690101  // Port multiplier
 

#define  AHCI_DEV_NULL    0
#define  AHCI_DEV_SATA    1
#define  AHCI_DEV_SEMB    2
#define  AHCI_DEV_PM      3
#define  AHCI_DEV_SATAPI  4

 
#define  HBA_PORT_IPM_ACTIVE     1
#define  HBA_PORT_DET_PRESENT    3


 
unsigned long sata_handler_address; 

void probe_port(HBA_MEM *abar); 
static int check_type(HBA_PORT *port);

 
#endif  

 
//
// End.
//


