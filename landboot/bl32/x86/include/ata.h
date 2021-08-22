/*
 * File: ata.h
 *
 * Essas rotinas fazem parte do projeto Sirius e são usadas aqui
 * para suporte à IDE/AHCI.
 *
 * 2018 - Created by Nelson Cole. 
 */

/*
 * credits:
 * Khole Operating System
 * ata/ata.h 
 * Copyright (C) 2017,2018 Nelson Cole <nelsoncole72@gmail.com>
 */


#ifndef __ATA_H__
#define __ATA_H__


// nelson cole
// suporte a disco.
// usado no kernel base



//
// ==========================================================================
//     IDE controller support by Nelson Cole
// ==========================================================================
//


int ATAFlag;
#define FORCEPIO 1234




/*
//
// Definições de tipos usados pelo Nelson el disk.h e disk.c
//
// See: types.h

typedef char _i8;
typedef short _i16;
typedef int _i32;
typedef long long _i64;

typedef unsigned char _u8;
typedef unsigned short _u16;
typedef unsigned long _u32;
typedef unsigned long long _u64;

//typedef unsigned char uint8_t;
//typedef unsigned short uint16_t;
//typedef unsigned long uint32_t;
typedef unsigned long long uint64_t;

typedef void _void;

*/

// IO Delay.
#define io_delay() asm("out %%al,$0x80"::);


// Atenção:
// Esse endereço está na memória baixa.
//#define DMA_PHYS_ADDR0 (0x40000)
//#define DMA_PHYS_ADDR1 (DMA_PHYS_ADDR0 + 0x10000)
//#define DMA_PHYS_ADDR2 (DMA_PHYS_ADDR1 + 0x10000)
//#define DMA_PHYS_ADDR3 (DMA_PHYS_ADDR2 + 0x10000)



//
// ## bug bug precisamos encontrar endereços válidos.
//

//#bugbug: precisa encontrar endereços válidos.
//user mode 1:1
#define DMA_PHYS_ADDR0 0xa0000
#define DMA_PHYS_ADDR1 0xb0000
#define DMA_PHYS_ADDR2 0xb0000
#define DMA_PHYS_ADDR3 0xb0000 



#define PCI_CLASSE_MASS 1

// Controladores de unidades ATA.
#define ATA_IDE_CONTROLLER  0x1
#define ATA_RAID_CONTROLLER 0x4
#define ATA_AHCI_CONTROLLER 0x6

// Retorno da inicializacao PCI. 
#define PCI_MSG_ERROR       -1
#define PCI_MSG_AVALIABLE   0x80
#define PCI_MSG_SUCCESSFUL  0


// IO Space Legacy BARs IDE. 
#define ATA_IDE_BAR0 0x1F0  // Primary Command Block Base Address.
#define ATA_IDE_BAR1 0x3F6  // Primary Control Block Base Address.
#define ATA_IDE_BAR2 0x170  // Secondary Command Block Base Address.
#define ATA_IDE_BAR3 0x376  // Secondary Control Block Base Address.
#define ATA_IDE_BAR4 0      // Bus Master Base Address.
#define ATA_IDE_BAR5 0      // Usado pelo AHCI.




// ATA/ATAPI Command Set.

#define ATA_CMD_CFA_ERASE_SECTORS               0xC0
#define ATA_CMD_CFA REQUEST_EXTENDED_ERROR_CODE 0x03
#define ATA_CMD_CHECK_MEDIA_CARD_TYPE           0xD1
#define ATA_CMD_CHECK_POWER_MODE                0xE5
#define ATA_CMD_DEVICE_RESET                    0x08
#define ATA_CMD_EXECUTE_DEVICE_DIAGNOSTIC       0x90
#define ATA_CMD_FLUSH_CACHE                     0xE7
#define ATA_CMD_FLUSH_CACHE_EXT                 0xEA
#define ATA_CMD_IDENTIFY_DEVICE                 0xEC
#define ATA_CMD_IDENTIFY_PACKET_DEVICE          0xA1
#define ATA_CMD_PACKET                          0xA0
#define ATA_CMD_READ_BUFFER                     0xE4
#define ATA_CMD_READ_DMA                        0xC8
#define ATA_CMD_READ_DMA_EXT                    0x25
#define ATA_CMD_READ_SECTORS                    0x20
#define ATA_CMD_READ_SECTORS_EXT                0x24
#define ATA_CMD_WRITE_BUFFER                    0xE8
#define ATA_CMD_WRITE_DMA                       0xCA
#define ATA_CMD_WRITE_DMA_EXT                   0x35
#define ATA_CMD_WRITE_SECTORS                   0x30
#define ATA_CMD_WRITE_SECTORS_EXT               0x34

