/*
 * File: pci/pci.c
 *
 *     PCI interface.
 *     ring0.
 *
 * History:
 *     2013 - Created by Fred Nora.
 */


// See:
// ./dn_pci.txt


#include <kernel.h>


//
// Definições internas.
//

 

//
// BAR Support.
//

//Primeiro bit do BAR. (bit 0)
//Indica se o BAR é endereço de memória ou número de porta.
#define PCI_BAR_MEMORY_SPACE_INDICATOR 0
#define PCI_BAR_IO_INDICATOR 1

//Bits (1 e 2) do BAR.
//Indica se o endereço de memória é de 32bit ou 64bit.
#define PCI_BAR_32BIT_INDICATOR 0   //00b
//#define PCI_BAR_X_INDICATOR    1  //01b (Usado na revisão 3.0)
#define PCI_BAR_64BIT_INDICATOR 2   //10b
//#define PCI_BAR_XXX_INDICATOR 3   //11b (Indefinido)



// #Obs: 
// ?? O dispositivo cria BAR para i/o e para memória ?? 
// ?? O driver tem a opção de escolher o método. ??


// (BDF) or (B/D/F) bus/device/function:
// ====================================
//
// * eight-bit PCI bus, 
// * five-bit device, and 
// * three-bit function numbers for the device
//
// 1111,1111, | 1111,1 | 111.
//
//
// type 0:  [31-11]                          [function 10-8][7-2][1][0]
// type 1:  [31-24] [bus 23-16][device 15-11][function 10-8][7-2][1][0]



/*
 * #Testing macros.

//#define PCIADDRESS(bus, dev, func) ((1 << 31) | (bus << 16) | (dev << 11) | (func << 8))
//#define PCIADDRESS(bus, dev, func) ((1 << 31) | (bus << 16) | (dev << 11) | (func << PCI_MAX_FUNCTIONS))
 
#define PCI_ADDRESS(bus, deviceNum, funcNum, offset) \
                                     ((1 << 31) |                 \
                                     ((bus & 0xff) << 16) |       \
                                     ((deviceNum & 0x1f) << 11) | \
                                     ((funcNum & 0x7) << 8) |     \
                                     ((offset & 0x3f) << 2))
*/



//
// Defines.
//


//...


//
// Variáveis internas.
//

int pci_supported;
int pciListOffset;
//int pciStatus;
//int pciError;
//...



//========================================
// pci_classes2:
//    Estrutura com string para classes de dispositivos pci.
//    Created by Nelson Cole.
//========================================

const char *pci_classes2[] = {
    "Unclassified",
    "Mass Storage Controller",
    "Network Controller",
    "Display Controller",
    "Multimedia Controller",
    "Memory Controller",
    "Bridge device",
    "Simple Communication Controller",
    "Base System Peripheral",
    "Input Device Controller",
    "Docking Station",
    "Processor",
    "Serial Bus Controller",
    "Wireless Controller",
    "Intelligent I/O Controllers",
    "Satellite Communication Controller",
    "Encryption Controller",
    "Signal Processing Controller",
    "Processing Accelerator",
    "Non-Essential Instrumentation",
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,    // [0x40 - 0x14]="(Reserved)",
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,
    "Co-Processor",
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,    // [0xFE - 0x41]="(Reserved)",
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    "Unassigned Class (Vendor specific)",
};


/*
Class Code: 
A read-only register that specifies the type of function the device performs.

Subclass: 
A read-only register that specifies the specific function the device performs.

Prog IF: 
A read-only register that specifies a register-level programming interface 
the device has, if it has any at all.

The upper byte (at offset 0Bh) is a base class code which broadly classifies 
the type of function the device performs
The middle byte (at offset 0Ah) is a sub-class code which identifies more 
specifically the function of the device
The lower byte (at offset 09h) identifies a specific register-level programming 
interface (if any) so that device independent software can interact with the device
*/


/*
 ********************************
 * pci_classnames_t
 *     Estrutura para gerenciamento de classes.
 *     0, 'Class code' 'Subclass' 'Prog IF', e string.
 *     Credits: Nelson Cole.
 */

typedef struct {

    //0, 'Class code' 'Subclass' 'Prog IF',
    uint32_t classcode; 

    char *name;

}pci_classnames_t;


// PCI Express, compatibility to PCI local Bus 3.0 
// Credits: Nelson Cole.
 
