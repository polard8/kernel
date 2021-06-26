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

    register int i=0;
    int Status = 0;
    int Max = PCI_DEVICE_LIST_SIZE; 
    unsigned long data=0;


    g_driver_pci_initialized = (int) FALSE; 
    pci_supported = FALSE;

    debug_print ("init_pci: [FIXME]\n");


//
// Supported ?
//

// ++
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

    if ( data != 0x80000000 ){
        panic ("init_pci: PCI not supported\n");
    }
    pci_supported = TRUE;
// --


	//#todo: 
	//Colocar esse status na estrutura platform->pci_supported.
	//Talvez assim: platform->platform_type.

	//#debug
	//refresh_screen();
	//while(1){}


// ==========

    // Initialise PCI device list.
    // Initialise the offset.

    for ( i=0; i<Max; ++i ){
        pcideviceList[i] = (unsigned long) 0;
    };
    pciListOffset = 0;

//
// Devices
//

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
    int Status = -1;
    struct pci_device_d *D; 
    uint32_t data=0;
    
    // char, block, network
    int __class=0;
    
    // name support.
    char __tmpname[64];
    char *newname;


    // #debug
    debug_print("pciHandleDevice:\n");
	//printf ("bus=%d dev=%d fun=%d \n", bus, dev, fun);

//
// PCI device
//
    D = (void *) kmalloc ( sizeof( struct pci_device_d  ) );

    if ( (void *) D == NULL ){
        panic ("pciHandleDevice: D\n");
    }else{
        D->objectType  = ObjectTypePciDevice;
        D->objectClass = ObjectClassKernelObjects;
        D->used  = (int) TRUE;
        D->magic = (int) 1234;

        D->id = (int) pciListOffset;

        // Localização.
        D->bus  = (unsigned char) bus;
        D->dev  = (unsigned char) dev;
        D->func = (unsigned char) fun; 

        // PCI Header.
        D->Vendor = (unsigned short) pciCheckVendor(bus,dev);
        D->Device = (unsigned short) pciCheckDevice(bus,dev);

        D->name = "pci-device-no-name";

		// #debug
		// printf ("$ vendor=%x device=%x \n",D->Vendor, D->Device);

        // OK, it is working
        // #todo: 
        // Nao deveriamos estar usando rotina que pertence ao modulo ata.
        // precisamos de uma rotina do modulo pci
        data = (uint32_t) diskReadPCIConfigAddr ( bus, dev, fun, 8 );
        D->classCode = (data >> 24) & 0xff;
        D->subclass  = (data >> 16) & 0xff;

		//#bugbug: Isso falhou. Deletar isso e trabalhar essas funções.
		//D->classCode = (unsigned char) pciGetClassCode(bus, dev);
		//D->subclass = (unsigned char) pciGetSubClass(bus, dev); 

        D->irq_line = (unsigned char) pciGetInterruptLine(bus,dev);
        D->irq_pin  = (unsigned char) pciGetInterruptPin(bus,dev);

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

        // #bugbug
        // Ver em que hora que os buffers são configurados.
        // precisam ser os mesmos encontrados na 
        // infraestrutura de network e usados pelos aplicativos.

        // e1000 = 0x8086 0x100E
        // 82540EM Gigabit Ethernet Controller
        if ( (D->Vendor == 0x8086)  && 
             (D->Device == 0x100E ) && 
             (D->classCode == PCI_CLASSCODE_NETWORK) )
        {
            //serial debug
            debug_print ("pciHandleDevice: [0x8086:0x100E] e1000 found \n"); 
            //printf("b=%d d=%d f=%d \n", D->bus, D->dev, D->func );
            //printf("82540EM Gigabit Ethernet Controller found\n");

            /*
            // See: 
            // 2io/dev/tty/netdev/e1000/e1000.c
            Status = (int) e1000_init_nic ( 
                               (unsigned char) D->bus, 
                               (unsigned char) D->dev, 
                               (unsigned char) D->func, 
                               (struct pci_device_d *) D );

            // OK. Setup e1000 nic device.
            if (Status == 0)
            {
                //irq and reset.
                // See: 
                // 2io/dev/tty/netdev/e1000/e1000.c
                
                // #debug
                // currentNIC foi configurado pela rotina acima.
                if ( D->irq_line != currentNIC->pci->irq_line )
                {
                     panic("pciHandleDevice: D->irq_line fail\n");
                }
                
                e1000_setup_irq( D->irq_line );  //currentNIC->pci->irq_line
                e1000_reset_controller();
                printf ("pciHandleDevice: Unlocking interrupt handler \n");
                e1000_interrupt_flag = TRUE;
                //class=network device,
                __class = 3;
 
            }else{
                panic ("pciHandleDevice: NIC Intel [0x8086:0x100E]");
            };
            */
        }


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

            /*
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
                 panic ("pciHandleDevice: [0x8086:0x7000] Serial controller\n");
             };
             */
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

        if ( pciListOffset < 0 || pciListOffset >= PCI_DEVICE_LIST_SIZE )
        { 
            
            // #bugbug
            // Suspendendo isso porque esta sujaando muito a tela
            // na maquina real.
            printf ("pciHandleDevice: [FAIL] No more slots!\n");
            
            //debug_print ("pciHandleDevice: [FAIL] No more slots!\n");
            
            return (int) (-1);
        }

        // Saving.
        pcideviceList[pciListOffset] = (unsigned long) D;
        pciListOffset++;

        // #debug
        //printf("$");
    };

//
// == Name ==========================================
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
    if ( (void*) newname == NULL ){
        panic("pciHandleDevice: [FAIL] newname\n");
    }
    strcpy (newname,__tmpname);

//
// == file ====================================
//
    // Agora registra o dispositivo pci na lista genérica
    // de dispositivos.
    // #importante: ele precisa de um arquivo 'file'.
    
    file *__file;
    
    __file = (file *) kmalloc ( sizeof(file) );
    
    if ( (void *) __file == NULL ){
        panic("pciHandleDevice: __file fail, can't register device\n");
    }else{
        __file->used  = TRUE;
        __file->magic = 1234;
        __file->isDevice = TRUE;


        //debug_print("pciHandleDevice: #todo Call devmgr_register_device()\n");
        
        // Register

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






































