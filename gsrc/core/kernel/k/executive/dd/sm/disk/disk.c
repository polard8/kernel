/*
 * File: sm\disk\disk.c 
 * 
 * Descrição:
 *     Gerenciador de discos. 
 *     Arquivo principal do Disk Manager.
 *     MB - Módulos incluídos no Kernel Base.
 *
 *     O Gerenciador de Discos é um módulo muito importante do Kernel.
 *
 *    Versão 1.0, 2015, 2016.
 */

 
//
// Obs: o foco está na lista de discos. diskList
//

#include <kernel.h>



void *disk_get_disk_handle( int number )
{
	//check limts
	if( number < 0 || number >= DISK_COUNT_MAX ){
		return NULL;
	}
	
	return (void *) diskList[number];
};




void *disk_get_current_disk_info()
{
	return (void *) CurrentDiskInfo; 
};


/*
 * disk_init:
 *     Inicializa o Disk Manager.
 *     Que é um módulo do tipo MB.
 *
 */
//int diskInit() 
int disk_init()
{
	
#ifdef KERNEL_VERBOSE	
    printf("disk_init: Initializing..\n");
#endif	
	
	//
	// Inicializando uma estrutura global de informações sobre o 
	// disco do sistema.
	// ?? Em que arquivo está essa estrutura.
	//

	// disk info
    diskinfo_conductor = (void*) malloc( sizeof(struct diskinfo_d) );
	if( (void*) diskinfo_conductor == NULL )
	{
	    printf("sm-disk-disk_init:");
		die();
	}else{
		
	    diskinfo_conductor->id = 0;
	    
		diskinfo_conductor->used = 1;
	    diskinfo_conductor->magic = 1234;
	    
		diskinfo_conductor->name = "DISK INFO";
		
		//diskinfo_conductor->BytesPerSector = DISK_BYTES_PER_SECTOR;
	    //diskinfo_conductor->SectorsPerCluster = 0;
        //...		
	};
	
	
	// disk.
    disk_conductor = (void*) malloc( sizeof(struct disk_d) );
	if( (void*) disk_conductor == NULL )
	{
	    printf("sm-disk-disk_init:");
		die();
	}else{
		
		//@todo:
		//disk_conductor->objectType = ?;
		//disk_conductor->objectClass = ?;
		
		disk_conductor->diskType = DISK_TYPE_NULL;
		
	    disk_conductor->id = 0;
	    
		disk_conductor->used = 1;
	    disk_conductor->magic = 1234;
	    
		disk_conductor->name = "DISK 0";
		
		disk_conductor->disk_info = (struct diskinfo_d *) diskinfo_conductor;
	};	
		
    //
	//@todo: Nothing more ?!!
	//
	
done:
    printf("Done.\n");
    return (int) 0;
};


/*
 * init_test_disk:
 *     Testando operações com disco.
 *
 *     @todo: Essa rotina pode virar um aplicativo de teste.
 *
 * + Carrega o arquivo KCONFIG.TXT se estiver presente e 
 *   sonda informações de configuração contidas nele, exibindo as
 *   informações.
 * 
 */
void init_test_disk()
{
	/*@todo: Teste desse tipo pode ser feito em user mode.*/
	
 	/*
    int Index = 0;
	//int fileSize = 0;
	void *addr;
	
	//Deve existir uma estrutura de propriedades do arquivo,
	//como tamanho ...

	
	//@todo: testando lock
	//taskswitch_lock();
	
	printf("init_test_disk: Testing..\n");
	
	//
	// Alocando no heap do kernel. (Root dir de 32 setores).
	//
	
	//@todo: Usar constantes ou variáveis para esses valores.
	
	addr = (void *) malloc(512*32); 
	if( (void *) addr ==  NULL)
	{
	    printf("init_test_disk: error\n");
		
		free(addr);     //@todo *** Cuidado (testando free()).
		
		refresh_screen();
		//while(1){}
		return;
	}
	else
	{		
	    printf("init_test_disk: Loading file..\n");
		fsLoadFile("KCONFIG TXT", (unsigned long) addr);
		printf(addr);	   		
	};
	
	
	//
	// buffer. @todo: Usar ioBuffers.
	//
	
	
	unsigned char *buffer = (unsigned char *) addr;			

	
	
	//@todo: Checar esse valor máximo.
	
	Index = 0;
	while(Index < 128)
	{
	    if( buffer[Index] == 'U')
        {
			if( buffer[Index +1] == 'S' &&
                buffer[Index +2] == 'E' &&
                buffer[Index +3] == 'R' &&
                buffer[Index +4] == '='	)
			{
			    printf("UserName={%s}\n", &buffer[Index+5]);	
			};
			
		};			
		
		Index++;
	};
	
	
//checkingMBR:	
	fsCheckMbr();    //Check MBR.
	
	
	
	//read_lba( FAT16_ROOTDIR_ADDRESS + b, FAT16_ROOTDIR_LBA + i);  

	//@todo: Testando unlock
	//taskswitch_unlock();

done:
	printf("Done.\n");
	*/
    return;
};


/*
int init_disk_manager();
int init_disk_manager()
{
	disk_init();
    return (int) 0;
};


*/


//
// ==============================================================================================
// ATA  - TESTANDO O SUPORTE A ATA DO NELSON...
// ==============================================================================================
//


/* *
 * Copyright (C) 2017-2018 (Nelson Sapalo da Silva Cole)
 * Khole OS v0.3
 *
 *
 */
//#include "ata.h"




extern st_dev *current_dev;
static _u32 ata_irq_invoked = 1; 

_void ata_wait(_i32 val)
{ 
   val/=100;
   while(val--)io_delay();
   //while(val--)delay();
}



// TODO: Nelson, ao configurar os bits BUSY e DRQ 
// devemos verificar retornos de erros.
_u8 ata_wait_not_busy()
{
    while(ata_status_read() &ATA_SR_BSY)
    if(ata_status_read() &ATA_SR_ERR)
    return 1;

    return 0;

}

_u8 ata_wait_busy()
{
    while(!(ata_status_read() &ATA_SR_BSY))
    if(ata_status_read() &ATA_SR_ERR)
    return 1;

    return 0;

}


