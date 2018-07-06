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
int init_network()
{
	
	//...
	
done:	
    return (int) 0;	
};


/*
int nicInit()
{};
*/

//
// End.
//


