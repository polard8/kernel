
// ipv4.c

#include <kernel.h>

// handle ipv4 package
// Called by all the embedded nic device drivers.
// IN:
// buffer = The address after the ethernet header.
void 
network_handle_ipv4( 
    const unsigned char *buffer, 
    ssize_t size )
{
    struct ip_d *ip;
// The protocol for the payload.
    uint8_t Protocol=0;

    ip = (struct ip_d *) buffer;

    printf("network_handle_ipv4: ==== IP ====\n");

    if ( (void*) ip == NULL ){
        printf("network_handle_ipv4: ip\n");
        goto fail;
    }

    unsigned char *src_ipv4 = 
        (unsigned char *) &ip->ip_src.s_addr;
    unsigned char *dst_ipv4 = 
        (unsigned char *) &ip->ip_dst.s_addr;

// Show data.
// Bytes: Net-style.

    uint8_t v_hl = (uint8_t) ip->v_hl;
    uint8_t Version = (uint8_t) ((v_hl >> 4) & 0x0F);
    uint8_t Lenght  = (uint8_t) (v_hl & 0x0F);  // Header lenght. 5=20bytes.

    printf("IP Version: {%d}\n", Version);
    printf("Header lenght: {%d}\n", Lenght);

    if (Version!=4){
        printf("Not version 4\n");
        goto fail;
    }

// Total lenght (16bits)
// (IP + (TCP + data)) given in bytes.
// 20~65535
    printf("Total lenght: {%d}\n",ip->ip_len);

    if (ip->ip_len < 20 || ip->ip_len > 65535){
        //#debug
        panic("Bad total lenght\n");
    }


// List of IP protocol numbers
// See:
// https://en.wikipedia.org/wiki/List_of_IP_protocol_numbers

    Protocol = (uint8_t) ip->ip_p;
    printf("Protocol: {%xH}\n",Protocol);

// 0x01 -  1 - ICMP - Internet Control Message Protocol
// 0x06 -  6 - TCP  - Transmission Control Protocol
// 0x11 - 17 - UDP  - User Datagram Protocol

// ping?
    if (Protocol == PROTOCOL_IP_ICMP)
    {
        printf("ICMP Protocol\n");
        //network_handle_icmp(..);
    }
// TCP
    if (Protocol == PROTOCOL_IP_TCP)
    {
        printf("TCP Protocol\n");
        //network_handle_tcp(..);
    }
// UCP
    if (Protocol == PROTOCOL_IP_UDP)
    {
        printf("UDP Protocol\n");
        network_handle_udp(
            (buffer + IP_HEADER_LENGHT),
            ip->ip_len 
            );
        return;
    }

// ---------------
// Not to me.
    if ( dst_ipv4[3] != 112 ||
         dst_ipv4[2] != 1 ||
         dst_ipv4[1] != 168 ||
         dst_ipv4[0] != 192 )
    {
        printf ("NOT TO ME!\n");
        goto fail; 
    }

// ---------------
// To me.
    printf ("TO ME!\n");
    //printf("Src IPV4: {%x}\n", ip->ip_src.s_addr);
    //printf("Dst IPV4: {%x}\n", ip->ip_dst.s_addr);
    // destination
    printf ("Src: 0={%d} | 1={%d} | 2={%d} | 3={%d}\n",
        src_ipv4[0], src_ipv4[1], src_ipv4[2], src_ipv4[3]);
    printf ("Dst: 0={%d} | 1={%d} | 2={%d} | 3={%d}\n",
        dst_ipv4[0], dst_ipv4[1], dst_ipv4[2], dst_ipv4[3]);

    // hang
    printf ("network_handle_ipv4: #breakpoint :)\n");
    refresh_screen();
    while(1){}

fail:
    refresh_screen();
    return;
}