_u8 ata_wait_no_drq()
{
    while(ata_status_read() &ATA_SR_DRQ)
    if(ata_status_read() &ATA_SR_ERR)
    return 1;

    return 0;
}

_u8 ata_wait_drq()
{
    while(!(ata_status_read() &ATA_SR_DRQ))
    if(ata_status_read() &ATA_SR_ERR)
    return 1;

    return 0;
}




_void ata_irq_handler1(_void)
{

    ata_irq_invoked = 1;
   
}

_void ata_irq_handler2(_void)
{

    ata_irq_invoked = 1;
    
}


_u8 ata_wait_irq()
{
   _u32 tmp = 0x10000;
   _u8 data;
   while (!ata_irq_invoked){
    data = ata_status_read();
    if((data &ATA_SR_ERR)){
        ata_irq_invoked = 0;
        return -1;
        }
                         //ns
        if(--tmp)ata_wait(100);
        else{
        ata_irq_invoked = 0;
        return 0x80;
        }
    }
 
    ata_irq_invoked = 0;
    return 0;
}

_void ata_soft_reset()
{
    _u8 data =  inb(ata.ctrl_block_base_address + 2);
    outb(ata.ctrl_block_base_address, data | 0x4);
    outb(ata.ctrl_block_base_address, data &0xfb);    
}


_u8 ata_status_read()
{
   	return inb(ata.cmd_block_base_address + ATA_REG_STATUS);

}

_void ata_cmd_write(_i32 cmd_val)
{
           
    	// no_busy      	
	ata_wait_not_busy();
	outb(ata.cmd_block_base_address + ATA_REG_CMD,cmd_val);
	ata_wait(400);  // Esperamos 400ns

}



_u8 ata_assert_dever(_i8 nport)
{

    switch(nport){
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
    default:
        kprintf("Port %d, volue not used\n",nport);
        return -1;
     break;
    }

    set_ata_addr(ata.channel);


    return 0;

}


int ide_identify_device(uint8_t nport)
{
    _u8 status;
    _u8 lba1,lba2;

    ata_assert_dever(nport);

    // Ponto flutuante
    if(ata_status_read() == 0xff)//Sem unidade conectada ao barramento
        return -1;

    outb(ata.cmd_block_base_address + ATA_REG_SECCOUNT,0);	// Sector Count 7:0
	outb(ata.cmd_block_base_address + ATA_REG_LBA0,0);        // LBA 7-0   
	outb(ata.cmd_block_base_address + ATA_REG_LBA1,0);        // LBA 15-8
	outb(ata.cmd_block_base_address + ATA_REG_LBA2,0);        // LBA 23-16

    
    // Select device,
    outb(ata.cmd_block_base_address + ATA_REG_DEVSEL,0xE0| ata.dev_num << 4);
    ata_wait(400);

    // cmd
    ata_cmd_write(ATA_CMD_IDENTIFY_DEVICE); 
    // ata_wait_irq();
    // Nunca espere por um IRQ aqui
    // Devido unidades ATAPI, ao menos que pesquisamos pelo Bit ERROR
    // Melhor seria fazermos polling
     
    ata_wait(400);


    if(ata_status_read() == 0) //Sem unidade no canal 
        return -1;

   lba1 = inb(ata.cmd_block_base_address + ATA_REG_LBA1);
   lba2 = inb(ata.cmd_block_base_address + ATA_REG_LBA2);

   if(lba1 == 0x14 && lba2 == 0xEB){
        //kputs("Unidade PATAPI\n");   
        ata_cmd_write(ATA_CMD_IDENTIFY_PACKET_DEVICE);
        ata_wait(400);
        ata_wait_drq(); 
        ata_pio_read(ata_identify_dev_buf,512);
        ata_wait_not_busy();
        ata_wait_no_drq();
        

        return 0x80;
   }
   else if(lba1 == 0x69  && lba2 == 0x96){

        //kputs("Unidade SATAPI\n");   
        ata_cmd_write(ATA_CMD_IDENTIFY_PACKET_DEVICE);
        ata_wait(400);
        ata_wait_drq(); 
        ata_pio_read(ata_identify_dev_buf,512);
        ata_wait_not_busy();
        ata_wait_no_drq();
        return 0x80;

   }
   else if(lba1 == 0x3C && lba2 == 0xC3){
        //kputs("Unidade SATA\n");   
        // O dispositivo responde imediatamente um erro ao cmd Identify device
        // entao devemos esperar pelo DRQ ao invez de um BUSY
        // em seguida enviar 256 word de dados PIO.
        ata_wait_drq(); 
        ata_pio_read(ata_identify_dev_buf,512);
        ata_wait_not_busy();
        ata_wait_no_drq();
        return 0;
   }


   else if(lba1 == 0 && lba2 == 0){
        // kputs("Unidade PATA\n");
        // aqui esperamos pelo DRQ
        // e eviamoos 256 word de dados PIO
        ata_wait_drq();
        ata_pio_read(ata_identify_dev_buf,512);

        ata_wait_not_busy();
        ata_wait_no_drq();
        return 0;
    }


	return 0;   

}


// TODO
// Nelson aqui, devemos destinguir se a Interface é IDE ou AHCI
// Por em quanto temos suporte a IDE
int read_sector(void *buf,uint64_t addr,uint16_t count,char dev)
{

    int i;
    if(nport_ajuste(dev) != 0)
    return -1;

    if(current_dev->dev_type == ATA_DEVICE_TYPE){
	for(i=0;i < count;i++){
        if((ide_read_sector(dev,1,addr + i ,buf + (current_dev->dev_byte_per_sector*i))) !=0)
        return -1;

	}

    }
    else if(current_dev->dev_type == ATAPI_DEVICE_TYPE){
	for(i=0;i < count;i++){
        if((atapi_read_sector(dev,count,addr + i,buf+ (current_dev->dev_byte_per_sector*i)))!=0)
        return -1;
    	}
	
    }
    return 0;

}

