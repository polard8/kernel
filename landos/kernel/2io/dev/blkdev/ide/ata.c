
// ata handshake.
// write command and read status.


#include <kernel.h>  


extern st_dev_t *current_dev;

void __local_io_delay (void);




void ata_wait (int val)
{

    if ( val <= 0 )
    {
        val = 400;
    }

    val = ( val/100 );

    while (val--)
    {
        io_delay();
    };
}


// Forces a 400 ns delay.
void ata_delay (void)
{
    int i=0;

    // Waste some time.
    for (i=0; i < 5; i++)
    {
        //__x86_io_delay();
        __local_io_delay();
    };
}


void __local_io_delay (void)
{
    asm ("xorl %%eax, %%eax" ::);
    asm ("outb %%al, $0x80" ::);
    return;
}





// #bugbug
// Lê o status de um disco determinado, se os valores na estrutura 
// estiverem certos.

unsigned char ata_status_read (void)
{
    return in8 ( ata.cmd_block_base_address + ATA_REG_STATUS );
}

void ata_cmd_write (int cmd_val)
{
    // no_busy 

    ata_wait_not_busy ();
    out8 ( ata.cmd_block_base_address + ATA_REG_CMD, cmd_val );

	// #todo
	// Esperamos 400ns

    ata_wait (400);  
}


// ata soft reset. 
void ata_soft_reset (void)
{
    // #todo
    // Review this thing.

    //unsigned char data = in8 ( ata.ctrl_block_base_address + 2 );
    unsigned char data = in8 ( ata.ctrl_block_base_address );
    
    out8 ( ata.ctrl_block_base_address, data | 0x4 );
    out8 ( ata.ctrl_block_base_address, data & 0xfb );
}



unsigned char ata_wait_drq (void)
{

    while (!(ata_status_read () & ATA_SR_DRQ))
        if ( ata_status_read () & ATA_SR_ERR )
            return 1;

    return 0;
} 

unsigned char ata_wait_no_drq (void)
{

    while ( ata_status_read() & ATA_SR_DRQ )
        if ( ata_status_read() & ATA_SR_ERR )
            return 1;

    return 0;
}


unsigned char ata_wait_busy (void)
{

    while (!(ata_status_read() & ATA_SR_BSY ))
        if ( ata_status_read() & ATA_SR_ERR )
            return 1;

    return 0;
}


// TODO: 
// Ao configurar os bits BUSY e DRQ devemos verificar retornos de erros.

unsigned char ata_wait_not_busy (void)
{

    while ( ata_status_read() & ATA_SR_BSY )
        if ( ata_status_read() & ATA_SR_ERR )
            return 1;

    return 0;
}




// #atenção.
extern st_dev_t *current_dev;


void set_ata_addr (int channel)
{

    // #todo
    // filtrar limites.
    
    switch (channel){

        case ATA_PRIMARY:
            ata.cmd_block_base_address  = ATA_BAR0;
            ata.ctrl_block_base_address = ATA_BAR1;
            ata.bus_master_base_address = ATA_BAR4;
            break;

        case ATA_SECONDARY:
            ata.cmd_block_base_address  = ATA_BAR2;
            ata.ctrl_block_base_address = ATA_BAR3;
            ata.bus_master_base_address = ATA_BAR4 + 8;
            break;

        //default:
            //PANIC
            //break;
    };
}



// Set up the ata.xxx structure.
// #todo: Where is that structure defined?
// See: hal/dev/blkdev/ata.h
// De acordo com a porta, saberemos se é 
// primary ou secondary e se é
// master ou slave.

unsigned char ata_assert_dever (char nport)
{

    // todo
    // filtrar limits.

    switch (nport){

    case 0:
        ata.channel = ATA_PRIMARY; //0;  // primary
        ata.dev_num = ATA_MASTER;  //0;  // not slave ATA_MASTER
        break;

    case 1: 
        ata.channel = ATA_PRIMARY; //0;  // primary
        ata.dev_num = ATA_SLAVE;   //1;  // slave    ATA_SLAVE
        break;

    case 2:
        ata.channel = ATA_SECONDARY;  //1;  // secondary
        ata.dev_num = ATA_MASTER;     //0;  // not slave ATA_MASTER
        break;

    case 3:
        ata.channel = ATA_SECONDARY;  //1;  // secondary
        ata.dev_num = ATA_SLAVE;      //1;  // slave    ATA_SLAVE
        break;

    default:
        // panic ?
        printk ("Port %d not used\n", nport );
        return -1;
        break;
    };


    set_ata_addr (ata.channel);

    return 0;
}

void ata_pio_read ( void *buffer, int bytes )
{

// #todo:
// avoid this for compatibility with another compiler.

    asm volatile  (\
        "cld;\
        rep; insw"::"D"(buffer),\
        "d"(ata.cmd_block_base_address + ATA_REG_DATA),\
        "c"(bytes/2) );
}


void ata_pio_write ( void *buffer, int bytes )
{

// #todo:
// avoid this for compatibility with another compiler.

    asm volatile  (\
        "cld;\
        rep; outsw"::"S"(buffer),\
        "d"(ata.cmd_block_base_address + ATA_REG_DATA),\
        "c"(bytes/2) );
}



/*
 * atapi_pio_read:
 * 
 */
 
static inline void atapi_pio_read ( void *buffer, uint32_t bytes )
{

// #todo
// Avoid this for compatibility with another compiler.

    asm volatile  (\
        "cld;\
        rep; insw"::"D"(buffer),\
        "d"(ata.cmd_block_base_address + ATA_REG_DATA),\
        "c"(bytes/2) );
}

// primary or secondary
int ata_get_current_ide_channel(void)
{
    return (int) g_current_ide_channel;
}


// master or slave
int ata_get_current_ide_device(void)
{
    return (int) g_current_ide_device;
}


// primary or secondary
void ata_set_current_ide_channel(int channel)
{
    g_current_ide_channel = channel;
}

// master or slave
void ata_set_current_ide_device(int device)
{
    g_current_ide_device = device;
}

// ====================================



// primary or secondary
int ata_get_boottime_ide_channel(void)
{
    return (int) g_boottime_ide_channel;
}


// master or slave
int ata_get_boottime_ide_device(void)
{
    return (int) g_boottime_ide_device;
}

// primary or secondary
void ata_set_boottime_ide_channel(int channel)
{
    g_boottime_ide_channel = channel;
}


// master or slave
void ata_set_boottime_ide_device(int device)
{
    g_boottime_ide_device = device;
}  



int 
ata_ioctl ( 
    int fd, 
    unsigned long request, 
    unsigned long arg )
{
    debug_print("ata_ioctl: [TODO] \n");
    return -1;
}


/*
 *******************************************
 * ata_initialize:
 *     Inicializa o IDE e mostra informações sobre o disco.
 */
 
int ata_initialize ( int ataflag )
{
    debug_print("ata_initialize: [TODO] \n");
    return -1;
}










