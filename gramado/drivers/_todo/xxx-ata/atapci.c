

#include <kernel.h>

// #todo:
// Checar se temos uma lista dessa no suporte a PCI.
					   
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

/* read_pci_config_addr:
 *     READ */

uint32_t 
diskReadPCIConfigAddr ( int bus, 
						int dev,
						int fun, 
						int offset )
{
	outportl ( PCI_PORT_ADDR, CONFIG_ADDR( bus, dev, fun, offset ) );
	
	return (uint32_t) inportl(PCI_PORT_DATA);
}


/* write_pci_config_addr:
 *     WRITE */

void 
diskWritePCIConfigAddr ( int bus, 
                         int dev,
						 int fun, 
						 int offset, 
						 int data )
{
    outportl ( PCI_PORT_ADDR, CONFIG_ADDR( bus, dev, fun, offset ) );
	
    outportl ( PCI_PORT_DATA, data );
};



/*
 ********************************************************************
 * pci_scan_device:
 *     Busca um dispositivo de acordo com a classe.  
 *     Esta função deve retornar uma varia'vel contendo: 
 *     + O número de barramento, 
 *     + o dispositivo e  
 *     + a função.
 *
 * IN: Class.
 * OUT: data.
 *      -1 = error (#bugbug, pois o tipo de retorno eh unsigned int)
 */

uint32_t diskPCIScanDevice ( int class ){
	
    int bus, dev, fun;
    
	//#bugbug -1 para unsigned int 
	
	uint32_t data = -1;
	
#ifdef KERNEL_VERBOSE		
	printf("sm-disk-disk-diskPCIScanDevice:\n");
    refresh_screen();
#endif
    
    //
	// Probe.
	//
	
	for ( bus=0; bus < 256; bus++ )
	{
        for ( dev=0; dev < 32; dev++ )
		{
            for ( fun=0; fun < 8; fun++ )
			{
                outportl( PCI_PORT_ADDR, CONFIG_ADDR( bus, dev, fun, 0x8) );
				
                data = inportl(PCI_PORT_DATA);
                
				if ( ( data >> 24 & 0xff ) == class )
				{
					
//#ifdef KERNEL_VERBOSE							
					printf ( "[ Detected PCI device: %s ]\n", 
					         pci_classes[class] );
//#endif
							 
					// Done !
                    
					return (uint32_t) ( fun + (dev*8) + (bus*32) );
                }
            };
     
        };
    };

	// Fail !
    
	kprintf ("PCI device NOT detected\n");		
	
	//#bugbug
	//isso e' lento
	//refresh_screen();
	
    return (uint32_t) (-1);
};



//===================


/*
 *************************************************************
 * diskATAPCIConfigurationSpace:
 *     Espaço de configuraçao PCI Mass Storage
 */