int write_sector(void *buf,uint64_t addr,uint16_t count,char dev)
{
    int i;
    if(nport_ajuste(dev) != 0)
    return 1;

    if(current_dev->dev_type == ATA_DEVICE_TYPE){
    for(i=0;i < count;i++){
        if((ide_write_sector(dev,1,addr + i ,buf + (current_dev->dev_byte_per_sector*i))) !=0)
        return -1;
    }    

    }
    else if(current_dev->dev_type == ATAPI_DEVICE_TYPE){
        kprintf("Acesso negado, apenas leitura devd%\n",dev);
        return -1;
    }

    return 0;

}




/* *
 * Copyright (C) 2017-2018 (Nelson Sapalo da Silva Cole)
 * Khole OS v0.3
 *
 *
 */
//#include "ata.h"

#define DISK1 1
#define DISK2 2
#define DISK3 3
#define DISK4 4

static const char *ata_sub_class_code_register_strings[] ={
    "Unknown",
    "IDE Controller",
    "Unknown",
    "Unknown",
    "RAID Controller",
    "Unknown",
    "AHCI Controller"
};


extern st_dev *current_dev;



// base address 
static _u32 ATA_BAR0;    // Primary Command Block Base Address
static _u32 ATA_BAR1;    // Primary Control Block Base Address
static _u32 ATA_BAR2;    // Secondary Command Block Base Address
static _u32 ATA_BAR3;    // Secondary Control Block Base Address
static _u32 ATA_BAR4;    // Legacy Bus Master Base Address
static _u32 ATA_BAR5;    // AHCI Base Address / SATA Index Data Pair Base Address



/*
 ****************************************************************
 * ata_initialize:
 *     Inicializa o IDE e mostra informações sobre o disco.
 *
 */
int ata_initialize()
{
    //kprintf("sm-disk-disk-ata_initalize:\n");
    kprintf("sm-disk-disk-ata_initalize: [ IDE/AHCI Initialize ]\n");
	refresh_screen();

    _u32 data;
    data = (_u32) pci_scan_device(PCI_CALSSE_MASS);

    if(data == -1)
	{
		kprintf("sm-disk-disk-ata_initalize: pci_scan_device fail. ret={%d} \n", (_u32) data);
		refresh_screen();
	    return(PCI_MSG_ERROR); // Abortar	
	}
    
    _u8 bus =(data  >>  8 &0xff);
    _u8 dev =(data  >> 3  &31);
    _u8 fun =(data  &7);


	kprintf("sm-disk-disk-ata_initalize: chamando ata_pci_configuration_space\n");
	refresh_screen();

    data = (_u32) ata_pci_configuration_space(bus,dev,fun);

    if(data == PCI_MSG_ERROR)
	{
        kprintf("Error Driver [%X]\n",data);
        refresh_screen();
		return 1;    
	
	}else if(data == PCI_MSG_AVALIABLE){
        
        kprintf("Not suport, RAID Controller\n");
		refresh_screen();
        return 1;       
    }


    // Initialize base address
    // AHCI/IDE Compativel com portas IO IDE legado
    ATA_BAR0 = (ata_pci.bar0 & ~7) + ATA_IDE_BAR0 * ( !ata_pci.bar0);
    ATA_BAR1 = (ata_pci.bar1 & ~3) + ATA_IDE_BAR1 * ( !ata_pci.bar1);       
    ATA_BAR2 = (ata_pci.bar2 & ~7) + ATA_IDE_BAR2 * ( !ata_pci.bar2);
    ATA_BAR3 = (ata_pci.bar3 & ~3) + ATA_IDE_BAR3 * ( !ata_pci.bar3);
    ATA_BAR4 = (ata_pci.bar4 & ~0x7) + ATA_IDE_BAR4 * ( !ata_pci.bar4);
    ATA_BAR5 = (ata_pci.bar5 & ~0xf) + ATA_IDE_BAR5 * ( !ata_pci.bar5);

    if(ata.chip_control_type == ATA_IDE_CONTROLLER){

    //Soft Reset, defina IRQ
    outb(ATA_BAR1,0xff);
    outb(ATA_BAR3,0xff);
    outb(ATA_BAR1,0x00);
    outb(ATA_BAR3,0x00);


    ata_record_dev = 0xff;
    ata_record_channel = 0xff;

    //cli();
    //irq_enable(14);
    //irq_enable(15);
    //sti();

    //kputs("[ IDE Mass Storage initialize ]\n");
	printf("[ IDE Mass Storage initialize ]\n");
	refresh_screen();
    ide_mass_storage_initialize();


    }else if(ata.chip_control_type == ATA_AHCI_CONTROLLER){

    // Aqui, vamos mapear o BAR5
    // Estou colocando na marca 28MB
    
	printf("ata_initialize: mem_map para ahci\n");
	refresh_screen();
	//mem_map( (uint32_t*)0x01C00000, (uint32_t*) ATA_BAR5, 0x13, 2);

    //kputs("[ AHCI Mass Storage initialize ]\n");
    //ahci_mass_storage_init();


    }else {

        kprintf("Controlador IDE ou AHCI nao encontrado\n");
        //while(1)hlt();
		die();
    
    }
	
	
 done:                                                                                                
    printf("done!\n");
    refresh_screen();
    return 0;	
}



void set_ata_addr(int channel)
{

    switch(channel){
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
    default:
       //PANIC
        break;

    }

}


/*
 * ata_pci_configuration_space:
 *     Espaço de configuraçao PCI Mass Storage
 */
