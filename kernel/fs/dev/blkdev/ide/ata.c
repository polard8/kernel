
// ata handshake.
// write command and read status.


#include <kernel.h>  


extern st_dev_t *current_dev;


/* 
 * Obs:
 * O que segue são rotinas de suporte ao controlador IDE.
 */

st_dev_t *current_dev;       // A unidade atualmente selecionada.
st_dev_t *ready_queue_dev;   // O início da lista.

uint32_t  dev_next_pid = 0;  // O próximo ID de unidade disponível. 


// Local
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
    int Status = 1;  

    // iterator.
    int iPortNumber=0;

    unsigned char bus=0;
    unsigned char dev=0;
    unsigned char fun=0;

    int Ret = -1;


    debug_print("ata_initialize: todo \n");
    //return 0;


    // Setup interrupt breaker.
    debug_print("ata_initialize: Turn on interrupt breaker\n");

    __breaker_ata1_initialized = FALSE;
    __breaker_ata2_initialized = FALSE;


    //
    // ===============================================================
    //

    // #importante 
    // HACK HACK
    // usando as definições feitas em config.h
    // até que possamos encontrar o canal e o dispositivo certos.
    // __IDE_PORT indica qual é o canal.
    // __IDE_SLAVE indica se é master ou slave.
    // ex: primary/master.
    // See: config.h


    g_boottime_ide_channel =  __IDE_PORT;   // primary
    g_boottime_ide_device  =  __IDE_SLAVE;  // master

    // Configumos o atual como sendo o mesmo
    // usado durante o boot.
    // #todo
    // Poderemos mudar o atual conforme nossa intenção
    // de acessarmos outros discos.
    
    g_current_ide_channel =  g_boottime_ide_channel;
    g_current_ide_device  =  g_boottime_ide_device;

    //
    // ===============================================================
    //


	// Configurando flags do driver.
	// FORCEPIO = 1234

    ATAFlag = (int) ataflag;


	//
	// Messages
	//

#ifdef KERNEL_VERBOSE
    printf ("ata_initialize:\n");
    printf ("Initializing IDE/AHCI support ...\n");
