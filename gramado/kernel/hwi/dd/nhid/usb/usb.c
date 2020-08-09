/*
 * File: usb.c
 *
 * Suporte ao controlador de USB.
 */


// See:
// https://wiki.osdev.org/Universal_Serial_Bus


// USB System 
// A USB System consists of three discrete parts: 
// >> the USB device(s), 
// >> the USB interconnect, and 
// >> the USB host.


#include <kernel.h>




int 
serial_bus_controller_init ( unsigned char bus, 
                         unsigned char dev, 
                         unsigned char fun, 
                         struct pci_device_d *pci_device )

{
	//pci info.
    uint32_t data;
    unsigned long phy_address;
    unsigned short tmp16;
    uint32_t i; 



	// #debug
    printf ("serial_bus_controller_init:\n");
    debug_print ("serial_bus_controller_init:\n");


    //
    // #todo
    //

    return 0;



    data = (uint32_t) diskReadPCIConfigAddr ( bus, dev, fun, 0 );

    unsigned short Vendor = (unsigned short) (data       & 0xffff);
    unsigned short Device = (unsigned short) (data >> 16 & 0xffff);



    //if ( Vendor != 0x8086 || Device != 0x7000 )
         //return -1;
         
         
	//#debug

    printf ("Vendor=%x \n", (data       & 0xffff) );
    printf ("Device=%x \n", (data >> 16 & 0xffff) );


	//pci device struct
	//passado via argumento. 

    if ( (void *) pci_device ==  NULL )
    {

        panic ("e1000_init_nic: pci_device\n");
    }else{

        pci_device->used = 1;
        pci_device->magic = 1234;

        pci_device->bus  = (unsigned char) bus;
        pci_device->dev  = (unsigned char) dev;
        pci_device->func = (unsigned char) fun;

        pci_device->Vendor = (unsigned short) (data       & 0xffff);
        pci_device->Device = (unsigned short) (data >> 16 & 0xffff);


		// #IMPORTANTE
		// #bugbug:
		// Esse driver é para placa Intel, vamos cancelar a inicialização 
		// do driver se a placa não for Intel.

		// 8086:100e
		// 82540EM Gigabit Ethernet Controller

		// #todo
		// Fazer uma lista de dispositivos Intel suportados por esse driver.
		// +usar if else.
		// já fizemos essa checagem antes.

		if ( pci_device->Vendor != 0x8086 || 
		     pci_device->Device != 0x7000 )
		{
			panic ("serial_bus_controller_init: serial bus controller not found\n");
		}


		//
		// BARs
		//

        pci_device->BAR0 = (unsigned long) diskReadPCIConfigAddr ( bus, 
                                               dev, fun, 0x10 );
        pci_device->BAR1 = (unsigned long) diskReadPCIConfigAddr ( bus, 
                                               dev, fun, 0x14 ); 
        pci_device->BAR2 = (unsigned long) diskReadPCIConfigAddr ( bus, 
                                               dev, fun, 0x18 );
        pci_device->BAR3 = (unsigned long) diskReadPCIConfigAddr ( bus, 
                                               dev, fun, 0x1C );
        pci_device->BAR4 = (unsigned long) diskReadPCIConfigAddr ( bus, 
                                               dev, fun, 0x20 );
        pci_device->BAR5 = (unsigned long) diskReadPCIConfigAddr ( bus, 
                                               dev, fun, 0x24 );


		// IRQ.

		// irq
        pci_device->irq_line = (uint8_t) pciConfigReadByte ( bus, 
                                             dev, fun, 0x3C );

		// letras
        pci_device->irq_pin  = (uint8_t) pciConfigReadByte ( bus, 
                                             dev, fun, 0x3D ); 


		// ##importante:
		// Grab the Base I/O Address of the device
		// Aqui nós pegamos o endereço dos registadores na BAR0,
		// Então mapeamos esse endereço físico para termos um endereço virtual 
		// para manipularmos os registradores. 

        phy_address = ( pci_device->BAR0 & 0xFFFFFFF0 );

        //...
    };


    printf("phy_address = %x\n",phy_address);
    


    //#todo
        
    //
    //   Continuar ;;;;;;...............................................
    //


   refresh_screen();
    while(1){}




   //#todo
   // copiar do nic.

    //provisório pra agradas a rotina de sondagem de pci.
    return 0;
}

void usbInit (void)
{	
	//return;
}


//
// End.
//

