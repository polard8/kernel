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
int init_network (){
	
	//...
	
//done:	

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

/*
int nicInit()
{};
*/

//
// End.
//