int ata_pci_configuration_space( char bus, char dev, char fun )
{
    uint32_t data;

    kprintf("ata_pci_configuration_space: [ PCI Mass Storage Initialize ]\n");
    refresh_screen();

    // Indentification Device
    data  = (uint32_t) read_pci_config_addr( bus, dev, fun, 0 );
    
    ata_pci.vendor_id = data &0xffff;
    ata_pci.device_id = data >> 16 &0xffff;
	
    kprintf("[ Vendor ID: %X,Device ID: %X ]\n", ata_pci.vendor_id, ata_pci.device_id );
    refresh_screen();
	
    // Classe code, programming interface, revision id
    data  = (uint32_t) read_pci_config_addr( bus, dev, fun, 8 );
    
    ata_pci.classe      = data >> 24 &0xff;
    ata_pci.subclasse   = data >> 16 &0xff;
    ata_pci.prog_if     = data >> 8 &0xff;
    ata_pci.revision_id = data &0xff;

    if( ata_pci.classe == 1 && 
	    ata_pci.subclasse == 1 )
	{
        ata.chip_control_type = ATA_IDE_CONTROLLER; 
                   
        // IDE
	
        // Compatibilidade e nativo, primary
        data  = read_pci_config_addr( bus, dev, fun, 8 );
        if(data &0x200) write_pci_config_addr(bus,dev,fun,8,data | 0x100);        

        // Compatibilidade e nativo, secundary
        data  = read_pci_config_addr( bus, dev, fun, 8 );
        if(data &0x800) write_pci_config_addr(bus,dev,fun,8,data | 0x400);        



        data  = read_pci_config_addr(bus,dev,fun,8);
        if( data &0x8000 )
		{    
            // Bus Master Enable
            data  = read_pci_config_addr(bus,dev,fun,4);
            write_pci_config_addr(bus,dev,fun,4,data | 0x4);
        }; 


	    // Habilitar interrupcao (INTx#)
        data  = read_pci_config_addr(bus,dev,fun,4);
        write_pci_config_addr(bus,dev,fun,4,data & ~0x400);



       	// IDE Decode Enable
       	data  = read_pci_config_addr(bus,dev,fun,0x40);
       	write_pci_config_addr(bus,dev,fun,0x40,data | 0x80008000);



        //Synchronous DMA Control Register
	    // Enable UDMA
	    data = read_pci_config_addr(bus,dev,fun,0x48);
	    write_pci_config_addr(bus,dev,fun,0x48,data | 0xf);

       kprintf("[ Sub Class Code %s Programming Interface %d Revision ID %d ]\n",\
       ata_sub_class_code_register_strings[ata.chip_control_type],ata_pci.prog_if,ata_pci.revision_id);
            
    }else if( ata_pci.classe == 1 && ata_pci.subclasse == 4 )
	      {
              //RAID
              ata.chip_control_type = ATA_RAID_CONTROLLER;
              
			  kprintf("[ Sub Class Code %s Programming Interface %d Revision ID %d ]\n",\
                  ata_sub_class_code_register_strings[ata.chip_control_type],ata_pci.prog_if,ata_pci.revision_id);
    
              refresh_screen(); 
			  // Em avaliacao
              return PCI_MSG_AVALIABLE;
    }
    else if(ata_pci.classe == 1 && ata_pci.subclasse == 6){
        ata.chip_control_type = ATA_AHCI_CONTROLLER;
       
        //ACHI

        // Compatibilidade e nativo, primary
        data  = read_pci_config_addr(bus,dev,fun,8);
        if(data &0x200) write_pci_config_addr(bus,dev,fun,8,data | 0x100);        

        // Compatibilidade e nativo, secundary
        data  = read_pci_config_addr(bus,dev,fun,8);
        if(data &0x800) write_pci_config_addr(bus,dev,fun,8,data | 0x400);        



        data  = read_pci_config_addr(bus,dev,fun,8);
        if(data &0x8000) {    
        // Bus Master Enable
        data  = read_pci_config_addr(bus,dev,fun,4);
        write_pci_config_addr(bus,dev,fun,4,data | 0x4);

        } 


        // IDE Decode Enable
        data  = read_pci_config_addr(bus,dev,fun,0x40);
        write_pci_config_addr(bus,dev,fun,0x40,data | 0x80008000);



        
        // Habilitar interrupcao (INTx#)
        data  = read_pci_config_addr(bus,dev,fun,4);
        write_pci_config_addr(bus,dev,fun,4,data & ~0x400);


        kprintf("[ Sub Class Code %s Programming Interface %d Revision ID %d ]\n",\
        ata_sub_class_code_register_strings[ata.chip_control_type],ata_pci.prog_if,ata_pci.revision_id);
        refresh_screen();		
    }
    else {
       //PANIC 
        kprintf("PANICO DRIVER BLOCK");
		refresh_screen();
        while(TRUE);
    }



    // PCI cacheline, Latancy, Headr type, end BIST
    data  = read_pci_config_addr(bus,dev,fun,0xC);

    ata_pci.primary_aster_tatency_timer = data >>8 &0xff;
    ata_pci.header_type     = data >>16 &0xff;
    ata_pci.BIST            = data >>24 &0xff;
    
    ata_pci.bar0    = read_pci_config_addr(bus,dev,fun,0x10);
    ata_pci.bar1    = read_pci_config_addr(bus,dev,fun,0x14);
    ata_pci.bar2    = read_pci_config_addr(bus,dev,fun,0x18);
    ata_pci.bar3    = read_pci_config_addr(bus,dev,fun,0x1C);
    ata_pci.bar4    = read_pci_config_addr(bus,dev,fun,0x20);
    ata_pci.bar5    = read_pci_config_addr(bus,dev,fun,0x24);




//-------------------------------------------------------------------

    
    // Interrupt
    data  = read_pci_config_addr(bus,dev,fun,0x3C);
    ata_pci.interrupt_line  = data &0xff;
    ata_pci.interrupt_pin   = data >> 8 &0xff;



    // PCI command and status
    data  = read_pci_config_addr(bus,dev,fun,4);
    ata_pci.command = data &0xffff; 
    ata_pci.status  = data >>16 &0xffff;
	
    kprintf("[ Command %x Status %x ]\n",ata_pci.command,ata_pci.status);
    refresh_screen();
	
    kprintf("[ Interrupt Line %x Interrupt Pin %x ]\n",ata_pci.interrupt_pin,ata_pci.interrupt_line);
    refresh_screen();
	
    data = read_pci_config_addr(bus,dev,fun,0x48);
    kprintf("[ Synchronous DMA Control Register %X ]\n",data);
    refresh_screen(); 

done:	
    return (PCI_MSG_SUCCESSFUL);
};






/* *
 * Copyright (C) 2017-2018 (Nelson Sapalo da Silva Cole)
 * Khole OS v0.3
 *
 *
 */
//#include "ata.h"

const char *dev_type[]={
"ATA",
"ATAPI"
};

st_dev *current_dev;     // A unidade actualmente seleccionada
st_dev *ready_queue_dev; // O início da lista.
uint32_t  dev_next_pid = 0;     // O próximo ID de unidade disponível. 


