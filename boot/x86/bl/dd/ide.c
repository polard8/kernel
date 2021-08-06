/*
 * File: ide.c
 *
 * IDE/AHCI support.
 *
 * History:
 *     2018 - Created by Nelson Cole. 
 *          ~ Adapted by Fred Nora.
 */


// #todo:
// Rever a tipagem.
// Usar os nomes tradicionais para os tipos.

// Obs: 
// O foco está na lista de discos. 
// diskList


#include <bootloader.h>



#define PCI_PORT_ADDR  0xCF8
#define PCI_PORT_DATA  0xCFC


extern st_dev_t *current_dev;

// IRQ support.
//static _u32 ata_irq_invoked = 1; 
static _u32 ata_irq_invoked = 0;



int disk_get_ata_irq_invoked()
{
    return (int) ata_irq_invoked;
}


void disk_reset_ata_irq_invoked ()
{
    ata_irq_invoked = 0;
}


void ata_wait (_i32 val)
{
    val /= 100;

    if (val<0){
        val=1;
    }

    while (val--)
    {
        io_delay();
    };
}


// #TODO: 
// Nelson, ao configurar os bits BUSY e DRQ. 
// Devemos verificar retornos de erros.

_u8 ata_wait_not_busy ()
{
    while ( ata_status_read() & ATA_SR_BSY ){
        if ( ata_status_read() & ATA_SR_ERR ){
            return 1;
        }
    };

    return 0;
}


_u8 ata_wait_busy (){

    while ( !(ata_status_read() & ATA_SR_BSY ) ){
        if ( ata_status_read() & ATA_SR_ERR ){
            return 1;
        }
    };

    return 0;
}


_u8 ata_wait_no_drq()
{
    while ( ata_status_read() & ATA_SR_DRQ ){
        if (ata_status_read() & ATA_SR_ERR){
            return 1;
        }
    }

    return 0;
}


_u8 ata_wait_drq()
{
    while ( !(ata_status_read() & ATA_SR_DRQ) ){
        if (ata_status_read() & ATA_SR_ERR){
            return 1;
        }
    };

    return 0;
}


_u8 ata_wait_irq (){

   _u8 Data=0;

   _u32 tmp = 0x10000;

    while (!ata_irq_invoked)
    {
        Data = ata_status_read();
        
        if ( (Data & ATA_SR_ERR) )
        {
            ata_irq_invoked = 0;
            return -1;
        }

        // ns
        
        if (--tmp){ 
            ata_wait (100); 
        }else{
            ata_irq_invoked = 0;
            return 0x80;
        };
    };
 
    ata_irq_invoked = 0;

    return 0;
}


// Soft reset.
void ata_soft_reset()
{
    _u8 Data = 0;


    Data = in8 (ata.ctrl_block_base_address + 2);

    out8( 
        ata.ctrl_block_base_address, 
        Data | 0x4 );
    
    out8( 
        ata.ctrl_block_base_address, 
        Data & 0xfb ); 
}


//#bugbug
//Lê o status de um disco determinado, se os valores  
//na estrutura estiverem certos.

_u8 ata_status_read()
{
    _u8 Value=0;
    
    Value = in8 ( ata.cmd_block_base_address + ATA_REG_STATUS );
    
    return Value;
}

void ata_cmd_write (_i32 cmd_val)
{
	// no_busy 

    ata_wait_not_busy ();
    out8 ( ata.cmd_block_base_address + ATA_REG_CMD, cmd_val );


	// Esperamos 400ns
    ata_wait (400);  
}



_u8 ata_assert_dever (_i8 nport){

    switch (nport){

    case 0:
        ata.channel = 0;
        ata.dev_num = 0;
        break;

    case 1:   
        ata.channel = 0;
        ata.dev_num = 1;
        break;

    case 2:
        ata.channel = 1;
        ata.dev_num = 0;
        break;

    case 3:
        ata.channel = 1;
        ata.dev_num = 1;
        break;

    // Fail.
    default:
        printf ("bl-ata_assert_dever: [FAIL] Port %d, value not used\n", 
            nport );
        return -1;
        break;
    };

    set_ata_addr (ata.channel);

    return 0;
}


/*
 *************************************
 * ide_identify_device:
 */