#endif


	// #test
	// Sondando na lista de dispositivos encontrados pra ver se tem algum
	// controlador de disco IDE.
	// #importante:
	// Estamos sondando uma lista que contruimos quando fizemos
	// uma sondagem no começo da inicializaçao do kernel.
	// #todo: podemos salvar essa lista.
	
	// #todo
	// O que eh PCIDeviceATA?
	// Eh uma estrutura para dispositivos pci. (pci_device_d)
	// Vamos mudar de nome.

    PCIDeviceATA = (struct pci_device_d *) scan_pci_device_list2 ( 
                                        (unsigned char) PCI_CLASSCODE_MASS, 
                                        (unsigned char) PCI_SUBCLASS_IDE );

    if ( (void *) PCIDeviceATA == NULL ){
        panic ("ata_initialize: PCIDeviceATA\n");
    }else{
        if ( PCIDeviceATA->used != TRUE || PCIDeviceATA->magic != 1234 )
        {
            panic ("ata_initialize: Validation\n");
        }

		//#debug
		//kprintf ("ata-diskATAInitialize: IDE device found\n");
		//kprintf ("[ Vendor=%x Device=%x ]\n", PCIDeviceATA->Vendor, PCIDeviceATA->Device );

    };

	//
	// Vamos saber mais sobre o dispositivo encontrado. 
	//

	// #bugbug: 
	// Esse data é só um código de erro.

    Ret = (unsigned long) diskATAPCIConfigurationSpace(PCIDeviceATA);

    if ( Ret == PCI_MSG_ERROR )
    {
        printk ("ata_initialize: Error Driver [%x]\n", Ret );
        Status = (int) 1;
        goto fail;  
    }

	//
	// Salvando informações.
	//

	// Aqui estamos pegando informações na estrutura PCIDeviceATA sobre as BARs 
	// e manipulando essas informações.
	// ?? Não sei o que está fazendo aqui, talvez procurando endereço de porta.


    // Initialize base address
    // AHCI/IDE Compativel com portas IO IDE legado

    ATA_BAR0 = ( PCIDeviceATA->BAR0 & ~7 ) + ATA_IDE_BAR0 * ( !PCIDeviceATA->BAR0 );
    ATA_BAR1 = ( PCIDeviceATA->BAR1 & ~3 ) + ATA_IDE_BAR1 * ( !PCIDeviceATA->BAR1 );       
    ATA_BAR2 = ( PCIDeviceATA->BAR2 & ~7 ) + ATA_IDE_BAR2 * ( !PCIDeviceATA->BAR2 );
    ATA_BAR3 = ( PCIDeviceATA->BAR3 & ~3 ) + ATA_IDE_BAR3 * ( !PCIDeviceATA->BAR3 );

    ATA_BAR4 = ( PCIDeviceATA->BAR4 & ~0x7 ) + ATA_IDE_BAR4 * ( !PCIDeviceATA->BAR4 );
    ATA_BAR5 = ( PCIDeviceATA->BAR5 & ~0xf ) + ATA_IDE_BAR5 * ( !PCIDeviceATA->BAR5 );


	//
	// Colocando nas estruturas.
	//

    ide_ports[0].base_port = (unsigned short) ATA_BAR0;
    ide_ports[1].base_port = (unsigned short) ATA_BAR1;
    ide_ports[2].base_port = (unsigned short) ATA_BAR2;
    ide_ports[3].base_port = (unsigned short) ATA_BAR3;
	//tem ainda a porta do dma na bar4


	//
	// De acordo com o tipo.
	//


	//
	// Se for IDE.
	//


	// Type
    if ( ata.chip_control_type == ATA_IDE_CONTROLLER )
    {
        //Soft Reset, defina IRQ
        
        out8 ( ATA_BAR1, 0xff );
        out8 ( ATA_BAR3, 0xff );
        out8 ( ATA_BAR1, 0x00 );
        out8 ( ATA_BAR3, 0x00 );

        ata_record_dev     = 0xff;
        ata_record_channel = 0xff;


#ifdef KERNEL_VERBOSE
        printf ("Initializing IDE Mass Storage device ...\n");
        refresh_screen ();
#endif    


	    //
	    // As estruturas de disco serão colocadas em uma lista encadeada.
	    //

        //ide_mass_storage_initialize();


        //
        // Vamos trabalhar na lista de dispositivos.
        //

        // Iniciando a lista.
        // st_dev structure.

        ready_queue_dev = ( struct st_dev * ) kmalloc ( sizeof( struct st_dev) );

        if ( (void*) ready_queue_dev == NULL ){
            panic("ata_initialize: ready_queue_dev\n");
        }

        current_dev = ( struct st_dev * ) ready_queue_dev;

        current_dev->dev_id      = dev_next_pid++;
        current_dev->dev_type    = -1;
        
        // Channel and device.
        // ex: primary/master.

        current_dev->dev_channel = -1;
        current_dev->dev_num     = -1;

        current_dev->dev_nport   = -1;
        current_dev->next = NULL;

        // #bugbug
        // Is this a buffer ? For what ?
        // Is this bugger enough ?

        ata_identify_dev_buf = (unsigned short *) kmalloc (4096);

        if ( (void *) ata_identify_dev_buf == NULL ){
            panic ("ata_initialize: ata_identify_dev_buf\n");
        }

		// Sondando dispositivos e imprimindo na tela.
		// As primeiras quatro portas do controlador IDE. 
		
        // #todo
        // Create a constant for 'max'. 

        for ( iPortNumber=0; iPortNumber < 4; iPortNumber++ )
        {
            ide_dev_init (iPortNumber);
        };


		//
		// Agora se for AHCI.
		//

    }else if( ata.chip_control_type == ATA_AHCI_CONTROLLER )
          {

              // Nothing for now !!!
              
              panic ("ata_initialize: AHCI not supported yet\n");

              // Aqui, vamos mapear o BAR5
              // Estou colocando na marca 28MB
    
    
//#ifdef KERNEL_VERBOSE
              // printf("ata_initialize: mem_map para ahci\n");
              // refresh_screen();
//#endif


              //mem_map( (uint32_t*)0x01C00000, (uint32_t*) ATA_BAR5, 0x13, 2);

              //kputs("[ AHCI Mass Storage initialize ]\n");
              //ahci_mass_storage_init();


          }else{
              panic ("ata_initialize: IDE and AHCI not found\n");
          };


    // Ok
    
    Status = 0;
    
    goto done;


