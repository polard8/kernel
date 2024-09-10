// e1000.c
// Top layer interface for the e1000 NIC driver.
// Created by Fred Nora.


#include <kernel.h>


int 
e1000_send(
    struct intel_nic_info_d *dev, 
    size_t len, 
    const char *data )
{
    if ((void*) dev == NULL)
        goto fail;

    if (len <0)
        goto fail;

// Send
    e1000hw_send(dev,len,data);

fail:
    return (int) -1;
}

// #todo ioctl
int 
e1000_ioctl ( 
    int fd, 
    unsigned long request, 
    unsigned long arg )
{
    debug_print("e1000_ioctl: #todo\n");

// Parameters:
    if ( fd < 0 || fd >= OPEN_MAX ){
        return (int) (-EBADF);
    }

    switch (request){
    //case ?:
        //break;
    default:
        return (int) (-EINVAL);
        break;
    };

fail:
    return (int) -1;
}

