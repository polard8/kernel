
/*
 * File: ahci.c
 *
 */




// O esquema deve ser igual ao driver do ide.
// primeiro procura o dispositivo na interface PCI.
// depois inicializa.


//#importante:
//estamos seguindo o esquema do driver de ide
//para scaneamento do discpositivo. Est'a em ide/disk1.c



#include <kernel.h>


int SATAFlag;



int diskSATAPCIConfigurationSpace ( char bus, char dev, char fun ){

	
	uint32_t data;
	
	kprintf("diskSATAPCIConfigurationSpace:\n");
	
    // Indentification Device
    data = (uint32_t) diskReadPCIConfigAddr ( bus, dev, fun, 0 );	
	
	// Salvando configurações.
    sata_pci.Vendor = data &0xffff;
    sata_pci.Device = data >> 16 &0xffff;
	
	kprintf("\nDisk info:\n");
    kprintf("[ Vendor ID: %X,Device ID: %X ]\n", 
	    sata_pci.Vendor, sata_pci.Device );
	
	
	// Obtendo informações.
	// Classe code, programming interface, revision id.
	
    data  = (uint32_t) diskReadPCIConfigAddr ( bus, dev, fun, 8 );
    
	// Saving info.
	// Classe e sub-classe.
    // prog if.
	// Revision.
	
	sata_pci.classCode  = data >> 24 & 0xff;
    sata_pci.subclass   = data >> 16 & 0xff;
	sata_pci.progif     = data >> 8  & 0xff;
    sata_pci.revisionId = data       & 0xff;
	
	
	
	//
    //  ## ACHI ##
    //	
	
	if ( ata_pci.classCode == PCI_CLASSCODE_MASS && ata_pci.subclass == PCI_SUBCLASS_SATA )
	{
	
	}else{
	    kprintf("It's not a SATA device\n");
		return -1;
	}
	
	
	sata_pci.BAR0 = (unsigned long) diskReadPCIConfigAddr ( bus, dev, fun, 0x10 );
	sata_pci.BAR1 = (unsigned long) diskReadPCIConfigAddr ( bus, dev, fun, 0x14 ); 
	sata_pci.BAR2 = (unsigned long) diskReadPCIConfigAddr ( bus, dev, fun, 0x18 );
	sata_pci.BAR3 = (unsigned long) diskReadPCIConfigAddr ( bus, dev, fun, 0x1C );
	sata_pci.BAR4 = (unsigned long) diskReadPCIConfigAddr ( bus, dev, fun, 0x20 );
	sata_pci.BAR5 = (unsigned long) diskReadPCIConfigAddr ( bus, dev, fun, 0x24 );

	
	//
	// ## IRQ ##
	//

	sata_pci.irq_line = (uint8_t) pciConfigReadByte( bus, dev, fun, 0x3C );   //irq
	sata_pci.irq_pin = (uint8_t) pciConfigReadByte( bus, dev, fun, 0x3D );    //letras		
	

	//pegamos o endereç[o físico do início dos registradores.
	unsigned long phy_address = (sata_pci.BAR5 & 0xFFFFFFF0);
	
	//#todo
	//mapeando para obter o endereço virtual que o kernel pode manipular.
	//Criar esssa rotina lá em pages.c
	//unsigned long virt_address = mapping_ahci_device_address ( phy_address );
	
	//endereço base.
	//unsigned char *base_address = (unsigned char *) virt_address;
	//unsigned long *base_address32 = (unsigned long *) virt_address;		

	//Continua ... tem mais pra reproduzir do driver de ide, em disk.c
}



int ahciSATAInitialize ( int ataflag ){

		int Status = 1;  //error
	int port;
	
	unsigned long data;
	
	unsigned char bus;
	unsigned char dev;
	unsigned char fun;
	
	
	// Configurando flags do driver.
	
	ATAFlag = (int) ataflag;
	
	kprintf("ahciSATAInitialize: Initializing ..\n");
	
	//#bugbug
	//Estamos pegando um dispositicvo de armazenamento.
	//E se for ide?
	//ja estamos usando um ide.
	
	//PCI_CLASSCODE_MASS	
    data = (unsigned long) diskPCIScanDevice(PCI_CLASSE_MASS);
	
	if( data == -1 )
	{
		kprintf ("ahciSATAInitialize: diskPCIScanDevice fail. ret={%d} \n", 
		    (unsigned long) data );
		
	    // Abortar.
		Status = (int) (PCI_MSG_ERROR);
		return -1;
		//goto fail;
	}
    
    bus = ( data >> 8 & 0xff );
    dev = ( data >> 3 & 31 );
    fun = ( data      & 7 );
	
	//
	// Vamos saber mais sobre o dispositivo enconrtado. 
	//
	
    data = (unsigned long) diskSATAPCIConfigurationSpace ( bus, dev, fun );
	
    if( data == PCI_MSG_ERROR )
	{
        kprintf("sm-disk-disk-diskATAInitialize: Error Driver [%X]\n",data);
		Status = (int) 1;
		return -1;
		//goto fail;  
	
	}else if( data == PCI_MSG_AVALIABLE )
	      {
              kprintf("sm-disk-disk-diskATAInitialize: RAID Controller Not supported.\n");
		      Status = (int) 1;
		      return -1;
		      //goto fail;  
          };
	
	//continua ... tem mais pra reproduzir do driver de ide, em disk.c
	

}













