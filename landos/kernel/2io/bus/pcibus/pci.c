// pci.c


#include <kernel.h>    

//
// BAR Support
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
// Internal
//

int pci_supported;
int pciListOffset;
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
    // Retorno armazenado na porta de status.
    unsigned char Ret=0;

    // Montando uma unsigned int. (32 bits)
    // Bus, Device and Function.

    unsigned int ibus  = (unsigned int) bus; 
    unsigned int islot = (unsigned int) slot; 
    unsigned int ifunc = (unsigned int) func; 

    // O endereço a ser montado e enviado para porta 0xCF8.
    // 32bit
    unsigned int address = 0;

    // #todo: 
    // Filtros de tamanho máximo.

    // Create configuration address.
    // 32bit
    address = (unsigned int) ((ibus  << 16) | (islot << 11) | (ifunc <<  8) | (offset & 0xfc) | ((unsigned int) 0x80000000) );

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

    // 1 byte
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
    // Retorno armazenado na porta de status.
    unsigned short Ret=0;

    // Montando uma unsigned int. 32bits
    // Bus, Device and Function.

    unsigned int ibus  = (unsigned int) bus; 
    unsigned int islot = (unsigned int) slot; 
    unsigned int ifunc = (unsigned int) func; 

    // O endereço a ser montado e enviado para porta 0xCF8.
    // 32bit
    unsigned int address = 0;



    // #todo: 
    // Filtros de tamanho máximo.

    // Create configuration address.
    // 32bit
    address = (unsigned int) ((ibus << 16) | (islot << 11) | (ifunc << 8) | (offset & 0xfc) | ((unsigned int)0x80000000));


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

    // 16 bits
    return (unsigned short) Ret; 
}


/* 
 *****************************
 * pciConfigReadDWord:
 *     Read com retorno do tipo unsigned int. 32bit
 */