pci_classnames_t pci_classnames [256] = {
    { 0x000000,  "Non-VGA-Compatible devices"		},
    { 0x000100,  "VGA-Compatible Device"			},
    { 0x010000,  "SCSI bus controller" 				},
    { 0x010100,  "IDE controller (ISA Compatibility mode-only controller)"			},
    { 0x010105,  "IDE controller (PCI native mode-only controller)"					},
    { 0x01010A,  "IDE controller (ISA Compatibility mode controller, \
supports both channels switched to PCI native mode)"								},
    { 0x01010F,  "IDE controller (PCI native mode controller, \
supports both channels switched to ISA compatibility mode)"							},
    { 0x010180,  "IDE controller (ISA Compatibility mode-only controller, supports bus mastering)"	},
    { 0x010185,  "IDE controller (PCI native mode-only controller, supports bus mastering )"		},
    { 0x01018A,  "IDE controller (ISA Compatibility mode controller, \
supports both channels switched to PCI native mode, supports bus mastering )"						},
    { 0x01018F,  "IDE controller (PCI native mode controller, \
supports both channels switched to ISA compatibility mode, supports bus mastering )"				},
    { 0x010200,  "Floppy disk controller"								},
    { 0x010300,  "IPI bus controller"									},
    { 0x010400,  "RAID bus controller"									},
    { 0x010520,  "ATA Controller (Single DMA)"							},
    { 0x010530,  "ATA Controller (Chained DMA)"							},
    { 0x010600,  "Serial ATA controller (vendor specific interface)"	},
    { 0x010601,  "Serial ATA controller (AHCI 1.0 interface)"			},
    { 0x010602,  "Serial ATA controller (Serial Storage Bus)"			},
    { 0x010700,  "Serial Attached SCSI (SAS)"							},
    { 0x010701,  "Serial Attached SCSI (Serial Storage Bus)"			},
    { 0x010801,  "Non-Volatile Memory Controlle (NVMHCI)"				},
    { 0x010802,  "Non-Volatile Memory Controlle (NVM Express)"			},
    { 0x018000,  "Other mass storage controller"						},
    { 0x020000,  "Ethernet controller"									},
    { 0x020100,  "Token ring controller"								},
    { 0x020200,  "FDDI controller"										},
    { 0x020300,  "ATM controller"										},
    { 0x020400,  "ISDN controller"										},
    { 0x020500,  "WorldFip Controller"									},
    { 0x020600,  "PICMG 2.14 Multi Computing"							},
    { 0x020700,  "Infiniband Controller"								},
    { 0x020800,  "Fabric Controller"									},
    { 0x028000,  "Other Network controller"								},
    { 0x030000,  "VGA Compatible controller (VGA Controller)"					},
    { 0x030001,  "VGA Compatible controller (8514-Compatible Controller )"		},
    { 0x030100,  "XGA controller"												},
    { 0x030200,  "3D controller (Not VGA-Compatible)"							},
    { 0x038000,  "Other Display controller"										},
    { 0x040000,  "Multimedia video controller"									},
    { 0x040100,  "Multimedia audio controller"									},
    { 0x040200,  "Computer telephony device"									},
    { 0x040300,  "Audio Device (Intel High Definition Audio (HDA) Controller)"	},
    { 0x048000,  "Other Multimedia controller"									},
    { 0x050000,  "RAM controller"									},
    { 0x050100,  "FLASH controller"									},
    { 0x058000,  "Other Memory controller"							},
    { 0x060000,  "Host bridge"										},
    { 0x060100,  "ISA bridge"										},
    { 0x060200,  "EISA bridge"										},
    { 0x060300,  "MCA bridge"										},
    { 0x060400,  "PCI-to-PCI Bridge (Normal Decode)"				},
    { 0x060401,  "PCI-to-PCI Bridge (Subtractive Decode)"			},
    { 0x060500,  "PCMCIA bridge"									},
    { 0x060600,  "NuBus bridge"										},
    { 0x060700,  "CardBus bridge"									},
    { 0x060800,  "RACEway bridge (Transparent Mode)"				},
    { 0x060801,  "RACEway bridge (Endpoint Mode)"					},
    { 0x060940,  "PCI-to-PCI Bridge (Semi-Transparent, Primary bus towards host CPU)"		},
    { 0x060980,  "PCI-to-PCI Bridge (Semi-Transparent, Secondary bus towards host CPU)"		},
    { 0x060A00,  "InfiniBand to PCI host bridge"						},
    { 0x068000,  "Other Bridge"											},
    { 0x070000,  "Serial controller (8250-Compatible (Generic XT))"		},
    { 0x070001,  "Serial controller (16450-Compatible )"				},
    { 0x070002,  "Serial controller (16550-Compatible )"				},
    { 0x070003,  "Serial controller (16650-Compatible )"				},
    { 0x070004,  "Serial controller (16750-Compatible)"					},
    { 0x070005,  "Serial controller (16850-Compatible)"					},
    { 0x070006,  "Serial controller (16950-Compatible)"					},
    { 0x070100,  "Parallel Controller (Standard Parallel Port)"				},
    { 0x070101,  "Parallel Controller (Bi-Directional Parallel Port)"		},
    { 0x070102,  "Parallel Controller (ECP 1.X Compliant Parallel Port)"	},
    { 0x070103,  "Parallel Controller (IEEE 1284 Controller)"				},
    { 0x0701FE,  "Parallel Controller (IEEE 1284 Target Device)"			},
    { 0x070200,  "Multiport Serial Controller"								},
    { 0x070300,  "Modem (Generic Modem)"									},
    { 0x070301,  "Modem (Hayes 16450-Compatible Interface)"		},
    { 0x070302,  "Modem (Hayes 16550-Compatible Interface)"		},
    { 0x070303,  "Modem (Hayes 16650-Compatible Interface)"		},
    { 0x070304,  "Modem (Hayes 16750-Compatible Interface)"		},
    { 0x070400,  "GPIB (IEEE 488.1/2) Controller"				},
    { 0x070500,  "Smart Card"									},
    { 0x078000,  "Other Simple Communication controller"		},
    { 0x080000,  "PIC (Generic 8259-Compatible)"				},
    { 0x080001,  "PIC (ISA-Compatible)"							},
    { 0x080002,  "PIC (EISA-Compatible)"						},
    { 0x080010,  "PIC (I/O APIC Interrupt Controller)"			},
    { 0x080020,  "PIC (I/O(x) APIC Interrupt Controller)"		},
    { 0x080100,  "DMA controller (Generic 8237-Compatible)"		},
    { 0x080101,  "DMA controller (ISA-Compatible)"				},
    { 0x080102,  "DMA controller (EISA-Compatible)"				},
    { 0x080200,  "Timer (Generic 8254-Compatible)"				},
    { 0x080201,  "Timer (ISA-Compatible)"						},
    { 0x080202,  "Timer (EISA-Compatible)"						},
    { 0x080203,  "Timer (HPET)"									},
    { 0x080300,  "RTC (Generic RTC)"							},
    { 0x080301,  "RTC (ISA-Compatible)"							},
    { 0x080400,  "PCI Hot-plug controller"						},
    { 0x080500,  "SD Host controller"							},
    { 0x080600,  "IOMMU"										},
    { 0x088000,  "Other System peripheral controller"			},
    { 0x090000,  "Keyboard controller"							},
    { 0x090100,  "Digitizer Pen"								},
    { 0x090200,  "Mouse controller"								},
    { 0x090300,  "Scanner controller"							},
    { 0x090400,  "Gameport controller (Generic)"				},
    { 0x090401,  "Gameport controller (Extended)"				},
    { 0x098000,  "Other input controller"						},
    { 0x0A0000,  "Generic Docking Station"						},
    { 0x0A8000,  "Other type of docking station"				},
    { 0x0B0000,  "386"											},
    { 0x0B0100,  "486"											},
    { 0x0B0200,  "Pentium"										},
    { 0x0B1000,  "Alpha"										},
    { 0x0B2000,  "Power PC"										},
    { 0x0B3000,  "MIPS"											},
    { 0x0B4000,  "Co-processor"									},
    { 0x0C0000,  "FireWire (IEEE 1394) controller (Generic)"	},
    { 0x0C0010,  "FireWire (IEEE 1394) controller (OHCI)"		},
    { 0x0C0100,  "ACCESS Bus"									},
    { 0x0C0200,  "SSA"											},
    { 0x0C0300,  "USB (UHCI Controller)"						},
    { 0x0C0310,  "USB1.1 (OHCI Controller)"						},
    { 0x0C0320,  "USB2.0 (EHCI Controller)"						},
    { 0x0C0330,  "USB3.0 (XHCI Controller)"						},
    { 0x0C0380,  "USB Controller (Unspecified )"				},
    { 0x0C03FE,  "USB Device (Not a host controller)"			},
    { 0x0C0400,  "Fiber Channel"								},
    { 0x0C0500,  "SMBus"										},
    { 0x0C0600,  "InfiniBand"									},
    { 0x0C0700,  "IPMI Interface (SMIC)"						},
    { 0x0C0701,  "IPMI Interface (Keyboard Controller Style)"	},
    { 0x0C0702,  "IPMI Interface (Block Transfer)"				},
    { 0x0C0800,  "SERCOS Interface (IEC 61491"					},
    { 0x0C0900,  "CANbus"										},
    { 0x0D0000,  "iRDA controller"								},
    { 0x0D0100,  "Consumer IR controller"						},
    { 0x0D1000,  "RF controller"								},
    { 0x0D1100,  "Bluetooth Controller"							},
    { 0x0D1200,  "Broadband Controller"							},
    { 0x0D2000,  "Ethernet Controller (802.1a ? 5 GHz)"			},
    { 0x0D2100,  "Ethernet Controller (802.1b 2.4 GHz)"			},
    { 0x0D8000,  "Other type of wireless controller"			},
    { 0x0E0000,  "I2O"											},
    { 0x0F0000,  "Satellite TV controller"						},
    { 0x0F0100,  "Satellite audio controller"					},
    { 0x0F0300,  "Satellite voice controller"					},
    { 0x0F0400,  "Satellite data  controller"					},
    { 0x100000,  "Network and Computing Encrpytion/Decryption"	},
    { 0x101000,  "Entertainment Encryption/Decryption"			},
    { 0x108000,  "Other Encryption/Decryption"					},
    { 0x110000,  "DPIO module"									},
    { 0x110100,  "Performance counters"							},
    { 0x111000,  "Communication synchronizer"					},
    { 0x112000,  "Signal Processing Management"					},
    { 0x118000,  "Other Signal Processing Controller"			},
    { 0x000000,  "Null"	}
};


