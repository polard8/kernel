
/*
 * File: ahci.c
 *      Status: Construindo um driver para ahci.
 */


//82801HM/HEM (ICH8M/ICH8M-E) SATA Controller [AHCI mode]


// O esquema deve ser igual ao driver do ide.
// primeiro procura o dispositivo na interface PCI.
// depois inicializa.
//#importante:
//estamos seguindo o esquema do driver de ide
//para scaneamento do discpositivo. Est'a em ide/disk1.c


#include <kernel.h>


int SATAFlag;



// Check device type

static int check_type(HBA_PORT *port)
{
	uint32_t ssts = port->ssts;
 
	uint8_t ipm = (ssts >> 8) & 0x0F;
	uint8_t det = ssts & 0x0F;
 
	if (det != HBA_PORT_DET_PRESENT)	// Check drive status
		return AHCI_DEV_NULL;
	if (ipm != HBA_PORT_IPM_ACTIVE)
		return AHCI_DEV_NULL;
 
	switch (port->sig)
	{
	case SATA_SIG_ATAPI:
		return AHCI_DEV_SATAPI;
	case SATA_SIG_SEMB:
		return AHCI_DEV_SEMB;
	case SATA_SIG_PM:
		return AHCI_DEV_PM;
	default:
		return AHCI_DEV_SATA;
	}
}





void probe_port(HBA_MEM *abar)
{
	// Search disk in impelemented ports
	uint32_t pi = abar->pi;
	int i = 0;
	while (i<32)
	{
		if (pi & 1)
		{
			int dt = check_type(&abar->ports[i]);
			if (dt == AHCI_DEV_SATA)
			{
				kprintf ("SATA drive found at port %d\n", i);
			}
			else if (dt == AHCI_DEV_SATAPI)
			{
				kprintf ("SATAPI drive found at port %d\n", i);
			}
			else if (dt == AHCI_DEV_SEMB)
			{
				kprintf("SEMB drive found at port %d\n", i);
			}
			else if (dt == AHCI_DEV_PM)
			{
				kprintf("PM drive found at port %d\n", i);
			}
			else
			{
				kprintf("No drive found at port %d\n", i);
			}
		}
 
		pi >>= 1;
		i ++;
	}
}