int ide_identify_device ( uint8_t nport ){

    _u8 status=0;

    _u8 lba1=0; 
    _u8 lba2=0;


    ata_assert_dever (nport);

	// Ponto flutuante
	// Sem unidade conectada ao barramento

 
    if ( ata_status_read() == 0xff )
    {
        return (int) -1;
    }


    out8 ( ata.cmd_block_base_address + ATA_REG_SECCOUNT, 0 );  // Sector Count 7:0
    out8 ( ata.cmd_block_base_address + ATA_REG_LBA0, 0 );      // LBA 7-0
    out8 ( ata.cmd_block_base_address + ATA_REG_LBA1, 0 );      // LBA 15-8
    out8 ( ata.cmd_block_base_address + ATA_REG_LBA2, 0 );      // LBA 23-16


    // Select device.
    out8 ( 
        ata.cmd_block_base_address + ATA_REG_DEVSEL, 
        0xE0 | ata.dev_num << 4 );
    ata_wait(400);

    // cmd
    ata_cmd_write (ATA_CMD_IDENTIFY_DEVICE); 
    
    // ata_wait_irq();
    // Nunca espere por um IRQ aqui
    // Devido unidades ATAPI, ao menos que pesquisamos pelo Bit ERROR
    // Melhor seria fazermos polling

    ata_wait (400);


	//Sem unidade no canal

    if ( ata_status_read() == 0 )
    {  
        return (int) -1;
    }


    lba1 = in8 ( ata.cmd_block_base_address + ATA_REG_LBA1 );
    lba2 = in8 ( ata.cmd_block_base_address + ATA_REG_LBA2 );

    //
    //    ## type ## 
    //


    //PATA
    if ( lba1 == 0 && lba2 == 0 )
    {
        // kputs("Unidade PATA\n");
        // aqui esperamos pelo DRQ
        // e eviamos 256 word de dados PIO

        ata_wait_drq();
        ata_pio_read ( ata_identify_dev_buf, 512 );

        ata_wait_not_busy();
        ata_wait_no_drq();

        // Salvando o tipo em estrutura de porta.
        ide_ports[nport].id    = (uint8_t) nport;
        ide_ports[nport].used  = (int) TRUE;
        ide_ports[nport].magic = (int) 1234;
        ide_ports[nport].name  = "PATA";
        ide_ports[nport].type  = (int) idedevicetypesPATA;

        return 0;


	//SATA
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

        //salvando o tipo em estrutura de porta.
        ide_ports[nport].id    = (uint8_t) nport;
        ide_ports[nport].used  = (int) TRUE;
        ide_ports[nport].magic = (int) 1234;
        ide_ports[nport].name  = "SATA";
        ide_ports[nport].type  = (int) idedevicetypesSATA;

        return 0;

    //PATAPI
    }
    else if ( lba1 == 0x14 && lba2 == 0xEB )
    {
        //kputs("Unidade PATAPI\n");   
        ata_cmd_write(ATA_CMD_IDENTIFY_PACKET_DEVICE);
        ata_wait(400);
        ata_wait_drq(); 
        ata_pio_read ( ata_identify_dev_buf, 512 );
        ata_wait_not_busy();
        ata_wait_no_drq();

        // Salvando o tipo em estrutura de porta.
        ide_ports[nport].id    = (uint8_t) nport;
        ide_ports[nport].used  = (int) TRUE;
        ide_ports[nport].magic = (int) 1234;
        ide_ports[nport].name  = "PATAPI";
        ide_ports[nport].type  = (int) idedevicetypesPATAPI;

        return (int) 0x80;

    //SATAPI
    }
    else if (lba1 == 0x69  && lba2 == 0x96){

        //kputs("Unidade SATAPI\n");   
        ata_cmd_write(ATA_CMD_IDENTIFY_PACKET_DEVICE);
        ata_wait(400);
        ata_wait_drq(); 
        ata_pio_read(ata_identify_dev_buf,512);
        ata_wait_not_busy();
        ata_wait_no_drq();

        //salvando o tipo em estrutura de porta.
        ide_ports[nport].id    = (uint8_t) nport;
        ide_ports[nport].used  = (int) TRUE;
        ide_ports[nport].magic = (int) 1234;
        ide_ports[nport].name  = "SATAPI";
        ide_ports[nport].type  = (int) idedevicetypesSATAPI;

        return (int) 0x80;
    };

    // Fail?

    return 0;
}



#define DISK1  1
#define DISK2  2
#define DISK3  3
#define DISK4  4

static const char *ata_sub_class_code_register_strings[] = {
    "Unknown",
    "IDE Controller",
    "Unknown",
    "Unknown",
    "RAID Controller",
    "Unknown",
    "AHCI Controller"
};


extern st_dev_t *current_dev;


// base address 
static _u32 ATA_BAR0;    // Primary Command Block Base Address
static _u32 ATA_BAR1;    // Primary Control Block Base Address
static _u32 ATA_BAR2;    // Secondary Command Block Base Address
static _u32 ATA_BAR3;    // Secondary Control Block Base Address
static _u32 ATA_BAR4;    // Legacy Bus Master Base Address
static _u32 ATA_BAR5;    // AHCI Base Address / SATA Index Data Pair Base Address


// Set address.
// Primary or secondary.