//========================================
// end - estrutura do Nelson
//========================================



//
// SubClass strings.
//


//
// Strings para a subclass mass storage controllers.
//

//
// #bugbug Cuidado. Incluindo isso, o kernel base aparentemente 
// fica grande e não funciona. Alguma coisa de área de dados.
//



//1 mass storage
//Obs: Parece que outra forma de lista é mais apropriado.

static const char *mass_storage_subclass_strings[] = {

    "SCSI Bus Controller",         // 0x00
    "IDE Controller",              // 0x01
    "Floppy Disk Controller",      // 0x02 
    "IPI Bus Controller",          // 0x03
    "RAID Controller",             // 0x04
    "ATA Controller",              // 0x05 (ATA controller with ADMA interface)
    "Serial ATA",                  // 0x06 (Serial ATA controller)
    "Serial Attached SCSI (SAS)",  // 0x07 (Serial Attached SCSI (SAS) controller)
    0
    //0x08 (Non-volatile memory subsystem)
    //0x09 (Universal Flash Storage (UFS) controller)
    //0x80 Other Mass Storage Controller
};


/*
//2 network
static const char* networkcard_subclass_strings[] = {
    "Ethernet controller",  //0
    "Token ring",  //1
    "FDDI controller",  //2
    "ATM controller",  //3
    0
};
*/


/*
//3 display controllers
static const char* displaycontrollers_subclass_strings[] = {
    "",  //0
    "XGA controller",  //1
    "",  //2
    "",  //3
	0
};
*/


/*
//4 multimedia
static const char* multimedia_subclass_strings[] = {
    "Video device",  //0
    "Audio device",  //1
    "",  //2
    "",  //3
	0
};
*/


/*
//5 memory controllers
static const char* memorycontrollers_subclass_strings[] = {
    "RAM controller",  //0
    "Flash memory controller",  //1
    "",  //2
    "",  //3
	0
};
*/