void ide_mass_storage_initialize()
{

    current_dev = ready_queue_dev   = (st_dev*)kmalloc(sizeof(st_dev));
    current_dev->dev_id             = dev_next_pid++;
    current_dev->dev_type           = -1;
    current_dev->dev_num            = -1;
    current_dev->dev_channel        = -1;
    current_dev->dev_nport          = -1;
    current_dev->next               = NULL;



    ata_identify_dev_buf =(_u16*)kmalloc(4096);

    int port;
    for(port =0;port < 4;port++)
        ide_dev_init(port);
    
 
    
}

int ide_dev_init(char port)
{
    int data = (int) ide_identify_device(port);
    //_u8 data = ide_identify_device(port);
    if(data == -1)
    return 1;

    st_dev *new_dev = (st_dev*)kmalloc(sizeof(st_dev));
    if(data == 0){

        // unidades ATA

        new_dev->dev_type   = (ata_identify_dev_buf[0]&0x8000)? 0xffff:ATA_DEVICE_TYPE;
        new_dev->dev_access = (ata_identify_dev_buf[83]&0x0400)? ATA_LBA48:ATA_LBA28;
        new_dev->dev_modo_transfere = (ata_identify_dev_buf[49]&0x0100)? ATA_DMA_MODO:ATA_PIO_MODO;
        new_dev->dev_total_num_sector  = ata_identify_dev_buf[60];
        new_dev->dev_total_num_sector += ata_identify_dev_buf[61];
        new_dev->dev_byte_per_sector = 512; 
        new_dev->dev_total_num_sector_lba48  = ata_identify_dev_buf[100];
        new_dev->dev_total_num_sector_lba48 += ata_identify_dev_buf[101];
        new_dev->dev_total_num_sector_lba48 += ata_identify_dev_buf[102];
        new_dev->dev_total_num_sector_lba48 += ata_identify_dev_buf[103];
        new_dev->dev_size = (new_dev->dev_total_num_sector_lba48 * 512);

        
    }else if(data == 0x80){

        // Unidades ATAPI

        new_dev->dev_type   =(ata_identify_dev_buf[0]&0x8000)? ATAPI_DEVICE_TYPE : 0xffff;
        new_dev->dev_access = ATA_LBA28;
        new_dev->dev_modo_transfere = (ata_identify_dev_buf[49]&0x0100)? ATA_DMA_MODO:ATA_PIO_MODO;
        new_dev->dev_total_num_sector  = 0;
        new_dev->dev_total_num_sector += 0;
        new_dev->dev_byte_per_sector = 2048; 
        new_dev->dev_total_num_sector_lba48  = 0;
        new_dev->dev_total_num_sector_lba48 += 0;
        new_dev->dev_total_num_sector_lba48 += 0;
        new_dev->dev_total_num_sector_lba48 += 0;
        new_dev->dev_size = (new_dev->dev_total_num_sector_lba48 * 2048);

    
    }else{
        //Identificar o erro
        return (1);}

    //Dados em comum.

    new_dev->dev_id     = dev_next_pid++;
    new_dev->dev_num    = ata.dev_num;
    new_dev->dev_channel= ata.channel;


        new_dev->dev_nport = port;
        switch(port){
            case 0:
            dev_nport.dev0 = 0x81;
            break;
            case 1:
            dev_nport.dev1 = 0x82;
            break;
            case 2:
            dev_nport.dev2 = 0x83;
            break;
            case 3:
            dev_nport.dev3 = 0x84;
            break;        
        }



    kprintf("[ Detected Disk type: %s ]\n",dev_type[new_dev->dev_type]);

    new_dev->next = NULL;


    //add no fim da lista
    st_dev* tmp_dev = (st_dev*)ready_queue_dev;

    while (tmp_dev->next){
        tmp_dev = tmp_dev->next;
    }
    
    tmp_dev->next = new_dev;
    return 0;
}




static inline void dev_switch(_void)
{

    // Pula, se ainda não tiver 
    // nenhuma unidade
    if (!current_dev)
    return;
    // Obter a próxima tarefa a ser executada.
    current_dev = current_dev->next;
    
    // Se caímos no final da lista vinculada, 
    // comece novamente do início.
    if (!current_dev)
    current_dev = ready_queue_dev;


}

static inline int getpid_dev()
{
    return current_dev->dev_id;
}


static inline int getnport_dev()
{
    return current_dev->dev_nport;
}






int nport_ajuste(char nport){
    _i8 i = 0;
    while(nport != getnport_dev()){
    if (i == 4)return 1;
    dev_switch();
    i++;
    }
    if(getnport_dev() == -1)return 1;
     return 0;
}



/**
 * Copyright (C) 2017-2018 (Nelson Sapalo da Silva Cole)
 * Khole OS v0.3
 *  
 *
 *
 */
//#include "ata.h"

_void ata_pio_read(_void *buffer,_i32 bytes){
__asm__ __volatile__(\
                "cld;\
                 rep; insw"::"D"(buffer),\
                "d"(ata.cmd_block_base_address + ATA_REG_DATA),\
                "c"(bytes/2));


}


_void ata_pio_write(_void *buffer,_i32 bytes){
__asm__ __volatile__(\
                "cld;\
                 rep; outsw"::"S"(buffer),\
                "d"(ata.cmd_block_base_address + ATA_REG_DATA),\
                "c"(bytes/2));
}



/**
 * Copyright (C) 2017-2018 (Nelson Sapalo da Silva Cole)
 * Khole OS v0.3
 *
 */
//#include "ata.h"


extern st_dev *current_dev;
extern uint8_t *dma_addr;

static inline void atapi_pio_read(void *buffer,uint32_t bytes)
{
__asm__ __volatile__(\
                "cld;\
                 rep; insw"::"D"(buffer),\
                "d"(ata.cmd_block_base_address + ATA_REG_DATA),\
                "c"(bytes/2));

}

