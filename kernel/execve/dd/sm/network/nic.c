/*
 * File: nic.c   
 *
 * Descrição:
 *     Network interface controller
 *     Network card driver.
 *     Algum gerenciamento de adaptador de network.
 *     Esse é o header do driver da placa de rede.
 *
  * 8086/100e network controller encontrado na oracle virtual box.
 * History:
 *     2016 - Created by Fred Nora.
 *
 */
 
 
// >> The register at offset 0x00 is the "IOADDR" window. 
// >> The register at offset 0x04 is the "IODATA" window. 

 /*
   wikipedia - NIC
   A network interface controller 
   (NIC, also known as a network interface card, network adapter, 
   LAN adapter or physical network interface,[1] and by similar terms) 
   is a computer hardware component that connects a computer to a computer network.[2]
  
Connects to Motherboard via one of:
    Integrated, PCI Connector, ISA Connector, PCI-E, FireWire, USB, Thunderbolt.

Network via one of:
    Ethernet, Wi-Fi, Fibre Channel, ATM, FDDI, Token ring.

Speeds:
    10 Mbit/s, 100 Mbit/s, 1 Gbit/s, 10 Gbit/s, up to 160 Gbit/s.

Common manufacturers:
    Intel, Realtek, Broadcom, Marvell Technology Group, QLogic, Mellanox.
 
techniques:
    Polling, Interrupt-driven I/O, Programmed input/output, Direct memory access.
 
 */
 
#include <kernel.h>

/*
void nicHandler();
void nicHandler()
{
	return;
}
*/


/*
 * init_network:
 *     Inicializa o módulo gerenciador de rede.
 *     @todo: deletar: Usar nicInit()
 */
 
int init_nic (){
	
	
	//pci info.
	uint32_t data; 
	unsigned char bus;
	unsigned char dev;
	unsigned char fun;			


	
	printf("\n");
	printf("probing pci ...\n");
					
	data = (uint32_t) diskPCIScanDevice ( PCI_CLASSCODE_NETWORK);
	
	//#test: testando encontrar placa de rede.
	if( data == -1 )
	{
		printf("**fail**\n");
		
		return (int) 1;
		//refresh_screen();
	}
					
	bus = ( data >> 8 &0xff );
    dev = ( data >> 3 &31 );
    fun = ( data &7 );
					
	data = (uint32_t) diskReadPCIConfigAddr( bus, dev, fun, 0 );
					
					
	//#todo: salvar na estrutura de pci device.
	//printf("Vendor=%x \n", (data & 0xffff) );
	//printf("Device=%x \n", (data >> 16 &0xffff) );
	
    //
	//  PCI
	//	
	
	struct pci_device_d *pci_device;
	
	pci_device = (void *) malloc ( sizeof( struct pci_device_d  ) );
	
	if ( (void *) pci_device ==  NULL )
    {
		return (int) 1;
	}else{
		
		pci_device->deviceUsed = 1;
		pci_device->deviceMagic = 1234;
		
		pci_device->bus = (unsigned char) bus;
		pci_device->dev = (unsigned char) dev;
		pci_device->func = (unsigned char) fun;
		
		pci_device->Vendor = (unsigned short) (data & 0xffff);
		pci_device->Device = (unsigned short) (data >> 16 &0xffff);
		
		//...
	};

    //
	//  NIC
	//
	
	currentNIC = (void *) malloc ( sizeof( struct nic_info_d ) );
	
	if ( (void *) currentNIC ==  NULL )
	{
	    return (int) 1;	
	}else{
		
		currentNIC->used = 1;
		currentNIC->magic = 1234;
		
		currentNIC->pci = (struct pci_device_d *) pci_device;
		
		//...
		
	};	
	
	printf("done\n");		
	

    return (int) 0;	
};



//testando controlador ... 
//encontrando o controlador e identificando vendor e device.
void nic_test1 (){
	
	//pci info.
	uint32_t data; 
	unsigned char bus;
	unsigned char dev;
	unsigned char fun;		
	
	printf("\n");
	printf("probing pci ...\n");
					
	data = (uint32_t) diskPCIScanDevice ( PCI_CLASSCODE_NETWORK);
	
	//#test: testando encontrar placa de rede.
	if( data == -1 )
	{
		printf("**fail**\n");
		refresh_screen();
	}
					
	bus = ( data >> 8 &0xff );
    dev = ( data >> 3 &31 );
    fun = ( data &7 );
					
	data = (uint32_t) diskReadPCIConfigAddr( bus, dev, fun, 0 );
					
	printf("Vendor=%x \n", (data & 0xffff) );
	printf("Device=%x \n", (data >> 16 &0xffff) );
	printf("done\n");	
};



void show_current_nic_info (){

	if ( (void *) currentNIC ==  NULL )
	{
		printf("show_current_nic_info: struct fail\n");
	    return;	
	}else{
		
		if ( currentNIC->used != 1 || currentNIC->magic != 1234 )
		{
		    printf("show_current_nic_info: validation fail\n");
	        return;				
		}
		
		if ( (void *) currentNIC->pci == NULL )
		{
		    printf("show_current_nic_info: pci struct fail\n");
	        return;				
		}

        //messages  		
		printf("NIC device info:\n");
		printf("Vendor %x Device %x \n", 
		    currentNIC->pci->Vendor, currentNIC->pci->Device );
		
		//...
		
	};	    
	
};

/*
int nicInit()
{};
*/

//
// End.
//