//6 bridge
static const char* bridge_subclass_strings[] = {
    "Host/PCI bridge",           //0
    "PCI/ISA bridge",            //1
    "PCI/EISA bridge",           //2
    "PCI/Micro Channel bridge",  //3
    "PCI/PCI bridge",            //4
    "PCI/PCMCIA bridge",         //5
    "PCI/NuBus bridge",          //6
    "PCI/CardBus bridge",        //7
    0 
};


/*
//7 Simple Communications Controllers
static const char* scc_subclass_strings[] = {
    "",  //0
    "",  //1
    "",  //2
    "",  //3
	0
};
*/


/*
// 8 Base System Peripherals
static const char* bsp_subclass_strings[] = {
    "",  //0
    "",  //1
    "",  //2
    "",  //3
	0
};
*/


/*
// 9 Input Devices
static const char* inputdevices_subclass_strings[] = {
    "Keyboard controller",  //0
    "Digitizer (pen)",  //1
    "Mouse controller",  //2
    "",  //3
	0
};
*/


/*
// A Docking Stations
static const char* dockingstations_subclass_strings[] = {
    "Generic docking station",  //0
    "",  //1
	0
};
*/


/*
// B Processors
static const char* processors_subclass_strings[] = {
    "386",      //0
    "486",      //1
    "Pentium",  //2
    "",         //3
	0
};
*/


/*
// C Serial Bus Controllers
static const char* sbc_subclass_strings[] = {
    "Firewire (IEEE 1394)",               //0
    "ACCESS bus",                         //1
    "SSA (Serial Storage Architecture)",  //2
    "USB (Universal Serial Bus)",         //3
	0
};
*/


//
// Funções internas.
//

 

//...


//
// Obs: 
//     Os dispositivos podem compartilhar a mesma interrupção no PIC/APIC. 
// Então para uma IRQ destinada à PCI terá que identificar qual dispositivo 
// gerou a interrupção, para chamar a rotina apropriada.
//


/*
 *****************************************
 * irq_SHARED0: 
 * 
 *     **** PCI HANDLER ****
 *
 *     Todas as interrupções geradas pelos dispositivos PCI
 * usarão o mesmo isr (handler). 
 *     Caberá à rotina do handler identificar qual dispositivo 
 * sinalizou que efetuou uma interrupção. Então direcionar 
 * para a rotina de serviço aproriada.
 */

void irq_SHARED0 (void)
{
    debug_print ("irq_SHARED0:\n");
    //...
    return;
}


/*
 * irq_SHARED1: 
 * 
 *     **** PCI HANDLER ****
 *
 *     **** PCI HANDLER ****
 *
 *     Todas as interrupções geradas pelos dispositivos PCI
 * usarão o mesmo isr (handler). 
 *     Caberá à rotina do handler identificar qual dispositivo 
 * sinalizou que efetuou uma interrupção. Então direcionar 
 * para a rotina de serviço aproriada.
 */

void irq_SHARED1 (void)
{
    debug_print ("irq_SHARED1:\n");
    //...
    return;
}


/*
 * irq_SHARED2: 
 * 
 *     **** PCI HANDLER ****
 *
 *     **** PCI HANDLER ****
 *
 *     Todas as interrupções geradas pelos dispositivos PCI
 * usarão o mesmo isr (handler). 
 *     Caberá à rotina do handler identificar qual dispositivo 
 * sinalizou que efetuou uma interrupção. Então direcionar 
 * para a rotina de serviço aproriada.
 */
void irq_SHARED2 (void)
{
    debug_print ("irq_SHARED2:\n");
    //...
    return;
}


/*
 * irq_SHARED3: 
 * 
 *     **** PCI HANDLER ****
 *
 *     **** PCI HANDLER ****
 *
 *     Todas as interrupções geradas pelos dispositivos PCI
 * usarão o mesmo isr (handler). 
 *     Caberá à rotina do handler identificar qual dispositivo 
 * sinalizou que efetuou uma interrupção. Então direcionar 
 * para a rotina de serviço aproriada.
 */

void irq_SHARED3 (void)
{
    debug_print ("irq_SHARED3:\n");
	//...
    return;
}


/**
   Exemplo:
   
   ** sanOS ** 
   
   @todo: read/write.
   
static __inline unsigned char pci_read_byte(int busno, int devno, int funcno, int addr) {
  outpd(PCI_CONFIG_ADDR, ((unsigned long) 0x80000000 | (busno << 16) | (devno << 11) | (funcno << 8) | addr));
  return inp(PCI_CONFIG_DATA);
}

static __inline unsigned short pci_read_word(int busno, int devno, int funcno, int addr) {
  outpd(PCI_CONFIG_ADDR, ((unsigned long) 0x80000000 | (busno << 16) | (devno << 11) | (funcno << 8) | addr));
  return inpw(PCI_CONFIG_DATA);
}

static __inline unsigned long pci_read_dword(int busno, int devno, int funcno, int addr) {
  outpd(PCI_CONFIG_ADDR, ((unsigned long) 0x80000000 | (busno << 16) | (devno << 11) | (funcno << 8) | addr));
  return inpd(PCI_CONFIG_DATA);
}

static __inline void pci_write_byte(int busno, int devno, int funcno, int addr, unsigned char value) {
  outpd(PCI_CONFIG_ADDR, ((unsigned long) 0x80000000 | (busno << 16) | (devno << 11) | (funcno << 8) | addr));
  outp(PCI_CONFIG_DATA, value);
}

static __inline void pci_write_word(int busno, int devno, int funcno, int addr, unsigned short value) {
  outpd(PCI_CONFIG_ADDR, ((unsigned long) 0x80000000 | (busno << 16) | (devno << 11) | (funcno << 8) | addr));
  outpw(PCI_CONFIG_DATA, value);
}

static __inline void pci_write_dword(int busno, int devno, int funcno, int addr, unsigned long value) {
  outpd(PCI_CONFIG_ADDR, ((unsigned long) 0x80000000 | (busno << 16) | (devno << 11) | (funcno << 8) | addr));
  outpd(PCI_CONFIG_DATA, value);
}

**/