// ATAPI descrito no SCSI.
#define ATAPI_CMD_READ  0xA8
#define ATAPI_CMD_EJECT 0x1B

//ATA bits de status control (alternativo).
#define ATA_SC_HOB  0x80    // High Order Byte.
#define ATA_SC_SRST 0x04    // Soft Reset.
#define ATA_SC_nINE 0x02    // INTRQ.




//ATA bits de status. 
#define ATA_SR_BSY  0x80    // Busy
#define ATA_SR_DRDY 0x40    // Device Ready
#define ATA_SR_DF   0x20    // Device Fault
#define ATA_SR_DSC  0x10    // Device Seek Complete
#define ATA_SR_DRQ  0x08    // Data Request
#define ATA_SR_SRST 0x04    // 
#define ATA_SR_IDX  0x02    // Index
#define ATA_SR_ERR  0x01    // Error

//ATA bits de errro após a leitura.
#define ATA_ER_BBK   0x80    // 
#define ATA_ER_UNC   0x40    //
#define ATA_ER_MC    0x20    //
#define ATA_ER_IDNF  0x10    //
#define ATA_ER_MCR   0x08    //
#define ATA_ER_ABRT  0x04    //
#define ATA_ER_TK0NF 0x02    //
#define ATA_ER_AMNF  0x01    //

// Registradores. 
#define ATA_REG_DATA     0x00
#define ATA_REG_ERROR    0x01
#define ATA_REG_FEATURES 0x01
#define ATA_REG_SECCOUNT 0x02
#define ATA_REG_LBA0     0x03
#define ATA_REG_LBA1     0x04
#define ATA_REG_LBA2     0x05
#define ATA_REG_DEVSEL   0x06
#define ATA_REG_CMD      0x07
#define ATA_REG_STATUS   0x07


// Devices.
#define ATA_MASTER_DEV 0x00
#define ATA_SLAVE_DEV  0x01

// Bus.
#define ATA_PRIMARY   0x00
#define ATA_SECONDARY 0x01

// ATA type.
#define ATA_DEVICE_TYPE   0x00
#define ATAPI_DEVICE_TYPE 0x01

// Modo de transferência.
#define ATA_PIO_MODO 0 
#define ATA_DMA_MODO 1
#define ATA_LBA28    28
#define ATA_LBA48    48



/*
 * dev_nport:
 *
 */

struct dev_nport 
{ 
    unsigned char dev0;
    unsigned char dev1;
    unsigned char dev2;
    unsigned char dev3;
    unsigned char dev4;
    unsigned char dev5;
    unsigned char dev6;
    unsigned char dev7;
    unsigned char dev8;
    unsigned char dev9;
    unsigned char dev10;
    unsigned char dev11;
    unsigned char dev12;
    unsigned char dev13;
    unsigned char dev14;
    unsigned char dev15;
    unsigned char dev16;
    unsigned char dev17;
    unsigned char dev18;
    unsigned char dev19;
    unsigned char dev20;
    unsigned char dev21;
    unsigned char dev22;
    unsigned char dev23;
    unsigned char dev24;
    unsigned char dev25;
    unsigned char dev26;
    unsigned char dev27;
    unsigned char dev28;
    unsigned char dev29;
    unsigned char dev30;
    unsigned char dev31;
};
struct dev_nport dev_nport;


//
// História:
//     Programação do ATA a partir do ICH5/9 e suporte a IDE legado.
//     ICH5 integraçao do SATA e suporte total ACPI 2.0.
//     ICH6 implementaram os controladores AHCI SATA pela primeira vez.
//


