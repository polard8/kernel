// ethernet.c

#include <kernel.h>


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

// Send frame via NIC.
// IN: nic, frame size, frame pointer.
    e1000_send( dev, len, data );

// done:
    return 0;

fail:
    return (int) -1;
}