fail:
    printk ("ata_initialize: fail\n"); 

done:

    // Setup interrupt breaker.
    // Só liberamos se a inicialização fncionou.

    if ( Status == 0 ){
        debug_print("ata_initialize: Turn off interrupt breaker\n");
        __breaker_ata1_initialized = TRUE; 
        __breaker_ata2_initialized = TRUE; 
    }

    return (int) Status;
}

/*
 ********************************************
 * ide_identify_device:
 */

// ??
// O número da porta identica qual disco queremos pegar informações.
// Slavaremos algumas informações na estrutura de disco.

int ide_identify_device ( uint8_t nport )
{

    struct disk_d  *disk;

    // Signature bytes.
    unsigned char lba1 = 0; 
    unsigned char lba2 = 0;

    char name_buffer[32];
    unsigned char status=0;


    // #todo:
    // Rever esse assert. 
    // Precisamos de uma mensagem de erro aqui.
    
    ata_assert_dever(nport);

    // ??
    // Ponto flutuante
    // Sem unidade conectada ao barramento

    // #todo
    // Precisamos de uma mensagem aqui.

    if ( ata_status_read() == 0xFF )
    {
        //debug_print(...);
        return (int) -1;
    }



    // #bugbug
    // O que é isso?
    // Se estamos escrevendo em uma porta de input/output
    // então temos que nos certificar que esses valores 
    // são válidos.

    out8 ( ata.cmd_block_base_address + ATA_REG_SECCOUNT, 0 );  // Sector Count 7:0
    out8 ( ata.cmd_block_base_address + ATA_REG_LBA0,     0 );  // LBA  7-0
    out8 ( ata.cmd_block_base_address + ATA_REG_LBA1,     0 );  // LBA 15-8
    out8 ( ata.cmd_block_base_address + ATA_REG_LBA2,     0 );  // LBA 23-16

    // Select device
    out8 ( 
        ( ata.cmd_block_base_address + ATA_REG_DEVSEL), 
        0xE0 | ata.dev_num << 4 );


    //
    // Solicitando informações sobre o disco.
    //

    // cmd
    ata_wait (400);
    ata_cmd_write (ATA_CMD_IDENTIFY_DEVICE); 


    // ata_wait_irq();
    // Nunca espere por um IRQ aqui
    // Devido unidades ATAPI, ao menos que pesquisamos pelo Bit ERROR
    // Melhor seria fazermos polling

    //Sem unidade no canal

    ata_wait (400);
    
    if ( ata_status_read() == 0 )
    {
        // ??
        // Talvez precismos de uma mensagem de erro.
        return (int) -1;
    }


    // #todo
    // Use esses registradores para pegar mais informações.
    // See:
    // hal/dev/blkdev/ata.h

    // See
    // https://wiki.osdev.org/ATA_PIO_Mode
    // https://wiki.osdev.org/PCI_IDE_Controller
    
    /*
    // #exemplo:
    // get the "signature bytes" 
    unsigned cl=inb(ctrl->base + REG_CYL_LO);	
	unsigned ch=inb(ctrl->base + REG_CYL_HI);
	differentiate ATA, ATAPI, SATA and SATAPI 
	if (cl==0x14 && ch==0xEB) return ATADEV_PATAPI;
	if (cl==0x69 && ch==0x96) return ATADEV_SATAPI;
	if (cl==0 && ch == 0) return ATADEV_PATA;
	if (cl==0x3c && ch==0xc3) return ATADEV_SATA;
    */

    // Saving.
    // lba1 = in8( ata.cmd_block_base_address + ATA_REG_LBA1 );
    // lba2 = in8( ata.cmd_block_base_address + ATA_REG_LBA2 );

    // REG_CYL_LO = 4
    // REG_CYL_HI = 5

    // Getting signature bytes.
    lba1 = in8( ata.cmd_block_base_address + 4 );
    lba2 = in8( ata.cmd_block_base_address + 5 );




    /*
    // #test
    // Isso provavelmente é o número de setores envolvidos em
    // uma operação de leitura ou escrita.
    //===============
    unsigned long NumberOfSectors=0;
    NumberOfSectors = in8( ata.cmd_block_base_address + ATA_REG_SECCOUNT );
    if (NumberOfSectors>0){
       printf(">>>> %d | *breakpoint\n",NumberOfSectors);
       refresh_screen();
       while(1){}
    }
    */
    //===============

    
    // #test
    // vamos pegar mais informações. 
    
    

    //
    // # Type
    //

    // ==========================
    // # PATA
    if ( lba1 == 0 && lba2 == 0 )
    {
        // kputs("Unidade PATA\n");
        // aqui esperamos pelo DRQ
        // e eviamos 256 word de dados PIO

        ata_wait_drq();
        ata_pio_read ( ata_identify_dev_buf, 512 );

        ata_wait_not_busy();
        ata_wait_no_drq();

        // See:
        // ide.h

        ide_ports[nport].used    = (int) TRUE;
        ide_ports[nport].magic   = (int) 1234;
        ide_ports[nport].id      = (uint8_t) nport;           // Port index.
        ide_ports[nport].type    = (int) idedevicetypesPATA;  // Device type.
        ide_ports[nport].name    = "PATA";
        ide_ports[nport].channel = ata.channel;  // Primary or secondary.
        ide_ports[nport].dev_num = ata.dev_num;  // Master or slave.


        // Disk

        disk = (struct disk_d *) kmalloc ( sizeof(struct disk_d) );

        if ((void *) disk != NULL )
        {

            // See:
            // disk.h

            // Object header.
            // #todo
            //disk->objectType = ?
            //disk->objectClass = ?

            disk->used  = TRUE;
            disk->magic = 1234;

            // type and class.
            disk->diskType = DISK_TYPE_PATA;
            // disk->diskClass = ? // #todo:

            // ID and index.
            disk->id = nport;
            disk->boot_disk_number = 0; // ?? #todo


            // name
 
            // name = "sd?"
            //disk->name = "PATA-TEST";
            sprintf ( (char *) name_buffer, "PATA-TEST-%d",nport);
            disk->name = (char *) strdup ( (const char *) name_buffer);  

            // Security
            disk->pid = current_process;
            disk->gid = current_group;
            // ...

            disk->channel = ata.channel;  // Primary or secondary.
            disk->dev_num = ata.dev_num;  // Master or slave.

            // disk->next = NULL;
            
            // #bugbug
            // #todo: Check overflow.
            diskList[nport] = (unsigned long) disk;
        }

        return (int) 0;


    // ==========================
    // #SATA
    }
    else if ( lba1 == 0x3C && lba2 == 0xC3 ){

        //kputs("Unidade SATA\n");   
        // O dispositivo responde imediatamente um erro ao cmd Identify device
        // entao devemos esperar pelo DRQ ao invez de um BUSY
        // em seguida enviar 256 word de dados PIO.

        ata_wait_drq(); 
        ata_pio_read ( ata_identify_dev_buf, 512 );
        ata_wait_not_busy();
        ata_wait_no_drq();

        // See:
        // ide.h

        ide_ports[nport].used    = (int) TRUE;
        ide_ports[nport].magic   = (int) 1234;
        ide_ports[nport].id      = (uint8_t) nport;
        ide_ports[nport].type    = (int) idedevicetypesSATA;  // Device type.
        ide_ports[nport].name    = "SATA";                    // Port name.
        ide_ports[nport].channel = ata.channel;  // Primary or secondary.
        ide_ports[nport].dev_num = ata.dev_num;  // Master or slave.

        // Disk

        disk = (struct disk_d *) kmalloc (  sizeof(struct disk_d) );

        if ((void *) disk != NULL )
        {

            // See:
            // disk.h

            // Object header.
            // #todo
            //disk->objectType = ?
            //disk->objectClass = ?

            disk->used  = TRUE;
            disk->magic = 1234;

            disk->diskType = DISK_TYPE_SATA;
            // disk->diskClass = ?


            // ID and index.
            disk->id = nport;
            disk->boot_disk_number = 0; // ?? #todo


            // name

            //disk->name = "SATA-TEST";
            sprintf ( (char *) name_buffer, "SATA-TEST-%d",nport);
            disk->name = (char *) strdup ( (const char *) name_buffer);  

            // Security
            disk->pid = current_process;
            disk->gid = current_group;
              
            disk->channel = ata.channel;  // Primary or secondary.
            disk->dev_num = ata.dev_num;  // Master or slave.
 
            // disk->next = NULL;
            
            // #todo: Check overflow.
            diskList[nport] = (unsigned long) disk;
        }

        return (int) 0;


    // ==========================
    // # PATAPI
    }
    else if ( lba1 == 0x14 && lba2 == 0xEB ){

        //kputs("Unidade PATAPI\n");   
        ata_cmd_write(ATA_CMD_IDENTIFY_PACKET_DEVICE);
        ata_wait(400);
        ata_wait_drq(); 
        ata_pio_read ( ata_identify_dev_buf, 512 );
        ata_wait_not_busy();
        ata_wait_no_drq();

        // See:
        // ide.h
        
        ide_ports[nport].used    = (int) TRUE;
        ide_ports[nport].magic   = (int) 1234;
        ide_ports[nport].id      = (uint8_t) nport;
        ide_ports[nport].type    = (int) idedevicetypesPATAPI;
        ide_ports[nport].name    = "PATAPI";
        ide_ports[nport].channel = ata.channel;  // Primary or secondary.
        ide_ports[nport].dev_num = ata.dev_num;  // Master or slave.

        // Disk
        
        disk = (struct disk_d *) kmalloc (  sizeof(struct disk_d) );

        if ((void *) disk != NULL )
        {
            // See:
            // disk.h


            disk->used  = TRUE;
            disk->magic = 1234;

            disk->diskType = DISK_TYPE_PATAPI;
            // disk->diskClass = ?

            disk->id = nport;  
                        
            // name
            
            //disk->name = "PATAPI-TEST";
            sprintf ( (char *) name_buffer, "PATAPI-TEST-%d",nport);
            disk->name = (char *) strdup ( (const char *) name_buffer);  



            disk->channel = ata.channel;  // Primary or secondary.
            disk->dev_num = ata.dev_num;  // Master or slave.

            // #todo: Check overflow.
            diskList[nport] = (unsigned long) disk;
        }

        return (int) 0x80;


    // ==========================
    // # SATAPI
    }
    else if (lba1 == 0x69  && lba2 == 0x96){

        //kputs("Unidade SATAPI\n");   
        ata_cmd_write(ATA_CMD_IDENTIFY_PACKET_DEVICE);
        ata_wait(400);
        ata_wait_drq(); 
        ata_pio_read(ata_identify_dev_buf,512);
        ata_wait_not_busy();
        ata_wait_no_drq();

        // See:
        // ide.h

        ide_ports[nport].used    = (int) TRUE;
        ide_ports[nport].magic   = (int) 1234;
        ide_ports[nport].type    = (int) idedevicetypesSATAPI;
        ide_ports[nport].id      = (uint8_t) nport;
        ide_ports[nport].name    = "SATAPI";
        ide_ports[nport].channel = ata.channel;  // Primary or secondary.
        ide_ports[nport].dev_num = ata.dev_num;  // Master or slave.

        // Disk
        
        disk = (struct disk_d *) kmalloc (  sizeof(struct disk_d) );

        if ( (void *) disk != NULL )
        {

            // See:
            // disk.h

            disk->used  = TRUE;
            disk->magic = 1234;

            disk->diskType = DISK_TYPE_SATAPI;
            //disk->diskClass = ?

            disk->id = nport;  

            // name
            
            //disk->name = "SATAPI-TEST";
            sprintf ( (char *) name_buffer, "SATAPI-TEST-%d",nport);
            disk->name = (char *) strdup ( (const char *) name_buffer);  

            disk->channel = ata.channel;  // Primary or secondary.
            disk->dev_num = ata.dev_num;  // Master or slave.

            // #todo: Check overflow.
            diskList[nport] = (unsigned long) disk;
        }

        return (int) 0x80;
    };

    // fail ??
    // Is something wrong here?

    return 0; 
}

