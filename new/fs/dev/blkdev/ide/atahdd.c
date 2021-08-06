

#include <kernel.h>  



uint8_t hdd_ata_status_read (int p)
{
    if (p<0){
        panic("hdd_ata_status_read: p");
    }

    // #bugbug: 
    // Rever o offset.

    //return inb(ata[p].cmd_block_base_addr + ATA_REG_STATUS);
    return (uint8_t) in8( (int) ide_ports[p].base_port + 7);
}

int hdd_ata_wait_not_busy (int p)
{
    while ( hdd_ata_status_read(p) & ATA_SR_BSY )
    {
        if ( hdd_ata_status_read(p) & ATA_SR_ERR ){
            return 1;
        }
    };

    return 0;
}

void hdd_ata_cmd_write ( int port, int cmd_val )
{
    if (port<0)
        panic("hdd_ata_status_read: port");

    // no_busy 
    hdd_ata_wait_not_busy (port);

    //outb(ata.cmd_block_base_address + ATA_REG_CMD,cmd_val);
    out8 ( (int) ide_ports[port].base_port + 7 , (int) cmd_val );

    ata_wait (400);  
}

int hdd_ata_wait_no_drq (int p)
{
    while ( hdd_ata_status_read(p) & ATA_SR_DRQ){
        if (hdd_ata_status_read(p) & ATA_SR_ERR)
            return 1;
    };

    return 0;
}


// #todo: buffer address 64bit
static void hdd_ata_pio_read ( int p, void *buffer, int bytes )
{
    //#todo
    //if ( (void*) buffer == NULL ){ return; );

    asm volatile (\
                "cld;\
                rep; insw":: "D" (buffer),\
                "d" ( ide_ports[p].base_port + 0 ),\
                "c" (bytes/2));
}

// #todo: buffer address 64bit
void hdd_ata_pio_write ( int p, void *buffer, int bytes )
{
    //#todo
    //if ( (void*) buffer == NULL ){ return; );
    
    asm volatile (\
                "cld;\
                rep; outsw"::"S"(buffer),\
                "d"( ide_ports[p].base_port + 0 ),\
                "c"(bytes/2));
}

/*
 *******************************
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

// # Changing the lba type to 'unsigned int' 32 bit.

int 
pio_rw_sector ( 
    unsigned long buffer, 
    unsigned int lba, 
    int rw, 
    int port,
    int slave )
{
    unsigned char c=0;
    unsigned int tmplba = (unsigned int) lba;

    // msg?
    if ( port < 0 || port >= 4 )
         return -1;


	//Selecionar se é master ou slave.
	//outb (0x1F6, slavebit<<4)
	//0 - 3     In CHS addressing, bits 0 to 3 of the head. 
	//          In LBA addressing, bits 24 to 27 of the block number
	//4 DRV Selects the drive number.
	//5 1   Always set.
	//6 LBA Uses CHS addressing if clear or LBA addressing if set.
	//7 1   Always set.


	// 0x01F6 
	// Port to send drive and bit 24 - 27 of LBA

    tmplba = tmplba >> 24;



    // #todo
    // O número da porta já indica se o dispositivo é 
    // master ou slave.
    // Nesse caso nem precisamos do parâmetro 'slave'.
    // #todo
    // A intenção aqui é não usar mais o parametro 'slave'

    // See:
    // ide_ports[port].channel
    // ide_ports[port].dev_num
    
    // #debug
    if ( ide_ports[port].dev_num != slave )
    {
        panic("pio_rw_sector: [DEBUG] WRONG PARAMETER\n");
    }
    

	// no bit 4.
	// 0 = master 
	// 1 = slave

	// master. bit 4 = 0
	// 1110 0000b;

    // not slave
    if (slave == 0)
    { 
        tmplba = tmplba | 0x000000E0;
    }


	// slave. bit 4 = 1
	//1111 0000b;

    // slave
    if (slave == 1)
    {
        tmplba = tmplba | 0x000000F0;
    }

    out8 ( (int) ide_ports[port].base_port + 6 , (int) tmplba );

	// 0x01F2 ; Port to send, number of sectors
    out8 ( (int) ide_ports[port].base_port + 2 , (int) 1 );

	// 0x1F3  ; Port to send, bit 0 - 7 of LBA
    tmplba = lba;
    tmplba = tmplba & 0x000000FF;
    out8 ( (int) ide_ports[port].base_port + 3 , (int) tmplba );


	// 0x1F4  ; Port to send, bit 8 - 15 of LBA
    tmplba = lba;
    tmplba = tmplba >> 8;
    tmplba = tmplba & 0x000000FF;
    out8 ( (int) ide_ports[port].base_port + 4 , (int) tmplba );


	// 0x1F5  ; Port to send, bit 16 - 23 of LBA
    tmplba = lba;
    tmplba = tmplba >> 16;
    tmplba = tmplba & 0x000000FF;
    out8 ( (int) ide_ports[port].base_port + 5 , (int) tmplba );


	// 0x1F7; Command port
	// rw
    rw = rw & 0x000000FF;
    out8 ( (int) ide_ports[port].base_port + 7 , (int) rw );



	//PIO or DMA ??
	//If the command is going to use DMA, set the Features Register to 1, otherwise 0 for PIO.
	//out8 (0x1F1, isDMA)



	//
	// # timeout sim, 
	// não podemos esperar para sempre.
	//


    // #bugbug:
    // Isso deve ir para cima.
    unsigned long timeout = (4444*512);


again:

    c = (unsigned char) in8 ( (int) ide_ports[port].base_port + 7);

    c = ( c & 8 );


    if ( c == 0 ){

        timeout--;

        if ( timeout == 0 ){
            printf ("pio_rw_sector: rw sector timeout fail\n");
            // refresh_screen(); ??
            return -3;
        }

        // #bugbug: 
        // Isso pode enrroscar aqui.
        goto again;
    }


    switch (rw)
    {

        // read
        // #todo: buffer address 64bit
        case 0x20:
            hdd_ata_pio_read ( (int) port, (void *) buffer, (int) 512 );
            break;


        // write
        // #todo: buffer address 64bit
        case 0x30:
            hdd_ata_pio_write ( (int) port, (void *) buffer, (int) 512 );

            //Flush Cache
    
            //ata_cmd_write(p,ATA_CMD_FLUSH_CACHE);
            hdd_ata_cmd_write ( (int) port, (int) ATA_CMD_FLUSH_CACHE );
            hdd_ata_wait_not_busy (port);
            if ( hdd_ata_wait_no_drq(port) != 0)
            {
                // msg?
                return -1;
            }
            break;


        // fail
        default:
            panic ("pio_rw_sector: fail *hang");
            //die();
            break; 
    };

    return 0;
}

/*
 *****************************************
 * my_read_hd_sector:
 * 
 * eax - buffer
 * ebx - lba
 * ecx - null
 * edx - null
 * 
 * Opção: void hddReadSector(....)
 */
 
