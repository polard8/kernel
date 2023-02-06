
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

    network_send_udp( 
        __dhcp_source_ipv4,   // scr ip
        __dhcp_target_ipv4,    // dst ip
        __dhcp_target_mac,    // dst mac
        67,                  // source port
        68,                  // target port
        message,                         // msg - dhcp structure.
        512 );                               // msg lenght

}



