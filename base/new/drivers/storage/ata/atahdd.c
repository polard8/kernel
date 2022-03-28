
// atahdd.c

#include <kernel.h>  


uint8_t hdd_ata_status_read (unsigned int port_index)
{
    unsigned short port=0;

    if (port_index>3){
        panic("hdd_ata_status_read: port_index\n");
    }

// #bugbug: 
// Rever o offset.

    port = (unsigned short) (ide_ports[port_index].base_port + 7);

    return (uint8_t) in8( (unsigned short) port );
}


void 
hdd_ata_cmd_write ( 
    unsigned int port_index, 
    unsigned char cmd_val )
{

    unsigned short port=0;

    if (port_index>3){
        panic("hdd_ata_cmd_write: port_index");
    }

// no_busy 
    hdd_ata_wait_not_busy (port_index);

    port = (unsigned short) (ide_ports[port_index].base_port + 7);

    out8( 
        (unsigned short) port, 
        (unsigned char) cmd_val );

    ata_wait (400);  
}


int hdd_ata_wait_not_busy (unsigned int port_index)
{
    if (port_index>3){
        panic("hdd_ata_wait_not_busy: port_index\n");
    }

    while ( hdd_ata_status_read(port_index) & ATA_SR_BSY )
    {
        if ( hdd_ata_status_read(port_index) & ATA_SR_ERR )
        {
            return TRUE;
        }
    };

    return FALSE;
}


int hdd_ata_wait_no_drq (unsigned int port_index)
{
    if (port_index>3){
        panic("hdd_ata_wait_no_drq: port_index");
    }

    while ( hdd_ata_status_read(port_index) & ATA_SR_DRQ)
    {
        if (hdd_ata_status_read(port_index) & ATA_SR_ERR)
        {
            return TRUE;
        }
    };

    return FALSE;
}


// #todo: buffer address 64bit
// IN:
// + port - ata port. (0~3)
// + buffer
// + bytes
void 
hdd_ata_pio_read ( 
    unsigned int port_index, 
    void *buffer, 
    int bytes )
{
    unsigned short port=0;
    unsigned long next_lba=0;

    int nwords=0;

    //debug_print("hdd_ata_pio_read:\n");

    if ( port_index > 3 ){
        panic("hdd_ata_pio_read: We only support 4 ata ports\n");
    }

    // bytes/2
    nwords = (int)(bytes >> 1);

    // #todo
    // What is the limit for the current disk?
    // ex: (32*1024*1024/2) sectors for 32mb disk.
    // (32*1024*1024/2) = 16777216

    unsigned long TestMaxLBA = 16777216;

    if ( next_lba >= TestMaxLBA ){
        panic("hdd_ata_pio_read: [debug] Trying to read outside the temporary limit\n");
    }

// ================================
// #todo
// Se possível, invocar a rotina padrão para portas.
// See: ports64.c

    //#todo
    //if ( (void*) buffer == NULL ){ return; );

    //ATA_REG_DATA
    port = (unsigned short) (ide_ports[port_index].base_port + 0);

    asm volatile (\
        "cld;\
        rep; insw":: "D" (buffer),\
        "d" ( (unsigned short) port ),\
        "c" (nwords) );

    //debug_print("hdd_ata_pio_read: done\n");
}


// #todo: buffer address 64bit
// IN:
// + port - ata port. (0~3)
// + buffer
// + bytes
void 
hdd_ata_pio_write ( 
    unsigned int port_index, 
    void *buffer, 
    int bytes )
{
    unsigned short port=0;
    unsigned long next_lba=0;

    int nwords=0;

    if ( port_index > 3 ){
        panic("hdd_ata_pio_write: We only support 4 ata ports\n");
    }


    // bytes/2
    nwords = (int)(bytes >> 1);


    // #todo
    // What is the limit for the current disk?
    // ex: (32*1024*1024/2) sectors for 32mb disk.
    // (32*1024*1024/2) = 16777216

    unsigned long TestMaxLBA = 16777216;

    if ( next_lba >= TestMaxLBA ){
        panic("hdd_ata_pio_write: Trying to write outside the disk limits\n");
    }


// ================================
// #todo
// Se possível, invocar a rotina padrão para portas.
// See: ports64.c

    //#todo
    //if ( (void*) buffer == NULL ){ return; );

    port = (unsigned short) (ide_ports[port_index].base_port + 0);

    asm volatile (\
        "cld;\
        rep; outsw"::"S" (buffer),\
        "d" ( (unsigned short) port ),\
        "c" (nwords));
}


