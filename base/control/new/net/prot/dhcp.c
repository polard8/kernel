
// dhcp.c

#include <kernel.h>


// source ip
unsigned char __dhcp_source_ipv4[4] = { 
    0, 0, 0, 0 
};
// destination ip (broadcast)
unsigned char __dhcp_target_ipv4[4]  = { 
    0xFF, 0xFF, 0xFF, 0xFF  
};

// Target MAC.
unsigned char __dhcp_target_mac[6] = { 
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF 
};


void network_dhcp_dialog(void)
{
    char message[512];
    memset(message,0,sizeof(message));
    sprintf(message,"#todo dhcp structure\n");

    struct dhcp_d *dhcp;
    dhcp = (struct dhcp_d *) kmalloc ( sizeof(struct dhcp_d) );
    if ((void*) dhcp == NULL){
        printf("network_dhcp_dialog: dhcp\n");
        goto fail;
    }

    dhcp->op    = 1;
    dhcp->htype = 1;
    dhcp->hlen  = 6;
    dhcp->hops  = 0;
    //#todo: //dhcp->xid   = htonl(0x3903F326);
    //#todo: //dhcp->secs  = htons(0);
    //#todo: dhcp->flags = htons(0x0000);
    dhcp->ciaddr= 0;
    dhcp->yiaddr= 0;
    dhcp->siaddr = 0;
    dhcp->giaddr = 0;


    //memset(dhcp->sname, 0, 64);
   //memset(dhcp->file, 0, 128);

    dhcp->options[0] = OPT_DHCP_MESSAGE_TYPE;
    dhcp->options[1] = 0x01;

// DHCP Message Type
// #todo: via parameter.
    //dhcp->options[2] = message_type;

/*
    switch(message_type){
        case DHCP_DISCOVER:
            break;
        case DHCP_REQUEST:
            break;
        default:
            printf("DHCP UNKNOWN\n");
            break;   
    };
*/

    network_send_udp( 
        __dhcp_source_ipv4,   // scr ip
        __dhcp_target_ipv4,    // dst ip
        __dhcp_target_mac,    // dst mac
        68,                  // source port
        67,                  // target port
        message,                         // msg - dhcp structure.
        512 );                               // msg lenght

    return;
fail:
    refresh_screen();
    return;
}



