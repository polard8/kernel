
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
	
	//
	// ## IRQ ##
	//

	D->irq_line = (uint8_t) pciConfigReadByte( bus, dev, fun, 0x3C );   //irq
	D->irq_pin = (uint8_t) pciConfigReadByte( bus, dev, fun, 0x3D );    //letras		
	
	
	kprintf ("line=%d pin=%d \n", D->irq_line, D->irq_pin );

	//pegamos o endereç[o físico do início dos registradores.
	unsigned long phy_address = ( D->BAR5 & 0xFFFFFFF0);
	

     //#debug
	  kprintf ("PhysicalAddress=%x \n", phy_address );
	
	
	
	//#todo
	//mapeando para obter o endereço virtual que o kernel pode manipular.
	//Criar esssa rotina lá em pages.c
	//unsigned long virt_address = mapping_ahci_device_address ( phy_address );
	
	//endereço base.
	//unsigned char *base_address = (unsigned char *) virt_address;
	//unsigned long *base_address32 = (unsigned long *) virt_address;		

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


