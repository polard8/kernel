
// atapci.c



#include <kernel.h>


// #todo:
// Checar se temos uma lista dessa no suporte a PCI.

const char *pci_classes[] = {
    "Unknown [old]",
    "Mass storage",
    "Network",
    "Display",
    "Multimedia device",
    "Memory",
    "Bridge device",
    "Simple Communication",
    "Base System Peripheral",
    "Input Device",
    "Docking Station",
    "Processor",
    "Serial Bus",
    "Wireless",
    "Inteligent I/O",
    "Satellite Communications",
    "Encrypt/Decrypt",
    "Data acquisition and signal processing",
    [255]="Unknown"
};




/* 
 * diskReadPCIConfigAddr:
 *     READ 
 */

uint32_t 
diskReadPCIConfigAddr ( 
    int bus, 
    int dev,
    int fun, 
    int offset )
{
    out32 ( PCI_PORT_ADDR, CONFIG_ADDR( bus, dev, fun, offset ) );

    return (uint32_t) in32 (PCI_PORT_DATA);
}


/* 
 * diskWritePCIConfigAddr:
 *     WRITE 
 */

void 
diskWritePCIConfigAddr ( 
    int bus, 
    int dev,
    int fun, 
    int offset, 
    int data )
{
    out32 ( PCI_PORT_ADDR, CONFIG_ADDR( bus, dev, fun, offset ) );

    out32 ( PCI_PORT_DATA, data );
}


















