// ethernet.c

#include <kernel.h>


// Sending a raw packet.
// #bugbug
// For now we're sending it only for intel e1000 nic device.
int 
ethernet_send(
    struct intel_nic_info_d *dev, 
    size_t len, 
    const char *data )
{

// #todo
// NIC Intel device structure.
    if ((void *) dev == NULL){
        printk("ethernet_send: dev\n");
        goto fail;
    }

// Telling to the network manager that we're gonna send something 
// a a nic device driver.
// see: network.c
    network_on_sending();

// Send frame via NIC.
// IN: nic, frame size, frame pointer.
    e1000_send( dev, len, data );

// done:
    return 0;

fail:
    return (int) -1;
}