void set_ata_addr (int channel){

    if (channel<0){
        printf ("set_ata_addr: [FAIL] channel\n");
        return;
    }


    // #bugbug
    // Porque estamos checando se é primário ou
    // secundario?

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


/* 
 * #Obs: 
 * O que segue são rotinas de suporte ao controlador IDE.
 */


const char *dev_type[] = {
    "ATA",
    "ATAPI"
};

st_dev_t *current_dev;       // A unidade atualmente selecionada.
st_dev_t *ready_queue_dev;   // O início da lista.
uint32_t  dev_next_pid = 0;  // O próximo ID de unidade disponível. 


/*
 ********************************************************
 * ide_mass_storage_initialize:
 *     Rotina de inicialização de dispositivo de armazenamento de dados.
 */

void ide_mass_storage_initialize ()
{

    int port=0;

    //
    // Vamos trabalhar na lista de dispositivos.
    //


	// Iniciando a lista.
	ready_queue_dev = ( struct st_dev * ) malloc ( sizeof( struct st_dev) );

    // #bugbug
    // Check validation!

    current_dev = ( struct st_dev * ) ready_queue_dev;
    current_dev->dev_id      = dev_next_pid++;
    current_dev->dev_type    = -1;
    current_dev->dev_num     = -1;
    current_dev->dev_channel = -1;
    current_dev->dev_nport   = -1;
    current_dev->next = NULL;

    // Buffer to get information 
    // about a single device, i guess.

    ata_identify_dev_buf = ( _u16 * ) malloc(4096);

    // Invalid buffer
    if ( (void*) ata_identify_dev_buf == NULL )
    {
        printf("ide_mass_storage_initialize: [FAIL] invalid buffer\n");
        
        // #todo
        // hang here
    }


    // Initializing the IDE ports.

    for ( port=0; port < 4; port++ )
    {
        ide_dev_init(port);
    };
}


/*
 ****************************************************
 * ide_dev_init:
 *    Obtendo informações sobre um dos dispositivos.
 */

int ide_dev_init (char port){

    int data=0;

    st_dev_t *new_dev;


    // Storage device structure.
    
    new_dev = ( struct st_dev * ) malloc ( sizeof( struct st_dev) );
    
    if ( (void *) new_dev ==  NULL )
    {
        printf ("ide_dev_init: [FAIL] struct\n");
        die();
    }


    data = (int) ide_identify_device (port);

    if ( data == -1 )
    {
        printf ("ide_dev_init: [FAIL] ide_identify_device fail\n");
        return (int) 1;
    }


    if ( data == 0 )
    {
        // Unidades ATA.

        new_dev->dev_type   = (ata_identify_dev_buf[0] &0x8000)? 0xffff: ATA_DEVICE_TYPE;
        new_dev->dev_access = (ata_identify_dev_buf[83]&0x0400)? ATA_LBA48: ATA_LBA28;
        
		if(ATAFlag == FORCEPIO)
		{
			//com esse só funciona em pio
		    new_dev->dev_modo_transfere = 0;	
		}else{
		    //com esse pode funcionar em dma
		    new_dev->dev_modo_transfere = (ata_identify_dev_buf[49]&0x0100)? ATA_DMA_MODO: ATA_PIO_MODO;
        };
		
		new_dev->dev_total_num_sector   = ata_identify_dev_buf[60];
        new_dev->dev_total_num_sector  += ata_identify_dev_buf[61];
		
        new_dev->dev_byte_per_sector = 512;
		
        new_dev->dev_total_num_sector_lba48  = ata_identify_dev_buf[100];
        new_dev->dev_total_num_sector_lba48 += ata_identify_dev_buf[101];
        new_dev->dev_total_num_sector_lba48 += ata_identify_dev_buf[102];
        new_dev->dev_total_num_sector_lba48 += ata_identify_dev_buf[103];
		
        new_dev->dev_size = (new_dev->dev_total_num_sector_lba48 * 512);

        
    }else if( data == 0x80 )
          {

              // Unidades ATAPI.

              new_dev->dev_type = (ata_identify_dev_buf[0]&0x8000)? ATAPI_DEVICE_TYPE: 0xffff;
              
			  new_dev->dev_access = ATA_LBA28;
              
			  if(ATAFlag == FORCEPIO)
			  {
                  //com esse só funciona em pio 				  
			      new_dev->dev_modo_transfere = 0; 
			  }else{
			      //com esse pode funcionar em dma
			      new_dev->dev_modo_transfere = (ata_identify_dev_buf[49]&0x0100)? ATA_DMA_MODO: ATA_PIO_MODO;
              };

			  new_dev->dev_total_num_sector  = 0;
              new_dev->dev_total_num_sector += 0;
              
			  new_dev->dev_byte_per_sector = 2048; 
              
			  new_dev->dev_total_num_sector_lba48  = 0;
              new_dev->dev_total_num_sector_lba48 += 0;
              new_dev->dev_total_num_sector_lba48 += 0;
              new_dev->dev_total_num_sector_lba48 += 0;
              
			  new_dev->dev_size = (new_dev->dev_total_num_sector_lba48 * 2048);

          }else{
              printf ("ide_dev_init: [FAIL] Invalid device?\n");
              return (int) 1;
          };

    //Dados em comum.

    new_dev->dev_id      = dev_next_pid++;
    new_dev->dev_num     = ata.dev_num;
    new_dev->dev_channel = ata.channel;
    new_dev->dev_nport   = port;


	//
	// port
	//

    switch ( port ){

        case 0:  
            // Message
            dev_nport.dev0 = 0x81;
            break;

        case 1:
            // Message
            dev_nport.dev1 = 0x82;
            break;

        case 2:
            // Message
            dev_nport.dev2 = 0x83;
            break;

        case 3:
            // Message
            dev_nport.dev3 = 0x84;
            break;

        default: 
            // Message
            printf ("ide_dev_init: [FAIL] Invalid port?\n");
            break; 
    };


#ifdef KERNEL_VERBOSE
    printf ("[ Detected Disk type: %s ]\n", 
        dev_type[new_dev->dev_type] );
    refresh_screen ();
#endif

    new_dev->next = NULL;


    //
    // Queue
    //

    // Add no fim da lista (ready_queue_dev).

    st_dev_t *tmp_dev; 

    tmp_dev = ( struct st_dev * ) ready_queue_dev;

    if ( (void*) tmp_dev == NULL ){
        printf ("ide_dev_init: [FAIL] tmp_dev\n");
        die();
    }

    while ( tmp_dev->next )
    {
        tmp_dev = tmp_dev->next;
    };
    
    tmp_dev->next = new_dev;


    return 0;
}


/*
 * dev_switch:
 *     ?? Porque esse tipo ??
 */

static inline void dev_switch (void){

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



/*
 * getpid_dev:
 *     ?? Deve ser algum suporte a Processos.
 */

static inline int getpid_dev ()
{

    if ( (void*) current_dev == NULL ){
        printf("getpid_dev: [FAIL] Invalid pointer\n");
        return -1;
    }

    return current_dev->dev_id;
}


/*
 * getnport_dev:
 */

static inline int getnport_dev (){

    if ( (void*) current_dev == NULL ){
        printf("getnport_dev: [FAIL] Invalid pointer\n");
        return -1;
    }

    return current_dev->dev_nport;
}


/*
 * nport_ajuste:
 */

// #todo
// Change this name.

int nport_ajuste ( char nport ){

    _i8 i=0;

    // #todo: Simplify.

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

// ===============================================
// Obs: 
// O que segue são rotinas de suporte a ATA.


// #bugbug
// #portability
// This is avery gcc specific thing.

void ata_pio_read ( void *buffer, _i32 bytes )
{
    asm volatile (\
        "cld;\
        rep; insw"::"D"(buffer),\
        "d"(ata.cmd_block_base_address + ATA_REG_DATA),\
        "c"(bytes/2) );
}


// #bugbug
// #portability
// This is avery gcc specific thing.

void ata_pio_write ( void *buffer, _i32 bytes )
{
    asm volatile (\
        "cld;\
        rep; outsw"::"S"(buffer),\
        "d"(ata.cmd_block_base_address + ATA_REG_DATA),\
        "c"(bytes/2) );
}

extern st_dev_t *current_dev;
extern uint8_t *dma_addr;


// #bugbug
// #portability
// This is avery gcc specific thing.

// atapi_pio_read:
static inline void atapi_pio_read ( void *buffer, uint32_t bytes )
{
    asm volatile (\
        "cld;\
        rep; insw"::"D"(buffer),\
        "d"(ata.cmd_block_base_address + ATA_REG_DATA),\
        "c"(bytes/2) );
}

extern st_dev_t *current_dev;
_u8 *dma_addr;



// ata_set_device_and_sector:
static inline _void ata_set_device_and_sector ( 
    _u32 count, 
    _u64 addr,
    _i32 access_type, 
    _i8 nport )
{

    ata_assert_dever(nport);

	//
	// Access type.
	//

    switch ( access_type ){

        // Mode LBA28
        case 28:
	        out8 ( ata.cmd_block_base_address + ATA_REG_SECCOUNT, count );   // Sector Count 7:0
	        out8 ( ata.cmd_block_base_address + ATA_REG_LBA0, addr );		 // LBA 7-0   
	        out8 ( ata.cmd_block_base_address + ATA_REG_LBA1, addr >> 8 );   // LBA 15-8
	        out8 ( ata.cmd_block_base_address + ATA_REG_LBA2, addr >> 16 );  // LBA 23-16
            
			// Modo LBA active, Select device, and LBA 27-24
            out8 ( ata.cmd_block_base_address + ATA_REG_DEVSEL, 
			    0x40 | (ata.dev_num << 4) | (addr >> 24 &0x0f) );
     
			// Verifique se e a mesma unidade para não esperar pelos 400ns.
			
            if ( ata_record_dev != ata.dev_num && 
			     ata_record_channel != ata.channel )
			{
                ata_wait(400);
                
				//verifique erro
                ata_record_dev = ata.dev_num;
                ata_record_channel  = ata.channel;
			};
            break;

		//Mode LBA48
        case 48:
            
            out8( ata.cmd_block_base_address + ATA_REG_SECCOUNT,0);	      // Sector Count 15:8
	        out8( ata.cmd_block_base_address + ATA_REG_LBA0,addr >> 24);  // LBA 31-24   
	        out8( ata.cmd_block_base_address + ATA_REG_LBA1,addr >> 32);  // LBA 39-32
	        out8( ata.cmd_block_base_address + ATA_REG_LBA2,addr >> 40);  // LBA 47-40
	        out8( ata.cmd_block_base_address + ATA_REG_SECCOUNT,count);   // Sector Count 7:0
	        out8( ata.cmd_block_base_address + ATA_REG_LBA0,addr);		  // LBA 7-0   
	        out8( ata.cmd_block_base_address + ATA_REG_LBA1,addr >> 8);   // LBA 15-8
	        out8( ata.cmd_block_base_address + ATA_REG_LBA2,addr >> 16);  // LBA 23-16
            
			out8 ( ata.cmd_block_base_address + ATA_REG_DEVSEL,
			    0x40 | ata.dev_num << 4 );   // Modo LBA active, Select device,        
            
			// Verifique se e a mesma unidade para não esperar pelos 400ns.
            if ( ata_record_dev     != ata.dev_num && 
                 ata_record_channel != ata.channel )
            {
                ata_wait(400);
                ata_record_dev     = ata.dev_num;
                ata_record_channel = ata.channel;
            }
            break;

        // Modo CHS
        // not supported
        case 0:
            break;

        // Default ??
    };
}



/*
 * Credits:
 * Copyright (C) 2017-2018 (Nelson Sapalo da Silva Cole)

 * Obs: 

 */

// ==========================
// O que segue é um suporte ao controlador de DMA para uso nas rotinas de IDE.

//
// DMA support
//


// ============
// Legacy Bus Master Base Address
// #todo Nelson, Não se esqueça de habiliatar o // Bus Master Enable
// no espaço de configuraçao PCI (offset 0x4 Command Register)

// Commands dma 
#define dma_bus_start   1
#define dma_bus_stop    0
#define dma_bus_read    0
#define dma_bus_write   1


// Status dma
#define ide_dma_sr_err     0x02


// Registros bus master base address
#define ide_dma_reg_cmd     0x00
#define ide_dma_reg_status  0x02
#define ide_dma_reg_addr    0x04

// channel
#define ide_dma_primary     0x00
#define ide_dma_secundary   0x01


/* 
 * ide_dma_prdt: 
 */

struct {

    uint32_t addr;
    uint32_t len;

}ide_dma_prdt[4];


/* 
 * ide_dma_data: 
 * 
 */

void 
ide_dma_data ( 
    void *addr, 
    uint16_t byte_count,
    uint8_t flg,
    uint8_t nport )
{

    _u8 data=0;
    uint32_t phy=0;


	// @todo: 
	// Check limits.


    ide_dma_prdt[nport].addr = (_u32) addr;  //@todo: (&~1)sera que e necessario?
    ide_dma_prdt[nport].len  = byte_count | 0x80000000;

    phy = (uint32_t) &ide_dma_prdt[nport];

    // prds physical.
    out32 ( ata.bus_master_base_address + ide_dma_reg_addr, phy );
 
    // (bit 3 read/write)
    // 0 = Memory reads.
    // 1 = Memory writes.
	
    data = in8 ( ata.bus_master_base_address + ide_dma_reg_cmd ) &~8;

	//
	// TODO bit 8 Confilito no Oracle VirtualBox
	// Obs: Isso foi enviado via argumento e agora foi alerado.
	//
	
    flg = 1; 

    out8 ( 
        ata.bus_master_base_address + ide_dma_reg_cmd, 
        data | flg << 3 );

    // Limpar o bit de interrupção e 
	// o bit de erro no registo de status.
	
    data = in8 ( ata.bus_master_base_address + ide_dma_reg_status );
    
    out8 ( 
        ata.bus_master_base_address + ide_dma_reg_status, 
        data & ~6 );

// #todo: 
//   Deletar retorno.

done:
    return;
}



/*
 * ide_dma_start:
 */

void ide_dma_start ()
{
    _u8 Data = 0; 
    
    Data = in8 ( ata.bus_master_base_address + ide_dma_reg_cmd );

    out8 ( 
        ata.bus_master_base_address + ide_dma_reg_cmd, 
        Data | 1);
}



/*
 * ide_dma_stop:
 */

void ide_dma_stop ()
{
    _u8 Data = 0;
    
    Data = in8 ( ata.bus_master_base_address + ide_dma_reg_cmd );  
    out8( 
        ata.bus_master_base_address + ide_dma_reg_cmd, 
        Data & ~1);

    Data = in8 ( ata.bus_master_base_address + ide_dma_reg_status );
    out8( 
        ata.bus_master_base_address + ide_dma_reg_status, 
        Data & ~6);

// #todo: 
// Deletar retorno.

done:
    return;
}


/*
 * ide_dma_read_status:
 *     DMA read status.
 */

int ide_dma_read_status ()
{
    int Status=0;
    
    Status = in8 ( ata.bus_master_base_address + ide_dma_reg_status );
    
    return Status;
}



//
// pci support
//

// #bugbug
// No macros, please

#define CONFIG_ADDR(bus,device,fn,offset)\
                       (\
                       (((uint32_t)(bus)    & 0xff) << 16)|\
                       (((uint32_t)(device) & 0x3f) << 11)|\
                       (((uint32_t)(fn)     & 0x07) <<  8)|\
                       ( (uint32_t)(offset) & 0xfc)|0x80000000 )

// #todo:
// Checar se temos uma lista dessa no suporte a PCI.

// #bugbug
// That 'Unknown' thing in the bottom of the list.

const char *pci_classes[] = {
    "Unknown [old]",
    "Mass storage",
    "Network",
    "Display",
    "Multimedia device",
    "Memory",
    "Bridge device",
    "Simple Communication",
    "Base System Peripheral",
    "Input Device",
    "Docking Station",
    "Processor",
    "Serial Bus",
    "Wireless",
    "Inteligent I/O",
    "Satellite Communications",
    "Encrypt/Decrypt",
    "Data acquisition and signal processing",
    [255]="Unknown"
};


/*
 * read_pci_config_addr:
 *     READ
 */

uint32_t 
diskReadPCIConfigAddr ( 
    int bus, 
    int dev,
    int fun, 
    int offset )
{

    // #bugbug
    // Do not use macros.
    // Expand this macro outside the function.
 
    out32 ( 
        PCI_PORT_ADDR, 
        CONFIG_ADDR( bus, dev, fun, offset ) );

    return (uint32_t) in32 (PCI_PORT_DATA);
}


/*
 * write_pci_config_addr:
 *     WRITE
 */

void 
diskWritePCIConfigAddr ( 
    int bus, 
    int dev,
    int fun, 
    int offset, 
    int data )
{
    // #bugbug
    // Do not use macros.
    // Expand this macro outside the function.

    out32 ( 
        PCI_PORT_ADDR, 
        CONFIG_ADDR( bus, dev, fun, offset ) );

    out32 ( PCI_PORT_DATA, data );
}



/*
 ***********************************************
 * diskATAPCIConfigurationSpace:
 * 
 *     Espaço de configuraçao PCI Mass Storage
 *     Aqui vamos analisar o tipo de dispositivo.
 */

int 
diskATAPCIConfigurationSpace ( 
    char bus, 
    char dev, 
    char fun )
{

    uint32_t data=0;


//#ifdef KERNEL_VERBOSE	
	printf ("diskATAPCIConfigurationSpace:\n");
    printf ("Initializing PCI Mass Storage support..\n");
//#endif

    // Indentification Device
    data = (uint32_t) diskReadPCIConfigAddr ( bus, dev, fun, 0 );
	
	// Salvando configurações.
    ata_pci.vendor_id = data       & 0xffff;
    ata_pci.device_id = data >> 16 & 0xffff;


//#ifdef KERNEL_VERBOSE	
    printf ("\nDisk info:\n");
    printf ("[ Vendor ID: %X,Device ID: %X ]\n", ata_pci.vendor_id, 
        ata_pci.device_id );
//#endif



	// Obtendo informações.
	// Classe code, programming interface, revision id.
	
    data  = (uint32_t) diskReadPCIConfigAddr ( bus, dev, fun, 8 );
    
	// Salvando informações.


    // Classe, sub-classe, prog if and revision.

    ata_pci.classe      = data >> 24 & 0xff;
    ata_pci.subclasse   = data >> 16 & 0xff;
    ata_pci.prog_if     = data >>  8 & 0xff;
    ata_pci.revision_id = data       & 0xff;


	// #importante:
	// Aqui detectamos o tipo de dispositivo com base 
	// nas informações de classe e subclasse.


	//
	//  ## IDE ##
	//

    if ( ata_pci.classe == 1 && ata_pci.subclasse == 1 )
    {
        // IDE
		//#debug
        //printf (">>> IDE \n");
        //refresh_screen();		
        //while(1){}
		//refresh_screen();
		//refresh_screen();

		ata.chip_control_type = ATA_IDE_CONTROLLER; 
		
        // Compatibilidade e nativo, primary.
        data  = diskReadPCIConfigAddr( bus, dev, fun, 8 );
        if ( data & 0x200 )
        { 
            diskWritePCIConfigAddr ( 
                bus, 
                dev, 
                fun, 
                8, 
                data | 0x100 ); 
        }

        // Compatibilidade e nativo, secundary.
        data = diskReadPCIConfigAddr( bus, dev, fun, 8 );
        if ( data & 0x800 )
        { 
            diskWritePCIConfigAddr ( 
                bus, 
                dev, 
                fun, 
                8, 
                data | 0x400 ); 
        }

        data = diskReadPCIConfigAddr( bus, dev, fun, 8 );
        if ( data & 0x8000 )
        {
            // Bus Master Enable
            data = diskReadPCIConfigAddr(bus,dev,fun,4);
            diskWritePCIConfigAddr(bus,dev,fun,4,data | 0x4);
        } 


	    // Habilitar interrupcao (INTx#)
        data = diskReadPCIConfigAddr( bus, dev, fun, 4 );
        diskWritePCIConfigAddr( bus, dev, fun, 4, data & ~0x400);

       	// IDE Decode Enable
       	data = diskReadPCIConfigAddr( bus, dev, fun, 0x40 );
       	diskWritePCIConfigAddr( bus, dev, fun, 0x40, data | 0x80008000 );

        // Synchronous DMA Control Register
	    // Enable UDMA
	    data = diskReadPCIConfigAddr( bus, dev, fun, 0x48 );
	    diskWritePCIConfigAddr( bus, dev, fun, 0x48, data | 0xf);

//#ifdef KERNEL_VERBOSE 		
        printf("[ Sub Class Code %s Programming Interface %d Revision ID %d ]\n",\
            ata_sub_class_code_register_strings[ata.chip_control_type],
	        ata_pci.prog_if,
			ata_pci.revision_id );
//#endif

    //
    //  ## RAID ##
    //
  
    }else if ( ata_pci.classe == 1 && ata_pci.subclasse == 4 )
          {
              //RAID
		      //printf (">>> RAID \n");
		      //#debug
		      //refresh_screen();
		      //while(1){}
		      //refresh_screen();
		      //refresh_screen();
		
              ata.chip_control_type = ATA_RAID_CONTROLLER;
			  
//#ifdef KERNEL_VERBOSE              
			  printf("[ Sub Class Code %s Programming Interface %d Revision ID %d ]\n",\
                  ata_sub_class_code_register_strings[ata.chip_control_type], 
				  ata_pci.prog_if,
				  ata_pci.revision_id );
//#endif
    
			  // Em avaliacao
              return PCI_MSG_AVALIABLE;
			  
			  
			  
	            //
                //  ## ACHI ##  SATA
                //

          }else if ( ata_pci.classe == 1 && ata_pci.subclasse == 6 )
                {
					// ACHI
		            //#debug
		            //printf (">>> SATA \n");
		            //while(1){}
		            //refresh_screen();
		            //refresh_screen();
		            //refresh_screen();
					
			        ata.chip_control_type = ATA_AHCI_CONTROLLER;
       
                    // Compatibilidade e nativo, primary.
                    data = diskReadPCIConfigAddr ( bus, dev, fun, 8 );
                    if ( data & 0x200 )
                    { 
                        diskWritePCIConfigAddr ( 
                            bus, 
                            dev, 
                            fun, 
                            8, 
                            data | 0x100 ); 
                    }        

                    // Compatibilidade e nativo, secundary.
                    data = diskReadPCIConfigAddr ( bus, dev, fun, 8 );
                    if ( data & 0x800 )
                    { 
                        diskWritePCIConfigAddr ( 
                            bus, 
                            dev, 
                            fun, 
                            8, 
                            data | 0x400 ); 
                    }

		            // ??
                    data = diskReadPCIConfigAddr ( bus, dev, fun, 8 );
                    if ( data & 0x8000 ) 
                    {    
                        // Bus Master Enable.
                        data = diskReadPCIConfigAddr ( bus, dev, fun, 4 );
                        diskWritePCIConfigAddr ( bus, dev, fun, 4, data | 0x4 );
                    } 

                    // IDE Decode Enable
                    data = diskReadPCIConfigAddr ( bus, dev, fun, 0x40 );
                    diskWritePCIConfigAddr ( bus, dev, fun, 0x40, data | 0x80008000 );

                    // Habilitar interrupcao (INTx#)
                    data = diskReadPCIConfigAddr ( bus, dev, fun, 4 );
                    diskWritePCIConfigAddr ( bus, dev, fun, 4, data & ~0x400);

//#ifdef KERNEL_VERBOSE
                    printf("[ Sub Class Code %s Programming Interface %d Revision ID %d ]\n",\
                        ata_sub_class_code_register_strings[ata.chip_control_type], 
                        ata_pci.prog_if,
                        ata_pci.revision_id );
//#endif

                // Ok

                } else {
                    // Panic
                    printf ("diskATAPCIConfigurationSpace: [FAIL] DRIVER BLOCK!");
                    die();
                };

	// #obs:
	// Nesse momento já sabemos se é IDE, RAID, AHCI.
	// Vamos pegar mais informações,
	// Salvaremos as informações na estrutura.


	// PCI cacheline, Latancy, Headr type, end BIST

    data = diskReadPCIConfigAddr ( bus, dev, fun, 0xC );

    ata_pci.primary_master_latency_timer = data >>  8 & 0xff;
    ata_pci.header_type                  = data >> 16 & 0xff;
    ata_pci.BIST                         = data >> 24 & 0xff;

    // BARs

    ata_pci.bar0 = diskReadPCIConfigAddr( bus, dev, fun, 0x10 );
    ata_pci.bar1 = diskReadPCIConfigAddr( bus, dev, fun, 0x14 );
    ata_pci.bar2 = diskReadPCIConfigAddr( bus, dev, fun, 0x18 );
    ata_pci.bar3 = diskReadPCIConfigAddr( bus, dev, fun, 0x1C );
    ata_pci.bar4 = diskReadPCIConfigAddr( bus, dev, fun, 0x20 );
    ata_pci.bar5 = diskReadPCIConfigAddr( bus, dev, fun, 0x24 );


    // ========================
    // Interrupt

    data = diskReadPCIConfigAddr( bus, dev, fun, 0x3C );

    ata_pci.interrupt_line = data      & 0xff;
    ata_pci.interrupt_pin  = data >> 8 & 0xff;

    // ========================
    // PCI command and status

    data = diskReadPCIConfigAddr( bus, dev, fun, 4 );

    ata_pci.command = data       & 0xffff; 
    ata_pci.status  = data >> 16 & 0xffff;

    // ------------------------

// #debug
#ifdef KERNEL_VERBOSE

    printf ("[ Command %x Status %x ]\n", 
        ata_pci.command, 
        ata_pci.status );

    printf ("[ Interrupt Line %x Interrupt Pin %x ]\n", 
        ata_pci.interrupt_pin, 
        ata_pci.interrupt_line );

#endif

    // Get Synchronous DMA Control Register.

    data = diskReadPCIConfigAddr (bus,dev,fun,0x48);

#ifdef KERNEL_VERBOSE
    printf ("[ Synchronous DMA Control Register %X ]\n", data );
#endif


done:

#ifdef KERNEL_VERBOSE
    refresh_screen();
#endif 

    return (PCI_MSG_SUCCESSFUL);
}



/*
 ***********************************
 * diskPCIScanDevice:
 *
 * Esta função deve retornar o número de barramento, 
 * o dispositivo e a função do dispositivo conectado ao barramento PCI 
 * de acordo a classe.
 */

uint32_t diskPCIScanDevice ( int class )
{
    uint32_t data = -1;

    int bus=0; 
    int dev=0; 
    int fun=0;



#ifdef KERNEL_VERBOSE
    printf ("diskPCIScanDevice:\n");
    refresh_screen ();
#endif

    // Probe

    for ( bus=0; bus < 256; bus++ )
    {
        for ( dev=0; dev < 32; dev++ )
        {
            for ( fun=0; fun < 8; fun++ )
            {
                out32 ( PCI_PORT_ADDR, CONFIG_ADDR( bus, dev, fun, 0x8) );
                
                data = in32 (PCI_PORT_DATA);
                
                // #todo
                // We need a class variable outside the if statement.
                // ex: ClassValue = data >> 24 & 0xff;
                
                if ( ( data >> 24 & 0xff ) == class )
                {

                    printf( "[ Detected PCI device: %s ]\n", 
                        pci_classes[class] );

                    // Done
                    
                    // #todo
                    // Put this into a variable.
                    
                    // XXXValue = ( fun + (dev*8) + (bus*32) );
                    // return (uint32_t) XXXValue;
                    
                    return (uint32_t) ( fun + (dev*8) + (bus*32) );
                }
            };
        };
    };

    // Fail

    printf ("[ PCI device NOT detected ]\n");

    refresh_screen ();

    return (uint32_t) (-1);
}


/*
 ********************
 * diskATAInitialize:
 *     Inicializa o IDE e mostra informações sobre o disco.
 * Credits: Nelson Cole;
 */

int diskATAInitialize ( int ataflag )
{
    _u8 bus=0;
    _u8 dev=0;
    _u8 fun=0;

    int Status = 1;  //error
    int port=0;

    _u32 data=0;



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

    g_current_ide_channel =  __IDE_PORT;
    g_current_ide_device  =  __IDE_SLAVE;


    //
    // ===============================================================
    //


	//
	// Configurando flags do driver.
	//


	ATAFlag = (int) ataflag;
	
	//
	// Messages
	//
	
#ifdef KERNEL_VERBOSE
    printf ("sm-disk-disk-diskATAInitialize:\n");
    printf ("Initializing IDE/AHCI support ...\n");
	//refresh_screen();
#endif

    // Sondando a interface PCI para encontrarmos um dispositivo
    // que seja de armazenamento de dados.
	
	//PCI_CLASSCODE_MASS
	
    data = (_u32) diskPCIScanDevice(PCI_CLASSE_MASS);
    
	// Error.
	if( data == -1 )
	{

		printf ("diskATAInitialize: pci_scan_device fail. ret={%d} \n", 
		    (_u32) data );

	    // Abortar.
		Status = (int) (PCI_MSG_ERROR);
		goto fail;
	};


    bus = ( data >> 8 & 0xff );
    dev = ( data >> 3 & 31 );
    fun = ( data      & 7 );


	//
	// Vamos saber mais sobre o dispositivo enconrtado. 
	//

    data = (_u32) diskATAPCIConfigurationSpace ( bus, dev, fun );

	// Error.
    if( data == PCI_MSG_ERROR ){
        printf ("diskATAInitialize: Error Driver [%X]\n", data );
        Status = (int) 1;
        goto fail;  

    }else if( data == PCI_MSG_AVALIABLE )
          {
              printf ("diskATAInitialize: RAID Controller Not supported.\n");
              Status = (int) 1;
              goto fail;  
          };

	//
    // Salvando informações.
    //	
	
	// Aqui estamos pegando informações na estrutura ata_pci sobre as BARs 
	// e manipulando essas informações.
	// ?? Não sei o que está fazendo aqui, talvez procurando endereço de porta.

    // Initialize base address
    // AHCI/IDE Compativel com portas IO IDE legado

    ATA_BAR0 = ( ata_pci.bar0 & ~7 )   + ATA_IDE_BAR0 * ( !ata_pci.bar0 ); 
    ATA_BAR1 = ( ata_pci.bar1 & ~3 )   + ATA_IDE_BAR1 * ( !ata_pci.bar1 );       

    ATA_BAR2 = ( ata_pci.bar2 & ~7 )   + ATA_IDE_BAR2 * ( !ata_pci.bar2 );
    ATA_BAR3 = ( ata_pci.bar3 & ~3 )   + ATA_IDE_BAR3 * ( !ata_pci.bar3 );

    ATA_BAR4 = ( ata_pci.bar4 & ~0x7 ) + ATA_IDE_BAR4 * ( !ata_pci.bar4 );
    ATA_BAR5 = ( ata_pci.bar5 & ~0xf ) + ATA_IDE_BAR5 * ( !ata_pci.bar5 );


	//
	// Colocando nas estruturas.
	//

	ide_ports[0].base_port = (unsigned short) ATA_BAR0; //funciona para primary master e primary slave.
	ide_ports[1].base_port = (unsigned short) ATA_BAR1; //não funciona
	ide_ports[2].base_port = (unsigned short) ATA_BAR2; //funciona para secondary master e secondary slave.
	ide_ports[3].base_port = (unsigned short) ATA_BAR3; //não funciona
	//tem ainda a porta do dma na bar4

	
	//
	// De acordo com o tipo.
	//
	


	//
	// Se for IDE.
	//

    // Type  ATA
    if ( ata.chip_control_type == ATA_IDE_CONTROLLER )
    {

        //Soft Reset, defina IRQ
        
        out8 ( ATA_BAR1, 0xff );
        out8 ( ATA_BAR3, 0xff );
        out8 ( ATA_BAR1, 0x00 );
        out8 ( ATA_BAR3, 0x00 );

        ata_record_dev = 0xff;
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
	    ready_queue_dev = ( struct st_dev * ) malloc ( sizeof( struct st_dev) );
		
	    if ( (void *) ready_queue_dev == NULL )
	    {
	        printf ("diskATAInitialize: ready_queue_dev struct fail");
		    die();
	    }

	    //#todo:
	    //Checar a validade da estrutura.
	
        current_dev = ( struct st_dev * ) ready_queue_dev;
    
        current_dev->dev_id = dev_next_pid++;
    
        current_dev->dev_type = -1;
        current_dev->dev_num = -1;
        current_dev->dev_channel = -1;
        current_dev->dev_nport = -1;
        current_dev->next = NULL;

        // ??
        ata_identify_dev_buf = ( _u16 * ) malloc (4096);

	    if ( (void *) ata_identify_dev_buf == NULL )
	    {
	        printf ("diskATAInitialize: ata_identify_dev_buf fail");
		    die();
	    }

	    // Sondando dispositivos
	
        // As primeiras quatro portas do controlador IDE.    
	    for ( port=0; port < 4; port++ ){
            ide_dev_init (port);
	    };


		//
		// Agora se for AHCI.
		//

    }else if( ata.chip_control_type == ATA_AHCI_CONTROLLER )
	      {
			  
		      //
              // Nothing for now !!!
              //

              // Aqui, vamos mapear o BAR5
              // Estou colocando na marca 28MB
    
//#ifdef KERNEL_VERBOSE	
              // printf("ata_initialize: mem_map para ahci\n");
              // refresh_screen();
//#endif
	
	          //mem_map( (uint32_t*)0x01C00000, (uint32_t*) ATA_BAR5, 0x13, 2);

              //kputs("[ AHCI Mass Storage initialize ]\n");
              //ahci_mass_storage_init();

              printf (" # Panic! # \n");
              printf ("diskATAInitialize: AHCI not found \n");
              die();

          // Panic!
          }else{
              printf (" # Panic! # \n");
              printf ("diskATAInitialize: IDE and AHCI not found \n");
              die();
          };

//
// Ok
//

    Status = 0;
    goto done;


//
// fail
//

fail:
    printf ("diskATAInitialize: fail\n");

//
// done
//

done:

    // #debug
    // printf ("diskATAInitialize: done\n");

    return (int) Status;
}



/*
 *******************************************
 * diskATADialog:
 *     Rotina de diálogo com o driver ATA.
 */

int 
diskATADialog ( 
    int msg, 
    unsigned long long1, 
    unsigned long long2 )
{

    int Status = 1;    //Error.



    switch (msg)
    {
		//ATAMSG_INITIALIZE
		//Initialize driver.
		case 1:
		    diskATAInitialize ( (int) long1 );
		    Status = 0;
			goto done;
			break;
			
		//ATAMSG_REGISTER
        //registra o driver. 
		//case 2:
		//    break;
			
		default:
		    goto fail;
			break;
    };

//
// Done:
//

fail:
    printf ("diskATADialog: fail\n");

done:
    return (int) Status;
}


/*
 ***********************************
 * diskATAIRQHandler1
 *     irq 14 handler
 */

void diskATAIRQHandler1 ()
{
    ata_irq_invoked = 1;  
}


/*
 ***********************************
 * diskATAIRQHandler2
 *     irq 15 handler
 */
 
void diskATAIRQHandler2 ()
{
    ata_irq_invoked = 1;   
}



/*
 ******************************************************
 * show_ide_info:
 *     Mostrar as informações obtidas na inicializações do controlador.
 */

void show_ide_info (){

    int i=0;

    printf ("show_ide_info:\n");

    // four ports.
    for ( i=0; i<4; i++ ){
        printf ("\n");
        printf ("id        = %d \n", ide_ports[i].id );
        printf ("used      = %d \n", ide_ports[i].used );
        printf ("magic     = %d \n", ide_ports[i].magic );
        printf ("type      = %d \n", ide_ports[i].type );
        printf ("name      = %s \n", ide_ports[i].name );
        printf ("base_port = %x \n", ide_ports[i].base_port );
    };


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
	

   //...
}


/*
 * disk_ata_wait_irq:
 *     Esperando pela interrupção.
 * OUT:
 *     0    = ok por status da interrupção. 
 *     -1   = ok por status do controlador.
 *     0x80 = ok por tempo esperado.
 */

int disk_ata_wait_irq (){

   _u32 tmp = 0x10000;
   _u8 data=0;


    // #bugbug
    // Em nenhum momento a flag ata_irq_invoked vira TRUE.

    while (!ata_irq_invoked)
    {

        data = ata_status_read();

        // #bugbug: Review this code.
        if ( (data &ATA_SR_ERR) )
        {
            ata_irq_invoked = 0;
            return (int) -1;
        }

		//ns
        if (tmp--)  //??
		{
			ata_wait (100);
        
		}else{
			
            //ok por tempo esperado.
			ata_irq_invoked = 0;
			
			return (int) 0x80;
        };
    };
 
    //ok por status da interrupção.
	ata_irq_invoked = 0;


	// ok 

    return 0;
}


//
// End.
//