/*
 ********************************************************
 * pciConfigReadByte:
 *     Read com retorno do tipo unsigned char.
 */

unsigned char 
pciConfigReadByte ( 
    unsigned char bus, 
    unsigned char slot, 
    unsigned char func, 
    unsigned char offset )
{

	// Montando uma unsigned long.
	// Bus, Device and Function.

    unsigned long lbus  = (unsigned long) bus; 
    unsigned long lslot = (unsigned long) slot; 
    unsigned long lfunc = (unsigned long) func; 

	//O endereço a ser montado e enviado para porta 0xCF8.
    unsigned long address;   

	//Retorno armazenado na porta de status.
    unsigned char Ret = 0;             


	// #todo: 
	// Filtros de tamanho máximo.

	// Create configuration address.
    address = (unsigned long) ((lbus << 16) | (lslot << 11) | (lfunc << 8) | (offset & 0xfc) | ((unsigned long)0x80000000));

	// sendComand:
	// Write out the address. (0x0CF8).

    out32 (PCI_ADDRESS_PORT, address);
    io_delay();

	// getData:
	// Read in the data port. (0x0CFC).
	// Talves possamos usar um input do tipo char, que é assim
	// inline unsigned char inportb(int port)  
    // int inport8(int port) 

    Ret = (unsigned char) (( in32(PCI_DATA_PORT) >> ((offset & 3) * 8)) & 0xff); 
    io_delay();
    
    
    // Obs: 
    // (offset & 2) * 8) = 0 Will choose the first word of the 32 bits register.    


    return (unsigned char) Ret; 
}


/*
 *******************************
 * pciConfigReadWord:
 *    Read com retorno do tipo unsigned short.
 *    Envia o comando (32bit) para a porta 0xCF8, e retorna o status (16bit) 
 * armazenado na porta 0xCFC.
 * 
 * Argumentos:
 *    bus    = Número do BUS.           total 256.
 *    slot   = Número do slot. (device) total 32.
 *    func   = Número da função.        total 8. 
 *    offset = Offset.
 *
 *  Ex: 0x80000000 | bus << 16 | device << 11 | function <<  8 | offset.
 *
 *  1111,1111, | 1111,1 | 111.
 *
 * @todo: 
 *     Essa função retorna short. Criar funções equivalentes para retornar 
 * char e unsigned long.
 *
 * @todo: 
 *     Criar a função equivalente oposta, para escrever. pciConfigWriteWord(...)
 * para podermos configurar o BAR.
 *
 */

unsigned short 
pciConfigReadWord ( 
    unsigned char bus, 
    unsigned char slot, 
    unsigned char func, 
    unsigned char offset )
{

	// Montando uma unsigned long.
	// Bus, Device and Function.

    unsigned long lbus  = (unsigned long) bus; 
    unsigned long lslot = (unsigned long) slot; 
    unsigned long lfunc = (unsigned long) func; 

	// O endereço a ser montado e enviado para porta 0xCF8.
    unsigned long address;   

	// Retorno armazenado na porta de status.
    unsigned short Ret = 0;             

	// #todo: 
	// Filtros de tamanho máximo.

	// Create configuration address.
    address = (unsigned long) ((lbus << 16) | (lslot << 11) | (lfunc << 8) | (offset & 0xfc) | ((unsigned long)0x80000000));


	// sendComand:
	// Write out the address. (0x0CF8).

    out32 (PCI_ADDRESS_PORT, address);
    io_delay();

	// getData:
	// Read in the data port. (0x0CFC).
	// Apesar do inpot pegar uma longo o retornno é short.
	// @todo: Talvez possamos usar um input do tipo short.
	// que é assim int inport16(int port)

    Ret = (unsigned short) (( in32(PCI_DATA_PORT) >> ((offset & 2) * 8)) & 0xffff);
	//Ret = (unsigned short)(  inport16(PCI_DATA_PORT) );
    io_delay();

    // Obs: 
    // (offset & 2) * 8) = 0 Will choose the first word of the 32 bits register.   

    return (unsigned short) Ret; 
}


/* 
 *****************************
 * pciConfigReadDWord:
 *     Read com retorno do tipo unsigned long. 
 */

unsigned long 
pciConfigReadDWord ( 
    unsigned char bus, 
    unsigned char slot, 
    unsigned char func, 
    unsigned char offset )
{

	// Montando uma unsigned long.
	// Bus, Device and Function.

    unsigned long lbus  = (unsigned long) bus; 
    unsigned long lslot = (unsigned long) slot; 
    unsigned long lfunc = (unsigned long) func; 

	//O endereço a ser montado e enviado para porta 0xCF8.
    unsigned long address;   

	//Retorno armazenado na porta de status.
    unsigned long Ret = 0;
 
 
	// #todo: 
	// Filtros de tamanho máximo.

	// Create configuration address.
    address = (unsigned long) ((lbus << 16) | (lslot << 11) | (lfunc << 8) | (offset & 0xfc) | ((unsigned long)0x80000000));


	// sendComand:
	// Write out the address. (0x0CF8).

    out32 (PCI_ADDRESS_PORT, address);
    io_delay();

	// getData:
	// Read in the data port. (0x0CFC).

	// Parece ser o certo.
	Ret = (unsigned long) ( in32(PCI_DATA_PORT) ); 
    io_delay();
    
    // Obs: 
    // (offset & 2) * 8) = 0 Will choose the first word of the 32 bits register.

    return (unsigned long) Ret; 
}


