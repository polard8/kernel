/*
 * File: dd/pci/pci.c
 * 
 * Descrição:
 *     Driver de PCI presente no kernel Base.
 *
 * Ambiente: 
 *     RING 0.
 *
 * History:
 *     2013 - Created by Fred Nora.
 *     2016 - Small changes.
 */
 
/*
 Wikipedia:
     
    One of the major improvements the PCI Local Bus had over other I/O 
architectures was its configuration mechanism. In addition to the 
normal memory-mapped and I/O port spaces, each device function 
on the bus has a configuration space, which is 256 bytes long, 
addressable by knowing the eight-bit PCI bus, five-bit device, and 
three-bit function numbers for the device (commonly referred to as the BDF or 
B/D/F, as abbreviated from bus/device/function). 
    This allows up to 256 buses, each with up to 32 devices, each supporting 
eight functions. A single PCI expansion card can respond as a device and 
must implement at least function number zero. 
    The first 64 bytes of configuration space are standardized, the remainder 
are available for vendor-defined purposes.
 
    The system's firmware, device drivers or the operating system program the 
Base Address Registers (commonly called BARs).
 
    Because all PCI devices are in an inactive state upon system reset, they 
will have no addresses assigned to them by which the operating system or 
device drivers can communicate with them. 

    The BIOS or operating system will program the memory-mapped and I/O port 
addresses into the device's BAR configuration register. These addresses stay 
valid as long as the system remains turned on.

    Each non-bridge PCI device function can implement up to 6 BARs, each of 
which can respond to different addresses in I/O port and memory-mapped 
address space. Each BAR describes a region.

    The value written to the 'Configuration Space Address I/O port' is created 
by combining B/D/F values and the registers address value into a 32-bit word.

    ** Methods **
	Configuration reads and writes can be initiated from the CPU in two ways: 
    One legacy method via I/O addresses 0xCF8 and 0xCFC, and another called 
	memory-mapped configuration.
	
    The legacy method was present in the original PCI, and it is called 
Configuration Access Mechanism (CAM). It allows for 256 bytes of a device's 
address space to be reached indirectly via two 32-bit registers called 
PCI CONFIG_ADDRESS and PCI CONFIG_DATA. These registers are at addresses 
0xCF8 and 0xCFC in the x86 I/O address space.

*/ 
  
  
/*
 http://wiki.osdev.org/PCI
 
 Base Address Registers:
     
	Base address Registers (or BARs) can be used to hold memory addresses used 
by the device, or offsets for port addresses. 
 
    Typically, memory address BARs need to be located in physical ram while 
I/O space BARs can reside at any memory address (even beyond physical memory). 
To distinguish between them, you can check the value of the lowest bit. 
 
;----
    
    The following tables describe the two types of BARs:

* Memory Space BAR Layout:
                  31 - 4	          3	         2 - 1	 0
16-Byte Aligned Base Address	|Prefetchable	|Type	|Always 0

* I/O Space BAR Layout:
                  31 - 2	    1	        0
4-Byte Aligned Base Address	| Reserved	| Always 1

;----

    The Type field of the Memory Space BAR Layout specifies the size of the 
base register and where in memory it can be mapped. 
* If it has a value of 0x00 then the base register is 32-bits wide and can be 
mapped anywhere in the 32-bit Memory Space. 
* A value of 0x02 means the base register is 64-bits wide 
and can be mapped anywhere in the 64-bit Memory Space (A 64-bit base address 
register consumes 2 of the base address registers available). 
* A value of 0x01 is reserved as of revision 3.0 of the PCI Local Bus 
Specification. 

    In earlier versions it was used to support memory space below 1MB (16-bit 
wide base register that can be mapped anywhere in the 16-bit Memory Space).

 *** 
 When you want to retrieve the actual base address of a BAR, be sure to mask 
 the lower bits. 
 ***
 
 ------
 Para encontrar o endereço de memória é só mascarar os valores de 16bit encontrados
na BAR dessa maneira:

 For 16-Bit Memory Space BARs, you calculate 
 (BAR[x] & 0xFFF0). 
 
 For 32-Bit Memory Space BARs, you calculate 
 (BAR[x] & 0xFFFFFFF0). 
 
 For 64-Bit Memory Space BARs, you calculate 
 ((BAR[x] & 0xFFFFFFF0) + ((BAR[x+1] & 0xFFFFFFFF) << 32)) 

 -------
 Para o número da porta de I/O, é só mascarar o BAR dessa maneira:
 
 For I/O Space BARs, you calculate (BAR[x] & 0xFFFFFFFC).

 * IMPORTANTE.
    Para determinar a quantidade de memória que um dispositivo irá precisar,
é só salvar o valor da BAR, colocar tudo 1 e ler de volta. A quantidade de 	
memória poderá ser vista mascarando os bits com um NOT (~) e incrementando
em 1. Depois disso podemos restaurar o valor original da BAR, que antes 
foi salvo.
	
    ----    
	To determine the amount of address space needed by a PCI device, you must 
save the original value of the BAR, write a value of all 1's to the register, 
then read it back. 
    The amount of memory can then be determined by masking the information 
bits, performing a bitwise NOT ('~' in C), and incrementing the value by 1. 

    The original value of the BAR should then be restored. 

    The BAR register is naturally aligned and as such you can only modify 
the bits that are set. For example, if a device utilizes 16 MB it will have BAR0 filled with 0xFF000000 
(0x01000000 after decoding) and you can only modify the upper 8-bits.

 */  
  
  