int atapi_read_sector(char nport,uint16_t count,uint64_t addr,void *buffer)
{

    uint32_t sector_size = current_dev->dev_byte_per_sector;
    uint8_t  modo_atapi  = 0;
    char atapi_packet [] ={ATAPI_CMD_READ,0,0,0,0,0,0,0,0,0,0,0};

    
    ata_assert_dever(nport); //FIXME
    if(current_dev->dev_modo_transfere == ATA_DMA_MODO)
        switch(nport){
            case 0: dma_addr = (_u8*)DMA_PHYS_ADDR0;
                    break;
            case 1: dma_addr = (_u8*)DMA_PHYS_ADDR1;
                    break;
            case 2: dma_addr = (_u8*)DMA_PHYS_ADDR2;
                    break;
            case 3: dma_addr = (_u8*)DMA_PHYS_ADDR3;
                    break;

    }
    
    
    

    // configurar o pacote SCSI, 
    // 12 bytes de tamanho
    // Use LBA28
    atapi_packet [ 0x02 ] = ( addr >> 24 ) & 0xff ;
    atapi_packet [ 0x03 ] = ( addr >> 16 ) & 0xff ;
    atapi_packet [ 0x04 ] = ( addr >> 8 ) & 0xff ;
    atapi_packet [ 0x05 ] = ( addr) & 0xff ;
    atapi_packet [ 0x09 ] = (count);
    
    // Seleccionar a unidade
    outb(ata.cmd_block_base_address + ATA_REG_DEVSEL,0x40 | ata.dev_num << 4);
    // verifique se e a mesma unidade para nao esperar
    if(ata_record_dev != ata.dev_num && ata_record_channel != ata.channel){
            ata_wait(400); // 400 ns
            ata_record_dev      = ata.dev_num;
            ata_record_channel  = ata.channel;
    }

    // Selecionar modo ATAPI
    // 0 = Modo PIO.
    // 1 = DMA or UDMA
    if( current_dev->dev_modo_transfere == ATA_DMA_MODO){

        modo_atapi = 1;
        sector_size =0;
    } 
    outb(ata.cmd_block_base_address + ATA_REG_FEATURES,modo_atapi); // Modo PIO or DMA

    // Defina o tamanho do buffer em LBA0 e LBA1
    // O tamanho do bytes por sector
     outb(ata.cmd_block_base_address + ATA_REG_LBA0,sector_size &0xff);   // LBA 7-0   
	 outb(ata.cmd_block_base_address + ATA_REG_LBA1,sector_size >> 8);   // LBA 15-8

    // Enviar comando PACKET
    ata_cmd_write(ATA_CMD_PACKET);
    if(modo_atapi == 0)ata_wait_irq(); //FIXME IRQs
    else{ 
    if(ata_wait_not_busy() != 0)return -1;
    
                
    
    }

    if(ata_wait_drq() != 0)return -1;
    // Enviar os dados do pacote
    __asm__ __volatile__("cld; rep; outsw" ::"c" (6) , "d" (\
    (ata.cmd_block_base_address +ATA_REG_DATA)),"S"(atapi_packet));
 
    if(ata_wait_drq() != 0)return -1; //TODO Nelson e mesmo correcto DRQ aqui?

    if( current_dev->dev_modo_transfere == ATA_DMA_MODO){


           
            ide_dma_data(buffer,current_dev->dev_byte_per_sector*count,0x0,nport);    

            ide_dma_start();

            ata_wait_irq();

            while(ide_dma_read_status() &1)
            if(ide_dma_read_status() &2){
            ide_dma_stop(); 
            return -1;
            } 

            ide_dma_stop();
            __asm__ __volatile__("cld; rep; movsd;"::"D"(buffer),\
            "S"(dma_addr),"c"((current_dev->dev_byte_per_sector*count)/4));
     

     return 0;


    }
    
    atapi_pio_read(buffer,sector_size);
    ata_wait_irq();
    // Verifica erros
    
    return 0;
}

/* *
 * Copyright (C) 2017-2018 (Nelson Sapalo da Silva Cole)
 * Khole OS v0.3
 *
 *
 */
//#include "ata.h"

extern st_dev *current_dev;
//extern _u8 nested_task;
_u8 *dma_addr;

static inline _void ata_set_device_and_sector(_u32 count,_u64 addr,\
                                            _i32 access_type,_i8 nport)
{
   
    ata_assert_dever(nport);

    switch(access_type){
    case 28:
        //Mode LBA28
	    outb(ata.cmd_block_base_address + ATA_REG_SECCOUNT,count);	// Sector Count 7:0
	    outb(ata.cmd_block_base_address + ATA_REG_LBA0,addr);		        // LBA 7-0   
	    outb(ata.cmd_block_base_address + ATA_REG_LBA1,addr >> 8);          // LBA 15-8
	    outb(ata.cmd_block_base_address + ATA_REG_LBA2,addr >> 16);	        // LBA 23-16
         // Modo LBA active, Select device, and LBA 27-24
        outb(ata.cmd_block_base_address + ATA_REG_DEVSEL,0x40 |(ata.dev_num << 4) | (addr >> 24 &0x0f));
        // verifique se e a mesma unidade para nao esperar pelos 400ns
        if(ata_record_dev != ata.dev_num && ata_record_channel != ata.channel){
            ata_wait(400);
            //verifique erro
            ata_record_dev      = ata.dev_num;
            ata_record_channel  = ata.channel;}
        break;
    case 48:
        //Mode LBA48
        outb(ata.cmd_block_base_address + ATA_REG_SECCOUNT,0);	            // Sector Count 15:8
	    outb(ata.cmd_block_base_address + ATA_REG_LBA0,addr >> 24);	        // LBA 31-24   
	    outb(ata.cmd_block_base_address + ATA_REG_LBA1,addr >> 32);	        // LBA 39-32
	    outb(ata.cmd_block_base_address + ATA_REG_LBA2,addr >> 40);	        // LBA 47-40
	    outb(ata.cmd_block_base_address + ATA_REG_SECCOUNT,count);	        // Sector Count 7:0
	    outb(ata.cmd_block_base_address + ATA_REG_LBA0,addr);		        // LBA 7-0   
	    outb(ata.cmd_block_base_address + ATA_REG_LBA1,addr >> 8);           // LBA 15-8
	    outb(ata.cmd_block_base_address + ATA_REG_LBA2,addr >> 16);	        // LBA 23-16
        outb(ata.cmd_block_base_address + ATA_REG_DEVSEL,0x40 | ata.dev_num << 4);   // Modo LBA active, Select device,        
        // verifique se e a mesma unidade para nao esperar pelos 400ns
        if(ata_record_dev != ata.dev_num && ata_record_channel != ata.channel){
            ata_wait(400);
            ata_record_dev      = ata.dev_num;
            ata_record_channel  = ata.channel;}
        break;
    case 0:
        //Modo CHS
        // not suport
        break;



       }
       

}