/*
 ************************************************
 * pciCheckVendor:
 *     Check vendor, offset 0. 
 */

// #todo: 
// Nesse momento não há nenhume busca por fuction.
// Vendor.

unsigned short 
pciCheckVendor (unsigned char bus, unsigned char slot)
{
    return (unsigned short) pciConfigReadWord ( bus, slot, 0, 
                                PCI_OFFSET_VENDORID );  
}


/*
 *****************************************
 * pciCheckDevice:
 *     Check device, offset 2. 
 */

// #todo: 
// Nesse momento não há nenhume busca por fuction. 
// Device.

unsigned short 
pciCheckDevice (unsigned char bus, unsigned char slot)
{
    return (unsigned short) pciConfigReadWord ( bus, slot, 0, 
                                PCI_OFFSET_DEVICEID ); 
}


/*
 * pciGetClassCode:
 *     Get class code, offset 0x0B.  
 */

// #todo: 
// Nesse momento não há nenhume busca por fuction.

unsigned char 
pciGetClassCode (unsigned char bus, unsigned char slot)
{
    return (unsigned char) pciConfigReadByte ( bus, slot, 0, 
                               PCI_OFFSET_CLASSCODE );
}


/*
 *****************************************
 * pciGetSubClass:
 *     Get subclass code. Offset 0x0A.
 */

	// #todo: 
	// Nesse momento não há nenhume busca por fuction.

unsigned char 
pciGetSubClass (unsigned char bus, unsigned char slot)
{
    return (unsigned char) pciConfigReadByte ( bus, slot, 0, 
                               PCI_OFFSET_SUBCLASS );
}


/*
 **********************************
 * pciGetHeaderType:
 * 
 */

// #todo: 
// Nesse momento não há nenhuma busca por fuction.

unsigned char 
pciGetHeaderType (unsigned char bus, unsigned char slot)
{
    return (unsigned char) pciConfigReadByte ( bus, slot, 0, 
                               PCI_OFFSET_HEADERTYPE );
}


/*
 ***********************************************************
 * pciGetBAR:
 *     Get BAR.
 *
 * Offsets:
 * #define PCI_OFFSET_BASEADDRESS0   0x10
 * #define PCI_OFFSET_BASEADDRESS1   0x14
 * #define PCI_OFFSET_BASEADDRESS2   0x18
 * #define PCI_OFFSET_BASEADDRESS3   0x1C
 * #define PCI_OFFSET_BASEADDRESS4   0x20
 * #define PCI_OFFSET_BASEADDRESS5   0x24
 *
 * Obs: 
 * @todo: 
 *     Talvez o retorno não pegue uma unsigned long como desejado e sim 
 * apenas uma unsigned short ou ainda retorne um unsigned long com uma 
 * parte suja.
 *
 * Obs: O argumento 'number' é o número do BAR.
 *
 * Primeiro devemos salvar o valor encontrado na BAR, o valor do BAR
 * servirá para identificarmos um endereço de memória ou número de
 * porta de i/o. Os bits do bar dirão se o endereço de memória é
 * de 32bit ou 64bit.
 *
 * Depois para sabermos a quantidade de memória que um dispositivo irá precisar
 * devemos colocar tudo 1 na BAR, pegar o valor da bar e efetuar um NOT (~) each
 * incrementar em 1, 
 *
 * Depois disso tudo podemos restaurar o valor da BAR que foi salvo.
 *
 * Obs: Nessa rotina apenas pegamos o valor da bar.
 */

unsigned long 
pciGetBAR ( 
    unsigned char bus, 
    unsigned char slot, 
    int number )
{

    unsigned long BAR = 0;

	// #todo: 
	// Filtros para argumentos.

    if ( number <0 || number > 5 )
    {
        // ?? msg
        return 0;
    }


    switch (number){

        case 0:
            BAR = (unsigned long) pciConfigReadDWord ( bus, 
                                      slot, 
                                      0, 
                                      PCI_OFFSET_BASEADDRESS0 );
            goto done;
            break;

        case 1:
            BAR = (unsigned long) pciConfigReadDWord ( bus, 
                                      slot, 
                                      0, 
                                      PCI_OFFSET_BASEADDRESS1 );
            goto done;
            break;

        case 2:
            BAR = (unsigned long) pciConfigReadDWord ( bus, 
                                      slot, 
                                      0, 
                                      PCI_OFFSET_BASEADDRESS2 );
            goto done;
            break;

        case 3:
            BAR = (unsigned long) pciConfigReadDWord ( bus, 
                                      slot, 
                                      0, 
                                      PCI_OFFSET_BASEADDRESS3 );
            goto done;
            break;

        case 4:
            BAR = (unsigned long) pciConfigReadDWord ( bus, 
                                      slot, 
                                      0, 
                                      PCI_OFFSET_BASEADDRESS4 );
            goto done;
            break;

        case 5:
            BAR = (unsigned long) pciConfigReadDWord( bus, 
                                      slot, 
                                      0, 
                                      PCI_OFFSET_BASEADDRESS5 );
            goto done;
            break;


        default:
            // ??
            return 0;
            break;
    };

	// Nothing.

done:
    return (unsigned long) BAR;
}



//
// Continua ...
//


/*
 *******************************************
 * pciGetInterruptLine:
 *     Get Interrupt Line, offset 0x3C.
 *     (Read an write register).
 */

unsigned char 
pciGetInterruptLine ( 
    unsigned char bus, 
    unsigned char slot )
{
    return (unsigned char) pciConfigReadByte ( bus, slot, 0, 
                               PCI_OFFSET_INTERRUPTLINE );
}