/*
 ***********************************
 * ide_dev_init:
 *     ?? Alguma rotina de configuração de dispositivos.
 */

// This routine was called by ata_initialize.

// #todo
// Agora essa função precisa receber um ponteiro 
// para a estrutura de disco usada pelo gramado.
// Para salvarmos os valores que pegamos nos registradores.

int ide_dev_init (char port)
{

    struct st_dev  *tmp_dev;
    int data=0;

    // #?
    // We have four ports in the ide controller.
    // See: ata_initialize.
    
    if (port<0){
        panic("ide_dev_init: [ERROR] port\n");
    }

    
    // See: hal/dev/blkdev/ata.h
    // st_dev_t *new_dev;
        
    struct st_dev  *new_dev;

    new_dev = ( struct st_dev * ) kmalloc ( sizeof( struct st_dev) );

    if ( (void *) new_dev ==  NULL ){
        panic ("ide_dev_init: [FAIL] new_dev\n");
    }


    //
    // data thing ??
    //

    data = (int) ide_identify_device (port);

    // #todo:
    // Penso que esse valor de '-1' for determinado 
    // por Nelson como erro.
    
    //if ( data < 0 )
    if ( data == -1 )
    {
        debug_print ("ide_dev_init: [FIXME] data\n");
        return (int) 1;
    }


    unsigned long value=0;
    unsigned long value2=0;

    // Unidades ATA.
    if ( data == 0 )
    {

        // Is it an ata device?
        new_dev->dev_type = (ata_identify_dev_buf[0] & 0x8000) ? 0xffff : ATA_DEVICE_TYPE;

        // What kind of lba?
        new_dev->dev_access = (ata_identify_dev_buf[83] & 0x0400) ? ATA_LBA48 : ATA_LBA28;

        // Let's set up the PIO support.
        // Where ATAFlag was defined?
        // Where FORCEPIO was defined?
        
        // Com esse só funciona em pio
        if (ATAFlag == FORCEPIO){
            new_dev->dev_modo_transfere = 0;

        // Com esse pode funcionar em dma
        }else{
            new_dev->dev_modo_transfere = ( ata_identify_dev_buf[49] & 0x0100 ) ? ATA_DMA_MODO : ATA_PIO_MODO;
        };


        new_dev->dev_total_num_sector  = ata_identify_dev_buf[60];
        new_dev->dev_total_num_sector += ata_identify_dev_buf[61];

        // #bugbug
        // We can not do this.
        // We need to check the supported sector size.
        // 512 or 4096 ?

        new_dev->dev_byte_per_sector = 512;

        new_dev->dev_total_num_sector_lba48  = ata_identify_dev_buf[100];
        new_dev->dev_total_num_sector_lba48 += ata_identify_dev_buf[101];
        new_dev->dev_total_num_sector_lba48 += ata_identify_dev_buf[102];
        new_dev->dev_total_num_sector_lba48 += ata_identify_dev_buf[103];

        // #bugbug
        // We can not do this.
        // We need to check the supported sector size.
        // 512 or 4096 ?

        new_dev->dev_size = (new_dev->dev_total_num_sector_lba48 * 512);

        // Pegando o size.
        // Quantidade de setores.
        // Uma parte está em 61 e outra em 60.
 
        value = ata_identify_dev_buf[61];  
        value = ( value << 16 );           
        value = ( value & 0xFFFF0000 );    
        
        value2 = ata_identify_dev_buf[60];  
        value2 = ( value2 & 0x0000FFFF );  
        
        new_dev->dev_total_num_sector = value | value2;
        
        new_dev->_MaxLBA = new_dev->dev_total_num_sector;
              
        //if ( new_dev->dev_total_num_sector > 0 )
        //{
        //     printf ("#debug: >>>> ata Size %d\n", 
        //         new_dev->dev_total_num_sector );
        //     refresh_screen();
        //     while(1){}
        //}


        // #todo
        // Agora essa função precisa receber um ponteiro 
        // para a estrutura de disco usada pelo gramado.

          // Unidades ATAPI. 
    }else if( data == 0x80 )
          {
              //  Is this an ATAPI device ?
              new_dev->dev_type = (ata_identify_dev_buf[0] & 0x8000) ? ATAPI_DEVICE_TYPE : 0xffff;

              // What kind of lba?
              new_dev->dev_access = ATA_LBA28;

              // Let's set up the PIO support.
              // Where ATAFlag was defined?
              // Where FORCEPIO was defined?

              // Com esse só funciona em pio 
              if (ATAFlag == FORCEPIO){
                  new_dev->dev_modo_transfere = 0; 

              // Com esse pode funcionar em dma
              }else{
                  new_dev->dev_modo_transfere = (ata_identify_dev_buf[49] & 0x0100) ? ATA_DMA_MODO : ATA_PIO_MODO;
              };

              // ??
              new_dev->dev_total_num_sector  = 0;
              new_dev->dev_total_num_sector += 0;

              // #bugbug
              // 2024
              // Is this standard for all kind of CD?
              // We need to get this information in some place.

              new_dev->dev_byte_per_sector = 2048; 

              new_dev->dev_total_num_sector_lba48  = 0;
              new_dev->dev_total_num_sector_lba48 += 0;
              new_dev->dev_total_num_sector_lba48 += 0;
              new_dev->dev_total_num_sector_lba48 += 0;

              // #bugbug
              // 2024
              // Is this standard for all kind of CD?
              // We need to get this information in some place.

              new_dev->dev_size = (new_dev->dev_total_num_sector_lba48 * 2048);

              // Pegando o size.
              // Quantidade de setores.
              // Uma parte está em 61 e outra em 60.
 
              value = ata_identify_dev_buf[61];  
              value = ( value << 16 );           
              value = ( value & 0xFFFF0000 );    
        
              value2 = ata_identify_dev_buf[60];  
              value2 = ( value2 & 0x0000FFFF );  
        
              new_dev->dev_total_num_sector = value | value2;
        
              new_dev->_MaxLBA = new_dev->dev_total_num_sector;
              
              //if ( new_dev->dev_total_num_sector > 0 )
              //{
              //   printf ("#debug: >>>> atapi Size %d\n", 
              //       new_dev->dev_total_num_sector );
              //   refresh_screen();
              //   while(1){}
              //}

             // #todo
             // Agora essa função precisa receber um ponteiro 
             // para a estrutura de disco usada pelo gramado.


          }else{
               debug_print ("ide_dev_init: [ERROR] not ATA, not ATAPI.\n");
               return (int) 1;
          };


    //Dados em comum.

    new_dev->dev_id = dev_next_pid++;


    //
    // ??
    // Salvando na estrutura de dispositivo as
    // informações sobre a porta ide.
    // channel and device.
    // ex: primary/master.
    // #bugbug
    // Mas temos um problema. Talvez quando essa função
    // foi chamada o dev_num ainda não tenha cido inicializado.
    //

    new_dev->dev_channel = ata.channel;
    new_dev->dev_num     = ata.dev_num;

    new_dev->dev_nport = port;


    //
    // == port ====================================
    //

    // #bugbug
    // Nao devemos confundir esses numeros com os numeros
    // gerados pelo BIOS, pois bios tambem considera
    // outras midias alem do ide.

    switch (port){

        case 0:  dev_nport.dev0 = 0x81;  break;
        case 1:  dev_nport.dev1 = 0x82;  break;
        case 2:  dev_nport.dev2 = 0x83;  break;
        case 3:  dev_nport.dev3 = 0x84;  break;

        // #atenção
        // Essa estrutura é para 32 portas.
        // para listar as portas AHCI.
        // Mas aqui está apenas listando as 4 portas IDE.

        default:
            debug_print ("ide_dev_init: [ERROR] default port number\n");
            break;
    };


    new_dev->next = NULL;


//#ifdef KERNEL_VERBOSE
    // #todo
    // kprintf("[ Detected Disk type: %s ]\n", dev_type[new_dev->dev_type] );
    // refresh_screen ();
//#endif


    // =========================================

    //
    // Add no fim da lista (ready_queue_dev).
    //

    tmp_dev = ( struct st_dev * ) ready_queue_dev;

    if ( (void *) tmp_dev ==  NULL ){
        panic ("ide_dev_init: [FAIL] tmp_dev\n");
    }

    // Linked list

    while ( tmp_dev->next )
    {
        tmp_dev = tmp_dev->next;
    };

    tmp_dev->next = new_dev;


    debug_print ("ide_dev_init: done\n");

    return 0;
}