_i32 ide_read_sector(_i8 nport,_u16 count,_u64 addr, _void *buffer)
{ 
        //nested_task = 1;
        //select device, lba, count
        ata_set_device_and_sector(count,addr,current_dev->dev_access,nport);


        if(current_dev->dev_modo_transfere == ATA_DMA_MODO)
        switch(nport){
            case 0: dma_addr = (_u8*)DMA_PHYS_ADDR0;
                    break;
            case 1: dma_addr = (_u8*)DMA_PHYS_ADDR1;
                    break;
            case 2: dma_addr = (_u8*)DMA_PHYS_ADDR2;
                    break;
            case 3: dma_addr = (_u8*)DMA_PHYS_ADDR3;
                    break;

        }


        
        
        if(current_dev->dev_access == ATA_LBA28 && current_dev->dev_modo_transfere == ATA_PIO_MODO){

            ata_cmd_write(ATA_CMD_READ_SECTORS);
            //ata_wait_irq(); //FIXME IRQs
            ata_wait_not_busy();
            if(ata_wait_drq() != 0)return -1;
            ata_pio_read(buffer,current_dev->dev_byte_per_sector);
            ata_wait_not_busy();
            if(ata_wait_no_drq() != 0){

            //nested_task = 0;
            return -1;

            }

        }

        else if(current_dev->dev_access == ATA_LBA48 && current_dev->dev_modo_transfere == ATA_PIO_MODO){

            ata_cmd_write(ATA_CMD_READ_SECTORS_EXT);
            //ata_wait_irq(); //FIXME IRQs
            ata_wait_not_busy();
            if(ata_wait_drq() != 0)return -1;
            ata_pio_read(buffer,current_dev->dev_byte_per_sector);
            ata_wait_not_busy();
            if(ata_wait_no_drq() != 0){
            
            //nested_task = 0;
            return -1;
            }
            
        }

        else if(current_dev->dev_access == ATA_LBA28 && current_dev->dev_modo_transfere == ATA_DMA_MODO){

            
            ide_dma_data(dma_addr,current_dev->dev_byte_per_sector*count,0x0,nport);    
            ata_cmd_write(ATA_CMD_READ_DMA);
            
            ide_dma_start();

            ata_wait_irq();
	    
            
            while(ide_dma_read_status() &1)
            if(ide_dma_read_status() &2){
            ide_dma_stop();
            //nested_task = 0; 
            return -1;
            }
            ide_dma_stop();
            

            __asm__ __volatile__("cld; rep; movsd;"::"D"(buffer),\
            "S"(dma_addr),"c"((current_dev->dev_byte_per_sector*count)/4));
            
        }


        else if(current_dev->dev_access == ATA_LBA48 && current_dev->dev_modo_transfere == ATA_DMA_MODO){
   

            ide_dma_data(dma_addr,current_dev->dev_byte_per_sector*count,0x0,nport);    
            ata_cmd_write(ATA_CMD_READ_DMA_EXT);
            
            ide_dma_start();

            ata_wait_irq();
            
            while(ide_dma_read_status() &1)
            if(ide_dma_read_status() &2){
            ide_dma_stop();
            //nested_task = 0; 
            return -1;
            }

            ide_dma_stop();
          
          
            __asm__ __volatile__("cld; rep; movsd;"::"D"(buffer),\
            "S"(dma_addr),"c"((current_dev->dev_byte_per_sector*count)/4));
         
        }

        //nested_task = 0;
        return 0;

}

_i32 ide_write_sector(_i8 nport,_u16 count,_u64 addr, _void *buffer)
{ 
       // nested_task = 1;
     
        //select device, lba, count
        ata_set_device_and_sector(count,addr,current_dev->dev_access,nport);

        if(current_dev->dev_modo_transfere == ATA_DMA_MODO)
        switch(nport){
            case 0: dma_addr = (_u8*)DMA_PHYS_ADDR0;
                    break;
            case 1: dma_addr = (_u8*)DMA_PHYS_ADDR1;
                    break;
            case 2: dma_addr = (_u8*)DMA_PHYS_ADDR2;
                    break;
            case 3: dma_addr = (_u8*)DMA_PHYS_ADDR3;
                    break;

        }

        
        if(current_dev->dev_access == ATA_LBA28 && current_dev->dev_modo_transfere == ATA_PIO_MODO){

            ata_cmd_write(ATA_CMD_WRITE_SECTORS);
            //ata_wait_irq(); //FIXME IRQs
            ata_wait_not_busy();
            if(ata_wait_drq() != 0)return -1;
            ata_pio_write(buffer,current_dev->dev_byte_per_sector);

            //Flush Cache
            ata_cmd_write(ATA_CMD_FLUSH_CACHE);
            ata_wait_not_busy();
            if(ata_wait_no_drq() != 0){
            
            //nested_task = 0;
            return -1;
            }
        }

        else if(current_dev->dev_access == ATA_LBA48 && current_dev->dev_modo_transfere == ATA_PIO_MODO){

            ata_cmd_write(ATA_CMD_WRITE_SECTORS_EXT);
            //ata_wait_irq(); //FIXME IRQs
            ata_wait_not_busy();
            if(ata_wait_drq() != 0)return -1;
            ata_pio_write(buffer,current_dev->dev_byte_per_sector);

            //Flush Cache
            ata_cmd_write(ATA_CMD_FLUSH_CACHE_EXT);
            ata_wait_not_busy();
            if(ata_wait_no_drq() != 0){
            
            //nested_task = 0;
            return -1;
            }

        }    
    
        else if(current_dev->dev_access == ATA_LBA28 && current_dev->dev_modo_transfere == ATA_DMA_MODO){
            
            __asm__ __volatile__("cld; rep; movsd;"::"S"(buffer),\
            "D"(dma_addr),"c"((current_dev->dev_byte_per_sector*count)/4));


            ide_dma_data(dma_addr,current_dev->dev_byte_per_sector*count,0x1,nport);    
            ata_cmd_write(ATA_CMD_WRITE_DMA);

            ide_dma_start();

            ata_wait_irq();
            while(ide_dma_read_status() &1)
            if(ide_dma_read_status() &2){
            ide_dma_stop();
            //nested_task = 0; 
            return -1;
            } 
            ide_dma_stop();
            //Flush Cache
            ata_cmd_write(ATA_CMD_FLUSH_CACHE); 

        } 


        else if(current_dev->dev_access == ATA_LBA48 && current_dev->dev_modo_transfere == ATA_DMA_MODO){

            __asm__ __volatile__("cld; rep; movsd;"::"S"(buffer),\
            "D"(dma_addr),"c"((current_dev->dev_byte_per_sector*count)/4));            

            ide_dma_data(dma_addr,current_dev->dev_byte_per_sector*count,0x1,nport);    
            ata_cmd_write(ATA_CMD_WRITE_DMA_EXT);

            ide_dma_start();

            ata_wait_irq();
            while(ide_dma_read_status() &1)
            if(ide_dma_read_status() &2){
            ide_dma_stop();
            //nested_task = 0; 
            return -1;
            }
            ide_dma_stop();
            //Flush Cache
            ata_cmd_write(ATA_CMD_FLUSH_CACHE_EXT);  
        }

        //nested_task = 0;
        return 0;

}