/*
 *************************************
 * pciGetInterruptPin:
 *     Get interrupt pin offser 3d (Read only).
 */

unsigned char 
pciGetInterruptPin ( 
    unsigned char bus, 
    unsigned char slot )
{
    return (unsigned char) pciConfigReadByte ( bus, slot, 0, 
                              PCI_OFFSET_INTERRUPTPIN );
}


//
// Continua ...
//


/*
 ********************************
 * pciHandleDevice
 *    Registra um dispositivo encontrado na sondagem. 
 *    Inicializa em alguns casos.
 */

// Called by pci_setup_devices() in pciscan.c

int 
pciHandleDevice ( 
    unsigned char bus, 
    unsigned char dev, 
    unsigned char fun )
{ 
    // Device.
    struct pci_device_d *D;    

    uint32_t data=0;

    int Status = -1;
    
    // char, block, network
    int __class=0;
    
    // name support.
    char __tmpname[64];
    char *newname;


	//#debug
	//printf ("bus=%d dev=%d fun=%d \n", bus, dev, fun);

    //
    // PCI device
    //


    D = (void *) kmalloc ( sizeof( struct pci_device_d  ) );

    if ( (void *) D == NULL ){
        panic ("pciHandleDevice: D");

    }else{
        D->objectType  = ObjectTypePciDevice;
        D->objectClass = ObjectClassKernelObjects;
        D->used  = (int) 1;
        D->magic = (int) 1234;

        D->id = (int) pciListOffset;

        // Localização.
        D->bus  = (unsigned char) bus;
        D->dev  = (unsigned char) dev;
        D->func = (unsigned char) fun; 

        // PCI Header.
        D->Vendor = (unsigned short) pciCheckVendor (bus,dev);
        D->Device = (unsigned short) pciCheckDevice (bus,dev);

        D->name = "pci-device-no-name";


		// #debug
		// printf ("$ vendor=%x device=%x \n",D->Vendor, D->Device);

        //OK, it is working
        data = (uint32_t) diskReadPCIConfigAddr ( bus, dev, fun, 8 );
        D->classCode = data >> 24 & 0xff;
        D->subclass  = data >> 16 & 0xff;

		//#bugbug: Isso falhou. Deletar isso e trabalhar essas funções.
		//D->classCode = (unsigned char) pciGetClassCode(bus, dev);
		//D->subclass = (unsigned char) pciGetSubClass(bus, dev); 

        D->irq_line = (unsigned char) pciGetInterruptLine (bus,dev);
        D->irq_pin  = (unsigned char) pciGetInterruptPin (bus,dev);

        // Next device.
        D->next = NULL; 

        // #debug
        // 07d1	D-Link System Inc
        // 101e	American Megatrends Inc.
        // 1028	Dell
        // 1022	Advanced Micro Devices, Inc. [AMD]
        // 101c	Western Digital
        // 103c	Hewlett-Packard Company
        // 1043	ASUSTeK Computer Inc.
        // 104c	Texas Instruments
        // 1050	Winbond Electronics Corp
        // 1078	Cyrix Corporation
        // 108e	Oracle/SUN
        // 10de	NVIDIA Corporation
        // 1106	VIA Technologies, Inc.
        // 1412	VIA Technologies Inc.
        // 115f	Maxtor Corporation
        // 1186	D-Link System Inc
        // 11c3	NEC Corporation
        // 121a	3Dfx Interactive, Inc.
        // 10ec	Realtek Semiconductor Co., Ltd.
        // 0bda Realtek Semiconductor Corp. 
        // 807d	Asustek Computer, Inc.
        // 8c4a	Winbond
        // ...
        
        if ( (D->Vendor == 0xFFFF) ){
            debug_print ("pciHandleDevice: [BUGBUG] Illegal vendor\n");
        }

        // nvidia
        if ( (D->Vendor == 0x10DE) ){
            debug_print ("pciHandleDevice: [TODO] nvidia device found\n");
        }

        // VIA
        if ( (D->Vendor == 0x1106 || D->Vendor == 0x1412) ){
            debug_print ("pciHandleDevice: [TODO] VIA device found\n");
        }

        // realtek
        if ( (D->Vendor == 0x10EC || D->Vendor == 0x0BDA ) ){
            debug_print ("pciHandleDevice: [TODO] realtek device found\n");
        }

        // logitec
        if ( (D->Vendor == 0x046D) ){
            debug_print ("pciHandleDevice: [TODO] logitec device found\n");
        }

        // ...

        //
        // == NIC Intel. ===================
        //

        if ( (D->Vendor == 0x8086)  && 
             (D->Device == 0x100E ) && 
             (D->classCode == PCI_CLASSCODE_NETWORK) )
        {
            //serial debug
            debug_print ("0x8086:0x100E found \n"); 
            //printf("b=%d d=%d f=%d \n", D->bus, D->dev, D->func );
            //printf("82540EM Gigabit Ethernet Controller found\n");

            //See: network/nicintel.c

            Status = (int) e1000_init_nic ( 
                               (unsigned char) D->bus, 
                               (unsigned char) D->dev, 
                               (unsigned char) D->func, 
                               (struct pci_device_d *) D );


            if (Status == 0)
            {
                // # irq and reset.
                //printf("8086:100e initialized\n");

                e1000_setup_irq ();
                e1000_reset_controller ();
                
                //testNIC();
                printf ("pciHandleDevice: Unlocking interrupt handler \n");
                e1000_interrupt_flag = 1;

                //printf("8086:100e done\n");
                //printf("#debug breakpoint");
                //refresh_screen();
                //while(1){} 
                
                //network device,
                __class = 3;
 
            }else{
                panic ("pciHandleDevice: NIC Intel [0x8086:0x100E]");
            };
        };


        // 8086:1237
        // 440FX - 82441FX PMC [Natoma] - Intel Corporation
        //if ( (D->Vendor == 0x8086)  && 
             //(D->Device == 0x1237 ) && 
             //(D->classCode == PCI_CLASSCODE_BRIDGE) )
        //{}

        // 8086:7000
        // 82371SB PIIX3 ISA [Natoma/Triton II] - Intel Corporation
        //if ( (D->Vendor == 0x8086)  && 
             //(D->Device == 0x7000 ) && 
             //(D->classCode == PCI_CLASSCODE_BRIDGE) )
        //{}

         
        // serial controller.
        // desejamos a subclasse 3 que é usb. 
        if ( (D->Vendor == 0x8086)  && 
             (D->Device == 0x7000 ) && 
             (D->classCode == PCI_CLASSCODE_SERIALBUS ) )
        {
            //serial debug
            debug_print ("0x8086:0x7000 found \n");  

            // See: usb.c
            Status = (int) serial_bus_controller_init ( 
                               (unsigned char) D->bus, 
                               (unsigned char) D->dev, 
                               (unsigned char) D->func, 
                               (struct pci_device_d *) D );
                               
             if (Status == 0)
             {
                 // ...
             }else{
                 panic ("pciHandleDevice: Serial controller [0x8086:0x7000]\n");
             };
        }

        // #todo
        // Display controller on qemu.
        //if ( (D->Vendor == 0x1234)  && 
             //(D->Device == 0x1111 ) && 
             //(D->classCode == PCI_CLASSCODE_DISPLAY) )
        //{}


		//Colocar a estrutura na lista.

		// #todo: Limits
		// #bugbug: limite determinado ... 
		// precisa de variável.

        if ( pciListOffset < 0 || pciListOffset >= 32 )
        { 
            printf ("pciHandleDevice: [FAIL] No more slots!\n");
            return (int) (-1);
        }

        // Saving.
        pcideviceList[pciListOffset] = (unsigned long) D;
        pciListOffset++;

        // #debug
        //printf("$");
    };

    //
    // == Name ==============================================
    //
    
    // #bugbug
    // buffer overflow?
    
    // #test
    // isso não é o ponto de montagem.
    
    //buffer1.
    sprintf ( 
        (char *) &__tmpname[0], 
        "/DEV_%x_%x", 
        D->Vendor, 
        D->Device );

    //buffer2.
    newname = (char *) kmalloc (64);
    if ( (void*) newname == NULL )
    {
        panic("pciHandleDevice: newname");
    }
    strcpy (newname,__tmpname);

    //
    // == file ====================================
    //

    //
    // Agora registra o dispositivo pci na lista genérica
    // de dispositivos.
    // #importante: ele precisa de um arquivo 'file'.
    //
    
    file *__file;
    
    __file = (file *) kmalloc ( sizeof(file) );
    
    if ( (void *) __file == NULL ){
        panic ("pciHandleDevice: __file fail, can't register device");
    
    }else{
        __file->used = 1;
        __file->magic = 1234;
        __file->isDevice = 1;

        //
        // Register.
        //

        // #importante
        // Essa é a tabela de montagem de dispositivos.
        // O nome do dispositivo deve ser um pathname.
        // Mas podemos ter mais de um nome.
        // vamos criar uma string aqui usando sprint e depois duplicala.
     
        // IN:
        // file structure, device name, class (char,block,network).
        // type (pci, legacy), pci device structure, tty driver struct.
 
        devmgr_register_device ( 
            (file *) __file, 
            newname, 
            __class, 
            1, 
            (struct pci_device_d *) D,   // <<<< The PCI device.
            NULL );
    };

    return 0;
}


