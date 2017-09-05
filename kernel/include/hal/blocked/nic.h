/*
 * Arquivo: nic.h
 *
 * Descrição:
 *     Header para driver de adaptador de rede.
 *     network interface card (NIC)
 *  
 * Opções:
 * Oracle virtual box: // 1022, 2000  //Advanced Micro Devices, 
 * PCnet LANCE PCI Ethernet Controller.
 * ASUS H81: REALTEK, VENDOR 0x10EC; DEVICE 0x8168 
 *
 * Versão 1.0, 2016.
 */
 

/*
typedef struct nic_controller_d nic_controller_t; 
struct nic_controller_d
{
	object_type_t objectType;
	object_class_t objectClass;
	
	struct pci_device_d *pci;
	struct device_d     *device;	
} 
nic_controller_t *NicControllerHook;
//...
*/
 
int init_network();

//
//fim.
//