/*
 * ide_mass_storage_initialize:
 *     Rotina de inicialização de dispositivo de armazenamento de dados.
 */

void ide_mass_storage_initialize (void)
{
    int port=0;

    //
    // Vamos trabalhar na lista de dispositivos.
    //

	// Iniciando a lista.

    ready_queue_dev = ( struct st_dev * ) kmalloc ( sizeof( struct st_dev) );

    if ( (void *) ready_queue_dev == NULL )
    {
        panic ("ide_mass_storage_initialize: ready_queue_dev\n");
    }


    current_dev = ( struct st_dev * ) ready_queue_dev;

    current_dev->dev_id = dev_next_pid++;

    current_dev->dev_type    = -1;
    current_dev->dev_num     = -1;
    current_dev->dev_channel = -1;
    current_dev->dev_nport   = -1;

    current_dev->next = NULL;

    // ??

    ata_identify_dev_buf = ( unsigned short * ) kmalloc (4096);

    if ( (void *) ata_identify_dev_buf == NULL )
    {
        panic ("ide_mass_storage_initialize: ata_identify_dev_buf \n");
    }


	//
	// Sondando dispositivos e imprimindo na tela.
	//


    // As primeiras quatro portas do controlador IDE.

    for ( port=0; port < 4; port++ )
    {
        ide_dev_init (port);
    };
}

