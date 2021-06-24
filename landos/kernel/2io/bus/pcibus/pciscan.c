


#include <kernel.h>  


int pci_setup_devices (void)
{
    debug_print ("pci_setup_devices: [TODO] \n");
    return -1;
}


/*
 * scan_pci_device_list:
 *     Procurar na lista de dispositivos por um dispositivo de determinados 
 * vendor e device.
 */

struct pci_device_d *scan_pci_device_list ( 
    unsigned short vendor, 
    unsigned short device )
{
    struct pci_device_d *D;

    register int i=0;


	// #bugbug
	// Nossa lista só tem 32 slots por enquanto.

    for ( i=0; i<32; i++ )
    {
        D = (void *) pcideviceList[i];

        if ( (void *) D != NULL )
        {
            if ( D->used == TRUE && D->magic == 1234 )
            {
                if ( D->Vendor == vendor && D->Device == device )
                {
                    return (struct pci_device_d *) D;
                }
            }
        }
    };

    return NULL;
}

/*
 * scan_pci_device_list2:
 *     Procurar na lista de dispositivos por um dispositivo de determinada 
 * classe e subclasse.
 */

struct pci_device_d *scan_pci_device_list2 ( 
    unsigned char class, 
    unsigned char subclass )
{
    struct pci_device_d *D;

    int i=0;

	// #bugbug
	// Nossa lista só tem 32 slots por enquanto.

    for ( i=0; i<32; i++ )
    {
        D = (void *) pcideviceList[i];

        if ( (void *) D != NULL )
        {
            if ( D->used == TRUE && D->magic == 1234 )
            {
                if ( D->classCode == class && D->subclass == subclass )
                {
                    return (struct pci_device_d *) D;
                }
            }
        }
    };

    return NULL;
}

//
// End.
//





