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
 * Versão 1.0, 2015.
 */

 
unsigned long sata_handler_address; 
 
//
//fim.
//