/**
 * Copyright (C) 2017-2018 (Nelson Sapalo da Silva Cole)
 * Khole OS v0.3
 * Legacy Bus Master Base Address
 *
 *  TODO Nelson, ja mais se esqueça de habiliatar o // Bus Master Enable
 *  no espaço de configuraçao PCI (offset 0x4 Command Register)
 */
//#include "ata.h"


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

struct {
    uint32_t    addr;
    uint32_t    len;
}ide_dma_prdt[4];


void ide_dma_data(void *addr,uint16_t byte_count,uint8_t flg,uint8_t nport)
{
    _u8 data;
           
    ide_dma_prdt[nport].addr   = (_u32)addr; //TODO (&~1)sera que e necessario?
    ide_dma_prdt[nport].len    = byte_count |0x80000000;

    uint32_t phy = (uint32_t)&ide_dma_prdt[nport];

    // prds physical
    //outpl(ata.bus_master_base_address + ide_dma_reg_addr,phy);
    outportl(ata.bus_master_base_address + ide_dma_reg_addr,phy);



     //  bit 3 read/write
    //      0 = Memory reads
    //      1 = Memory writes
    data = inb(ata.bus_master_base_address + ide_dma_reg_cmd) &~8;

    flg  =1; //TODO bit 8 Confilito no Oracle VirtualBox 
    outb(ata.bus_master_base_address + ide_dma_reg_cmd, data | flg << 3);
    //Limpar o bit de interrupção e o bit de erro no registo de status
    data = inb(ata.bus_master_base_address + ide_dma_reg_status);
    outb(ata.bus_master_base_address + ide_dma_reg_status, data &~6);

    
    
}


_void ide_dma_start(){
    _u8 data = inb(ata.bus_master_base_address + ide_dma_reg_cmd);
    outb(ata.bus_master_base_address + ide_dma_reg_cmd, data | 1);

}

_void ide_dma_stop(){
    _u8 data = inb(ata.bus_master_base_address + ide_dma_reg_cmd);
    outb(ata.bus_master_base_address + ide_dma_reg_cmd, data &~1);
    data = inb(ata.bus_master_base_address + ide_dma_reg_status);
    outb(ata.bus_master_base_address + ide_dma_reg_status, data &~6);

}

int ide_dma_read_status(){
    return inb(ata.bus_master_base_address + ide_dma_reg_status);
}



// pci support

#define PCI_PORT_ADDR 0xCF8
#define PCI_PORT_DATA 0xCFC



#define CONFIG_ADDR(bus,device,fn,offset)\
                       (\
                       (((uint32_t)(bus) &0xff) << 16)|\
                       (((uint32_t)(device) &0x3f) << 11)|\
                       (((uint32_t)(fn) &0x07) << 8)|\
                       ((uint32_t)(offset) &0xfc)|0x80000000)
					   
					   


/*					   
unsigned char read_pci_config_addr( unsigned char bus, 
                                 unsigned char slot, 
								 unsigned char func, 
								 unsigned char offset )
{
	pciConfigReadByte( bus, slot, func, offset);	
};
*/

uint32_t read_pci_config_addr(int bus,int dev,int fun, int offset){
    outportl(PCI_PORT_ADDR,CONFIG_ADDR(bus,dev,fun, offset));
    return inportl(PCI_PORT_DATA);
}


void write_pci_config_addr( int bus, 
                            int dev,
							int fun, 
							int offset, 
							int data )
{
    outportl(PCI_PORT_ADDR,CONFIG_ADDR(bus,dev,fun, offset));
    outportl(PCI_PORT_DATA,data);
}

const char *pci_classes[]={
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

// Esta funçao deve retornar o numero de barramento, a dispositivo e a funçao
// do dispositivo conectado ao barramento PCI, de acordo a classe.
uint32_t pci_scan_device(int classe)
{
    uint32_t data = -1;

    int bus, dev, fun;
		
	printf("sm-disk-disk-pci_scan_device:\n");
    refresh_screen();
    
    for(bus = 0;bus < 256; bus++){
        for(dev = 0; dev < 32; dev++){
            for(fun = 0; fun < 8; fun++){
                outportl(PCI_PORT_ADDR,CONFIG_ADDR(bus,dev,fun, 0x8));
                data =inportl(PCI_PORT_DATA);
                if((data >> 24 &0xff) == classe){
                    kprintf("[ Detected PCI device: %s ]\n",pci_classes[classe]);
                    return (fun + (dev * 8) + (bus * 32));
            
                }
            }
     
        }
     
    }

    kprintf("[ PCI Not device detected ]\n");
    return (-1);

}

//
// End.
//