void 
my_read_hd_sector ( 
    unsigned long ax, 
    unsigned long bx, 
    unsigned long cx, 
    unsigned long dx )
{


	//======================== ATENÇAO ==============================
	// #IMPORTANTE:
	// #todo
	// Só falta conseguirmos as variáveis que indicam o canal e 
	// se é master ou slave.

    // IN:
    // (buffer, lba, rw flag, port number, master )

    pio_rw_sector ( 
        (unsigned long) ax, 
        (unsigned long) bx, 
        (int) 0x20, 
        (int) g_current_ide_channel,     // 0 ... channel
        (int) g_current_ide_device );    // 1 ... master=1 slave=0


	/*
	// #antigo.
	// Suspenso.
	// Passando os argumentos.
	 hd_buffer = (unsigned long) ax;    //arg1 = buffer. 
	 hd_lba = (unsigned long) bx;       //arg2 = lba.
	
	// Read sector. (ASM)
	os_read_sector(); 

	//#todo: deletar esse return.
	//testar sem ele antes.
	*/

    return;
}

/*
 *************************************
 * my_write_hd_sector:
 * 
 * eax - buffer
 * ebx - lba
 * ecx - null
 * edx - null
 * Opção: void hddWriteSector(....)
 */

void 
my_write_hd_sector ( 
    unsigned long ax,
    unsigned long bx,
    unsigned long cx,
    unsigned long dx )
{

	//================ ATENÇAO ==============================
	// #IMPORTANTE:
	// #todo
	// Só falta conseguirmos as variáveis que indicam o canal e 
	// se é master ou slave.


    // IN:
    // (buffer, lba, rw flag, port number, master )

    pio_rw_sector ( 
        (unsigned long) ax, 
        (unsigned long) bx, 
        (int) 0x30, 
        (int) g_current_ide_channel,     // 0 ... channel
        (int) g_current_ide_device );    // 1 ... master=1 slave=0


/*
	//antigo.
	//Passando os argumentos.
	hd_buffer = (unsigned long) ax;    //arg1 = buffer. 
	hd_lba = (unsigned long) bx;       //arg2 = lba.

	// Write sector. (ASM)
	// entry/x86/head/hwlib.inc

	os_write_sector(); 
*/


	//#todo: deletar esse return.
	//testar sem ele antes.

    return;
}


/*
 ***************************************
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















