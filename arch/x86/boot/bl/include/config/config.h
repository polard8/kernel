//Debug flags.
//Testando desligado.

// #BUGBUG
// Nao usar por enquanto.
// usar essa flag esta ativando alguma rotina
// defeituosa.
// #define BL_VERBOSE 1  

//
// ## IMPORNTANTE ##
//

//TEM QUE CONFIGURAR O BL TAMBÉM

// USE PRIMARY MASTER!!

// Portas bases encontradas nas BARs.
//BAR0 = base port 1F0   ( channel 0 primary master) (channel 0 primary slave) 
//BAR1 = base port 3F6	 channel ??
//BAR2 = base port 170   (channel 1 secondary master) (channel 1 secondary slave)
//BAR3 = base port 376   channel ??

#define __CHANNEL0 0  // BAR 0 primary, master and slave
#define __CHANNEL1 2  // BAR 2 secondary, master and slave
#define __CHANNEL2 1  // BAR 1 extra (sata amulating ide)
#define __CHANNEL3 3  // BAR 3 extra (sata amulating ide)


// #importante
// Esses valores são usados pelo driver.
#define __IDE_PORT __CHANNEL0    //primary
#define __IDE_SLAVE  0           // 0=master 1=slave




// #tests:

// + Funcionou BAR=0 slave=0.
// + Funcionou BAR=0 slave=1.

// + Funcionou BAR=2 slave=0. secondary master 
// + Funcionou BAR=2 slave=1. secondary slave

// #bugbug
// Ouve uma falha..
// Só temos o registro das portas 0 e 2.
// A porta 0 equivale ao canal primary.
// A porta 2 equivale ao canal secondary.
// Eram para as portas 0 e 1 representarem o canal primary.
// Eram para as portas 2 e 3 represerntarem o canal secondary.

// #importante:
// Na verdade só funcionam as portas 0 e 2 porque são 
// selecionadores das BARs 0 e 2, onde estão as portas de HD.
// #todo: rever o código nessa parte de configuração das BARs.


//a questao 'e que existem canais extras
//vamos presizar ler mais bars.

/*
Current disk controller chips almost always support two ATA buses per chip. 
There is a standardized set of IO ports to control the disks on the buses. 
The first two buses are called the Primary and Secondary ATA bus, and are almost 
always controlled by IO ports 0x1F0 through 0x1F7, and 0x170 through 0x177, 
respectively (unless you change it). The associated 
Device Control Registers/Alternate Status ports are IO ports 0x3F6, and 0x376,
respectively. The standard IRQ for the Primary bus is IRQ14, and IRQ15 for the Secondary bus.

If the next two buses exist, they are normally controlled by IO ports 0x1E8 through 0x1EF, 
and 0x168 through 0x16F, respectively. The associated
Device Control Registers/Alternate Status ports are IO ports 0x3E6, and 0x366. 
*/

/*
This is the multiple IDE interface driver, as evolved from hd.c.

It supports up to 9 IDE interfaces per default, on one or more IRQs (usually
14 & 15).  There can be up to two drives per interface, as per the ATA-6 spec.

Primary:    ide0, port 0x1f0; major=3;  hda is minor=0; hdb is minor=64
Secondary:  ide1, port 0x170; major=22; hdc is minor=0; hdd is minor=64
Tertiary:   ide2, port 0x1e8; major=33; hde is minor=0; hdf is minor=64
Quaternary: ide3, port 0x168; major=34; hdg is minor=0; hdh is minor=64
fifth..     ide4, usually PCI, probed
sixth..     ide5, usually PCI, probed
*/