/*
 OSDEV.ORG

 Interrupt Line:

    *PIC:
	If you're using the old PIC, your life is really easy. You have the 
Interrupt Line field of the header, which is read/write (you can change 
it's value!) and it says which interrupt will the PCI device fire when 
it needs attention.
    
	*APIC:
    If you plan to use the I/O APIC, your life will be a nightmare. 
You have 4 new IRQs called INTA#, INTB#, INTC# and INTD#. You can find which 
IRQ the device will use in the Interrupt Line field. In the ACPI AML Tables 
you will find (using ACPICA) that INTA# is connected to a specified interrupt 
line, INTB# to another, etc...

    So far so good. You have, say, 20 devices. 10 of those are using INTA#, 
5 for INTB#, 5 for INTC#, and none for INTD#. So when the IRQ number related 
to #INTC you have to scan the 5 devices to understand who was the interested 
one. So there is a LOT of IRQ sharing, expecially for INTA#.

* 
    With time manufacturers started to use mainly INTA#, forgetting the 
existence of other pins. So you will likely have 18 devices on INTA# and 2 
on INTB#. 
    Motherboard manufacturers decided take the situation in control. So at 
boot the INTx# are remapped, so that you will have 5 devices for INTA#, 
5 for INTB#, 5 for INTC#, and 5 for INTD# (in the best case). That's great! 
IRQs are balanced and IRQ sharing is reduced. 
    The only problem is that you don't know what devices where mapped. If you 
read the Interrupt Pin you still get INTA#. You now need to parse the MP Tables 
or the ACPI ones to solve the mess. Good luck.

*/  
  
  
//Lista de alguns dispositivos:  
//0x2668	82801FB (ICH6) High Definition Audio Controller	0x8086	Intel Corporation  
//0x7113	PIIX4/4E/4M Power Management Controller	0x8086	Intel Corporation  
//0x2448	Hub Interface to PCI Bridge	0x8086	Intel Corporation  
//0x27B9	Intel(R) ICH7M/U LPC Interface Controller	0x8086	Intel Corporation  
//0x2000	PCnet LANCE PCI Ethernet Controller	0x1022	Advanced Micro Devices
//...  
  
  
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


//
// Obs: ?? O dispositivo cria BAR para i/o e para memória
// o driver tem a opção de escolher o método. ??
//

//
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
//

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

#define PCI_INVALID_VENDORID  0xFFFF
//...


//
// Variáveis internas.
//

int pci_supported;

//int pciStatus;
//int pciError;
//...



int pciListOffset;




//========================================
// start - estrutura do Nelson
//========================================

