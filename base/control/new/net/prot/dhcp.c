
// dhcp.c
// dhcp initialization.
// 2023 - Created by Fred Nora.
// Credits: Nelson Cole. (Sirius OS)

#include <kernel.h>


struct dhcp_info_d  dhcp_info;

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


void 
network_dhcp_send(
    struct dhcp_d *dhcp,
    uint8_t source_ip[4], 
    uint8_t target_ip[4], 
    int message_type, 
    unsigned short sport, 
    unsigned short dport )
{
    //char message[512];
    //memset(message,0,sizeof(message));
    //sprintf(message,"#todo dhcp structure\n");

    int opt_size = 0;

    //struct dhcp_d *dhcp;
    //dhcp = (struct dhcp_d *) kmalloc ( sizeof(struct dhcp_d) );
    if ((void*) dhcp == NULL){
        printf("network_dhcp_dialog: dhcp\n");
        goto fail;
    }

    dhcp->op    = 1;
    dhcp->htype = 1;
    dhcp->hlen  = 6;
    dhcp->hops  = 0;
    dhcp->xid   = ToNetByteOrder32(0x3903F326);
    dhcp->secs  = ToNetByteOrder16(0);
    dhcp->flags = ToNetByteOrder16(0x0000);
    dhcp->ciaddr= 0;
    dhcp->yiaddr= 0;
    dhcp->siaddr = 0;
    dhcp->giaddr = 0;

// Fill mac

    //fillMac(dhcp->chaddr, default_ethernet_device.mac);

    int i=0;
    if ( (void*) currentNIC != NULL )
    {
        for ( i=0; i<6; i++ ){
            dhcp->chaddr[i] = (uint8_t) currentNIC->mac_address[i];  // source 
        };
    }



    memset(dhcp->sname, 0, 64);
    memset(dhcp->file, 0, 128);
    dhcp->magic_cookie = ToNetByteOrder32(0x63825363);

    dhcp->options[0] = OPT_DHCP_MESSAGE_TYPE;
    dhcp->options[1] = 0x01;

// DHCP Message Type
    dhcp->options[2] = message_type;


    switch(message_type){

        case DHCP_DISCOVER:
            printf("DHCP DISCOVERY\n");
            // Parameter Request list
            dhcp->options[3] = OPT_PARAMETER_REQUEST;
            dhcp->options[4] = 3;
            dhcp->options[5] = OPT_SUBNET_MASK;
            dhcp->options[6] = OPT_ROUTER;
            dhcp->options[7] = OPT_DNS;
            // Option End
            dhcp->options[8] = OPT_END;
            opt_size = 9;
            break;

        case DHCP_REQUEST:
            printf("DHCP REQUEST\n");
            // Requested IP address
            dhcp->options[3] = OPT_REQUESTED_IP_ADDR;
            dhcp->options[4] = IPV4_IN_BYTES;
            dhcp->options[5] = (uint8_t) source_ip[0];
            dhcp->options[6] = (uint8_t) source_ip[1];
            dhcp->options[7] = (uint8_t) source_ip[2];
            dhcp->options[8] = (uint8_t) source_ip[3];
            // Server Identifier
            dhcp->options[9] = OPT_SERVER_ID;
            dhcp->options[10] = IPV4_IN_BYTES;
            dhcp->options[11] = (uint8_t) target_ip[0];
            dhcp->options[12] = (uint8_t) target_ip[1];
            dhcp->options[13] = (uint8_t) target_ip[2];
            dhcp->options[14] = (uint8_t) target_ip[3];
            // Parameter Request list 
            dhcp->options[15]= OPT_PARAMETER_REQUEST;
            dhcp->options[16]= 3;
            dhcp->options[17]= OPT_SUBNET_MASK;
            dhcp->options[18]= OPT_ROUTER;
            dhcp->options[19]= OPT_DNS;
            // Option End
            dhcp->options[20]= OPT_END;
            opt_size = 21;

            break;
        default:
            printf("DHCP UNKNOWN\n");
            break;   
    };

    printf("Sending udp ...\n");

    network_send_udp( 
        __dhcp_source_ipv4,    // scr ip
        __dhcp_target_ipv4,    // dst ip
        __dhcp_target_mac,    // dst mac
        sport,                  // source port
        dport,                  // target port
        dhcp,                         // (data) msg - dhcp structure.
        sizeof(struct dhcp_d) - 308 + opt_size );   // data len msg lenght

    //printf("done\n");

    return;
fail:
    refresh_screen();
    return;
}


// Initialize the dhcp_info structure,
// by calling the dialog with the dhcp server via dhcp/udp/ip.
int network_initialize_dhcp(void)
{
    dhcp_info.initialized = FALSE;
    dhcp_info.host_ip = (unsigned int) 0;
    //...

    struct dhcp_d *dhcp;

    dhcp = (struct dhcp_d *) kmalloc ( sizeof(struct dhcp_d) );
    if ((void*) dhcp == NULL){
        printf("network_initialize_dhcp: dhcp\n");
        goto fail;
    }

//
// Dialog
//

// Send discover
    network_dhcp_send( 
        dhcp,  //header 
        __dhcp_source_ipv4,  // 0.0.0.0 
        __dhcp_target_ipv4,  // Broadcast
        DHCP_DISCOVER,  // message code. 
        68,                             // s port
        67 );                          // d port

// listen 68

/*
// Send request
    network_dhcp_send( 
        #todo my ip,
        #todo dhcp server ip,
        dhcp,  //header 
        DHCP_REQUEST,  // message code. 
        ?,                             // s port
        ? );                          // d port
*/

// listen


    printf("network_initialize_dhcp: done\n");
    //dhcp_info.initialized =  TRUE;
    
    //while(1){}
    return 0;
fail:
    printf("network_initialize_dhcp: fail\n");
    dhcp_info.initialized =  FALSE;
    
    while(1){}
    return -1;
}