int diskATAPCIConfigurationSpace ( char bus, char dev, char fun ){
	
    uint32_t data;

//#ifdef KERNEL_VERBOSE	
	kprintf("diskATAPCIConfigurationSpace:\n");
    kprintf("Initializing PCI Mass Storage support..\n");
//#endif

    // Indentification Device
    data = (uint32_t) diskReadPCIConfigAddr ( bus, dev, fun, 0 );
	
	// Salvando configurações.
    ata_pci.Vendor = data &0xffff;
    ata_pci.Device = data >> 16 &0xffff;
	
//#ifdef KERNEL_VERBOSE	
	kprintf("\nDisk info:\n");
    kprintf("[ Vendor ID: %X,Device ID: %X ]\n", 
	    ata_pci.Vendor, ata_pci.Device );
//#endif	
	
    
	// Obtendo informações.
	// Classe code, programming interface, revision id.
	
    data  = (uint32_t) diskReadPCIConfigAddr ( bus, dev, fun, 8 );
    
	// Saving info.
	// Classe e sub-classe.
    // prog if.
	// Revision.
	
	ata_pci.classCode  = data >> 24 & 0xff;
    ata_pci.subclass   = data >> 16 & 0xff;
	ata_pci.progif     = data >> 8  & 0xff;
    ata_pci.revisionId = data       & 0xff;

	
	// #importante:
	// Aqui detectamos o tipo de dispositivo com base 
	// nas informações de classe e subclasse.
	
	//
	//  ## IDE ##
	//
	
    if ( ata_pci.classCode == 1 && ata_pci.subclass == 1 )
	{
        // IDE
		ata.chip_control_type = ATA_IDE_CONTROLLER; 
		
        // Compatibilidade e nativo, primary.
        data  = diskReadPCIConfigAddr( bus, dev, fun, 8 );
        if( data &0x200 )
		{ 
	        diskWritePCIConfigAddr( bus, dev, fun, 8, data | 0x100 ); 
		};        

        // Compatibilidade e nativo, secundary.
        data = diskReadPCIConfigAddr( bus, dev, fun, 8 );
        if( data &0x800 )
		{ 
	        diskWritePCIConfigAddr( bus, dev, fun, 8, data | 0x400 ); 
		};        

        data = diskReadPCIConfigAddr( bus, dev, fun, 8 );
        if( data &0x8000 )
		{    
            // Bus Master Enable
            data = diskReadPCIConfigAddr(bus,dev,fun,4);
            diskWritePCIConfigAddr(bus,dev,fun,4,data | 0x4);
        }; 

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

#ifdef KERNEL_VERBOSE 		
        //kprintf("[ Sub Class Code %s Programming Interface %d Revision ID %d ]\n",\
        //    ata_sub_class_code_register_strings[ata.chip_control_type],
	    //    ata_pci.progif,
		//	ata_pci.revisionId );
#endif

        //
        //  ## RAID ##
        //		
  
    }else if ( ata_pci.classCode == 1 && ata_pci.subclass == 4 )
	      {
              //RAID
              ata.chip_control_type = ATA_RAID_CONTROLLER;
			  
#ifdef KERNEL_VERBOSE              
			  //kprintf("[ Sub Class Code %s Programming Interface %d Revision ID %d ]\n",\
              //    ata_sub_class_code_register_strings[ata.chip_control_type], 
				//  ata_pci.progif,
				 // ata_pci.revisionId );
#endif
    
			  // Em avaliacao
              return PCI_MSG_AVALIABLE;
			  
			  
			  
	            //
                //  ## ACHI ##
                //			  
			  
          }else if ( ata_pci.classCode == 1 && ata_pci.subclass == 6 )
		        {
					// ACHI
					
			        ata.chip_control_type = ATA_AHCI_CONTROLLER;
       
                    // Compatibilidade e nativo, primary.
                    data = diskReadPCIConfigAddr ( bus, dev, fun, 8 );
                    if ( data & 0x200 )
					{ 
		                diskWritePCIConfigAddr ( bus, dev, fun, 8, data | 0x100 ); 
		            }        

                    // Compatibilidade e nativo, secundary.
                    data = diskReadPCIConfigAddr ( bus, dev, fun, 8 );
                    if ( data & 0x800 )
					{ 
	                    diskWritePCIConfigAddr ( bus, dev, fun, 8, data | 0x400 ); 
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

#ifdef KERNEL_VERBOSE
                    //kprintf("[ Sub Class Code %s Programming Interface %d Revision ID %d ]\n",\
                       // ata_sub_class_code_register_strings[ata.chip_control_type], 
		               // ata_pci.progif,
			           // ata_pci.revisionId );
#endif			

                    //Ok.
                } else {
					
					 //
                     // PANIC! 
                     //
					 
					 kprintf("sm-disk-disk-diskATAPCIConfigurationSpace: PANIC DRIVER BLOCK!");
		             die();
                 };

    
	// #obs:
	// Nesse momento já sabemos se é IDE, RAID, AHCI.
	// Vamos pegar mais informações,
    // Salvaremos as informações na estrutura.
	
	
    // PCI cacheline, Latancy, Headr type, end BIST
	
    data = diskReadPCIConfigAddr ( bus, dev, fun, 0xC );
	
	ata_pci.latency_timer = data >>  8 & 0xff;
	ata_pci.header_type   = data >> 16 & 0xff;
    ata_pci.bist          = data >> 24 & 0xff;
    
	
	//
	// ## BARs ##
	//
	
    ata_pci.BAR0 = diskReadPCIConfigAddr( bus, dev, fun, 0x10 );
    ata_pci.BAR1 = diskReadPCIConfigAddr( bus, dev, fun, 0x14 );
    ata_pci.BAR2 = diskReadPCIConfigAddr( bus, dev, fun, 0x18 );
    ata_pci.BAR3 = diskReadPCIConfigAddr( bus, dev, fun, 0x1C );
    ata_pci.BAR4 = diskReadPCIConfigAddr( bus, dev, fun, 0x20 );
    ata_pci.BAR5 = diskReadPCIConfigAddr( bus, dev, fun, 0x24 );
	
    //--------------
    
    // Interrupt
    data = diskReadPCIConfigAddr( bus, dev, fun, 0x3C );
    
    //
    // Salvando configurações.
    //		
	
	ata_pci.irq_line = data & 0xff;
    ata_pci.irq_pin  = data >> 8 & 0xff;


    // PCI command and status
    data = diskReadPCIConfigAddr( bus, dev, fun, 4 );
    

    // Salvando configurações.
   
	ata_pci.Command = data & 0xffff; 
    ata_pci.Status  = data >> 16 & 0xffff;
	
	
#ifdef KERNEL_VERBOSE	
    kprintf("[ Command %x Status %x ]\n", 
		ata_pci.Command, ata_pci.Status );
		
    kprintf("[ Interrupt Line %x Interrupt Pin %x ]\n", 
		ata_pci.irq_line, ata_pci.irq_pin );
#endif		
	
    data = diskReadPCIConfigAddr(bus,dev,fun,0x48);
	
#ifdef KERNEL_VERBOSE		
    kprintf("[ Synchronous DMA Control Register %X ]\n", data );
#endif
	
done:

#ifdef KERNEL_VERBOSE	
    refresh_screen();
#endif 
 	
    return (PCI_MSG_SUCCESSFUL);
};

