int ahciSetupDeviceStructure ( struct pci_device_d *D, char bus, char dev, char fun ){

	uint32_t data;
	
	kprintf("diskSATAPCIConfigurationSpace:\n");
	
    // Indentification Device
    data = (uint32_t) diskReadPCIConfigAddr ( bus, dev, fun, 0 );	
	
	// Salvando configurações.
    D->Vendor = data &0xffff;
    D->Device = data >> 16 &0xffff;
	
	kprintf("\nDisk info:\n");
    kprintf("Vendor=%x Device=%x\n", D->Vendor, D->Device );
	
	// Obtendo informações.
	// Classe code, programming interface, revision id.
	
    data  = (uint32_t) diskReadPCIConfigAddr ( bus, dev, fun, 8 );
    
	// Saving info.
	// Classe e sub-classe.
    // prog if.
	// Revision.
	
	D->classCode  = data >> 24 & 0xff;
    D->subclass   = data >> 16 & 0xff;
	D->progif     = data >> 8  & 0xff;
    D->revisionId = data       & 0xff;
		
	//
    //  ## ACHI ##
    //	
	
	if ( D->classCode == PCI_CLASSCODE_MASS && D->subclass == PCI_SUBCLASS_SATA )
	{
	    kprintf("It's a SATA device\n");	
	}else{
	    kprintf("It's not a SATA device\n");
		return -1;
	}

	kprintf ("progif=%d revisionID=%d \n", D->progif, D->revisionId );	
	
	D->BAR0 = (unsigned long) diskReadPCIConfigAddr ( bus, dev, fun, 0x10 );
	D->BAR1 = (unsigned long) diskReadPCIConfigAddr ( bus, dev, fun, 0x14 ); 
	D->BAR2 = (unsigned long) diskReadPCIConfigAddr ( bus, dev, fun, 0x18 );
	D->BAR3 = (unsigned long) diskReadPCIConfigAddr ( bus, dev, fun, 0x1C );
	D->BAR4 = (unsigned long) diskReadPCIConfigAddr ( bus, dev, fun, 0x20 );
	D->BAR5 = (unsigned long) diskReadPCIConfigAddr ( bus, dev, fun, 0x24 );

	kprintf ("BAR0=%x \n", (unsigned long) D->BAR0 );
	kprintf ("BAR5=%x \n", (unsigned long) D->BAR5 );	
	
    // The last PCI base address register (BAR[5], header offset 0x24) points 
	// to the AHCI base memory, it’s called ABAR (AHCI Base Memory Register). 
	// The other PCI base address registers act same as a traditional IDE controller. 
		
    //HBA memory registers can be divided into two parts: 
	//Generic Host Control registers and Port Control registers. 
	//Generic Host Control registers controls the behavior of the whole controller, 
	//while each port owns its own set of Port Control registers.	
	
	//
	// ## IRQ ##
	//

	D->irq_line = (uint8_t) pciConfigReadByte( bus, dev, fun, 0x3C );   //irq
	D->irq_pin = (uint8_t) pciConfigReadByte( bus, dev, fun, 0x3D );    //letras		
	
	
	kprintf ("line=%d pin=%d \n", D->irq_line, D->irq_pin );

	
	//ABAR (AHCI Base Memory Register). pa
	//pegamos o endereç[o físico do início dos registradores.
	unsigned long phy_address = ( D->BAR5 & 0xFFFFFFF0);
	

     //#debug
	  kprintf ("PhysicalAddress=%x \n", phy_address );
	
	
	
	//#todo
	//mapeando para obter o endereço virtual que o kernel pode manipular.
	//Criar esssa rotina lá em pages.c
	//ABAR (AHCI Base Memory Register). va
	unsigned long virt_address = mapping_ahci1_device_address ( phy_address );
	
	//endereço base.
	unsigned char *base_address = (unsigned char *) virt_address;
	unsigned long *base_address32 = (unsigned long *) virt_address;		

	
	kprintf ("VIRTUAL ADDRESS %x\n", virt_address);
	
	
	//#test
	//vamos sondar as portas usando uma estrutura que contempla os primeiros registradores,
	//então o ponteiro da estrutura é o início dos registradores.
	
	//#bugbug
	//Isso tá dando page fault ..
	//vamos fazer verbose de parte por parte,
	//até encontrarmos o problema.
	
	//probe_port ( (HBA_MEM *) virt_address );
	
	//#importante
	//#todo
	//Continua ... tem mais pra reproduzir do driver de ide, em disk.c
}



/*
 * ahciSATAInitialize:
 * 
 */

int ahciSATAInitialize ( int ataflag ){

	int Status = 1;  //error
	int port;
	
	
	struct pci_device_d *D;
	
	
	// Configurando flags do driver.
	
	ATAFlag = (int) ataflag;
	
	kprintf ("ahciSATAInitialize: Initializing ..\n");
	
	//#bugbug
	//Estamos pegando um dispositicvo de armazenamento.
	//E se for ide?
	//ja estamos usando um ide.
	
	
	//#importante
	//#todo
    //procurar na lista de dispositivos por um dispositivo de 
    //determinada classe e subclasse.
    //Vai retornar o ponteiro para a estrutura de dispositivo. 
	//(struct pci_device_d *)
	
	D = (struct pci_device_d *) scan_pci_device_list2 ( (unsigned char) PCI_CLASSCODE_MASS, 
							          (unsigned char) PCI_SUBCLASS_SATA );	
	
	
	if ( (void *) D == NULL )
	{
	    printf ("device not found\n");
	    //...
		
	}else{
		
		printf ("device found\n");
	   //...
	}
	
	
	if ( D->used != 1 || D->magic != 1234 )
	{
		kprintf ("validation fail\n");
		return -1;
	}
	
	//#debug
	// Ok funcionou .. arotina acima encontrou uma controladora SATA.
	
		//Localização.
		//D->bus
		//D->dev 
		//D->func 
	
	//
	// Vamos saber mais sobre o dispositivo enconrtado. 
	//
	
    ahciSetupDeviceStructure ( D, D->bus, D->dev, D->func );
	

	kprintf ("test done\n");
	
	//continua ... tem mais pra reproduzir do driver de ide, em disk.c
	
	return 0;
}