/* 
 * dev_switch:
 *     ?? Porque esse tipo ?? 
 */

static inline void dev_switch (void)
{
    // ??
    // Pula, se ainda não tiver nenhuma unidade.

    if ( !current_dev )
    {
        return;
    }


    // Obter a próxima tarefa a ser executada.
    // Se caímos no final da lista vinculada, 
    // comece novamente do início.

    current_dev = current_dev->next;    
    
    if ( !current_dev )
    {
        current_dev = ready_queue_dev;
    }
}

static inline int getnport_dev (void)
{

    if ( (void *) current_dev == NULL )
        return -1;

    return current_dev->dev_nport;
}

static inline int getpid_dev (void)
{
    if ( (void *) current_dev == NULL )
    {
        return -1;
    }

    return current_dev->dev_id;
}

int nport_ajuste ( char nport )
{
    char i = 0;

    // #todo
    // Simplify this thing.
 
    while ( nport != getnport_dev() )
    {
        if ( i == 4 )
        { 
            return (int) 1; 
        }
        
        dev_switch ();
        
        i++;
    };

    if ( getnport_dev() == -1 )
    { 
        return (int) 1; 
    }

    return 0;
}

/*
 **************************************************
 * show_ide_info:
 *     Mostrar as informações obtidas na inicializações 
 * do controlador.
 */

