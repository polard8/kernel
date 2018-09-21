/*
 * File: nic.h
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
 * 8086/100e network controller encontrado na oracle virtual box.
 *
 * Versão 1.0, 2016.
 */

/*
VirtualBox (3.1 is all I can personally confirm) supports rather dodgy 
implementations of an Intel PRO/1000 MT Server (82545EM), Intel PRO/1000 MT Desktop (82540EM), and Intel PRO/1000 T Server (82543GC).
Bugs:
The EERD register is unimplemented (you *must* use the 4-wire access method 
if you want to read from the EEPROM). [01000101 - I had a patch committed to fix this. It will soon be mainstream]
VMWare Virtual Server 2 emulates/virtualizes an 82545EM-based card rather well.
QEMU (since 0.10.0) supports an 82540EM-based card and it seems to work OK. It is the default network card since 0.11.0.
Bugs:
QEMU does not properly handle the software reset operation (CTRL.RST) in builds prior to June 2009.
*/
 
//NIC 82540EM Intel PRO/1000 MT   8086 100e

typedef struct nic_info_d nic_info_t; 
struct nic_info_d
{
	object_type_t objectType;
	object_class_t objectClass;
	
	//validação da estrutura.
	//se as flags estiverem acionadas, devemos
	//procurar as informações na estrutura de dispositivo pci.
	
	int used;
	int magic;
	
	//pci device.
    struct pci_device_d *pci;	
	
	//salvando o endereço base.
	unsigned long registers_base_address;
	
	unsigned long DeviceControl;
	
	unsigned long DeviceStatus;
	
	unsigned char mac0;
	unsigned char mac1;
	unsigned char mac2;
	unsigned char mac3;
	unsigned char mac4;
	unsigned char mac5;
	
	//unsigned char bus;
	//unsigned char dev;
	//unsigned char fun;	
	
	
	//unsigned short vendor;
	//unsigned short device;

	// rede.
	//struct network_info_d *network;
	
	//struct device_d     *device;

    //struct nic_info_d *next;	
};
struct nic_info_d *currentNIC;
//...

//nic_info_t *NicControllerHook;
//...
 
//lista de placas de rede.
//#todo: o valor máximo precisa ser definido. 
unsigned long nicList[8]; 
 
int init_nic();

//testando controlador ... 
//encontrando o controlador e identificando vendor e device.
void nic_test1();

void show_current_nic_info ();

void nic_i8254x_transmit();

void nic_i8254x_reset();

//
// End.
//