/*
 * pio_rw_sector:
 * 
 * IN:
 *   buffer - Buffer address. ??? virtual address ??
 *   lba - LBA number 
 *   rw - Flag read or write.
 *
 *   //inline unsigned char in8 (int port)
 *   //out8 ( int port, int data )
 *   (IDE PIO)
 */

// Read and write via pio mode.
int 
pio_rw_sector ( 
    unsigned long buffer, 
    unsigned int _lba, 
    int rw, 
    unsigned int port_index )
{
    unsigned short port=0;
    unsigned char c=0;
    unsigned int lba = (unsigned int) _lba;


    if (rw<0)
    {
         // msg?
         return (-1);
    }

// 0~3
// We only support 4 ports.
    port_index = (unsigned int) (port_index & 0xFF);

    if( port_index > 3 ){
        panic ("pio_rw_sector: We only support 4 ata ports.");
    }


// #todo
// Maybe check the limits for lba.
// Based on the current disk's properties.

// =========================

	//Selecionar se é master ou slave.
	//outb (0x1F6, slavebit<<4)
	//0 - 3     In CHS addressing, bits 0 to 3 of the head. 
	//          In LBA addressing, bits 24 to 27 of the block number
	//4 DRV Selects the drive number.
	//5 1   Always set.
	//6 LBA Uses CHS addressing if clear or LBA addressing if set.
	//7 1   Always set.


// =================================================
// 0x01F6 
// Port to send drive and bit 24 - 27 of LBA
// Setup the bit 24-27 of the lba.

    lba = (int) (_lba >> 24);

// no bit 4.
// 0 = master 
// 1 = slave
// master. bit 4 = 0
// 1110 0000b;
// slave. bit 4 = 1
//1111 0000b;

    int is_slave=0;

    is_slave = ide_ports[port_index].dev_num;

    if( is_slave != FALSE && is_slave != TRUE )
        panic("pio_rw_sector: is_slave");


// not slave
    if (is_slave == FALSE){ 
        lba = (unsigned int) (lba | 0x000000E0);
    }

// slave
    if (is_slave == TRUE){
        lba = (unsigned int) (lba | 0x000000F0);
    }

    port = (unsigned short) (ide_ports[port_index].base_port + 6);
    out8 ( 
        (unsigned short) port, 
        (unsigned char) lba );

// =================================================
// 0x01F2: 
// Port to send, number of sectors
    
    port = (unsigned short) (ide_ports[port_index].base_port + 2);
    out8 ( 
        (unsigned short) port, 
        (unsigned char) 1 );

// =================================================
// 0x1F3: 
// Port to send, bit 0 - 7 of LBA

    lba = (unsigned int) _lba;
    lba = (unsigned int) (lba & 0x000000FF);
    port = (unsigned short) (ide_ports[port_index].base_port + 3); 
    out8 ( 
        (unsigned short) port, 
        (unsigned char) lba );


// =================================================
// 0x1F4: 
// Port to send, bit 8 - 15 of LBA

    lba = (unsigned int) _lba;
    lba = (unsigned int) (lba >> 8);
    lba = (unsigned int) (lba & 0x000000FF);
    port = (unsigned short) (ide_ports[port_index].base_port + 4); 
    out8 ( 
        (unsigned short) port, 
        (unsigned char) lba );

// =================================================
// 0x1F5  ; Port to send, bit 16 - 23 of LBA

    lba = (unsigned int) _lba;
    lba = (unsigned int) (lba >> 16);
    lba = (unsigned int) (lba & 0x000000FF);
    port = (unsigned short) (ide_ports[port_index].base_port + 5); 
    out8 ( 
        (unsigned short) port, 
        (unsigned char) lba );

// =================================================
// 0x1F7; Command port
// rw

    rw = (int) (rw & 0x000000FF);
    port = (unsigned short) (ide_ports[port_index].base_port + 7); 
    out8 ( 
        (unsigned short) port, 
        (unsigned char) rw );


// PIO or DMA ??
// If the command is going to use DMA, 
// set the Features Register to 1, otherwise 0 for PIO.

    //out8 (0x1F1, isDMA)


//
// # timeout sim, 
// não podemos esperar para sempre.
//


// #bugbug:
// Isso deve ir para cima.

    unsigned long timeout = (5000*512);

//++
// =========================
again:

// Pega um byte de status.
    port = (unsigned short) (ide_ports[port_index].base_port + 7);
    c = (unsigned char) in8 ( (unsigned short) port );

// Seleciona o bit do byte de status.
    c = (unsigned char) ( c & 8 );

// Checa o estado do bit.
    if ( c == 0 )
    {
        timeout--;

        if ( timeout == 0 )
        {
            printf ("pio_rw_sector: rw sector timeout fail\n");
            // refresh_screen(); ??
            return -3;
        }

        // #bugbug: 
        // Isso pode enrroscar aqui.
        goto again;
    }
// ================================
//--


//
// Read or write.
//

    switch (rw){

// read
// #todo: buffer address 64bit

    case 0x20:
        // read
        hdd_ata_pio_read ( 
            (unsigned int) port_index, 
            (void *) buffer, 
            (int) 512 );
        return 0;
        break;

// write
// #todo: buffer address 64bit

    case 0x30:
        // write
        hdd_ata_pio_write ( 
            (unsigned int) port_index, 
            (void *) buffer, 
            (int) 512 );

        //Flush Cache
        hdd_ata_cmd_write ( 
            (unsigned short) port_index, 
            (unsigned char) ATA_CMD_FLUSH_CACHE );
 
        hdd_ata_wait_not_busy (port_index);
        if ( hdd_ata_wait_no_drq(port_index) != 0)
        {
            // msg?
            return -1;
        }
        return 0;
        break;

// fail
    default:
        panic ("pio_rw_sector: fail *hang");
        break; 
    };

    return 0;
}