// 32bit
unsigned int 
pciConfigReadDWord ( 
    unsigned char bus, 
    unsigned char slot, 
    unsigned char func, 
    unsigned char offset )
{

    // Retorno armazenado na porta de status.
    // 32bit
    unsigned int Ret = 0;


    // Montando uma unsigned int. 32bit
    // Bus, Device and Function.

    unsigned int ibus  = (unsigned int) bus; 
    unsigned int islot = (unsigned int) slot; 
    unsigned int ifunc = (unsigned int) func; 

    // O endereço a ser montado e enviado para porta 0xCF8.
    // 32bit
    unsigned int address = 0;
 
    // #todo: 
    // Filtros de tamanho máximo.

    // Create configuration address.
    address = (unsigned int) ((ibus << 16) | (islot << 11) | (ifunc << 8) | (offset & 0xfc) | ((unsigned int)0x80000000));

    // sendComand:
    // Write out the address. (0x0CF8).

    out32 (PCI_ADDRESS_PORT, address);
    io_delay();

    // getData:
    // Read in the data port. (0x0CFC).

    // Parece ser o certo.
    // 32bit
    Ret = (unsigned int) ( in32(PCI_DATA_PORT) ); 
    io_delay();
    
    // Obs: 
    // (offset & 2) * 8) = 0 Will choose the first word of the 32 bits register.

    // 32bit
    return (unsigned int) Ret; 
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

unsigned int 
pciGetBAR ( 
    unsigned char bus, 
    unsigned char slot, 
    int number )
{

    unsigned int BAR = 0;

	// #todo: 
	// Filtros para argumentos.

    if ( number < 0 || number > 5 )
    {
        // ?? msg
        return 0;
    }


    switch (number){

        case 0:
            BAR = (unsigned int) pciConfigReadDWord ( 
                                      bus, slot, 0, 
                                      PCI_OFFSET_BASEADDRESS0 );
            goto done;
            break;

        case 1:
            BAR = (unsigned int) pciConfigReadDWord ( 
                                      bus, slot, 0, 
                                      PCI_OFFSET_BASEADDRESS1 );
            goto done;
            break;

        case 2:
            BAR = (unsigned int) pciConfigReadDWord ( 
                                      bus, slot, 0, 
                                      PCI_OFFSET_BASEADDRESS2 );
            goto done;
            break;

        case 3:
            BAR = (unsigned int) pciConfigReadDWord ( 
                                      bus, slot, 0, 
                                      PCI_OFFSET_BASEADDRESS3 );
            goto done;
            break;

        case 4:
            BAR = (unsigned int) pciConfigReadDWord ( 
                                      bus, slot, 0, 
                                      PCI_OFFSET_BASEADDRESS4 );
            goto done;
            break;

        case 5:
            BAR = (unsigned int) pciConfigReadDWord( 
                                      bus, slot, 0, 
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
    return (unsigned int) BAR;
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
    return (unsigned char) pciConfigReadByte ( 
                               bus, slot, 0, PCI_OFFSET_CLASSCODE );
}



/*
 * pciGetHeaderType:
 * 
 */

// #todo: 
// Nesse momento não há nenhuma busca por fuction.

unsigned char 
pciGetHeaderType (unsigned char bus, unsigned char slot)
{
    return (unsigned char) pciConfigReadByte ( 
                               bus, slot, 0, PCI_OFFSET_HEADERTYPE );
}


/*
 * pciGetInterruptLine:
 *     Get Interrupt Line, offset 0x3C.
 *     (Read an write register).
 */

unsigned char 
pciGetInterruptLine ( 
    unsigned char bus, 
    unsigned char slot )
{
    return (unsigned char) pciConfigReadByte ( 
                               bus, slot, 0, 
                               PCI_OFFSET_INTERRUPTLINE );
}

/*
 * pciGetInterruptPin:
 *     Get interrupt pin offser 3d (Read only).
 */

unsigned char 
pciGetInterruptPin ( 
    unsigned char bus, 
    unsigned char slot )
{
    return (unsigned char) pciConfigReadByte ( 
                               bus, slot, 0, 
                               PCI_OFFSET_INTERRUPTPIN );
}

/*
 * pciGetSubClass:
 *     Get subclass code. Offset 0x0A.
 */

// #todo: 
// Nesse momento não há nenhume busca por fuction.

unsigned char 
pciGetSubClass (unsigned char bus, unsigned char slot)
{
    return (unsigned char) pciConfigReadByte ( 
                               bus, slot, 0, PCI_OFFSET_SUBCLASS );
}


/*
 * pciCheckDevice:
 *     Check device, offset 2. 
 */

// #todo: 
// Nesse momento não há nenhume busca por fuction. 
// Device.

unsigned short 
pciCheckDevice (unsigned char bus, unsigned char slot)
{
    return (unsigned short) pciConfigReadWord ( 
                                bus, slot, 0, PCI_OFFSET_DEVICEID ); 
}


/*
 * pciCheckVendor:
 *     Check vendor, offset 0. 
 */

// #todo: 
// Nesse momento não há nenhume busca por fuction.
// Vendor.

unsigned short 
pciCheckVendor (unsigned char bus, unsigned char slot)
{
    return (unsigned short) pciConfigReadWord ( 
                                bus, slot, 0, PCI_OFFSET_VENDORID );
}

/*
 ***************************************
 * init_pci:
 * 
 *     Inicializa o módulo PCI em Kernel Mode, dentro do Kernel Base. 
 * 
 * todo: 
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

    g_driver_pci_initialized = (int) FALSE; 


    debug_print ("init_pci: [FIXME]\n");

    // Is PCI supported ?
    
    out32 ( 0xCF8, 0x80000000 );
    io_delay();
    
    data = (unsigned long) in32(0xCF8);
    io_delay();

 
	// #todo:
	// Fazer alguma coisa pra esse caso.
	// Talvez seja um 386 ou 486 sem suporte a PCI.
	// Talvez ISA.

    // STATUS_NOT_SUPPORTED
    // Can we live with no pci support. Maybe ISA.

    pci_supported = FALSE;

    if ( data != 0x80000000 ){
        panic ("init_pci: [FIXME] PCI not supported\n");
    }
    pci_supported = TRUE;


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
	// See: pciscan.c

    //debug_print ("init_pci: [TODO] Call pci_setup_devices() \n");
    
    Status = (int) pci_setup_devices();
    if (Status != 0){
        panic ("init_pci: pci_setup_devices fail\n");
    }

    // ...

    g_driver_pci_initialized = (int) TRUE; 

	//printf("Done\n");

    return (int) Status; 
}



__VOID_IRQ 
irq_SHARED0 (void)
{
}

__VOID_IRQ 
irq_SHARED1 (void)
{
}

__VOID_IRQ 
irq_SHARED2 (void)
{
}

__VOID_IRQ 
irq_SHARED3 (void)
{
}






