const char *pci_classes2[]={
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
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,//[0x40 - 0x14]="(Reserved)",
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,
	"Co-Processor",
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,//[0xFE - 0x41]="(Reserved)",
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
Class Code: A read-only register that specifies the type of function the device performs.
Subclass: A read-only register that specifies the specific function the device performs.
Prog IF: A read-only register that specifies a register-level programming interface the device has, if it has any at all.

The upper byte (at offset 0Bh) is a base class code which broadly classifies the type of function the device performs
The middle byte (at offset 0Ah) is a sub-class code which identifies more specifically the function of the device
The lower byte (at offset 09h) identifies a specific register-level programming interface (if any) so that device independent software can interact with the device
*/



/*
 * pci_classnames_t
 * //0, 'Class code' 'Subclass' 'Prog IF', e string.
 *
 * Credits: Nelson Cole.
 *
 */
typedef struct {
  uint32_t classcode; //0, 'Class code' 'Subclass' 'Prog IF',
  char *name;
}pci_classnames_t;


//PCI Express, compatibility to PCI local Bus 3.0 
pci_classnames_t pci_classnames [256] = {
  	{0x000000, 	"Non-VGA-Compatible devices"								},
  	{0x000100, 	"VGA-Compatible Device"									},
  	{0x010000, 	"SCSI bus controller"									},
  	{0x010100,	"IDE controller (ISA Compatibility mode-only controller)"				},
	{0x010105,	"IDE controller (PCI native mode-only controller)"					},
	{0x01010A,	"IDE controller (ISA Compatibility mode controller, \
supports both channels switched to PCI native mode)"								},
	{0x01010F,	"IDE controller (PCI native mode controller, \
supports both channels switched to ISA compatibility mode)"							},
	{0x010180,	"IDE controller (ISA Compatibility mode-only controller, supports bus mastering)"	},
	{0x010185,	"IDE controller (PCI native mode-only controller, supports bus mastering )"		},
	{0x01018A,	"IDE controller (ISA Compatibility mode controller, \
supports both channels switched to PCI native mode, supports bus mastering )"					},
	{0x01018F,	"IDE controller (PCI native mode controller, \
supports both channels switched to ISA compatibility mode, supports bus mastering )"				},
  	{0x010200, 	"Floppy disk controller"								},
  	{0x010300, 	"IPI bus controller"									},
  	{0x010400, 	"RAID bus controller"									},
	{0x010520, 	"ATA Controller (Single DMA)"								},
	{0x010530, 	"ATA Controller (Chained DMA)"								},
	{0x010600, 	"Serial ATA controller (vendor specific interface)"					},
	{0x010601, 	"Serial ATA controller (AHCI 1.0 interface)"						},
	{0x010602, 	"Serial ATA controller (Serial Storage Bus)"						},
	{0x010700, 	"Serial Attached SCSI (SAS)"								},
	{0x010701, 	"Serial Attached SCSI (Serial Storage Bus)"						},
	{0x010801, 	"Non-Volatile Memory Controlle (NVMHCI)"						},
	{0x010802, 	"Non-Volatile Memory Controlle (NVM Express)"						},
	{0x018000, 	"Other mass storage controller"								},
  	{0x020000, 	"Ethernet controller"									},
  	{0x020100, 	"Token ring controller"									},
  	{0x020200, 	"FDDI controller"									},
  	{0x020300, 	"ATM controller"									},
  	{0x020400, 	"ISDN controller"									},
	{0x020500, 	"WorldFip Controller"									},
	{0x020600, 	"PICMG 2.14 Multi Computing"								},
	{0x020700, 	"Infiniband Controller"									},
	{0x020800, 	"Fabric Controller"									},
  	{0x028000, 	"Other Network controller"								},
  	{0x030000, 	"VGA Compatible controller (VGA Controller)"						},
	{0x030001, 	"VGA Compatible controller (8514-Compatible Controller )"				},
  	{0x030100, 	"XGA controller"									},
  	{0x030200, 	"3D controller (Not VGA-Compatible)"							},
  	{0x038000, 	"Other Display controller"								},
  	{0x040000, 	"Multimedia video controller"								},
  	{0x040100, 	"Multimedia audio controller"								},
  	{0x040200, 	"Computer telephony device"								},
	{0x040300, 	"Audio Device (Intel High Definition Audio (HDA) Controller)"				},
  	{0x048000, 	"Other Multimedia controller"								},
  	{0x050000, 	"RAM controller"									},
  	{0x050100, 	"FLASH controller"									},
  	{0x058000, 	"Other Memory controller"								},
  	{0x060000, 	"Host bridge"										},
  	{0x060100, 	"ISA bridge"										},
  	{0x060200, 	"EISA bridge"										},
  	{0x060300, 	"MCA bridge"										},
  	{0x060400, 	"PCI-to-PCI Bridge (Normal Decode)"							},
	{0x060401, 	"PCI-to-PCI Bridge (Subtractive Decode)"						},
  	{0x060500, 	"PCMCIA bridge"										},
  	{0x060600, 	"NuBus bridge"										},
  	{0x060700, 	"CardBus bridge"									},
  	{0x060800, 	"RACEway bridge (Transparent Mode)"							},
	{0x060801, 	"RACEway bridge (Endpoint Mode)"							},
  	{0x060940, 	"PCI-to-PCI Bridge (Semi-Transparent, Primary bus towards host CPU)"			},
	{0x060980, 	"PCI-to-PCI Bridge (Semi-Transparent, Secondary bus towards host CPU)"			},
  	{0x060A00, 	"InfiniBand to PCI host bridge"								},
  	{0x068000, 	"Other Bridge"										},
  	{0x070000, 	"Serial controller (8250-Compatible (Generic XT))"					},
	{0x070001, 	"Serial controller (16450-Compatible )"							},
	{0x070002, 	"Serial controller (16550-Compatible )"							},
	{0x070003, 	"Serial controller (16650-Compatible )"							},
	{0x070004, 	"Serial controller (16750-Compatible)"							},
	{0x070005, 	"Serial controller (16850-Compatible)"							},
	{0x070006, 	"Serial controller (16950-Compatible)"							},
	{0x070100, 	"Parallel Controller (Standard Parallel Port)"						},
	{0x070101, 	"Parallel Controller (Bi-Directional Parallel Port)"					},
	{0x070102, 	"Parallel Controller (ECP 1.X Compliant Parallel Port)"					},
	{0x070103, 	"Parallel Controller (IEEE 1284 Controller)"						},
	{0x0701FE, 	"Parallel Controller (IEEE 1284 Target Device)"						},
	{0x070200, 	"Multiport Serial Controller"								},
	{0x070300, 	"Modem (Generic Modem)"									},
	{0x070301, 	"Modem (Hayes 16450-Compatible Interface)"						},
	{0x070302, 	"Modem (Hayes 16550-Compatible Interface)"						},
	{0x070303, 	"Modem (Hayes 16650-Compatible Interface)"						},
	{0x070304, 	"Modem (Hayes 16750-Compatible Interface)"						},
	{0x070400, 	"GPIB (IEEE 488.1/2) Controller"							},
	{0x070500, 	"Smart Card"										},
	{0x078000, 	"Other Simple Communication controller"							},
  	{0x080000, 	"PIC (Generic 8259-Compatible)"								},
	{0x080001, 	"PIC (ISA-Compatible)"									},
	{0x080002, 	"PIC (EISA-Compatible)"									},
	{0x080010, 	"PIC (I/O APIC Interrupt Controller)"							},
	{0x080020, 	"PIC (I/O(x) APIC Interrupt Controller)"						},
  	{0x080100, 	"DMA controller (Generic 8237-Compatible)"						},
	{0x080101, 	"DMA controller (ISA-Compatible)"							},
	{0x080102, 	"DMA controller (EISA-Compatible)"							},
  	{0x080200, 	"Timer (Generic 8254-Compatible)"							},
	{0x080201, 	"Timer (ISA-Compatible)"								},
	{0x080202, 	"Timer (EISA-Compatible)"								},
	{0x080203, 	"Timer (HPET)"										},
  	{0x080300, 	"RTC (Generic RTC)"									},
	{0x080301, 	"RTC (ISA-Compatible)"									},
  	{0x080400, 	"PCI Hot-plug controller"								},
	{0x080500, 	"SD Host controller"									},
	{0x080600, 	"IOMMU"											},
  	{0x088000, 	"Other System peripheral controller"							},
  	{0x090000, 	"Keyboard controller"									},
  	{0x090100, 	"Digitizer Pen"										},
  	{0x090200, 	"Mouse controller"									},
  	{0x090300, 	"Scanner controller"									},
  	{0x090400, 	"Gameport controller (Generic)"								},
	{0x090401, 	"Gameport controller (Extended)"							},
  	{0x098000, 	"Other input controller"								},
  	{0x0A0000, 	"Generic Docking Station"								},
  	{0x0A8000, 	"Other type of docking station"								},
  	{0x0B0000, 	"386"											},
  	{0x0B0100, 	"486"											},
  	{0x0B0200, 	"Pentium"										},
  	{0x0B1000, 	"Alpha"											},
  	{0x0B2000, 	"Power PC"										},
  	{0x0B3000, 	"MIPS"											},
  	{0x0B4000, 	"Co-processor"										},
  	{0x0C0000, 	"FireWire (IEEE 1394) controller (Generic)"						},
	{0x0C0010, 	"FireWire (IEEE 1394) controller (OHCI)"						},
  	{0x0C0100, 	"ACCESS Bus"										},
  	{0x0C0200, 	"SSA"											},
  	{0x0C0300, 	"USB (UHCI Controller)"									},
	{0x0C0310, 	"USB1.1 (OHCI Controller)"								},
	{0x0C0320, 	"USB2.0 (EHCI Controller)"								},
	{0x0C0330, 	"USB3.0 (XHCI Controller)"								},
	{0x0C0380, 	"USB Controller (Unspecified )"								},
	{0x0C03FE, 	"USB Device (Not a host controller)"							},
	{0x0C0400, 	"Fiber Channel"										},
  	{0x0C0500, 	"SMBus"											},
  	{0x0C0600, 	"InfiniBand"										},
	{0x0C0700, 	"IPMI Interface (SMIC)"									},
	{0x0C0701, 	"IPMI Interface (Keyboard Controller Style)"						},
	{0x0C0702, 	"IPMI Interface (Block Transfer)"							},
	{0x0C0800, 	"SERCOS Interface (IEC 61491"								},
	{0x0C0900, 	"CANbus"										},
  	{0x0D0000, 	"iRDA controller"									},
  	{0x0D0100, 	"Consumer IR controller"								},
  	{0x0D1000, 	"RF controller"										},
	{0x0D1100, 	"Bluetooth Controller"									},
	{0x0D1200, 	"Broadband Controller"									},
	{0x0D2000, 	"Ethernet Controller (802.1a ? 5 GHz)"							},
	{0x0D2100, 	"Ethernet Controller (802.1b 2.4 GHz)"							},
  	{0x0D8000, 	"Other type of wireless controller"							},
  	{0x0E0000, 	"I2O"											},
  	{0x0F0000, 	"Satellite TV controller"								},
  	{0x0F0100, 	"Satellite audio controller"								},
  	{0x0F0300, 	"Satellite voice controller"								},
  	{0x0F0400, 	"Satellite data  controller"								},
  	{0x100000, 	"Network and Computing Encrpytion/Decryption"						},
  	{0x101000, 	"Entertainment Encryption/Decryption"							},
  	{0x108000, 	"Other Encryption/Decryption"								},
  	{0x110000, 	"DPIO module"},
  	{0x110100, 	"Performance counters"},
  	{0x111000, 	"Communication synchronizer"},
  	{0x112000, 	"Signal Processing Management"},
	{0x118000, 	"Other Signal Processing Controller"},
  	{0x000000, 	"Null"}
};


//========================================
// end - estrutura do Nelson
//========================================


//
// Class strings.
//

//Obs: parece que outra forma de lista é mais apropriado.
static const char* pci_class_strings[] = {
	"Unknow",                              //0x00 (Pre 2.0 device)
	"Mass Storage Controller",             //0x01
	"Network Controller",                  //0x02
	"Display Controller",                  //0x03
	"Multimedia Controller",               //0x04 (Multimedia Device)
	"Memory Controller",                   //0x05
	"Bridge Device",                       //0x06
	"Simple Communication Controller",     //0x07
	"Base System Peripheral",              //0x08
	"Input Device",                        //0x09
	"Docking Station",                     //0x0a
	"Processor",                           //0x0b
	"Serial Bus Controller",               //0x0c
	"Wireless Controller",                 //0x0d
	"Intelligent IO Controllers",          //0x0e
	"Satellite Communication Controller",  //0x0f
	"Encryption Decryption Controller",    //0x10
	"Data Acquisition and Signal Processing Controller",
	0
	//"Processing Accelerators",      //0x12
	//"Non-Essential Instrumentation" //0x13
	//Daqui pra frente está reservado.
	//0xff (Device does not fit in any defined classes)
};


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
//Obs: parece que outra forma de lista é mais apropriado.
static const char* mass_storage_subclass_strings[] = {
    "SCSI Bus Controller",          //0x00
	"IDE Controller",               //0x01
	"Floppy Disk Controller",       //0x02 
	"IPI Bus Controller",           //0x03
	"RAID Controller",              //0x04
	"ATA Controller",               //0x05 (ATA controller with ADMA interface)
	"Serial ATA",                   //0x06 (Serial ATA controller)
	"Serial Attached SCSI (SAS)",   //0x07 (Serial Attached SCSI (SAS) controller)
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

int pci_setup_devices();
//...


//
// Obs: 
//     Os dispositivos podem compartilhar a mesma interrupção no PIC/APIC. 
// Então para uma IRQ destinada à PCI terá que identificar qual dispositivo 
// gerou a interrupção, para chamar a rotina apropriada.
//


/*
 * KiPciHandler1: 
 * 
 *     **** PCI HANDLER ****
 *
 *     Todas as interrupções geradas pelos dispositivos PCI
 * usarão o mesmo isr (handler). Caberá à rotina do handler identificar
 * qual dispositivo sinalizou que efetuou uma interrupção. Então direcionar 
 * para a rotina de serviço aproriada.
 *
 */
unsigned long KiPciHandler1()
{
	//...
	return (unsigned long) 0;
};


/*
 * KiPciHandler2: 
 * 
 *     **** PCI HANDLER ****
 *
 *     Todas as interrupções geradas pelos dispositivos PCI
 * usarão o mesmo isr (handler). Cabera à rotina do handler identificar
 * qual dispositivo sinalizou que efetuou uma interrupção. Então direcionar 
 * para a rotina de serviço aproriada.
 *
 */
unsigned long KiPciHandler2()
{
	//...
	return (unsigned long) 0;
};

/*
 * KiPciHandler3: 
 * 
 *     **** PCI HANDLER ****
 *
 *     Todas as interrupções geradas pelos dispositivos PCI
 * usarão o mesmo isr (handler). Cabera à rotina do handler identificar
 * qual dispositivo sinalizou que efetuou uma interrupção. Então direcionar 
 * para a rotina de serviço aproriada.
 *
 */
unsigned long KiPciHandler3()
{
	//...
	return (unsigned long) 0;
};


/*
 * KiPciHandler4: 
 * 
 *     **** PCI HANDLER ****
 *
 *     Todas as interrupções geradas pelos dispositivos PCI
 * usarão o mesmo isr (handler). Cabera à rotina do handler identificar
 * qual dispositivo sinalizou que efetuou uma interrupção. Então direcionar 
 * para a rotina de serviço aproriada.
 *
 */
unsigned long KiPciHandler4()
{
	//...
	return (unsigned long) 0;
};


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
 * pciConfigReadByte:
 *     Read com retorno do tipo unsigned char.
 */	

unsigned char 
pciConfigReadByte ( unsigned char bus, 
					unsigned char slot, 
					unsigned char func, 
					unsigned char offset )
{
	//Montando uma unsigned long.
	unsigned long lbus  = (unsigned long) bus;   //Bus.
	unsigned long lslot = (unsigned long) slot;  //Device.
	unsigned long lfunc = (unsigned long) func;  //Function.
	
	//O endereço a ser montado e enviado para porta 0xCF8.
	unsigned long address;   
	
	//Retorno armazenado na porta de status.
	unsigned char Ret = 0;             
 
	//
	// @todo: Filtros de tamanho máximo.
	//
	
	// Create configuration address.
	address = (unsigned long)((lbus << 16) | (lslot << 11) | (lfunc << 8) | (offset & 0xfc) | ((unsigned long)0x80000000));
 
    //
	// sendComand:
    // Write out the address. (0x0CF8).
    //
    outportl(PCI_ADDRESS_PORT, address);
    
	//
	// getData:
	// Read in the data port. (0x0CFC).
	// Talves possamos usar um input do tipo char, que é assim
	// inline unsigned char inportb(int port)  
    // int inport8(int port) 
	//

	Ret = (unsigned char)(( inportl(PCI_DATA_PORT) >> ((offset & 3) * 8)) & 0xff); //Parece ser o certo.
	//Ret = (unsigned char)(( inportl(PCI_DATA_PORT) >> ((offset & 2) * 8)) & 0xff);	
	//Ret = (unsigned char)( inport8(PCI_DATA_PORT) );
	//Ret = (unsigned char)(( inportl(PCI_DATA_PORT) >> ((offset & 2) * 8)) & 0xff); //??	
	

    // Obs: 
	// (offset & 2) * 8) = 0 Will choose the first word of the 32 bits register.    
	
	return (unsigned char) Ret; 
} 


/*
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
pciConfigReadWord ( unsigned char bus, 
					unsigned char slot, 
					unsigned char func, 
					unsigned char offset )
{
	//Montando uma unsigned long.
	unsigned long lbus  = (unsigned long) bus;   //Bus.
	unsigned long lslot = (unsigned long) slot;  //Device.
	unsigned long lfunc = (unsigned long) func;  //Function.
	
	//O endereço a ser montado e enviado para porta 0xCF8.
	unsigned long address;   
	
	//Retorno armazenado na porta de status.
	unsigned short Ret = 0;             
 
	//
	// @todo: Filtros de tamanho máximo.
	//
	
	// Create configuration address.
	address = (unsigned long)((lbus << 16) | (lslot << 11) | (lfunc << 8) | (offset & 0xfc) | ((unsigned long)0x80000000));
 

	// sendComand:
	// Write out the address. (0x0CF8).

	outportl(PCI_ADDRESS_PORT, address);

	//
	// getData:
	// Read in the data port. (0x0CFC).
    //
	// Apesar do inpot pegar uma longo o retornno é short.
	// @todo: Talvez possamos usar um input do tipo short.
	// que é assim int inport16(int port)
	//

	Ret = (unsigned short)(( inportl(PCI_DATA_PORT) >> ((offset & 2) * 8)) & 0xffff);	
	//Ret = (unsigned short)(  inport16(PCI_DATA_PORT) );

	
    // Obs: 
	// (offset & 2) * 8) = 0 Will choose the first word of the 32 bits register.   
	
	return (unsigned short) Ret; 
}
 
 
/* 
 * pciConfigReadDWord:
 *     Read com retorno do tipo unsigned long.
 */							  
unsigned long pciConfigReadDWord( unsigned char bus, 
                                  unsigned char slot, 
								  unsigned char func, 
								  unsigned char offset )
{
	//Montando uma unsigned long.
	unsigned long lbus  = (unsigned long) bus;   //Bus.
    unsigned long lslot = (unsigned long) slot;  //Device.
    unsigned long lfunc = (unsigned long) func;  //Function.
	
	//O endereço a ser montado e enviado para porta 0xCF8.
    unsigned long address;   
	
	//Retorno armazenado na porta de status.
    unsigned long Ret = 0;             
 
    //
	// @todo: Filtros de tamanho máximo.
	//
	
    // Create configuration address.
	address = (unsigned long)((lbus << 16) | (lslot << 11) | (lfunc << 8) | (offset & 0xfc) | ((unsigned long)0x80000000));
 
    //
	// sendComand:
    // Write out the address. (0x0CF8).
    //
    outportl(PCI_ADDRESS_PORT, address);
    
	//
	// getData:
	// Read in the data port. (0x0CFC).
	//int inport32(int port)
    //

	Ret = (unsigned long)( inportl(PCI_DATA_PORT) ); //Parece ser o certo.
	//Ret = (unsigned long)(( inportl(PCI_DATA_PORT) >> ((offset & 2) * 8)) & 0xffffffff); 
	//Ret = (unsigned long)(  inport32(PCI_DATA_PORT) );	
	//Ret = (unsigned long)(( inportl(PCI_DATA_PORT) >> ((offset & 2) * 8)) & 0xffff);

	
	//
    // Obs: 
	// (offset & 2) * 8) = 0 Will choose the first word of the 32 bits register.
	//
	
done:    
	return (unsigned long) Ret; 
};

 
/*
 * pciCheckVendor:
 *     Check vendor, offset 0.
 */ 
unsigned short pciCheckVendor(unsigned char bus, unsigned char slot)
{
	//@todo: Nesse momento não há nenhume busca por fuction.
	// Vendor.
	return (unsigned short) pciConfigReadWord( bus, slot, 0, PCI_OFFSET_VENDORID );  
}; 

 
/*
 * pciCheckDevice:
 *     Check device, offset 2.    
 */ 
unsigned short pciCheckDevice(unsigned char bus, unsigned char slot)
{   
    //@todo: Nesse momento não há nenhume busca por fuction.     
    // Device.
	return (unsigned short) pciConfigReadWord( bus, slot, 0, PCI_OFFSET_DEVICEID );   
};

/*
 * pciGetClassCode:
 *     Get class code, offset 0x0B.  
 */
unsigned char pciGetClassCode(unsigned char bus, unsigned char slot)
{
    //@todo: Nesse momento não há nenhume busca por fuction.	
	return (unsigned char) pciConfigReadByte( bus, slot, 0, PCI_OFFSET_CLASSCODE );
};


/*
 * pciGetSubClass:
 *     Get subclass code. Offset 0x0A.
 */
unsigned char pciGetSubClass(unsigned char bus, unsigned char slot)
{
	//@todo: Nesse momento não há nenhume busca por fuction.
	return (unsigned char) pciConfigReadByte( bus, slot, 0, PCI_OFFSET_SUBCLASS );
};



unsigned char pciGetHeaderType(unsigned char bus, unsigned char slot)
{
    //@todo: Nesse momento não há nenhume busca por fuction.	
	return (unsigned char) pciConfigReadByte( bus, slot, 0, PCI_OFFSET_HEADERTYPE );
};

/*
 *****************************************************************
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
unsigned long pciGetBAR( unsigned char bus, 
                         unsigned char slot, 
						 int number )
{
	unsigned long BAR;
	
	//@todo: Filtros para argumentos.
	
	if( number <0 || number > 5 ){
		return 0;
	};
	
    switch(number)
	{
		case 0:
			BAR = (unsigned long) pciConfigReadDWord( bus, 
			                                          slot, 
													  0, 
													  PCI_OFFSET_BASEADDRESS0 );
			goto done;
		    break;
	
		case 1:
			BAR = (unsigned long) pciConfigReadDWord( bus, 
			                                          slot, 
													  0, 
													  PCI_OFFSET_BASEADDRESS1 );
			goto done;
		    break;

		case 2:
			BAR = (unsigned long) pciConfigReadDWord( bus, 
			                                          slot, 
													  0, 
													  PCI_OFFSET_BASEADDRESS2 );
			goto done;
		    break;

		case 3:
			BAR = (unsigned long) pciConfigReadDWord( bus, 
			                                          slot, 
													  0, 
													  PCI_OFFSET_BASEADDRESS3 );
			goto done;
		    break;

		case 4:
			BAR = (unsigned long) pciConfigReadDWord( bus, 
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
		    return 0;
            break;		
	};
	//Nothing.
done:	
	return (unsigned long) BAR;
};


//
// Continua ...
//


/*
 * pciGetInterruptLine:
 *     Get Interrupt Line, offset 0x3C.
 *     (Read an write register).
 */
unsigned char pciGetInterruptLine( unsigned char bus, 
                                   unsigned char slot )
{
	return (unsigned char) pciConfigReadByte( bus, 
	                                          slot, 
											  0, 
											  PCI_OFFSET_INTERRUPTLINE );
};


/*
 * pciGetInterruptPin:
 *     Get interrupt pin offser 3d (Read only).
 */
unsigned char pciGetInterruptPin( unsigned char bus, 
                                  unsigned char slot )
{
	return (unsigned char) pciConfigReadByte( bus, 
	                                          slot, 
											  0, 
											  PCI_OFFSET_INTERRUPTPIN );
};


//
// Continua ...
//


/*
 ****************************************************************************
 * pciInfo:
 *     Mostra as informações salvas nas estruturas da lista de dispositivos. 
 *
 * 0x2668	82801FB (ICH6) High Definition Audio Controller 0x8086	Intel Corporation.
 * 0x2829	Intel(R) ICH8M SATA AHCI Controller	0x8086	Intel Corporation.
 * 0x1237	PCI & Memory	0x8086	Intel Corporation.
 * ...
 *
 */

int pciInfo (){
	
	int i;
	int Max = 32;

	struct pci_device_d *D;
	
	printf("pciInfo: \n");
	
	//
	// Uma lista com no máximo 32 ponteiros para estrutura de dispositivo pci.
	//
	
	for ( i=0; i<Max; i++ )
	{
		//Pega um ponteiro de estrutura na lista.
		D = (void *) pcideviceList[i];
		
		//Checa se o ponteiro é válido.
		if( (void *) D != NULL )
		{
			//@todo: Mostrar mais informações.
			if(D->deviceMagic == 1234)
			{
				printf("\n [%d/%d/%d] Vendor=%x Device=%x Class=%s SubClass=%x iLine=%d iPin=%d \n",
				       D->bus, D->dev , D->func,
					   D->Vendor, 
					   D->Device, 
					   pci_class_strings[ D->classCode ], 
					   D->subclass, 
					   D->irq_line, 
					   D->irq_pin );
			
			
			};
		};
	};
	
	printf("done\n");
	return (int) 0; 
}


/*
 * Mostra informações sobre um dispositivo PCI da lista.
 */

int pciShowDeviceInfo(int number)
{
    struct pci_device_d *D;
  
	if(number < 0 || number > 32)
	{
		return 0;
	}
	
	//Pega um ponteiro de estrutura na lista.
	D = (void *) pcideviceList[number];
	
	//Checa se o ponteiro é válido.
	if( (void *) D != NULL )
	{
		if(D->deviceMagic == 1234){
			
			printf ("Vendor={%x} Device={%x} ClassCode={%x} IntLine={%x} \n",
			    D->Vendor, D->Device, D->classCode, D->irq_line );
		}
	}
	//Nothing
	return 0;
};



/*
 ********************************
 * pciHandleDevice
 *    Registra um dispositivo encontrado na sondagem. 
 *    Inicializa em alguns casos.
 */

int pciHandleDevice ( unsigned char bus, unsigned char dev, unsigned char fun )
{
    
	//ok
	printf("bus=%d dev=%d fun=%d \n", bus, dev, fun);

	int Status = -1;
	
	struct pci_device_d *D;   //Device. 
	//struct pci_driver_d *Dr;  //Driver.
	
    D = (void *) malloc ( sizeof( struct pci_device_d  ) );
    
	if ( (void *) D == NULL )
	{
		printf("pciHandleDevice: struct");
		die();
	    //return -1;
	
	}else{
			
		//Identificador.
		D->deviceId = (int) pciListOffset;
		D->deviceUsed = (int) 1;
		D->deviceMagic = (int) 1234;
		D->name = "No name";
					
		//Localização.
		D->bus = (unsigned char) bus;
		D->dev = (unsigned char) dev;
		D->func = (unsigned char) fun; 
					
		//Object support.
		D->objectType = ObjectTypePciDevice;
		D->objectClass = ObjectClassKernelObjects;
					
		//Pci Header.
		D->Vendor = (unsigned short) pciCheckVendor (bus, dev);	
		D->Device = (unsigned short) pciCheckDevice (bus, dev);
					
		printf("$ vendor=%x device=%x \n",D->Vendor, D->Device);
		
		
		D->classCode = (unsigned char) pciGetClassCode(bus, dev);
		D->subclass = (unsigned char) pciGetSubClass(bus, dev); 
					
		D->irq_line = (unsigned char) pciGetInterruptLine(bus, dev);
		D->irq_pin = (unsigned char) pciGetInterruptPin(bus, dev);
					
			
		D->next = NULL;   //Next device.
		
		
		//Nic intel
		if ( (D->Vendor == 0x8086) && (D->Device == 0x100E ) && (D->classCode == PCI_CLASSCODE_NETWORK) )	
		{
			debug_print("0x8086:0x100E found \n");
		     
			 //printf("b=%d d=%d f=%d \n", D->bus, D->dev, D->func );
								
		     //printf("82540EM Gigabit Ethernet Controller found\n");
		     Status = (int) e1000_init_nic ( (unsigned char) D->bus, 
							   (unsigned char) D->dev, 
							   (unsigned char) D->func, 
							   (struct pci_device_d *) D );
			
			 if (Status == 0)
			 {
			      //# irq and reset.
				 
				  //printf("8086:100e initialized\n");
			      
				  e1000_setup_irq();
				  e1000_reset_controller();
			      
				  //printf("8086:100e done\n");
				  //printf("#debug breakpoint");
				  //refresh_screen();
				  //while(1){} 
				 
		     }else{
			      //printf("."); 
		    }
	    }		
		
		//Colocar a estrutura na lista.		
					
		//#todo: Limits
		//#bugbug: limite determinado ... precisa de variável.
		
		if ( pciListOffset < 0 || pciListOffset >= 32 )
		{ 
			printf("No more slots!\n");
			return -1;
		}
					
		pcideviceList[pciListOffset] = (unsigned long) D;
		pciListOffset++;
		
		printf("$");
	
	}
	
	return 0;
}


/*
 ***********************************************************************
 * pci_setup_devices:
 *     Encontrar os dispositivos PCI e salvar as informações sobre eles
 * em suas respectivas estruturas.
 *
 * @todo: 
 *     Completar toda a estrutura, ainda faltam elementos.
 *     Obs: A estrutura está em pci.h.    
 *
 * #importante:
 * #todo
 * Quando sondamos os dispositivos pci usando for, podemos checar a
 * classe e a subclasse dos dispositivos e se encontrarmos a combilaçao desejada
 * entao inicializamos o dispositivo.
 */


//##bugbug
//Não precisamos inicialziar os dispositivos nesse momento.
//somente colocar na estrutura

int pci_setup_devices (){	
	
    unsigned short Vendor;    //Offset 0.
	unsigned short Device;    //Offset 2.
	
	//@todo: rever tamanho
	//unsigned char ClassCode;
	//unsigned char SubClassCode;
	//unsigned char ProgIF;	
	
 	
	unsigned char i = 0; //Bus.
    unsigned char j = 0; //Devices. (Slots).
	unsigned char k = 0; //Functions
	
 
    printf("Detecting PCI Devices..\n");
	
	unsigned char HeaderType;
	int funcCount;
	
	//Bus.
	for( i=0; i < PCI_MAX_BUSES; i++)   
	{
		//Device.
	    for( j=0; j < PCI_MAX_DEVICES; j++)
        {
			
		    // Valid device ?
			
		    Vendor = (unsigned short) pciCheckVendor (i,j);			
		    
			if ( Vendor != 0 && Vendor != PCI_INVALID_VENDORID )
		    { 
				
				printf("vendor=%x\n",Vendor);
				// Multifunction ??
				//Se o bit 7 estiver acionado, entao e' multifunction.
				
				HeaderType = pciGetHeaderType (i,j);
                
				funcCount = HeaderType & PCI_TYPE_MULTIFUNC ? PCI_MAX_FUNCTIONS : 1;
				
				//function
			    for( k=0; k<funcCount; k++)
			    {
				    //k=0;
					printf("+");
				    pciHandleDevice ( i, j, k );			
			    }; //fuction for.
				
		    };				
					
		};  // Device for.		
		
	};  //bus for.
	


    printf("Detecting PCI Devices completes..\n");
	
	debug_print("Detecting PCI Devices completes..\n");
	//refresh_screen();
	//while(1){}

    return 0; 
}


/*
 * init_pci:
 *     Inicializa o módulo PCI em Kernel Mode, dentro do Kernel Base. 
 * 
 * @todo: 
 *     +Pega informações sobre PCI.
 *     +Pegar as informações e por em estrutura e registro.
 *
 *     Obs: Essa rotina está incompleta.
 */

int init_pci (){
	
	
	debug_print("init_pci:\n");
	
	
	int Status = 0;
    int Index;
    int Max = 32;   //@todo.	
	
	//===========
	
    unsigned long data;
	
	outportl ( 0xCF8, 0x80000000);
	
	data = (unsigned long) inportl (0xCF8);
 
    if ( data != 0x80000000 )
    {
		//#todo:
		//Fazer alguma coisa pra esse caso.
		//Talvez seja um 386 ou 486 sem suporte a PCI.
		//Talvez ISA.
		
		pci_supported = 0;
		
	    //STATUS_NOT_SUPPORTED	
		printf("init_pci: PCI NOT supported");
		die();
		
	}else{
		
		pci_supported = 1;
		
	    //STATUS_SUCCESS
        //printf("PCI supported!");		
	};
	
	
	//#todo: 
	//Colocar esse status na estrutura platform->pci_supported.
	//Talvez assim: platform->platform_type.
	
	//#debug
	//refresh_screen();
	//while(1){}
		
	
	//==========
	

	
    // Initializa PCI device list.
   
    //@todo: Criar um construtor que faça isso.
	//Exemplo: pciPci().
    
	for ( Index=0; Index<Max; Index++ )
	{
		pcideviceList[Index] = (unsigned long) 0;
	}
	
	// Indice para a lista de dispositivos PCI.
	pciListOffset = 0;
   

	//
	// Encontrar os dispositivos PCI e salvar as informações sobre eles
	// em suas respectivas estruturas.
	//
   
	Status = (int) pci_setup_devices(); 
	
	if (Status != 0)
	{
	    printf("init_pci:\n");
        die();		
	};
    
    //...
	
//done:	

    g_driver_pci_initialized = (int) 1; 
	
	//printf("Done\n");
    
	return (int) Status; 
};






/*
 * pciPci:
 *     Constructor.
int pciPci(){
	;
};
 */


/*
 * pciInit:
 *     Inicialização do módulo.
 */
 
int pciInit (){
	
	//#bugbug  essa funções nem é chamada.
	
	debug_print("pciInit:\n");
	
	/*
	return (int) init_pci();
	*/
	
	return -1;
	
}; 
 
//
// End.
//