/*
 ***************************************
 * init_pci:
 *     Inicializa o módulo PCI em Kernel Mode, dentro do Kernel Base. 
 * 
 * @todo: 
 *     +Pega informações sobre PCI.
 *     +Pegar as informações e por em estrutura e registro.
 *
 *     Obs: Essa rotina está incompleta.
 */

int init_pci (void){

    //loop
    register int i=0;

    int Status = 0;
    int Max = 32;   //@todo.

    unsigned long data=0;


    debug_print ("init_pci:\n");

    // Is PCI supported ?
    
    out32 ( 0xCF8, 0x80000000 );
    io_delay();
    
    data = (unsigned long) in32 (0xCF8);
    io_delay();

 
	// #todo:
	// Fazer alguma coisa pra esse caso.
	// Talvez seja um 386 ou 486 sem suporte a PCI.
	// Talvez ISA.

    // STATUS_NOT_SUPPORTED
    // Can we live with no pci support. Maybe ISA.
    if ( data != 0x80000000 )
    {
        pci_supported = 0;
        panic ("init_pci: [FIXME] PCI NOT supported\n");
    }
    
    pci_supported = 1;
    //printf("PCI supported!");


	//#todo: 
	//Colocar esse status na estrutura platform->pci_supported.
	//Talvez assim: platform->platform_type.

	//#debug
	//refresh_screen();
	//while(1){}


	//==========


    // Initialise PCI device list.
    // Initialise the offset.

    for ( i=0; i<Max; ++i ){
        pcideviceList[i] = (unsigned long) 0;
    };

    pciListOffset = 0;


	// Encontrar os dispositivos PCI e salvar as informações sobre eles
	// em suas respectivas estruturas.

    Status = (int) pci_setup_devices();
    
    if (Status != 0){
        panic ("init_pci: pci_setup_devices fail.\n");
    }

    //...

    g_driver_pci_initialized = (int) 1; 

	//printf("Done\n");

    return (int) Status; 
}


//
// End.
//