/*
 *****************************************
 * ataReadSector:
 * 
 * buffer - buffer
 * lba - lba
 * reserved1 - null
 * reserved2 - null
 */

// #todo
// Só falta conseguirmos as variáveis que indicam o canal e 
// se é master ou slave.

// ======================== ATENÇAO ==============================
// #IMPORTANTE:
// #todo
// Só falta conseguirmos as variáveis que indicam o canal e 
// se é master ou slave.

 
int
ataReadSector ( 
    unsigned long buffer, 
    unsigned long lba, 
    unsigned long reserved1, 
    unsigned long reserved2 )
{

    int Status=0;

// #bugbug
// This is the port index, not the channel index.
    unsigned int CurrentPortIndex = (unsigned int) ata_get_current_ide_port_index();


/*
// ====================================================
// #test
// lba limits

// #todo
// Check limits for 'buffer' and 'lba'
// The lba limits is given by the disk properties.
// For now all we have is a 32mb virtual disk.
// Our limit is (32*1024*1024)/512
// #todo
// But we need to use the ata driver to find the size
// of the disk when running the system on a real HD.
// In this case the size is bigger than the
// size of the virtual disk.
// #todo
// Cada disco tem que ter seu limite.

    unsigned long vhd_lba_limits=0;

// #bugbug
// Nao podemos calcular isso toda vez que chamarmos essa rotina,
    vhd_lba_limits = (unsigned long) ((32*1024*1024)/512);

    if ( lba >= vhd_lba_limits )
        panic("ataReadSector> lba limits");

// ====================================================
*/


// IN:
// (buffer, lba, rw flag, port number, master )

    Status = pio_rw_sector ( 
        (unsigned long) buffer, 
        (unsigned long) lba, 
        (int) 0x20,
        (unsigned int) CurrentPortIndex ); 

    return Status;
}


/*
 *************************************
 * ataWriteSector:
 * 
 * buffer - buffer
 * lba - lba
 * reserved1 - null
 * reserved2 - null
 */

int
ataWriteSector ( 
    unsigned long buffer,
    unsigned long lba,
    unsigned long reserved1,
    unsigned long reserved2 )
{

    int Status=0;

// ================ ATENÇAO ==============================
// #IMPORTANTE:
// #todo
// Só falta conseguirmos as variáveis que indicam o canal e 
// se é master ou slave.


// #todo
// Limits for 'buffer' and 'lba'.

// #bugbug
// This is the port index, not the channel index.

    unsigned int port_index = (unsigned int) ata_get_current_ide_port_index();

// IN:
// (buffer, lba, rw flag, port number, master )

    Status = pio_rw_sector ( 
        (unsigned long) buffer, 
        (unsigned long) lba, 
        (int) 0x30, 
        (unsigned int) port_index ); 

    return Status;
}


/*
 * init_hdd:
 *     Inicializa o driver de hd.
 *     @todo: Mudar para hddInit().
 */

int init_hdd (void)
{

// #todo: 
// We need to do something here.

    g_driver_hdd_initialized = (int) TRUE;
    return 0;
}

