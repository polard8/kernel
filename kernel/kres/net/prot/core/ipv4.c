// ipv4.c
// Created by Fred Nora.

#include <kernel.h>

// When receving IPV4 packet from NIC device.
// handle ipv4 package
// IN:
// buffer = ip header base address.
// size = ip packet size. (ip header + ip payload).
void 
network_handle_ipv4( 
    const unsigned char *buffer, 
    ssize_t size )
{
// Network layer.
// Called by network_on_receiving() in network.c.
// 0x0800

// The buffer.
    struct ip_d *ip;
// The protocol for the payload.
    uint8_t Protocol=0;

    //printk ("IP: received\n");

// #warning
// It's ok to use pointer here.
// We're not allocating memory, we're using 
// a pre-allocated buffer.
    ip = (struct ip_d *) buffer;
    if ((void*) ip == NULL){
        printk("network_handle_ipv4: ip\n");
        goto fail;
    }

// The minimum size.
// Only the ip header.
    //if (size < IP_HEADER_LENGHT){
    //    printk("network_handle_ipv4: size\n");
    //    goto fail;
    //}

// IP
// #todo
// Let's save it for future use.
// We're gonna need to send responses.

    unsigned char *src_ipv4 = (unsigned char *) &ip->ip_src.s_addr;
    unsigned char *dst_ipv4 = (unsigned char *) &ip->ip_dst.s_addr;

// Save the IP of the caller.
    network_fill_ipv4(__saved_caller_ipv4, src_ipv4);

// Show data.
// Bytes: Net-style.

    uint8_t v_hl = (uint8_t) ip->v_hl;
    uint8_t Version = (uint8_t) ((v_hl >> 4) & 0x0F);
    uint8_t Lenght  = (uint8_t) (v_hl & 0x0F);  // Header lenght. 5=20bytes.

    //printk("IP Version: {%d}\n", Version);
    //printk("Header lenght: {%d}\n", Lenght);

    if (Version != 4){
        printk("IP: Not version 4\n");
        goto fail;
    }

// Total lenght (16bits)
// ip header + ip payload.
// (IP + (TCP + data)) given in bytes.
// 20~65535
    //printk("Total lenght: {%d}\n",ip->ip_len);

// #bugbug
// What is the style of this information?
// little endian?
    uint16_t ip_lenght = (uint16_t) FromNetByteOrder16(ip->ip_len);
    if ( ip_lenght < 20 || ip_lenght > 65535 )
    {
        //#debug
        printk("IP: size={%d}\n",size);
        printk("IP: ip_lenght={%d}\n",ip_lenght);
        // #todo:
        // Maybe simply drop it for now.
        panic("IP: Bad total lenght #debug\n");
    }


    unsigned char *payload_pointer;
    ssize_t payload_size;

    payload_pointer = (buffer + IP_HEADER_LENGHT);
    payload_size = (ip_lenght - IP_HEADER_LENGHT);


    //printk ("target: %d.%d.%d.%d \n",
    //    dst_ipv4[0],dst_ipv4[1],dst_ipv4[2],dst_ipv4[3]);
    //printk("ip_sum={%x} \n",ip->ip_sum);

//
// Protocol
//

// List of IP protocol numbers
// See:
// https://en.wikipedia.org/wiki/List_of_IP_protocol_numbers

// 0x01 -  1 - ICMP - Internet Control Message Protocol
// 0x06 -  6 - TCP  - Transmission Control Protocol
// 0x11 - 17 - UDP  - User Datagram Protocol

    Protocol = (uint8_t) ip->ip_p;
    //printk("Protocol: {%xH}\n",Protocol);

// UDP
    if (Protocol == PROTOCOL_IP_UDP){
        //printk("IP: UDP Protocol\n");
        network_handle_udp( payload_pointer, payload_size );
        return;
    }
// ICMP: ping?
    if (Protocol == PROTOCOL_IP_ICMP){
        //printk("IP: ICMP Protocol\n");
        //network_handle_icmp(..);
        goto drop;
    }
// TCP
    if (Protocol == PROTOCOL_IP_TCP){
        //printk("IP: TCP Protocol\n");        
        network_handle_tcp( payload_pointer, payload_size );
        return;
    }

    // #debug
    // Not supported ipv4 protocol.

drop:
    return;

// debug:
// ---------------
// Not to me.
    /*
    if ( dst_ipv4[3] != 12 ||
         dst_ipv4[2] != 1 ||
         dst_ipv4[1] != 168 ||
         dst_ipv4[0] != 192 )
    {
        printk ("IP: NOT TO ME. Drop it\n");
        return;
    }
    */

// ---------------
// To me.

    //printk ("IP: TO ME!\n");
    //printk("Src IPV4: {%x}\n", ip->ip_src.s_addr);
    //printk("Dst IPV4: {%x}\n", ip->ip_dst.s_addr);
    // destination

    printk ("Src: %d.%d.%d.%d\n",
        src_ipv4[0], src_ipv4[1], src_ipv4[2], src_ipv4[3]);
    printk ("Dst:  %d.%d.%d.%d\n",
        dst_ipv4[0], dst_ipv4[1], dst_ipv4[2], dst_ipv4[3]);

    // hang
    printk("network_handle_ipv4: #breakpoint :)\n");
    while (1){
    };

fail:
    printk("network_handle_ipv4: Fail\n");
    return;
}