// #todo
// Not used. Please, call this routine.

void show_ide_info (void)
{
    int i=0;

    printf ("\n  show_ide_info:  \n");

    for ( i=0; i<4; i++ )
    {
        printf ("id=%d \n", ide_ports[i].id );
        printf ("channel=%d dev_num=%d \n", 
            ide_ports[i].channel, 
            ide_ports[i].dev_num );
        //printk ("used=%d magic=%d \n", 
        //    ide_ports[i].used, 
        //    ide_ports[i].magic );
        printf ("type=%d      \n", ide_ports[i].type );
        printf ("base_port=%x \n", ide_ports[i].base_port );
        printf ("name=%s      \n", ide_ports[i].name );
    };

    //
    // # debug.
    //

	// primary secondary  ... master slave
	// printf ( " channel=%d dev=%d \n", ata.channel, ata.dev_num );


	/*
	// Estrutura 'ata'
	// Qual lista ??
	
	//pegar a estrutura de uma lista.
	
	//if( ata != NULL )
	//{
		printf("ata:\n");
 	    printf("type={%d}\n", (int) ata.chip_control_type);
	    printf("channel={%d}\n", (int) ata.channel);
	    printf("devType={%d}\n", (int) ata.dev_type);
	    printf("devNum={%d}\n", (int) ata.dev_num);
	    printf("accessType={%d}\n", (int) ata.access_type);
	    printf("cmdReadMode={%d}\n", (int) ata.cmd_read_modo);
	    printf("cmdBlockBaseAddress={%d}\n", (int) ata.cmd_block_base_address);
	    printf("controlBlockBaseAddress={%d}\n", (int) ata.ctrl_block_base_address);
		printf("busMasterBaseAddress={%d}\n", (int) ata.bus_master_base_address);
		printf("ahciBaseAddress={%d}\n", (int) ata.ahci_base_address);
	//};
	*/


	// Estrutura 'atapi'
	// Qual lista ??

	// Estrutura 'st_dev'
	// Estão na lista 'ready_queue_dev'	

    //refresh_screen ();
}





