/*
 * ata_pci:
 *     Suporta a IDE Controller.
 *     Essa é uma estrutura de superte a discos ata.
 */
struct ata_pci
{
    _u16 vendor_id;
    _u16 device_id;
    _u16 command;
    _u16 status;
    _u8  prog_if;
    _u8  revision_id;
    _u8  classe;
    _u8  subclasse;
    _u8  primary_master_latency_timer;
    _u8  header_type;
    _u8  BIST;
    _u32 bar0;
    _u32 bar1; 
    _u32 bar2;
    _u32 bar3;
    _u32 bar4;
    _u32 bar5;
    _u16 subsystem_vendor_id;
    _u16 subsystem_id;  
    _u32 capabilities_pointer;
    _u8  interrupt_line;
    _u8  interrupt_pin;

    // AHCI

};

struct ata_pci ata_pci;



/*
 * ata:
 *     Estrutura para o controle de execução do programa.
 */ 

struct ata
{
    //int used;
    //int magic;

    uint8_t  chip_control_type;
    uint8_t  channel;
    uint8_t  dev_type;
    uint8_t  dev_num;
    uint8_t  access_type;
    uint8_t  cmd_read_modo;
    uint32_t cmd_block_base_address;
    uint32_t ctrl_block_base_address;
    uint32_t bus_master_base_address;
    uint32_t ahci_base_address;
	
};
struct ata ata;


/*
 * st_dev:
 *
 */

typedef struct st_dev st_dev_t;
typedef struct st_dev 
{
    _u32 dev_id;
    _u8  dev_nport;
    _u8  dev_type;            // ATA or ATAPI
    _u8  dev_num;
    _u8  dev_channel;
    _u8  dev_access;          // LBA28 or LBA48
    _u8  dev_modo_transfere;
    _u32 dev_byte_per_sector;
    _u32 dev_total_num_sector;
    _u64 dev_total_num_sector_lba48;
    _u32 dev_size;
       
    struct st_dev *next;
}st_dev;


//
// variables
//

_u16 *ata_identify_dev_buf;
_u8 ata_record_dev;
_u8 ata_record_channel;


//
// prototypes
//


// ata_dev.c
int nport_ajuste(char nport);
void ide_mass_storage_initialize();
int ide_dev_init(char port);


// ata_main.c
void set_ata_addr(int channel);


// ata.c
int ide_identify_device(uint8_t nport);
void ata_wait(int val);
_u8 ata_wait_not_busy();
_u8 ata_wait_busy();
_u8 ata_wait_no_drq();
_u8 ata_wait_drq();
_u8 ata_wait_irq();
_u8 ata_status_read();
void ata_cmd_write(int cmd_val);

_u8 ata_assert_dever(char nport);


// ata_pio.c
void ata_pio_read(_void *buffer,_i32 bytes);
void ata_pio_write(_void *buffer,_i32 bytes);

// ide.c



//ide_dma.c
void 
ide_dma_data ( 
    void *addr, 
    uint16_t byte_count, 
    uint8_t flg, 
    uint8_t nport );
void ide_dma_start();
void ide_dma_stop();
int ide_dma_read_status();


//ahci.c
void ahci_mass_storage_init();


//
// PCI support.
//


// PCI READ.
uint32_t 
diskReadPCIConfigAddr ( 
    int bus, 
    int dev,
    int fun, 
    int offset );


// PCI WRITE.
void 
diskWritePCIConfigAddr ( 
    int bus, 
    int dev,
    int fun, 
    int offset, 
    int data );

uint32_t diskPCIScanDevice( int class );


int 
diskATAPCIConfigurationSpace ( 
    char bus, 
    char dev, 
    char fun );


/*
 ****************************************************************
 * diskATAInitialize:
 *     Inicializa o IDE e mostra informações sobre o disco.
 */

int diskATAInitialize( int ataflag );


/*
 *******************************************
 * diskATADialog:
 *     Rotina de diálogo com o driver ATA.
 */

int 
diskATADialog ( 
    int msg, 
    unsigned long long1, 
    unsigned long long2 );

int disk_ata_wait_irq();

void show_ide_info();


#endif








